// Dungeon Wild Encounter Pools
// This file defines wild encounter tables for each biome type
// Levels are set to 0,0 and will be filled in at runtime based on dungeon tier

#include "constants/species.h"

// TODO: Fill in species for each biome
// These should be thematically appropriate (cave = rock/ground, forest = bug/grass, etc.)
// Levels will be dynamically set based on the dungeon's level range

// === CAVE BIOME ENCOUNTERS ===
static const struct WildPokemon sCaveEncounters[] = {
    { 0, 0, SPECIES_ZUBAT },      // Common (20%)
    { 0, 0, SPECIES_ZUBAT },      // Common (20%)
    { 0, 0, SPECIES_GEODUDE },    // Common (10%)
    { 0, 0, SPECIES_GEODUDE },    // Common (10%)
    { 0, 0, SPECIES_ROGGENROLA }, // Common (10%)
    { 0, 0, SPECIES_ROGGENROLA }, // Common (10%)
    { 0, 0, SPECIES_ONIX },       // Uncommon (5%)
    { 0, 0, SPECIES_ONIX },       // Uncommon (5%)
    { 0, 0, SPECIES_CARBINK },    // Rare (4%)
    { 0, 0, SPECIES_CARBINK },    // Rare (4%)
    { 0, 0, SPECIES_DRILBUR },    // Very Rare (1%)
    { 0, 0, SPECIES_DRILBUR },    // Very Rare (1%)
};

static const struct DungeonEncounterPool sCaveEncounterPool = {
    .biome = DUNGEON_BIOME_CAVE,
    .encounterRate = 20,
    .landMons = sCaveEncounters,
    .waterMons = NULL,
};

// === FOREST BIOME ENCOUNTERS ===
static const struct WildPokemon sForestEncounters[] = {
    { 0, 0, SPECIES_CATERPIE },   // Common (20%)
    { 0, 0, SPECIES_CATERPIE },   // Common (20%)
    { 0, 0, SPECIES_WEEDLE },     // Common (10%)
    { 0, 0, SPECIES_WEEDLE },     // Common (10%)
    { 0, 0, SPECIES_ODDISH },     // Common (10%)
    { 0, 0, SPECIES_ODDISH },     // Common (10%)
    { 0, 0, SPECIES_BELLSPROUT }, // Uncommon (5%)
    { 0, 0, SPECIES_BELLSPROUT }, // Uncommon (5%)
    { 0, 0, SPECIES_TANGELA },    // Rare (4%)
    { 0, 0, SPECIES_TANGELA },    // Rare (4%)
    { 0, 0, SPECIES_HERACROSS },  // Very Rare (1%)
    { 0, 0, SPECIES_HERACROSS },  // Very Rare (1%)
};

static const struct DungeonEncounterPool sForestEncounterPool = {
    .biome = DUNGEON_BIOME_FOREST,
    .encounterRate = 20,
    .landMons = sForestEncounters,
    .waterMons = NULL,
};

// === MOUNTAIN BIOME ENCOUNTERS ===
static const struct WildPokemon sMountainEncounters[] = {
    { 0, 0, SPECIES_MACHOP },     // Common (20%)
    { 0, 0, SPECIES_MACHOP },     // Common (20%)
    { 0, 0, SPECIES_GRAVELER },   // Common (10%)
    { 0, 0, SPECIES_GRAVELER },   // Common (10%)
    { 0, 0, SPECIES_RHYHORN },    // Common (10%)
    { 0, 0, SPECIES_RHYHORN },    // Common (10%)
    { 0, 0, SPECIES_GOLEM },      // Uncommon (5%)
    { 0, 0, SPECIES_GOLEM },      // Uncommon (5%)
    { 0, 0, SPECIES_SKARMORY },   // Rare (4%)
    { 0, 0, SPECIES_SKARMORY },   // Rare (4%)
    { 0, 0, SPECIES_ABSOL },      // Very Rare (1%)
    { 0, 0, SPECIES_ABSOL },      // Very Rare (1%)
};

static const struct DungeonEncounterPool sMountainEncounterPool = {
    .biome = DUNGEON_BIOME_MOUNTAIN,
    .encounterRate = 20,
    .landMons = sMountainEncounters,
    .waterMons = NULL,
};

// TODO: Add more biome encounter pools as needed:
// - DUNGEON_BIOME_WATER
// - DUNGEON_BIOME_DESERT
// - DUNGEON_BIOME_SNOW
