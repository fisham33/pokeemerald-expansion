# Pokemon Trainer Tools V2 - Complete Rebuild Prompt

## Task Overview

You are tasked with building a **modular, extensible Pokemon filtering and data management application** optimized for GitHub Pages deployment. This is a complete rewrite (V2) of an existing toolset with the following goals:

1. **Eliminate code duplication** - Share core logic across all interfaces
2. **Enable extensibility** - Plugin system for community contributions
3. **Improve maintainability** - Clean architecture with clear separation of concerns
4. **Optimize for web** - Fast, static site hosted on GitHub Pages
5. **Automate deployment** - Build pipeline for data generation and publishing

---

## Context Files to Review

Before starting, review these files from the current V1 implementation to understand the data structures and business logic:

### **Required Files** (must review):
1. `tools/trainer_gen/pokemon_data.json` - Pokemon data structure (first 100 lines)
2. `tools/trainer_gen/move_data.json` - Move data structure (first 100 lines)
3. `tools/trainer_gen/web/filter.js` - Current filtering logic (lines 103-157)
4. `tools/trainer_gen/web/index.html` - Current UI structure
5. `tools/trainer_gen/web/styles.css` - Current styling and theme

### **Optional Files** (for deeper understanding):
6. `tools/trainer_gen/extract_pokemon_data.py` - How Pokemon data is extracted
7. `tools/trainer_gen/filter_pokemon.py` - CLI filter implementation
8. `tools/trainer_gen/README.md` - Overview of all tools

---

## Project Structure

Create this exact directory structure:

```
pokemon-tools-v2/
├── core/                           # Shared core library (pure JavaScript)
│   ├── data/
│   │   ├── loaders/
│   │   │   ├── base-loader.js
│   │   │   ├── json-loader.js
│   │   │   └── cached-loader.js
│   │   ├── models/
│   │   │   ├── pokemon.js
│   │   │   └── move.js
│   │   └── stores/
│   │       ├── pokemon-store.js
│   │       └── filter-store.js
│   ├── filters/
│   │   ├── base-filter.js
│   │   ├── generation-filter.js
│   │   ├── type-filter.js
│   │   ├── ability-filter.js
│   │   ├── stat-filter.js
│   │   ├── bst-filter.js
│   │   └── filter-registry.js
│   ├── services/
│   │   ├── pokemon-service.js
│   │   ├── filter-service.js
│   │   └── export-service.js
│   └── utils/
│       ├── fuzzy-match.js
│       ├── validators.js
│       └── logger.js
│
├── web/                            # GitHub Pages application
│   ├── src/
│   │   ├── components/
│   │   │   ├── filters/
│   │   │   │   ├── FilterPanel.js
│   │   │   │   ├── GenerationFilter.js
│   │   │   │   ├── TypeFilter.js
│   │   │   │   ├── AbilityFilter.js
│   │   │   │   └── StatFilter.js
│   │   │   ├── results/
│   │   │   │   ├── PokemonCard.js
│   │   │   │   ├── PokemonList.js
│   │   │   │   └── ResultsHeader.js
│   │   │   └── shared/
│   │   │       ├── TypeBadge.js
│   │   │       ├── StatBar.js
│   │   │       └── LoadingSpinner.js
│   │   ├── views/
│   │   │   ├── FilterView.js
│   │   │   ├── CompareView.js
│   │   │   └── QueryView.js
│   │   ├── app.js
│   │   ├── router.js
│   │   └── config.js
│   ├── public/
│   │   ├── data/
│   │   │   ├── pokemon.json
│   │   │   └── moves.json
│   │   ├── styles/
│   │   │   ├── main.css
│   │   │   ├── components.css
│   │   │   └── themes.css
│   │   └── assets/
│   ├── index.html
│   └── README.md
│
├── plugins/                        # Example plugins
│   ├── filters/
│   │   └── evolution-stage-filter.js
│   └── README.md
│
├── build/                          # Build scripts
│   ├── generate-data.js
│   ├── optimize.js
│   └── deploy.sh
│
├── tests/                          # Test suite
│   ├── core/
│   │   ├── filters.test.js
│   │   └── services.test.js
│   └── web/
│       └── components.test.js
│
├── package.json
├── .gitignore
└── README.md
```

---

## Implementation Instructions

Build the application in this exact order:

### **Phase 1: Core Library** (Build First)

#### Step 1.1: Base Filter System

Create `core/filters/base-filter.js`:

