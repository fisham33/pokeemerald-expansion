#!/usr/bin/env python3
"""
Extract Pokemon move data from pokeemerald-expansion codebase
Generates a comprehensive database of level-up moves and teachable moves
"""

import re
import json
from pathlib import Path
from typing import Dict, List, Tuple, Optional


def clean_move_name(move_constant: str) -> str:
    """Convert MOVE_SOLAR_BEAM to Solar Beam"""
    if move_constant.startswith('MOVE_'):
        move_constant = move_constant[5:]  # Remove 'MOVE_' prefix

    # Special cases
    special_cases = {
        'WILLOWISP': 'Will-O-Wisp',
        'XSCISSOR': 'X-Scissor',
        'UTURN': 'U-turn',
        'VCREATE': 'V-create',
    }

    if move_constant in special_cases:
        return special_cases[move_constant]

    # Convert SOLAR_BEAM to Solar Beam
    words = move_constant.split('_')
    return ' '.join(word.capitalize() for word in words)


def parse_level_up_learnsets(learnset_dir: Path) -> Dict[str, List[Tuple[int, str]]]:
    """
    Parse level-up learnsets from gen_X.h files

    Returns:
        Dict mapping species name to list of (level, move_name) tuples
    """
    learnsets = {}

    # Find all gen_X.h files
    gen_files = sorted(learnset_dir.glob('gen_*.h'))

    for gen_file in gen_files:
        with open(gen_file, 'r', encoding='utf-8') as f:
            content = f.read()

        # Pattern: static const struct LevelUpMove sSpeciesLevelUpLearnset[] = {
        learnset_pattern = r'static\s+const\s+struct\s+LevelUpMove\s+s(\w+)LevelUpLearnset\[\]\s*=\s*\{([^}]+)\}'

        for match in re.finditer(learnset_pattern, content, re.DOTALL):
            species_name = match.group(1).upper()
            learnset_content = match.group(2)

            # Skip special entries
            if species_name in ['NONE']:
                continue

            moves = []

            # Extract LEVEL_UP_MOVE entries
            move_pattern = r'LEVEL_UP_MOVE\s*\(\s*(\d+)\s*,\s*MOVE_(\w+)\s*\)'

            for move_match in re.finditer(move_pattern, learnset_content):
                level = int(move_match.group(1))
                move_constant = move_match.group(2)
                move_name = clean_move_name(f'MOVE_{move_constant}')

                moves.append((level, move_name))

            if moves:
                learnsets[species_name] = moves

    return learnsets


def parse_teachable_learnsets(teachable_file: Path) -> Dict[str, List[str]]:
    """
    Parse teachable learnsets from teachable_learnsets.h

    Returns:
        Dict mapping species name to list of move names
    """
    learnsets = {}

    with open(teachable_file, 'r', encoding='utf-8') as f:
        content = f.read()

    # Pattern: static const u16 sSpeciesTeachableLearnset[] = {
    learnset_pattern = r'static\s+const\s+u16\s+s(\w+)TeachableLearnset\[\]\s*=\s*\{([^}]+)\}'

    for match in re.finditer(learnset_pattern, content, re.DOTALL):
        species_name = match.group(1).upper()
        learnset_content = match.group(2)

        # Skip special entries
        if species_name in ['NONE']:
            continue

        moves = []

        # Extract MOVE_ constants
        move_pattern = r'MOVE_(\w+)'

        for move_match in re.finditer(move_pattern, learnset_content):
            move_constant = move_match.group(1)

            # Skip special markers
            if move_constant in ['UNAVAILABLE']:
                continue

            move_name = clean_move_name(f'MOVE_{move_constant}')
            moves.append(move_name)

        if moves:
            learnsets[species_name] = moves

    return learnsets


