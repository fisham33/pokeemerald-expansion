#!/usr/bin/env python3
"""
Convert Pokemon Showdown Random Battle JSON to trainers.party format
Enhanced with Trainer Party Pool (TPP) support
"""

import json
import urllib.request
import random
import argparse
from typing import Dict, List, Any, Set, Optional
from pathlib import Path
import os

# URLs to fetch JSON from
RANDBATS_URLS = {
    "gen9randomdoublesbattle.json": "https://pkmn.github.io/randbats/data/gen9randomdoublesbattle.json",
    "gen9randombattle.json": "https://pkmn.github.io/randbats/data/gen9randombattle.json",
    "gen9babyrandombattle.json": "https://pkmn.github.io/randbats/data/gen9babyrandombattle.json",
}

# Role to Tag mapping for TPP
ROLE_TO_TAGS = {
    # Fast attackers make good leads
    "Doubles Fast Attacker": ["Lead"],

    # Setup sweepers are good aces
    "Doubles Setup Sweeper": ["Ace"],

    # Support roles
    "Doubles Support": ["Support"],

    # Bulky attackers can be versatile
    "Doubles Bulky Attacker": [],

    # Wallbreakers are good aces
    "Doubles Wallbreaker": ["Ace"],

    # Bulky setup can be aces
    "Doubles Bulky Setup": ["Ace"],

    # Other roles
    "Offensive Protect": [],
    "Bulky Protect": [],
    "Choice Item user": [],
    "Tera Blast user": [],
}

# Ability-based tags for weather/terrain
WEATHER_SETTER_ABILITIES = {
    "Drought", "Drizzle", "Snow Warning", "Sand Stream",
    "Electric Surge", "Grassy Surge", "Misty Surge", "Psychic Surge"
}

WEATHER_ABUSER_ABILITIES = {
    "Chlorophyll", "Swift Swim", "Sand Rush", "Slush Rush",
    "Surge Surfer", "Solar Power", "Rain Dish", "Ice Body",
    "Protosynthesis", "Quark Drive"
}

def fetch_json(url: str, local_file: str) -> Dict:
    """Fetch JSON from URL or use local file as fallback"""
    try:
        print(f"  Fetching {local_file} from URL...")
        with urllib.request.urlopen(url, timeout=10) as response:
            data = response.read()
        print(f"  ✓ Successfully fetched {local_file}")
        return json.loads(data)
    except Exception as e:
        print(f"  ✗ Error fetching from URL: {e}")
        print(f"  Trying local file '{local_file}'...")
        try:
            with open(local_file, 'r') as f:
                data = json.load(f)
            print(f"  ✓ Loaded {local_file} from disk")
            return data
        except Exception as e2:
            print(f"  ✗ Error reading local file: {e2}")
            return None

def load_all_json_files(file_filter: Optional[List[str]] = None) -> Dict[str, Dict]:
    """
    Load all available random battle JSON files

    Args:
        file_filter: Optional list of filenames to load. If None, loads all available files.
    """
    all_data = {}

    print("Loading Random Battle data files...")
    print("=" * 70)

    # Determine which files to load
    files_to_load = RANDBATS_URLS if file_filter is None else {
        f: RANDBATS_URLS[f] for f in file_filter if f in RANDBATS_URLS
    }

    for filename, url in files_to_load.items():
        # Check if file exists locally
        if os.path.exists(filename):
            print(f"\nProcessing {filename}:")
            data = fetch_json(url, filename)
            if data:
                all_data[filename] = data
        else:
            print(f"\n{filename} not found, skipping...")

    return all_data

def load_pokemon_database() -> Optional[Dict]:
    """Load the Pokemon database from pokemon_data.json"""
    db_path = Path(__file__).parent / 'pokemon_data.json'

    if not db_path.exists():
        return None

    with open(db_path, 'r', encoding='utf-8') as f:
        return json.load(f)

