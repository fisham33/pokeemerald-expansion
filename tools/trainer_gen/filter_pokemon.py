#!/usr/bin/env python3
"""
Filter Pokemon by base stats
Search for Pokemon within specific stat ranges
"""

import json
import argparse
from pathlib import Path
from typing import List, Dict, Optional


def filter_pokemon(
    pokemon_data: Dict,
    min_bst: Optional[int] = None,
    max_bst: Optional[int] = None,
    min_hp: Optional[int] = None,
    max_hp: Optional[int] = None,
    min_atk: Optional[int] = None,
    max_atk: Optional[int] = None,
    min_def: Optional[int] = None,
    max_def: Optional[int] = None,
    min_spa: Optional[int] = None,
    max_spa: Optional[int] = None,
    min_spd: Optional[int] = None,
    max_spd: Optional[int] = None,
    min_spe: Optional[int] = None,
    max_spe: Optional[int] = None,
    generation: Optional[int] = None,
    types: Optional[List[str]] = None,
    ability: Optional[str] = None,
) -> List[Dict]:
    """
    Filter Pokemon based on stat criteria

    Returns:
        List of Pokemon that match the criteria
    """
    results = []

    for pokemon in pokemon_data['pokemon']:
        stats = pokemon.get('baseStats', {})
        bst = pokemon.get('bst', 0)
        gen = pokemon.get('generation', 0)

        # Check generation filter
        if generation is not None and gen != generation:
            continue

        # Check type filter
        if types is not None and len(types) > 0:
            pokemon_types = [t.lower() for t in pokemon.get('types', [])]
            # Check if Pokemon has ANY of the specified types
            has_type = any(t.lower() in pokemon_types for t in types)
            if not has_type:
                continue

        # Check ability filter
        if ability is not None and ability.strip():
            ability_lower = ability.lower()
            pokemon_abilities = [a.lower() for a in pokemon.get('abilities', [])]
            hidden_ability = pokemon.get('hiddenAbility', '')
            if hidden_ability:
                pokemon_abilities.append(hidden_ability.lower())
            # Check if Pokemon has the specified ability
            has_ability = any(ability_lower in a for a in pokemon_abilities)
            if not has_ability:
                continue

        # Check BST filter
        if min_bst is not None and bst < min_bst:
            continue
        if max_bst is not None and bst > max_bst:
            continue

        # Check individual stat filters
        if min_hp is not None and stats.get('hp', 0) < min_hp:
            continue
        if max_hp is not None and stats.get('hp', 0) > max_hp:
            continue

        if min_atk is not None and stats.get('atk', 0) < min_atk:
            continue
        if max_atk is not None and stats.get('atk', 0) > max_atk:
            continue

        if min_def is not None and stats.get('def', 0) < min_def:
            continue
        if max_def is not None and stats.get('def', 0) > max_def:
            continue

        if min_spa is not None and stats.get('spa', 0) < min_spa:
            continue
        if max_spa is not None and stats.get('spa', 0) > max_spa:
            continue

        if min_spd is not None and stats.get('spd', 0) < min_spd:
            continue
        if max_spd is not None and stats.get('spd', 0) > max_spd:
            continue

        if min_spe is not None and stats.get('spe', 0) < min_spe:
            continue
        if max_spe is not None and stats.get('spe', 0) > max_spe:
            continue

        results.append(pokemon)

    return results


def display_results(results: List[Dict], show_stats: bool = True):
    """Display filtered Pokemon results"""
    if not results:
        print("\n✗ No Pokemon found matching the criteria.")
        return

    print(f"\n{'=' * 80}")
    print(f"Found {len(results)} Pokemon matching criteria")
    print(f"{'=' * 80}\n")

    if show_stats:
        # Display with full stats
        for i, pokemon in enumerate(results, 1):
            stats = pokemon.get('baseStats', {})
            bst = pokemon.get('bst', 0)
            gen = pokemon.get('generation', 0)
            types = pokemon.get('types', [])
            types_str = '/'.join(types) if types else 'Unknown'

            print(f"{i:3d}. {pokemon['name']:<20} ({pokemon['species']})")
            print(f"     Gen: {gen}  Types: {types_str:<20} BST: {bst}")
            print(f"     HP: {stats.get('hp', 0):3d}  Atk: {stats.get('atk', 0):3d}  Def: {stats.get('def', 0):3d}  "
                  f"SpA: {stats.get('spa', 0):3d}  SpD: {stats.get('spd', 0):3d}  Spe: {stats.get('spe', 0):3d}")
            print()
    else:
        # Compact list
        for i, pokemon in enumerate(results, 1):
            bst = pokemon.get('bst', 0)
            gen = pokemon.get('generation', 0)
            print(f"{i:3d}. {pokemon['name']:<25} Gen: {gen}  BST: {bst:3d}")


