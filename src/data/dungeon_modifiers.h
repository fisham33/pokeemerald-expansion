#ifndef GUARD_DATA_DUNGEON_MODIFIERS_H
#define GUARD_DATA_DUNGEON_MODIFIERS_H

#include "constants/battle.h"
#include "constants/dungeons.h"

// === MODIFIER DEFINITIONS ===

// Strings for modifiers
static const u8 sModifierNone_Name[] = _("No Modifier");
static const u8 sModifierNone_Description[] = _("No special conditions active.$");
static const u8 sModifierSun_Name[] = _("Permanent Sunlight");
static const u8 sModifierSun_Description[] = _("Harsh sunlight shines\pthroughout the dungeon.$");
static const u8 sModifierRain_Name[] = _("Permanent Rain");
static const u8 sModifierRain_Description[] = _("Rain falls constantly\pthroughout the dungeon.$");
static const u8 sModifierSandstorm_Name[] = _("Permanent Sandstorm");
static const u8 sModifierSandstorm_Description[] = _("A sandstorm rages\pthroughout the dungeon.$");
static const u8 sModifierHail_Name[] = _("Permanent Hail");
static const u8 sModifierHail_Description[] = _("Hail falls constantly\pthroughout the dungeon.$");
static const u8 sModifierSnow_Name[] = _("Permanent Snow");
static const u8 sModifierSnow_Description[] = _("Snow falls constantly\pthroughout the dungeon.$");
static const u8 sModifierStrongWinds_Name[] = _("Strong Winds");
static const u8 sModifierStrongWinds_Description[] = _("Mysterious strong winds\pblow throughout the dungeon.$");
static const u8 sModifierTrickRoom_Name[] = _("Trick Room");
static const u8 sModifierTrickRoom_Description[] = _("Trick Room is active for\p5 turns at battle start.$");
static const u8 sModifierInverse_Name[] = _("Inverse Battle");
static const u8 sModifierInverse_Description[] = _("Type matchups are\pinverted in all battles.$");
static const u8 sModifierDoubleExp_Name[] = _("Double Experience");
static const u8 sModifierDoubleExp_Description[] = _("All battles grant\pdouble experience.$");
static const u8 sModifierExpert_Name[] = _("Expert Challenge");
static const u8 sModifierExpert_Description[] = _("All enemy Pokemon are\p+5 levels higher.$");

