#ifndef GUARD_DUNGEON_H
#define GUARD_DUNGEON_H

#include "constants/dungeons.h"

// === DUNGEON TRAINER SYSTEM ===
struct DungeonTrainer {
    u16 arrayElement;      // Index into trainer class pool
    u16 gfxIdVar;          // VAR_OBJ_GFX_ID_X to use
    u16 trainerFlag;       // FLAG_DUNGEON_TRAINER_X
    u16 trainerId;         // TRAINER_DUNGEON_RANDOM_X
};

// === DUNGEON DEFINITION ===
struct Dungeon {
    u8 id;                 // DUNGEON_ID
    u8 tier;               // DUNGEON_TIER (affects level scaling)
    u8 biome;              // DUNGEON_BIOME (affects encounters)
    u8 baseLevel;          // Base level for encounters/trainers
    u8 levelRange;         // ±range for variation (e.g., 20±5 = 15-25)
    u8 roomCount;          // Number of rooms before boss
    u16 entranceMap;       // MAP_DUNGEON_EARLY_ENTRANCE, etc.
};

// === ROOM DEFINITION ===
struct DungeonRoom {
    u16 mapConstant;       // Which map to load
    u8 trainerCountMin;    // Minimum trainers in this room
    u8 trainerCountMax;    // Maximum trainers in this room
    u8 spawnX;             // Player spawn X coordinate
    u8 spawnY;             // Player spawn Y coordinate
    u8 exitX;              // Exit warp X coordinate
    u8 exitY;              // Exit warp Y coordinate
};

// === WILD ENCOUNTER POOL ===
struct DungeonEncounterPool {
    u8 biome;              // DUNGEON_BIOME
    u8 encounterRate;      // Encounter rate (0-255)
    const struct WildPokemon *landMons;   // Array of 12 species
    const struct WildPokemon *waterMons;  // Array of 5 species (if applicable)
};

// === TRAINER CLASS POOL ===
struct DungeonTrainerClass {
    u16 graphicsId;        // OBJ_EVENT_GFX_*
    u16 trainerPic;        // TRAINER_PIC_*
    u16 trainerClass;      // TRAINER_CLASS_*
    u8 gender;             // MALE/FEMALE
};

// === BOSS DEFINITION ===
enum {
    DUNGEON_BOSS_STATIC,   // Static wild encounter
    DUNGEON_BOSS_TRAINER,  // Trainer battle
};

struct DungeonBoss {
    u8 encounterType;      // DUNGEON_BOSS_STATIC or DUNGEON_BOSS_TRAINER
    u16 species;           // Species for static encounter
    u8 level;              // Level
    u16 heldItem;          // Held item
    u16 moves[4];          // Move set
    u16 graphicsId;        // OBJ_EVENT_GFX_*
    u16 trainerPic;        // TRAINER_PIC_*
    u16 trainerClass;      // TRAINER_CLASS_*
    u16 trainerId;         // TRAINER_ID (if trainer type)
};

// === PUBLIC API ===

// Dungeon entry/exit
void Dungeon_Enter(u8 dungeonId);
void Dungeon_Exit(void);
// Note: Dungeon_IsActive() is a macro defined in constants/dungeons.h

// State management
u8 Dungeon_GetCurrentRoom(void);
u8 Dungeon_GetCurrentDungeonId(void);
// Note: Dungeon_GetRewardScore() is a macro defined in constants/dungeons.h
void Dungeon_IncrementRewardScore(u16 points);

// Room progression
void Dungeon_AdvanceToNextRoom(void);
bool8 Dungeon_IsOnBossFloor(void);
void Dungeon_ResetRun(void);

// Trainer spawning
void Dungeon_SpawnTrainers(void);
void Dungeon_ClearTrainerFlags(void);
u8 Dungeon_GetTrainersDefeatedThisRoom(void);
void Dungeon_OnTrainerDefeated(void);

// Boss handling
void Dungeon_SpawnBoss(void);
const struct DungeonBoss *Dungeon_GetCurrentBoss(void);

// Wild encounters
void Dungeon_SetupWildEncounters(void);
const struct WildPokemonInfo *Dungeon_GetLandEncounters(void);
const struct WildPokemonInfo *Dungeon_GetWaterEncounters(void);

// Rewards
void Dungeon_DistributeRewards(void);
u16 Dungeon_CalculateRewardTier(void);  // Returns reward quality based on score

// Utility
const struct Dungeon *Dungeon_GetDefinition(u8 dungeonId);
u8 Dungeon_GetCurrentLevel(void);  // Returns scaled level for current dungeon

// === SCRIPT-CALLABLE FUNCTIONS (for callnative) ===
// These functions are designed to be called from Pory/ASM scripts using callnative.
// They communicate with scripts via gSpecialVar_0x8000 and VAR_RESULT.

void Script_Dungeon_Enter(void);              // Enter dungeon (reads dungeonId from gSpecialVar_0x8000)
void Script_Dungeon_InitializeIfNeeded(void); // Initialize dungeon if not already active
void Script_Dungeon_Exit(void);               // Exit dungeon and reset state
void Script_Dungeon_SpawnTrainers(void);      // Spawn trainers in current room
void Script_Dungeon_OnTrainerDefeated(void);  // Call after defeating a trainer
void Script_Dungeon_CheckRoomCleared(void);   // Check if room cleared (sets VAR_RESULT)
void Script_Dungeon_PrepareNextRoom(void);    // Prepare next room warp (sets VAR_0x8004-8008)
void Script_Dungeon_AdvanceToNextRoom(void);  // Move to next room (legacy, calls PrepareNextRoom)
void Script_Dungeon_IsOnBossFloor(void);      // Check if on boss floor (sets VAR_RESULT)
void Script_Dungeon_SpawnBoss(void);          // Spawn boss encounter
void Script_Dungeon_DistributeRewards(void);  // Give rewards based on performance
void Script_Dungeon_GetRewardTier(void);      // Get reward tier 1-3 (sets VAR_RESULT)
void Script_Dungeon_IsActive(void);           // Check if dungeon active (sets VAR_RESULT)
void Script_Dungeon_GetCurrentRoom(void);     // Get room number (sets VAR_RESULT)
void Script_Dungeon_GetRewardScore(void);     // Get reward score (sets VAR_RESULT)

#endif // GUARD_DUNGEON_H
