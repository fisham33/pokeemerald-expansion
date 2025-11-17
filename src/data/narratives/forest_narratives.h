#ifndef GUARD_DATA_NARRATIVES_FOREST_H
#define GUARD_DATA_NARRATIVES_FOREST_H

// ========================================
// FOREST DUNGEON NARRATIVES
// ========================================
// This file contains all narrative content for DUNGEON_MID_FOREST
//
// Each narrative is a self-contained block containing:
//   1. Trainer pool (trainers that spawn in rooms)
//   2. Wild encounter table (Pokemon found in grass/caves)
//   3. Reward items (items given based on score tiers)
//   4. Dialog text arrays (intro/defeat/boss dialog)
//   5. Narrative definition struct (ties everything together)
//
// To add a new forest narrative:
//   1. Copy the template below or an existing narrative from cave_narratives.h
//   2. Find/replace the narrative prefix (e.g., "sForestExample" -> "sForestTeamAqua")
//   3. Modify the content (trainers, encounters, rewards, dialog, boss)
//   4. Adjust Pokemon levels to mid-tier dungeon range (~38-44)
//   5. Add the narrative ID to include/constants/dungeons.h (enum DungeonNarratives)
//   6. Add the narrative to sForestNarrativePool in dungeon_narratives.h
//   7. Add the narrative to gDungeonNarratives array in dungeon_narratives.h

// ========================================
// TEMPLATE: COPY THIS BLOCK TO ADD NEW NARRATIVES
// ========================================
/*
// --- TRAINER POOL ---
static const struct DungeonTrainerEntry sForestExample_TrainerPool[] = {
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
    { .trainerId = TRAINER_XXX, .graphicsId = OBJ_EVENT_GFX_XXX },
};

// --- WILD ENCOUNTER TABLE ---
// Levels should match mid-tier dungeon range (~38-44)
static const struct WildPokemon sForestExample_LandMons[] = {
    { 38, 40, SPECIES_XXX },  // 20%
    { 38, 40, SPECIES_XXX },  // 20%
    { 39, 41, SPECIES_XXX },  // 10%
    { 39, 41, SPECIES_XXX },  // 10%
    { 38, 40, SPECIES_XXX },  // 10%
    { 39, 41, SPECIES_XXX },  // 10%
    { 40, 42, SPECIES_XXX },  // 5%
    { 40, 42, SPECIES_XXX },  // 5%
    { 41, 43, SPECIES_XXX },  // 4%
    { 41, 43, SPECIES_XXX },  // 4%
    { 42, 44, SPECIES_XXX },  // 1%
    { 42, 44, SPECIES_XXX },  // 1%
};

static const struct WildPokemonInfo sForestExample_LandMonsInfo = {
    .encounterRate = 4,
    .wildPokemon = sForestExample_LandMons
};

// --- REWARD ITEMS ---
static const u16 sForestExample_RewardItems[] = {
    ITEM_XXX,  // Bronze
    ITEM_XXX,  // Silver
    ITEM_XXX,  // Gold
};

// --- DIALOG TEXT ---
static const u8 sForestExample_TrainerIntro1[] = _("...");
static const u8 sForestExample_TrainerIntro2[] = _("...");
static const u8 sForestExample_TrainerIntro3[] = _("...");

static const u8 sForestExample_TrainerDefeat1[] = _("...");
static const u8 sForestExample_TrainerDefeat2[] = _("...");
static const u8 sForestExample_TrainerDefeat3[] = _("...");

static const u8 sForestExample_BossIntro1[] = _("...");
static const u8 sForestExample_BossDefeat1[] = _("...");
static const u8 sForestExample_BossVictory1[] = _("...");

static const u8 * const sForestExample_TrainerIntroTexts[] = {
    sForestExample_TrainerIntro1,
    sForestExample_TrainerIntro2,
    sForestExample_TrainerIntro3,
};

static const u8 * const sForestExample_TrainerDefeatTexts[] = {
    sForestExample_TrainerDefeat1,
    sForestExample_TrainerDefeat2,
    sForestExample_TrainerDefeat3,
};

static const u8 * const sForestExample_BossIntroTexts[] = {
    sForestExample_BossIntro1,
};

static const u8 * const sForestExample_BossDefeatTexts[] = {
    sForestExample_BossDefeat1,
};

static const u8 * const sForestExample_BossVictoryTexts[] = {
    sForestExample_BossVictory1,
};

// --- NARRATIVE DEFINITION ---
static const u8 sForestExample_Name[] = _("Example Forest Narrative");
static const u8 sForestExample_Description[] = _("Description goes here...$");

static const struct DungeonNarrative gNarrative_ForestExample = {
    .id = NARRATIVE_FOREST_XXX,
    .name = sForestExample_Name,
    .description = sForestExample_Description,

    .trainerCount = ARRAY_COUNT(sForestExample_TrainerPool),
    .trainerPool = sForestExample_TrainerPool,

    .landEncounters = &sForestExample_LandMonsInfo,
    .waterEncounters = NULL,

    .bossType = BOSS_TYPE_POKEMON,  // or BOSS_TYPE_TRAINER
    .boss = {
        .pokemon = {
            .species = SPECIES_XXX,
            .level = 48,  // Mid-tier boss level (~+8 above dungeon base)
            .heldItem = ITEM_XXX,
            .totemBoosts = {1, 1, 1, 1, 1, 1, 1},
        },
    },

    .rewardItems = sForestExample_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sForestExample_RewardItems),

    .trainerIntroTexts = sForestExample_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sForestExample_TrainerIntroTexts),
    .trainerDefeatTexts = sForestExample_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sForestExample_TrainerDefeatTexts),
    .bossIntroTexts = sForestExample_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sForestExample_BossIntroTexts),
    .bossDefeatTexts = sForestExample_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sForestExample_BossDefeatTexts),
    .bossVictoryTexts = sForestExample_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sForestExample_BossVictoryTexts),
};
*/

#endif // GUARD_DATA_NARRATIVES_FOREST_H
