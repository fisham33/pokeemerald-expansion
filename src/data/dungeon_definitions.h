// Dungeon Definitions
// This file defines the configuration for each dungeon
//
// Refresh Mode Configuration:
// - Global defaults are set in include/config/dungeon.h
// - To override for a specific dungeon, replace the DUNGEON_DEFAULT_* macros
//
// Example - Make cave dungeon refresh per entry:
//   .narrativeRefreshMode = REFRESH_PER_ENTRY,  // Override default
//   .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,  // Use default
//
// Example - Make forest dungeon use fixed narrative:
//   .narrativeRefreshMode = REFRESH_FIXED,
//   .fixedNarrativeId = NARRATIVE_FOREST_AQUA,  // Always use this narrative

#include "constants/dungeons.h"
#include "constants/maps.h"
#include "dungeon_rooms.h"  // Include room pool definitions (same directory)

// TODO: Replace MAP placeholders with actual map constants once maps are created

static const struct Dungeon sDungeons[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = {
        .id = DUNGEON_EARLY_CAVE,
        .tier = DUNGEON_TIER_EARLY,
        .biome = DUNGEON_BIOME_CAVE,
        .baseLevel = 20,
        .levelRange = 5,  // Level range: 15-25
        .roomCount = 5,
        .entranceMap = MAP_UNDEFINED, // TODO: Replace with MAP_DUNGEON_CAVE_ENTRANCE
        .roomPool = sCaveRooms,
        .roomPoolSize = ARRAY_COUNT(sCaveRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,
    },
    [DUNGEON_MID_FOREST] = {
        .id = DUNGEON_MID_FOREST,
        .tier = DUNGEON_TIER_MID,
        .biome = DUNGEON_BIOME_FOREST,
        .baseLevel = 40,
        .levelRange = 5,  // Level range: 35-45
        .roomCount = 5,
        .entranceMap = MAP_UNDEFINED, // TODO: Replace with MAP_DUNGEON_FOREST_ENTRANCE
        .roomPool = sForestRooms,
        .roomPoolSize = ARRAY_COUNT(sForestRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,
    },
    [DUNGEON_LATE_MOUNTAIN] = {
        .id = DUNGEON_LATE_MOUNTAIN,
        .tier = DUNGEON_TIER_LATE,
        .biome = DUNGEON_BIOME_MOUNTAIN,
        .baseLevel = 60,
        .levelRange = 5,  // Level range: 55-65
        .roomCount = 5,
        .entranceMap = MAP_UNDEFINED, // TODO: Replace with MAP_DUNGEON_MOUNTAIN_ENTRANCE
        .roomPool = sMountainRooms,
        .roomPoolSize = ARRAY_COUNT(sMountainRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,
    },
};
