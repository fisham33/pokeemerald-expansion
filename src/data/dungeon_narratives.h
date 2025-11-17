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

// team magma:
static const struct DungeonTrainerEntry sCaveTeamMagma_TrainerPool[] = {
    { .trainerId = TRAINER_GRUNT_MT_CHIMNEY_1, .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_F },
    { .trainerId = TRAINER_GRUNT_MT_CHIMNEY_2,  .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_M },
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

static const struct WildPokemon sCaveTeamMagma_LandMons[] = {
    { 18, 20, SPECIES_SIZZLIPEDE },      // 20% - Slot 0
    { 18, 20, SPECIES_LINOONE_GALAR },        // 20% - Slot 1
    { 19, 21, SPECIES_SIZZLIPEDE },      // 10% - Slot 2
    { 19, 21, SPECIES_LINOONE_GALAR },        // 10% - Slot 3
    { 18, 20, SPECIES_GROWLITHE_HISUI },   // 10% - Slot 4
    { 19, 21, SPECIES_GROWLITHE_HISUI },   // 10% - Slot 5
    { 20, 22, SPECIES_THIEVUL },         // 5%  - Slot 6
    { 20, 22, SPECIES_THIEVUL },         // 5%  - Slot 7
    { 21, 23, SPECIES_CHARCADET },     // 4%  - Slot 8 (rare)
    { 21, 23, SPECIES_CHARCADET },     // 4%  - Slot 9 (rare)
    { 22, 24, SPECIES_CHARCADET },     // 1%  - Slot 10 (very rare)
    { 22, 24, SPECIES_CHARCADET },     // 1%  - Slot 11 (very rare)
};

static const struct WildPokemonInfo sCaveTest_LandMonsInfo = {
    .encounterRate = 4,  // 2 out of 256 chance per step
    .wildPokemon = sCaveTest_LandMons
};

static const struct WildPokemonInfo sCaveTeamMagma_LandMonsInfo = {
    .encounterRate = 4,  // 2 out of 256 chance per step
    .wildPokemon = sCaveTeamMagma_LandMons
};

// Reward items for test narrative (3 tiers based on score)
static const u16 sCaveTest_RewardItems[] = {
    ITEM_POKE_BALL,         // Low score (0-100)
    ITEM_GREAT_BALL,        // Medium score (101-200)
    ITEM_ULTRA_BALL,        // High score (201+)
};

static const u16 sCaveTeamMagma_RewardItems[] = {
    ITEM_HEAT_ROCK,         // Low score (0-100)
    ITEM_TM_FLAMETHROWER,        // Medium score (101-200)
    ITEM_FIRE_STONE,        // High score (201+)
};

// === DIALOG TEXT ARRAYS ===

// Cave Test narrative dialog
static const u8 sCaveTest_TrainerIntro1[] = _("sCaveTest_TrainerIntro1");
static const u8 sCaveTest_TrainerIntro2[] = _("sCaveTest_TrainerIntro2");
static const u8 sCaveTest_TrainerIntro3[] = _("sCaveTest_TrainerIntro3");

static const u8 sCaveTest_TrainerDefeat1[] = _("sCaveTest_TrainerDefeat1");
static const u8 sCaveTest_TrainerDefeat2[] = _("sCaveTest_TrainerDefeat2");
static const u8 sCaveTest_TrainerDefeat3[] = _("sCaveTest_TrainerDefeat3");

static const u8 sCaveTest_BossIntro1[] = _(
    "The ground trembles as a massive\n"
    "{STR_VAR_1} emerges from the shadows!"
);

static const u8 sCaveTest_BossDefeat1[] = _("...");
static const u8 sCaveTest_BossVictory1[] = _("The mighty {STR_VAR_1} has been defeated!");

static const u8 * const sCaveTest_TrainerIntroTexts[] = {
    sCaveTest_TrainerIntro1,
    sCaveTest_TrainerIntro2,
    sCaveTest_TrainerIntro3,
};

static const u8 * const sCaveTest_TrainerDefeatTexts[] = {
    sCaveTest_TrainerDefeat1,
    sCaveTest_TrainerDefeat2,
    sCaveTest_TrainerDefeat3,
};

static const u8 * const sCaveTest_BossIntroTexts[] = {
    sCaveTest_BossIntro1,
};

static const u8 * const sCaveTest_BossDefeatTexts[] = {
    sCaveTest_BossDefeat1,
};

static const u8 * const sCaveTest_BossVictoryTexts[] = {
    sCaveTest_BossVictory1,
};

// Team Magma narrative dialog
static const u8 sCaveTeamMagma_TrainerIntro1[] = _("Team Magma will prevail!");
static const u8 sCaveTeamMagma_TrainerIntro2[] = _("Out of my way, intruder!");
static const u8 sCaveTeamMagma_TrainerIntro3[] = _("You'll never stop Team Magma!");

static const u8 sCaveTeamMagma_TrainerDefeat1[] = _("Team Magma won't forget this...");
static const u8 sCaveTeamMagma_TrainerDefeat2[] = _("Impossible!");
static const u8 sCaveTeamMagma_TrainerDefeat3[] = _("I've failed the mission!");

static const u8 sCaveTeamMagma_BossIntro1[] = _(
    "{STR_VAR_1}: You've made it this far...\n"
    "But this is where your run ends!"
);
static const u8 sCaveTeamMagma_BossIntro2[] = _(
    "{STR_VAR_1}: So, you're the one interfering\n"
    "with Team Magma's operations!"
);

static const u8 sCaveTeamMagma_BossDefeat1[] = _("{STR_VAR_1}: Impossible...!");
static const u8 sCaveTeamMagma_BossDefeat2[] = _("{STR_VAR_1}: You're stronger than I thought.");

static const u8 sCaveTeamMagma_BossVictory1[] = _("{STR_VAR_1} has been defeated!");
static const u8 sCaveTeamMagma_BossVictory2[] = _("Team Magma retreats in defeat!");

static const u8 * const sCaveTeamMagma_TrainerIntroTexts[] = {
    sCaveTeamMagma_TrainerIntro1,
    sCaveTeamMagma_TrainerIntro2,
    sCaveTeamMagma_TrainerIntro3,
};

static const u8 * const sCaveTeamMagma_TrainerDefeatTexts[] = {
    sCaveTeamMagma_TrainerDefeat1,
    sCaveTeamMagma_TrainerDefeat2,
    sCaveTeamMagma_TrainerDefeat3,
};

static const u8 * const sCaveTeamMagma_BossIntroTexts[] = {
    sCaveTeamMagma_BossIntro1,
    sCaveTeamMagma_BossIntro2,
};

static const u8 * const sCaveTeamMagma_BossDefeatTexts[] = {
    sCaveTeamMagma_BossDefeat1,
    sCaveTeamMagma_BossDefeat2,
};

static const u8 * const sCaveTeamMagma_BossVictoryTexts[] = {
    sCaveTeamMagma_BossVictory1,
    sCaveTeamMagma_BossVictory2,
};

// Strings for test narrative
static const u8 sCaveTest_Name[] = _("Test Expedition");
static const u8 sCaveTest_Description[] = _(
    "A simple test narrative for\p"
    "validating the daily rotation\n"
    "system implementation.$"
);

// Team Magma:
static const u8 sCaveTeamMagma_Name[] = _("Team Magma Dungeon");
static const u8 sCaveTeamMagma_Description[] = _(
    "Team Magma are investigating this\p"
    "cave to try and find rare items to\n"
    "awaken Groudon!$"
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

    // Boss configuration - Pokemon boss for testing
    .bossType = BOSS_TYPE_POKEMON,
    .boss = {
        .pokemon = {
            .species = SPECIES_ONIX,
            .level = 28,
            .heldItem = ITEM_HARD_STONE,
            .totemBoosts = {1, 1, 1, 1, 1, 1, 1},  // +1 to all stats
        }, 
    },

    // Rewards
    .rewardItems = sCaveTest_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveTest_RewardItems),

    // Dialog text
    .trainerIntroTexts = sCaveTest_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sCaveTest_TrainerIntroTexts),
    .trainerDefeatTexts = sCaveTest_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sCaveTest_TrainerDefeatTexts),
    .bossIntroTexts = sCaveTest_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sCaveTest_BossIntroTexts),
    .bossDefeatTexts = sCaveTest_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sCaveTest_BossDefeatTexts),
    .bossVictoryTexts = sCaveTest_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sCaveTest_BossVictoryTexts),
};

