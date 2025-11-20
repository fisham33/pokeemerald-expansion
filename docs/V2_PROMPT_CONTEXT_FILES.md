# V2 Rebuild Prompt - Required Context Files

When using the V2 rebuild prompt (`REBUILD_PROMPT_V2.md`), provide these files to give the AI complete context about the current implementation and data structures.

---

## Required Files (Must Include)

These files are essential for understanding the data structures and business logic:

### 1. Pokemon Data Structure
**File:** `tools/trainer_gen/pokemon_data.json`
**Lines:** First 100 lines
**Why:** Shows exact Pokemon object structure (species, name, stats, types, abilities, BST, generation, family)

**How to extract:**
```bash
head -100 tools/trainer_gen/pokemon_data.json
```

### 2. Move Data Structure
**File:** `tools/trainer_gen/move_data.json`
**Lines:** First 100 lines
**Why:** Shows move data structure (level-up moves, teachable moves, egg moves, randbats movesets)

**How to extract:**
```bash
head -100 tools/trainer_gen/move_data.json
```

### 3. Current Filter Logic
**File:** `tools/trainer_gen/web/filter.js`
**Lines:** 103-157 (the `filterPokemon` function)
**Why:** Shows current filtering algorithm that must be replicated

**How to extract:**
```bash
sed -n '103,157p' tools/trainer_gen/web/filter.js
```

### 4. Current UI Structure
**File:** `tools/trainer_gen/web/index.html`
**All lines**
**Why:** Shows HTML structure and UI organization

### 5. Current Styles
**File:** `tools/trainer_gen/web/styles.css`
**All lines**
**Why:** Shows purple gradient theme, type colors, responsive design

---

## Optional Files (Helpful Context)

These provide deeper understanding but aren't strictly required:

### 6. Pokemon Data Extraction
**File:** `tools/trainer_gen/extract_pokemon_data.py`
**Lines:** 1-100
**Why:** Shows how to parse C files and extract Pokemon data

### 7. CLI Filter Implementation
**File:** `tools/trainer_gen/filter_pokemon.py`
**All lines**
**Why:** Shows another implementation of filtering logic

### 8. README
**File:** `tools/trainer_gen/README.md`
**All lines**
**Why:** Overview of all tools and their purposes

---

## How to Provide Context to AI

### Option 1: Direct File Contents

When prompting an AI, include these sections:

```
I need you to rebuild this application using the V2 architecture.
Here are the key files from the current implementation:

=== pokemon_data.json (first 100 lines) ===
[paste content]

=== move_data.json (first 100 lines) ===
[paste content]

=== filter.js (lines 103-157) ===
[paste content]

=== index.html ===
[paste content]

=== styles.css ===
[paste content]

Now follow the instructions in REBUILD_PROMPT_V2.md to build the modular V2 version.
```

### Option 2: File References

If using an AI that can read files directly:

```
Please read these files for context:
1. tools/trainer_gen/pokemon_data.json (first 100 lines)
2. tools/trainer_gen/move_data.json (first 100 lines)
3. tools/trainer_gen/web/filter.js (lines 103-157)
4. tools/trainer_gen/web/index.html
5. tools/trainer_gen/web/styles.css

Then follow the build instructions in docs/REBUILD_PROMPT_V2.md
```

---

## Quick Context Extraction Script

Create this helper script to extract all required context:

**File:** `build/extract-context.sh`

```bash
#!/bin/bash
# Extract context files for V2 rebuild prompt

OUTPUT="v2-context.txt"

echo "Extracting context files..."

{
  echo "=== POKEMON DATA STRUCTURE ==="
  head -100 tools/trainer_gen/pokemon_data.json
  echo ""

  echo "=== MOVE DATA STRUCTURE ==="
  head -100 tools/trainer_gen/move_data.json
  echo ""

  echo "=== FILTER LOGIC ==="
  sed -n '103,157p' tools/trainer_gen/web/filter.js
  echo ""

  echo "=== HTML STRUCTURE ==="
  cat tools/trainer_gen/web/index.html
  echo ""

  echo "=== STYLES ==="
  cat tools/trainer_gen/web/styles.css
  echo ""

} > "$OUTPUT"

echo "✓ Context saved to $OUTPUT"
echo "File size: $(wc -c < $OUTPUT) bytes"
```

**Usage:**
```bash
chmod +x build/extract-context.sh
./build/extract-context.sh
# Creates v2-context.txt with all required context
```

---

## Data Structure Reference

### Pokemon Object Structure
```json
{
  "species": "BULBASAUR",
  "name": "Bulbasaur",
  "natDexNum": 1,
  "baseStats": {
    "hp": 45,
    "atk": 49,
    "def": 49,
    "spa": 65,
    "spd": 65,
    "spe": 45
  },
  "types": ["Grass", "Poison"],
  "abilities": ["Overgrow"],
  "hiddenAbility": "Chlorophyll",
  "bst": 318,
  "generation": 1,
  "family": "P_FAMILY_BULBASAUR"
}
```

### Move Object Structure
```json
{
  "BULBASAUR": {
    "name": "Bulbasaur",
    "level_up_moves": [
      {"level": 1, "move": "Tackle"},
      {"level": 3, "move": "Vine Whip"}
    ],
    "teachable_moves": ["Body Slam", "Cut", "Solar Beam"],
    "egg_moves": ["Curse", "Endure", "Giga Drain"],
    "randbats_movesets": {
      "Setup Sweeper": {
        "moves": ["Growth", "Sludge Bomb", "Giga Drain"],
        "abilities": ["Overgrow"],
        "items": ["Eviolite"]
      }
    }
  }
}
```

---

## Verification Checklist

Before submitting to AI, verify you have:

- [ ] Pokemon data structure (JSON format)
- [ ] Move data structure (JSON format)
- [ ] Current filtering algorithm (JavaScript)
- [ ] Current HTML structure
- [ ] Current CSS styles (including type colors)
- [ ] V2 rebuild prompt document

---

## Expected AI Output

After providing the context and rebuild prompt, the AI should produce:

1. **Core library** (~15 JavaScript files)
2. **Web application** (~10 JavaScript files, 1 HTML, 3 CSS)
3. **Plugin example** (~1 JavaScript file)
4. **Build scripts** (~2 bash files)
5. **Tests** (~2 test files)
6. **Documentation** (README.md)

**Total:** ~30 files, ~3000 lines of modular, tested code

---

## Common Issues

### Issue: AI doesn't understand data structure
**Solution:** Include more lines from pokemon_data.json (100-200 lines) showing different Pokemon types

### Issue: Filtering logic doesn't match V1
**Solution:** Explicitly show V1 filter code and ask AI to replicate exact behavior

### Issue: Styles don't match
**Solution:** Include complete styles.css, especially type colors section

### Issue: Missing test cases
**Solution:** Reference the test criteria from V1 (Gen 9: 124 Pokemon, Fire: 90, etc.)

---

## Summary

**Minimum required context:** 5 files
**Recommended context:** 8 files
**Total context size:** ~500KB
**Time to extract:** ~2 minutes with script

With this context, any AI can rebuild the application following the V2 architecture with full compatibility to V1 data structures and behavior.
