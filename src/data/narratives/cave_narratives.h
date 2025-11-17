#ifndef GUARD_DATA_NARRATIVES_CAVE_H
#define GUARD_DATA_NARRATIVES_CAVE_H

// ========================================
// CAVE DUNGEON NARRATIVES
// ========================================
// This file contains all narrative content for DUNGEON_EARLY_CAVE
//
// Each narrative is a self-contained block containing:
//   1. Trainer pool (trainers that spawn in rooms)
//   2. Wild encounter table (Pokemon found in grass/caves)
//   3. Reward items (items given based on score tiers)
//   4. Dialog text arrays (intro/defeat/boss dialog)
//   5. Narrative definition struct (ties everything together)
//
// To add a new cave narrative:
//   1. Copy an existing narrative block below (all sections from trainer pool to definition)
//   2. Find/replace the narrative prefix (e.g., "sCaveTest" -> "sCaveNewNarrative")
//   3. Modify the content (trainers, encounters, rewards, dialog, boss)
//   4. Add the narrative ID to include/constants/dungeons.h (enum DungeonNarratives)
//   5. Add the narrative to sCaveNarrativePool in dungeon_narratives.h
//   6. Add the narrative to gDungeonNarratives array in dungeon_narratives.h

// ========================================
// NARRATIVE 1: CAVE TEST
// ========================================

// --- TRAINER POOL ---
// Defines which trainers can appear in this narrative's rooms
// Each entry pairs a trainer ID (from trainers.party) with their overworld sprite
// The system randomly selects from this pool when spawning trainers in rooms
static const struct DungeonTrainerEntry sCaveTest_TrainerPool[] = {
    { .trainerId = TRAINER_NICOLAS_1, .graphicsId = OBJ_EVENT_GFX_HIKER },    // Hiker Nicolas
    { .trainerId = TRAINER_CALVIN_1,  .graphicsId = OBJ_EVENT_GFX_YOUNGSTER }, // Youngster Calvin
    { .trainerId = TRAINER_ANDRES_1,  .graphicsId = OBJ_EVENT_GFX_CAMPER },   // Camper Andres
};

// --- WILD ENCOUNTER TABLE ---
// Defines which wild Pokemon appear in this narrative
// 12 slots total, distributed by rarity:
//   Slots 0-1:  20% each (common)
//   Slots 2-5:  10% each (uncommon)
//   Slots 6-7:  5% each (semi-rare)
//   Slots 8-9:  4% each (rare)
//   Slots 10-11: 1% each (very rare)
// Each entry: { minLevel, maxLevel, species }
// Levels should match the dungeon tier (cave = ~18-24)
static const struct WildPokemon sCaveTest_LandMons[] = {
    { 18, 20, SPECIES_GEODUDE },      // 20% - Common rock type
    { 18, 20, SPECIES_ZUBAT },        // 20% - Common cave type
    { 19, 21, SPECIES_GEODUDE },      // 10% - Slightly higher level
    { 19, 21, SPECIES_ZUBAT },        // 10% - Slightly higher level
    { 18, 20, SPECIES_ROGGENROLA },   // 10% - Uncommon rock type
    { 19, 21, SPECIES_ROGGENROLA },   // 10% - Uncommon rock type
    { 20, 22, SPECIES_ONIX },         // 5%  - Semi-rare (matches boss theme)
    { 20, 22, SPECIES_ONIX },         // 5%  - Semi-rare (matches boss theme)
    { 21, 23, SPECIES_NOSEPASS },     // 4%  - Rare rock type
    { 21, 23, SPECIES_NOSEPASS },     // 4%  - Rare rock type
    { 22, 24, SPECIES_LARVITAR },     // 1%  - Very rare pseudo-legendary
    { 22, 24, SPECIES_LARVITAR },     // 1%  - Very rare pseudo-legendary
};

// Wrap the encounter table in a WildPokemonInfo struct
// encounterRate: 4 = ~1.5% chance per step (4/256)
static const struct WildPokemonInfo sCaveTest_LandMonsInfo = {
    .encounterRate = 4,
    .wildPokemon = sCaveTest_LandMons
};

