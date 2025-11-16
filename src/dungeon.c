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
#include "script_pokemon_util.h"
#include "battle_setup.h"
#include "battle.h"
#include "battle_main.h"
#include "rtc.h"
#include "datetime.h"
#include "constants/dungeons.h"
#include "constants/maps.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/battle.h"
#include "constants/battle_setup.h"
#include "constants/weather.h"
#include "constants/opponents.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "config/dungeon.h"
#include "debug.h"

// Include data files
#include "data/dungeon_definitions.h"
#include "data/dungeon_rooms.h"
#include "data/dungeon_trainers.h"
#include "data/dungeon_encounters.h"
#include "data/dungeon_bosses.h"
#include "data/dungeon_narratives.h"
#include "data/dungeon_modifiers.h"

// Forward declarations for static functions
static void Dungeon_WarpToRoom(u8 roomIndex);
static void Dungeon_WarpToBossRoom(void);

// Note: Boss is now defined per narrative, not stored statically
// Use Dungeon_GetActiveNarrative()->boss instead

// ==========================================================================
// DUNGEON ENTRY/EXIT
// ==========================================================================

void Dungeon_Enter(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
    {
        DebugPrintf("Dungeon_Enter: Invalid dungeonId %d", dungeonId);
        return;
    }

    DebugPrintf("Dungeon_Enter: Entering dungeon %d", dungeonId);

    // Initialize dungeon state
    Dungeon_SetActive(TRUE);
    Dungeon_SetRoom(0);
    Dungeon_SetTrainersDefeated(0);
    Dungeon_SetRewardScore(0);

    // Store which dungeon we're in using temp var
    VarSet(VAR_TEMP_0, dungeonId);

    DebugPrintf("Dungeon_Enter: Set active, room=0, dungeonId stored in VAR_TEMP_0=%d", VarGet(VAR_TEMP_0));

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

    // Clear boss defeated flag
    FlagClear(FLAG_DUNGEON_BOSS_DEFEATED);

    // Clear inverse battle flag if it was set
    if (B_FLAG_INVERSE_BATTLE != 0)
        FlagClear(B_FLAG_INVERSE_BATTLE);

    // Hide boss objects
    FlagSet(FLAG_DUNGEON_TRAINER_0);
    FlagSet(FLAG_DUNGEON_TRAINER_1);
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
    u16 oldScore = Dungeon_GetRewardScore();
    u16 newScore = oldScore + points;

    // Cap at 127 (7-bit max)
    if (newScore > 127)
        newScore = 127;

    Dungeon_SetRewardScore(newScore);

    // Info logging (shows even without debug mode)
    u16 tier = Dungeon_CalculateRewardTier();
    const char *tierName = (tier == 3) ? "GOLD" : (tier == 2) ? "SILVER" : "BRONZE";

    MgbaPrintf(MGBA_LOG_INFO, "=== DUNGEON POINTS ===");
    MgbaPrintf(MGBA_LOG_INFO, "Gained: +%d points", points);
    MgbaPrintf(MGBA_LOG_INFO, "Total: %d points (was %d)", newScore, oldScore);
    MgbaPrintf(MGBA_LOG_INFO, "Thresholds: Bronze=0-20, Silver=21-40, Gold=41+");
    MgbaPrintf(MGBA_LOG_INFO, "Current Tier: %s (%d)", tierName, tier);
    MgbaPrintf(MGBA_LOG_INFO, "======================");
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
        .trainerIdVar = VAR_DUNGEON_TRAINER_0,
    },
    [1] = {
        .arrayElement = 1,
        .gfxIdVar = VAR_OBJ_GFX_ID_1,
        .trainerFlag = FLAG_DUNGEON_TRAINER_1,
        .trainerIdVar = VAR_DUNGEON_TRAINER_1,
    },
    [2] = {
        .arrayElement = 2,
        .gfxIdVar = VAR_OBJ_GFX_ID_2,
        .trainerFlag = FLAG_DUNGEON_TRAINER_2,
        .trainerIdVar = VAR_DUNGEON_TRAINER_2,
    },
    [3] = {
        .arrayElement = 3,
        .gfxIdVar = VAR_OBJ_GFX_ID_3,
        .trainerFlag = FLAG_DUNGEON_TRAINER_3,
        .trainerIdVar = VAR_DUNGEON_TRAINER_3,
    },
};

