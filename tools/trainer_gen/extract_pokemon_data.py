#!/usr/bin/env python3
"""
Extract Pokemon data from pokeemerald-expansion codebase
Generates a JSON database with species name, dex number, base stats, and types
"""

import re
import json
from pathlib import Path
from typing import Dict, List, Optional

# Type name mapping
TYPE_MAP = {
    'TYPE_NONE': 'None',
    'TYPE_NORMAL': 'Normal',
    'TYPE_FIGHTING': 'Fighting',
    'TYPE_FLYING': 'Flying',
    'TYPE_POISON': 'Poison',
    'TYPE_GROUND': 'Ground',
    'TYPE_ROCK': 'Rock',
    'TYPE_BUG': 'Bug',
    'TYPE_GHOST': 'Ghost',
    'TYPE_STEEL': 'Steel',
    'TYPE_MYSTERY': 'Mystery',
    'TYPE_FIRE': 'Fire',
    'TYPE_WATER': 'Water',
    'TYPE_GRASS': 'Grass',
    'TYPE_ELECTRIC': 'Electric',
    'TYPE_PSYCHIC': 'Psychic',
    'TYPE_ICE': 'Ice',
    'TYPE_DRAGON': 'Dragon',
    'TYPE_DARK': 'Dark',
    'TYPE_FAIRY': 'Fairy',
}

def parse_species_file(file_path: Path, generation: int) -> List[Dict]:
    """Parse a species info file and extract Pokemon data"""
    pokemon_list = []

    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Track current family context
    current_family = None

    # First, find all P_FAMILY_ blocks to map species to families
    family_pattern = r'#if\s+P_FAMILY_(\w+)\s*\n(.*?)(?=#(?:if|endif|else)|$)'
    family_blocks = {}

    for family_match in re.finditer(family_pattern, content, re.DOTALL):
        family_name = family_match.group(1)
        block_content = family_match.group(2)

        # Find all SPECIES in this block
        species_in_block = re.findall(r'\[SPECIES_(\w+)\]', block_content)
        for species in species_in_block:
            family_blocks[species] = f"P_FAMILY_{family_name}"

    # Find all SPECIES_ entries
    # Pattern: [SPECIES_NAME] = { ... }
    species_pattern = r'\[SPECIES_(\w+)\]\s*=\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\}'

    for match in re.finditer(species_pattern, content, re.DOTALL):
        species_name = match.group(1)
        species_data = match.group(2)

        # Skip special entries
        if species_name in ['NONE', 'EGG']:
            continue

        # Get family for this species
        family = family_blocks.get(species_name, None)

        pokemon = {
            'species': species_name,
            'name': None,
            'natDexNum': None,
            'baseStats': {},
            'types': [],
            'bst': 0,
            'generation': generation,
            'family': family
        }

        # Extract species name
        name_match = re.search(r'\.speciesName\s*=\s*_\("([^"]+)"\)', species_data)
        if name_match:
            pokemon['name'] = name_match.group(1)
        else:
            # Use species constant name if no display name found
            pokemon['name'] = species_name.replace('_', ' ').title()

        # Extract national dex number
        dex_match = re.search(r'\.natDexNum\s*=\s*NATIONAL_DEX_(\w+)', species_data)
        if dex_match:
            pokemon['natDexNum'] = dex_match.group(1)
        else:
            # Use species name as fallback
            pokemon['natDexNum'] = species_name

        # Extract base stats
        stat_patterns = {
            'hp': r'\.baseHP\s*=\s*(\d+)',
            'atk': r'\.baseAttack\s*=\s*(\d+)',
            'def': r'\.baseDefense\s*=\s*(\d+)',
            'spa': r'\.baseSpAttack\s*=\s*(\d+)',
            'spd': r'\.baseSpDefense\s*=\s*(\d+)',
            'spe': r'\.baseSpeed\s*=\s*(\d+)',
        }

        all_stats_found = True
        for stat_key, pattern in stat_patterns.items():
            stat_match = re.search(pattern, species_data)
            if stat_match:
                pokemon['baseStats'][stat_key] = int(stat_match.group(1))
            else:
                all_stats_found = False
                break

        # Skip if we don't have all base stats
        if not all_stats_found:
            continue

        # Calculate BST
        pokemon['bst'] = sum(pokemon['baseStats'].values())

        # Extract types
        types_match = re.search(r'\.types\s*=\s*MON_TYPES\(([^)]+)\)', species_data)
        if types_match:
            types_str = types_match.group(1)
            # Extract TYPE_ constants
            type_constants = re.findall(r'TYPE_\w+', types_str)
            pokemon['types'] = [TYPE_MAP.get(t, t) for t in type_constants if t in TYPE_MAP]

        # Only add Pokemon with valid data
        if pokemon['name'] and pokemon['types'] and pokemon['baseStats']:
            pokemon_list.append(pokemon)

    return pokemon_list

