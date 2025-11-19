#include "global.h"
#include "camping.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_object_lock.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "item.h"
#include "item_use.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "sprite.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/flags.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/trainer_types.h"
#include "follower_npc.h"

// External script declarations
extern const u8 Campsite_EventScript_CampingPokemon[];

// Local IDs for party Pokemon objects (starting at a safe range)
#define CAMPING_PARTY1_LOCALID 10
#define CAMPING_PARTY2_LOCALID 11
#define CAMPING_PARTY3_LOCALID 12
#define CAMPING_PARTY4_LOCALID 13
#define CAMPING_PARTY5_LOCALID 14
#define CAMPING_PARTY6_LOCALID 15

// Global camping data
EWRAM_DATA struct CampingData gCampingData = {0};

// Static function declarations
static void Camping_SaveReturnLocation(void);
static void Camping_WarpToCampsite(void);
static void Camping_WarpBack(void);

// Initialize camping data
void Camping_Init(void)
{
    u8 i;

    gCampingData.active = FALSE;
    gCampingData.numSpawnedPokemon = 0;
    gCampingData.hadFollowerEnabled = FALSE;
    gCampingData.returnLocation.mapGroup = 0;
    gCampingData.returnLocation.mapNum = 0;
    gCampingData.returnLocation.warpId = WARP_ID_NONE;
    gCampingData.returnLocation.x = 0;
    gCampingData.returnLocation.y = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        gCampingData.partyObjectIds[i] = 0;
    }
}

// Set up camp (called when using Camping Equipment)
void Camping_SetupCamp(void)
{
    Camping_SaveReturnLocation();
    gCampingData.active = TRUE;

    // Save follower state and disable follower
    gCampingData.hadFollowerEnabled = FlagGet(FLAG_POKEMON_FOLLOWERS);
    if (gCampingData.hadFollowerEnabled)
        FlagClear(FLAG_POKEMON_FOLLOWERS);

    Camping_WarpToCampsite();
}

// Exit camp and return to previous location
void Camping_ExitCamp(void)
{
    Camping_DespawnPartyPokemon();
    gCampingData.active = FALSE;

    // Restore follower state
    if (gCampingData.hadFollowerEnabled)
        FlagSet(FLAG_POKEMON_FOLLOWERS);

    Camping_WarpBack();
}

// Check if camping is currently active
bool8 Camping_IsActive(void)
{
    return gCampingData.active;
}

// Save the current location to return to later
static void Camping_SaveReturnLocation(void)
{
    gCampingData.returnLocation = gSaveBlock1Ptr->location;
}

// Warp to the campsite map
static void Camping_WarpToCampsite(void)
{
    // Warp to center of campsite (coordinates can be adjusted)
    SetWarpDestination(MAP_GROUP(MAP_CAMPSITE1), MAP_NUM(MAP_CAMPSITE1), WARP_ID_NONE, 7, 6);
    WarpIntoMap();
    SetMainCallback2(CB2_LoadMap);
}

// Warp back to the saved return location
static void Camping_WarpBack(void)
{
    SetWarpDestination(
        gCampingData.returnLocation.mapGroup,
        gCampingData.returnLocation.mapNum,
        WARP_ID_NONE,
        gCampingData.returnLocation.x,
        gCampingData.returnLocation.y
    );
    WarpIntoMap();
    SetMainCallback2(CB2_LoadMap);
}

// Spawn party Pokemon as overworld objects
void Camping_SpawnPartyPokemon(void)
{
    u8 i, partyIndex;
    struct Pokemon *mon;
    struct ObjectEventTemplate objectTemplate;
    u8 objectEventId;

    // Starting positions for Pokemon (adjust these coordinates as needed)
    const s16 partyPositions[][2] = {
        {4, 4},   // Party slot 1
        {10, 4},  // Party slot 2
        {4, 10},  // Party slot 3
        {10, 10}, // Party slot 4
        {7, 3},   // Party slot 5
        {7, 11}   // Party slot 6
    };

    gCampingData.numSpawnedPokemon = 0;
    partyIndex = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        mon = &gPlayerParty[i];
        u16 monSpecies = GetMonData(mon, MON_DATA_SPECIES);
        u16 hp = GetMonData(mon, MON_DATA_HP);

        if (monSpecies != SPECIES_NONE && monSpecies != SPECIES_EGG && hp > 0)
        {
            // Set up object template
            objectTemplate.localId = CAMPING_PARTY1_LOCALID + partyIndex;
            objectTemplate.graphicsId = monSpecies + OBJ_EVENT_MON;
            objectTemplate.x = partyPositions[partyIndex][0];
            objectTemplate.y = partyPositions[partyIndex][1];
            objectTemplate.elevation = 0;
            objectTemplate.movementType = MOVEMENT_TYPE_WANDER_AROUND;
            objectTemplate.movementRangeX = 3;
            objectTemplate.movementRangeY = 3;
            objectTemplate.trainerType = TRAINER_TYPE_NONE;
            objectTemplate.trainerRange_berryTreeId = 0;
            objectTemplate.script = Campsite_EventScript_CampingPokemon;
            objectTemplate.flagId = 0;

            // Spawn the object using TrySpawnObjectEventTemplate
            objectEventId = TrySpawnObjectEventTemplate(&objectTemplate,
                gSaveBlock1Ptr->location.mapNum,
                gSaveBlock1Ptr->location.mapGroup,
                0, 0); // camera coordinates (not used for spawning)

            if (objectEventId != OBJECT_EVENTS_COUNT)
            {
                gCampingData.partyObjectIds[partyIndex] = objectEventId;
                gCampingData.partySlotNumbers[partyIndex] = i; // Track which party slot this is
                gCampingData.numSpawnedPokemon++;
                partyIndex++;
            }
        }
    }
}

