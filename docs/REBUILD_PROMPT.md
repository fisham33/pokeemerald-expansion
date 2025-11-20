# Pokemon Trainer Generator - Complete Rebuild Prompt

## Project Overview

Build a comprehensive Pokemon toolset for the pokeemerald-expansion ROM hack project that:
1. Extracts Pokemon data from C source files into JSON databases
2. Converts Smogon Random Battle movesets to trainers.party format
3. Filters Pokemon by stats, types, and abilities (CLI, GUI, and web versions)
4. Queries all moves available to any Pokemon

## Architecture

```
pokeemerald-expansion/
├── src/data/pokemon/              # Source data (C files)
│   ├── species_info/gen_*.h       # Pokemon stats, types, abilities
│   ├── level_up_learnsets/gen_*.h # Level-up moves
│   ├── teachable_learnsets.h      # TM/HM/Tutor moves
│   └── egg_moves/gen_*.h          # Egg moves
│
├── include/config/
│   └── species_enabled.h          # Pokemon family enable/disable flags
│
└── tools/trainer_gen/
    ├── extract_pokemon_data.py    # Generate pokemon_data.json
    ├── extract_move_data.py       # Generate move_data.json
    ├── convert_randbats_to_party.py # Convert Showdown → trainers.party
    ├── filter_pokemon.py          # CLI filter tool
    ├── gui_filter.py              # Desktop GUI filter
    ├── query_moves.py             # Query Pokemon moves
    ├── pokemon_data.json          # Generated Pokemon database
    ├── move_data.json             # Generated move database
    └── web/                       # Web-based filter (GitHub Pages)
        ├── index.html
        ├── filter.js
        ├── styles.css
        └── pokemon_data.json
```

---

## Part 1: Pokemon Data Extraction

### 1.1 Extract Pokemon Stats (`extract_pokemon_data.py`)

**Purpose**: Parse C source files and generate `pokemon_data.json` with all Pokemon data.

**Input**: `src/data/pokemon/species_info/gen_*.h` files

**Output**: `pokemon_data.json`

```json
{
  "metadata": {
    "total_pokemon": 1082,
    "source": "pokeemerald-expansion",
    "generation": 9
  },
  "pokemon": [
    {
      "species": "BULBASAUR",
      "name": "Bulbasaur",
      "natDexNum": 1,
      "baseStats": {"hp": 45, "atk": 49, "def": 49, "spa": 65, "spd": 65, "spe": 45},
      "types": ["Grass", "Poison"],
      "abilities": ["Overgrow"],
      "hiddenAbility": "Chlorophyll",
      "bst": 318,
      "generation": 1,
      "family": "P_FAMILY_BULBASAUR"
    }
  ]
}
```

**Key Requirements**:
- Parse C structs using brace counting (not regex) for nested structures
- Extract: species name, display name, dex number, stats, types, abilities, BST
- Map families using `#if P_FAMILY_*` blocks
- Handle COMPOUND_STRING macros for species names
- Support all 9 generations

### 1.2 Extract Move Data (`extract_move_data.py`)

**Purpose**: Parse learnset files and generate `move_data.json` with all moves.

**Input**:
- `src/data/pokemon/level_up_learnsets/gen_*.h`
- `src/data/pokemon/teachable_learnsets.h`
- `src/data/pokemon/egg_moves/gen_*.h`
- Smogon JSON files (optional)

**Output**: `move_data.json`

```json
{
  "metadata": {
    "total_pokemon": 1082,
    "source": "pokeemerald-expansion"
  },
  "pokemon": {
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
}
```

**Key Requirements**:
- Parse level-up moves with levels
- Parse teachable moves (TMs/HMs/Tutor)
- Parse egg moves and propagate to entire evolutionary family
- Handle name variants (BASCULIN vs BASCULIN_WHITE_STRIPED)
- Handle gender variants (propagate from _M/_F to base form)
- Merge Smogon Random Battle movesets from multiple files (singles, doubles, babies)
- Clean move names: `MOVE_SOLAR_BEAM` → `Solar Beam`

---

## Part 2: Smogon Random Battles Converter

### 2.1 Convert to trainers.party Format (`convert_randbats_to_party.py`)

**Purpose**: Download Smogon Random Battle data and convert to pokeemerald trainers.party format.