```javascript
/**
 * Base class for all filters
 * All custom filters must extend this class
 */
export class BaseFilter {
  constructor(config) {
    this.name = config.name;           // Unique identifier (e.g., 'generation')
    this.type = config.type;           // UI type: 'number', 'select', 'multi-select', 'range', 'text'
    this.label = config.label;         // Display label (e.g., 'Generation')
    this.options = config.options;     // For select types
    this.placeholder = config.placeholder;
  }

  /**
   * Apply the filter to a Pokemon
   * @param {Object} pokemon - Pokemon object to test
   * @param {any} value - Filter value from user input
   * @returns {boolean} - True if Pokemon passes the filter
   */
  apply(pokemon, value) {
    throw new Error('apply() must be implemented by subclass');
  }

  /**
   * Validate user input
   * @param {any} value - Value to validate
   * @returns {boolean} - True if valid
   */
  validate(value) {
    return true; // Override if validation needed
  }

  /**
   * Get filter configuration for UI rendering
   * @returns {Object} - Filter configuration
   */
  getConfig() {
    return {
      name: this.name,
      type: this.type,
      label: this.label,
      options: this.options,
      placeholder: this.placeholder
    };
  }
}
```

#### Step 1.2: Implement Concrete Filters

Create `core/filters/generation-filter.js`:

```javascript
import { BaseFilter } from './base-filter.js';

export class GenerationFilter extends BaseFilter {
  constructor() {
    super({
      name: 'generation',
      type: 'number',
      label: 'Generation',
      placeholder: '1-9'
    });
  }

  apply(pokemon, generation) {
    if (!generation) return true;
    return pokemon.generation === parseInt(generation);
  }

  validate(value) {
    const gen = parseInt(value);
    return gen >= 1 && gen <= 9;
  }
}
```

Create `core/filters/type-filter.js`:

```javascript
import { BaseFilter } from './base-filter.js';

export class TypeFilter extends BaseFilter {
  constructor() {
    super({
      name: 'types',
      type: 'multi-select',
      label: 'Type(s)',
      options: [
        'Normal', 'Fire', 'Water', 'Electric',
        'Grass', 'Ice', 'Fighting', 'Poison',
        'Ground', 'Flying', 'Psychic', 'Bug',
        'Rock', 'Ghost', 'Dragon', 'Dark',
        'Steel', 'Fairy'
      ],
      placeholder: 'e.g., Fire, Dragon'
    });
  }

  apply(pokemon, selectedTypes) {
    if (!selectedTypes || selectedTypes.length === 0) {
      return true;
    }

    // Pokemon passes if it has ANY of the selected types
    return pokemon.types.some(type =>
      selectedTypes.includes(type)
    );
  }

  validate(value) {
    if (!Array.isArray(value)) return false;
    return value.every(type => this.options.includes(type));
  }
}
```

Create `core/filters/ability-filter.js`:

```javascript
import { BaseFilter } from './base-filter.js';

export class AbilityFilter extends BaseFilter {
  constructor() {
    super({
      name: 'ability',
      type: 'text',
      label: 'Ability',
      placeholder: 'e.g., Intimidate (partial match)'
    });
  }

  apply(pokemon, searchText) {
    if (!searchText || !searchText.trim()) {
      return true;
    }

    const search = searchText.toLowerCase();

    // Check normal abilities
    const hasNormalAbility = pokemon.abilities.some(ability =>
      ability.toLowerCase().includes(search)
    );

    // Check hidden ability
    const hasHiddenAbility = pokemon.hiddenAbility &&
      pokemon.hiddenAbility.toLowerCase().includes(search);

    return hasNormalAbility || hasHiddenAbility;
  }
}
```

Create `core/filters/stat-filter.js`:

```javascript
import { BaseFilter } from './base-filter.js';

export class StatFilter extends BaseFilter {
  constructor(statName) {
    super({
      name: statName.toLowerCase(),
      type: 'range',
      label: statName,
      placeholder: 'Min - Max'
    });
    this.statName = statName.toLowerCase();
  }

  apply(pokemon, range) {
    if (!range || (!range.min && !range.max)) {
      return true;
    }

    const statValue = pokemon.baseStats[this.statName];

    if (range.min && statValue < range.min) return false;
    if (range.max && statValue > range.max) return false;

    return true;
  }

  validate(value) {
    if (!value) return true;
    if (value.min && value.min < 0) return false;
    if (value.max && value.max < 0) return false;
    if (value.min && value.max && value.min > value.max) return false;
    return true;
  }
}
```

Create `core/filters/bst-filter.js`:

```javascript
import { BaseFilter } from './base-filter.js';

export class BSTFilter extends BaseFilter {
  constructor() {
    super({
      name: 'bst',
      type: 'range',
      label: 'Base Stat Total',
      placeholder: 'Min - Max'
    });
  }

  apply(pokemon, range) {
    if (!range || (!range.min && !range.max)) {
      return true;
    }

    if (range.min && pokemon.bst < range.min) return false;
    if (range.max && pokemon.bst > range.max) return false;

    return true;
  }

  validate(value) {
    if (!value) return true;
    if (value.min && value.min < 0) return false;
    if (value.max && value.max > 720) return false; // Max possible BST
    if (value.min && value.max && value.min > value.max) return false;
    return true;
  }
}
```

#### Step 1.3: Filter Registry

Create `core/filters/filter-registry.js`:

```javascript
import { BaseFilter } from './base-filter.js';
import { GenerationFilter } from './generation-filter.js';
import { TypeFilter } from './type-filter.js';
import { AbilityFilter } from './ability-filter.js';
import { StatFilter } from './stat-filter.js';
import { BSTFilter } from './bst-filter.js';

/**
 * Central registry for all filters
 * Supports dynamic filter registration for plugins
 */
export class FilterRegistry {
  static filters = new Map();
  static initialized = false;

  /**
   * Initialize with built-in filters
   */
  static init() {
    if (this.initialized) return;

    // Register built-in filters
    this.register(new GenerationFilter());
    this.register(new TypeFilter());
    this.register(new AbilityFilter());
    this.register(new BSTFilter());

    // Register individual stat filters
    this.register(new StatFilter('hp'));
    this.register(new StatFilter('atk'));
    this.register(new StatFilter('def'));
    this.register(new StatFilter('spa'));
    this.register(new StatFilter('spd'));
    this.register(new StatFilter('spe'));

    this.initialized = true;
  }

  /**
   * Register a filter
   * @param {BaseFilter} filter - Filter instance
   */
  static register(filter) {
    if (!(filter instanceof BaseFilter)) {
      throw new Error('Filter must extend BaseFilter');
    }

    if (this.filters.has(filter.name)) {
      console.warn(`Filter '${filter.name}' already registered, overwriting`);
    }

    this.filters.set(filter.name, filter);
  }

  /**
   * Get a filter by name
   * @param {string} name - Filter name
   * @returns {BaseFilter|undefined}
   */
  static get(name) {
    return this.filters.get(name);
  }

  /**
   * Get all registered filters
   * @returns {BaseFilter[]}
   */
  static getAll() {
    return Array.from(this.filters.values());
  }

  /**
   * Get all filter names
   * @returns {string[]}
   */
  static getNames() {
    return Array.from(this.filters.keys());
  }

  /**
   * Remove a filter
   * @param {string} name - Filter name
   */
  static unregister(name) {
    this.filters.delete(name);
  }

  /**
   * Clear all filters
   */
  static clear() {
    this.filters.clear();
    this.initialized = false;
  }
}
```

#### Step 1.4: Data Loaders

Create `core/data/loaders/base-loader.js`:

```javascript
/**
 * Base class for data loaders
 */
export class BaseLoader {
  async load(source) {
    throw new Error('load() must be implemented by subclass');
  }
}
```

Create `core/data/loaders/json-loader.js`:

```javascript
import { BaseLoader } from './base-loader.js';

/**
 * Load data from JSON files
 */
export class JSONLoader extends BaseLoader {
  async load(url) {
    try {
      const response = await fetch(url);

      if (!response.ok) {
        throw new Error(`HTTP ${response.status}: ${response.statusText}`);
      }

      const data = await response.json();
      return data;
    } catch (error) {
      console.error(`Failed to load ${url}:`, error);
      throw error;
    }
  }
}
```

Create `core/data/loaders/cached-loader.js`:

```javascript
import { BaseLoader } from './base-loader.js';

/**
 * Wrapper loader that caches results
 */
export class CachedLoader extends BaseLoader {
  constructor(loader, ttl = 3600000) { // 1 hour default
    super();
    this.loader = loader;
    this.ttl = ttl;
    this.cache = new Map();
  }

  async load(source) {
    const cached = this.cache.get(source);

    // Return cached data if still valid
    if (cached && Date.now() - cached.timestamp < this.ttl) {
      console.log(`Cache hit: ${source}`);
      return cached.data;
    }

    // Load fresh data
    console.log(`Cache miss: ${source}`);
    const data = await this.loader.load(source);

    // Store in cache
    this.cache.set(source, {
      data,
      timestamp: Date.now()
    });

    return data;
  }

  /**
   * Clear cache
   */
  clear() {
    this.cache.clear();
  }

  /**
   * Clear specific cached item
   */
  clearItem(source) {
    this.cache.delete(source);
  }
}
```