// Select a random trainer entry (trainerId + graphicsId pair) from the narrative pool
static struct DungeonTrainerEntry Dungeon_SelectRandomTrainer(u8 dungeonId)
{
    // Default fallback entry
    struct DungeonTrainerEntry fallback = {
        .trainerId = TRAINER_CALVIN_1,
        .graphicsId = OBJ_EVENT_GFX_YOUNGSTER
    };

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);

    if (narrative == NULL || narrative->trainerCount == 0 || narrative->trainerPool == NULL)
    {
        DebugPrintf("WARNING: Invalid narrative or empty trainer pool for dungeon %d", dungeonId);
        return fallback;
    }

    // Select random trainer from pool
    u32 randomValue = Random();
    u8 index = randomValue % narrative->trainerCount;
    struct DungeonTrainerEntry entry = narrative->trainerPool[index];

    DebugPrintf("Random trainer: value=%u, count=%d, index=%d, ID=%d, gfx=%d",
        randomValue, narrative->trainerCount, index, entry.trainerId, entry.graphicsId);

    // Validate trainer ID is in valid range
    if (entry.trainerId >= TRAINERS_COUNT)
    {
        DebugPrintf("ERROR: Invalid trainer ID %d selected from pool", entry.trainerId);
        return fallback;
    }

    return entry;
}

// Clear trainer defeated flags so trainers can be rebattled in new rooms
static void Dungeon_ClearTrainerDefeatedFlags(u8 dungeonId)
{
    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);

    if (narrative == NULL || narrative->trainerCount == 0 || narrative->trainerPool == NULL)
        return;

    // Clear defeated flags for all trainers in the narrative pool
    for (u8 i = 0; i < narrative->trainerCount; i++)
    {
        u16 trainerId = narrative->trainerPool[i].trainerId;
        u16 trainerFlag = TRAINER_FLAGS_START + trainerId;
        FlagClear(trainerFlag);
    }
}

