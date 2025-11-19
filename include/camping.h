#ifndef GUARD_CAMPING_H
#define GUARD_CAMPING_H

#include "global.h"

// Camping system constants
#define MAX_CAMPING_POKEMON PARTY_SIZE

// Camping data structure
struct CampingData
{
    struct WarpData returnLocation;     // Where to return when exiting camp
    u8 active;                          // Is camping currently active
    u8 partyObjectIds[PARTY_SIZE];     // Object IDs of spawned party Pokemon
    u8 numSpawnedPokemon;               // Number of Pokemon spawned
};

// Global camping data
extern struct CampingData gCampingData;

// Function declarations
void Camping_Init(void);
void Camping_SetupCamp(void);
void Camping_ExitCamp(void);
bool8 Camping_IsActive(void);
void Camping_SpawnPartyPokemon(void);
void Camping_DespawnPartyPokemon(void);
void Camping_StartMealCutscene(u8 pokeblockId);

// Special functions (called from scripts)
void Camping_SelectPokeblock(void);
void Camping_ExitCamping(void);
void Camping_SpawnParty(void);

#endif // GUARD_CAMPING_H
