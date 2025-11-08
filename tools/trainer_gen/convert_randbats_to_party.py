#!/usr/bin/env python3
"""
Convert Pokemon Showdown Random Battle JSON to trainers.party format
Enhanced with Trainer Party Pool (TPP) support
"""

import json
import urllib.request
import random
import argparse
from typing import Dict, List, Any, Set
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

def load_all_json_files() -> Dict[str, Dict]:
    """Load all available random battle JSON files"""
    all_data = {}

    print("Loading Random Battle data files...")
    print("=" * 70)

    for filename, url in RANDBATS_URLS.items():
        # Check if file exists locally
        if os.path.exists(filename):
            print(f"\nProcessing {filename}:")
            data = fetch_json(url, filename)
            if data:
                all_data[filename] = data
        else:
            print(f"\n{filename} not found, skipping...")

    return all_data

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

    args = parser.parse_args()

    print("Pokemon Showdown Random Battle to trainers.party Converter")
    print("Enhanced with Trainer Party Pool (TPP) Support")
    print("=" * 70)

    # Load all available JSON files
    all_data_files = load_all_json_files()

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
    print("Converting...\n")

    all_entries = []

    # Process each data file
    for filename, data in all_data_files.items():
        source_tag = filename.replace('.json', '').replace('gen9', 'Gen9 ')
        print(f"Processing {filename} ({len(data)} Pokemon)...")

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
                    all_entries.append(entries[0]['text'])

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

                    if len(entries) > 1:
                        header = f"/* {pokemon_name} - {role_name}"
                        if entry.get('variant', 1) > 1:
                            header += f" (Variant {variant_num})"
                        header += f" - {source_tag} */"
                        all_entries.append(f"{header}\n{entry['text']}")
                    else:
                        all_entries.append(entry['text'])

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
                    all_entries.append(entry['text'])

        elif args.mode == "trainer-pool":
            # Generate a complete trainer with pool from this file
            trainer_pool = generate_trainer_pool(
                f"TRAINER_EXAMPLE_{filename.split('.')[0].upper()}",
                "Ace Trainer",
                party_size=args.party_size,
                pool_size=args.pool_size,
                data=data,
                pool_rules="Weather Doubles",
                level_range=(75, 85),
                double_battle=True
            )
            all_entries.append(f"/* From {filename} */\n{trainer_pool}")

    # Output results
    with open(args.output, 'w') as f:
        f.write('\n\n'.join(all_entries))

    print(f"\n{'=' * 70}")
    print(f"✓ Conversion complete!")
    print(f"✓ Generated {len(all_entries)} entries")
    print(f"✓ Output saved to: {args.output}")
    print(f"\nYou can now copy and paste from {args.output} into your trainers.party file!")

    # Show preview
    print(f"\n{'=' * 70}")
    print("Preview (first entry):")
    print('=' * 70)
    if all_entries:
        preview = all_entries[0][:800]  # First 800 chars
        print(preview)
        if len(all_entries[0]) > 800:
            print("\n... (truncated)")

if __name__ == "__main__":
    main()