// --- REWARD ITEMS ---
// Items given to player based on performance score
// Index 0 = Bronze tier (low score)
// Index 1 = Silver tier (medium score)
// Index 2 = Gold tier (high score)
// Score thresholds defined in src/dungeon.c (typically 0-100, 101-200, 201+)
static const u16 sCaveTest_RewardItems[] = {
    ITEM_POKE_BALL,   // Bronze - basic reward
    ITEM_GREAT_BALL,  // Silver - better reward
    ITEM_ULTRA_BALL,  // Gold - best reward
};

// --- DIALOG TEXT ---
// Text shown during battles and interactions
// Multiple options allow for variety (system picks randomly)
// Use {STR_VAR_1} placeholder for boss name/species (auto-populated)
// Use {STR_VAR_2}/{STR_VAR_3} for script-populated values (tier, score, etc.)

// Regular trainer intro text (shown when engaging trainers)
static const u8 sCaveTest_TrainerIntro1[] = _("sCaveTest_TrainerIntro1");
static const u8 sCaveTest_TrainerIntro2[] = _("sCaveTest_TrainerIntro2");
static const u8 sCaveTest_TrainerIntro3[] = _("sCaveTest_TrainerIntro3");

// Regular trainer defeat text (shown after defeating trainers)
static const u8 sCaveTest_TrainerDefeat1[] = _("sCaveTest_TrainerDefeat1");
static const u8 sCaveTest_TrainerDefeat2[] = _("sCaveTest_TrainerDefeat2");
static const u8 sCaveTest_TrainerDefeat3[] = _("sCaveTest_TrainerDefeat3");

// Boss intro text (shown when engaging boss)
// {STR_VAR_1} = Boss Pokemon species OR Trainer name (auto-populated)
static const u8 sCaveTest_BossIntro1[] = _(
    "The ground trembles as a massive\n"
    "{STR_VAR_1} emerges from the shadows!"
);

// Boss defeat text (boss says this when defeated)
static const u8 sCaveTest_BossDefeat1[] = _("...");

// Boss victory text (shown after player wins)
// {STR_VAR_1} = Boss Pokemon species OR Trainer name (auto-populated)
static const u8 sCaveTest_BossVictory1[] = _("The mighty {STR_VAR_1} has been defeated!");

// Group text into arrays for random selection
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

// --- NARRATIVE DEFINITION ---
// Ties all components together into a single narrative

// Narrative name and description (shown at dungeon entrance)
static const u8 sCaveTest_Name[] = _("Test Expedition");
static const u8 sCaveTest_Description[] = _(
    "A simple test narrative for\p"
    "validating the daily rotation\n"
    "system implementation.$"
);

// Main narrative struct
static const struct DungeonNarrative gNarrative_CaveTest = {
    .id = NARRATIVE_CAVE_TEST,
    .name = sCaveTest_Name,
    .description = sCaveTest_Description,

    // Trainer configuration
    .trainerCount = ARRAY_COUNT(sCaveTest_TrainerPool),
    .trainerPool = sCaveTest_TrainerPool,

    // Wild encounter configuration
    .landEncounters = &sCaveTest_LandMonsInfo,
    .waterEncounters = NULL,  // Set to NULL if no water encounters

    // Boss configuration
    // Option 1: Pokemon boss (use BOSS_TYPE_POKEMON)
    .bossType = BOSS_TYPE_POKEMON,
    .boss = {
        .pokemon = {
            .species = SPECIES_ONIX,              // Boss Pokemon species
            .level = 28,                          // Boss level (typically +8 above dungeon base)
            .heldItem = ITEM_HARD_STONE,          // Held item (can be ITEM_NONE)
            .totemBoosts = {1, 1, 1, 1, 1, 1, 1}, // Stat boosts: HP/Atk/Def/SpA/SpD/Spe/Acc (+1 to all)
        },
    },
    // Option 2: Trainer boss (use BOSS_TYPE_TRAINER instead)
    // .bossType = BOSS_TYPE_TRAINER,
    // .boss = {
    //     .trainer = {
    //         .trainerId = TRAINER_XXX,      // Trainer ID from trainers.party
    //         .graphicsId = OBJ_EVENT_GFX_XXX, // Overworld sprite
    //     }
    // },

    // Reward configuration
    .rewardItems = sCaveTest_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveTest_RewardItems),

    // Dialog text configuration
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

// ========================================
// NARRATIVE 2: TEAM MAGMA
// ========================================

