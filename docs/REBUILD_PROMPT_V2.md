# Pokemon Trainer Tools V2 - Modular Architecture Build Instructions

## Project Goal

Build a **modular, extensible web application** for filtering Pokemon data from the pokeemerald-expansion ROM hack codebase. The application should:

1. Extract Pokemon data from C source files into JSON
2. Convert Smogon Random Battle movesets to trainers.party format
3. Provide a filterable web interface hosted on GitHub Pages
4. Use a plugin architecture for easy extensibility
5. Eliminate code duplication through a shared core library

---

## Phase 1: Data Extraction System

### Step 1.1: Parse Pokemon Stats from C Files

**Source Files:**
- `src/data/pokemon/species_info/gen_1.h` through `gen_9.h`

**Data to Extract:**

Each Pokemon is defined as a C struct like this:
```c
#if P_FAMILY_BULBASAUR
    [SPECIES_BULBASAUR] =
    {
        .baseHP        = 45,
        .baseAttack    = 49,
        .baseDefense   = 49,
        .baseSpeed     = 45,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GRASS, TYPE_POISON),
        .abilities = { ABILITY_OVERGROW },
        .hiddenAbility = ABILITY_CHLOROPHYLL,
        .speciesName = _("Bulbasaur"),
        .natDexNum = NATIONAL_DEX_BULBASAUR,
        // ... more fields
    },
#endif
```

**Extraction Requirements:**

1. **Parse with brace counting** - Use a brace counting algorithm, NOT regex, because structs have nested braces
2. **Extract family mappings** - Map each species to its family using `#if P_FAMILY_*` directives
3. **Parse COMPOUND_STRING macros** - Handle multi-line string definitions for species names
4. **Map type constants** - Convert `TYPE_FIRE` to `"Fire"`, etc.
5. **Map ability constants** - Convert `ABILITY_OVERGROW` to `"Overgrow"`
6. **Calculate BST** - Sum all base stats (HP + Atk + Def + SpA + SpD + Spe)
7. **Determine generation** - Track which gen_X.h file each Pokemon came from

**Output Format:**

Generate `pokemon_data.json`:
```json
{
  "metadata": {
    "total_pokemon": 1082,
    "source": "pokeemerald-expansion",
    "extracted_at": "2025-01-20T12:00:00Z"
  },
  "pokemon": [
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
  ]
}
```

**Implementation Instructions:**

1. Read all gen_*.h files from `src/data/pokemon/species_info/`
2. For each file, track the generation number from filename
3. Find all `#if P_FAMILY_*` blocks and map species to families
4. Find all `[SPECIES_*] = {` entries
5. Use brace counting to extract complete struct (count opening/closing braces)
6. Parse each field using regex patterns
7. Build Pokemon objects and add to array
8. Sort by national dex number
9. Write to JSON file with proper formatting

---

### Step 1.2: Parse Move Data from C Files

**Source Files:**
- `src/data/pokemon/level_up_learnsets/gen_1.h` through `gen_9.h` - Level-up moves
- `src/data/pokemon/teachable_learnsets.h` - TM/HM/Tutor moves
- `src/data/pokemon/egg_moves/gen_1.h` through `gen_9.h` - Egg moves

**Level-Up Move Format:**
```c
static const struct LevelUpMove sBulbasaurLevelUpLearnset[] = {
    LEVEL_UP_MOVE( 1, MOVE_TACKLE),
    LEVEL_UP_MOVE( 3, MOVE_VINE_WHIP),
    LEVEL_UP_MOVE( 6, MOVE_GROWTH),
    // ...
    LEVEL_UP_END
};
```

**Teachable Move Format:**
```c
static const u16 sBulbasaurTeachableLearnset[] = {
    MOVE_BODY_SLAM,
    MOVE_CUT,
    MOVE_SOLAR_BEAM,
    // ...
    TEACHABLE_LEARNSET_END
};
```

**Egg Move Format:**
```c
#if P_FAMILY_BULBASAUR
    egg_moves(BULBASAUR,
        MOVE_CURSE,
        MOVE_ENDURE,
        MOVE_GIGA_DRAIN),
#endif
```

**Extraction Requirements:**

1. **Parse level-up moves** - Extract level and move constant pairs
2. **Parse teachable moves** - Extract move constant lists
3. **Parse egg moves** - Extract from `egg_moves()` macro
4. **Propagate egg moves to families** - All Pokemon in a family get the same egg moves
5. **Handle name variants** - Match `BASCULIN_WHITE_STRIPED` to `BASCULIN` family
6. **Handle gender variants** - Propagate from `_MALE`/`_FEMALE` to base form
7. **Clean move names** - Convert `MOVE_SOLAR_BEAM` to `"Solar Beam"`

