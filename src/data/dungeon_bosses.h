// Dungeon Boss Definitions
// This file defines boss encounters for each difficulty tier

#include "constants/species.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/event_objects.h"

// TODO: Populate boss pools with actual encounters
// Bosses can be either:
// 1. Static wild encounters (single powerful Pokemon)
// 2. Trainer battles (boss trainers with themed teams)
// The encounterType field determines which type

// ==========================================================================
// EARLY TIER BOSS POOL (Level 25-30)
// ==========================================================================

// Early tier bosses - powerful but not legendary
static const struct DungeonBoss sEarlyTierBosses[] = {
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_ONIX,
        .level = 28,
        .heldItem = ITEM_HARD_STONE,
        .moves = {MOVE_ROCK_THROW, MOVE_SLAM, MOVE_ROCK_TOMB, MOVE_SCREECH},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_ROUTE_119_TREECKO,  // TODO: Replace with TRAINER_DUNGEON_BOSS_EARLY_1
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_PINSIR,
        .level = 27,
        .heldItem = ITEM_SILVER_POWDER,
        .moves = {MOVE_VICE_GRIP, MOVE_SEISMIC_TOSS, MOVE_BRICK_BREAK, MOVE_VITAL_THROW},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_ROUTE_119_MUDKIP,  // TODO: Replace with TRAINER_DUNGEON_BOSS_EARLY_2
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_MILTANK,
        .level = 26,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_STOMP, MOVE_ROLLOUT, MOVE_MILK_DRINK, MOVE_BODY_SLAM},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_ROUTE_103_TREECKO,  // TODO: Replace with TRAINER_DUNGEON_BOSS_EARLY_3
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_GOLEM,
        .level = 29,
        .heldItem = ITEM_QUICK_CLAW,
        .moves = {MOVE_MAGNITUDE, MOVE_ROCK_BLAST, MOVE_SELF_DESTRUCT, MOVE_BULLDOZE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_ROUTE_103_MUDKIP,  // TODO: Replace with TRAINER_DUNGEON_BOSS_EARLY_4
    },
    // TODO: Add 6-10 more boss options for variety
    // Consider: Scyther, Heracross, Tauros, Electabuzz, Magmar, Jynx, etc.
};

#define EARLY_TIER_BOSS_COUNT ARRAY_COUNT(sEarlyTierBosses)

// ==========================================================================
// MID TIER BOSS POOL (Level 45-50)
// ==========================================================================

// Mid tier bosses - pseudo-legendaries and powerful fully-evolved Pokemon
static const struct DungeonBoss sMidTierBosses[] = {
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_DRAGONAIR,
        .level = 47,
        .heldItem = ITEM_DRAGON_FANG,
        .moves = {MOVE_DRAGON_PULSE, MOVE_AQUA_TAIL, MOVE_THUNDER_WAVE, MOVE_DRAGON_DANCE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_MAY,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_MAY_ROUTE_119_TREECKO,  // TODO: Replace with TRAINER_DUNGEON_BOSS_MID_1
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_SNORLAX,
        .level = 48,
        .heldItem = ITEM_CHESTO_BERRY,
        .moves = {MOVE_BODY_SLAM, MOVE_REST, MOVE_CRUNCH, MOVE_HEAVY_SLAM},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_MAY,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_MAY_ROUTE_119_MUDKIP,  // TODO: Replace with TRAINER_DUNGEON_BOSS_MID_2
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_LAPRAS,
        .level = 46,
        .heldItem = ITEM_MYSTIC_WATER,
        .moves = {MOVE_SURF, MOVE_ICE_BEAM, MOVE_THUNDERBOLT, MOVE_PERISH_SONG},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_MAY,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_MAY_ROUTE_119_TORCHIC,  // TODO: Replace with TRAINER_DUNGEON_BOSS_MID_3
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_METAGROSS,
        .level = 49,
        .heldItem = ITEM_METAL_COAT,
        .moves = {MOVE_METEOR_MASH, MOVE_EARTHQUAKE, MOVE_ZEN_HEADBUTT, MOVE_BULLET_PUNCH},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_RS_MAY,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_MAY_ROUTE_103_TREECKO,  // TODO: Replace with TRAINER_DUNGEON_BOSS_MID_4
    },
    // TODO: Add 6-10 more boss options for variety
    // Consider: Salamence, Tyranitar, Garchomp, Dragonite, Arcanine, Gyarados, etc.
};

