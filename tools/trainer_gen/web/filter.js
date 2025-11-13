// Global variable to store Pokemon data
let pokemonData = null;

// Load Pokemon data when page loads
document.addEventListener('DOMContentLoaded', async () => {
    try {
        // Try to load from parent directory (for local development)
        const response = await fetch('../pokemon_data.json');
        if (!response.ok) {
            throw new Error('Failed to load Pokemon data');
        }
        const data = await response.json();
        pokemonData = data.pokemon;
        console.log(`Loaded ${pokemonData.length} Pokemon`);
    } catch (error) {
        console.error('Error loading Pokemon data:', error);
        document.getElementById('results').innerHTML = `
            <p class="placeholder" style="color: red;">
                Error loading Pokemon data. Please ensure pokemon_data.json is accessible.
            </p>
        `;
    }

    // Set up event listeners
    document.getElementById('filterBtn').addEventListener('click', applyFilters);
    document.getElementById('clearBtn').addEventListener('click', clearFilters);
    document.getElementById('showAllBtn').addEventListener('click', showAll);

    // Allow Enter key to trigger filter
    document.querySelectorAll('input').forEach(input => {
        input.addEventListener('keypress', (e) => {
            if (e.key === 'Enter') {
                applyFilters();
            }
        });
    });
});

function getIntValue(id) {
    const value = document.getElementById(id).value.trim();
    return value === '' ? null : parseInt(value);
}

function getStringValue(id) {
    const value = document.getElementById(id).value.trim();
    return value === '' ? null : value;
}

function applyFilters() {
    if (!pokemonData) {
        alert('Pokemon data not loaded yet. Please wait...');
        return;
    }

    // Get filter values
    const generation = getIntValue('generation');
    const typesStr = getStringValue('types');
    const types = typesStr ? typesStr.split(',').map(t => t.trim()) : null;
    const ability = getStringValue('ability');

    const minBst = getIntValue('minBst');
    const maxBst = getIntValue('maxBst');

    const minHp = getIntValue('minHp');
    const maxHp = getIntValue('maxHp');
    const minAtk = getIntValue('minAtk');
    const maxAtk = getIntValue('maxAtk');
    const minDef = getIntValue('minDef');
    const maxDef = getIntValue('maxDef');
    const minSpa = getIntValue('minSpa');
    const maxSpa = getIntValue('maxSpa');
    const minSpd = getIntValue('minSpd');
    const maxSpd = getIntValue('maxSpd');
    const minSpe = getIntValue('minSpe');
    const maxSpe = getIntValue('maxSpe');

    // Filter Pokemon
    const results = filterPokemon(pokemonData, {
        generation,
        types,
        ability,
        minBst, maxBst,
        minHp, maxHp,
        minAtk, maxAtk,
        minDef, maxDef,
        minSpa, maxSpa,
        minSpd, maxSpd,
        minSpe, maxSpe
    });

    displayResults(results);
}

function filterPokemon(pokemon, filters) {
    return pokemon.filter(p => {
        const stats = p.baseStats || {};
        const bst = p.bst || 0;
        const gen = p.generation || 0;

        // Generation filter
        if (filters.generation !== null && gen !== filters.generation) {
            return false;
        }

        // Type filter
        if (filters.types && filters.types.length > 0) {
            const pokemonTypes = (p.types || []).map(t => t.toLowerCase());
            const hasType = filters.types.some(t => pokemonTypes.includes(t.toLowerCase()));
            if (!hasType) return false;
        }

        // Ability filter
        if (filters.ability) {
            const abilityLower = filters.ability.toLowerCase();
            const pokemonAbilities = (p.abilities || []).map(a => a.toLowerCase());
            const hiddenAbility = p.hiddenAbility ? p.hiddenAbility.toLowerCase() : '';
            if (hiddenAbility) pokemonAbilities.push(hiddenAbility);

            const hasAbility = pokemonAbilities.some(a => a.includes(abilityLower));
            if (!hasAbility) return false;
        }

        // BST filter
        if (filters.minBst !== null && bst < filters.minBst) return false;
        if (filters.maxBst !== null && bst > filters.maxBst) return false;

        // Individual stat filters
        if (filters.minHp !== null && (stats.hp || 0) < filters.minHp) return false;
        if (filters.maxHp !== null && (stats.hp || 0) > filters.maxHp) return false;

        if (filters.minAtk !== null && (stats.atk || 0) < filters.minAtk) return false;
        if (filters.maxAtk !== null && (stats.atk || 0) > filters.maxAtk) return false;

        if (filters.minDef !== null && (stats.def || 0) < filters.minDef) return false;
        if (filters.maxDef !== null && (stats.def || 0) > filters.maxDef) return false;

        if (filters.minSpa !== null && (stats.spa || 0) < filters.minSpa) return false;
        if (filters.maxSpa !== null && (stats.spa || 0) > filters.maxSpa) return false;

        if (filters.minSpd !== null && (stats.spd || 0) < filters.minSpd) return false;
        if (filters.maxSpd !== null && (stats.spd || 0) > filters.maxSpd) return false;

        if (filters.minSpe !== null && (stats.spe || 0) < filters.minSpe) return false;
        if (filters.maxSpe !== null && (stats.spe || 0) > filters.maxSpe) return false;

        return true;
    });
}

