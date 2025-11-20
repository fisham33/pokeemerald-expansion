# Pokemon Trainer Tools - Architecture V2 (Modular & Extensible)

## Overview

Redesigned architecture for a GitHub Pages-hosted application with modularity, extensibility, and maintainability as core principles.

---

## Current Architecture Problems

### 1. **Code Duplication**
- Filtering logic duplicated across CLI, GUI, and web versions
- Pokemon data parsing logic not reusable
- Each interface reimplements the same business logic

### 2. **Tight Coupling**
- Data extraction directly coupled to C file parsing
- UI tightly coupled to data structures
- No abstraction layers between components

### 3. **Hard to Extend**
- Adding new filters requires changes in 3+ places
- Adding new data sources requires rewriting parsers
- No plugin system for community extensions

### 4. **Monolithic Scripts**
- Each script is 400-800 lines doing everything
- Hard to test individual components
- Difficult to maintain and debug

---

## V2 Architecture: Modular Design

```
pokemon-tools/
├── core/                           # Shared core library
│   ├── data/
│   │   ├── loaders/               # Data source adapters
│   │   │   ├── base.js            # Base loader interface
│   │   │   ├── json-loader.js     # Load from JSON files
│   │   │   ├── api-loader.js      # Load from REST API
│   │   │   └── cache-loader.js    # Cached loader wrapper
│   │   ├── models/                # Data models
│   │   │   ├── pokemon.js         # Pokemon model with validation
│   │   │   ├── move.js            # Move model
│   │   │   └── moveset.js         # Moveset model
│   │   └── stores/                # Data stores (state management)
│   │       ├── pokemon-store.js   # Pokemon data store
│   │       └── filter-store.js    # Filter state store
│   ├── filters/                   # Filter system
│   │   ├── base-filter.js         # Base filter class
│   │   ├── generation-filter.js   # Generation filter
│   │   ├── type-filter.js         # Type filter
│   │   ├── ability-filter.js      # Ability filter
│   │   ├── stat-filter.js         # Stat range filter
│   │   └── filter-registry.js     # Plugin registry for filters
│   ├── parsers/                   # Data parsers
│   │   ├── c-parser.js            # C file parser
│   │   ├── showdown-parser.js     # Smogon data parser
│   │   └── parser-utils.js        # Shared utilities
│   ├── exporters/                 # Data exporters
│   │   ├── json-exporter.js       # Export to JSON
│   │   ├── party-exporter.js      # Export to trainers.party
│   │   └── csv-exporter.js        # Export to CSV
│   └── utils/                     # Utilities
│       ├── fuzzy-match.js         # Fuzzy name matching
│       ├── validators.js          # Data validation
│       └── logger.js              # Logging utility
│
├── web/                           # Web application (GitHub Pages)
│   ├── src/
│   │   ├── components/           # UI components
│   │   │   ├── filters/
│   │   │   │   ├── FilterPanel.js
│   │   │   │   ├── GenerationFilter.js
│   │   │   │   ├── TypeFilter.js
│   │   │   │   └── StatFilter.js
│   │   │   ├── results/
│   │   │   │   ├── PokemonCard.js
│   │   │   │   ├── PokemonList.js
│   │   │   │   └── ResultsHeader.js
│   │   │   └── layout/
│   │   │       ├── Header.js
│   │   │       ├── Sidebar.js
│   │   │       └── Footer.js
│   │   ├── views/                # Page views
│   │   │   ├── FilterView.js     # Pokemon filter page
│   │   │   ├── QueryView.js      # Move query page
│   │   │   ├── CompareView.js    # Compare Pokemon
│   │   │   └── ExportView.js     # Export data page
│   │   ├── services/             # Business logic
│   │   │   ├── pokemon-service.js
│   │   │   ├── filter-service.js
│   │   │   └── export-service.js
│   │   ├── app.js                # Main application
│   │   └── config.js             # Configuration
│   ├── public/
│   │   ├── data/
│   │   │   ├── pokemon.json
│   │   │   └── moves.json
│   │   └── assets/
│   ├── index.html
│   └── package.json
│
├── cli/                          # Command-line tools
│   ├── commands/
│   │   ├── extract.js           # Extract data command
│   │   ├── convert.js           # Convert command
│   │   ├── filter.js            # Filter command
│   │   └── query.js             # Query command
│   ├── cli.js                   # CLI entry point
│   └── package.json
│
├── plugins/                      # Plugin system
│   ├── examples/
│   │   ├── custom-filter/       # Example custom filter
│   │   └── custom-exporter/     # Example custom exporter
│   └── README.md
│
├── build/                        # Build system
│   ├── generate-data.js         # Generate JSON from C files
│   ├── optimize.js              # Optimize for production
│   └── deploy.js                # Deploy to GitHub Pages
│
└── tests/                        # Tests
    ├── core/
    ├── web/
    └── cli/
```

