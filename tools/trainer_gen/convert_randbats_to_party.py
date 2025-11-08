#!/usr/bin/env python3
"""
Convert Pokemon Showdown Random Doubles Battle JSON to trainers.party format
Enhanced with Trainer Party Pool (TPP) support
"""

import json
import urllib.request
import random
import argparse
from typing import Dict, List, Any, Set
from pathlib import Path

# URL to fetch the JSON from
RANDBATS_URL = "https://pkmn.github.io/randbats/data/gen9randomdoublesbattle.json"

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

def fetch_json(url: str, local_file: str = "gen9randomdoublesbattle.json") -> Dict:
    """Fetch JSON from URL or use local file as fallback"""
    try:
        print(f"Fetching data from {url}...")
        with urllib.request.urlopen(url, timeout=10) as response:
            data = response.read()
        print("Successfully fetched data!")
        return json.loads(data)
    except Exception as e:
        print(f"Error fetching from URL: {e}")
        print(f"Trying to read from local file '{local_file}'...")
        try:
            with open(local_file, 'r') as f:
                return json.load(f)
        except Exception as e2:
            print(f"Error reading local file: {e2}")
            return None

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

    level = pokemon_data.get('level', 100)
    roles = pokemon_data.get('roles', {})
    if not roles:
        return results

    if role_name and role_name in roles:
        roles_to_process = {role_name: roles[role_name]}
    else:
        roles_to_process = roles

    for role, role_data in roles_to_process.items():
        lines = []
        tags = []

        # Pokemon name @ Item
        items = role_data.get('items', pokemon_data.get('items', []))
        item = items[0] if items else None
        if item:
            lines.append(f"{pokemon_name} @ {item}")
        else:
            lines.append(pokemon_name)

        # Level
        lines.append(f"Level: {level}")

        # Ability
        abilities = role_data.get('abilities', pokemon_data.get('abilities', []))
        if abilities:
            ability = abilities[0]
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
            tera_type = tera_types[0]
            lines.append(f"Tera Type: {tera_type}")

        # Determine tags for TPP
        if include_tags:
            tags = determine_tags(role, role_data, pokemon_data)
            if tags:
                lines.append(f"Tags: {' / '.join(tags)}")

        # Moves
        moves = role_data.get('moves', [])
        if moves:
            selected_moves = random.sample(moves, min(max_moves, len(moves)))
            for move in selected_moves:
                lines.append(f"- {move}")

        results.append({
            'text': '\n'.join(lines),
            'role': role,
            'tags': tags
        })

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
    tag_counts = {
        'Lead': 0,
        'Ace': 0,
        'Weather Setter': 0,
        'Weather Abuser': 0,
        'Support': 0
    }

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
            # Pick the first role for simplicity
            entry = entries[0]
            pokemon_entries.append(entry['text'])

    # Add all Pokemon to the pool
    return '\n\n'.join(lines) + '\n\n'.join(pokemon_entries[:pool_size])

def main():
    """Main conversion function"""
    parser = argparse.ArgumentParser(
        description='Convert Random Doubles Battle JSON to trainers.party format'
    )
    parser.add_argument(
        '--input', '-i',
        default='gen9randomdoublesbattle.json',
        help='Input JSON file (default: gen9randomdoublesbattle.json)'
    )
    parser.add_argument(
        '--output', '-o',
        default='converted_movesets.txt',
        help='Output file (default: converted_movesets.txt)'
    )
    parser.add_argument(
        '--mode',
        choices=['single', 'all-roles', 'pool', 'trainer-pool'],
        default='single',
        help='Conversion mode'
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

    print("Pokemon Showdown Random Doubles Battle to trainers.party Converter")
    print("Enhanced with Trainer Party Pool (TPP) Support")
    print("=" * 70)

    # Fetch the JSON data
    data = fetch_json(RANDBATS_URL, args.input)
    if not data:
        print("Failed to load data. Exiting.")
        return

    print(f"\nLoaded data for {len(data)} Pokemon!")
    print(f"\nMode: {args.mode}")
    print(f"Conversion in progress...\n")

    all_entries = []

    if args.mode == "single":
        # One entry per Pokemon (first role)
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
        # All roles with tags
        for pokemon_name in sorted(data.keys()):
            pokemon_data = data[pokemon_name]
            entries = convert_pokemon_to_party_format(
                pokemon_name,
                pokemon_data,
                include_tags=True
            )
            for entry in entries:
                role_name = entry['role']
                if len(entries) > 1:
                    all_entries.append(f"/* {pokemon_name} - {role_name} */\n{entry['text']}")
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
            if entries:
                all_entries.append(entries[0]['text'])

    elif args.mode == "trainer-pool":
        # Generate a complete trainer with pool
        trainer_pool = generate_trainer_pool(
            "TRAINER_EXAMPLE_DOUBLES",
            "Ace Trainer",
            party_size=args.party_size,
            pool_size=args.pool_size,
            data=data,
            pool_rules="Weather Doubles",
            level_range=(75, 85),
            double_battle=True
        )
        all_entries.append(trainer_pool)

    # Output results
    with open(args.output, 'w') as f:
        f.write('\n\n'.join(all_entries))

    print(f"\n{'=' * 70}")
    print(f"Conversion complete! Generated {len(all_entries)} entries.")
    print(f"Output saved to: {args.output}")
    print(f"\nYou can now copy and paste from {args.output} into your trainers.party file!")

    # Show preview
    print(f"\n{'=' * 70}")
    print("Preview (first entry):")
    print('=' * 70)
    if all_entries:
        preview = all_entries[0][:1000]  # First 1000 chars
        print(preview)
        if len(all_entries[0]) > 1000:
            print("\n... (truncated)")

if __name__ == "__main__":
    main()