void Dungeon_SpawnTrainers(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();

    // TEMPORARY: Allow spawning even when dungeon isn't active (for debug testing)
    if (dungeonId == 0xFF)
        dungeonId = DUNGEON_EARLY_CAVE; // Default to cave for testing

    // FIRST: Hide all trainers by setting their flags (must do this BEFORE map loads objects)
    for (u8 i = 0; i < DUNGEON_MAX_TRAINERS_PER_ROOM; i++)
    {
        FlagSet(sDungeonTrainers[i].trainerFlag);
    }

    // Clear trainer defeated flags so trainers can be rebattled
    Dungeon_ClearTrainerDefeatedFlags(dungeonId);

    // Determine how many trainers to spawn
    u8 trainersToSpawn = Random() % (I_DUNGEON_TRAINER_COUNT_MAX - I_DUNGEON_TRAINER_COUNT_MIN + 1) + I_DUNGEON_TRAINER_COUNT_MIN;

    DebugPrintf("Spawning %d trainers in dungeon %d", trainersToSpawn, dungeonId);

    for (u8 i = 0; i < DUNGEON_MAX_TRAINERS_PER_ROOM; i++)
    {
        if (i < trainersToSpawn)
        {
            // Select random trainer entry (paired trainerId + graphicsId)
            struct DungeonTrainerEntry entry = Dungeon_SelectRandomTrainer(dungeonId);

            DebugPrintf("Slot %d: trainerId=%d, graphicsId=%d, trainerVar=0x%04X, gfxVar=0x%04X",
                i, entry.trainerId, entry.graphicsId, sDungeonTrainers[i].trainerIdVar, sDungeonTrainers[i].gfxIdVar);

            // Store trainer ID in variable for battle script to use
            VarSet(sDungeonTrainers[i].trainerIdVar, entry.trainerId);

            // Set graphics for overworld sprite
            VarSet(sDungeonTrainers[i].gfxIdVar, entry.graphicsId);

            // Make trainer visible (clear flag so object spawns)
            FlagClear(sDungeonTrainers[i].trainerFlag);
        }
        else
        {
            DebugPrintf("Slot %d: Hidden (not spawning)", i);

            // Initialize variables to safe values for unspawned trainers (in case of bugs)
            VarSet(sDungeonTrainers[i].trainerIdVar, TRAINER_CALVIN_1);
            VarSet(sDungeonTrainers[i].gfxIdVar, OBJ_EVENT_GFX_BOY_1);

            // Keep this trainer slot hidden (flag remains SET)
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
    Dungeon_IncrementRewardScore(DUNGEON_POINTS_PER_TRAINER);
}

// ==========================================================================
// BOSS HANDLING
// ==========================================================================

void Dungeon_SpawnBoss(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    // Get active narrative (boss is defined per narrative, not per tier)
    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL)
        return;

    MgbaPrintf(MGBA_LOG_INFO, "Dungeon_SpawnBoss: narrative=%d, bossType=%d", narrative->id, narrative->bossType);

    // Spawn boss based on narrative's boss type
    if (narrative->bossType == BOSS_TYPE_TRAINER)
    {
        // Trainer boss from narrative
        MgbaPrintf(MGBA_LOG_INFO, "Dungeon_SpawnBoss: Trainer boss, trainerId=%d, graphicsId=%d",
            narrative->boss.trainer.trainerId, narrative->boss.trainer.graphicsId);

        // Store trainer ID in dedicated boss var
        VarSet(VAR_DUNGEON_BOSS_TRAINER, narrative->boss.trainer.trainerId);

        // Set trainer overworld sprite (VAR_OBJ_GFX_ID_4 for boss trainer)
        if (narrative->boss.trainer.graphicsId != 0)
            VarSet(VAR_OBJ_GFX_ID_4, narrative->boss.trainer.graphicsId);
        else
            VarSet(VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_HIKER);  // Default

        // The trainer boss object in map.json uses FLAG_DUNGEON_BOSS_DEFEATED
        // We don't need to do anything here for visibility - it's automatic
    }
    else if (narrative->bossType == BOSS_TYPE_POKEMON)
    {
        // Pokemon boss from narrative (simplified - just species/level/item)
        MgbaPrintf(MGBA_LOG_INFO, "Dungeon_SpawnBoss: Pokemon boss, species=%d, level=%d",
            narrative->boss.pokemon.species, narrative->boss.pokemon.level);

        // Set Pokemon overworld sprite (VAR_OBJ_GFX_ID_5 for boss pokemon)
        // Use species-specific graphics: OBJ_EVENT_GFX_SPECIES(species) = species + OBJ_EVENT_MON
        u16 speciesGfxId = narrative->boss.pokemon.species + OBJ_EVENT_MON;
        VarSet(VAR_OBJ_GFX_ID_5, speciesGfxId);

        // The pokemon boss object in map.json uses FLAG_DUNGEON_BOSS_DEFEATED
        // We don't need to do anything here for visibility - it's automatic
        // Note: The actual Pokemon encounter is created in Script_Dungeon_StartBossPokemonBattle()
        // using the narrative's boss.pokemon data
    }
    else
    {
        // BOSS_TYPE_NONE - no boss for this narrative
        MgbaPrintf(MGBA_LOG_INFO, "Dungeon_SpawnBoss: No boss (type=BOSS_TYPE_NONE)");
    }
}

const struct DungeonBoss *Dungeon_GetCurrentBoss(void)
{
    // Note: This function is deprecated - boss data is now in narrative
    // Kept for backward compatibility but returns NULL
    // Use Dungeon_GetActiveNarrative()->boss instead
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
    if (!Dungeon_IsActive())
        return NULL;

    // IMPORTANT: Also check if we're actually on a dungeon map
    // This prevents dungeon encounters from persisting if player warps out or whites out
    // without going through the entrance (which would clear the active flag)
    u16 currentMap = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    bool8 isOnDungeonMap = (currentMap >= MAP_DUNGEON1_ROOM1 && currentMap <= MAP_DUNGEON1_ROOM_END);

    if (!isOnDungeonMap)
    {
        // Auto-clear dungeon state since we're not in a dungeon anymore
        Dungeon_Exit();
        return NULL;
    }

    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);

    if (narrative == NULL)
        return NULL;

    return narrative->landEncounters;
}

const struct WildPokemonInfo *Dungeon_GetWaterEncounters(void)
{
    if (!Dungeon_IsActive())
        return NULL;

    // IMPORTANT: Also check if we're actually on a dungeon map
    // This prevents dungeon encounters from persisting if player warps out or whites out
    u16 currentMap = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    bool8 isOnDungeonMap = (currentMap >= MAP_DUNGEON1_ROOM1 && currentMap <= MAP_DUNGEON1_ROOM_END);

    if (!isOnDungeonMap)
    {
        // Auto-clear dungeon state since we're not in a dungeon anymore
        Dungeon_Exit();
        return NULL;
    }

    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);

    if (narrative == NULL)
        return NULL;

    return narrative->waterEncounters;
}

// ==========================================================================
// REWARDS
// ==========================================================================