**Input**: JSON files from https://pkmn.github.io/randbats/data/
- `gen9randombattle.json` (singles)
- `gen9randomdoublesbattle.json` (doubles)
- `gen9babyrandombattle.json` (LC)

**Output**: `converted_movesets.txt` in trainers.party format

**Features**:
- 4 conversion modes: single, all-roles, pool, trainer-pool
- Archetype filtering (by type or trainer class)
- Species filtering (respect species_enabled.h)
- Auto-assign tags (Lead, Ace, Support, Weather Setter, Weather Abuser)
- Generate set variants (multiple abilities/items/moves)
- Split output by format (singles/doubles/babies)

**Example Output**:
```
Ninetales-Alola @ Light Clay
Ability: Snow Warning
Tera Type: Ice
Tags: Weather Setter
- Aurora Veil
- Blizzard
- Moonblast
- Protect
```

**Tag Assignment Logic**:
- Weather setters: Drought, Drizzle, Snow Warning, Sand Stream → `Weather Setter`
- Weather abusers: Chlorophyll, Swift Swim, Slush Rush, etc. → `Weather Abuser`
- Fast attackers, setup sweepers → `Lead` or `Ace`
- Support roles → `Support`

---

## Part 3: Pokemon Filtering Tools

### 3.1 CLI Filter (`filter_pokemon.py`)

**Purpose**: Command-line tool to filter Pokemon by stats, types, abilities.

**Usage**:
```bash
python3 filter_pokemon.py --gen 9 --type Fire --ability Intimidate --min-bst 500 --min-spe 100
```

**Filters**:
- Generation (1-9)
- Types (comma-separated, ANY match)
- Ability (partial match, includes hidden)
- BST range (min/max)
- Individual stats (HP, Atk, Def, SpA, SpD, Spe) with min/max

**Output modes**: detailed, compact, count-only

### 3.2 Desktop GUI Filter (`gui_filter.py`)

**Purpose**: Tkinter GUI for the CLI filter tool.

**Features**:
- Text inputs for all filter criteria
- Filter, Clear, Show All buttons
- Scrollable results with full stats display
- Cross-platform launchers (launch_filter_gui.sh, launch_filter_gui.bat)

### 3.3 Web Filter (`web/index.html`, `web/filter.js`, `web/styles.css`)

**Purpose**: GitHub Pages hosted filter tool (no installation needed).

**Tech Stack**: Pure HTML/CSS/JavaScript, no frameworks

