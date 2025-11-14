#include "global.h"
#include "dungeon.h"
#include "event_data.h"
#include "random.h"
#include "pokemon.h"
#include "wild_encounter.h"
#include "overworld.h"
#include "fieldmap.h"
#include "field_screen_effect.h"
#include "script.h"
#include "item.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "task.h"
#include "event_object_movement.h"
#include "constants/dungeons.h"
#include "constants/maps.h"
#include "constants/items.h"
#include "constants/species.h"
#include "config/dungeon.h"

// Include data files
#include "data/dungeon_definitions.h"
#include "data/dungeon_rooms.h"
#include "data/dungeon_trainers.h"
#include "data/dungeon_encounters.h"
#include "data/dungeon_bosses.h"

// Forward declarations for static functions
static void Dungeon_WarpToRoom(u8 roomIndex);
static void Dungeon_WarpToBossRoom(void);

// ==========================================================================
// DUNGEON ENTRY/EXIT
// ==========================================================================

void Dungeon_Enter(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
        return;

    // Initialize dungeon state
    Dungeon_SetActive(TRUE);
    Dungeon_SetRoom(0);
    Dungeon_SetTrainersDefeated(0);
    Dungeon_SetRewardScore(0);

    // Store which dungeon we're in using temp var
    VarSet(VAR_TEMP_0, dungeonId);

    // Clear all trainer flags
    Dungeon_ClearTrainerFlags();
}

void Dungeon_Exit(void)
{
    // Clear dungeon state
    Dungeon_SetActive(FALSE);
    Dungeon_SetRoom(0);
    Dungeon_SetTrainersDefeated(0);
    Dungeon_SetRewardScore(0);
    VarSet(VAR_TEMP_0, 0);

    // Clear all trainer flags
    Dungeon_ClearTrainerFlags();
}

// Note: Dungeon_IsActive() is defined as a macro in constants/dungeons.h

// ==========================================================================
// STATE MANAGEMENT
// ==========================================================================

u8 Dungeon_GetCurrentRoom(void)
{
    return gSaveBlock2Ptr->dungeonCurrentRoom;
}

u8 Dungeon_GetCurrentDungeonId(void)
{
    if (!Dungeon_IsActive())
        return 0xFF;

    // Option 1: Get from temp var
    u8 dungeonId = VarGet(VAR_TEMP_0);
    if (dungeonId < DUNGEON_COUNT)
        return dungeonId;

    // Option 2: Infer from current map (fallback)
    // TODO: Implement map-based detection once maps are created
    // u16 map = gSaveBlock1Ptr->location.mapNum;
    // if (map >= MAP_DUNGEON_CAVE_ROOM1 && map <= MAP_DUNGEON_CAVE_BOSS)
    //     return DUNGEON_EARLY_CAVE;
    // ... etc

    return 0xFF; // Not in a valid dungeon
}

// Note: Dungeon_GetRewardScore() is defined as a macro in constants/dungeons.h

void Dungeon_IncrementRewardScore(u16 points)
{
    u16 newScore = Dungeon_GetRewardScore() + points;

    // Cap at 511 (9-bit max)
    if (newScore > 511)
        newScore = 511;

    Dungeon_SetRewardScore(newScore);
}

// ==========================================================================
// ROOM PROGRESSION
// ==========================================================================

void Dungeon_AdvanceToNextRoom(void)
{
    u8 nextRoom = Dungeon_GetRoom() + 1;
    Dungeon_SetRoom(nextRoom);
    Dungeon_SetTrainersDefeated(0);  // Reset for new room

    // Clear trainer flags for next room
    Dungeon_ClearTrainerFlags();

    // Determine warp destination
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return;

    if (nextRoom >= dungeon->roomCount)
    {
        // Warp to boss room
        Dungeon_WarpToBossRoom();
    }
    else
    {
        // Warp to next regular room
        Dungeon_WarpToRoom(nextRoom);
    }
}

bool8 Dungeon_IsOnBossFloor(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return FALSE;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return FALSE;

    return Dungeon_GetRoom() >= dungeon->roomCount;
}

void Dungeon_ResetRun(void)
{
    Dungeon_Exit();
}