void Dungeon_DistributeRewards(void)
{
    // Get current dungeon and narrative
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        DebugPrintf("Dungeon_DistributeRewards: Not in a valid dungeon");
        gSpecialVar_Result = FALSE;
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL)
    {
        DebugPrintf("Dungeon_DistributeRewards: No active narrative");
        gSpecialVar_Result = FALSE;
        return;
    }

    // Check if narrative has rewards defined
    if (narrative->rewardItems == NULL || narrative->rewardTierCount == 0)
    {
        DebugPrintf("Dungeon_DistributeRewards: Narrative has no rewards defined");
        gSpecialVar_Result = FALSE;
        return;
    }

    // Calculate reward tier (1-3)
    u16 tier = Dungeon_CalculateRewardTier();

    // Convert tier to array index (tier 1 = index 0, tier 2 = index 1, tier 3 = index 2)
    u8 rewardIndex = tier - 1;

    // Clamp index to available tiers
    if (rewardIndex >= narrative->rewardTierCount)
        rewardIndex = narrative->rewardTierCount - 1;

    // Get the reward item for this tier
    u16 itemId = narrative->rewardItems[rewardIndex];

    DebugPrintf("Dungeon_DistributeRewards: score=%d, tier=%d, itemId=%d",
                Dungeon_GetRewardScore(), tier, itemId);

    // Check if bag has space
    if (!CheckBagHasSpace(itemId, 1))
    {
        DebugPrintf("Dungeon_DistributeRewards: Bag full, cannot give item");
        gSpecialVar_Result = FALSE;
        gSpecialVar_0x8004 = itemId; // Store item ID for script to display "bag full" message
        return;
    }

    // Give the item to the player
    if (AddBagItem(itemId, 1))
    {
        DebugPrintf("Dungeon_DistributeRewards: Successfully gave item %d", itemId);
        gSpecialVar_Result = TRUE;
        gSpecialVar_0x8004 = itemId; // Store item ID for script to display reward message
    }
    else
    {
        DebugPrintf("Dungeon_DistributeRewards: Failed to give item %d", itemId);
        gSpecialVar_Result = FALSE;
        gSpecialVar_0x8004 = itemId;
    }
}