---

## Core Principles

### 1. **Separation of Concerns**

```javascript
// Data Layer - Handles data loading and storage
class PokemonDataLoader {
  async load(source) { /* ... */ }
}

// Business Logic Layer - Handles filtering, validation
class PokemonFilterService {
  filter(pokemon, filters) { /* ... */ }
}

// Presentation Layer - Handles UI rendering
class PokemonCard {
  render(pokemon) { /* ... */ }
}
```

### 2. **Plugin Architecture**

```javascript
// Base Filter Interface
class BaseFilter {
  constructor(config) {
    this.name = config.name;
    this.type = config.type;
  }

  // Must be implemented by subclasses
  apply(pokemon, value) {
    throw new Error('Not implemented');
  }

  // Optional: validation
  validate(value) {
    return true;
  }
}

// Custom Filter Plugin
class ShinyFilter extends BaseFilter {
  constructor() {
    super({ name: 'Shiny', type: 'boolean' });
  }

  apply(pokemon, value) {
    return value ? pokemon.hasShinyForm : true;
  }
}

// Register plugin
FilterRegistry.register(new ShinyFilter());
```

### 3. **Configuration-Driven**

```javascript
// config.js - Single source of truth
export default {
  data: {
    sources: {
      pokemon: '/data/pokemon.json',
      moves: '/data/moves.json',
      smogon: 'https://pkmn.github.io/randbats/data/'
    },
    cache: {
      enabled: true,
      ttl: 3600000 // 1 hour
    }
  },

  filters: {
    enabled: [
      'generation', 'type', 'ability',
      'bst', 'stats', 'egg-group'
    ],
    defaults: {
      generation: null,
      types: []
    }
  },

  ui: {
    theme: 'purple-gradient',
    resultsPerPage: 50,
    enableAnimations: true
  },

  features: {
    comparison: true,
    export: true,
    teamBuilder: false
  }
};
```

---

## Detailed Component Design

### 1. **Data Loading System**

```javascript
// core/data/loaders/base.js
export class BaseLoader {
  async load(source) {
    throw new Error('Must implement load()');
  }
}

// core/data/loaders/json-loader.js
export class JSONLoader extends BaseLoader {
  async load(url) {
    const response = await fetch(url);
    if (!response.ok) {
      throw new Error(`Failed to load: ${response.statusText}`);
    }
    return await response.json();
  }
}

// core/data/loaders/cache-loader.js
export class CachedLoader extends BaseLoader {
  constructor(loader, ttl = 3600000) {
    super();
    this.loader = loader;
    this.ttl = ttl;
    this.cache = new Map();
  }

  async load(source) {
    const cached = this.cache.get(source);
    if (cached && Date.now() - cached.timestamp < this.ttl) {
      return cached.data;
    }

    const data = await this.loader.load(source);
    this.cache.set(source, { data, timestamp: Date.now() });
    return data;
  }
}

// Usage
const loader = new CachedLoader(new JSONLoader());
const pokemon = await loader.load('/data/pokemon.json');
```

### 2. **Filter System**

