#ifndef GUARD_DATA_DUNGEON_NARRATIVES_H
#define GUARD_DATA_DUNGEON_NARRATIVES_H

#include "constants/trainers.h"
#include "constants/species.h"
#include "constants/items.h"
#include "constants/event_objects.h"
#include "constants/dungeons.h"
#include "wild_encounter.h"

// ========================================
// DUNGEON NARRATIVE SYSTEM
// ========================================
// This file organizes all dungeon narratives by including dungeon-specific files
// and defining the narrative pools and global narrative array.
//
// To add a new narrative:
// 1. Edit the appropriate dungeon file in src/data/narratives/
//    - cave_narratives.h (for DUNGEON_EARLY_CAVE)
//    - forest_narratives.h (for DUNGEON_MID_FOREST)
//    - mountain_narratives.h (for DUNGEON_LATE_MOUNTAIN)
// 2. Add the narrative ID to include/constants/dungeons.h (enum DungeonNarratives)
// 3. Add the narrative to the appropriate pool below (sCaveNarrativePool, etc.)
// 4. Add the narrative to gDungeonNarratives array below

// Include narrative definitions for each dungeon type
#include "narratives/cave_narratives.h"
#include "narratives/forest_narratives.h"
#include "narratives/mountain_narratives.h"

// === NARRATIVE POOLS ===
// Each dungeon has a pool of narratives that can be selected via daily rotation

// Cave narrative pool (DUNGEON_EARLY_CAVE)
static const u8 sCaveNarrativePool[] = {
    NARRATIVE_CAVE_TEST,
    NARRATIVE_CAVE_TEAM_MAGMA,
    // Future narratives:
    // NARRATIVE_CAVE_PROFESSOR,
    // NARRATIVE_CAVE_MAGMA,
    // NARRATIVE_CAVE_STEVEN,
};

// Forest narrative pool (DUNGEON_MID_FOREST) - empty for now
static const u8 sForestNarrativePool[] = {
    NARRATIVE_NONE,
};

// Mountain narrative pool (DUNGEON_LATE_MOUNTAIN) - empty for now
static const u8 sMountainNarrativePool[] = {
    NARRATIVE_NONE,
};

// Pool array indexed by dungeon ID
static const u8 *sDungeonNarrativePools[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = sCaveNarrativePool,
    [DUNGEON_MID_FOREST] = sForestNarrativePool,
    [DUNGEON_LATE_MOUNTAIN] = sMountainNarrativePool,
};

// Pool counts indexed by dungeon ID
static const u8 sDungeonNarrativePoolCounts[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = ARRAY_COUNT(sCaveNarrativePool),
    [DUNGEON_MID_FOREST] = ARRAY_COUNT(sForestNarrativePool),
    [DUNGEON_LATE_MOUNTAIN] = ARRAY_COUNT(sMountainNarrativePool),
};

// === GLOBAL NARRATIVE ARRAY ===

// Strings for NARRATIVE_NONE
static const u8 sNarrativeNone_Name[] = _("None");
static const u8 sNarrativeNone_Description[] = _("No narrative active.");

// All narratives indexed by narrative ID
// When adding a new narrative, add it here with its ID from constants/dungeons.h
static const struct DungeonNarrative gDungeonNarratives[NARRATIVE_COUNT] = {
    [NARRATIVE_NONE] = {
        .id = NARRATIVE_NONE,
        .name = sNarrativeNone_Name,
        .description = sNarrativeNone_Description,
        .trainerCount = 0,
        .trainerPool = NULL,
        .landEncounters = NULL,
        .waterEncounters = NULL,
        .bossType = BOSS_TYPE_NONE,
        .rewardItems = NULL,
        .rewardTierCount = 0,
        .trainerIntroTexts = NULL,
        .trainerIntroTextCount = 0,
        .trainerDefeatTexts = NULL,
        .trainerDefeatTextCount = 0,
        .bossIntroTexts = NULL,
        .bossIntroTextCount = 0,
        .bossDefeatTexts = NULL,
        .bossDefeatTextCount = 0,
        .bossVictoryTexts = NULL,
        .bossVictoryTextCount = 0,
    },
    [NARRATIVE_CAVE_TEST] = gNarrative_CaveTest,
    [NARRATIVE_CAVE_TEAM_MAGMA] = gNarrative_CaveTeamMagma,
    // Future narratives will be added here as they are defined
};

#endif // GUARD_DATA_DUNGEON_NARRATIVES_H