def parse_egg_moves(egg_moves_file: Path) -> Dict[str, List[str]]:
    """
    Parse egg moves from egg_moves.h

    Returns:
        Dict mapping species name to list of move names
    """
    learnsets = {}

    with open(egg_moves_file, 'r', encoding='utf-8') as f:
        content = f.read()

    # Pattern: static const u16 sSpeciesEggMoveLearnset[] = {
    learnset_pattern = r'static\s+const\s+u16\s+s(\w+)EggMoveLearnset\[\]\s*=\s*\{([^}]+)\}'

    for match in re.finditer(learnset_pattern, content, re.DOTALL):
        species_name = match.group(1).upper()
        learnset_content = match.group(2)

        # Skip special entries
        if species_name in ['NONE']:
            continue

        moves = []

        # Extract MOVE_ constants
        move_pattern = r'MOVE_(\w+)'

        for move_match in re.finditer(move_pattern, learnset_content):
            move_constant = move_match.group(1)

            # Skip special markers
            if move_constant in ['UNAVAILABLE']:
                continue

            move_name = clean_move_name(f'MOVE_{move_constant}')
            moves.append(move_name)

        if moves:
            learnsets[species_name] = moves

    return learnsets


def load_randbats_movesets(randbats_files: List[Path]) -> Dict[str, Dict]:
    """
    Load movesets from randbats JSON files

    Returns:
        Dict mapping pokemon name to their randbats data
    """
    all_movesets = {}

    for randbats_file in randbats_files:
        if not randbats_file.exists():
            continue

        try:
            with open(randbats_file, 'r', encoding='utf-8') as f:
                data = json.load(f)

            for pokemon_name, pokemon_data in data.items():
                # Normalize name for matching
                normalized_name = pokemon_name.upper().replace('-', '').replace(' ', '').replace("'", "")

                if normalized_name not in all_movesets:
                    all_movesets[normalized_name] = {
                        'name': pokemon_name,
                        'roles': {}
                    }

                # Merge roles from all files
                all_movesets[normalized_name]['roles'].update(pokemon_data.get('roles', {}))
        except Exception as e:
            print(f"  Warning: Could not load {randbats_file.name}: {e}")

    return all_movesets


def normalize_species_name(name: str) -> str:
    """Normalize species name for matching"""
    return name.upper().replace('-', '').replace(' ', '').replace('_', '').replace("'", "")


def parse_families_from_source(species_info_dir: Path) -> Dict[str, List[str]]:
    """
    Parse family information directly from gen_X_families.h files

    Returns:
        Dict mapping family name to list of species in that family
    """
    family_to_species = {}

    # Find all gen_X_families.h files
    gen_files = sorted(species_info_dir.glob('gen_*_families.h'))

    for gen_file in gen_files:
        with open(gen_file, 'r', encoding='utf-8') as f:
            content = f.read()

        # Pattern: #if P_FAMILY_XXX ... #endif //P_FAMILY_XXX
        family_pattern = r'#if\s+(P_FAMILY_\w+)\s*\n(.*?)#endif\s*//\1'

        for match in re.finditer(family_pattern, content, re.DOTALL):
            family_name = match.group(1)
            family_content = match.group(2)

            # Extract all [SPECIES_XXX] entries within this family
            species_pattern = r'\[SPECIES_(\w+)\]\s*='
            species_list = re.findall(species_pattern, family_content)

            if species_list and family_name not in family_to_species:
                family_to_species[family_name] = [s.upper() for s in species_list]

    return family_to_species


def propagate_egg_moves_to_families(egg_moves_learnsets: Dict[str, List[str]], species_info_dir: Path) -> Dict[str, List[str]]:
    """
    Propagate egg moves to all members of the same family

    Args:
        egg_moves_learnsets: Dict mapping species to egg moves
        species_info_dir: Path to species_info directory with family information

    Returns:
        Updated egg moves dict with moves propagated to all family members
    """
    if not species_info_dir.exists():
        print(f"  Warning: species_info directory not found at {species_info_dir}, skipping family propagation")
        return egg_moves_learnsets

    # Parse family information from source files
    family_to_species = parse_families_from_source(species_info_dir)

    # Build a mapping of species -> family for quick lookup
    species_to_family = {}
    for family, species_list in family_to_species.items():
        for species in species_list:
            species_to_family[species] = family

    # Collect all egg moves for each family
    # Need to handle species name variants (e.g., BASCULIN vs BASCULIN_RED_STRIPED)
    family_egg_moves = {}
    for species, moves in egg_moves_learnsets.items():
        family = species_to_family.get(species)

        # If exact match not found, try to find species that start with this name
        if not family:
            # Remove underscores for matching (BASCULINWHITESTRIPED -> BASCULIN_WHITE_STRIPED)
            species_normalized = species.replace('_', '')
            for actual_species, actual_family in species_to_family.items():
                actual_normalized = actual_species.replace('_', '')
                # Check if this is a variant (e.g., BASCULIN matches BASCULIN_RED_STRIPED)
                if actual_normalized.startswith(species_normalized) or species_normalized.startswith(actual_normalized):
                    family = actual_family
                    break

        if family:
            if family not in family_egg_moves:
                family_egg_moves[family] = set()
            family_egg_moves[family].update(moves)

    # Propagate egg moves to all family members
    updated_learnsets = dict(egg_moves_learnsets)  # Start with original
    propagated_count = 0

    for family, all_moves in family_egg_moves.items():
        move_list = sorted(list(all_moves))  # Convert to sorted list
        for species in family_to_species[family]:
            if species not in updated_learnsets:
                updated_learnsets[species] = move_list
                propagated_count += 1
            elif set(updated_learnsets[species]) != all_moves:
                # Update with all family moves
                updated_learnsets[species] = move_list

    print(f"  ✓ Propagated egg moves to {propagated_count} additional Pokemon across families")

    return updated_learnsets