#### Step 1.5: Services

Create `core/services/pokemon-service.js`:

```javascript
/**
 * Service for Pokemon data management
 */
export class PokemonService {
  constructor(loader) {
    this.loader = loader;
    this.pokemon = [];
    this.loaded = false;
  }

  /**
   * Initialize - load Pokemon data
   */
  async initialize(url) {
    if (this.loaded) {
      console.log('Pokemon data already loaded');
      return;
    }

    const data = await this.loader.load(url);
    this.pokemon = data.pokemon || data; // Handle different formats

    console.log(`Loaded ${this.pokemon.length} Pokemon`);
    this.loaded = true;
  }

  /**
   * Get all Pokemon
   */
  getAll() {
    return [...this.pokemon];
  }

  /**
   * Get Pokemon by national dex number
   */
  getByDexNum(num) {
    return this.pokemon.find(p => p.natDexNum === num);
  }

  /**
   * Get Pokemon by species constant
   */
  getBySpecies(species) {
    return this.pokemon.find(p => p.species === species);
  }

  /**
   * Search Pokemon by name (fuzzy)
   */
  search(query) {
    if (!query) return this.pokemon;

    const normalized = query.toLowerCase();
    return this.pokemon.filter(p =>
      p.name.toLowerCase().includes(normalized) ||
      p.species.toLowerCase().includes(normalized)
    );
  }

  /**
   * Get count
   */
  getCount() {
    return this.pokemon.length;
  }
}
```

Create `core/services/filter-service.js`:

```javascript
import { FilterRegistry } from '../filters/filter-registry.js';

/**
 * Service for filtering Pokemon
 */
export class FilterService {
  constructor() {
    FilterRegistry.init();
  }

  /**
   * Apply filters to Pokemon array
   * @param {Object[]} pokemon - Array of Pokemon
   * @param {Object} filterValues - Object with filter values {filterName: value}
   * @returns {Object[]} - Filtered Pokemon
   */
  apply(pokemon, filterValues) {
    return pokemon.filter(p => {
      // Test each filter
      for (const [filterName, value] of Object.entries(filterValues)) {
        const filter = FilterRegistry.get(filterName);

        if (!filter) {
          console.warn(`Unknown filter: ${filterName}`);
          continue;
        }

        // Skip empty/null values
        if (value === null || value === undefined || value === '') {
          continue;
        }

        // Validate
        if (!filter.validate(value)) {
          console.warn(`Invalid value for ${filterName}:`, value);
          continue;
        }

        // Apply filter
        if (!filter.apply(p, value)) {
          return false; // Pokemon doesn't match this filter
        }
      }

      return true; // Pokemon passed all filters
    });
  }

  /**
   * Get all available filters
   */
  getAvailableFilters() {
    return FilterRegistry.getAll();
  }

  /**
   * Get filter by name
   */
  getFilter(name) {
    return FilterRegistry.get(name);
  }
}
```

---

### **Phase 2: Web Application** (Build Second)

#### Step 2.1: Configuration

Create `web/src/config.js`:

```javascript
/**
 * Application configuration
 */
export const config = {
  // Data sources
  data: {
    sources: {
      pokemon: '/data/pokemon.json',
      moves: '/data/moves.json'
    },
    cache: {
      enabled: true,
      ttl: 3600000 // 1 hour
    }
  },

  // UI settings
  ui: {
    theme: 'purple-gradient',
    resultsPerPage: 50,
    enableAnimations: true,
    typeColors: {
      normal: '#A8A878',
      fire: '#F08030',
      water: '#6890F0',
      electric: '#F8D030',
      grass: '#78C850',
      ice: '#98D8D8',
      fighting: '#C03028',
      poison: '#A040A0',
      ground: '#E0C068',
      flying: '#A890F0',
      psychic: '#F85888',
      bug: '#A8B820',
      rock: '#B8A038',
      ghost: '#705898',
      dragon: '#7038F8',
      dark: '#705848',
      steel: '#B8B8D0',
      fairy: '#EE99AC'
    }
  },

  // Feature flags
  features: {
    comparison: false,   // Coming soon
    export: false,       // Coming soon
    teamBuilder: false   // Coming soon
  }
};
```

#### Step 2.2: Main Application

Create `web/src/app.js`:

```javascript
import { JSONLoader } from '../../core/data/loaders/json-loader.js';
import { CachedLoader } from '../../core/data/loaders/cached-loader.js';
import { PokemonService } from '../../core/services/pokemon-service.js';
import { FilterService } from '../../core/services/filter-service.js';
import { FilterView } from './views/FilterView.js';
import { config } from './config.js';

/**
 * Main application class
 */
class App {
  constructor() {
    this.pokemonService = null;
    this.filterService = null;
    this.currentView = null;
  }

  /**
   * Initialize the application
   */
  async init() {
    console.log('Initializing Pokemon Tools V2...');

    try {
      // Show loading
      this.showLoading();

      // Initialize data loader
      const loader = config.data.cache.enabled
        ? new CachedLoader(new JSONLoader(), config.data.cache.ttl)
        : new JSONLoader();

      // Initialize services
      this.pokemonService = new PokemonService(loader);
      this.filterService = new FilterService();

      // Load Pokemon data
      await this.pokemonService.initialize(config.data.sources.pokemon);

      // Initialize default view
      this.currentView = new FilterView({
        pokemonService: this.pokemonService,
        filterService: this.filterService
      });

      this.currentView.render();

      console.log('Application initialized successfully');
    } catch (error) {
      console.error('Failed to initialize application:', error);
      this.showError(error.message);
    }
  }

  showLoading() {
    document.getElementById('app').innerHTML = `
      <div class="loading">
        <div class="spinner"></div>
        <p>Loading Pokemon data...</p>
      </div>
    `;
  }

  showError(message) {
    document.getElementById('app').innerHTML = `
      <div class="error">
        <h2>Error</h2>
        <p>${message}</p>
        <button onclick="location.reload()">Retry</button>
      </div>
    `;
  }
}

// Initialize app when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
  const app = new App();
  app.init();
});
```

#### Step 2.3: Filter View

Create `web/src/views/FilterView.js`:

```javascript
import { FilterPanel } from '../components/filters/FilterPanel.js';
import { PokemonList } from '../components/results/PokemonList.js';
import { ResultsHeader } from '../components/results/ResultsHeader.js';

/**
 * Main filter view
 */
export class FilterView {
  constructor({ pokemonService, filterService }) {
    this.pokemonService = pokemonService;
    this.filterService = filterService;
    this.results = [];
  }

  render() {
    const container = document.getElementById('app');

    container.innerHTML = `
      <div class="container">
        <header>
          <h1>Pokemon Stat Filter</h1>
          <p class="subtitle">Filter Pokemon by generation, type, ability, and stats</p>
        </header>

        <div id="filter-panel"></div>
        <div id="results-container"></div>

        <footer>
          <p>Data from pokeemerald-expansion |
             <a href="https://github.com/fisham33/pokeemerald-expansion" target="_blank">GitHub</a>
          </p>
        </footer>
      </div>
    `;

    // Initialize components
    this.filterPanel = new FilterPanel(
      document.getElementById('filter-panel'),
      this.filterService
    );

    this.resultsHeader = new ResultsHeader(
      document.getElementById('results-container')
    );

    this.pokemonList = new PokemonList(
      document.getElementById('results-container')
    );

    // Wire up events
    this.filterPanel.onApply = (filterValues) => {
      this.applyFilters(filterValues);
    };

    this.filterPanel.onClear = () => {
      this.clearFilters();
    };

    this.filterPanel.onShowAll = () => {
      this.showAll();
    };

    // Render components
    this.filterPanel.render();
    this.showInitialMessage();
  }

  applyFilters(filterValues) {
    const allPokemon = this.pokemonService.getAll();
    this.results = this.filterService.apply(allPokemon, filterValues);

    this.resultsHeader.render(this.results.length);
    this.pokemonList.render(this.results);
  }

  clearFilters() {
    this.filterPanel.clear();
    this.showInitialMessage();
  }

  showAll() {
    this.results = this.pokemonService.getAll();
    this.resultsHeader.render(this.results.length);
    this.pokemonList.render(this.results);
  }

  showInitialMessage() {
    const container = document.getElementById('results-container');
    container.innerHTML = `
      <div class="placeholder">
        ✓ Loaded ${this.pokemonService.getCount()} Pokemon<br><br>
        Enter filter criteria and click "Filter" to see results
      </div>
    `;
  }
}
```

#### Step 2.4: Filter Panel Component

Create `web/src/components/filters/FilterPanel.js`:

