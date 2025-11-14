/*
 * Dungeon Boss Definitions
 *
 * This file defines all dungeon bosses (both Pokemon and Trainers).
 *
 * BOSS POKEMON:
 *   - Wild encounters with totem stat boosts
 *   - Can be single or double battles
 *   - Support custom movesets, held items, field effects (weather/terrain)
 *   - Custom overworld sprites and battle text
 *
 * BOSS TRAINERS:
 *   - Defined in trainers.party with party pools for randomization
 *   - Can override overworld sprite and battle text here
 *   - Use "Party Size" and "Pool Rules" in trainers.party for variety
 *   - Example: Party Size: 3, Pool Rules: POOL_RULESET_BASIC with 5 Pokemon = 3 random selections
 */

#include "constants/species.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/event_objects.h"
#include "constants/weather.h"

// ============================================
// TEXT STRINGS
// ============================================

// Boss Pokemon text
static const u8 sText_OnixBoss_Intro[] = _(
    "The ground trembles as a massive\n"
    "ONIX emerges from the shadows!");

static const u8 sText_OnixBoss_Defeat[] = _(
    "The mighty ONIX has been defeated!");

static const u8 sText_DoubleDragon_Intro[] = _(
    "Two fierce dragon Pokémon block\n"
    "your path!");

static const u8 sText_DoubleDragon_Defeat[] = _(
    "The dragon duo falls in defeat!");

static const u8 sText_Lapras_Intro[] = _(
    "A majestic LAPRAS rises from\n"
    "the misty waters!");

static const u8 sText_Lapras_Defeat[] = _(
    "LAPRAS sinks beneath the waves...");

// Boss Trainer custom text (overrides trainers.party if specified, NULL uses defaults)
static const u8 sText_CaveBoss_Intro[] = _(
    "You've made it this far...\n"
    "But this is where your run ends!");

static const u8 sText_CaveBoss_Defeat[] = _(
    "Impossible... You're stronger\n"
    "than I thought!");

// ============================================
// BOSS POKEMON DEFINITIONS
// ============================================

// EXAMPLE 1: Early tier single battle with totem boosts and sandstorm
static const struct DungeonBoss sBoss_Onix_Cave = {
    .encounterType = DUNGEON_BOSS_POKEMON,
    .data = {
        .pokemon = {
            // Primary Pokemon
            .species = SPECIES_ONIX,
            .level = 28,
            .heldItem = ITEM_HARD_STONE,
            .moves = {MOVE_ROCK_THROW, MOVE_SLAM, MOVE_ROCK_TOMB, MOVE_SCREECH},

            // No second Pokemon (single battle)
            .species2 = SPECIES_NONE,
            .level2 = 0,
            .heldItem2 = ITEM_NONE,
            .moves2 = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE},

            // Totem stat boosts (like settotemboost macro)
            .boosts = {
                .atk = 1,      // +1 Attack
                .def = 1,      // +1 Defense
                .speed = 0,
                .spatk = 0,
                .spdef = 0,
                .acc = 0,
                .evas = 0,
            },

            // Field effects
            .fieldEffect = {
                .weather = WEATHER_SANDSTORM,  // Sandstorm benefits rock-type
                .terrain = 0,                   // No terrain
            },

            // Visual/text
            .graphicsId = OBJ_EVENT_GFX_FOSSIL,
            .introText = sText_OnixBoss_Intro,
            .defeatText = sText_OnixBoss_Defeat,
        }
    }
};

// EXAMPLE 2: Mid tier double battle with dragons
static const struct DungeonBoss sBoss_DoubleDragon_Forest = {
    .encounterType = DUNGEON_BOSS_POKEMON,
    .data = {
        .pokemon = {
            // First Pokemon
            .species = SPECIES_GABITE,
            .level = 45,
            .heldItem = ITEM_DRAGON_FANG,
            .moves = {MOVE_DRAGON_CLAW, MOVE_DIG, MOVE_SLASH, MOVE_SANDSTORM},

            // Second Pokemon (double battle)
            .species2 = SPECIES_SHELGON,
            .level2 = 45,
            .heldItem2 = ITEM_DRAGON_SCALE,
            .moves2 = {MOVE_DRAGON_BREATH, MOVE_HEADBUTT, MOVE_PROTECT, MOVE_SCARY_FACE},

            // Totem boosts (applied to BOTH Pokemon in double battles)
            .boosts = {
                .atk = 1,      // +1 Attack
                .def = 0,
                .speed = 1,    // +1 Speed
                .spatk = 0,
                .spdef = 0,
                .acc = 0,
                .evas = 0,
            },

            // No field effects
            .fieldEffect = {
                .weather = WEATHER_NONE,
                .terrain = 0,
            },

            .graphicsId = OBJ_EVENT_GFX_FOSSIL,
            .introText = sText_DoubleDragon_Intro,
            .defeatText = sText_DoubleDragon_Defeat,
        }
    }
};