u16 Dungeon_CalculateRewardTier(void)
{
    u16 score = Dungeon_GetRewardScore();

    // Tier calculation based on performance
    // 0-20 = Tier 1 (Bronze) - Boss only
    // 21-40 = Tier 2 (Silver) - Boss + 1-5 trainers
    // 41+ = Tier 3 (Gold) - Boss + 6+ trainers (or many catches)

    if (score >= 41)
        return 3;
    else if (score >= 21)
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
// NARRATIVE SYSTEM
// ==========================================================================

// Generate daily seed based on current RTC date
u16 Dungeon_GetDailySeed(void)
{
    struct DateTime dateTime;

    RtcCalcLocalTime();
    ConvertTimeToDateTime(&dateTime, &gLocalTime);

    // Create seed from year/month/day
    // This ensures the seed changes once per day
    u16 seed = (dateTime.year << 9)
             | (dateTime.month << 5)
             | (dateTime.day);

    return seed;
}

// Select narrative for a dungeon based on seed
static u8 Dungeon_SelectNarrative(u8 dungeonId, u16 seed)
{
    if (dungeonId >= DUNGEON_COUNT)
        return NARRATIVE_NONE;

    // Get narrative pool for this dungeon
    const u8 *pool = sDungeonNarrativePools[dungeonId];
    u8 count = sDungeonNarrativePoolCounts[dungeonId];

    if (count == 0)
        return NARRATIVE_NONE;

    // Use seed to select narrative
    return pool[seed % count];
}

// Select modifier for a dungeon based on seed
static u8 Dungeon_SelectModifier(u8 dungeonId, u16 seed)
{
    if (dungeonId >= DUNGEON_COUNT)
        return MODIFIER_NONE;

    // Get modifier pool for this dungeon
    const u8 *pool = sDungeonModifierPools[dungeonId];
    u8 count = sDungeonModifierPoolCounts[dungeonId];

    if (count == 0)
        return MODIFIER_NONE;

    // Use seed to select modifier (offset by 7 to get different result than narrative)
    return pool[(seed + 7) % count];
}

// Check if daily rotation needs to be updated
void Dungeon_CheckDailyRotation(void)
{
#if I_DUNGEON_DAILY_ROTATION == FALSE
    return; // Daily rotation disabled
#endif

    u16 currentSeed = Dungeon_GetDailySeed();
    bool8 needsInit = FALSE;

    // Check if this is first run (seed is 0 or narratives/modifiers look uninitialized)
    if (gSaveBlock2Ptr->dungeonDailySeed == 0)
        needsInit = TRUE;

    // Check if any modifier is invalid (indicates uninitialized save data)
    for (u8 i = 0; i < DUNGEON_COUNT; i++)
    {
        if (gSaveBlock2Ptr->dungeonModifiers[i] >= MODIFIER_COUNT)
            needsInit = TRUE;
    }

    // Check if seed has changed (new day) or needs initialization
    if (needsInit || gSaveBlock2Ptr->dungeonDailySeed != currentSeed)
    {
        // Update seed
        gSaveBlock2Ptr->dungeonDailySeed = currentSeed;

        // Update narratives and modifiers for all dungeons
        for (u8 i = 0; i < DUNGEON_COUNT; i++)
        {
            gSaveBlock2Ptr->dungeonNarratives[i] = Dungeon_SelectNarrative(i, currentSeed);
            gSaveBlock2Ptr->dungeonModifiers[i] = Dungeon_SelectModifier(i, currentSeed);
        }
    }
}

// Get active narrative for a dungeon
const struct DungeonNarrative *Dungeon_GetActiveNarrative(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
        return NULL;

#if I_DUNGEON_DEBUG_MODE == TRUE
    // Debug mode: Force specific narrative for testing
    u8 narrativeId = I_DUNGEON_DEBUG_NARRATIVE;
#else
    // Production: Use daily rotation system
    u8 narrativeId = gSaveBlock2Ptr->dungeonNarratives[dungeonId];
#endif

    if (narrativeId >= NARRATIVE_COUNT)
        return NULL;

    return &gDungeonNarratives[narrativeId];
}

// Get active modifier for a dungeon
const struct DungeonModifier *Dungeon_GetActiveModifier(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
        return NULL;

#if I_DUNGEON_DEBUG_MODE == TRUE
    // Debug mode: Force specific modifier for testing
    u8 modifierId = I_DUNGEON_DEBUG_MODIFIER;
#else
    // Production: Use daily rotation system
    u8 modifierId = gSaveBlock2Ptr->dungeonModifiers[dungeonId];
#endif

    if (modifierId >= MODIFIER_COUNT)
        return NULL;

    return &gDungeonModifiers[modifierId];
}

// Display entrance info (narrative + modifier) for a dungeon
void Dungeon_ShowEntranceInfo(u8 dungeonId)
{
    static const u8 sText_Challenge[] = _("CHALLENGE: ");
    static const u8 sText_Modifier[] = _("\pMODIFIER: ");
    static const u8 sText_Newline[] = _("\n");

    const struct DungeonNarrative *narrative;
    const struct DungeonModifier *modifier;
    u8 buffer[300];

    // Check for daily rotation first
    Dungeon_CheckDailyRotation();

    // Get active narrative and modifier
    narrative = Dungeon_GetActiveNarrative(dungeonId);
    modifier = Dungeon_GetActiveModifier(dungeonId);

    if (narrative == NULL || modifier == NULL)
        return;

    // Build message manually
    StringCopy(buffer, sText_Challenge);
    StringAppend(buffer, narrative->name);
    StringAppend(buffer, sText_Newline);
    StringAppend(buffer, narrative->description);
    StringAppend(buffer, sText_Modifier);
    StringAppend(buffer, modifier->name);
    StringAppend(buffer, sText_Newline);
    StringAppend(buffer, modifier->description);

    // Copy to gStringVar4 for script to display
    StringCopy(gStringVar4, buffer);
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

// Called from dungeon entrance scripts to display narrative/modifier info
// Usage: setvar VAR_0x8000, DUNGEON_EARLY_CAVE
//        callnative Script_Dungeon_ShowEntranceInfo
//        msgbox gStringVar4, MSGBOX_DEFAULT
void Script_Dungeon_ShowEntranceInfo(void)
{
    u8 dungeonId = gSpecialVar_0x8000; // Script should set this before calling
    Dungeon_ShowEntranceInfo(dungeonId);
}

// Initialize dungeon if not already active (called from Room1 entrance)
// Usage: callnative Script_Dungeon_InitializeIfNeeded
void Script_Dungeon_InitializeIfNeeded(void)
{
    bool8 wasActive = Dungeon_IsActive();
    DebugPrintf("Script_Dungeon_InitializeIfNeeded: wasActive=%d", wasActive);

    if (!wasActive)
    {
        // Default to DUNGEON_EARLY_CAVE (ID 0) when entering Room1 directly
        Dungeon_Enter(0);
        DebugPrintf("Script_Dungeon_InitializeIfNeeded: Called Dungeon_Enter(0), now active=%d", Dungeon_IsActive());
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
    // Use center of map (10, 10) for 20x20 boss room, (7, 7) for 15x15 regular rooms
    u8 x = (mapConstant == MAP_DUNGEON1_ROOM_BOSS) ? 10 : 9;
    u8 y = (mapConstant == MAP_DUNGEON1_ROOM_BOSS) ? 10 : 8;
    SetWarpDestination(mapGroup, mapNum, WARP_ID_NONE, x, y);
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

// Prepare boss Pokemon battle (sets up the encounter, but doesn't start it)
// Script should call dowildbattle after this to actually start the battle
// Usage: callnative Script_Dungeon_StartBossPokemonBattle
void Script_Dungeon_StartBossPokemonBattle(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL || narrative->bossType != BOSS_TYPE_POKEMON)
        return;

    // Note: Narrative only has simplified Pokemon boss data (species/level/item)
    // Full boss Pokemon features (double battles, custom moves, field effects) not yet supported
    u16 species = narrative->boss.pokemon.species;
    u8 level = narrative->boss.pokemon.level;
    u16 heldItem = narrative->boss.pokemon.heldItem;

    MgbaPrintf(MGBA_LOG_INFO, "Script_Dungeon_StartBossPokemonBattle: species=%d, level=%d, item=%d",
        species, level, heldItem);

    // Create wild Pokemon encounter
    // The script will call dowildbattle after this to start the battle
    CreateScriptedWildMon(species, level, heldItem);

    // Apply totem boosts if any
    // Note: Narrative has totemBoosts[7] array but no struct - just copy values
    // TODO: Apply boosts from narrative->boss.pokemon.totemBoosts[]
}

// Load custom trainer text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossTrainerText
void Script_Dungeon_GetBossTrainerText(void)
{
    // Note: Narrative trainer bosses use the trainer's default text from trainers.party
    // Custom text not supported in narrative struct yet
    // Function kept for compatibility but does nothing
}

// Load custom Pokemon intro text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossPokemonText
void Script_Dungeon_GetBossPokemonText(void)
{
    // Note: Narrative Pokemon bosses don't have custom text yet
    // Function kept for compatibility but does nothing
}

// Load custom Pokemon defeat text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossPokemonDefeatText
void Script_Dungeon_GetBossPokemonDefeatText(void)
{
    // Note: Narrative Pokemon bosses don't have custom text yet
    // Function kept for compatibility but does nothing
}

// Get active boss type from narrative
// Sets VAR_RESULT to boss type (BOSS_TYPE_TRAINER, BOSS_TYPE_POKEMON, or BOSS_TYPE_NONE)
// Usage: callnative Script_Dungeon_GetBossType
void Script_Dungeon_GetBossType(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_Result = BOSS_TYPE_NONE;
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL)
    {
        gSpecialVar_Result = BOSS_TYPE_NONE;
        return;
    }

    gSpecialVar_Result = narrative->bossType;
}

// Get boss Pokemon species from active narrative
// Sets VAR_0x8004 to species ID
// Usage: callnative Script_Dungeon_GetBossPokemonSpecies
void Script_Dungeon_GetBossPokemonSpecies(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_0x8004 = SPECIES_NONE;
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL || narrative->bossType != BOSS_TYPE_POKEMON)
    {
        gSpecialVar_0x8004 = SPECIES_NONE;
        return;
    }

    gSpecialVar_0x8004 = narrative->boss.pokemon.species;
}

// Get boss Pokemon level from active narrative
// Sets VAR_0x8004 to level
// Usage: callnative Script_Dungeon_GetBossPokemonLevel
void Script_Dungeon_GetBossPokemonLevel(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_0x8004 = 50;  // Default level
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL || narrative->bossType != BOSS_TYPE_POKEMON)
    {
        gSpecialVar_0x8004 = 50;  // Default level
        return;
    }

    gSpecialVar_0x8004 = narrative->boss.pokemon.level;
}