function displayResults(results) {
    const resultsDiv = document.getElementById('results');
    const countSpan = document.getElementById('resultCount');

    countSpan.textContent = `${results.length} Pokemon`;

    if (results.length === 0) {
        resultsDiv.innerHTML = '<p class="placeholder">No Pokemon found matching the criteria.</p>';
        return;
    }

    const html = results.map((pokemon, index) => {
        const stats = pokemon.baseStats || {};
        const types = pokemon.types || [];
        const abilities = pokemon.abilities || [];
        const hiddenAbility = pokemon.hiddenAbility || null;
        const bst = pokemon.bst || 0;
        const gen = pokemon.generation || 0;

        const typesHtml = types.map(type =>
            `<span class="type-badge type-${type.toLowerCase()}">${type}</span>`
        ).join('');

        const abilitiesHtml = abilities.map(ability =>
            `<span class="ability">${ability}</span>`
        ).join('');

        const hiddenHtml = hiddenAbility
            ? `<span class="ability hidden">Hidden: ${hiddenAbility}</span>`
            : '';

        return `
            <div class="pokemon-card">
                <div class="pokemon-header">
                    <div>
                        <div class="pokemon-name">${pokemon.name}</div>
                        <div class="pokemon-species">${pokemon.species}</div>
                    </div>
                </div>

                <div class="pokemon-info">
                    <div class="info-item">
                        <span class="info-label">Gen:</span>
                        <span class="info-value">${gen}</span>
                    </div>
                    <div class="info-item">
                        <span class="info-label">Types:</span>
                        <div class="types">${typesHtml}</div>
                    </div>
                    <div class="info-item">
                        <span class="info-label">BST:</span>
                        <span class="info-value">${bst}</span>
                    </div>
                </div>

                <div class="stat-bar-container">
                    <div class="stat-item">
                        <div class="stat-name">HP</div>
                        <div class="stat-value">${stats.hp || 0}</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-name">ATK</div>
                        <div class="stat-value">${stats.atk || 0}</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-name">DEF</div>
                        <div class="stat-value">${stats.def || 0}</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-name">SPA</div>
                        <div class="stat-value">${stats.spa || 0}</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-name">SPD</div>
                        <div class="stat-value">${stats.spd || 0}</div>
                    </div>
                    <div class="stat-item">
                        <div class="stat-name">SPE</div>
                        <div class="stat-value">${stats.spe || 0}</div>
                    </div>
                </div>

                <div class="abilities">
                    <span class="abilities-label">Abilities:</span>
                    ${abilitiesHtml}
                    ${hiddenHtml}
                </div>
            </div>
        `;
    }).join('');

    resultsDiv.innerHTML = html;
    resultsDiv.scrollTop = 0;
}

function clearFilters() {
    document.querySelectorAll('input').forEach(input => {
        input.value = '';
    });

    document.getElementById('results').innerHTML =
        '<p class="placeholder">Enter filter criteria and click "Filter" to see results</p>';
    document.getElementById('resultCount').textContent = '0 Pokemon';
}

function showAll() {
    if (!pokemonData) {
        alert('Pokemon data not loaded yet. Please wait...');
        return;
    }

    clearFilters();
    displayResults(pokemonData);
}