```javascript
import { GenerationFilter } from '../../../core/filters/generation-filter.js';
import { TypeFilter } from '../../../core/filters/type-filter.js';
import { AbilityFilter } from '../../../core/filters/ability-filter.js';
import { BSTFilter } from '../../../core/filters/bst-filter.js';
import { StatFilter } from '../../../core/filters/stat-filter.js';

/**
 * Filter panel component
 */
export class FilterPanel {
  constructor(container, filterService) {
    this.container = container;
    this.filterService = filterService;
    this.onApply = null;
    this.onClear = null;
    this.onShowAll = null;
  }

  render() {
    this.container.innerHTML = `
      <div class="filters-container">
        <div class="filter-group">
          <label for="generation">Generation:</label>
          <input type="number" id="generation" min="1" max="9" placeholder="1-9">
        </div>

        <div class="filter-group">
          <label for="types">Type(s):</label>
          <input type="text" id="types" placeholder="e.g., Fire, Dragon">
          <span class="hint">Comma-separated</span>
        </div>

        <div class="filter-group">
          <label for="ability">Ability:</label>
          <input type="text" id="ability" placeholder="e.g., Intimidate">
          <span class="hint">Partial match</span>
        </div>

        <div class="filter-group">
          <label>BST Range:</label>
          <div class="range-inputs">
            <input type="number" id="minBst" placeholder="Min">
            <span>to</span>
            <input type="number" id="maxBst" placeholder="Max">
          </div>
        </div>

        <div class="stat-filters">
          <h3>Individual Stats</h3>
          <div class="stat-grid">
            ${this.renderStatFilters()}
          </div>
        </div>

        <div class="button-group">
          <button id="filterBtn" class="btn btn-primary">Filter</button>
          <button id="clearBtn" class="btn btn-secondary">Clear</button>
          <button id="showAllBtn" class="btn btn-secondary">Show All</button>
        </div>
      </div>
    `;

    this.attachEvents();
  }

  renderStatFilters() {
    const stats = ['HP', 'Attack', 'Defense', 'Sp. Atk', 'Sp. Def', 'Speed'];
    const statKeys = ['hp', 'atk', 'def', 'spa', 'spd', 'spe'];

    return stats.map((stat, i) => `
      <div class="stat-filter">
        <label>${stat}:</label>
        <input type="number" id="min${statKeys[i]}" placeholder="Min">
        <span>-</span>
        <input type="number" id="max${statKeys[i]}" placeholder="Max">
      </div>
    `).join('');
  }

  attachEvents() {
    document.getElementById('filterBtn').addEventListener('click', () => {
      if (this.onApply) {
        this.onApply(this.getFilterValues());
      }
    });

    document.getElementById('clearBtn').addEventListener('click', () => {
      if (this.onClear) {
        this.onClear();
      }
    });

    document.getElementById('showAllBtn').addEventListener('click', () => {
      if (this.onShowAll) {
        this.onShowAll();
      }
    });

    // Enter key triggers filter
    this.container.querySelectorAll('input').forEach(input => {
      input.addEventListener('keypress', (e) => {
        if (e.key === 'Enter' && this.onApply) {
          this.onApply(this.getFilterValues());
        }
      });
    });
  }

  getFilterValues() {
    const values = {};

    // Generation
    const gen = document.getElementById('generation').value;
    if (gen) values.generation = parseInt(gen);

    // Types
    const typesStr = document.getElementById('types').value.trim();
    if (typesStr) {
      values.types = typesStr.split(',').map(t => t.trim());
    }

    // Ability
    const ability = document.getElementById('ability').value.trim();
    if (ability) values.ability = ability;

    // BST
    const minBst = document.getElementById('minBst').value;
    const maxBst = document.getElementById('maxBst').value;
    if (minBst || maxBst) {
      values.bst = {
        min: minBst ? parseInt(minBst) : null,
        max: maxBst ? parseInt(maxBst) : null
      };
    }

    // Individual stats
    const stats = ['hp', 'atk', 'def', 'spa', 'spd', 'spe'];
    stats.forEach(stat => {
      const min = document.getElementById(`min${stat}`).value;
      const max = document.getElementById(`max${stat}`).value;
      if (min || max) {
        values[stat] = {
          min: min ? parseInt(min) : null,
          max: max ? parseInt(max) : null
        };
      }
    });

    return values;
  }

  clear() {
    this.container.querySelectorAll('input').forEach(input => {
      input.value = '';
    });
  }
}
```

#### Step 2.5: Results Components

Create `web/src/components/results/ResultsHeader.js`:

```javascript
export class ResultsHeader {
  constructor(container) {
    this.container = container;
  }

  render(count) {
    const existing = this.container.querySelector('.results-header');
    if (existing) {
      existing.querySelector('.count').textContent = `${count} Pokemon`;
    } else {
      const header = document.createElement('div');
      header.className = 'results-header';
      header.innerHTML = `
        <h2>Results</h2>
        <span class="count">${count} Pokemon</span>
      `;
      this.container.prepend(header);
    }
  }
}
```

