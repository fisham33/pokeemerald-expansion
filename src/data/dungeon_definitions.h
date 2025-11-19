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
#include "dungeon_rooms.h"  // Include room pool definitions (same directory)

static const struct Dungeon sDungeons[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = {
        .baseLevel = 20,
        .levelRange = 5,  // Level range: 15-25
        .roomCount = 5,
        .roomPool = sCaveRooms,
        .roomPoolSize = ARRAY_COUNT(sCaveRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,

        // Lockout mode
        .lockoutMode = LOCKOUT_DAILY,  // Rewards once per day
    },
    [DUNGEON_MID_FOREST] = {
        .baseLevel = 40,
        .levelRange = 5,  // Level range: 35-45
        .roomCount = 5,
        .roomPool = sForestRooms,
        .roomPoolSize = ARRAY_COUNT(sForestRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,

        // Lockout mode
        .lockoutMode = LOCKOUT_DAILY,  // Rewards once per day
    },
    [DUNGEON_LATE_MOUNTAIN] = {
        .baseLevel = 60,
        .levelRange = 5,  // Level range: 55-65
        .roomCount = 5,
        .roomPool = sMountainRooms,
        .roomPoolSize = ARRAY_COUNT(sMountainRooms),

        // Refresh modes (using global defaults from config/dungeon.h)
        // Override these values per-dungeon if needed
        .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
        .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,
        .fixedNarrativeId = DUNGEON_DEFAULT_FIXED_NARRATIVE_ID,
        .fixedModifierId = DUNGEON_DEFAULT_FIXED_MODIFIER_ID,

        // Lockout mode
        .lockoutMode = LOCKOUT_DAILY,  // Rewards once per day
    },
};
