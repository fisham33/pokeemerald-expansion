# Pokemon Trainer Tools V2 - Modular Architecture Build Instructions

## Project Goal

Build a **modular, extensible web application** for filtering Pokemon data from the pokeemerald-expansion ROM hack codebase. The application should:

1. Extract Pokemon data from C source files into JSON
2. Provide a filterable web interface hosted on GitHub Pages
3. Use a plugin architecture for easy extensibility
4. Eliminate code duplication through a shared core library

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

## Phase 2: Core Filter Library

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

## Phase 3: Web Application

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

## Phase 4: Plugin System

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

## Phase 5: Build and Deployment

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
- Output is valid JSON

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
3. Generate JSON files
4. Verify data quality

**Phase 2: Core Library** (Build shared logic second)
1. Create base filter class
2. Implement all concrete filters
3. Create filter registry
4. Implement services
5. Write unit tests

**Phase 3: Web Application** (Build UI third)
1. Create HTML structure
2. Implement data loading
3. Build filter panel component
4. Build results components
5. Wire up events
6. Apply styles
7. Test responsiveness

**Phase 4: Plugin System** (Add extensibility fourth)
1. Define plugin interface
2. Create example plugin
3. Document plugin development
4. Test plugin integration

**Phase 5: Build & Deploy** (Automate last)
1. Create build scripts
2. Set up GitHub Actions
3. Deploy to GitHub Pages
4. Verify production build

---

## Next Steps After V2

Once V2 is complete, these features can be added as plugins:

1. **Pokemon Comparison** - Compare stats of multiple Pokemon side-by-side
2. **Export System** - Export filtered results to CSV, JSON, or trainers.party format
3. **Team Builder** - Build 6-Pokemon teams with type coverage analysis
4. **Move Query** - Look up all moves available to any Pokemon
5. **Advanced Filters** - Egg groups, evolution stage, legendary status, etc.

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
