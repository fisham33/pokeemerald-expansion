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
#include "constants/weather.h"
#include "config/dungeon.h"

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

// Static storage for current boss (persists during dungeon run)
static const struct DungeonBoss *sCurrentBoss = NULL;

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
    Dungeon_IncrementRewardScore(DUNGEON_POINTS_PER_TRAINER);
}

// ==========================================================================
// BOSS HANDLING
// ==========================================================================

void Dungeon_SpawnBoss(void)
{
    // Get current dungeon and select random boss from tier pool
    u8 dungeonId = Dungeon_GetCurrentDungeonId();
    if (dungeonId == 0xFF)
        return;

    const struct Dungeon *dungeon = Dungeon_GetDefinition(dungeonId);
    if (dungeon == NULL)
        return;

    // Get boss pool for this tier
    const struct BossPoolEntry *pool = &sBossPools[dungeon->tier];
    if (pool->count == 0)
        return;

    // Select random boss from pool
    u8 bossIndex = Random() % pool->count;
    sCurrentBoss = pool->bosses[bossIndex];

    // Set up vars based on encounter type
    if (sCurrentBoss->encounterType == DUNGEON_BOSS_TRAINER)
    {
        // Trainer battle
        const struct BossTrainer *trainer = &sCurrentBoss->data.trainer;
        VarSet(VAR_TEMP_1, trainer->trainerId);
        VarSet(VAR_TEMP_3, 0);  // 0 = trainer

        // Set trainer overworld sprite (VAR_OBJ_GFX_ID_0 = object 1 in map)
        if (trainer->graphicsId != 0)
            VarSet(VAR_OBJ_GFX_ID_0, trainer->graphicsId);
        else
            VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_HIKER);  // Default trainer sprite

        // Make trainer visible, Pokemon hidden
        FlagClear(FLAG_DUNGEON_TRAINER_0);  // Trainer object visible
        FlagSet(FLAG_DUNGEON_TRAINER_1);    // Pokemon object hidden
    }
    else // DUNGEON_BOSS_POKEMON (Boss Pokemon)
    {
        // Boss Pokemon encounter
        const struct BossPokemon *pokemon = &sCurrentBoss->data.pokemon;

        // Check if double battle
        bool8 isDouble = (pokemon->species2 != SPECIES_NONE);

        VarSet(VAR_TEMP_3, isDouble ? 2 : 1);  // 1 = single, 2 = double

        // Set Pokemon overworld sprite (VAR_OBJ_GFX_ID_1 = object 2 in map)
        VarSet(VAR_OBJ_GFX_ID_1, pokemon->graphicsId);

        // Make Pokemon visible, trainer hidden
        FlagSet(FLAG_DUNGEON_TRAINER_0);    // Trainer object hidden
        FlagClear(FLAG_DUNGEON_TRAINER_1);  // Pokemon object visible
    }
}

const struct DungeonBoss *Dungeon_GetCurrentBoss(void)
{
    return sCurrentBoss;
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

    u8 narrativeId = gSaveBlock2Ptr->dungeonNarratives[dungeonId];

    if (narrativeId >= NARRATIVE_COUNT)
        return NULL;

    return &gDungeonNarratives[narrativeId];
}

