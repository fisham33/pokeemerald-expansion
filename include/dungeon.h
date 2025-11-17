#ifndef GUARD_DUNGEON_H
#define GUARD_DUNGEON_H

#include "constants/dungeons.h"

// === DUNGEON TRAINER SYSTEM ===
struct DungeonTrainer {
    u16 arrayElement;      // Index into trainer class pool
    u16 gfxIdVar;          // VAR_OBJ_GFX_ID_X to use
    u16 trainerFlag;       // FLAG_DUNGEON_TRAINER_X
    u16 trainerIdVar;      // VAR_DUNGEON_TRAINER_X (stores dynamic trainer ID)
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
    DUNGEON_BOSS_POKEMON,  // Boss Pokemon (wild encounter with totem boosts)
    DUNGEON_BOSS_TRAINER,  // Trainer battle
};

// Totem boosts for boss Pokemon
struct TotemBoosts {
    s8 atk;
    s8 def;
    s8 speed;
    s8 spatk;
    s8 spdef;
    s8 acc;
    s8 evas;
};

// Field effects for boss battles
struct BossFieldEffect {
    u8 weather;        // WEATHER_* constant (0 = no weather)
    u8 terrain;        // Terrain type (0 = no terrain)
};

// Boss Pokemon configuration (for wild encounters)
struct BossPokemon {
    u16 species;           // Species (or species1 for doubles)
    u8 level;              // Level (or level1 for doubles)
    u16 heldItem;          // Held item (or item1 for doubles)
    u16 moves[4];          // Move set (or moves1 for doubles)
    u16 species2;          // Species2 (for double battles, 0 if single)
    u8 level2;             // Level2 (for double battles)
    u16 heldItem2;         // Held item2 (for double battles)
    u16 moves2[4];         // Move set2 (for double battles)
    struct TotemBoosts boosts;       // Stat boosts applied to boss
    struct BossFieldEffect fieldEffect;  // Field effects (weather/terrain)
    u16 graphicsId;        // OBJ_EVENT_GFX_* (overworld sprite)
    const u8 *introText;   // Text shown before battle
    const u8 *defeatText;  // Text shown after defeating boss
};

// Boss Trainer configuration
struct BossTrainer {
    u16 trainerId;         // TRAINER_* from trainers.party
    u16 graphicsId;        // OBJ_EVENT_GFX_* (overworld sprite, overrides trainer default if non-zero)
    const u8 *introText;   // Custom intro text (overrides trainer default if non-NULL)
    const u8 *defeatText;  // Custom defeat text (overrides trainer default if non-NULL)
};

// Main boss definition
struct DungeonBoss {
    u8 encounterType;      // DUNGEON_BOSS_POKEMON or DUNGEON_BOSS_TRAINER
    union {
        struct BossPokemon pokemon;
        struct BossTrainer trainer;
    } data;
};

// === NARRATIVE SYSTEM ===

#define BOSS_TYPE_NONE    0
#define BOSS_TYPE_TRAINER 1
#define BOSS_TYPE_POKEMON 2

// Pairs a trainer ID with their overworld sprite
struct DungeonTrainerEntry {
    u16 trainerId;      // TRAINER_* constant
    u16 graphicsId;     // OBJ_EVENT_GFX_* for overworld sprite
};

// Daily rotating narrative that affects dungeon content
struct DungeonNarrative {
    u8 id;
    const u8 *name;                          // "Professor's Expedition"
    const u8 *description;                   // Multi-line description shown at entrance

    // Trainer configuration
    u8 trainerCount;                         // Number of trainers in pool
    const struct DungeonTrainerEntry *trainerPool;  // Array of trainer+graphics pairs

    // Wild encounters
    const struct WildPokemonInfo *landEncounters;
    const struct WildPokemonInfo *waterEncounters;

    // Boss configuration
    u8 bossType;                             // BOSS_TYPE_TRAINER or BOSS_TYPE_POKEMON
    union {
        struct {
            u16 trainerId;                   // TRAINER_* constant
            u16 graphicsId;                  // OBJ_EVENT_GFX_*
        } trainer;
        struct {
            u16 species;                     // SPECIES_*
            u8 level;
            u16 heldItem;                    // ITEM_*
            u8 totemBoosts[7];               // HP/Atk/Def/SpA/SpD/Spe/Acc boosts
        } pokemon;
    } boss;

    // Rewards
    const u16 *rewardItems;                  // Array of ITEM_* based on score tiers
    u8 rewardTierCount;                      // Number of reward tiers

    // Dialog text pools (randomly selected for variety)
    const u8 * const *trainerIntroTexts;     // Array of regular trainer intro text options
    u8 trainerIntroTextCount;
    const u8 * const *trainerDefeatTexts;    // Array of regular trainer defeat text options
    u8 trainerDefeatTextCount;

    const u8 * const *bossIntroTexts;        // Array of boss intro text options
    u8 bossIntroTextCount;
    const u8 * const *bossDefeatTexts;       // Array of boss defeat text options
    u8 bossDefeatTextCount;
    const u8 * const *bossVictoryTexts;      // Array of boss victory text options (after player wins)
    u8 bossVictoryTextCount;
};

// Daily rotating modifier that affects battle conditions
struct DungeonModifier {
    u8 id;
    const u8 *name;                          // "Permanent Sunlight"
    const u8 *description;                   // "Harsh sunlight throughout the dungeon"

    // Battle conditions
    u8 weatherOrTerrain;                     // STARTING_STATUS_* constant
    u8 weatherDuration;                      // 0 = infinite, else turn count

    // Battle flags
    u16 battleTypeFlags;                     // B_FLAG_INVERSE_BATTLE, etc.

