#ifndef GUARD_DATA_NARRATIVES_MOUNTAIN_H
#define GUARD_DATA_NARRATIVES_MOUNTAIN_H

// ========================================
// MOUNTAIN DUNGEON NARRATIVES
// ========================================
// This file contains all narrative content for DUNGEON_LATE_MOUNTAIN
//
// Each narrative is a self-contained block containing:
//   1. Trainer pool (trainers that spawn in rooms)
//   2. Wild encounter table (Pokemon found in grass/caves)
//   3. Reward items (items given based on score tiers)
//   4. Dialog text arrays (intro/defeat/boss dialog)
//   5. Narrative definition struct (ties everything together)
//
// To add a new mountain narrative:
//   1. Copy the template below or an existing narrative from cave_narratives.h
//   2. Find/replace the narrative prefix (e.g., "sMountainExample" -> "sMountainChampion")
//   3. Modify the content (trainers, encounters, rewards, dialog, boss)
//   4. Adjust Pokemon levels to late-tier dungeon range (~58-64)
//   5. Add the narrative ID to include/constants/dungeons.h (enum DungeonNarratives)
//   6. Add the narrative to sMountainNarrativePool in dungeon_narratives.h
//   7. Add the narrative to gDungeonNarratives array in dungeon_narratives.h

// ========================================
// TEMPLATE: COPY THIS BLOCK TO ADD NEW NARRATIVES
// ========================================
/*
// --- TRAINER POOL ---
static const struct DungeonTrainerEntry sMountainExample_TrainerPool[] = {
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
};

// --- WILD ENCOUNTER TABLE ---
// Levels should match late-tier dungeon range (~58-64)
static const struct WildPokemon sMountainExample_LandMons[] = {
    { 58, 60, SPECIES_XXX },  // 20%
    { 58, 60, SPECIES_XXX },  // 20%
    { 59, 61, SPECIES_XXX },  // 10%
    { 59, 61, SPECIES_XXX },  // 10%
    { 58, 60, SPECIES_XXX },  // 10%
    { 59, 61, SPECIES_XXX },  // 10%
    { 60, 62, SPECIES_XXX },  // 5%
    { 60, 62, SPECIES_XXX },  // 5%
    { 61, 63, SPECIES_XXX },  // 4%
    { 61, 63, SPECIES_XXX },  // 4%
    { 62, 64, SPECIES_XXX },  // 1%
    { 62, 64, SPECIES_XXX },  // 1%
};

static const struct WildPokemonInfo sMountainExample_LandMonsInfo = {
    .encounterRate = 4,
    .wildPokemon = sMountainExample_LandMons
};

// --- REWARD ITEMS ---
static const u16 sMountainExample_RewardItems[] = {
    ITEM_XXX,  // Bronze
    ITEM_XXX,  // Silver
    ITEM_XXX,  // Gold
};

// --- DIALOG TEXT ---
static const u8 sMountainExample_TrainerIntro1[] = _("...");
static const u8 sMountainExample_TrainerIntro2[] = _("...");
static const u8 sMountainExample_TrainerIntro3[] = _("...");

static const u8 sMountainExample_TrainerDefeat1[] = _("...");
static const u8 sMountainExample_TrainerDefeat2[] = _("...");
static const u8 sMountainExample_TrainerDefeat3[] = _("...");

static const u8 sMountainExample_BossIntro1[] = _("...");
static const u8 sMountainExample_BossDefeat1[] = _("...");
static const u8 sMountainExample_BossVictory1[] = _("...");

static const u8 * const sMountainExample_TrainerIntroTexts[] = {
    sMountainExample_TrainerIntro1,
    sMountainExample_TrainerIntro2,
    sMountainExample_TrainerIntro3,
};

static const u8 * const sMountainExample_TrainerDefeatTexts[] = {
    sMountainExample_TrainerDefeat1,
    sMountainExample_TrainerDefeat2,
    sMountainExample_TrainerDefeat3,
};

static const u8 * const sMountainExample_BossIntroTexts[] = {
    sMountainExample_BossIntro1,
};

static const u8 * const sMountainExample_BossDefeatTexts[] = {
    sMountainExample_BossDefeat1,
};

static const u8 * const sMountainExample_BossVictoryTexts[] = {
    sMountainExample_BossVictory1,
};

// --- NARRATIVE DEFINITION ---
static const u8 sMountainExample_Name[] = _("Example Mountain Narrative");
static const u8 sMountainExample_Description[] = _("Description goes here...$");

static const struct DungeonNarrative gNarrative_MountainExample = {
    .id = NARRATIVE_MOUNTAIN_XXX,
    .name = sMountainExample_Name,
    .description = sMountainExample_Description,

    .trainerCount = ARRAY_COUNT(sMountainExample_TrainerPool),
    .trainerPool = sMountainExample_TrainerPool,

    .landEncounters = &sMountainExample_LandMonsInfo,
    .waterEncounters = NULL,

    .bossType = BOSS_TYPE_POKEMON,  // or BOSS_TYPE_TRAINER
    .boss = {
        .pokemon = {
            .species = SPECIES_XXX,
            .level = 68,  // Late-tier boss level (~+8 above dungeon base)
            .heldItem = ITEM_XXX,
            .totemBoosts = {1, 1, 1, 1, 1, 1, 1},
        },
    },

    .rewardItems = sMountainExample_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sMountainExample_RewardItems),

    .trainerIntroTexts = sMountainExample_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sMountainExample_TrainerIntroTexts),
    .trainerDefeatTexts = sMountainExample_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sMountainExample_TrainerDefeatTexts),
    .bossIntroTexts = sMountainExample_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sMountainExample_BossIntroTexts),
    .bossDefeatTexts = sMountainExample_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sMountainExample_BossDefeatTexts),
    .bossVictoryTexts = sMountainExample_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sMountainExample_BossVictoryTexts),
};
*/

#endif // GUARD_DATA_NARRATIVES_MOUNTAIN_H
