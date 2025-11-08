#!/usr/bin/env python3
"""
Convert Pokemon Showdown Random Doubles Battle JSON to trainers.party format
"""

import json
import urllib.request
import random
from typing import Dict, List, Any

# URL to fetch the JSON from
RANDBATS_URL = "https://pkmn.github.io/randbats/data/gen9randomdoublesbattle.json"

def fetch_json(url: str) -> Dict:
    """Fetch JSON from URL or use local file as fallback"""
    try:
        print(f"Fetching data from {url}...")
        with urllib.request.urlopen(url) as response:
            data = response.read()
        print("Successfully fetched data!")
        return json.loads(data)
    except Exception as e:
        print(f"Error fetching from URL: {e}")
        print("Trying to read from local file 'gen9randomdoublesbattle.json'...")
        try:
            with open('gen9randomdoublesbattle.json', 'r') as f:
                return json.load(f)
        except Exception as e2:
            print(f"Error reading local file: {e2}")
            return None

def format_evs_ivs(values: Dict[str, int], all_value: int) -> str:
    """Format EVs or IVs to trainers.party format"""
    # Map short names to full stat names
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

def convert_pokemon_to_party_format(pokemon_name: str, pokemon_data: Dict, role_name: str = None) -> List[str]:
    """Convert a single Pokemon's data to trainers.party format"""
    results = []

    # Get base level
    level = pokemon_data.get('level', 100)

    # Get roles - if role_name specified, use only that one
    roles = pokemon_data.get('roles', {})
    if not roles:
        return results

    if role_name and role_name in roles:
        roles_to_process = {role_name: roles[role_name]}
    else:
        roles_to_process = roles

    # Process each role
    for role, role_data in roles_to_process.items():
        lines = []

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

        # EVs (role-specific or Pokemon-wide)
        evs = role_data.get('evs', pokemon_data.get('evs', {}))
        if evs:
            ev_string = format_evs_ivs(evs, 0)  # Default EV is 0
            lines.append(f"EVs: {ev_string}")

        # IVs (role-specific or Pokemon-wide)
        ivs = role_data.get('ivs', pokemon_data.get('ivs', {}))
        if ivs:
            iv_string = format_evs_ivs(ivs, 31)  # Default IV is 31
            lines.append(f"IVs: {iv_string}")

        # Tera Type
        tera_types = role_data.get('teraTypes', [])
        if tera_types:
            tera_type = tera_types[0]
            lines.append(f"Tera Type: {tera_type}")

        # Moves (pick up to 4 randomly from the available moves)
        moves = role_data.get('moves', [])
        if moves:
            # Shuffle and pick up to 4
            selected_moves = random.sample(moves, min(4, len(moves)))
            for move in selected_moves:
                lines.append(f"- {move}")

        results.append('\n'.join(lines))

    return results

def main():
    """Main conversion function"""
    print("Pokemon Showdown Random Doubles Battle to trainers.party Converter")
    print("=" * 70)

    # Fetch the JSON data
    data = fetch_json(RANDBATS_URL)
    if not data:
        print("Failed to load data. Exiting.")
        return

    print(f"\nLoaded data for {len(data)} Pokemon!")
    print("\nConverting to trainers.party format...\n")

    # Ask user if they want all roles or just one per Pokemon
    print("Options:")
    print("1. Generate one entry per Pokemon (first role only)")
    print("2. Generate entries for all roles (multiple entries per Pokemon)")
    print("3. Generate for specific Pokemon only")

    choice = input("\nEnter your choice (1-3): ").strip()

    all_entries = []

    if choice == "1":
        # One entry per Pokemon (first role)
        for pokemon_name in sorted(data.keys()):
            pokemon_data = data[pokemon_name]
            entries = convert_pokemon_to_party_format(pokemon_name, pokemon_data)
            if entries:
                all_entries.append(entries[0])  # Just take first role

    elif choice == "2":
        # All roles
        for pokemon_name in sorted(data.keys()):
            pokemon_data = data[pokemon_name]
            entries = convert_pokemon_to_party_format(pokemon_name, pokemon_data)
            for i, entry in enumerate(entries):
                roles = list(pokemon_data.get('roles', {}).keys())
                if len(entries) > 1:
                    # Add comment to distinguish roles
                    role_name = roles[i] if i < len(roles) else "Unknown"
                    all_entries.append(f"/* {pokemon_name} - {role_name} */\n{entry}")
                else:
                    all_entries.append(entry)

    elif choice == "3":
        # Specific Pokemon
        pokemon_name = input("Enter Pokemon name (e.g., 'Abomasnow'): ").strip()
        if pokemon_name in data:
            pokemon_data = data[pokemon_name]
            roles = list(pokemon_data.get('roles', {}).keys())

            if len(roles) > 1:
                print(f"\nAvailable roles for {pokemon_name}:")
                for i, role in enumerate(roles, 1):
                    print(f"{i}. {role}")
                role_choice = input("Enter role number (or 'all' for all roles): ").strip()

                if role_choice.lower() == 'all':
                    entries = convert_pokemon_to_party_format(pokemon_name, pokemon_data)
                    all_entries.extend(entries)
                else:
                    try:
                        role_idx = int(role_choice) - 1
                        if 0 <= role_idx < len(roles):
                            entries = convert_pokemon_to_party_format(pokemon_name, pokemon_data, roles[role_idx])
                            all_entries.extend(entries)
                    except ValueError:
                        print("Invalid choice")
            else:
                entries = convert_pokemon_to_party_format(pokemon_name, pokemon_data)
                all_entries.extend(entries)
        else:
            print(f"Pokemon '{pokemon_name}' not found in data")

    else:
        print("Invalid choice")
        return

    # Output results
    output_file = "converted_movesets.txt"
    with open(output_file, 'w') as f:
        f.write('\n\n'.join(all_entries))

    print(f"\n{'=' * 70}")
    print(f"Conversion complete! Generated {len(all_entries)} entries.")
    print(f"Output saved to: {output_file}")
    print(f"\nYou can now copy and paste from {output_file} into your trainers.party file!")

    # Show first few entries as preview
    print(f"\n{'=' * 70}")
    print("Preview (first 3 entries):")
    print('=' * 70)
    for entry in all_entries[:3]:
        print(entry)
        print()

if __name__ == "__main__":
    main()