// Internal function to warp to a specific room
static void Dungeon_WarpToRoom(u8 roomIndex)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    // TODO: Proper room selection from dungeon_rooms.h pools
    // For now, cycle through Dungeon1_Room1 through Room5 for testing
    u16 mapNum;
    switch (roomIndex % 5) {
        case 0: mapNum = MAP_NUM(MAP_DUNGEON1_ROOM1); break;
        case 1: mapNum = MAP_NUM(MAP_DUNGEON1_ROOM2); break;
        case 2: mapNum = MAP_NUM(MAP_DUNGEON1_ROOM3); break;
        case 3: mapNum = MAP_NUM(MAP_DUNGEON1_ROOM4); break;
        default: mapNum = MAP_NUM(MAP_DUNGEON1_ROOM5); break;
    }

    u8 mapGroup = MAP_GROUP(MAP_DUNGEON1_ROOM1); // All rooms in same group

    // Warp to next room (spawn at 9,8 as defined in room data)
    SetWarpDestination(mapGroup, mapNum, WARP_ID_NONE, 9, 8);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
}

// Internal function to warp to boss room
static void Dungeon_WarpToBossRoom(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    // TODO: Implement boss room warp based on dungeonId
    // For now, just loop back to Room1 as placeholder
    SetWarpDestination(MAP_GROUP(MAP_DUNGEON1_ROOM1), MAP_NUM(MAP_DUNGEON1_ROOM1), WARP_ID_NONE, 9, 8);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
}

// ==========================================================================
// TRAINER SPAWNING
// ==========================================================================

// Trainer data array (similar to The Pit)
static const struct DungeonTrainer sDungeonTrainers[DUNGEON_MAX_TRAINERS_PER_ROOM] = {
    [0] = {
        .arrayElement = 0,
        .gfxIdVar = VAR_OBJ_GFX_ID_0,
        .trainerFlag = FLAG_DUNGEON_TRAINER_0,
        .trainerId = TRAINER_WINSTON_1,  // Placeholder
    },
    [1] = {
        .arrayElement = 1,
        .gfxIdVar = VAR_OBJ_GFX_ID_1,
        .trainerFlag = FLAG_DUNGEON_TRAINER_1,
        .trainerId = TRAINER_IVAN,  // Placeholder
    },
    [2] = {
        .arrayElement = 2,
        .gfxIdVar = VAR_OBJ_GFX_ID_2,
        .trainerFlag = FLAG_DUNGEON_TRAINER_2,
        .trainerId = TRAINER_JOEY,  // Placeholder
    },
    [3] = {
        .arrayElement = 3,
        .gfxIdVar = VAR_OBJ_GFX_ID_3,
        .trainerFlag = FLAG_DUNGEON_TRAINER_3,
        .trainerId = TRAINER_JOSE,  // Placeholder
    },
};

void Dungeon_SpawnTrainers(void)
{
    // TEMPORARY: Allow spawning even when dungeon isn't active (for debug testing)
    // In production, uncomment this check:
    // u8 dungeonId = Dungeon_GetCurrentDungeonId();
    // if (dungeonId == 0xFF)
    //     return;

    // TODO: Implement trainer spawning
    // 1. Determine how many trainers to spawn (based on current room definition)
    // 2. For each trainer:
    //    - Pick random trainer class from tier pool
    //    - Set VAR_OBJ_GFX_ID_X to trainer's graphics ID
    //    - Clear FLAG_DUNGEON_TRAINER_X (makes them visible)
    // 3. For un-spawned trainer slots, set flags to hide them

    // Placeholder implementation
    u8 trainersToSpawn = Random() % (I_DUNGEON_TRAINER_COUNT_MAX - I_DUNGEON_TRAINER_COUNT_MIN + 1) + I_DUNGEON_TRAINER_COUNT_MIN;

    for (u8 i = 0; i < DUNGEON_MAX_TRAINERS_PER_ROOM; i++)
    {
        if (i < trainersToSpawn)
        {
            // Spawn this trainer
            // TODO: Set VAR_OBJ_GFX_ID based on random trainer class
            VarSet(sDungeonTrainers[i].gfxIdVar, OBJ_EVENT_GFX_BOY_1); // Placeholder
            FlagClear(sDungeonTrainers[i].trainerFlag); // Make visible
        }
        else
        {
            // Hide this trainer
            FlagSet(sDungeonTrainers[i].trainerFlag);
        }
    }
}

void Dungeon_ClearTrainerFlags(void)
{
    for (u8 i = 0; i < DUNGEON_MAX_TRAINERS_PER_ROOM; i++)
    {
        FlagClear(sDungeonTrainers[i].trainerFlag);
    }
}

u8 Dungeon_GetTrainersDefeatedThisRoom(void)
{
    return gSaveBlock2Ptr->dungeonTrainersDefeated;
}