// Get boss Pokemon held item from active narrative
// Sets VAR_0x8004 to item ID
// Usage: callnative Script_Dungeon_GetBossPokemonItem
void Script_Dungeon_GetBossPokemonItem(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_0x8004 = ITEM_NONE;
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL || narrative->bossType != BOSS_TYPE_POKEMON)
    {
        gSpecialVar_0x8004 = ITEM_NONE;
        return;
    }

    gSpecialVar_0x8004 = narrative->boss.pokemon.heldItem;
}

// Handle boss defeat (trainer or boss Pokemon)
// Usage: callnative Script_Dungeon_OnBossDefeated
void Script_Dungeon_OnBossDefeated(void)
{
    // Award bonus points for defeating boss
    Dungeon_IncrementRewardScore(DUNGEON_POINTS_BOSS_TRAINER);

    // Hide both boss objects
    FlagSet(FLAG_DUNGEON_TRAINER_0);  // Hide trainer
    FlagSet(FLAG_DUNGEON_TRAINER_1);  // Hide Pokemon

    // Warp to end room for rewards
    SetWarpDestination(MAP_GROUP(MAP_DUNGEON1_ROOM_END), MAP_NUM(MAP_DUNGEON1_ROOM_END), WARP_ID_NONE, 9, 8);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
}