    // Additional modifiers (optional)
    s8 levelModifier;                        // ±level adjustment for all mons
    u8 expMultiplier;                        // 1-5x experience
    u8 moneyMultiplier;                      // 1-5x prize money
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

// Narrative system
void Dungeon_CheckDailyRotation(void);
const struct DungeonNarrative *Dungeon_GetActiveNarrative(u8 dungeonId);
const struct DungeonModifier *Dungeon_GetActiveModifier(u8 dungeonId);
void Dungeon_ShowEntranceInfo(u8 dungeonId);

// Modifier application
void Dungeon_ApplyModifierForBattle(void);

// === SCRIPT-CALLABLE FUNCTIONS (for callnative) ===
// These functions are designed to be called from Pory/ASM scripts using callnative.
// They communicate with scripts via gSpecialVar_0x8000 and VAR_RESULT.

void Script_Dungeon_Enter(void);              // Enter dungeon (reads dungeonId from gSpecialVar_0x8000)
void Script_Dungeon_ShowEntranceInfo(void);   // Display narrative/modifier info (reads dungeonId from gSpecialVar_0x8000)
void Script_Dungeon_InitializeIfNeeded(void); // Initialize dungeon if not already active
void Script_Dungeon_Exit(void);               // Exit dungeon and reset state
void Script_Dungeon_SpawnTrainers(void);      // Spawn trainers in current room
void Script_Dungeon_OnTrainerDefeated(void);  // Call after defeating a trainer
void Script_Dungeon_CheckRoomCleared(void);   // Check if room cleared (sets VAR_RESULT)
void Script_Dungeon_PrepareNextRoom(void);    // Prepare next room warp (sets VAR_0x8004-8008)
void Script_Dungeon_AdvanceToNextRoom(void);  // Move to next room (legacy, calls PrepareNextRoom)
void Script_Dungeon_IsOnBossFloor(void);      // Check if on boss floor (sets VAR_RESULT)
void Script_Dungeon_SpawnBoss(void);          // Spawn boss encounter
void Script_Dungeon_StartBossPokemonBattle(void);     // Start boss Pokemon battle
void Script_Dungeon_OnBossDefeated(void);             // Handle boss defeat and warp to end room
void Script_Dungeon_GetBossTrainerText(void);         // Load custom trainer text into gStringVar4
void Script_Dungeon_GetBossPokemonText(void);         // Load custom Pokemon intro text into gStringVar4
void Script_Dungeon_GetBossPokemonDefeatText(void);   // Load custom Pokemon defeat text into gStringVar4
void Script_Dungeon_GetBossType(void);                // Get boss type from narrative (sets VAR_RESULT)
void Script_Dungeon_GetBossPokemonSpecies(void);      // Get boss Pokemon species (sets VAR_0x8004)
void Script_Dungeon_GetBossPokemonLevel(void);        // Get boss Pokemon level (sets VAR_0x8004)
void Script_Dungeon_GetBossPokemonItem(void);         // Get boss Pokemon item (sets VAR_0x8004)
void Script_Dungeon_DistributeRewards(void);  // Give rewards based on performance
void Script_Dungeon_GetRewardTier(void);      // Get reward tier 1-3 (sets VAR_RESULT)
void Script_Dungeon_OnBossDefeated_SpawnRewards(void);  // Spawn reward items in boss room
void Script_Dungeon_GetRewardItem(void);      // Get specific reward item by tier (uses VAR_TEMP_0, sets VAR_0x8004)
void Script_Dungeon_IsActive(void);           // Check if dungeon active (sets VAR_RESULT)
void Script_Dungeon_GetCurrentRoom(void);     // Get room number (sets VAR_RESULT)
void Script_Dungeon_GetRewardScore(void);     // Get reward score (sets VAR_RESULT)
void Script_Dungeon_SetupTrainerBattle(void); // Setup trainer battle with dynamic ID (reads trainerIdVar from gSpecialVar_0x8000)

// Dialog text retrieval (loads random text from narrative into gStringVar4)
// These functions support merge field placeholders that are automatically expanded:
//
// Available merge fields:
//   {STR_VAR_1} - Auto-populated by boss functions:
//                 - Pokemon bosses: Species name (e.g., "ONIX")
//                 - Trainer bosses: Trainer name (e.g., "Maxie")
//   {STR_VAR_2} - Available for scripts to populate (e.g., tier, score)
//   {STR_VAR_3} - Available for scripts to populate (generic placeholder)
//   {PLAYER}    - Player's name (built-in game placeholder)
//
// Usage examples:
//   "The mighty {STR_VAR_1} has been defeated!"  -> "The mighty ONIX has been defeated!"
//   "{STR_VAR_1}: You've made it this far..."    -> "Maxie: You've made it this far..."
//   "You earned {STR_VAR_2} rank!"               -> "You earned Gold rank!" (script sets STR_VAR_2)
//
// To use {STR_VAR_2}/{STR_VAR_3} from scripts:
//   bufferstring(STR_VAR_2, "Gold")  // Sets STR_VAR_2
//   bufferstring(STR_VAR_3, "450")   // Sets STR_VAR_3
//   callnative(Script_Dungeon_GetRandomBossVictory)
//   msgbox(gStringVar4, MSGBOX_DEFAULT)
//
void Script_Dungeon_GetRandomTrainerIntro(void);    // Get random trainer intro text
void Script_Dungeon_GetRandomTrainerDefeat(void);   // Get random trainer defeat text
void Script_Dungeon_GetRandomBossIntro(void);       // Get random boss intro text (auto-populates {STR_VAR_1})
void Script_Dungeon_GetRandomBossDefeat(void);      // Get random boss defeat text (auto-populates {STR_VAR_1})
void Script_Dungeon_GetRandomBossVictory(void);     // Get random boss victory text (auto-populates {STR_VAR_1})

#endif // GUARD_DUNGEON_H