```javascript
// core/filters/filter-registry.js
export class FilterRegistry {
  static filters = new Map();

  static register(filter) {
    if (!(filter instanceof BaseFilter)) {
      throw new Error('Must extend BaseFilter');
    }
    this.filters.set(filter.name, filter);
  }

  static get(name) {
    return this.filters.get(name);
  }

  static getAll() {
    return Array.from(this.filters.values());
  }
}

// core/filters/type-filter.js
export class TypeFilter extends BaseFilter {
  constructor() {
    super({
      name: 'type',
      type: 'multi-select',
      options: [
        'Normal', 'Fire', 'Water', 'Electric',
        'Grass', 'Ice', 'Fighting', 'Poison',
        'Ground', 'Flying', 'Psychic', 'Bug',
        'Rock', 'Ghost', 'Dragon', 'Dark',
        'Steel', 'Fairy'
      ]
    });
  }

  apply(pokemon, selectedTypes) {
    if (!selectedTypes || selectedTypes.length === 0) {
      return true;
    }

    return pokemon.types.some(type =>
      selectedTypes.includes(type)
    );
  }

  validate(value) {
    if (!Array.isArray(value)) return false;
    return value.every(type => this.options.includes(type));
  }
}

// Auto-register built-in filters
FilterRegistry.register(new GenerationFilter());
FilterRegistry.register(new TypeFilter());
FilterRegistry.register(new AbilityFilter());
FilterRegistry.register(new StatFilter());
```

### 3. **Service Layer**

```javascript
// web/src/services/pokemon-service.js
export class PokemonService {
  constructor(loader, filterService) {
    this.loader = loader;
    this.filterService = filterService;
    this.pokemon = [];
  }

  async initialize() {
    this.pokemon = await this.loader.load(config.data.sources.pokemon);
  }

  filter(filters) {
    return this.filterService.apply(this.pokemon, filters);
  }

  getById(id) {
    return this.pokemon.find(p => p.natDexNum === id);
  }

  search(query) {
    const normalized = query.toLowerCase();
    return this.pokemon.filter(p =>
      p.name.toLowerCase().includes(normalized) ||
      p.species.toLowerCase().includes(normalized)
    );
  }
}

// web/src/services/filter-service.js
export class FilterService {
  constructor() {
    this.filters = FilterRegistry.getAll();
  }

  apply(pokemon, filterValues) {
    return pokemon.filter(p => {
      return this.filters.every(filter => {
        const value = filterValues[filter.name];
        if (value === null || value === undefined) {
          return true; // Skip empty filters
        }

        if (!filter.validate(value)) {
          console.warn(`Invalid value for ${filter.name}:`, value);
          return true;
        }

        return filter.apply(p, value);
      });
    });
  }
}
```

### 4. **Component System**

```javascript
// web/src/components/filters/FilterPanel.js
export class FilterPanel {
  constructor(container, filterService) {
    this.container = container;
    this.filterService = filterService;
    this.values = {};
  }

  render() {
    const filters = FilterRegistry.getAll();

    this.container.innerHTML = `
      <div class="filter-panel">
        ${filters.map(filter => this.renderFilter(filter)).join('')}
        <div class="filter-actions">
          <button id="apply-btn">Filter</button>
          <button id="clear-btn">Clear</button>
        </div>
      </div>
    `;

    this.attachEvents();
  }

  renderFilter(filter) {
    switch (filter.type) {
      case 'number':
        return this.renderNumberFilter(filter);
      case 'multi-select':
        return this.renderMultiSelectFilter(filter);
      case 'text':
        return this.renderTextFilter(filter);
      default:
        return '';
    }
  }

  renderNumberFilter(filter) {
    return `
      <div class="filter-group">
        <label>${filter.name}</label>
        <input type="number"
               data-filter="${filter.name}"
               placeholder="Enter ${filter.name}">
      </div>
    `;
  }

  getValues() {
    return { ...this.values };
  }

  attachEvents() {
    document.getElementById('apply-btn').addEventListener('click', () => {
      this.onApply(this.getValues());
    });
  }

  onApply(values) {
    // Override in parent
  }
}
```