// Spawn reward items in boss room (instead of warping to end room)
// Usage: callnative Script_Dungeon_OnBossDefeated_SpawnRewards
void Script_Dungeon_OnBossDefeated_SpawnRewards(void)
{
    // Award bonus points for defeating boss
    Dungeon_IncrementRewardScore(DUNGEON_POINTS_BOSS_TRAINER);

    // Clear flags to show reward item balls (FLAGS_DUNGEON_TRAINER_0/1/2)
    FlagClear(FLAG_DUNGEON_TRAINER_0);  // Bronze reward
    FlagClear(FLAG_DUNGEON_TRAINER_1);  // Silver reward
    FlagClear(FLAG_DUNGEON_TRAINER_2);  // Gold reward

    // Clear flag to show Psychic teleport NPC
    FlagClear(FLAG_DUNGEON_TRAINER_3);
}

// Get individual reward item by tier index
// Reads tier index from VAR_TEMP_0, sets item ID in VAR_0x8004
// Usage: setvar VAR_TEMP_0, <tier_index>
//        callnative Script_Dungeon_GetRewardItem
void Script_Dungeon_GetRewardItem(void)
{
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
    {
        gSpecialVar_0x8004 = ITEM_NONE;
        return;
    }

    const struct DungeonNarrative *narrative = Dungeon_GetActiveNarrative(dungeonId);
    if (narrative == NULL || narrative->rewardItems == NULL || narrative->rewardTierCount == 0)
    {
        gSpecialVar_0x8004 = ITEM_NONE;
        return;
    }

    // Get tier index from VAR_TEMP_0 (0 = bronze, 1 = silver, 2 = gold)
    u8 tierIndex = VarGet(VAR_TEMP_0);

    // Clamp to available tiers
    if (tierIndex >= narrative->rewardTierCount)
        tierIndex = narrative->rewardTierCount - 1;

    // Set item ID
    gSpecialVar_0x8004 = narrative->rewardItems[tierIndex];
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

// Shared text strings for dungeon trainer battles
static const u8 sDungeonTrainerIntro[] = _("Let's battle!");
static const u8 sDungeonTrainerDefeated[] = _("I lost!");

// Setup trainer battle with dynamic trainer ID
// Usage: setvar VAR_0x8000, <trainer_slot_index>
//        callnative Script_Dungeon_SetupTrainerBattle
//        dotrainerbattle
//        gotopostbattlescript
// gSpecialVar_0x8000 should contain the trainer slot index (0-3)
void Script_Dungeon_SetupTrainerBattle(void)
{
    u8 trainerSlot = gSpecialVar_0x8000;  // Which trainer slot (0-3)

    DebugPrintf("SetupTrainerBattle: slot=%d", trainerSlot);

    // Bounds check
    if (trainerSlot >= DUNGEON_MAX_TRAINERS_PER_ROOM)
    {
        DebugPrintf("ERROR: Invalid trainer slot %d", trainerSlot);
        return;
    }

    // Get trainer ID from the appropriate variable
    u16 trainerId = VarGet(sDungeonTrainers[trainerSlot].trainerIdVar);

    DebugPrintf("SetupTrainerBattle: trainerId=%d from var 0x%04X", trainerId, sDungeonTrainers[trainerSlot].trainerIdVar);

    // Validate trainer ID
    if (trainerId == 0 || trainerId >= TRAINERS_COUNT)
    {
        DebugPrintf("ERROR: Invalid trainer ID %d, using fallback", trainerId);
        trainerId = TRAINER_CALVIN_1;
    }

    // Initialize battle parameters
    memset(gTrainerBattleParameter.data, 0, sizeof(TrainerBattleParameter));

    // Set up single trainer battle with continue script
    TRAINER_BATTLE_PARAM.mode = TRAINER_BATTLE_CONTINUE_SCRIPT;
    TRAINER_BATTLE_PARAM.playMusicA = TRUE;
    TRAINER_BATTLE_PARAM.isDoubleBattle = FALSE;
    TRAINER_BATTLE_PARAM.isRematch = FALSE;

    TRAINER_BATTLE_PARAM.objEventLocalIdA = gSpecialVar_LastTalked; // The trainer NPC
    TRAINER_BATTLE_PARAM.opponentA = trainerId;                      // Dynamic trainer ID
    TRAINER_BATTLE_PARAM.introTextA = (u8 *)sDungeonTrainerIntro;   // Intro text (cast away const)
    TRAINER_BATTLE_PARAM.defeatTextA = (u8 *)sDungeonTrainerDefeated; // Defeat text (cast away const)
    TRAINER_BATTLE_PARAM.battleScriptRetAddrA = NULL;                // No post-battle script (will use gotopostbattlescript)

    // Trainer B fields (not used for single battles)
    TRAINER_BATTLE_PARAM.objEventLocalIdB = LOCALID_NONE;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_NONE;
    TRAINER_BATTLE_PARAM.introTextB = NULL;
    TRAINER_BATTLE_PARAM.defeatTextB = NULL;
    TRAINER_BATTLE_PARAM.battleScriptRetAddrB = NULL;

    // No victory/cannot battle text needed
    TRAINER_BATTLE_PARAM.victoryText = NULL;
    TRAINER_BATTLE_PARAM.cannotBattleText = NULL;
}

// ==========================================================================
// MODIFIER APPLICATION
// ==========================================================================

void Dungeon_ApplyModifierForBattle(void)
{
    // Check if we're in an active dungeon
    if (!Dungeon_IsActive())
    {
        // Not in dungeon, clear inverse battle flag if it was set
        if (B_FLAG_INVERSE_BATTLE != 0 && FlagGet(B_FLAG_INVERSE_BATTLE))
            FlagClear(B_FLAG_INVERSE_BATTLE);
        return;
    }

    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    // Get the active modifier for this dungeon
    const struct DungeonModifier *modifier = Dungeon_GetActiveModifier(dungeonId);
    if (modifier == NULL || modifier->id == MODIFIER_NONE)
    {
        // No modifier active, clear vars just in case
        VarSet(B_VAR_STARTING_STATUS, 0);
        VarSet(B_VAR_STARTING_STATUS_TIMER, 0);
        if (B_FLAG_INVERSE_BATTLE != 0)
            FlagClear(B_FLAG_INVERSE_BATTLE);
        return;
    }

    DebugPrintf("Applying dungeon modifier: %s", modifier->name);

    // Apply weather/terrain via B_VAR_STARTING_STATUS
    if (modifier->weatherOrTerrain != 0)
    {
        VarSet(B_VAR_STARTING_STATUS, modifier->weatherOrTerrain);
        VarSet(B_VAR_STARTING_STATUS_TIMER, modifier->weatherDuration);
        DebugPrintf("Set starting status: %d (duration: %d)",
                    modifier->weatherOrTerrain, modifier->weatherDuration);
    }

    // Apply battle type flags
    if (modifier->battleTypeFlags != 0)
    {
        gBattleTypeFlags |= modifier->battleTypeFlags;
        DebugPrintf("Added battle flags: 0x%04X", modifier->battleTypeFlags);
    }

    // Handle inverse battle modifier specially (uses a flag, not gBattleTypeFlags)
    if (B_FLAG_INVERSE_BATTLE != 0)
    {
        if (modifier->id == MODIFIER_INVERSE_BATTLE)
        {
            FlagSet(B_FLAG_INVERSE_BATTLE);
            DebugPrintf("Enabled inverse battle mode");
        }
        else
        {
            FlagClear(B_FLAG_INVERSE_BATTLE);
        }
    }

    // Note: Level modifiers, exp multipliers, and money multipliers
    // will be handled in separate hooks during battle calculations
}