// Get active modifier for a dungeon
const struct DungeonModifier *Dungeon_GetActiveModifier(u8 dungeonId)
{
    if (dungeonId >= DUNGEON_COUNT)
        return NULL;

    u8 modifierId = gSaveBlock2Ptr->dungeonModifiers[dungeonId];

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

// Start boss Pokemon battle
// Usage: callnative Script_Dungeon_StartBossPokemonBattle
void Script_Dungeon_StartBossPokemonBattle(void)
{
    const struct DungeonBoss *boss = Dungeon_GetCurrentBoss();
    if (boss == NULL || boss->encounterType != DUNGEON_BOSS_POKEMON)
        return;

    const struct BossPokemon *pokemon = &boss->data.pokemon;
    bool8 isDouble = (pokemon->species2 != SPECIES_NONE);

    // Step 1: Apply field effects BEFORE creating Pokemon
    const struct BossFieldEffect *fieldEffect = &pokemon->fieldEffect;
    if (fieldEffect->weather != WEATHER_NONE)
    {
        // Set weather (will be applied when battle starts)
        gBattleWeather = 0;
        switch (fieldEffect->weather)
        {
            case WEATHER_RAIN:
            case WEATHER_RAIN_THUNDERSTORM:
                gBattleWeather = B_WEATHER_RAIN;
                break;
            case WEATHER_SANDSTORM:
                gBattleWeather = B_WEATHER_SANDSTORM;
                break;
            case WEATHER_SUNNY:
                gBattleWeather = B_WEATHER_SUN;
                break;
            case WEATHER_FOG_HORIZONTAL:
            case WEATHER_FOG_DIAGONAL:
                gBattleWeather = B_WEATHER_FOG;
                break;
            case WEATHER_SNOW:
                gBattleWeather = B_WEATHER_HAIL;
                break;
        }
    }

    if (fieldEffect->terrain != 0)
    {
        // Set terrain (field status flags)
        switch (fieldEffect->terrain)
        {
            case 1:  // Electric Terrain
                gFieldStatuses = STATUS_FIELD_ELECTRIC_TERRAIN;
                gFieldTimers.terrainTimer = 5;
                break;
            case 2:  // Grassy Terrain
                gFieldStatuses = STATUS_FIELD_GRASSY_TERRAIN;
                gFieldTimers.terrainTimer = 5;
                break;
            case 3:  // Misty Terrain
                gFieldStatuses = STATUS_FIELD_MISTY_TERRAIN;
                gFieldTimers.terrainTimer = 5;
                break;
            case 4:  // Psychic Terrain
                gFieldStatuses = STATUS_FIELD_PSYCHIC_TERRAIN;
                gFieldTimers.terrainTimer = 5;
                break;
        }
    }

    // Step 2: Set totem boosts (must be done BEFORE creating wild Pokemon)
    // This follows the script pattern: settotemboost -> setwildbattle -> dowildbattle
    u8 battler = isDouble ? B_POSITION_OPPONENT_LEFT : B_POSITION_OPPONENT_RIGHT;
    const struct TotemBoosts *boosts = &pokemon->boosts;

    // Clear existing boosts first
    gQueuedStatBoosts[battler].stats = 0;
    for (u8 i = 0; i < NUM_BATTLE_STATS - 1; i++)
        gQueuedStatBoosts[battler].statChanges[i] = 0;

    // Set stat boosts if any are non-zero (following settotemboost macro pattern)
    bool8 hasBoosts = FALSE;
    if (boosts->atk != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 0);
        gQueuedStatBoosts[battler].statChanges[0] = boosts->atk;
        hasBoosts = TRUE;
    }
    if (boosts->def != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 1);
        gQueuedStatBoosts[battler].statChanges[1] = boosts->def;
        hasBoosts = TRUE;
    }
    if (boosts->speed != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 2);
        gQueuedStatBoosts[battler].statChanges[2] = boosts->speed;
        hasBoosts = TRUE;
    }
    if (boosts->spatk != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 3);
        gQueuedStatBoosts[battler].statChanges[3] = boosts->spatk;
        hasBoosts = TRUE;
    }
    if (boosts->spdef != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 4);
        gQueuedStatBoosts[battler].statChanges[4] = boosts->spdef;
        hasBoosts = TRUE;
    }
    if (boosts->acc != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 5);
        gQueuedStatBoosts[battler].statChanges[5] = boosts->acc;
        hasBoosts = TRUE;
    }
    if (boosts->evas != 0)
    {
        gQueuedStatBoosts[battler].stats |= (1 << 6);
        gQueuedStatBoosts[battler].statChanges[6] = boosts->evas;
        hasBoosts = TRUE;
    }

    // Set the "totem flared to life" flag if any boosts were applied
    if (hasBoosts)
        gQueuedStatBoosts[battler].stats |= 0x80;

    // Step 3: Create scripted wild encounter(s) (setwildbattle equivalent)
    if (isDouble)
    {
        CreateScriptedDoubleWildMon(
            pokemon->species, pokemon->level, pokemon->heldItem,
            pokemon->species2, pokemon->level2, pokemon->heldItem2
        );
    }
    else
    {
        CreateScriptedWildMon(pokemon->species, pokemon->level, pokemon->heldItem);
    }

    // Set custom moves for first Pokemon
    if (pokemon->moves[0] != MOVE_NONE)
    {
        for (u8 i = 0; i < MAX_MON_MOVES; i++)
        {
            if (pokemon->moves[i] != MOVE_NONE)
                SetMonMoveSlot(&gEnemyParty[0], pokemon->moves[i], i);
        }
    }

    // Set custom moves for second Pokemon (if double battle)
    if (isDouble && pokemon->moves2[0] != MOVE_NONE)
    {
        for (u8 i = 0; i < MAX_MON_MOVES; i++)
        {
            if (pokemon->moves2[i] != MOVE_NONE)
                SetMonMoveSlot(&gEnemyParty[1], pokemon->moves2[i], i);
        }
    }

    // Step 4: Start the battle (dowildbattle equivalent)
    // Use RAID battle type to ensure totem boosts work correctly
    BattleSetup_StartRaidBattle(isDouble);
}