// No modifier
static const struct DungeonModifier gModifier_None = {
    .id = MODIFIER_NONE,
    .name = sModifierNone_Name,
    .description = sModifierNone_Description,
    .weatherOrTerrain = 0,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Sun
static const struct DungeonModifier gModifier_PermanentSun = {
    .id = MODIFIER_PERMANENT_SUN,
    .name = sModifierSun_Name,
    .description = sModifierSun_Description,
    .weatherOrTerrain = STARTING_STATUS_SUN,
    .weatherDuration = 0, // 0 = infinite
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Rain
static const struct DungeonModifier gModifier_PermanentRain = {
    .id = MODIFIER_PERMANENT_RAIN,
    .name = sModifierRain_Name,
    .description = sModifierRain_Description,
    .weatherOrTerrain = STARTING_STATUS_RAIN,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Sandstorm
static const struct DungeonModifier gModifier_PermanentSandstorm = {
    .id = MODIFIER_PERMANENT_SANDSTORM,
    .name = sModifierSandstorm_Name,
    .description = sModifierSandstorm_Description,
    .weatherOrTerrain = STARTING_STATUS_SANDSTORM,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Hail
static const struct DungeonModifier gModifier_PermanentHail = {
    .id = MODIFIER_PERMANENT_HAIL,
    .name = sModifierHail_Name,
    .description = sModifierHail_Description,
    .weatherOrTerrain = STARTING_STATUS_HAIL,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Snow
static const struct DungeonModifier gModifier_PermanentSnow = {
    .id = MODIFIER_PERMANENT_SNOW,
    .name = sModifierSnow_Name,
    .description = sModifierSnow_Description,
    .weatherOrTerrain = STARTING_STATUS_SNOW,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Permanent Strong Winds
static const struct DungeonModifier gModifier_PermanentStrongWinds = {
    .id = MODIFIER_PERMANENT_STRONG_WINDS,
    .name = sModifierStrongWinds_Name,
    .description = sModifierStrongWinds_Description,
    .weatherOrTerrain = STARTING_STATUS_STRONG_WINDS,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Trick Room (5 turns)
static const struct DungeonModifier gModifier_TrickRoom = {
    .id = MODIFIER_TRICK_ROOM,
    .name = sModifierTrickRoom_Name,
    .description = sModifierTrickRoom_Description,
    .weatherOrTerrain = STARTING_STATUS_TRICK_ROOM,
    .weatherDuration = 5,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Inverse Battle
// Note: Inverse battles are handled via FLAG_ENABLE_INVERSE_BATTLE, not battleTypeFlags
static const struct DungeonModifier gModifier_InverseBattle = {
    .id = MODIFIER_INVERSE_BATTLE,
    .name = sModifierInverse_Name,
    .description = sModifierInverse_Description,
    .weatherOrTerrain = 0,
    .weatherDuration = 0,
    .battleTypeFlags = 0, // Inverse battles use a flag instead (FLAG_ENABLE_INVERSE_BATTLE)
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Double EXP
static const struct DungeonModifier gModifier_DoubleExp = {
    .id = MODIFIER_DOUBLE_EXP,
    .name = sModifierDoubleExp_Name,
    .description = sModifierDoubleExp_Description,
    .weatherOrTerrain = 0,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 2,
    .moneyMultiplier = 1,
};

// Expert Challenge (+5 levels)
static const struct DungeonModifier gModifier_ExpertChallenge = {
    .id = MODIFIER_EXPERT_CHALLENGE,
    .name = sModifierExpert_Name,
    .description = sModifierExpert_Description,
    .weatherOrTerrain = 0,
    .weatherDuration = 0,
    .battleTypeFlags = 0,
    .levelModifier = 5,
    .expMultiplier = 1,
    .moneyMultiplier = 2, // Extra money to compensate for difficulty
};

// === MODIFIER POOLS ===

// Cave modifier pool (DUNGEON_EARLY_CAVE)
static const u8 sCaveModifierPool[] = {
    DUNGEON_CAVE_MODIFIERS
};

// Forest modifier pool (DUNGEON_MID_FOREST)
static const u8 sForestModifierPool[] = {
    DUNGEON_FOREST_MODIFIERS
};

// Mountain modifier pool (DUNGEON_LATE_MOUNTAIN)
static const u8 sMountainModifierPool[] = {
    DUNGEON_MOUNTAIN_MODIFIERS
};

// Pool array indexed by dungeon ID
static const u8 *sDungeonModifierPools[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = sCaveModifierPool,
    [DUNGEON_MID_FOREST] = sForestModifierPool,
    [DUNGEON_LATE_MOUNTAIN] = sMountainModifierPool,
};

// Pool counts indexed by dungeon ID
static const u8 sDungeonModifierPoolCounts[DUNGEON_COUNT] = {
    [DUNGEON_EARLY_CAVE] = ARRAY_COUNT(sCaveModifierPool),
    [DUNGEON_MID_FOREST] = ARRAY_COUNT(sForestModifierPool),
    [DUNGEON_LATE_MOUNTAIN] = ARRAY_COUNT(sMountainModifierPool),
};

// === GLOBAL MODIFIER ARRAY ===

// All modifiers indexed by modifier ID
static const struct DungeonModifier gDungeonModifiers[MODIFIER_COUNT] = {
    [MODIFIER_NONE] = gModifier_None,
    [MODIFIER_PERMANENT_SUN] = gModifier_PermanentSun,
    [MODIFIER_PERMANENT_RAIN] = gModifier_PermanentRain,
    [MODIFIER_PERMANENT_SANDSTORM] = gModifier_PermanentSandstorm,
    [MODIFIER_PERMANENT_HAIL] = gModifier_PermanentHail,
    [MODIFIER_PERMANENT_SNOW] = gModifier_PermanentSnow,
    [MODIFIER_PERMANENT_STRONG_WINDS] = gModifier_PermanentStrongWinds,
    [MODIFIER_TRICK_ROOM] = gModifier_TrickRoom,
    [MODIFIER_INVERSE_BATTLE] = gModifier_InverseBattle,
    [MODIFIER_DOUBLE_EXP] = gModifier_DoubleExp,
    [MODIFIER_EXPERT_CHALLENGE] = gModifier_ExpertChallenge,
};

#endif // GUARD_DATA_DUNGEON_MODIFIERS_H