void Dungeon_OnTrainerDefeated(void)
{
    // Increment trainers defeated counter
    u8 defeated = Dungeon_GetTrainersDefeated() + 1;
    Dungeon_SetTrainersDefeated(defeated);

    // Award reward points
    Dungeon_IncrementRewardScore(I_DUNGEON_BASE_REWARD_POINTS);
}

// ==========================================================================
// BOSS HANDLING
// ==========================================================================

void Dungeon_SpawnBoss(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return;

    // TODO: Implement boss spawning
    // 1. Get boss pool for this tier
    // 2. Pick random boss from pool
    // 3. Set up boss encounter
}

const struct DungeonBoss *Dungeon_GetCurrentBoss(void)
{
    // TODO: Implement
    return NULL;
}

// ==========================================================================
// WILD ENCOUNTERS
// ==========================================================================

void Dungeon_SetupWildEncounters(void)
{
    if (!Dungeon_IsActive())
        return;

    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return;

    // TODO: Implement wild encounter override
    // This will modify the encounter tables based on biome and level
}

const struct WildPokemonInfo *Dungeon_GetLandEncounters(void)
{
    // TODO: Implement
    // Return the appropriate land encounters for current dungeon/biome
    return NULL;
}

const struct WildPokemonInfo *Dungeon_GetWaterEncounters(void)
{
    // TODO: Implement
    // Return the appropriate water encounters for current dungeon/biome
    return NULL;
}

// ==========================================================================
// REWARDS
// ==========================================================================

void Dungeon_DistributeRewards(void)
{
    u16 tier = Dungeon_CalculateRewardTier();
    (void)tier; // Unused for now, will be used in reward implementation

    // TODO: Implement reward distribution
    // Based on tier, give items/TMs/legendary encounters

    // Placeholder: Just give some items based on score
    u16 score = Dungeon_GetRewardScore();
    if (score > 400)
    {
        // High tier rewards
        // AddBagItem(ITEM_RARE_CANDY, 3);
    }
    else if (score > 200)
    {
        // Medium tier rewards
        // AddBagItem(ITEM_RARE_CANDY, 1);
    }
    else
    {
        // Low tier rewards
        // AddBagItem(ITEM_POTION, 3);
    }
}

u16 Dungeon_CalculateRewardTier(void)
{
    u16 score = Dungeon_GetRewardScore();

    // Simple tier calculation
    // 0-170 = Tier 1 (basic rewards)
    // 171-340 = Tier 2 (good rewards)
    // 341-511 = Tier 3 (excellent rewards)

    if (score >= 341)
        return 3;
    else if (score >= 171)
        return 2;
    else
        return 1;
}

// ==========================================================================
// UTILITY FUNCTIONS
// ==========================================================================

const struct Dungeon *Dungeon_GetDefinition(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
        return NULL;

    return &sDungeons[dungeonId];
}

u8 Dungeon_GetCurrentLevel(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return 5; // Default fallback

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return 5;

    // Return base level ± random range
    s8 variance = (Random() % (dungeon->levelRange * 2 + 1)) - dungeon->levelRange;
    return dungeon->baseLevel + variance;
}

// ==========================================================================
// SCRIPT-CALLABLE WRAPPERS (for callnative)
// ==========================================================================
// These functions are designed to be called from Pory scripts using callnative.
// They communicate with scripts via gSpecialVar_0x8000 and VAR_TEMP_X.

// Called from dungeon entrance scripts
// Usage: callnative Script_Dungeon_Enter
void Script_Dungeon_Enter(void)
{
    u8 dungeonId = gSpecialVar_0x8000; // Script should set this before calling
    Dungeon_Enter(dungeonId);
}

// Initialize dungeon if not already active (called from Room1 entrance)
// Usage: callnative Script_Dungeon_InitializeIfNeeded
void Script_Dungeon_InitializeIfNeeded(void)
{
    if (!Dungeon_IsActive())
    {
        // Default to DUNGEON_EARLY_CAVE (ID 0) when entering Room1 directly
        Dungeon_Enter(0);
    }
}

// Called when exiting dungeon (whiteout, escape rope, completion)
// Usage: callnative Script_Dungeon_Exit
void Script_Dungeon_Exit(void)
{
    Dungeon_Exit();
}