// Despawn all party Pokemon objects
void Camping_DespawnPartyPokemon(void)
{
    u8 i;
    struct ObjectEvent *objectEvent;

    for (i = 0; i < gCampingData.numSpawnedPokemon; i++)
    {
        objectEvent = &gObjectEvents[gCampingData.partyObjectIds[i]];

        if (objectEvent->active)
        {
            RemoveObjectEventByLocalIdAndMap(
                objectEvent->localId,
                gSaveBlock1Ptr->location.mapNum,
                gSaveBlock1Ptr->location.mapGroup
            );
        }

        gCampingData.partyObjectIds[i] = 0;
    }

    gCampingData.numSpawnedPokemon = 0;
}

// Start the meal cutscene with the selected pokeblock
void Camping_StartMealCutscene(u8 pokeblockId)
{
    // TODO: Implement meal cutscene
    // This will:
    // 1. Move all Pokemon to table positions
    // 2. Show eating emotes
    // 3. Heal 50% HP for each Pokemon
    // 4. Play healing sound
    // 5. Remove the pokeblock
    // 6. Return Pokemon to wandering
}

// Special function: Select a pokeblock from inventory
void Camping_SelectPokeblock(void)
{
    u8 i;
    u8 pkblId = 0;
    bool8 hasPokeblock = FALSE;

    // Find the first available pokeblock
    for (i = 0; i < POKEBLOCKS_COUNT; i++)
    {
        if (gSaveBlock1Ptr->pokeblocks[i].color != PBLOCK_CLR_NONE)
        {
            pkblId = i;
            hasPokeblock = TRUE;
            break;
        }
    }

    if (hasPokeblock)
    {
        // Heal all party Pokemon by 50%
        for (i = 0; i < PARTY_SIZE; i++)
        {
            struct Pokemon *mon = &gPlayerParty[i];
            u16 species = GetMonData(mon, MON_DATA_SPECIES);

            if (species != SPECIES_NONE && species != SPECIES_EGG)
            {
                u16 maxHP = GetMonData(mon, MON_DATA_MAX_HP);
                u16 currentHP = GetMonData(mon, MON_DATA_HP);
                u16 healAmount = maxHP / 2;
                u16 newHP = currentHP + healAmount;

                if (newHP > maxHP)
                    newHP = maxHP;

                SetMonData(mon, MON_DATA_HP, &newHP);
            }
        }

        // Remove the pokeblock from inventory
        TryClearPokeblock(pkblId);

        // Return success
        gSpecialVar_Result = 1;
    }
    else
    {
        // No pokeblocks available
        gSpecialVar_Result = 0;
    }
}

// Special function: Exit camping and return to previous location
void Camping_ExitCamping(void)
{
    Camping_ExitCamp();
}

// Special function: Spawn party Pokemon (called from MapScripts)
void Camping_SpawnParty(void)
{
    struct ObjectEvent *follower;

    // Remove follower Pokemon if it exists
    follower = GetFollowerObject();
    if (follower != NULL)
    {
        RemoveObjectEvent(follower);
    }

    // Destroy follower NPC if it exists
    DestroyFollowerNPC();

    // Spawn camping party
    Camping_SpawnPartyPokemon();
}

// Special function: Handle camping Pokemon interaction
void Camping_InteractWithPokemon(void)
{
    u8 localId = gSpecialVar_LastTalked;
    u8 i;

    // Find which party slot this Pokemon belongs to
    for (i = 0; i < gCampingData.numSpawnedPokemon; i++)
    {
        struct ObjectEvent *obj = &gObjectEvents[gCampingData.partyObjectIds[i]];
        if (obj->localId == localId)
        {
            // Found the Pokemon - get its species and nickname from correct party slot
            u8 partySlot = gCampingData.partySlotNumbers[i];
            struct Pokemon *mon = &gPlayerParty[partySlot];
            u16 species = GetMonData(mon, MON_DATA_SPECIES);

            // Set VAR_0x8004 to species for cry
            gSpecialVar_0x8004 = species;

            // Buffer the Pokemon's nickname to STR_VAR_1
            GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
            StringGet_Nickname(gStringVar1);

            return;
        }
    }
}
