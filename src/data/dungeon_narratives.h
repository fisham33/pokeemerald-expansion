#ifndef GUARD_DATA_DUNGEON_NARRATIVES_H
#define GUARD_DATA_DUNGEON_NARRATIVES_H

#include "constants/trainers.h"
#include "constants/species.h"
#include "constants/items.h"
#include "constants/event_objects.h"
#include "constants/dungeons.h"
#include "wild_encounter.h"

// === TEST NARRATIVE (Phase 1) ===

// Trainer pool for test narrative (paired with overworld sprites)
static const struct DungeonTrainerEntry sCaveTest_TrainerPool[] = {
    { .trainerId = TRAINER_NICOLAS_1, .graphicsId = OBJ_EVENT_GFX_HIKER },
    { .trainerId = TRAINER_CALVIN_1,  .graphicsId = OBJ_EVENT_GFX_YOUNGSTER },
    { .trainerId = TRAINER_ANDRES_1,  .graphicsId = OBJ_EVENT_GFX_CAMPER },
};

// Wild encounter table for test narrative (cave/rock themed)
// 12 slots for land encounters (same distribution as standard encounters)
static const struct WildPokemon sCaveTest_LandMons[] = {
    { 18, 20, SPECIES_GEODUDE },      // 20% - Slot 0
    { 18, 20, SPECIES_ZUBAT },        // 20% - Slot 1
    { 19, 21, SPECIES_GEODUDE },      // 10% - Slot 2
    { 19, 21, SPECIES_ZUBAT },        // 10% - Slot 3
    { 18, 20, SPECIES_ROGGENROLA },   // 10% - Slot 4
    { 19, 21, SPECIES_ROGGENROLA },   // 10% - Slot 5
    { 20, 22, SPECIES_ONIX },         // 5%  - Slot 6
    { 20, 22, SPECIES_ONIX },         // 5%  - Slot 7
    { 21, 23, SPECIES_NOSEPASS },     // 4%  - Slot 8 (rare)
    { 21, 23, SPECIES_NOSEPASS },     // 4%  - Slot 9 (rare)
    { 22, 24, SPECIES_LARVITAR },     // 1%  - Slot 10 (very rare)
    { 22, 24, SPECIES_LARVITAR },     // 1%  - Slot 11 (very rare)
};

static const struct WildPokemonInfo sCaveTest_LandMonsInfo = {
    .encounterRate = 4,  // 2 out of 256 chance per step
    .wildPokemon = sCaveTest_LandMons
};

// Reward items for test narrative (3 tiers based on score)
static const u16 sCaveTest_RewardItems[] = {
    ITEM_POKE_BALL,         // Low score (0-100)
    ITEM_GREAT_BALL,        // Medium score (101-200)
    ITEM_ULTRA_BALL,        // High score (201+)
};

// Strings for test narrative
static const u8 sCaveTest_Name[] = _("Test Expedition");
static const u8 sCaveTest_Description[] = _(
    "A simple test narrative for\p"
    "validating the daily rotation\n"
    "system implementation.$"
);

// Test narrative definition
static const struct DungeonNarrative gNarrative_CaveTest = {
    .id = NARRATIVE_CAVE_TEST,
    .name = sCaveTest_Name,
    .description = sCaveTest_Description,

    // Trainers
    .trainerCount = ARRAY_COUNT(sCaveTest_TrainerPool),
    .trainerPool = sCaveTest_TrainerPool,

    // Wild encounters
    .landEncounters = &sCaveTest_LandMonsInfo,
    .waterEncounters = NULL,  // No water encounters in cave

    // Boss configuration - using current test boss from map
    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_NICOLAS_1,
            .graphicsId = OBJ_EVENT_GFX_HIKER,
        }
    },

    // Rewards
    .rewardItems = sCaveTest_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveTest_RewardItems),
};

// === NARRATIVE POOLS ===

// Cave narrative pool (DUNGEON_EARLY_CAVE)
static const u8 sCaveNarrativePool[] = {
    NARRATIVE_CAVE_TEST,
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
    },
    [NARRATIVE_CAVE_TEST] = gNarrative_CaveTest,
    // Future narratives will be added here
};

#endif // GUARD_DATA_DUNGEON_NARRATIVES_H
