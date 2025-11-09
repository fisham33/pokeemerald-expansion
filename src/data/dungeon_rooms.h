// Dungeon Room Definitions
// This file defines the room pools for each dungeon

#include "constants/maps.h"

// TODO: Replace MAP placeholders with actual map constants once maps are created
// Each dungeon has a pool of rooms that are randomly selected during gameplay

// === EARLY CAVE DUNGEON ROOMS ===
static const struct DungeonRoom sCaveRooms[] = {
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_CAVE_ROOM1
        .trainerCountMin = 1,
        .trainerCountMax = 2,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_CAVE_ROOM2
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_CAVE_ROOM3
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_CAVE_ROOM4
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_CAVE_ROOM5
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
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
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM2
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM3
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM4
        .trainerCountMin = 2,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_FOREST_ROOM5
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
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
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM2
        .trainerCountMin = 2,
        .trainerCountMax = 3,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM3
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM4
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
    {
        .mapConstant = MAP_UNDEFINED,  // TODO: MAP_DUNGEON_MOUNTAIN_ROOM5
        .trainerCountMin = 3,
        .trainerCountMax = 4,
        .spawnX = 9,
        .spawnY = 8,
        .exitX = 9,
        .exitY = 9,
    },
};