Create `web/src/components/results/PokemonList.js`:

```javascript
import { PokemonCard } from './PokemonCard.js';

export class PokemonList {
  constructor(container) {
    this.container = container;
  }

  render(pokemon) {
    // Remove existing list
    const existing = this.container.querySelector('.results-list');
    if (existing) {
      existing.remove();
    }

    if (pokemon.length === 0) {
      const placeholder = document.createElement('div');
      placeholder.className = 'placeholder';
      placeholder.textContent = 'No Pokemon found matching the criteria.';
      this.container.appendChild(placeholder);
      return;
    }

    // Create results list
    const list = document.createElement('div');
    list.className = 'results-list';

    pokemon.forEach(p => {
      const card = new PokemonCard(p);
      list.appendChild(card.render());
    });

    this.container.appendChild(list);
  }
}
```

Create `web/src/components/results/PokemonCard.js`:

```javascript
import { config } from '../../config.js';

export class PokemonCard {
  constructor(pokemon) {
    this.pokemon = pokemon;
  }

  render() {
    const card = document.createElement('div');
    card.className = 'pokemon-card';

    card.innerHTML = `
      <div class="pokemon-header">
        <div>
          <div class="pokemon-name">${this.pokemon.name}</div>
          <div class="pokemon-species">${this.pokemon.species}</div>
        </div>
      </div>

      <div class="pokemon-info">
        <div class="info-item">
          <span class="info-label">Gen:</span>
          <span class="info-value">${this.pokemon.generation}</span>
        </div>
        <div class="info-item">
          <span class="info-label">Types:</span>
          <div class="types">${this.renderTypes()}</div>
        </div>
        <div class="info-item">
          <span class="info-label">BST:</span>
          <span class="info-value">${this.pokemon.bst}</span>
        </div>
      </div>

      <div class="stat-bar-container">
        ${this.renderStats()}
      </div>

      <div class="abilities">
        <span class="abilities-label">Abilities:</span>
        ${this.renderAbilities()}
      </div>
    `;

    return card;
  }

  renderTypes() {
    return this.pokemon.types.map(type => `
      <span class="type-badge type-${type.toLowerCase()}">${type}</span>
    `).join('');
  }

  renderStats() {
    const stats = this.pokemon.baseStats;
    return ['HP', 'ATK', 'DEF', 'SPA', 'SPD', 'SPE'].map((name, i) => {
      const key = ['hp', 'atk', 'def', 'spa', 'spd', 'spe'][i];
      return `
        <div class="stat-item">
          <div class="stat-name">${name}</div>
          <div class="stat-value">${stats[key] || 0}</div>
        </div>
      `;
    }).join('');
  }

  renderAbilities() {
    const abilities = this.pokemon.abilities.map(a => `
      <span class="ability">${a}</span>
    `).join('');

    const hidden = this.pokemon.hiddenAbility ? `
      <span class="ability hidden">Hidden: ${this.pokemon.hiddenAbility}</span>
    ` : '';

    return abilities + hidden;
  }
}
```

#### Step 2.6: HTML Entry Point

Create `web/index.html`:

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Pokemon Stat Filter V2</title>
  <link rel="stylesheet" href="public/styles/main.css">
  <link rel="stylesheet" href="public/styles/components.css">
</head>
<body>
  <div id="app">
    <!-- App renders here -->
  </div>

  <script type="module" src="src/app.js"></script>
</body>
</html>
```

#### Step 2.7: Styles

Create `web/public/styles/main.css`:

```css
/* Copy exact styles from existing web/styles.css */
/* Use the purple gradient theme (#667eea to #764ba2) */
/* Include all type colors */
/* Include responsive breakpoints */

/* Key requirements:
   - Purple gradient background
   - White container with shadow
   - Type badge colors for all 18 types
   - Responsive grid layouts
   - Smooth transitions
   - Custom scrollbar
*/

/* See current implementation at tools/trainer_gen/web/styles.css */
```

---

### **Phase 3: Plugin System** (Build Third)

Create `plugins/filters/evolution-stage-filter.js`:

```javascript
import { BaseFilter } from '../../core/filters/base-filter.js';
import { FilterRegistry } from '../../core/filters/filter-registry.js';

/**
 * Example plugin: Filter by evolution stage
 */
