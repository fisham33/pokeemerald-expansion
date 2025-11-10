#!/usr/bin/env python3
"""
Query Pokemon move data
Search for any Pokemon and get all its moves
"""

import json
import argparse
from pathlib import Path
from typing import Optional


def normalize_name(name: str) -> str:
    """Normalize name for matching"""
    return name.upper().replace('-', '').replace(' ', '').replace('_', '').replace("'", "")


def find_pokemon(search_name: str, move_data: dict) -> Optional[tuple]:
    """Find a Pokemon by name (fuzzy matching)"""
    normalized_search = normalize_name(search_name)

    # Try exact match first
    for species, data in move_data['pokemon'].items():
        if normalize_name(species) == normalized_search:
            return species, data

        # Also try the display name
        if normalize_name(data['name']) == normalized_search:
            return species, data

    # Try partial match
    matches = []
    for species, data in move_data['pokemon'].items():
        if normalized_search in normalize_name(species):
            matches.append((species, data))
        elif normalized_search in normalize_name(data['name']):
            matches.append((species, data))

    if len(matches) == 1:
        return matches[0]
    elif len(matches) > 1:
        print(f"\nMultiple matches found for '{search_name}':")
        for i, (species, data) in enumerate(matches[:10], 1):
            print(f"  {i}. {data['name']} ({species})")
        if len(matches) > 10:
            print(f"  ... and {len(matches) - 10} more")
        return None
    else:
        return None


def display_pokemon_moves(species: str, data: dict, show_randbats: bool = True):
    """Display all moves for a Pokemon"""
    print("=" * 80)
    print(f"{data['name']} ({species})")
    print("=" * 80)

    # Level-up moves
    if data['level_up_moves']:
        print(f"\n📈 LEVEL-UP MOVES ({len(data['level_up_moves'])} total)")
        print("-" * 80)

        for move_data in data['level_up_moves']:
            print(f"  Lv.{move_data['level']:3d}  {move_data['move']}")
    else:
        print(f"\n📈 LEVEL-UP MOVES: None defined")

    # Teachable moves
    if data['teachable_moves']:
        print(f"\n🎓 TEACHABLE MOVES (TMs/HMs/Tutor) - {len(data['teachable_moves'])} total")
        print("-" * 80)

        # Display in columns
        moves = data['teachable_moves']
        col_width = 25
        cols = 3

        for i in range(0, len(moves), cols):
            row_moves = moves[i:i+cols]
            print("  " + "".join(f"{move:<{col_width}}" for move in row_moves))
    else:
        print(f"\n🎓 TEACHABLE MOVES: None defined")

    # Randbats movesets
    if show_randbats and data['randbats_movesets']:
        print(f"\n🎮 RANDOM BATTLES MOVESETS ({len(data['randbats_movesets'])} roles)")
        print("-" * 80)

        for role_name, role_data in data['randbats_movesets'].items():
            print(f"\n  Role: {role_name}")

            # Show moves
            moves = role_data.get('moves', [])
            if moves:
                print(f"    Moves ({len(moves)}): {', '.join(moves)}")

            # Show abilities
            abilities = role_data.get('abilities', [])
            if abilities:
                print(f"    Abilities: {', '.join(abilities)}")

            # Show items
            items = role_data.get('items', [])
            if items:
                print(f"    Items: {', '.join(items[:5])}")
                if len(items) > 5:
                    print(f"           ... and {len(items) - 5} more")

    elif show_randbats:
        print(f"\n🎮 RANDOM BATTLES MOVESETS: None available")

    print("\n" + "=" * 80)


def main():
    """Main query function"""
    parser = argparse.ArgumentParser(
        description='Query Pokemon move data',
        epilog='Example: python3 query_moves.py Bulbasaur'
    )
    parser.add_argument(
        'pokemon',
        nargs='+',
        help='Pokemon name to search for (e.g., "Bulbasaur" or "Charizard Mega X")'
    )
    parser.add_argument(
        '--no-randbats',
        action='store_true',
        help='Hide Random Battles movesets'
    )
    parser.add_argument(
        '--level-only',
        action='store_true',
        help='Show only level-up moves'
    )
    parser.add_argument(
        '--teachable-only',
        action='store_true',
        help='Show only teachable moves'
    )

    args = parser.parse_args()

    # Join pokemon name parts
    pokemon_name = ' '.join(args.pokemon)

    # Load move data
    script_dir = Path(__file__).parent
    move_data_file = script_dir / 'move_data.json'

    if not move_data_file.exists():
        print(f"Error: Move data not found at {move_data_file}")
        print("\nPlease run 'python3 extract_move_data.py' first to generate the database.")
        return

    with open(move_data_file, 'r', encoding='utf-8') as f:
        move_data = json.load(f)

    # Search for Pokemon
    result = find_pokemon(pokemon_name, move_data)

    if result is None:
        if ',' not in str(result):  # Not a multiple match case
            print(f"\n✗ Pokemon '{pokemon_name}' not found in database.")
            print(f"\nDatabase contains {move_data['metadata']['total_pokemon']} Pokemon.")
        return

    species, data = result

    # Filter data based on args
    if args.level_only:
        data = {
            **data,
            'teachable_moves': [],
            'randbats_movesets': {}
        }
    elif args.teachable_only:
        data = {
            **data,
            'level_up_moves': [],
            'randbats_movesets': {}
        }

    # Display moves
    display_pokemon_moves(species, data, show_randbats=not args.no_randbats)

    # Show statistics
    total_moves = set()
    if data['level_up_moves']:
        total_moves.update(move['move'] for move in data['level_up_moves'])
    if data['teachable_moves']:
        total_moves.update(data['teachable_moves'])

    print(f"💡 Total unique moves available: {len(total_moves)}")


if __name__ == "__main__":
    main()