// EXAMPLE 3: Mid tier with Misty Terrain
static const struct DungeonBoss sBoss_Lapras_Lake = {
    .encounterType = DUNGEON_BOSS_POKEMON,
    .data = {
        .pokemon = {
            .species = SPECIES_LAPRAS,
            .level = 46,
            .heldItem = ITEM_MYSTIC_WATER,
            .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_PERISH_SONG},

            .species2 = SPECIES_NONE,  // Single battle
            .level2 = 0,
            .heldItem2 = ITEM_NONE,
            .moves2 = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE},

            .boosts = {
                .atk = 0,
                .def = 1,      // +1 Defense
                .speed = 0,
                .spatk = 1,    // +1 Sp. Attack
                .spdef = 1,    // +1 Sp. Defense
                .acc = 0,
                .evas = 0,
            },

            .fieldEffect = {
                .weather = WEATHER_FOG_HORIZONTAL,  // Fog for atmosphere
                .terrain = 3,                       // 3 = Misty Terrain
            },

            .graphicsId = OBJ_EVENT_GFX_FOSSIL,
            .introText = sText_Lapras_Intro,
            .defeatText = sText_Lapras_Defeat,
        }
    }
};

// ============================================
// BOSS TRAINER DEFINITIONS
// ============================================
//
// Boss trainers are defined in trainers.party with party pools.
//
// EXAMPLE in trainers.party:
//
// === TRAINER_DUNGEON_BOSS_CAVE_HIKER ===
// Name: Mountain Man Marcus
// Class: Hiker
// Pic: Hiker
// Gender: Male
// Music: Hiker
// Double Battle: No
// AI: Check Bad Move / Try To Faint / Check Viability / Smart Switching
// Party Size: 3
// Pool Rules: POOL_RULESET_BASIC
//
// Geodude @ Oran Berry
// Ability: Sturdy
// Level: 26
// IVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
// Tags: Lead
// - Rock Throw
// - Magnitude
// - Defense Curl
// - Rollout
//
// Onix @ Hard Stone
// Ability: Rock Head
// Level: 28
// IVs: 25 HP / 25 Atk / 25 Def / 25 SpA / 25 SpD / 25 Spe
// Tags: Ace
// - Rock Tomb
// - Slam
// - Screech
// - Rock Throw
//
// Graveler
// Level: 27
// IVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
// - Rock Blast
// - Bulldoze
// - Smack Down
//
// Roggenrola @ Sitrus Berry
// Level: 26
// IVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
// - Rock Blast
// - Headbutt
// - Sand Attack
//
// Nosepass
// Level: 27
// IVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
// - Rock Tomb
// - Thunder Wave
// - Block
// - Spark
//
// With "Party Size: 3", trainer randomly selects 3 Pokemon from pool each battle.
// Tags: Lead/Ace ensures those Pokemon are always included.
//

// EXAMPLE 1: Boss trainer with custom text/sprite
static const struct DungeonBoss sBoss_Trainer_Cave_Hiker = {
    .encounterType = DUNGEON_BOSS_TRAINER,
    .data = {
        .trainer = {
            .trainerId = TRAINER_NICOLAS_1,  // Using existing trainer for testing

            // Override overworld sprite (0 = use default from trainers.party)
            .graphicsId = 0,  // Use default for now

            // Override battle text (NULL = use default from trainers.party)
            .introText = sText_CaveBoss_Intro,
            .defeatText = sText_CaveBoss_Defeat,
        }
    }
};

// ============================================
// BOSS POOLS (Random Selection Per Run)
// ============================================

// Early tier boss pool (1 randomly selected per run)
static const struct DungeonBoss * const sBosses_EarlyTier[] = {
    &sBoss_Onix_Cave,
    &sBoss_Trainer_Cave_Hiker,
    // Add more early bosses here for variety
};

// Mid tier boss pool
static const struct DungeonBoss * const sBosses_MidTier[] = {
    &sBoss_DoubleDragon_Forest,
    &sBoss_Lapras_Lake,
    // Add more mid bosses here
};

// Late tier boss pool
static const struct DungeonBoss * const sBosses_LateTier[] = {
    // Define late tier bosses here (legendaries, etc.)
};

// Pool counts
#define BOSS_POOL_EARLY_COUNT ARRAY_COUNT(sBosses_EarlyTier)
#define BOSS_POOL_MID_COUNT   ARRAY_COUNT(sBosses_MidTier)
#define BOSS_POOL_LATE_COUNT  ARRAY_COUNT(sBosses_LateTier)

// ============================================
// BOSS POOL LOOKUP TABLE
// ============================================

struct BossPoolEntry {
    const struct DungeonBoss * const *bosses;  // Pointer to array of boss pointers
    u8 count;
};

static const struct BossPoolEntry sBossPools[DUNGEON_TIER_COUNT] = {
    [DUNGEON_TIER_EARLY] = {
        .bosses = sBosses_EarlyTier,
        .count = BOSS_POOL_EARLY_COUNT,
    },
    [DUNGEON_TIER_MID] = {
        .bosses = sBosses_MidTier,
        .count = BOSS_POOL_MID_COUNT,
    },
    [DUNGEON_TIER_LATE] = {
        .bosses = sBosses_LateTier,
        .count = BOSS_POOL_LATE_COUNT,
    },
};
