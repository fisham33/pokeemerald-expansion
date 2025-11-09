// Dungeon Trainer Class Pools
// This file defines which trainer classes can appear at each difficulty tier

#include "constants/trainers.h"
#include "constants/event_objects.h"

// TODO: Populate these arrays with actual trainer classes
// Each tier should have ~20-30 trainer class options for variety
// Trainers will use the party pool system to generate randomized teams

// === EARLY TIER TRAINER CLASSES (Level 15-25) ===
static const struct DungeonTrainerClass sEarlyTierTrainers[] = {
    {
        .graphicsId = OBJ_EVENT_GFX_YOUNGSTER,
        .trainerPic = TRAINER_PIC_YOUNGSTER,
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_LASS,
        .trainerPic = TRAINER_PIC_LASS,
        .trainerClass = TRAINER_CLASS_LASS,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_BUG_CATCHER,
        .trainerPic = TRAINER_PIC_BUG_CATCHER,
        .trainerClass = TRAINER_CLASS_BUG_CATCHER,
        .gender = MALE,
    },
    // TODO: Add more trainer classes (Camper, Picnicker, School Kid, etc.)
    // Aim for 20-30 total for good variety
};

#define EARLY_TIER_TRAINER_COUNT ARRAY_COUNT(sEarlyTierTrainers)

// === MID TIER TRAINER CLASSES (Level 35-45) ===
static const struct DungeonTrainerClass sMidTierTrainers[] = {
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_3,
        .trainerPic = TRAINER_PIC_COOLTRAINER_M,
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_WOMAN_5,
        .trainerPic = TRAINER_PIC_COOLTRAINER_F,
        .trainerClass = TRAINER_CLASS_COOLTRAINER,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_PSYCHIC_M,
        .trainerPic = TRAINER_PIC_PSYCHIC_M,
        .trainerClass = TRAINER_CLASS_PSYCHIC,
        .gender = MALE,
    },
    // TODO: Add more trainer classes (Battle Girl, Bird Keeper, Collector, etc.)
    // Aim for 20-30 total for good variety
};

#define MID_TIER_TRAINER_COUNT ARRAY_COUNT(sMidTierTrainers)

// === LATE TIER TRAINER CLASSES (Level 55-65) ===
static const struct DungeonTrainerClass sLateTierTrainers[] = {
    {
        .graphicsId = OBJ_EVENT_GFX_EXPERT_M,
        .trainerPic = TRAINER_PIC_EXPERT_M,
        .trainerClass = TRAINER_CLASS_EXPERT,
        .gender = MALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_EXPERT_F,
        .trainerPic = TRAINER_PIC_EXPERT_F,
        .trainerClass = TRAINER_CLASS_EXPERT,
        .gender = FEMALE,
    },
    {
        .graphicsId = OBJ_EVENT_GFX_MAN_3,
        .trainerPic = TRAINER_PIC_DRAGON_TAMER,
        .trainerClass = TRAINER_CLASS_DRAGON_TAMER,
        .gender = MALE,
    },
    // TODO: Add more trainer classes (Veteran, Elite Four classes, etc.)
    // Aim for 15-20 total for good variety
};

#define LATE_TIER_TRAINER_COUNT ARRAY_COUNT(sLateTierTrainers)