def main():
    """Main extraction function"""
    print("Pokemon Move Data Extraction Tool")
    print("=" * 70)

    # Get the root directory
    script_dir = Path(__file__).parent
    root_dir = script_dir.parent.parent

    # Paths
    learnset_dir = root_dir / 'src' / 'data' / 'pokemon' / 'level_up_learnsets'
    teachable_file = root_dir / 'src' / 'data' / 'pokemon' / 'teachable_learnsets.h'
    egg_moves_file = root_dir / 'src' / 'data' / 'pokemon' / 'egg_moves.h'
    species_info_dir = root_dir / 'src' / 'data' / 'pokemon' / 'species_info'

    if not learnset_dir.exists():
        print(f"Error: Level-up learnsets directory not found at {learnset_dir}")
        return

    if not teachable_file.exists():
        print(f"Error: Teachable learnsets file not found at {teachable_file}")
        return

    if not egg_moves_file.exists():
        print(f"Warning: Egg moves file not found at {egg_moves_file}")
        egg_moves_learnsets = {}
    else:
        print(f"\nExtracting egg moves from: {egg_moves_file}")
        egg_moves_learnsets = parse_egg_moves(egg_moves_file)
        print(f"  ✓ Found {len(egg_moves_learnsets)} Pokemon with egg moves")

        # Propagate egg moves to entire families
        print(f"\nPropagating egg moves to evolutionary families...")
        egg_moves_learnsets = propagate_egg_moves_to_families(egg_moves_learnsets, species_info_dir)

    print(f"\nExtracting level-up learnsets from: {learnset_dir}")
    level_up_learnsets = parse_level_up_learnsets(learnset_dir)
    print(f"  ✓ Found {len(level_up_learnsets)} Pokemon with level-up moves")

    print(f"\nExtracting teachable learnsets from: {teachable_file}")
    teachable_learnsets = parse_teachable_learnsets(teachable_file)
    print(f"  ✓ Found {len(teachable_learnsets)} Pokemon with teachable moves")

    # Load randbats data if available
    print(f"\nLoading randbats movesets...")
    randbats_files = [
        script_dir / 'gen9randomdoublesbattle.json',
        script_dir / 'gen9randombattle.json',
        script_dir / 'gen9babyrandombattle.json',
    ]
    randbats_movesets = load_randbats_movesets(randbats_files)
    print(f"  ✓ Loaded {len(randbats_movesets)} Pokemon from randbats data")

    # Combine all data
    print(f"\nCombining move data...")
    combined_data = {}

    # Start with all Pokemon that have level-up, teachable, or egg moves
    all_species = set(level_up_learnsets.keys()) | set(teachable_learnsets.keys()) | set(egg_moves_learnsets.keys())

    for species in all_species:
        normalized = normalize_species_name(species)

        pokemon_entry = {
            'species': species,
            'name': species.replace('_', ' ').title(),
            'level_up_moves': [],
            'teachable_moves': [],
            'egg_moves': [],
            'randbats_movesets': {}
        }

        # Add level-up moves
        if species in level_up_learnsets:
            pokemon_entry['level_up_moves'] = [
                {'level': level, 'move': move}
                for level, move in level_up_learnsets[species]
            ]

        # Add teachable moves
        if species in teachable_learnsets:
            pokemon_entry['teachable_moves'] = teachable_learnsets[species]

        # Add egg moves
        if species in egg_moves_learnsets:
            pokemon_entry['egg_moves'] = egg_moves_learnsets[species]

        # Try to match with randbats data
        if normalized in randbats_movesets:
            pokemon_entry['randbats_movesets'] = randbats_movesets[normalized]['roles']
            pokemon_entry['name'] = randbats_movesets[normalized]['name']

        combined_data[species] = pokemon_entry

    # Sort by species name
    combined_data = dict(sorted(combined_data.items()))

    # Copy egg moves from gender variants to generic forms
    # (e.g., BASCULEGION should get egg moves from BASCULEGION_M/BASCULEGION_F)
    generic_forms_updated = 0
    for species in list(combined_data.keys()):
        for suffix in ['_M', '_F', '_MALE', '_FEMALE']:
            if species.endswith(suffix):
                # This is a gender variant, check if generic form exists
                generic_species = species[:-len(suffix)]
                if generic_species in combined_data:
                    # If generic has no egg moves but variant does, copy them
                    if not combined_data[generic_species]['egg_moves'] and combined_data[species]['egg_moves']:
                        combined_data[generic_species]['egg_moves'] = combined_data[species]['egg_moves'].copy()
                        generic_forms_updated += 1

    if generic_forms_updated > 0:
        print(f"  ✓ Copied egg moves to {generic_forms_updated} generic forms from gender variants")

    # Create output
    output = {
        'metadata': {
            'total_pokemon': len(combined_data),
            'with_level_up_moves': len(level_up_learnsets),
            'with_teachable_moves': len(teachable_learnsets),
            'with_egg_moves': len(egg_moves_learnsets),
            'with_randbats_movesets': len(randbats_movesets),
            'source': 'pokeemerald-expansion'
        },
        'pokemon': combined_data
    }

    # Write to JSON file
    output_file = script_dir / 'move_data.json'
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2)

    print(f"\n{'=' * 70}")
    print(f"✓ Extraction complete!")
    print(f"✓ Total Pokemon: {len(combined_data)}")
    print(f"✓ Database saved to: {output_file}")

    # Show some statistics
    print(f"\n{'=' * 70}")
    print("Statistics:")
    print(f"  Pokemon with level-up moves: {len(level_up_learnsets)}")
    print(f"  Pokemon with teachable moves: {len(teachable_learnsets)}")
    print(f"  Pokemon with egg moves: {len(egg_moves_learnsets)}")
    print(f"  Pokemon with randbats movesets: {len(randbats_movesets)}")

    # Count total moves
    total_level_up = sum(len(moves) for moves in level_up_learnsets.values())
    total_teachable = sum(len(moves) for moves in teachable_learnsets.values())
    total_egg = sum(len(moves) for moves in egg_moves_learnsets.values())

    print(f"\n  Total level-up move entries: {total_level_up}")
    print(f"  Total teachable move entries: {total_teachable}")
    print(f"  Total egg move entries: {total_egg}")

    # Show preview
    print(f"\n{'=' * 70}")
    print("Preview (first 2 Pokemon):")
    print('=' * 70)

    for i, (species, data) in enumerate(list(combined_data.items())[:2]):
        print(f"\n{data['name']} ({species})")

        if data['level_up_moves']:
            print(f"  Level-up moves ({len(data['level_up_moves'])}):")
            for move_data in data['level_up_moves'][:5]:
                print(f"    Lv.{move_data['level']:2d}: {move_data['move']}")
            if len(data['level_up_moves']) > 5:
                print(f"    ... and {len(data['level_up_moves']) - 5} more")

        if data['teachable_moves']:
            print(f"  Teachable moves ({len(data['teachable_moves'])}):")
            print(f"    {', '.join(data['teachable_moves'][:8])}")
            if len(data['teachable_moves']) > 8:
                print(f"    ... and {len(data['teachable_moves']) - 8} more")

        if data['egg_moves']:
            print(f"  Egg moves ({len(data['egg_moves'])}):")
            print(f"    {', '.join(data['egg_moves'][:8])}")
            if len(data['egg_moves']) > 8:
                print(f"    ... and {len(data['egg_moves']) - 8} more")

        if data['randbats_movesets']:
            print(f"  Randbats roles: {', '.join(data['randbats_movesets'].keys())}")


if __name__ == "__main__":
    main()