#define MID_TIER_BOSS_COUNT ARRAY_COUNT(sMidTierBosses)

// ==========================================================================
// LATE TIER BOSS POOL (Level 65-70)
// ==========================================================================

// Late tier bosses - legendaries and mythicals
// Note: These are powerful reward encounters, should be rare/special
static const struct DungeonBoss sLateTierBosses[] = {
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_ARTICUNO,
        .level = 67,
        .heldItem = ITEM_NEVER_MELT_ICE,
        .moves = {MOVE_ICE_BEAM, MOVE_HURRICANE, MOVE_REFLECT, MOVE_ROOST},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_WALLY_VR_1,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_1
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_ZAPDOS,
        .level = 67,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_DRILL_PECK, MOVE_ANCIENT_POWER, MOVE_DISCHARGE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_WALLY_VR_2,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_2
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_MOLTRES,
        .level = 67,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_AIR_SLASH, MOVE_SOLAR_BEAM, MOVE_HEAT_WAVE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_WALLY_VR_3,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_3
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_SUICUNE,
        .level = 68,
        .heldItem = ITEM_LEFTOVERS,
        .moves = {MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_CALM_MIND, MOVE_MIRROR_COAT},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_WALLY_VR_4,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_4
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_RAIKOU,
        .level = 68,
        .heldItem = ITEM_MAGNET,
        .moves = {MOVE_THUNDERBOLT, MOVE_SHADOW_BALL, MOVE_CALM_MIND, MOVE_VOLT_SWITCH},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_WALLY_VR_5,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_5
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_ENTEI,
        .level = 68,
        .heldItem = ITEM_CHARCOAL,
        .moves = {MOVE_FLAMETHROWER, MOVE_STONE_EDGE, MOVE_EXTREME_SPEED, MOVE_SACRED_FIRE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_LILYCOVE_TREECKO,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_6
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_LATIAS,
        .level = 69,
        .heldItem = ITEM_SOUL_DEW,
        .moves = {MOVE_PSYCHIC, MOVE_DRAGON_PULSE, MOVE_CALM_MIND, MOVE_RECOVER},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_LILYCOVE_MUDKIP,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_7
    },
    {
        .encounterType = DUNGEON_BOSS_STATIC,
        .species = SPECIES_LATIOS,
        .level = 69,
        .heldItem = ITEM_SOUL_DEW,
        .moves = {MOVE_PSYCHIC, MOVE_DRAGON_PULSE, MOVE_CALM_MIND, MOVE_LUSTER_PURGE},
        .graphicsId = OBJ_EVENT_GFX_FOSSIL,
        .trainerPic = TRAINER_PIC_BRENDAN,  // Placeholder
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
        .trainerId = TRAINER_BRENDAN_LILYCOVE_TORCHIC,  // TODO: Replace with TRAINER_DUNGEON_BOSS_LATE_8
    },
    // TODO: Consider adding more legendaries for variety
    // Options: Regis, Heatran, Cresselia, Cobalion/Terrakion/Virizion, etc.
    // Note: Avoid box legendaries (Mewtwo, Rayquaza, etc.) to keep difficulty reasonable
};

#define LATE_TIER_BOSS_COUNT ARRAY_COUNT(sLateTierBosses)

// ==========================================================================
// BOSS POOL LOOKUP TABLE
// ==========================================================================

// Helper structure to organize boss pools by tier
struct BossPoolEntry {
    const struct DungeonBoss *bosses;
    u8 count;
};

static const struct BossPoolEntry sBossPools[DUNGEON_TIER_COUNT] = {
    [DUNGEON_TIER_EARLY] = {
        .bosses = sEarlyTierBosses,
        .count = EARLY_TIER_BOSS_COUNT,
    },
    [DUNGEON_TIER_MID] = {
        .bosses = sMidTierBosses,
        .count = MID_TIER_BOSS_COUNT,
    },
    [DUNGEON_TIER_LATE] = {
        .bosses = sLateTierBosses,
        .count = LATE_TIER_BOSS_COUNT,
    },
};