def load_national_dex_numbers() -> Dict[str, int]:
    """Load national dex number mappings from pokedex.h"""
    dex_map = {}

    pokedex_h = Path(__file__).parent.parent.parent / 'include' / 'constants' / 'pokedex.h'

    if not pokedex_h.exists():
        print(f"Warning: Could not find {pokedex_h}")
        return dex_map

    with open(pokedex_h, 'r', encoding='utf-8') as f:
        content = f.read()

    # Find the NationalDexOrder enum
    enum_match = re.search(r'enum\s+NationalDexOrder\s*\{([^}]+)\}', content, re.DOTALL)

    if not enum_match:
        print("Warning: Could not find NationalDexOrder enum")
        return dex_map

    enum_content = enum_match.group(1)

    # Parse enum entries (NATIONAL_DEX_NAME,)
    # Enum values start at 0 and increment by 1
    enum_pattern = r'NATIONAL_DEX_(\w+)'
    current_value = 0

    for match in re.finditer(enum_pattern, enum_content):
        name = match.group(1)
        dex_map[name] = current_value
        current_value += 1

    return dex_map

def main():
    """Main extraction function"""
    print("Pokemon Data Extraction Tool")
    print("=" * 70)

    # Get the root directory (2 levels up from tools/trainer_gen/)
    script_dir = Path(__file__).parent
    root_dir = script_dir.parent.parent

    # Path to species info files
    species_info_dir = root_dir / 'src' / 'data' / 'pokemon' / 'species_info'

    if not species_info_dir.exists():
        print(f"Error: Species info directory not found at {species_info_dir}")
        return

    print(f"Searching for species files in: {species_info_dir}")

    # Load national dex numbers
    print("\nLoading national dex numbers...")
    dex_map = load_national_dex_numbers()
    print(f"Loaded {len(dex_map)} dex number mappings")
    if dex_map:
        sample_keys = list(dex_map.keys())[:5]
        print(f"  Sample keys: {', '.join(sample_keys)}")
        print(f"  Sample values: {[dex_map[k] for k in sample_keys]}")

    # Find all generation family files
    gen_files = sorted(species_info_dir.glob('gen_*_families.h'))

    if not gen_files:
        print("Error: No generation family files found!")
        return

    print(f"\nFound {len(gen_files)} generation files:")
    for gen_file in gen_files:
        print(f"  - {gen_file.name}")

    # Parse all files
    all_pokemon = []

    print("\nExtracting Pokemon data...")
    for gen_file in gen_files:
        # Extract generation number from filename (gen_X_families.h)
        gen_match = re.search(r'gen_(\d+)_families', gen_file.name)
        generation = int(gen_match.group(1)) if gen_match else 0

        print(f"  Processing {gen_file.name} (Generation {generation})...")
        pokemon_list = parse_species_file(gen_file, generation)
        print(f"    Found {len(pokemon_list)} Pokemon")
        all_pokemon.extend(pokemon_list)

    # Map national dex numbers
    print("\nMapping national dex numbers...")
    mapped_count = 0
    unmapped = []

    # Debug: Show first few pokemon keys
    if all_pokemon:
        sample_pokemon_keys = [p['natDexNum'] for p in all_pokemon[:5]]
        print(f"  Sample Pokemon keys: {sample_pokemon_keys}")

    for pokemon in all_pokemon:
        dex_key = pokemon['natDexNum']
        if dex_key and dex_key in dex_map:
            pokemon['natDexNum'] = dex_map[dex_key]
            mapped_count += 1
        else:
            # Try removing form suffixes for alternate forms
            # e.g., BULBASAUR_MEGA -> BULBASAUR
            base_key = None
            if dex_key:
                # Common form suffixes
                suffixes = ['_MEGA', '_MEGA_X', '_MEGA_Y', '_GMAX', '_ALOLA', '_GALAR', '_HISUI',
                           '_PALDEA', '_PRIMAL', '_ORIGIN', '_THERIAN', '_BLACK', '_WHITE',
                           '_BLUE', '_RED', '_ORANGE', '_YELLOW', '_GREEN', '_PURPLE',
                           '_INDIGO', '_VIOLET', '_SHADOW', '_PURIFIED', '_SKY', '_UNBOUND',
                           '_CORE', '_ATTACK', '_DEFENSE', '_SPEED', '_PLANT', '_SANDY',
                           '_TRASH', '_FROST', '_FAN', '_MOW', '_WASH', '_HEAT', '_BLADE']

                for suffix in suffixes:
                    if dex_key.endswith(suffix):
                        base_key = dex_key[:-len(suffix)]
                        break

                # Try the base key
                if base_key and base_key in dex_map:
                    pokemon['natDexNum'] = dex_map[base_key]
                    mapped_count += 1
                    continue

            # If still not found, set to 0
            if dex_key and len(unmapped) < 5:  # Only collect first 5 for debugging
                unmapped.append(dex_key)
            pokemon['natDexNum'] = 0

    print(f"  Mapped {mapped_count}/{len(all_pokemon)} Pokemon")
    if unmapped:
        print(f"  Sample unmapped keys: {', '.join(unmapped)}")

    # Sort by national dex number
    all_pokemon.sort(key=lambda x: (x['natDexNum'], x['name']))

    # Create output database
    output = {
        'metadata': {
            'total_pokemon': len(all_pokemon),
            'source': 'pokeemerald-expansion',
            'generation': 9
        },
        'pokemon': all_pokemon
    }

    # Write to JSON file
    output_file = script_dir / 'pokemon_data.json'
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2)

    print(f"\n{'=' * 70}")
    print(f"✓ Extraction complete!")
    print(f"✓ Total Pokemon extracted: {len(all_pokemon)}")
    print(f"✓ Database saved to: {output_file}")

    # Show some statistics
    print(f"\n{'=' * 70}")
    print("Statistics:")
    print(f"  Highest BST: {max(p['bst'] for p in all_pokemon)}")
    print(f"  Lowest BST: {min(p['bst'] for p in all_pokemon if p['bst'] > 0)}")

    # Type distribution
    type_count = {}
    for pokemon in all_pokemon:
        for type_name in pokemon['types']:
            type_count[type_name] = type_count.get(type_name, 0) + 1

    print(f"\nType Distribution (top 5):")
    for type_name, count in sorted(type_count.items(), key=lambda x: x[1], reverse=True)[:5]:
        print(f"  {type_name}: {count}")

    # Show preview
    print(f"\n{'=' * 70}")
    print("Preview (first 3 Pokemon):")
    print('=' * 70)
    for pokemon in all_pokemon[:3]:
        print(f"\n{pokemon['name']} (#{pokemon['natDexNum']:03d})")
        print(f"  Types: {', '.join(pokemon['types'])}")
        print(f"  Base Stats: HP {pokemon['baseStats']['hp']}, "
              f"Atk {pokemon['baseStats']['atk']}, "
              f"Def {pokemon['baseStats']['def']}, "
              f"SpA {pokemon['baseStats']['spa']}, "
              f"SpD {pokemon['baseStats']['spd']}, "
              f"Spe {pokemon['baseStats']['spe']}")
        print(f"  BST: {pokemon['bst']}")

if __name__ == "__main__":
    main()
