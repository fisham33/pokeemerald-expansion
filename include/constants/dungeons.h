#ifndef GUARD_CONSTANTS_DUNGEONS_H
#define GUARD_CONSTANTS_DUNGEONS_H

// Dungeon IDs
enum DungeonId {
    DUNGEON_EARLY_CAVE,      // Level 20
    DUNGEON_MID_FOREST,      // Level 40
    DUNGEON_LATE_MOUNTAIN,   // Level 60
    DUNGEON_COUNT
};

// Dungeon biome types (affects wild encounters & aesthetics)
enum DungeonBiome {
    DUNGEON_BIOME_CAVE,
    DUNGEON_BIOME_FOREST,
    DUNGEON_BIOME_MOUNTAIN,
    DUNGEON_BIOME_WATER,
    DUNGEON_BIOME_DESERT,
    DUNGEON_BIOME_SNOW,
};

// Dungeon difficulty tiers
enum DungeonTier {
    DUNGEON_TIER_EARLY,   // Level 15-25
    DUNGEON_TIER_MID,     // Level 35-45
    DUNGEON_TIER_LATE,    // Level 55-65
    DUNGEON_TIER_COUNT
};

// Refresh modes for narratives and modifiers
enum DungeonRefreshMode {
    REFRESH_FIXED,        // Never changes (uses fixed narrative/modifier)
    REFRESH_PER_ENTRY,    // Randomizes every time player enters dungeon (no save required)
    REFRESH_DAILY,        // Changes once per day (based on RTC, persists in save)
    REFRESH_WEEKLY,       // Changes once per week (based on RTC, persists in save)
};

// Lockout modes for reward eligibility (how often player can receive rewards)
enum DungeonLockoutMode {
    LOCKOUT_NONE,         // No lockout - freely repeatable with rewards
    LOCKOUT_DAILY,        // Rewards once per day (based on RTC)
    LOCKOUT_WEEKLY,       // Rewards once per week (based on RTC)
};

// === STATE ACCESSOR MACROS ===
#define Dungeon_SetActive(val)           (gSaveBlock2Ptr->dungeonActive = (val))
#define Dungeon_IsActive()               (gSaveBlock2Ptr->dungeonActive)
#define Dungeon_SetRoom(val)             (gSaveBlock2Ptr->dungeonCurrentRoom = (val))
#define Dungeon_GetRoom()                (gSaveBlock2Ptr->dungeonCurrentRoom)
#define Dungeon_SetTrainersDefeated(val) (gSaveBlock2Ptr->dungeonTrainersDefeated = (val))
#define Dungeon_GetTrainersDefeated()    (gSaveBlock2Ptr->dungeonTrainersDefeated)
#define Dungeon_SetRewardScore(val)      (gSaveBlock2Ptr->dungeonRewardScore = (val))
#define Dungeon_GetRewardScore()         (gSaveBlock2Ptr->dungeonRewardScore)
#define Dungeon_GetRoomOrder(idx)        (gSaveBlock2Ptr->dungeonRoomOrder[idx])
#define Dungeon_SetRoomOrder(idx, val)   (gSaveBlock2Ptr->dungeonRoomOrder[idx] = (val))

// === FLAGS ===
// Note: All dungeon flags are defined in include/constants/flags.h
// Listed here for reference:
// FLAG_DUNGEON_TRAINER_0          - Trainer 0 visibility (cleared between rooms)
// FLAG_DUNGEON_TRAINER_1          - Trainer 1 visibility (cleared between rooms)
// FLAG_DUNGEON_TRAINER_2          - Trainer 2 visibility (cleared between rooms)
// FLAG_DUNGEON_TRAINER_3          - Trainer 3 visibility (cleared between rooms)
// FLAG_DUNGEON_BOSS_DEFEATED      - Boss defeated this run (cleared on dungeon exit)
// FLAG_DUNGEON_CAVE_COMPLETED     - Early Cave permanently completed
// FLAG_DUNGEON_FOREST_COMPLETED   - Mid Forest permanently completed
// FLAG_DUNGEON_MOUNTAIN_COMPLETED - Late Mountain permanently completed

// === TRAINER CONSTANTS ===
// Trainer IDs - These are now defined in src/data/trainers.party
// Each trainer has a basic 2-3 Pokemon team at level 20 for testing
// The actual teams will be randomized via Trainer Party Pool system (TODO)
// NOTE: The actual TRAINER_DUNGEON_RANDOM_0 etc. constants are auto-generated
// from trainers.party - we don't need to #define them here, just document them

// Boss trainer IDs
#define TRAINER_DUNGEON_BOSS_EARLY      TRAINER_PLAYER  // Placeholder
#define TRAINER_DUNGEON_BOSS_MID        TRAINER_PLAYER  // Placeholder
#define TRAINER_DUNGEON_BOSS_LATE       TRAINER_PLAYER  // Placeholder

// === NARRATIVE SYSTEM ===

// Dungeon narrative IDs
enum DungeonNarratives {
    NARRATIVE_NONE,               // No narrative (shouldn't happen)
    // Cave narratives
    NARRATIVE_CAVE_TEST,          // Test narrative for Phase 1
    NARRATIVE_CAVE_TEAM_MAGMA,    // testing
    NARRATIVE_CAVE_FITNESS,       // testing refactored config
    NARRATIVE_CAVE_PROFESSOR,     // Professor's Expedition
    NARRATIVE_CAVE_MAGMA,         // Team Magma's Search
    NARRATIVE_CAVE_STEVEN,        // Steven's Request
    // Forest narratives (future)
    NARRATIVE_FOREST_AQUA,        // Team Aqua's Search
    // Mountain narratives (future)
    NARRATIVE_MOUNTAIN_HIKER,     // Mountain Challenge
    NARRATIVE_COUNT
};

// Dungeon modifier IDs
enum DungeonModifiers {
    MODIFIER_NONE,                // No modifier
    MODIFIER_PERMANENT_SUN,       // Harsh sunlight throughout
    MODIFIER_PERMANENT_RAIN,      // Rain throughout
    MODIFIER_PERMANENT_SANDSTORM, // Sandstorm throughout
    MODIFIER_PERMANENT_HAIL,      // Hail throughout
    MODIFIER_PERMANENT_SNOW,      // Snow throughout
    MODIFIER_PERMANENT_STRONG_WINDS, // Strong winds (Delta Stream) throughout
    MODIFIER_TRICK_ROOM,          // Trick Room (5 turns)
    MODIFIER_GRAVITY,             // Gravity (5 turns)
    MODIFIER_INVERSE_BATTLE,      // Type matchups inverted
    MODIFIER_DOUBLE_EXP,          // 2x experience
    MODIFIER_EXPERT_CHALLENGE,    // +5 levels to all enemies
    MODIFIER_COUNT
};

#endif // GUARD_CONSTANTS_DUNGEONS_H