def main():
    parser = argparse.ArgumentParser(
        description='Filter Pokemon by base stat ranges',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Filter Pokemon with BST between 300 and 400
  python3 filter_pokemon.py --min-bst 300 --max-bst 400

  # Filter Pokemon with Attack between 90 and 110
  python3 filter_pokemon.py --min-atk 90 --max-atk 110

  # Filter Generation 9 Pokemon only
  python3 filter_pokemon.py --gen 9

  # Filter Generation 8 Pokemon with high speed
  python3 filter_pokemon.py --gen 8 --min-spe 100

  # Filter fast Pokemon (Speed >= 100) with high attack (>= 100)
  python3 filter_pokemon.py --min-spe 100 --min-atk 100

  # Filter bulky Pokemon (HP >= 90, Defense >= 90)
  python3 filter_pokemon.py --min-hp 90 --min-def 90

  # Compact list output
  python3 filter_pokemon.py --min-bst 500 --compact

  # Count Generation 1 Pokemon
  python3 filter_pokemon.py --gen 1 --count
        """
    )

    # Generation filter
    parser.add_argument('--gen', '--generation', type=int, dest='generation',
                        help='Filter by generation (1-9)', choices=range(1, 10), metavar='GEN')

    # Type filter
    parser.add_argument('--type', '--types', action='append', dest='types',
                        help='Filter by type (can specify multiple times, e.g., --type Fire --type Dragon)')

    # Ability filter
    parser.add_argument('--ability', type=str,
                        help='Filter by ability (partial match, e.g., "Intimidate" or "Levitate")')

    # BST filters
    parser.add_argument('--min-bst', type=int, help='Minimum Base Stat Total')
    parser.add_argument('--max-bst', type=int, help='Maximum Base Stat Total')

    # Individual stat filters
    parser.add_argument('--min-hp', type=int, help='Minimum HP')
    parser.add_argument('--max-hp', type=int, help='Maximum HP')

    parser.add_argument('--min-atk', type=int, help='Minimum Attack')
    parser.add_argument('--max-atk', type=int, help='Maximum Attack')

    parser.add_argument('--min-def', type=int, help='Minimum Defense')
    parser.add_argument('--max-def', type=int, help='Maximum Defense')

    parser.add_argument('--min-spa', type=int, help='Minimum Special Attack')
    parser.add_argument('--max-spa', type=int, help='Maximum Special Attack')

    parser.add_argument('--min-spd', type=int, help='Minimum Special Defense')
    parser.add_argument('--max-spd', type=int, help='Maximum Special Defense')

    parser.add_argument('--min-spe', type=int, help='Minimum Speed')
    parser.add_argument('--max-spe', type=int, help='Maximum Speed')

    # Output options
    parser.add_argument('--compact', action='store_true', help='Show compact list without detailed stats')
    parser.add_argument('--count', action='store_true', help='Show only the count of matching Pokemon')

    args = parser.parse_args()

    # Check if at least one filter is provided
    filters = [
        args.generation,
        args.types,
        args.ability,
        args.min_bst, args.max_bst,
        args.min_hp, args.max_hp,
        args.min_atk, args.max_atk,
        args.min_def, args.max_def,
        args.min_spa, args.max_spa,
        args.min_spd, args.max_spd,
        args.min_spe, args.max_spe,
    ]

    if not any(f is not None for f in filters):
        parser.print_help()
        print("\n✗ Error: At least one filter must be specified.")
        return

    # Load pokemon data
    script_dir = Path(__file__).parent
    pokemon_data_file = script_dir / 'pokemon_data.json'

    if not pokemon_data_file.exists():
        print(f"Error: Pokemon data not found at {pokemon_data_file}")
        print("\nPlease run 'python3 extract_pokemon_data.py' first to generate the database.")
        return

    with open(pokemon_data_file, 'r', encoding='utf-8') as f:
        pokemon_data = json.load(f)

    # Filter Pokemon
    results = filter_pokemon(
        pokemon_data,
        generation=args.generation,
        types=args.types,
        ability=args.ability,
        min_bst=args.min_bst,
        max_bst=args.max_bst,
        min_hp=args.min_hp,
        max_hp=args.max_hp,
        min_atk=args.min_atk,
        max_atk=args.max_atk,
        min_def=args.min_def,
        max_def=args.max_def,
        min_spa=args.min_spa,
        max_spa=args.max_spa,
        min_spd=args.min_spd,
        max_spd=args.max_spd,
        min_spe=args.min_spe,
        max_spe=args.max_spe,
    )

    # Display results
    if args.count:
        print(f"\n{len(results)} Pokemon match the criteria.")
    else:
        display_results(results, show_stats=not args.compact)


if __name__ == "__main__":
    main()