// Team Magma
static const struct DungeonNarrative gNarrative_CaveTeamMagma = {
    .id = NARRATIVE_CAVE_TEAM_MAGMA,
    .name = sCaveTeamMagma_Name,
    .description = sCaveTeamMagma_Description,

    // Trainers
    .trainerCount = ARRAY_COUNT(sCaveTeamMagma_TrainerPool),
    .trainerPool = sCaveTeamMagma_TrainerPool,

    // Wild encounters
    .landEncounters = &sCaveTeamMagma_LandMonsInfo,
    .waterEncounters = NULL,  // No water encounters in cave

    // Boss configuration - using current test boss from map
    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_MAXIE_MT_CHIMNEY,
            .graphicsId = OBJ_EVENT_GFX_MAXIE,
        }
    },

    // Rewards
    .rewardItems = sCaveTeamMagma_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveTeamMagma_RewardItems),

    // Dialog text
    .trainerIntroTexts = sCaveTeamMagma_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sCaveTeamMagma_TrainerIntroTexts),
    .trainerDefeatTexts = sCaveTeamMagma_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sCaveTeamMagma_TrainerDefeatTexts),
    .bossIntroTexts = sCaveTeamMagma_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sCaveTeamMagma_BossIntroTexts),
    .bossDefeatTexts = sCaveTeamMagma_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sCaveTeamMagma_BossDefeatTexts),
    .bossVictoryTexts = sCaveTeamMagma_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sCaveTeamMagma_BossVictoryTexts),
};

// === NARRATIVE POOLS ===

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
    // Future narratives will be added here
};

#endif // GUARD_DATA_DUNGEON_NARRATIVES_H