### 5. **State Management**

```javascript
// core/data/stores/filter-store.js
export class FilterStore {
  constructor() {
    this.state = {
      filters: {},
      results: [],
      loading: false,
      error: null
    };
    this.listeners = [];
  }

  subscribe(listener) {
    this.listeners.push(listener);
    return () => {
      this.listeners = this.listeners.filter(l => l !== listener);
    };
  }

  setState(updates) {
    this.state = { ...this.state, ...updates };
    this.notify();
  }

  notify() {
    this.listeners.forEach(listener => listener(this.state));
  }

  setFilters(filters) {
    this.setState({ filters });
  }

  setResults(results) {
    this.setState({ results, loading: false });
  }

  setError(error) {
    this.setState({ error, loading: false });
  }
}
```

---

## Build System for GitHub Pages

```javascript
// build/generate-data.js
import { CPars } from '../core/parsers/c-parser.js';
import { JSONExporter } from '../core/exporters/json-exporter.js';

export async function generateData() {
  console.log('Extracting Pokemon data from C files...');

  const parser = new CParser({
    sourceDir: '../../src/data/pokemon',
    generation: 9
  });

  const pokemon = await parser.parsePokemon();
  const moves = await parser.parseMoves();

  console.log(`Extracted ${pokemon.length} Pokemon`);
  console.log(`Extracted ${moves.length} moves`);

  const exporter = new JSONExporter({
    outputDir: '../web/public/data',
    pretty: false,
    minify: true
  });

  await exporter.export('pokemon.json', { pokemon });
  await exporter.export('moves.json', { moves });

  console.log('Data generation complete!');
}

// build/deploy.js
export async function deploy() {
  console.log('Building for production...');

  // Generate data
  await generateData();

  // Optimize assets
  await optimizeAssets();

  // Build web app
  await buildWebApp();

  console.log('Ready for GitHub Pages deployment!');
}
```

---

## Plugin System Example

```javascript
// plugins/examples/custom-filter/evolution-stage-filter.js
import { BaseFilter } from '../../../core/filters/base-filter.js';
import { FilterRegistry } from '../../../core/filters/filter-registry.js';

export class EvolutionStageFilter extends BaseFilter {
  constructor() {
    super({
      name: 'evolutionStage',
      type: 'select',
      label: 'Evolution Stage',
      options: ['Base', 'Stage 1', 'Stage 2', 'Mega']
    });
  }

  apply(pokemon, stage) {
    if (!stage) return true;

    // Logic to determine evolution stage
    const evolutionStage = this.getEvolutionStage(pokemon);
    return evolutionStage === stage;
  }

  getEvolutionStage(pokemon) {
    // Implement logic based on pokemon.family
    // This would need family evolution data
    return 'Base'; // Simplified
  }
}

// Register the plugin
FilterRegistry.register(new EvolutionStageFilter());
```

---

## Configuration for Different Environments

```javascript
// config/development.js
export default {
  data: {
    sources: {
      pokemon: 'http://localhost:8000/data/pokemon.json',
      moves: 'http://localhost:8000/data/moves.json'
    },
    cache: {
      enabled: false
    }
  },
  logging: {
    level: 'debug'
  }
};

// config/production.js
export default {
  data: {
    sources: {
      pokemon: '/data/pokemon.json',
      moves: '/data/moves.json'
    },
    cache: {
      enabled: true,
      ttl: 3600000
    }
  },
  logging: {
    level: 'error'
  }
};
```

---

## Benefits of V2 Architecture

### 1. **Modularity**
- Each component has a single responsibility
- Easy to test in isolation
- Can replace components without affecting others

### 2. **Extensibility**
- Plugin system allows community contributions
- New filters can be added without modifying core
- New data sources can be added via loader plugins

### 3. **Maintainability**
- Clear separation of concerns
- Configuration-driven behavior
- Comprehensive test coverage

### 4. **Performance**
- Lazy loading of components
- Caching at multiple levels
- Optimized builds for production