export class EvolutionStageFilter extends BaseFilter {
  constructor() {
    super({
      name: 'evolutionStage',
      type: 'select',
      label: 'Evolution Stage',
      options: ['Base', 'Stage 1', 'Stage 2']
    });
  }

  apply(pokemon, stage) {
    if (!stage) return true;

    // This would require family evolution data
    // For now, just return true
    // In a real implementation, analyze pokemon.family
    return true;
  }
}

// Auto-register when loaded
FilterRegistry.register(new EvolutionStageFilter());
```

---

### **Phase 4: Build System** (Build Fourth)

Create `build/generate-data.sh`:

```bash
#!/bin/bash
# Generate pokemon_data.json and move_data.json from C source files

echo "Generating Pokemon data from C source files..."

cd ../tools/trainer_gen

# Run existing Python extractors
python3 extract_pokemon_data.py
python3 extract_move_data.py

echo "Copying data to web/public/data/"

# Copy to web application
cp pokemon_data.json ../../pokemon-tools-v2/web/public/data/pokemon.json
cp move_data.json ../../pokemon-tools-v2/web/public/data/moves.json

echo "✓ Data generation complete!"
```

Create `build/deploy.sh`:

```bash
#!/bin/bash
# Deploy to GitHub Pages

echo "Building for production..."

# Generate data
./generate-data.sh

# TODO: Minify JavaScript
# TODO: Optimize assets

echo "Ready for GitHub Pages deployment!"
echo "Commit and push the web/ directory to your gh-pages branch"
```

---

### **Phase 5: Documentation** (Build Last)

Create `README.md`:

```markdown
# Pokemon Tools V2

Modular, extensible Pokemon filtering and data management for pokeemerald-expansion.

## Features

- ✅ Filter 1000+ Pokemon by stats, types, abilities
- ✅ Plugin system for custom filters
- ✅ GitHub Pages ready
- ✅ No dependencies, pure JavaScript
- ✅ Responsive design

## Quick Start

### Local Development

1. Generate data:
   ```bash
   cd build
   ./generate-data.sh
   ```

2. Start local server:
   ```bash
   cd web
   python3 -m http.server 8000
   ```

3. Open http://localhost:8000

### Adding Custom Filters

See `plugins/filters/evolution-stage-filter.js` for example.

## Architecture

- `core/` - Shared library (filters, services, loaders)
- `web/` - GitHub Pages application
- `plugins/` - Community extensions
- `build/` - Build scripts

## License

MIT
```

---

## Testing Requirements

Create `tests/core/filters.test.js`:

```javascript
import { TypeFilter } from '../../core/filters/type-filter.js';
import { GenerationFilter } from '../../core/filters/generation-filter.js';

describe('TypeFilter', () => {
  const filter = new TypeFilter();

  test('filters Fire types', () => {
    const pokemon = { types: ['Fire', 'Flying'] };
    expect(filter.apply(pokemon, ['Fire'])).toBe(true);
  });

  test('returns true for empty filter', () => {
    const pokemon = { types: ['Water'] };
    expect(filter.apply(pokemon, [])).toBe(true);
  });
});

describe('GenerationFilter', () => {
  const filter = new GenerationFilter();

  test('filters Gen 9', () => {
    const pokemon = { generation: 9 };
    expect(filter.apply(pokemon, 9)).toBe(true);
    expect(filter.apply(pokemon, 1)).toBe(false);
  });
});
```

---

## Deployment to GitHub Pages

1. Build the application:
   ```bash
   cd build
   ./generate-data.sh
   ```

2. Copy `web/` directory to your repository

3. Enable GitHub Pages in repository settings:
   - Source: Branch `main`
   - Folder: `/web`

4. Your site will be at: `https://username.github.io/repo-name/`

---

## Success Criteria

The V2 implementation is complete when:

✅ All Phase 1 core modules work independently
✅ Filter system supports plugins
✅ Web app loads and filters 1082 Pokemon correctly
✅ All test cases pass
✅ Data can be generated from C files
✅ Application runs on GitHub Pages
✅ Example plugin demonstrates extensibility
✅ Code has no duplication between CLI/GUI/web
✅ Documentation is complete

---

## Key Differences from V1

| V1 | V2 |
|----|-----|
| Duplicated filter logic | Shared core library |
| Monolithic scripts | Modular components |
| Hard to extend | Plugin system |
| Manual deployment | Automated build |
| No tests | Comprehensive tests |
| Tightly coupled | Clean separation |

---

## Next Steps After V2

1. Add team builder feature
2. Add Pokemon comparison view
3. Add export functionality
4. Add move query interface
5. Create CLI using same core library
6. Build desktop app using Electron + core library