**Output Format:**

Generate `move_data.json`:
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
      "egg_moves": ["Curse", "Endure", "Giga Drain"]
    }
  }
}
```

---

### Step 1.3: Integrate Smogon Random Battles Data (Optional)

**Purpose:** Enhance the move database with competitive movesets from Smogon's Random Battle formats.

**Source URLs:**
- Singles: `https://pkmn.github.io/randbats/data/gen9randombattle.json`
- Doubles: `https://pkmn.github.io/randbats/data/gen9randomdoublesbattle.json`
- Baby/LC: `https://pkmn.github.io/randbats/data/gen9babyrandombattle.json`

**Data Format:**
```json
{
  "bulbasaur": {
    "level": 84,
    "moves": [
      ["gigadrain", "sleeppowder", "sludgebomb"],
      ["sludgebomb", "synthesis", "toxicspikes", "powerwhip"]
    ],
    "abilities": ["Overgrow", "Chlorophyll"],
    "teraTypes": ["Fire", "Poison"],
    "items": ["Life Orb", "Heavy-Duty Boots"]
  }
}
```

**Integration Requirements:**

1. **Download all three JSON files** from Smogon's pkmn.github.io
2. **Merge data** - Combine movesets from all formats, don't overwrite
3. **Normalize names** - Convert Smogon names (lowercase, no spaces) to game constants (UPPERCASE)
4. **Handle variants** - Map forme names like "charizardmegax" to "CHARIZARD_MEGA_X"
5. **Identify roles** - Detect roles from moveset patterns (setup sweeper, wallbreaker, support, etc.)
6. **Add to move_data.json** - Include under `randbats_movesets` for each Pokemon

**Role Detection Logic:**
- **Setup Sweeper** - Has setup moves (Dragon Dance, Swords Dance, Calm Mind, etc.)
- **Wallbreaker** - High power moves with choice items
- **Fast Attacker** - High speed tier with offensive moves
- **Bulky Support** - Defensive moves (Protect, Wish, Heal Bell, etc.)
- **Weather Setter** - Has weather-setting ability
- **Weather Abuser** - Has weather-boosting ability

This data will be used later for the trainers.party converter.

---

## Phase 2: Smogon to trainers.party Converter

Build a tool that converts Smogon Random Battle data into pokeemerald's trainers.party format.

### trainers.party Format

The `trainers.party` file uses this format:
```
=== TRAINER_EXAMPLE ===
Name: Ace Trainer John
Class: Ace Trainer
Pic: Ace Trainer
Gender: Male
Music: Male
Double Battle: Yes
AI: Check Bad Move / Try To Faint / Check Viability
Party Size: 4
Pool Rules: Weather Doubles

Ninetales-Alola @ Light Clay
Ability: Snow Warning
Tera Type: Ice
Tags: Weather Setter
- Aurora Veil
- Blizzard
- Moonblast
- Protect

Arctozolt @ Life Orb
Ability: Slush Rush
Tera Type: Ice
Tags: Weather Abuser
- Bolt Beak
- Freeze-Dry
- Icicle Crash
- Protect
```

### Converter Requirements:

**Conversion Modes:**

1. **Single Mode** - One moveset per Pokemon, no tags, 4 random moves
2. **All Roles Mode** - Generate entry for every role a Pokemon can have
3. **Pool Mode** - Generate Pokemon with TPP tags for manual pool building
4. **Trainer Pool Mode** - Complete auto-generated trainer with configured pool

**Tag Assignment System:**

Automatically assign Trainer Party Pool (TPP) tags based on:

**Role-Based Tags:**
- Fast attackers, weather setters → `Lead`
- Setup sweepers, wallbreakers → `Ace`
- Support Pokemon → `Support`

**Ability-Based Tags:**
- Drought, Drizzle, Snow Warning, Sand Stream, terrain setters → `Weather Setter`
- Chlorophyll, Swift Swim, Slush Rush, Sand Rush, Solar Power → `Weather Abuser`

**Example Tag Mappings:**
```
Ninetales-Alola (Snow Warning) → Weather Setter
Arctozolt (Slush Rush) → Weather Abuser
Incineroar (Intimidate) → Support
Urshifu (Unseen Fist) → Ace
```

**Move Selection:**

1. **4 moves per set** - Randomly select 4 from available moves
2. **Prioritize coverage** - If moveset has 5+ moves, create variants
3. **Set variants** - Generate 2 variants when Pokemon has:
   - Multiple abilities
   - Multiple items
   - 5+ moves