**Design**:
- Purple gradient theme (#667eea to #764ba2)
- Pokemon type color badges (18 types)
- Responsive mobile layout
- Client-side filtering (fast, no backend)

**Data Loading**: Fetch `pokemon_data.json` on page load

**Filter Logic**: Same as CLI (generation, types, ability, BST, stats)

**UI Components**:
- Filter inputs (generation, types, ability, BST, 6 stats)
- 3 buttons: Filter, Clear, Show All
- Result count display
- Scrollable Pokemon cards with stats and abilities

---

## Part 4: Query Tool

### 4.1 Query Pokemon Moves (`query_moves.py`)

**Purpose**: Look up all moves available to any Pokemon.

**Usage**:
```bash
python3 query_moves.py Bulbasaur
python3 query_moves.py "Tapu Koko" --level-only
```

**Output**:
- Level-up moves with levels
- Teachable moves (TMs/HMs/Tutor)
- Egg moves (family-wide)
- Random Battles movesets (all roles)
- Total unique move count

---

## Part 5: Species Filtering

### 5.1 Parse species_enabled.h (`parse_species_enabled.py`)

**Purpose**: Read ROM hack configuration to determine which Pokemon families are enabled.

**Input**: `include/config/species_enabled.h`

**Logic**:
- Parse `#define P_GEN_X_POKEMON TRUE/FALSE`
- Parse `#define P_FAMILY_* TRUE/FALSE`
- Resolve define references iteratively

**Usage**: Used by converter with `--use-species-enabled` flag to filter Pokemon

---

## Implementation Guide

### Step 1: Pokemon Data Extractor

1. Parse species_info files using brace counting algorithm
2. Extract all fields from C structs
3. Map families from `#if P_FAMILY_*` blocks
4. Calculate BST (sum of all stats)
5. Output JSON with 1000+ Pokemon

### Step 2: Move Data Extractor

1. Parse level-up learnsets (level + move pairs)
2. Parse teachable learnsets (move lists)
3. Parse egg moves by family
4. Propagate egg moves across evolutionary families (with fuzzy matching)
5. Fetch and merge Smogon Random Battle data
6. Output comprehensive move database

### Step 3: Random Battles Converter

1. Download/load Smogon JSON files
2. Parse Pokemon roles and movesets
3. Filter by archetype (types or trainer classes)
4. Filter by species_enabled.h (optional)
5. Generate set variants (multiple abilities/items)
6. Assign TPP tags based on roles and abilities
7. Output in trainers.party format

### Step 4: Filter Tools

1. Load pokemon_data.json
2. Implement filter functions (generation, type, ability, BST, stats)
3. CLI: argparse with all filter options
4. GUI: Tkinter with text inputs and scrollable results
5. Web: HTML form + JavaScript filtering + CSS styling

### Step 5: Query Tool

1. Load move_data.json
2. Fuzzy name matching (normalize spaces, hyphens, case)
3. Display all move categories with formatting
4. Show Random Battles movesets by role

---

## Testing

**Pokemon Data Extraction**:
- ✓ 1082 Pokemon extracted
- ✓ All stats, types, abilities present
- ✓ Families mapped correctly
- ✓ BST calculated correctly

**Move Data Extraction**:
- ✓ Level-up moves with levels
- ✓ Teachable moves present
- ✓ Egg moves propagated to families
- ✓ Basculegion has egg moves (gender variant handling)
- ✓ Venusaur has 3 roles (merged from singles+doubles)

**Filtering**:
- ✓ Gen 9: 124 Pokemon
- ✓ Fire type: 90 Pokemon
- ✓ Intimidate: 33 Pokemon
- ✓ BST 500-600: 324 Pokemon
- ✓ Speed >= 100: 192 Pokemon
- ✓ Fire + Intimidate: 6 Pokemon

**Web Version**:
- ✓ Loads 1082 Pokemon
- ✓ All filters work correctly
- ✓ Responsive on mobile
- ✓ Type badges show correct colors
- ✓ Can be hosted on GitHub Pages

---

## Key Technical Challenges & Solutions

1. **Nested C Structures**: Use brace counting, not regex
2. **COMPOUND_STRING**: Parse multi-line string macros
3. **Egg Move Families**: Read gen_X_families.h, propagate to all members
4. **Name Variants**: Fuzzy matching with underscore removal
5. **Gender Variants**: Copy from _M/_F to base form
6. **Random Battles Merging**: Merge roles from multiple files (not overwrite)
7. **Web Data Loading**: Fetch from same directory for GitHub Pages compatibility
8. **Client-side Filtering**: Fast JavaScript filtering for 1000+ Pokemon

---

## Final Deliverables

```
tools/trainer_gen/
├── extract_pokemon_data.py       # 400 lines - Pokemon stats extractor
├── extract_move_data.py          # 500 lines - Move data extractor
├── convert_randbats_to_party.py  # 800 lines - Showdown converter
├── filter_pokemon.py             # 250 lines - CLI filter
├── gui_filter.py                 # 300 lines - Desktop GUI
├── query_moves.py                # 200 lines - Move query tool
├── parse_species_enabled.py      # 200 lines - Config parser
├── pokemon_data.json             # 494 KB - Pokemon database
├── move_data.json                # 3.2 MB - Move database
└── web/                          # Web-based filter
    ├── index.html                # 111 lines
    ├── filter.js                 # 273 lines
    ├── styles.css                # 408 lines
    └── pokemon_data.json         # 494 KB (copy)
```

**Total**: ~3200 lines of Python, ~800 lines of HTML/CSS/JS

---

## Summary

This is a complete Pokemon data pipeline:
1. **Extract** Pokemon and move data from C source files
2. **Convert** competitive movesets to ROM hack format
3. **Filter** Pokemon by any criteria (CLI/GUI/web)
4. **Query** all moves available to any Pokemon
5. **Deploy** web version to GitHub Pages for public access

All tools work together through shared JSON databases (`pokemon_data.json` and `move_data.json`).