// Called on room entry (MAP_SCRIPT_ON_TRANSITION)
// Usage: callnative Script_Dungeon_SpawnTrainers
void Script_Dungeon_SpawnTrainers(void)
{
    Dungeon_SpawnTrainers();
}

// Called after defeating a trainer
// Usage: callnative Script_Dungeon_OnTrainerDefeated
void Script_Dungeon_OnTrainerDefeated(void)
{
    Dungeon_OnTrainerDefeated();
}

// Check if all trainers in current room are defeated
// Sets VAR_RESULT to TRUE if room is cleared
// Usage: callnative Script_Dungeon_CheckRoomCleared
void Script_Dungeon_CheckRoomCleared(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    // Get current room definition
    // TODO: Implement once room pools are finalized
    // For now, use trainer count from config
    u8 expectedTrainers = I_DUNGEON_TRAINER_COUNT_MIN; // Placeholder
    u8 defeated = Dungeon_GetTrainersDefeated();

    gSpecialVar_Result = (defeated >= expectedTrainers);
}

// Prepare next room warp and execute teleport
// Usage: callnative Script_Dungeon_PrepareNextRoom
void Script_Dungeon_PrepareNextRoom(void)
{
    u8 nextRoom = Dungeon_GetRoom() + 1;
    Dungeon_SetRoom(nextRoom);
    Dungeon_SetTrainersDefeated(0);  // Reset for new room

    // Clear trainer flags for next room
    Dungeon_ClearTrainerFlags();

    // Determine warp destination
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return;

    // Determine which map to warp to
    u16 mapConstant;

    if (nextRoom >= dungeon->roomCount)
    {
        // Boss room
        mapConstant = MAP_DUNGEON1_ROOM_BOSS;
    }
    else
    {
        // Regular room (cycle through Room1-5)
        switch (nextRoom % 5) {
            case 0: mapConstant = MAP_DUNGEON1_ROOM1; break;
            case 1: mapConstant = MAP_DUNGEON1_ROOM2; break;
            case 2: mapConstant = MAP_DUNGEON1_ROOM3; break;
            case 3: mapConstant = MAP_DUNGEON1_ROOM4; break;
            default: mapConstant = MAP_DUNGEON1_ROOM5; break;
        }
    }

    // Extract map group and num from constant
    u8 mapGroup = MAP_GROUP(mapConstant);
    u8 mapNum = MAP_NUM(mapConstant);

    // Set warp destination and execute teleport
    // Script handles the locking and delay, we just do the warp
    SetWarpDestination(mapGroup, mapNum, WARP_ID_NONE, 9, 8);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
}

// Old function kept for compatibility (now calls prepare)
void Script_Dungeon_AdvanceToNextRoom(void)
{
    Script_Dungeon_PrepareNextRoom();
}

// Check if currently on boss floor
// Sets VAR_RESULT to TRUE if on boss floor
// Usage: callnative Script_Dungeon_IsOnBossFloor
void Script_Dungeon_IsOnBossFloor(void)
{
    gSpecialVar_Result = Dungeon_IsOnBossFloor();
}

// Spawn boss encounter
// Usage: callnative Script_Dungeon_SpawnBoss
void Script_Dungeon_SpawnBoss(void)
{
    Dungeon_SpawnBoss();
}

// Distribute rewards at end of dungeon
// Usage: callnative Script_Dungeon_DistributeRewards
void Script_Dungeon_DistributeRewards(void)
{
    Dungeon_DistributeRewards();
}

// Get reward tier (1-3) for display purposes
// Sets VAR_RESULT to reward tier
// Usage: callnative Script_Dungeon_GetRewardTier
void Script_Dungeon_GetRewardTier(void)
{
    gSpecialVar_Result = Dungeon_CalculateRewardTier();
}

// Check if dungeon is currently active
// Sets VAR_RESULT to TRUE if in dungeon
// Usage: callnative Script_Dungeon_IsActive
void Script_Dungeon_IsActive(void)
{
    gSpecialVar_Result = Dungeon_IsActive();
}

// Get current room number (0-indexed)
// Sets VAR_RESULT to current room
// Usage: callnative Script_Dungeon_GetCurrentRoom
void Script_Dungeon_GetCurrentRoom(void)
{
    gSpecialVar_Result = Dungeon_GetCurrentRoom();
}

// Get current reward score
// Sets VAR_RESULT to score (0-511)
// Usage: callnative Script_Dungeon_GetRewardScore
void Script_Dungeon_GetRewardScore(void)
{
    gSpecialVar_Result = Dungeon_GetRewardScore();
}