**Archetype Filtering:**

Support filtering Pokemon by:
- **Type filtering** - Single type or comma-separated list (e.g., "Fire,Dragon")
- **Trainer class filtering** - Use predefined archetypes:
  - Hiker: Rock/Ground/Fighting
  - Swimmer: Water
  - Kindler: Fire
  - Dragon Tamer: Dragon
  - Hex Maniac: Ghost/Dark/Poison
  - Psychic: Psychic
  - Ace Trainer: Any type

**Species Filtering:**

Respect `include/config/species_enabled.h`:
- Parse `#define P_GEN_X_POKEMON TRUE/FALSE`
- Parse `#define P_FAMILY_* TRUE/FALSE`
- Only include Pokemon from enabled families/generations

**Output Features:**

1. **Set comments** - Add role and format comments:
   ```
   /* Doubles */
   /* Doubles Bulky Attacker */
   Torkoal @ Sitrus Berry
   ```

2. **Split output** - Option to split into separate files:
   - `converted_movesets_singles.txt`
   - `converted_movesets_doubles.txt`
   - `converted_movesets_babies.txt`

3. **Level ranges** - Auto-detect from source:
   - Baby Random Battles: levels 5-15
   - Singles/Doubles: levels 75-85

### Trainer Pool Rules

When generating complete trainers, support these pool rules:
- `Basic` - Basic lead/ace selection for singles
- `Doubles` - Lead/ace for doubles (2 leads, 2 aces)
- `Weather Singles` - Weather setter + abuser for singles
- `Weather Doubles` - Weather setter + abuser for doubles
- `Support Doubles` - Includes support Pokemon

### Implementation Instructions:

1. Load Smogon Random Battle JSON files
2. Parse Pokemon entries and movesets
3. Apply archetype filter if specified
4. Apply species filter if `species_enabled.h` parsing enabled
5. For each Pokemon:
   - Detect roles from moveset patterns
   - Assign appropriate tags
   - Select 4 moves randomly
   - Generate variants if multiple options exist
6. Format output in trainers.party format
7. Add comments for role/format identification
8. Write to output file(s)

---

## Phase 3: Core Filter Library

Build a reusable JavaScript library for filtering Pokemon. This will be used by all interfaces (web, CLI, etc.).

### Architecture Requirements:

**Base Filter Class:**
- Every filter extends a base class
- Implements `apply(pokemon, value)` method
- Implements `validate(value)` method
- Has metadata (name, type, label, options)

**Filter Types:**
- `number` - Single number input (Generation)
- `text` - Text search (Ability)
- `multi-select` - Multiple selections (Types)
- `range` - Min/max inputs (BST, individual stats)

**Filter Registry:**
- Central registry for all filters
- Supports dynamic registration (plugins)
- Can retrieve filters by name
- Can get all available filters

### Filters to Implement:

1. **Generation Filter** - Filter by generation number (1-9)
2. **Type Filter** - Filter by type(s), matches if Pokemon has ANY selected type
3. **Ability Filter** - Filter by ability name (partial match, includes hidden)
4. **BST Filter** - Filter by base stat total range
5. **Individual Stat Filters** - Six filters for HP, Atk, Def, SpA, SpD, Spe (each with min/max)

### Filter Logic:

```
For each Pokemon:
  For each active filter:
    - Skip if filter value is empty/null
    - Validate the filter value
    - Apply filter - if fails, exclude Pokemon
  If all filters pass, include Pokemon
```

### Services to Implement:

**PokemonService:**
- Load Pokemon data from JSON
- Cache loaded data
- Search by name (fuzzy match)
- Get by dex number
- Get by species constant

**FilterService:**
- Apply multiple filters to Pokemon array
- Get available filters from registry
- Validate filter values

---

## Phase 4: Web Application

Build a static web application that can be hosted on GitHub Pages.

### File Structure:

```
web/
├── index.html
├── src/
│   ├── app.js                    # Main application
│   ├── config.js                 # Configuration
│   ├── components/
│   │   ├── FilterPanel.js        # Filter UI
│   │   ├── PokemonList.js        # Results display
│   │   └── PokemonCard.js        # Individual Pokemon card
│   └── views/
│       └── FilterView.js         # Main filter page
├── public/
│   ├── data/
│   │   └── pokemon.json          # Generated data
│   └── styles/
│       ├── main.css              # Base styles
│       └── components.css        # Component styles
└── core/                         # Symlink to shared core library
```

### UI Requirements:

**Layout:**
- Header with title and subtitle
- Filter panel on top
- Results section below
- Footer with credits

