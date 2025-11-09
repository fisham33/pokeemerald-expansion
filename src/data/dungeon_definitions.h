// Dungeon Definitions
// This file defines the configuration for each dungeon

#include "constants/dungeons.h"
#include "constants/maps.h"

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
    },
    [DUNGEON_MID_FOREST] = {
        .id = DUNGEON_MID_FOREST,
        .tier = DUNGEON_TIER_MID,
        .biome = DUNGEON_BIOME_FOREST,
        .baseLevel = 40,
        .levelRange = 5,  // Level range: 35-45
        .roomCount = 5,
        .entranceMap = MAP_UNDEFINED, // TODO: Replace with MAP_DUNGEON_FOREST_ENTRANCE
    },
    [DUNGEON_LATE_MOUNTAIN] = {
        .id = DUNGEON_LATE_MOUNTAIN,
        .tier = DUNGEON_TIER_LATE,
        .biome = DUNGEON_BIOME_MOUNTAIN,
        .baseLevel = 60,
        .levelRange = 5,  // Level range: 55-65
        .roomCount = 5,
        .entranceMap = MAP_UNDEFINED, // TODO: Replace with MAP_DUNGEON_MOUNTAIN_ENTRANCE
    },
};
