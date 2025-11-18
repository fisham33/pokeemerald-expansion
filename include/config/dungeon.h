#ifndef GUARD_CONFIG_DUNGEON_H
#define GUARD_CONFIG_DUNGEON_H

// === BASIC DUNGEON SETTINGS ===

// Number of rooms per dungeon run (before boss)
#define DUNGEON_ROOMS_PER_RUN           5

// Trainer configuration
#define DUNGEON_MAX_TRAINERS_PER_ROOM   4       // Maximum trainers that can spawn in a room
#define I_DUNGEON_TRAINER_COUNT_MIN     2       // Minimum trainers per room
#define I_DUNGEON_TRAINER_COUNT_MAX     4       // Maximum trainers per room

// Reward scoring
#define DUNGEON_POINTS_PER_TRAINER      4       // Points for defeating a trainer
#define DUNGEON_POINTS_PER_CATCH        1       // Points for catching a Pokemon
#define DUNGEON_POINTS_BOSS_POKEMON     20      // Points for defeating boss Pokemon
#define DUNGEON_POINTS_BOSS_TRAINER     20      // Points for defeating boss trainer

// Reward tier thresholds
#define DUNGEON_REWARD_TIER_GOLD        70      // Score needed for gold tier (best rewards)
#define DUNGEON_REWARD_TIER_SILVER      45      // Score needed for silver tier (medium rewards)
// Bronze tier is anything below DUNGEON_REWARD_TIER_SILVER

// === NARRATIVE & MODIFIER SYSTEM ===

// Enable daily rotation
#define I_DUNGEON_DAILY_ROTATION        TRUE

// Rotation interval (days)
// 1 = daily, 7 = weekly
#define I_DUNGEON_ROTATION_INTERVAL     1

// Default refresh modes (can be overridden per-dungeon in dungeon_definitions.h)
// Options:
//   REFRESH_FIXED      - Never changes (uses fixed IDs below)
//   REFRESH_PER_ENTRY  - Random every entry (no save needed - works even on reset!)
//   REFRESH_DAILY      - Changes once per day (persists in save)
//   REFRESH_WEEKLY     - Changes once per week (persists in save)
#define DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE  REFRESH_PER_ENTRY
#define DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE   REFRESH_PER_ENTRY

// Default fixed IDs (used when refresh mode is REFRESH_FIXED)
#define DUNGEON_DEFAULT_FIXED_NARRATIVE_ID      NARRATIVE_NONE
#define DUNGEON_DEFAULT_FIXED_MODIFIER_ID       MODIFIER_NONE

// === DEBUG & TESTING ===

// Enable debug mode to force specific narratives/modifiers
// Set to TRUE to override daily rotation for testing
#define I_DUNGEON_DEBUG_MODE            FALSE

// Force specific modifier (only when I_DUNGEON_DEBUG_MODE is TRUE)
// Example: MODIFIER_PERMANENT_SNOW, MODIFIER_INVERSE_BATTLE, etc.
#define I_DUNGEON_DEBUG_MODIFIER        MODIFIER_PERMANENT_HAIL

// Force specific narrative (only when I_DUNGEON_DEBUG_MODE is TRUE)
// Example: NARRATIVE_CAVE_TEST, NARRATIVE_CAVE_MAGMA, etc.
#define I_DUNGEON_DEBUG_NARRATIVE       NARRATIVE_CAVE_TEST

// Modifier pools (per dungeon)
// Define which modifiers can appear in each dungeon

// Cave modifiers (DUNGEON_EARLY_CAVE)
#define DUNGEON_CAVE_MODIFIERS \
    MODIFIER_PERMANENT_SUN, \
    MODIFIER_PERMANENT_SANDSTORM, \
    MODIFIER_TRICK_ROOM, \
    MODIFIER_INVERSE_BATTLE, \
    MODIFIER_DOUBLE_EXP

// Forest modifiers (DUNGEON_MID_FOREST) - future
#define DUNGEON_FOREST_MODIFIERS \
    MODIFIER_PERMANENT_RAIN, \
    MODIFIER_TRICK_ROOM, \
    MODIFIER_INVERSE_BATTLE

// Mountain modifiers (DUNGEON_LATE_MOUNTAIN) - future
#define DUNGEON_MOUNTAIN_MODIFIERS \
    MODIFIER_PERMANENT_HAIL, \
    MODIFIER_PERMANENT_SNOW, \
    MODIFIER_TRICK_ROOM, \
    MODIFIER_EXPERT_CHALLENGE

#endif // GUARD_CONFIG_DUNGEON_H
