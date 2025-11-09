#ifndef GUARD_CONFIG_DUNGEON_H
#define GUARD_CONFIG_DUNGEON_H

// === DUNGEON SYSTEM CONFIG ===

// Number of rooms before boss room
#define DUNGEON_ROOMS_PER_RUN           5

// Maximum trainers that can spawn in a single room
#define DUNGEON_MAX_TRAINERS_PER_ROOM   4

// Maximum number of concurrent dungeons
#define DUNGEON_COUNT                   3  // Early/Mid/Late game dungeons

// Healing between rooms
#define I_DUNGEON_HEAL_BETWEEN_ROOMS    TRUE

// Allow player to leave mid-run
#define I_DUNGEON_ALLOW_ESCAPE          TRUE

// Reset progress on escape/whiteout
#define I_DUNGEON_RESET_ON_LEAVE        TRUE

// Reward scaling
#define I_DUNGEON_BASE_REWARD_POINTS    10  // Base points per trainer defeat
#define I_DUNGEON_BONUS_CAUGHT_SPECIES  5   // Bonus points per unique species caught

// Difficulty scaling
#define I_DUNGEON_TRAINER_COUNT_MIN     1   // Minimum trainers per room
#define I_DUNGEON_TRAINER_COUNT_MAX     4   // Maximum trainers per room

// Level caps (optional)
#define I_DUNGEON_ENFORCE_LEVEL_CAP     FALSE

#endif // GUARD_CONFIG_DUNGEON_H