def load_trainer_archetypes() -> Optional[Dict]:
    """Load trainer archetype mappings"""
    archetypes_path = Path(__file__).parent / 'trainer_archetypes.json'

    if not archetypes_path.exists():
        return None

    with open(archetypes_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
        return data.get('archetypes', {})

def get_pokemon_types(pokemon_name: str, pokemon_db: Dict) -> List[str]:
    """Get types for a Pokemon from the database"""
    if not pokemon_db or 'pokemon' not in pokemon_db:
        return []

    # Normalize name for comparison (remove hyphens, spaces, make uppercase)
    normalized_search = pokemon_name.upper().replace('-', '').replace(' ', '')

    for poke in pokemon_db['pokemon']:
        poke_name = poke['name'].upper().replace('-', '').replace(' ', '')
        if poke_name == normalized_search:
            return poke.get('types', [])

    return []

def matches_archetype(pokemon_name: str, archetype_types: List[str], pokemon_db: Dict) -> bool:
    """
    Check if a Pokemon matches the archetype type requirements

    Args:
        pokemon_name: Name of the Pokemon
        archetype_types: List of type names the archetype uses
        pokemon_db: Pokemon database

    Returns:
        True if Pokemon has at least one matching type
    """
    if not archetype_types or 'Any' in archetype_types:
        return True

    pokemon_types = get_pokemon_types(pokemon_name, pokemon_db)

    # Check if any of the Pokemon's types match the archetype
    return any(ptype in archetype_types for ptype in pokemon_types)

def format_evs_ivs(values: Dict[str, int], all_value: int) -> str:
    """Format EVs or IVs to trainers.party format"""
    stat_map = {
        'hp': 'HP',
        'atk': 'Atk',
        'def': 'Def',
        'spa': 'SpA',
        'spd': 'SpD',
        'spe': 'Spe'
    }

    parts = []
    for stat in ['hp', 'atk', 'def', 'spa', 'spd', 'spe']:
        value = values.get(stat, all_value)
        parts.append(f"{value} {stat_map[stat]}")

    return " / ".join(parts)

def determine_tags(role_name: str, role_data: Dict, pokemon_data: Dict) -> List[str]:
    """Determine TPP tags for a Pokemon based on role and abilities"""
    tags = []

    # Add role-based tags
    if role_name in ROLE_TO_TAGS:
        tags.extend(ROLE_TO_TAGS[role_name])

    # Check abilities for weather/terrain tags
    abilities = role_data.get('abilities', pokemon_data.get('abilities', []))
    for ability in abilities:
        if ability in WEATHER_SETTER_ABILITIES:
            if "Weather Setter" not in tags:
                tags.append("Weather Setter")
        if ability in WEATHER_ABUSER_ABILITIES:
            if "Weather Abuser" not in tags:
                tags.append("Weather Abuser")

    return tags

def create_set_variants(
    pokemon_name: str,
    role_name: str,
    role_data: Dict,
    pokemon_data: Dict,
    include_tags: bool,
    max_moves: int = 4
) -> List[Dict[str, Any]]:
    """
    Create multiple variants of a set if it has multiple abilities/items/moves
    Returns list of set variants
    """
    variants = []

    # Get all possible values
    abilities = role_data.get('abilities', pokemon_data.get('abilities', []))
    items = role_data.get('items', pokemon_data.get('items', []))
    moves = role_data.get('moves', [])

    # Determine how many variants to create
    num_variants = 1
    if len(abilities) > 1 or len(items) > 1 or len(moves) > 5:
        num_variants = 2

    # Create variants
    for variant_num in range(num_variants):
        lines = []

        # Pokemon name @ Item
        if items:
            # Pick different items for each variant if possible
            if variant_num < len(items):
                item = items[variant_num]
            else:
                item = random.choice(items)
            lines.append(f"{pokemon_name} @ {item}")
        else:
            lines.append(pokemon_name)

        # Ability
        if abilities:
            # Pick different abilities for each variant if possible
            if variant_num < len(abilities):
                ability = abilities[variant_num]
            else:
                ability = random.choice(abilities)
            lines.append(f"Ability: {ability}")

        # EVs
        evs = role_data.get('evs', pokemon_data.get('evs', {}))
        if evs:
            ev_string = format_evs_ivs(evs, 0)
            lines.append(f"EVs: {ev_string}")

        # IVs
        ivs = role_data.get('ivs', pokemon_data.get('ivs', {}))
        if ivs:
            iv_string = format_evs_ivs(ivs, 31)
            lines.append(f"IVs: {iv_string}")

        # Tera Type
        tera_types = role_data.get('teraTypes', [])
        if tera_types:
            # Pick different tera types for variants if possible
            if variant_num < len(tera_types):
                tera_type = tera_types[variant_num]
            else:
                tera_type = random.choice(tera_types)
            lines.append(f"Tera Type: {tera_type}")

        # Determine tags for TPP
        tags = []
        if include_tags:
            tags = determine_tags(role_name, role_data, pokemon_data)
            if tags:
                lines.append(f"Tags: {' / '.join(tags)}")

        # Moves - ensure different combinations for each variant
        if moves:
            if len(moves) <= max_moves:
                selected_moves = moves
            else:
                # For variants, try to pick different combinations
                random.seed(variant_num)  # Use variant number for reproducibility
                selected_moves = random.sample(moves, max_moves)
                random.seed()  # Reset seed

            for move in selected_moves:
                lines.append(f"- {move}")

        variants.append({
            'text': '\n'.join(lines),
            'role': role_name,
            'tags': tags,
            'variant': variant_num + 1
        })

    return variants

def convert_pokemon_to_party_format(
    pokemon_name: str,
    pokemon_data: Dict,
    role_name: str = None,
    include_tags: bool = False,
    max_moves: int = 4
) -> List[Dict[str, Any]]:
    """
    Convert a single Pokemon's data to trainers.party format
    Returns list of dicts with 'text' and 'tags' keys
    """
    results = []

    roles = pokemon_data.get('roles', {})
    if not roles:
        return results

    if role_name and role_name in roles:
        roles_to_process = {role_name: roles[role_name]}
    else:
        roles_to_process = roles

    for role, role_data in roles_to_process.items():
        # Create set variants (1 or 2 depending on options)
        variants = create_set_variants(
            pokemon_name,
            role,
            role_data,
            pokemon_data,
            include_tags,
            max_moves
        )

        results.extend(variants)

    return results

def generate_trainer_pool(
    trainer_name: str,
    trainer_class: str,
    party_size: int,
    pool_size: int,
    data: Dict,
    pool_rules: str = "Weather Doubles",
    level_range: tuple = (50, 100),
    double_battle: bool = True
) -> str:
    """Generate a complete trainer with party pool"""

    lines = []

    # Trainer header
    lines.append(f"=== {trainer_name} ===")
    lines.append(f"Name: {trainer_name.replace('TRAINER_', '').replace('_', ' ').title()}")
    lines.append(f"Class: {trainer_class}")
    lines.append(f"Pic: {trainer_class}")
    lines.append(f"Gender: Male")
    lines.append(f"Music: Male")
    lines.append(f"Double Battle: {'Yes' if double_battle else 'No'}")
    lines.append(f"AI: Check Bad Move / Try To Faint / Check Viability")
    lines.append(f"Party Size: {party_size}")
    lines.append(f"Pool Rules: {pool_rules}")
    lines.append("")

    # Collect Pokemon entries
    pokemon_entries = []

    # Randomly select Pokemon from the dataset
    all_pokemon = list(data.keys())
    random.shuffle(all_pokemon)

    for pokemon_name in all_pokemon:
        if len(pokemon_entries) >= pool_size:
            break

        pokemon_data = data[pokemon_name]

        # Filter by level range
        poke_level = pokemon_data.get('level', 100)
        if not (level_range[0] <= poke_level <= level_range[1]):
            continue

        # Convert the Pokemon
        entries = convert_pokemon_to_party_format(
            pokemon_name,
            pokemon_data,
            include_tags=True,
            max_moves=4
        )

        if entries:
            # Pick the first variant
            entry = entries[0]
            pokemon_entries.append(entry['text'])

    # Add all Pokemon to the pool
    return '\n\n'.join(lines) + '\n\n'.join(pokemon_entries[:pool_size])

def main():
    """Main conversion function"""
    parser = argparse.ArgumentParser(
        description='Convert Random Battle JSON to trainers.party format'
    )
    parser.add_argument(
        '--input', '-i',
        help='Input JSON files (comma-separated). Leave blank to use all available files. '
             'Example: -i gen9randomdoublesbattle.json,gen9randombattle.json'
    )
    parser.add_argument(
        '--output', '-o',
        default='converted_movesets.txt',
        help='Output file (default: converted_movesets.txt)'
    )
    parser.add_argument(
        '--mode',
        choices=['single', 'all-roles', 'pool', 'trainer-pool'],
        default='pool',
        help='Conversion mode (default: pool)'
    )
    parser.add_argument(
        '--archetype',
        help='Filter Pokemon by type or trainer class. '
             'Examples: --archetype Water,Electric  or  --archetype Hiker'
    )
    parser.add_argument(
        '--pool-size',
        type=int,
        default=8,
        help='Pool size for trainer pools (default: 8)'
    )
    parser.add_argument(
        '--party-size',
        type=int,
        default=4,
        help='Party size for trainer pools (default: 4)'
    )
    parser.add_argument(
        '--split-output',
        action='store_true',
        help='Split output into separate files by format (singles/doubles/babies)'
    )
    parser.add_argument(
        '--level-min',
        type=int,
        help='Minimum level for trainer-pool mode (default: auto-detect based on input file)'
    )
    parser.add_argument(
        '--level-max',
        type=int,
        help='Maximum level for trainer-pool mode (default: auto-detect based on input file)'
    )

    args = parser.parse_args()

    print("Pokemon Showdown Random Battle to trainers.party Converter")
    print("Enhanced with Trainer Party Pool (TPP) Support")
    print("=" * 70)

    # Parse input file filter
    input_files = None
    if args.input:
        input_files = [f.strip() for f in args.input.split(',')]
        print(f"\nInput file filter: {', '.join(input_files)}")

    # Parse archetype
    archetype_types = None
    pokemon_db = None
    trainer_archetypes = None

    if args.archetype:
        # Load Pokemon database for type checking
        print("\nLoading Pokemon database...")
        pokemon_db = load_pokemon_database()

        if not pokemon_db:
            print("  Warning: Pokemon database not found. Run extract_pokemon_data.py first.")
            print("  Archetype filtering will be disabled.")
        else:
            print(f"  ✓ Loaded database with {pokemon_db['metadata']['total_pokemon']} Pokemon")

            # Load trainer archetypes
            trainer_archetypes = load_trainer_archetypes()

            # Determine if archetype is a trainer class or types
            archetype_value = args.archetype.strip()

            if trainer_archetypes and archetype_value in trainer_archetypes:
                # It's a trainer class
                archetype_types = trainer_archetypes[archetype_value]
                print(f"\nArchetype: {archetype_value} (Trainer Class)")
                print(f"  Preferred types: {', '.join(archetype_types)}")
            else:
                # Treat as comma-separated types
                archetype_types = [t.strip() for t in archetype_value.split(',')]
                print(f"\nArchetype: Custom types")
                print(f"  Types: {', '.join(archetype_types)}")

    # Load all available JSON files
    all_data_files = load_all_json_files(input_files)

    if not all_data_files:
        print("\n✗ No data files found! Please download at least one of:")
        for filename in RANDBATS_URLS.keys():
            print(f"  - {filename}")
        print("\nPlace them in the tools/trainer_gen/ directory.")
        return

    print(f"\n{'=' * 70}")
    print(f"Loaded {len(all_data_files)} data file(s)")
    total_pokemon = sum(len(data) for data in all_data_files.values())
    print(f"Total Pokemon: {total_pokemon}")
    print(f"\nMode: {args.mode}")
    print(f"Output: {'Split by format' if args.split_output else 'Combined'}")
    print("Converting...\n")

    # Determine source type from filename
    def get_source_type(filename):
        if 'double' in filename.lower():
            return 'Doubles'
        elif 'baby' in filename.lower():
            return 'Babies'
        else:
            return 'Singles'

    # Storage for entries - either combined or split by format
    if args.split_output:
        file_entries = {filename: [] for filename in all_data_files.keys()}
    else:
        all_entries = []

    # Process each data file
    for filename, data in all_data_files.items():
        source_type = get_source_type(filename)

        # Apply archetype filtering if specified
        if archetype_types and pokemon_db:
            filtered_data = {
                name: pdata for name, pdata in data.items()
                if matches_archetype(name, archetype_types, pokemon_db)
            }
            print(f"Processing {filename} - {source_type} "
                  f"({len(filtered_data)}/{len(data)} Pokemon match archetype)...")
            data = filtered_data
        else:
            print(f"Processing {filename} ({len(data)} Pokemon) - {source_type}...")

        if not data:
            print(f"  Skipping {filename} (no Pokemon match archetype)")
            continue

        if args.mode == "single":
            # One entry per Pokemon (first role, first variant)
            for pokemon_name in sorted(data.keys()):
                pokemon_data = data[pokemon_name]
                entries = convert_pokemon_to_party_format(
                    pokemon_name,
                    pokemon_data,
                    include_tags=False
                )
                if entries:
                    entry = entries[0]
                    role_name = entry['role']

                    # Build the entry with comments
                    entry_lines = []
                    if not args.split_output:
                        entry_lines.append(f"/* {source_type} */")
                    entry_lines.append(f"/* {role_name} */")
                    entry_lines.append(entry['text'])

                    formatted_entry = '\n'.join(entry_lines)

                    if args.split_output:
                        file_entries[filename].append(formatted_entry)
                    else:
                        all_entries.append(formatted_entry)

        elif args.mode == "all-roles":
            # All roles with all variants
            for pokemon_name in sorted(data.keys()):
                pokemon_data = data[pokemon_name]
                entries = convert_pokemon_to_party_format(
                    pokemon_name,
                    pokemon_data,
                    include_tags=True
                )
                for entry in entries:
                    role_name = entry['role']
                    variant_num = entry.get('variant', 1)

                    # Build the entry with comments
                    entry_lines = []
                    if not args.split_output:
                        entry_lines.append(f"/* {source_type} */")

                    role_comment = f"/* {role_name}"
                    if entry.get('variant', 1) > 1:
                        role_comment += f" (Variant {variant_num})"
                    role_comment += " */"
                    entry_lines.append(role_comment)
                    entry_lines.append(entry['text'])

                    formatted_entry = '\n'.join(entry_lines)

                    if args.split_output:
                        file_entries[filename].append(formatted_entry)
                    else:
                        all_entries.append(formatted_entry)

        elif args.mode == "pool":
            # Generate Pokemon with tags for manual pool creation
            for pokemon_name in sorted(data.keys()):
                pokemon_data = data[pokemon_name]
                entries = convert_pokemon_to_party_format(
                    pokemon_name,
                    pokemon_data,
                    include_tags=True
                )
                # Add all variants
                for entry in entries:
                    role_name = entry['role']
                    variant_num = entry.get('variant', 1)

                    # Build the entry with comments
                    entry_lines = []
                    if not args.split_output:
                        entry_lines.append(f"/* {source_type} */")

                    role_comment = f"/* {role_name}"
                    if entry.get('variant', 1) > 1:
                        role_comment += f" (Variant {variant_num})"
                    role_comment += " */"
                    entry_lines.append(role_comment)
                    entry_lines.append(entry['text'])

                    formatted_entry = '\n'.join(entry_lines)

                    if args.split_output:
                        file_entries[filename].append(formatted_entry)
                    else:
                        all_entries.append(formatted_entry)

        elif args.mode == "trainer-pool":
            # Determine appropriate level range
            if args.level_min is not None and args.level_max is not None:
                # User specified level range
                level_range = (args.level_min, args.level_max)
            else:
                # Auto-detect based on source type
                if 'baby' in filename.lower():
                    level_range = (5, 15)
                elif 'double' in filename.lower() or 'single' in filename.lower():
                    level_range = (75, 85)
                else:
                    level_range = (1, 100)  # Accept all levels by default

            # Generate a complete trainer with pool from this file
            trainer_pool = generate_trainer_pool(
                f"TRAINER_EXAMPLE_{filename.split('.')[0].upper()}",
                "Ace Trainer",
                party_size=args.party_size,
                pool_size=args.pool_size,
                data=data,
                pool_rules="Weather Doubles",
                level_range=level_range,
                double_battle=True
            )

            formatted_entry = f"/* {source_type} */\n{trainer_pool}"

            if args.split_output:
                file_entries[filename].append(formatted_entry)
            else:
                all_entries.append(formatted_entry)

    # Output results
    if args.split_output:
        # Create separate files for each format
        output_files = []
        for filename, entries in file_entries.items():
            if not entries:
                continue

            source_type = get_source_type(filename).lower()
            output_filename = f"converted_movesets_{source_type}.txt"

            with open(output_filename, 'w') as f:
                f.write('\n\n'.join(entries))

            output_files.append(output_filename)
            print(f"  ✓ Wrote {len(entries)} entries to {output_filename}")

        print(f"\n{'=' * 70}")
        print(f"✓ Conversion complete!")
        print(f"✓ Generated {len(output_files)} output files:")
        for output_file in output_files:
            print(f"  - {output_file}")
    else:
        # Write combined file
        with open(args.output, 'w') as f:
            f.write('\n\n'.join(all_entries))

        print(f"\n{'=' * 70}")
        print(f"✓ Conversion complete!")
        print(f"✓ Generated {len(all_entries)} entries")
        print(f"✓ Output saved to: {args.output}")

    print(f"\nYou can now copy and paste from the output file(s) into your trainers.party file!")

    # Show preview
    print(f"\n{'=' * 70}")
    print("Preview (first entry):")
    print('=' * 70)

    if args.split_output:
        # Show preview from first file with entries
        for filename, entries in file_entries.items():
            if entries:
                preview = entries[0][:800]  # First 800 chars
                print(preview)
                if len(entries[0]) > 800:
                    print("\n... (truncated)")
                break
    else:
        if all_entries:
            preview = all_entries[0][:800]  # First 800 chars
            print(preview)
            if len(all_entries[0]) > 800:
                print("\n... (truncated)")

if __name__ == "__main__":
    main()