**Filter Panel:**
- Input for Generation (number, 1-9)
- Input for Types (text, comma-separated)
- Input for Ability (text, partial match)
- Range inputs for BST (min/max)
- Range inputs for each stat (HP, Atk, Def, SpA, SpD, Spe)
- Three buttons: Filter, Clear, Show All

**Results Display:**
- Show count of results
- Display Pokemon cards in scrollable area
- Each card shows:
  - Name and species
  - Generation
  - Types (with colored badges)
  - BST
  - All six stats
  - Abilities (normal and hidden)

**Styling Requirements:**
- Purple gradient background: `linear-gradient(135deg, #667eea 0%, #764ba2 100%)`
- White container with shadow
- Type badge colors (all 18 types):
  - Normal: #A8A878, Fire: #F08030, Water: #6890F0, Electric: #F8D030
  - Grass: #78C850, Ice: #98D8D8, Fighting: #C03028, Poison: #A040A0
  - Ground: #E0C068, Flying: #A890F0, Psychic: #F85888, Bug: #A8B820
  - Rock: #B8A038, Ghost: #705898, Dragon: #7038F8, Dark: #705848
  - Steel: #B8B8D0, Fairy: #EE99AC
- Hidden ability badge: Gold background (#ffd700)
- Responsive design (mobile breakpoint: 768px)
- Smooth transitions (0.3s)
- Custom scrollbar (purple themed)

### Data Loading:

1. On page load, fetch `public/data/pokemon.json`
2. Show loading spinner while fetching
3. On success, initialize PokemonService with data
4. On error, show error message with retry button
5. Cache data for the session

### Event Handling:

1. Filter button - Collect all filter values, apply filters, display results
2. Clear button - Reset all inputs, show initial message
3. Show All button - Display all Pokemon
4. Enter key on any input - Trigger filter

---

## Phase 5: Plugin System

Create a plugin architecture that allows adding custom filters without modifying core code.

### Plugin Interface:

Plugins should:
1. Import base filter class
2. Extend it with custom logic
3. Register with FilterRegistry
4. Automatically appear in all UIs

### Example Plugin Structure:

```javascript
// plugins/evolution-stage-filter.js
import { BaseFilter } from '../core/filters/base-filter.js';
import { FilterRegistry } from '../core/filters/filter-registry.js';

class EvolutionStageFilter extends BaseFilter {
  constructor() {
    super({
      name: 'evolutionStage',
      type: 'select',
      label: 'Evolution Stage',
      options: ['Base', 'Stage 1', 'Stage 2']
    });
  }

  apply(pokemon, stage) {
    // Custom filter logic
    return true;
  }
}

FilterRegistry.register(new EvolutionStageFilter());
```

### Plugin Loading:

- Plugins are loaded as ES6 modules
- Register themselves on import
- Automatically integrate with UI
- No core code changes needed

---

## Phase 6: Build and Deployment

### Build Process:

**Step 1: Generate Data**
- Run data extraction on C source files
- Output pokemon_data.json
- Copy to web/public/data/

**Step 2: Optimize**
- Minify JavaScript (optional for v1)
- Compress JSON (optional)
- Optimize images/assets

**Step 3: Deploy to GitHub Pages**
- Copy web/ directory to repository
- Enable GitHub Pages in settings
- Source: Branch + Folder
- URL: `https://username.github.io/repo-name/`

### GitHub Actions Workflow:

Create `.github/workflows/deploy.yml`:
- Trigger on push to main
- Run data extraction
- Build web app
- Deploy to gh-pages branch

---

## Testing Requirements

### Core Library Tests:

Test each filter:
- Generation filter: Gen 9 returns 124 Pokemon
- Type filter: Fire returns 90 Pokemon
- Ability filter: Intimidate returns 33 Pokemon
- BST filter: 500-600 returns 324 Pokemon
- Stat filter: Speed >= 100 returns 192 Pokemon
- Combined: Fire + Intimidate returns 6 Pokemon

### Web Application Tests:

- Data loads successfully (1082 Pokemon)
- All filters work correctly
- UI renders properly
- Responsive on mobile
- Type badges show correct colors
- No console errors

### Data Extraction Tests:

- All 9 generations extracted
- Families mapped correctly
- Stats calculated correctly (BST)
- Types converted correctly
- Abilities extracted (normal + hidden)

---

## Configuration System

Create a centralized config file:

```javascript
// web/src/config.js
export const config = {
  data: {
    sources: {
      pokemon: '/public/data/pokemon.json'
    },
    cache: {
      enabled: true,
      ttl: 3600000 // 1 hour
    }
  },

  ui: {
    theme: 'purple-gradient',
    resultsPerPage: 50,
    typeColors: { /* ... */ }
  },

  features: {
    comparison: false,      // Future feature
    export: false,          // Future feature
    teamBuilder: false      // Future feature
  }
};
```

---

## Success Criteria

The V2 application is complete when:

✅ **Data Extraction:**
- Extracts 1082 Pokemon from C files
- All stats, types, abilities present
- Families mapped correctly
- BST calculated correctly
- Smogon Random Battle data integrated
- Output is valid JSON

✅ **Smogon Converter:**
- Parses all three Random Battle formats
- Correctly assigns TPP tags
- Generates valid trainers.party format
- Archetype filtering works
- Species filtering respects config
- Produces usable trainer pools

✅ **Core Library:**
- All 7 filters implemented and working
- Filter registry supports plugins
- Services load and filter data
- No code duplication

✅ **Web Application:**
- Loads and displays 1082 Pokemon
- All filters work correctly
- UI matches design (purple gradient, type colors)
- Responsive on mobile
- No errors in console

✅ **Plugin System:**
- Example plugin works
- Can add filters without core changes
- Plugins auto-integrate with UI

✅ **Build Process:**
- Data generation is automated
- Can deploy to GitHub Pages
- Production build is optimized

✅ **Testing:**
- All test cases pass
- Data extraction is verified
- Filter logic is correct

---

## Key Architectural Principles

### 1. Separation of Concerns
- **Data Layer** - Handles loading, caching, storage
- **Business Logic** - Handles filtering, validation
- **Presentation** - Handles UI rendering

### 2. Modularity
- Each component has single responsibility
- Components can be tested in isolation
- Can replace components independently

### 3. Extensibility
- Plugin system for custom filters
- Configuration-driven behavior
- Easy to add new features

### 4. No Duplication
- Single filter implementation used by all interfaces
- Shared data models
- Reusable components

### 5. Progressive Enhancement
- Core features work first
- Advanced features added via plugins
- Graceful degradation

---

## Implementation Order

Follow this exact sequence:

**Phase 1: Data Extraction** (Build data pipeline first)
1. Implement Pokemon stats extractor
2. Implement move data extractor
3. Integrate Smogon Random Battle data
4. Generate JSON files
5. Verify data quality

**Phase 2: Smogon Converter** (Build trainers.party converter second)
1. Parse Smogon JSON format
2. Implement role detection
3. Implement tag assignment
4. Implement archetype filtering
5. Implement species filtering
6. Generate trainers.party output
7. Test all conversion modes

**Phase 3: Core Library** (Build shared filter logic third)
1. Create base filter class
2. Implement all concrete filters
3. Create filter registry
4. Implement services
5. Write unit tests

**Phase 4: Web Application** (Build UI fourth)
1. Create HTML structure
2. Implement data loading
3. Build filter panel component
4. Build results components
5. Wire up events
6. Apply styles
7. Test responsiveness

**Phase 5: Plugin System** (Add extensibility fifth)
1. Define plugin interface
2. Create example plugin
3. Document plugin development
4. Test plugin integration

**Phase 6: Build & Deploy** (Automate last)
1. Create build scripts
2. Set up GitHub Actions
3. Deploy to GitHub Pages
4. Verify production build

---

## Next Steps After V2

Once V2 is complete, these features can be added as plugins or extensions:

1. **Pokemon Comparison** - Compare stats of multiple Pokemon side-by-side
2. **Team Builder** - Build 6-Pokemon teams with type coverage analysis
3. **Move Query Interface** - Web UI for looking up all moves available to any Pokemon
4. **Advanced Filters** - Egg groups, evolution stage, legendary status, etc.
5. **Trainer Pool Generator UI** - Web interface for the Smogon converter with live preview
6. **Moveset Analyzer** - Analyze competitive viability of movesets

Each new feature should be built as a plugin to demonstrate the extensibility of the architecture.

---

## Documentation Requirements

Create these documentation files:

1. **README.md** - Quick start, features, usage
2. **ARCHITECTURE.md** - System design, data flow
3. **PLUGIN_GUIDE.md** - How to create plugins
4. **API.md** - Core library API reference
5. **DEPLOYMENT.md** - Build and deployment process

---

## Summary

This V2 architecture provides:

- **Modular design** - Shared core library eliminates duplication
- **Extensibility** - Plugin system for community contributions
- **Maintainability** - Clear separation of concerns
- **Performance** - Optimized for static hosting
- **Developer experience** - Easy to understand and extend

The result is a professional, production-ready application that can evolve with community needs while maintaining code quality and architectural integrity.