// --- TRAINER POOL ---
static const struct DungeonTrainerEntry sCaveTeamMagma_TrainerPool[] = {
    { .trainerId = TRAINER_GRUNT_MT_CHIMNEY_1, .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_F },
    { .trainerId = TRAINER_GRUNT_MT_CHIMNEY_2, .graphicsId = OBJ_EVENT_GFX_MAGMA_MEMBER_M },
};

// --- WILD ENCOUNTER TABLE ---
static const struct WildPokemon sCaveTeamMagma_LandMons[] = {
    { 18, 20, SPECIES_SIZZLIPEDE },      // 20%
    { 18, 20, SPECIES_LINOONE_GALAR },   // 20%
    { 19, 21, SPECIES_SIZZLIPEDE },      // 10%
    { 19, 21, SPECIES_LINOONE_GALAR },   // 10%
    { 18, 20, SPECIES_GROWLITHE_HISUI }, // 10%
    { 19, 21, SPECIES_GROWLITHE_HISUI }, // 10%
    { 20, 22, SPECIES_THIEVUL },         // 5%
    { 20, 22, SPECIES_THIEVUL },         // 5%
    { 21, 23, SPECIES_CHARCADET },       // 4%
    { 21, 23, SPECIES_CHARCADET },       // 4%
    { 22, 24, SPECIES_CHARCADET },       // 1%
    { 22, 24, SPECIES_CHARCADET },       // 1%
};

static const struct WildPokemonInfo sCaveTeamMagma_LandMonsInfo = {
    .encounterRate = 4,
    .wildPokemon = sCaveTeamMagma_LandMons
};

// --- REWARD ITEMS ---
static const u16 sCaveTeamMagma_RewardItems[] = {
    ITEM_HEAT_ROCK,
    ITEM_TM_FLAMETHROWER,
    ITEM_FIRE_STONE,
};

// --- DIALOG TEXT ---
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

// --- NARRATIVE DEFINITION ---
static const u8 sCaveTeamMagma_Name[] = _("Team Magma Dungeon");
static const u8 sCaveTeamMagma_Description[] = _(
    "Team Magma are investigating this\p"
    "cave to try and find rare items to\n"
    "awaken Groudon!$"
);

static const struct DungeonNarrative gNarrative_CaveTeamMagma = {
    .id = NARRATIVE_CAVE_TEAM_MAGMA,
    .name = sCaveTeamMagma_Name,
    .description = sCaveTeamMagma_Description,

    .trainerCount = ARRAY_COUNT(sCaveTeamMagma_TrainerPool),
    .trainerPool = sCaveTeamMagma_TrainerPool,

    .landEncounters = &sCaveTeamMagma_LandMonsInfo,
    .waterEncounters = NULL,

    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_MAXIE_MT_CHIMNEY,
            .graphicsId = OBJ_EVENT_GFX_MAXIE,
        }
    },

    .rewardItems = sCaveTeamMagma_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveTeamMagma_RewardItems),

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

// ========================================
// NARRATIVE 2: FITNESS CLUB
// ========================================

// --- TRAINER POOL ---
static const struct DungeonTrainerEntry sCaveFitness_TrainerPool[] = {
    { .trainerId = TRAINER_ALYSSA, .graphicsId = OBJ_EVENT_GFX_CYCLING_TRIATHLETE_F },
    { .trainerId = TRAINER_PAULA, .graphicsId = OBJ_EVENT_GFX_GIRL_3 },
    { .trainerId = TRAINER_NOB_2, .graphicsId = OBJ_EVENT_GFX_BLACK_BELT },
    { .trainerId = TRAINER_JACOB, .graphicsId = OBJ_EVENT_GFX_CYCLING_TRIATHLETE_M },
};

// --- WILD ENCOUNTER TABLE ---
static const struct WildPokemon sCaveFitness_LandMons[] = {
    { 18, 20, SPECIES_VOLTORB_HISUI },      // 20%
    { 18, 20, SPECIES_LINOONE_GALAR },   // 20%
    { 19, 21, SPECIES_VOLTORB_HISUI },      // 10%
    { 19, 21, SPECIES_LINOONE_GALAR },   // 10%
    { 18, 20, SPECIES_PAWMO }, // 10%
    { 19, 21, SPECIES_PAWMO }, // 10%
    { 20, 22, SPECIES_VAROOM },         // 5%
    { 20, 22, SPECIES_VAROOM },         // 5%
    { 21, 23, SPECIES_CYCLIZAR },       // 4%
    { 21, 23, SPECIES_CYCLIZAR },       // 4%
    { 22, 24, SPECIES_CYCLIZAR },       // 1%
    { 22, 24, SPECIES_CYCLIZAR },       // 1%
};

