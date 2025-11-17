#ifndef GUARD_DATA_DUNGEON_ROOMS_H
#define GUARD_DATA_DUNGEON_ROOMS_H

// Dungeon Room Definitions
// This file defines the room pools for each dungeon

#include "constants/maps.h"

// TODO: Replace MAP placeholders with actual map constants once maps are created
// Each dungeon has a pool of rooms that are randomly selected during gameplay

// === EARLY CAVE DUNGEON ROOMS ===
static const struct DungeonRoom sCaveRooms[] = {
    {
        .mapConstant = MAP_DUNGEON1_ROOM1,
        .trainerCountMin = 1,
        .trainerCountMax = 2,
        .spawnX = 3,
        .spawnY = 3,
    },
    {
        .mapConstant = MAP_DUNGEON1_ROOM2,
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_DUNGEON1_ROOM3,
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 11,
        .spawnY = 9,
    },
    {
        .mapConstant = MAP_DUNGEON1_ROOM4,
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 8,
        .spawnY = 1,
    },
    {
        .mapConstant = MAP_DUNGEON1_ROOM5,
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 12,
        .spawnY = 8,
    },
};

// === MID FOREST DUNGEON ROOMS ===
static const struct DungeonRoom sForestRooms[] = {
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM1
        .trainerCountMin = 1,
        .trainerCountMax = 2,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM2
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM3
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM4
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM5
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
};

// === LATE MOUNTAIN DUNGEON ROOMS ===
static const struct DungeonRoom sMountainRooms[] = {
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM1
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM2
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM3
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM4
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM5
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
    },
};

#endif // GUARD_DATA_DUNGEON_ROOMS_H