### 5. **Developer Experience**
- Clear API contracts
- Good documentation
- Easy to understand codebase

---

## Migration Path from V1 to V2

### Phase 1: Core Library
1. Extract shared logic into core modules
2. Implement data loading system
3. Implement filter system
4. Write tests for core

### Phase 2: Web Application
1. Refactor web app to use core library
2. Implement component system
3. Add state management
4. Improve UI/UX

### Phase 3: Build System
1. Create automated data generation
2. Set up optimization pipeline
3. Configure GitHub Pages deployment

### Phase 4: Plugin System
1. Define plugin interfaces
2. Create example plugins
3. Document plugin development

### Phase 5: CLI Tools
1. Refactor CLI to use core library
2. Improve command structure
3. Add interactive mode

---

## Example: Adding a New Filter

```javascript
// 1. Create the filter
// plugins/my-filters/region-filter.js
import { BaseFilter } from '../../core/filters/base-filter.js';

export class RegionFilter extends BaseFilter {
  constructor() {
    super({
      name: 'region',
      type: 'select',
      label: 'Region',
      options: ['Kanto', 'Johto', 'Hoenn', 'Sinnoh',
                'Unova', 'Kalos', 'Alola', 'Galar', 'Paldea']
    });
  }

  apply(pokemon, region) {
    if (!region) return true;
    return this.getRegion(pokemon.generation) === region;
  }

  getRegion(gen) {
    const map = {
      1: 'Kanto', 2: 'Johto', 3: 'Hoenn',
      4: 'Sinnoh', 5: 'Unova', 6: 'Kalos',
      7: 'Alola', 8: 'Galar', 9: 'Paldea'
    };
    return map[gen];
  }
}

// 2. Register it
import { FilterRegistry } from '../../core/filters/filter-registry.js';
import { RegionFilter } from './plugins/my-filters/region-filter.js';

FilterRegistry.register(new RegionFilter());

// 3. Done! It automatically appears in all UIs
```

---

## Testing Strategy

```javascript
// tests/core/filters/type-filter.test.js
import { TypeFilter } from '../../../core/filters/type-filter.js';

describe('TypeFilter', () => {
  let filter;

  beforeEach(() => {
    filter = new TypeFilter();
  });

  test('filters Fire types correctly', () => {
    const pokemon = { types: ['Fire', 'Flying'] };
    expect(filter.apply(pokemon, ['Fire'])).toBe(true);
  });

  test('returns true for empty filter', () => {
    const pokemon = { types: ['Water'] };
    expect(filter.apply(pokemon, [])).toBe(true);
  });

  test('validates input correctly', () => {
    expect(filter.validate(['Fire'])).toBe(true);
    expect(filter.validate(['InvalidType'])).toBe(false);
    expect(filter.validate('not-an-array')).toBe(false);
  });
});
```

---

## Deployment to GitHub Pages

```yaml
# .github/workflows/deploy.yml
name: Deploy to GitHub Pages

on:
  push:
    branches: [ main ]

jobs:
  build-and-deploy:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v2

      - name: Setup Node.js
        uses: actions/setup-node@v2
        with:
          node-version: '18'

      - name: Install dependencies
        run: npm install

      - name: Generate data
        run: npm run build:data

      - name: Build web app
        run: npm run build

      - name: Deploy to GitHub Pages
        uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./dist
```

---

## Summary

**V2 Architecture Goals:**
1. ✅ Modular components that can be used independently
2. ✅ Plugin system for community extensions
3. ✅ Configuration-driven behavior
4. ✅ Separation of concerns (data/logic/UI)
5. ✅ Comprehensive testing
6. ✅ Optimized for GitHub Pages deployment
7. ✅ Easy to maintain and extend

**Key Improvements:**
- Shared core library eliminates code duplication
- Plugin architecture allows extending without modifying core
- Service layer provides clean API
- Component system makes UI development easier
- Build system automates data generation and deployment
- Clear migration path from V1 to V2