static const struct WildPokemonInfo sCaveFitness_LandMonsInfo = {
    .encounterRate = 4,
    .wildPokemon = sCaveFitness_LandMons
};

// --- REWARD ITEMS ---
static const u16 sCaveFitness_RewardItems[] = {
    ITEM_CARBOS,
    ITEM_TM_TRAILBLAZE,
    ITEM_CHOICE_SCARF,
};

// --- DIALOG TEXT ---
static const u8 sCaveFitness_TrainerIntro1[] = _("Gotta go fast!");
static const u8 sCaveFitness_TrainerIntro2[] = _("I could use a break!");
static const u8 sCaveFitness_TrainerIntro3[] = _("Can you keep up?");

static const u8 sCaveFitness_TrainerDefeat1[] = _("I could use another break.");
static const u8 sCaveFitness_TrainerDefeat2[] = _("So fast!");
static const u8 sCaveFitness_TrainerDefeat3[] = _("Can you slow down?");

static const u8 sCaveFitness_BossIntro1[] = _(
    "{STR_VAR_1}: You want to join the run club?\n"
    "It's pretty exclusive!$"
);
static const u8 sCaveFitness_BossIntro2[] = _(
    "{STR_VAR_1}: Are you lost?$"
);

static const u8 sCaveFitness_BossDefeat1[] = _("{STR_VAR_1}: Alright, you should be here.");
static const u8 sCaveFitness_BossDefeat2[] = _("{STR_VAR_1}: I get it!");

static const u8 sCaveFitness_BossVictory1[] = _("{STR_VAR_1} has been defeated!");
static const u8 sCaveFitness_BossVictory2[] = _("It's time for a ice bath!");

static const u8 * const sCaveFitness_TrainerIntroTexts[] = {
    sCaveFitness_TrainerIntro1,
    sCaveFitness_TrainerIntro2,
    sCaveFitness_TrainerIntro3,
};

static const u8 * const sCaveFitness_TrainerDefeatTexts[] = {
    sCaveFitness_TrainerDefeat1,
    sCaveFitness_TrainerDefeat2,
    sCaveFitness_TrainerDefeat3,
};

static const u8 * const sCaveFitness_BossIntroTexts[] = {
    sCaveFitness_BossIntro1,
    sCaveFitness_BossIntro2,
};

static const u8 * const sCaveFitness_BossDefeatTexts[] = {
    sCaveFitness_BossDefeat1,
    sCaveFitness_BossDefeat2,
};

static const u8 * const sCaveFitness_BossVictoryTexts[] = {
    sCaveFitness_BossVictory1,
    sCaveFitness_BossVictory2,
};

// --- NARRATIVE DEFINITION ---
static const u8 sCaveFitness_Name[] = _("Fitness Club");
static const u8 sCaveFitness_Description[] = _(
    "A group of personal trainers and\p"
    "fitness enthusiasts have started training\n"
    "in the cave!$"
);

static const struct DungeonNarrative gNarrative_CaveFitness = {
    .id = NARRATIVE_CAVE_FITNESS,
    .name = sCaveFitness_Name,
    .description = sCaveFitness_Description,

    .trainerCount = ARRAY_COUNT(sCaveFitness_TrainerPool),
    .trainerPool = sCaveFitness_TrainerPool,

    .landEncounters = &sCaveFitness_LandMonsInfo,
    .waterEncounters = NULL,

    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_DYLAN_2,
            .graphicsId = OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
        }
    },

    .rewardItems = sCaveFitness_RewardItems,
    .rewardTierCount = ARRAY_COUNT(sCaveFitness_RewardItems),

    .trainerIntroTexts = sCaveFitness_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sCaveFitness_TrainerIntroTexts),
    .trainerDefeatTexts = sCaveFitness_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sCaveFitness_TrainerDefeatTexts),
    .bossIntroTexts = sCaveFitness_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sCaveFitness_BossIntroTexts),
    .bossDefeatTexts = sCaveFitness_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sCaveFitness_BossDefeatTexts),
    .bossVictoryTexts = sCaveFitness_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sCaveFitness_BossVictoryTexts),
};

#endif // GUARD_DATA_NARRATIVES_CAVE_H
