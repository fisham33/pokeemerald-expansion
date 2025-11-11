#!/usr/bin/env python3
"""
Parse species_enabled.h to determine which Pokemon families are enabled
"""

import re
from pathlib import Path
from typing import Dict, Set


def evaluate_boolean_expression(expr: str, defines: Dict[str, bool]) -> bool:
    """Evaluate a simple boolean expression with TRUE/FALSE and define names"""
    expr = expr.strip()

    # Base cases
    if expr == 'TRUE':
        return True
    if expr == 'FALSE':
        return False

    # Check if it's a reference to another define
    if expr in defines:
        return defines[expr]

    # Handle simple logical expressions (we don't need full C preprocessing)
    # For now, just handle direct references and TRUE/FALSE
    return False


def parse_species_enabled(config_path: Path = None) -> Dict[str, bool]:
    """
    Parse species_enabled.h and return a dict of family/generation defines and their values

    Returns:
        Dict mapping define names (e.g., 'P_FAMILY_BULBASAUR', 'P_GEN_1_POKEMON') to bool values
    """
    if config_path is None:
        # Default path from tools/trainer_gen
        script_dir = Path(__file__).parent
        config_path = script_dir.parent.parent / 'include' / 'config' / 'species_enabled.h'

    if not config_path.exists():
        print(f"Warning: species_enabled.h not found at {config_path}")
        return {}

    defines = {}

    with open(config_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Parse #define statements
    # Pattern: #define NAME VALUE
    define_pattern = r'#define\s+(P_(?:GEN_\d+_POKEMON|FAMILY_\w+|.*FORMS?))\s+(\w+)'

    for match in re.finditer(define_pattern, content):
        define_name = match.group(1)
        define_value = match.group(2)

        # Evaluate the value
        if define_value == 'TRUE':
            defines[define_name] = True
        elif define_value == 'FALSE':
            defines[define_name] = False
        else:
            # It's a reference to another define - resolve it
            # We need to do this iteratively since defines can reference other defines
            pass

    # Second pass: resolve references
    max_iterations = 10
    for _ in range(max_iterations):
        changed = False
        for match in re.finditer(define_pattern, content):
            define_name = match.group(1)
            define_value = match.group(2)

            if define_value not in ['TRUE', 'FALSE']:
                # Try to resolve the reference
                if define_value in defines and define_name not in defines:
                    defines[define_name] = defines[define_value]
                    changed = True
                elif define_value in defines:
                    # Update if changed
                    new_val = defines[define_value]
                    if defines.get(define_name) != new_val:
                        defines[define_name] = new_val
                        changed = True

        if not changed:
            break

    return defines


def get_enabled_families(config_path: Path = None) -> Set[str]:
    """
    Get the set of all enabled Pokemon families

    Returns:
        Set of family names (e.g., {'P_FAMILY_BULBASAUR', 'P_FAMILY_CHARMANDER', ...})
    """
    defines = parse_species_enabled(config_path)

    # Filter to only families that are TRUE
    enabled = {
        name for name, value in defines.items()
        if name.startswith('P_FAMILY_') and value is True
    }

    return enabled


def get_enabled_generations(config_path: Path = None) -> Set[int]:
    """
    Get the set of enabled generation numbers

    Returns:
        Set of generation numbers (e.g., {1, 2, 3, 4, 5, 6, 7, 8, 9})
    """
    defines = parse_species_enabled(config_path)

    enabled_gens = set()

    for gen_num in range(1, 10):  # Gen 1-9
        define_name = f'P_GEN_{gen_num}_POKEMON'
        if defines.get(define_name, False):
            enabled_gens.add(gen_num)

    return enabled_gens


def is_pokemon_enabled(family: str, generation: int, config_path: Path = None) -> bool:
    """
    Check if a specific Pokemon is enabled based on its family and generation

    Args:
        family: Family name (e.g., 'P_FAMILY_BULBASAUR')
        generation: Generation number (1-9)
        config_path: Optional path to species_enabled.h

    Returns:
        True if the Pokemon is enabled
    """
    defines = parse_species_enabled(config_path)

    # Check family first
    if family in defines:
        return defines[family]

    # Fall back to generation
    gen_define = f'P_GEN_{generation}_POKEMON'
    return defines.get(gen_define, False)


def main():
    """Test/debug the parser"""
    print("Species Enabled Parser")
    print("=" * 70)

    defines = parse_species_enabled()

    print(f"\nTotal defines parsed: {len(defines)}")

    # Show generation settings
    print("\nGeneration Settings:")
    for gen_num in range(1, 10):
        define_name = f'P_GEN_{gen_num}_POKEMON'
        status = "✓ ENABLED" if defines.get(define_name, False) else "✗ DISABLED"
        print(f"  Gen {gen_num}: {status}")

    # Count enabled families
    enabled_families = get_enabled_families()
    total_families = sum(1 for name in defines.keys() if name.startswith('P_FAMILY_'))

    print(f"\nFamily Settings:")
    print(f"  Total families: {total_families}")
    print(f"  Enabled families: {len(enabled_families)}")
    print(f"  Disabled families: {total_families - len(enabled_families)}")

    # Show some sample families
    print(f"\nSample Enabled Families (first 10):")
    for family in sorted(enabled_families)[:10]:
        print(f"  - {family}")

    # Show some disabled families
    disabled_families = {
        name for name in defines.keys()
        if name.startswith('P_FAMILY_') and not defines[name]
    }

    if disabled_families:
        print(f"\nSample Disabled Families (first 5):")
        for family in sorted(disabled_families)[:5]:
            print(f"  - {family}")


if __name__ == "__main__":
    main()