// Load custom trainer text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossTrainerText
void Script_Dungeon_GetBossTrainerText(void)
{
    const struct DungeonBoss *boss = Dungeon_GetCurrentBoss();
    if (boss == NULL || boss->encounterType != DUNGEON_BOSS_TRAINER)
        return;

    const struct BossTrainer *trainer = &boss->data.trainer;

    // If custom intro text specified, copy to gStringVar4
    // Otherwise, trainer will use default text from trainers.h
    if (trainer->introText != NULL)
        StringCopy(gStringVar4, trainer->introText);
}

// Load custom Pokemon intro text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossPokemonText
void Script_Dungeon_GetBossPokemonText(void)
{
    const struct DungeonBoss *boss = Dungeon_GetCurrentBoss();
    if (boss == NULL || boss->encounterType != DUNGEON_BOSS_POKEMON)
        return;

    const struct BossPokemon *pokemon = &boss->data.pokemon;

    // Copy intro text to gStringVar4
    if (pokemon->introText != NULL)
        StringCopy(gStringVar4, pokemon->introText);
}

// Load custom Pokemon defeat text into gStringVar4
// Usage: callnative Script_Dungeon_GetBossPokemonDefeatText
void Script_Dungeon_GetBossPokemonDefeatText(void)
{
    const struct DungeonBoss *boss = Dungeon_GetCurrentBoss();
    if (boss == NULL || boss->encounterType != DUNGEON_BOSS_POKEMON)
        return;

    const struct BossPokemon *pokemon = &boss->data.pokemon;

    // Copy defeat text to gStringVar4
    if (pokemon->defeatText != NULL)
        StringCopy(gStringVar4, pokemon->defeatText);
}

// Handle boss defeat (trainer or boss Pokemon)
// Usage: callnative Script_Dungeon_OnBossDefeated
void Script_Dungeon_OnBossDefeated(void)
{
    // Award bonus points for defeating boss
    Dungeon_IncrementRewardScore(100);

    // Hide both boss objects
    FlagSet(FLAG_DUNGEON_TRAINER_0);  // Hide trainer
    FlagSet(FLAG_DUNGEON_TRAINER_1);  // Hide Pokemon

    // Warp to end room for rewards
    SetWarpDestination(MAP_GROUP(MAP_DUNGEON1_ROOM_END), MAP_NUM(MAP_DUNGEON1_ROOM_END), WARP_ID_NONE, 9, 8);
    DoTeleportTileWarp();
    ResetInitialPlayerAvatarState();
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
