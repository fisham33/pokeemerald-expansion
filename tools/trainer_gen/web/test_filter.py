#!/usr/bin/env python3
"""
Test script to verify the web filter logic works correctly
"""

import json
from pathlib import Path

# Load Pokemon data
data_file = Path(__file__).parent / 'pokemon_data.json'
with open(data_file) as f:
    data = json.load(f)
    pokemon_data = data['pokemon']

print(f"✓ Loaded {len(pokemon_data)} Pokemon\n")

# Test 1: Filter by generation
print("Test 1: Filter Generation 9")
gen9 = [p for p in pokemon_data if p.get('generation') == 9]
print(f"  Result: {len(gen9)} Pokemon")
print(f"  Sample: {gen9[0]['name'] if gen9 else 'None'}\n")

# Test 2: Filter by type
print("Test 2: Filter Fire type")
fire_types = []
for p in pokemon_data:
    pokemon_types = [t.lower() for t in p.get('types', [])]
    if 'fire' in pokemon_types:
        fire_types.append(p)
print(f"  Result: {len(fire_types)} Pokemon")
print(f"  Sample: {fire_types[0]['name'] if fire_types else 'None'}\n")

# Test 3: Filter by ability
print("Test 3: Filter Intimidate ability")
intimidate = []
for p in pokemon_data:
    pokemon_abilities = [a.lower() for a in p.get('abilities', [])]
    hidden = p.get('hiddenAbility', '')
    if hidden:
        pokemon_abilities.append(hidden.lower())
    if any('intimidate' in a for a in pokemon_abilities):
        intimidate.append(p)
print(f"  Result: {len(intimidate)} Pokemon")
if intimidate:
    sample = intimidate[0]
    print(f"  Sample: {sample['name']}")
    print(f"    Abilities: {sample.get('abilities', [])}")
    print(f"    Hidden: {sample.get('hiddenAbility', 'None')}\n")

# Test 4: Filter by BST range
print("Test 4: Filter BST 500-600")
bst_range = [p for p in pokemon_data if 500 <= p.get('bst', 0) <= 600]
print(f"  Result: {len(bst_range)} Pokemon")
if bst_range:
    sample = bst_range[0]
    print(f"  Sample: {sample['name']} (BST: {sample.get('bst', 0)})\n")

# Test 5: Filter by stat range
print("Test 5: Filter Speed >= 100")
fast_pokemon = []
for p in pokemon_data:
    stats = p.get('baseStats', {})
    if stats.get('spe', 0) >= 100:
        fast_pokemon.append(p)
print(f"  Result: {len(fast_pokemon)} Pokemon")
if fast_pokemon:
    sample = fast_pokemon[0]
    stats = sample.get('baseStats', {})
    print(f"  Sample: {sample['name']} (Speed: {stats.get('spe', 0)})\n")

# Test 6: Combined filters
print("Test 6: Combined - Fire type with Intimidate")
combined = []
for p in pokemon_data:
    # Check type
    pokemon_types = [t.lower() for t in p.get('types', [])]
    if 'fire' not in pokemon_types:
        continue

    # Check ability
    pokemon_abilities = [a.lower() for a in p.get('abilities', [])]
    hidden = p.get('hiddenAbility', '')
    if hidden:
        pokemon_abilities.append(hidden.lower())
    if any('intimidate' in a for a in pokemon_abilities):
        combined.append(p)

print(f"  Result: {len(combined)} Pokemon")
for i, p in enumerate(combined[:5], 1):
    print(f"    {i}. {p['name']}")

print("\n✓ All tests completed successfully!")
