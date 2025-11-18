#include "global.h"
#include "camping.h"
#include "event_data.h"
#include "event_object_movement.h"
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
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/species.h"

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
    Camping_WarpToCampsite();
}

// Exit camp and return to previous location
void Camping_ExitCamp(void)
{
    Camping_DespawnPartyPokemon();
    gCampingData.active = FALSE;
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
    SetWarpDestination(MAP_GROUP(CAMPSITE), MAP_NUM(CAMPSITE), WARP_ID_NONE, 7, 6);
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
    // TODO: Implement Pokemon spawning
    // This will be implemented in the next phase
    u8 i;
    struct Pokemon *mon;

    gCampingData.numSpawnedPokemon = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        mon = &gPlayerParty[i];

        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE
            && GetMonData(mon, MON_DATA_SPECIES) != SPECIES_EGG
            && GetMonData(mon, MON_DATA_HP) > 0)
        {
            // Spawn Pokemon object
            // We'll implement the actual spawning logic later
            gCampingData.numSpawnedPokemon++;
        }
    }
}

// Despawn all party Pokemon objects
void Camping_DespawnPartyPokemon(void)
{
    // TODO: Implement Pokemon despawning
    u8 i;

    for (i = 0; i < gCampingData.numSpawnedPokemon; i++)
    {
        // Despawn Pokemon object
        // We'll implement the actual despawning logic later
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
