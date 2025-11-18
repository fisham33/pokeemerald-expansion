# Procedural Dungeon System - Complete Documentation

**Credits:** [fisham33](https://github.com/fisham33)

This is the comprehensive documentation for the procedurally generated dungeon system in pokeemerald-expansion, including design, implementation status, and developer guides.

## System Status: **FULLY FUNCTIONAL** ✅

All core systems are complete and working:
- ✅ Daily narrative rotation with RTC
- ✅ Dynamic trainer spawning from narrative pools
- ✅ Party pool system for randomized teams
- ✅ Dynamic wild encounters (no JSON entries needed)
- ✅ **Narrative-driven bosses with selectmons battles**
- ✅ **Random dialog text system for variety**
- ✅ **Dynamic overworld sprites for bosses**
- ✅ Modifier system (weather, battle flags, exp/money multipliers)
- ✅ Score tracking and tiered reward distribution
- ✅ Complete entrance/end room scripts
- ✅ **Refresh mode system (fixed/per-entry/daily/weekly)**

**Ready for content creation!** The engine is complete and needs narratives/modifiers to be designed.

---

## Table of Contents

1. [Overview & Design](#overview--design)
2. [Implementation Status](#implementation-status)
3. [Architecture](#architecture)
4. [Boss System](#boss-system)
5. [Dialog System](#dialog-system)
6. [Reward System](#reward-system)
7. [Refresh Modes](#refresh-modes)
8. [Boss Room Template System](#boss-room-template-system)
9. [AI-Assisted Narrative Generation](#ai-assisted-narrative-generation)
10. [Developer Guides](#developer-guides)

---

# Overview & Design

## Vision

A replayable roguelike-style challenge where players:
- Enter a dungeon and progress through 5 rooms before facing a boss
- Battle randomly spawned trainers (1-4 per room) with randomized teams
- Encounter biome-themed wild Pokémon at scaled levels
- Experience **rotating narratives** that change trainers, encounters, and bosses
- Earn rewards based on performance (trainer defeats)

## Core Features

### Rotation System
- **Narratives**: Story/theme that affects trainers, encounters, bosses, rewards
- **Modifiers**: Battle conditions (weather, inverse battles, trick room, etc.)
- **Configurable Refresh**: Per dungeon configuration determines rotation frequency:
  - **REFRESH_FIXED**: Never changes (uses specific narrative/modifier)
  - **REFRESH_PER_ENTRY**: Random every entry (different every time)
  - **REFRESH_DAILY**: Changes once per day (RTC-based)
  - **REFRESH_WEEKLY**: Changes once per week (RTC-based)

### Dungeon Varieties
- Supports multiple dungeons in the world (requires creating dungeon maps)
- Feature comes with predefined cave dungeon (5 rooms + entrance/boss/end rooms)
- Placeholder code for forest and mountain dungeons
- **Only non-procedural element**: Wild Pokémon and trainer levels are set per dungeon tier

### Narrative Example
```
Today's Cave Narrative: "Team Magma's Search"
- Description: "Team Magma seeks an ancient artifact!"
- Trainers: Team Magma grunts with fire/ground types
- Wild Encounters: Numel, Torkoal, Baltoy
- Boss: Team Magma Admin with randomized fire/ground team
- Modifier: Permanent Sunlight
```

---

# Implementation Status

## Completed Systems

### Core Dungeon Engine ✅
- Room randomization (Fisher-Yates shuffle)
- Trainer spawning (1-4 per room from narrative pools)
- Wild encounter override (narrative-based)
- Boss encounter system (trainer and Pokémon types)
- Score tracking and reward distribution
- Auto-cleanup on map exit (prevents state leakage)

### Narrative System ✅
- **Modular file organization** (`src/data/narratives/cave_narratives.h`, etc.)
- Daily/weekly/per-entry rotation with RTC support
- Debug mode for testing specific narratives
- Narrative pools per dungeon type
- Full support for trainer pools, wild encounters, bosses, and rewards
- **Random dialog text** from pools (prevents repetition)

### Boss System ✅
- Trainer bosses with party pool randomization
- Pokémon bosses with totem boosts and custom movesets
- **Selectmons integration** (player chooses 3 Pokémon)
- Dynamic overworld sprites (both trainer and Pokémon)
- Boss-specific intro/defeat/victory dialog

### Modifier System ✅
- Weather modifiers (permanent sun, rain, sandstorm, hail, snow, strong winds)
- Field effects (Trick Room, Gravity)
- Battle modifiers (Inverse Battle, Double EXP, Expert Challenge +5 levels)
- Applied via `B_VAR_STARTING_STATUS` and battle flags
- Auto-clears when exiting dungeon

### Reward System ✅
- Three-tier system (Bronze/Silver/Gold) based on score
- **Randomized item selection** from narrative-defined pools
- Tier-locked rewards (visible but inaccessible until threshold met)
- Item ball objects in boss room
- Configurable thresholds in `config/dungeon.h`

## Current Content

### DUNGEON_EARLY_CAVE (Level 20)
- **Maps**: 5 rooms + entrance + boss + end room (fully functional)
- **Narratives**: 3 implemented
  - `NARRATIVE_CAVE_TEST` - Test narrative with basic encounters
  - `NARRATIVE_CAVE_TEAM_MAGMA` - Team Magma themed
  - `NARRATIVE_CAVE_FITNESS` - Fitness/sports themed
- **Modifiers**: 5 available (Sun, Sandstorm, Trick Room, Inverse Battle, Double EXP)

### DUNGEON_MID_FOREST (Level 40)
- **Maps**: Placeholder (MAP_UNDEFINED)
- **Narratives**: 1 placeholder (`NARRATIVE_NONE`)
- **Modifiers**: 3 defined (Rain, Trick Room, Inverse Battle)

### DUNGEON_LATE_MOUNTAIN (Level 60)
- **Maps**: Placeholder (MAP_UNDEFINED)
- **Narratives**: 1 placeholder (`NARRATIVE_NONE`)
- **Modifiers**: 4 defined (Hail, Snow, Trick Room, Expert Challenge)

---

# Architecture

## File Structure

```
include/
├── config/
│   └── dungeon.h                     // Configuration (points, thresholds, refresh modes)
├── constants/
│   ├── dungeons.h                    // Dungeon/narrative/modifier IDs and enums
│   ├── flags.h                       // Dungeon flags (trainer defeated, boss defeated)
│   └── vars.h                        // Dungeon variables (trainer IDs, graphics IDs)
└── dungeon.h                         // Public API & structs

src/
├── dungeon.c                         // Main implementation (all core logic)
└── data/
    ├── dungeon_definitions.h         // Base dungeon configs (tiers, room pools)
    ├── dungeon_modifiers.h           // All modifier definitions
    ├── dungeon_narratives.h          // Master narrative index (includes sub-files)
    ├── dungeon_rooms.h               // Room definitions (maps, spawn coords, trainer counts)
    └── narratives/                   // Modular narrative files by dungeon type
        ├── cave_narratives.h         // Cave dungeon narratives (DUNGEON_EARLY_CAVE)
        ├── forest_narratives.h       // Forest dungeon narratives (DUNGEON_MID_FOREST)
        └── mountain_narratives.h     // Mountain dungeon narratives (DUNGEON_LATE_MOUNTAIN)

data/scripts/
├── dungeon_rooms.pory                // Shared trainer battle scripts (all rooms)
└── DungeonBossRoom_Common.pory       // Reusable boss room template scripts
```

## Data Structures

### Narrative Definition
```c
struct DungeonNarrative {
    u8 id;
    const u8 *name;                          // "Professor's Expedition"
    const u8 *description;                   // Multi-line description

    // Trainer configuration
    u8 trainerCount;                         // Number of trainers in pool
    const struct DungeonTrainerEntry *trainerPool;  // Array of trainer+graphics pairs

    // Wild encounters
    const struct WildPokemonInfo *landEncounters;
    const struct WildPokemonInfo *waterEncounters;

    // Boss configuration - only one boss per narrative
    u8 bossType;                             // BOSS_TYPE_TRAINER or BOSS_TYPE_POKEMON
    union {
        struct {
            u16 trainerId;                   // TRAINER_* constant
            u16 graphicsId;                  // OBJ_EVENT_GFX_*
        } trainer;
        struct {
            u16 species;                     // SPECIES_*
            u8 level;
            u16 heldItem;                    // ITEM_*
            u8 totemBoosts[7];               // Stat boosts
        } pokemon;
    } boss;

    // Rewards - Randomized pools
    const u16 * const *rewardItemPools;      // Array of item pools per tier (bronze/silver/gold)
    const u8 *rewardPoolSizes;               // Array of pool sizes per tier
    u8 rewardTierCount;                      // Number of reward tiers (typically 3)

    // Dialog text pools (randomly selected for variety)
    const u8 * const *trainerIntroTexts;     // Array of regular trainer intro text options
    u8 trainerIntroTextCount;
    const u8 * const *trainerDefeatTexts;    // Array of regular trainer defeat text options
    u8 trainerDefeatTextCount;
    const u8 * const *bossIntroTexts;        // Array of boss intro text options
    u8 bossIntroTextCount;
    const u8 * const *bossDefeatTexts;       // Array of boss defeat text options
    u8 bossDefeatTextCount;
    const u8 * const *bossVictoryTexts;      // Array of boss victory text options (after player wins)
    u8 bossVictoryTextCount;
};
```

### Modifier Definition
```c
struct DungeonModifier {
    u8 id;
    const u8 *name;                          // "Permanent Sunlight"
    const u8 *description;                   // "Harsh sunlight throughout the dungeon"

    // Battle conditions
    u8 weatherOrTerrain;                     // STARTING_STATUS_* constant
    u8 weatherDuration;                      // 0 = infinite, else turn count

    // Battle flags
    u16 battleTypeFlags;                     // B_FLAG_INVERSE_BATTLE, etc.

    // Additional modifiers
    s8 levelModifier;                        // ±level adjustment
    u8 expMultiplier;                        // 1-5x experience
    u8 moneyMultiplier;                      // 1-5x prize money
};
```

### Dungeon Definition
```c
struct Dungeon {
    u8 id;                 // DUNGEON_ID
    u8 tier;               // DUNGEON_TIER (affects level scaling)
    u8 biome;              // DUNGEON_BIOME (affects encounters)
    u8 baseLevel;          // Base level for encounters/trainers
    u8 levelRange;         // ±range for variation (e.g., 20±5 = 15-25)
    u8 roomCount;          // Number of rooms before boss
    u16 entranceMap;       // MAP_DUNGEON_EARLY_ENTRANCE, etc.
    const struct DungeonRoom *roomPool;  // Pointer to array of available rooms
    u8 roomPoolSize;       // Number of rooms in the pool

    // Refresh mode configuration
    u8 narrativeRefreshMode;  // REFRESH_* mode for narrative rotation
    u8 modifierRefreshMode;   // REFRESH_* mode for modifier rotation
    u8 fixedNarrativeId;      // Used when narrativeRefreshMode = REFRESH_FIXED
    u8 fixedModifierId;       // Used when modifierRefreshMode = REFRESH_FIXED
};
```

## Memory Footprint (SaveBlock2)

**Total: 17 bytes**

```c
struct SaveBlock2
{
    // ... existing fields ...
             u16 dungeonActive:1;           // Dungeon system: Is a dungeon run currently active?
             u16 dungeonCurrentRoom:3;      // Dungeon system: Current room (0-7)
    /*0x16*/ u16 dungeonTrainersDefeated:3; // Dungeon system: Trainers defeated this room (0-7)
             u16 dungeonRewardScore:7;      // Dungeon system: Total reward points (0-127)
             u16 padding2:6;
    /*0x18*/ struct Pokedex pokedex;
    /*0x90*/ u16 dungeonDailySeed;           // Narrative system: Seed based on current day (for rotation)
    /*0x92*/ u8 dungeonNarratives[3];        // Narrative system: Active narrative ID per dungeon
    /*0x95*/ u8 dungeonModifiers[3];         // Narrative system: Active modifier ID per dungeon
    /*0x98*/ u8 dungeonRoomOrder[8];         // Dungeon system: Shuffled room indices for current run
};
```

**Breakdown:**
- **Bitfield state** (4 bits): dungeonActive, dungeonCurrentRoom, dungeonTrainersDefeated, dungeonRewardScore
- **Daily seed** (2 bytes): RTC-based rotation seed
- **Active narratives** (3 bytes): One per dungeon
- **Active modifiers** (3 bytes): One per dungeon
- **Room order** (8 bytes): Shuffled room sequence for current run

### Flags
- **FLAG_DUNGEON_TRAINER_0-3**: Trainer visibility (cleared per room), also used for reward item visibility
- **FLAG_DUNGEON_BOSS_DEFEATED**: Boss defeated this run (cleared on exit)
- **FLAG_DUNGEON_CAVE/FOREST/MOUNTAIN_COMPLETED**: Permanent completion flags

### Variables
- **VAR_TEMP_0**: Current dungeon ID (while active)
- **VAR_TEMP_1**: Selectmons mode flag for boss battles
- **VAR_TEMP_2**: Battle outcome (1 = won, 0 = lost)
- **VAR_OBJ_GFX_ID_0-3**: Dynamic trainer sprites (reused per room)
- **VAR_OBJ_GFX_ID_4**: Dynamic boss trainer sprite
- **VAR_OBJ_GFX_ID_5**: Dynamic boss Pokemon sprite
- **VAR_DUNGEON_TRAINER_0-3**: Trainer IDs for regular battles
- **VAR_DUNGEON_BOSS_TRAINER**: Boss trainer ID from narrative

## Key Architectural Decisions

### 1. Wild Encounters - Dynamic, Not JSON ✅
**Benefits:**
- No entries needed in `wild_encounters.json`
- Fully dynamic based on narrative
- Minimal changes to commonly-updated code
- Easy to maintain and merge

**Implementation:**
```c
// In wild_encounter.c - HEADER_NONE path
if (headerId == HEADER_NONE)
{
    // Check for dungeon encounters first
    const struct WildPokemonInfo *dungeonLandMonsInfo = Dungeon_GetLandEncounters();

    if (dungeonLandMonsInfo != NULL)
    {
        // Use dungeon encounters from active narrative
        // Auto-clears if player exits dungeon map
    }
}
```

**Auto-cleanup feature:**
- `Dungeon_GetLandEncounters()` checks if player is on a dungeon map
- If not on dungeon map, automatically calls `Dungeon_Exit()` to clear state
- Prevents dungeon encounters from persisting after white-out or warp

### 2. Trainer Integration - Entry Pairs ✅
**Decision:** Store both trainerId and graphicsId together in `struct DungeonTrainerEntry` arrays.

**Benefits:**
- Single array lookup gets both trainer and sprite
- Guaranteed matching pairs
- Simple random selection
- Easy to add new trainer variants

**Implementation:**
```c
struct DungeonTrainerEntry {
    u16 trainerId;      // TRAINER_* constant
    u16 graphicsId;     // OBJ_EVENT_GFX_* for overworld sprite
};

// In narrative:
static const struct DungeonTrainerEntry sCaveTest_TrainerPool[] = {
    { .trainerId = TRAINER_NICOLAS_1, .graphicsId = OBJ_EVENT_GFX_HIKER },
    { .trainerId = TRAINER_CALVIN_1,  .graphicsId = OBJ_EVENT_GFX_YOUNGSTER },
};
```

### 3. Boss System - Narrative Bosses ✅
**Decision:** Boss data is embedded in narrative definition

**How it works:**
- Narrative defines `boss.trainer.trainerId` or `boss.pokemon.species`
- Multiple narratives per dungeon allow for multiple boss variations
- Trainer bosses can use party pool system for randomized teams
- Perfect thematic coherence with daily rotation

**Result:** Team Magma narrative → Magma boss trainer with fire/ground team!

**Implementation:**
```c
// In dungeon_narratives.h
const struct DungeonNarrative gNarrative_CaveMagma = {
    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_DUNGEON_BOSS_MAGMA_ADMIN,  // ← Uses party pool!
            .graphicsId = OBJ_EVENT_GFX_MAGMA_ADMIN,
        }
    },
};
```

### 4. Modifier Application ✅
**Implementation:** Modifiers are applied at battle start via `Dungeon_ApplyModifierForBattle()`

**How it works:**
```c
void Dungeon_ApplyModifierForBattle(void)
{
    // Get active modifier for current dungeon
    const struct DungeonModifier *modifier = Dungeon_GetActiveModifier(dungeonId);

    // Apply weather/terrain via B_VAR_STARTING_STATUS
    if (modifier->weatherOrTerrain != 0)
    {
        VarSet(B_VAR_STARTING_STATUS, modifier->weatherOrTerrain);
        VarSet(B_VAR_STARTING_STATUS_TIMER, modifier->weatherDuration);
    }

    // Apply battle type flags
    if (modifier->battleTypeFlags != 0)
        gBattleTypeFlags |= modifier->battleTypeFlags;

    // Handle inverse battle (uses flag, not gBattleTypeFlags)
    if (modifier->id == MODIFIER_INVERSE_BATTLE)
        FlagSet(B_FLAG_INVERSE_BATTLE);
}
```

**Note:** This function should be called from battle setup code. Level modifiers, exp multipliers, and money multipliers are handled separately during battle calculations.

---

# Boss System

## Current Implementation (Narrative-Based)

The boss system is **fully integrated with narratives** for thematic coherence and uses **selectmons battle format**.

### How It Works

```
Narrative defines boss:
  .bossType = BOSS_TYPE_TRAINER
  .boss.trainer.trainerId = TRAINER_DUNGEON_BOSS_MAGMA_ADMIN
  .boss.trainer.graphicsId = OBJ_EVENT_GFX_MAGMA_ADMIN

That trainer in trainers.party uses trainer party pool feature:
  TRAINER_PARTY_FROM_POOL(sPartyPool_CaveMagma, 4, 6)
  → 4-6 Pokemon randomly selected from fire/ground themed pool

Player reaches boss room:
  Dungeon_SpawnBoss() → reads narrative->boss
  → Sets VAR_DUNGEON_BOSS_TRAINER = narrative->boss.trainer.trainerId
  → Sets VAR_OBJ_GFX_ID_4/5 for dynamic overworld sprite
  → Boss appears in room

Player interacts with boss:
  → Random intro text selected from narrative->bossIntroTexts
  → Player selects 3 Pokemon from their party (selectmons)
  → Battle starts with TRAINER_BATTLE_CONTINUE_SCRIPT_NO_INTRO_TEXT mode
  → Party is randomized from party pool
  → Boss has thematic team!

After victory:
  → Random victory text shown
  → Random defeat/post-battle text shown
  → Boss despawns, rewards appear
```

### Benefits

- ✅ Thematic coherence (Magma narrative → Magma boss)
- ✅ Boss trainers use party pools (automatic randomization)
- ✅ Boss changes with narrative rotation
- ✅ Consistent with narrative-driven architecture
- ✅ No extra work - just define trainerId, party pool handles the rest!
- ✅ **Selectmons battles** make boss fights more strategic
- ✅ **Dynamic dialog** prevents repetitive text on repeated runs
- ✅ **Dynamic sprites** for both trainer and Pokémon bosses

### Boss Types

**1. Trainer Boss**
```c
.bossType = BOSS_TYPE_TRAINER,
.boss = {
    .trainer = {
        .trainerId = TRAINER_MAXIE,  // Uses party pool in trainers.party
        .graphicsId = OBJ_EVENT_GFX_MAXIE,
    }
},
```

**2. Pokémon Boss**
```c
.bossType = BOSS_TYPE_POKEMON,
.boss = {
    .pokemon = {
        .species = SPECIES_ONIX,
        .level = 28,
        .heldItem = ITEM_HARD_STONE,
        .totemBoosts = {1, 1, 0, 0, 0, 0, 0},  // +1 HP, +1 Atk
    }
},
```

**Note:** Pokémon bosses:
- Are single Pokémon encounters
- Cannot be captured (FLAG_NO_CATCHING is set)
- Have totem stat boosts applied
- Use smart AI (FLAG_SMART_WILD_POKEMON)

---

# Dialog System

## Random Text Selection

The dialog system provides variety to dungeon runs by randomly selecting text from narrative-defined pools. This prevents repetitive dialog when players replay dungeons.

### How It Works

Each narrative defines arrays of dialog text options:

```c
// Example: Team Magma narrative dialog
static const u8 sCaveTeamMagma_TrainerIntro1[] = _("Team Magma will prevail!");
static const u8 sCaveTeamMagma_TrainerIntro2[] = _("Out of my way, intruder!");
static const u8 sCaveTeamMagma_TrainerIntro3[] = _("You'll never stop Team Magma!");

static const u8 * const sCaveTeamMagma_TrainerIntroTexts[] = {
    sCaveTeamMagma_TrainerIntro1,
    sCaveTeamMagma_TrainerIntro2,
    sCaveTeamMagma_TrainerIntro3,
};

// In narrative definition:
.trainerIntroTexts = sCaveTeamMagma_TrainerIntroTexts,
.trainerIntroTextCount = ARRAY_COUNT(sCaveTeamMagma_TrainerIntroTexts),
```

### Dialog Types

**1. Regular Trainer Dialog**
- **Intro Text**: Shown before trainer battle starts
- **Defeat Text**: Shown when trainer loses
- Selected randomly from `trainerIntroTexts` and `trainerDefeatTexts` arrays

**2. Boss Dialog**
- **Intro Text**: Shown when player interacts with boss
- **Victory Text**: Shown after player wins ("Boss trainer defeated!")
- **Defeat Text**: Shown after victory dialog ("You're stronger than I thought.")
- Selected randomly from `bossIntroTexts`, `bossVictoryTexts`, and `bossDefeatTexts` arrays

### Implementation Details

**Script Functions** (defined in dungeon.c, callable via `callnative`):
- `Script_Dungeon_GetRandomTrainerIntro()` - Loads random trainer intro into gStringVar4
- `Script_Dungeon_GetRandomTrainerDefeat()` - Loads random trainer defeat into gStringVar4
- `Script_Dungeon_GetRandomBossIntro()` - Loads random boss intro into gStringVar4
- `Script_Dungeon_GetRandomBossVictory()` - Loads random boss victory into gStringVar4
- `Script_Dungeon_GetRandomBossDefeat()` - Loads random boss defeat into gStringVar4

**Trainer Battle Integration**:
- Trainer battles automatically use random text from narrative pools
- Text is loaded into gStringVar4 and displayed via msgbox
- Boss battles call script functions manually for full control over dialog timing

**Usage in Scripts**:
```pory
// Boss intro example
callnative(Script_Dungeon_GetRandomBossIntro)
msgbox(gStringVar4, MSGBOX_DEFAULT)
```

### Benefits

- ✅ **Easy to expand** - Just add more text strings to arrays
- ✅ **Minimal overhead** - Random selection at battle time
- ✅ **Automatic for trainers** - No script changes needed
- ✅ **Full control for bosses** - Scripts control dialog timing

### Design Guidelines

When creating dialog text for narratives:

**Trainer Dialog (3-5 variations recommended)**:
- Keep intro text short (1-2 lines)
- Match narrative theme (Team Magma should sound like Team Magma)
- Vary the tone (confident, surprised, angry, etc.)
- Defeat text should show character (denial, respect, humor, etc.)

**Boss Dialog (2-3 variations recommended)**:
- Intro can be longer (2-3 lines) to establish boss presence
- Victory text celebrates the achievement
- Defeat text shows boss personality (gracious, bitter, mysterious, etc.)

**Example - Team Magma Trainer**:
```c
// Varied intro text
"Team Magma will prevail!"       // Confident
"Out of my way, intruder!"        // Aggressive
"You'll never stop Team Magma!"   // Defiant

// Varied defeat text
"Team Magma won't forget this..." // Threatening
"Impossible!"                      // Shocked
"I've failed the mission!"         // Disappointed
```

---

# Reward System

## How Rewards Work

The reward system tracks player performance throughout the dungeon run and distributes **randomized items from tiered pools** based on score.

### Score Calculation

Points are awarded for:
- **+4 points** per trainer defeated (`DUNGEON_POINTS_PER_TRAINER`)
- **+20 points** for defeating the boss (`DUNGEON_POINTS_BOSS_TRAINER` or `DUNGEON_POINTS_BOSS_POKEMON`)
- *(Future: +1 point per Pokémon caught - `DUNGEON_POINTS_PER_CATCH`)*

**Maximum possible score:**
- 5 rooms × 4 trainers max × 4 points = 80 points
- 1 boss × 20 points = 20 points
- **Total: 100 points** (capped at 127 due to 7-bit field)

### Reward Tiers

Scores are converted to tiers (Bronze/Silver/Gold):

| Tier | Score Range | Rank | Reward Selection |
|------|-------------|------|------------------|
| 1 | 0-44 | Bronze | Random item from bronze pool |
| 2 | 45-69 | Silver | Random item from silver pool |
| 3 | 70+ | Gold | Random item from gold pool |

**Thresholds** (configurable in `include/config/dungeon.h`):
- `DUNGEON_REWARD_TIER_GOLD = 70`
- `DUNGEON_REWARD_TIER_SILVER = 45`

**Note:** Each tier has a pool of items, and one per tier is randomly selected at reward time.

### Implementation

**Reward Distribution Function** (src/dungeon.c:625)
```c
void Dungeon_DistributeRewards(void)
{
    // Gets active narrative and its reward pool configuration
    // Calculates tier based on score (1-3) via Dungeon_CalculateRewardTier()
    // Gets the appropriate reward pool for the tier
    // Randomly selects one item from the pool using Random()
    // Checks bag space with CheckBagHasSpace()
    // Adds item to bag with AddBagItem()
    // Sets VAR_RESULT (success/fail) and VAR_0x8004 (item ID)
}
```

**Tier Calculation** (src/dungeon.c:704)
```c
u16 Dungeon_CalculateRewardTier(void)
{
    u16 score = Dungeon_GetRewardScore();

    if (score >= DUNGEON_REWARD_TIER_GOLD)        // 70+
        return 3;  // Gold tier
    else if (score >= DUNGEON_REWARD_TIER_SILVER) // 45-69
        return 2;  // Silver tier
    else                                           // 0-44
        return 1;  // Bronze tier
}
```

**Boss Room Script Functions**:
- `Script_Dungeon_GetRewardItem()` - Gets random item from specific tier (reads tier from VAR_TEMP_0)
- `Script_Dungeon_GetRewardTier()` - Returns current tier 1-3 in VAR_RESULT

**Boss Room Scripts** (data/scripts/DungeonBossRoom_Common.pory:179):
- Bronze reward: Always available (tier 1)
- Silver reward: Locked until tier 2+ ("Defeat more trainers for Silver rank!")
- Gold reward: Locked until tier 3 ("Defeat all trainers for Gold rank!")

**Communication Variables:**
- `VAR_RESULT`: TRUE if item given, FALSE if failed / Current tier (1-3)
- `VAR_0x8004`: Item ID for display
- `VAR_TEMP_0`: Reward tier index (0=bronze, 1=silver, 2=gold)

### Defining Rewards in Narratives

Each narrative defines **reward pools** for each tier, allowing multiple possible items per tier:

```c
// Bronze tier pool - multiple common items
static const u16 sCaveTest_BronzeRewardPool[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_ANTIDOTE,
};

// Silver tier pool - multiple valuable items
static const u16 sCaveTest_SilverRewardPool[] = {
    ITEM_GREAT_BALL,
    ITEM_SUPER_POTION,
    ITEM_FULL_HEAL,
};

// Gold tier pool - multiple rare items
static const u16 sCaveTest_GoldRewardPool[] = {
    ITEM_ULTRA_BALL,
    ITEM_HYPER_POTION,
    ITEM_MAX_REVIVE,
};

// Array of pools (indexed by tier)
static const u16 * const sCaveTest_RewardPools[] = {
    sCaveTest_BronzeRewardPool,
    sCaveTest_SilverRewardPool,
    sCaveTest_GoldRewardPool,
};

// Array of pool sizes
static const u8 sCaveTest_RewardPoolSizes[] = {
    ARRAY_COUNT(sCaveTest_BronzeRewardPool),
    ARRAY_COUNT(sCaveTest_SilverRewardPool),
    ARRAY_COUNT(sCaveTest_GoldRewardPool),
};

const struct DungeonNarrative gNarrative_CaveTest = {
    // ... other fields ...
    .rewardItemPools = sCaveTest_RewardPools,
    .rewardPoolSizes = sCaveTest_RewardPoolSizes,
    .rewardTierCount = ARRAY_COUNT(sCaveTest_RewardPools),
};
```

---

# Refresh Modes

## How Refresh Modes Work

Each dungeon can be configured independently to determine how often its narrative and modifier change. This is set in `src/data/dungeon_definitions.h`.

### Available Modes

| Mode | Behavior | Use Case | Requires RTC |
|------|----------|----------|--------------|
| `REFRESH_FIXED` | Never changes - uses specific narrative/modifier ID | Testing or themed dungeons | No |
| `REFRESH_PER_ENTRY` | Random every time player enters dungeon | Maximum variety, works without RTC | No |
| `REFRESH_DAILY` | Changes once per day based on real-time clock | Daily challenge dungeons | Yes |
| `REFRESH_WEEKLY` | Changes once per week based on real-time clock | Weekly challenge dungeons | Yes |

### Configuration

**Global Defaults** (`include/config/dungeon.h:40`):
```c
#define DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE  REFRESH_PER_ENTRY
#define DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE   REFRESH_PER_ENTRY
#define DUNGEON_DEFAULT_FIXED_NARRATIVE_ID      NARRATIVE_NONE
#define DUNGEON_DEFAULT_FIXED_MODIFIER_ID       MODIFIER_NONE
```

**Per-Dungeon Override** (`src/data/dungeon_definitions.h:23`):
```c
[DUNGEON_EARLY_CAVE] = {
    // ... other fields ...

    // Option 1: Use global defaults
    .narrativeRefreshMode = DUNGEON_DEFAULT_NARRATIVE_REFRESH_MODE,
    .modifierRefreshMode = DUNGEON_DEFAULT_MODIFIER_REFRESH_MODE,

    // Option 2: Override for this specific dungeon
    .narrativeRefreshMode = REFRESH_DAILY,      // Change narrative once per day
    .modifierRefreshMode = REFRESH_PER_ENTRY,   // Change modifier every entry

    // Option 3: Fixed mode (must set fixedNarrativeId/fixedModifierId)
    .narrativeRefreshMode = REFRESH_FIXED,
    .fixedNarrativeId = NARRATIVE_CAVE_MAGMA,   // Always Team Magma
    .fixedModifierId = MODIFIER_PERMANENT_SUN,  // Always sunny
},
```

### Implementation Details

**Seed Generation** (src/dungeon.c:788):
```c
static u16 Dungeon_GetSeedForMode(u8 dungeonId, u8 refreshMode)
{
    switch (refreshMode)
    {
    case REFRESH_FIXED:
        return 0;  // Not used (fixedNarrativeId/fixedModifierId used instead)

    case REFRESH_PER_ENTRY:
        return Random();  // New random value every time

    case REFRESH_DAILY:
        return Dungeon_GetDailySeed();  // RTC-based (year/month/day)

    case REFRESH_WEEKLY:
        return Dungeon_GetWeeklySeed();  // RTC-based (year/week)
    }
}
```

**Selection Logic** (src/dungeon.c:817):
```c
static u8 Dungeon_SelectNarrative(u8 dungeonId, u16 seed)
{
    // Get narrative pool for this dungeon
    const u8 *pool = sDungeonNarrativePools[dungeonId];
    u8 count = sDungeonNarrativePoolCounts[dungeonId];

    // Use seed to select narrative from pool
    return pool[seed % count];
}
```

**Daily/Weekly Rotation Check** (src/dungeon.c:852):
- `Dungeon_CheckDailyRotation()` is called at game startup
- Compares current RTC date/week with saved `dungeonDailySeed`
- Updates narratives/modifiers for dungeons using REFRESH_DAILY or REFRESH_WEEKLY
- First-time initialization sets all dungeon narratives/modifiers

**Per-Entry Randomization** (src/dungeon.c:104):
- Happens in `Dungeon_Enter()` when player enters dungeon
- Only applies if dungeon uses `REFRESH_PER_ENTRY` mode
- Generates new random seed and selects from pool
- **No save data needed** - truly random every time

### Debug Mode

For testing specific narratives/modifiers, enable debug mode:

**Configuration** (`include/config/dungeon.h:51`):
```c
#define I_DUNGEON_DEBUG_MODE            TRUE
#define I_DUNGEON_DEBUG_MODIFIER        MODIFIER_PERMANENT_HAIL
#define I_DUNGEON_DEBUG_NARRATIVE       NARRATIVE_CAVE_TEST
```

**Effect:**
- Overrides rotation system
- Forces specific narrative/modifier for **all dungeons**
- Useful for testing new content

---

# Boss Room Template System

## Reusable Boss Room Scripts (Phase 3)

To reduce code duplication and improve maintainability, all boss rooms use a **common template script** located in `data/scripts/DungeonBossRoom_Common.pory`.

### How It Works

**Common Template** (DungeonBossRoom_Common.pory):
- Contains reusable logic for boss battles (trainer and Pokémon)
- Handles intro text, battle setup, victory/defeat text
- Returns control to calling script after battle
- **Uses `return` instead of `end`** to allow wrapper scripts to execute cleanup

**Room-Specific Wrapper** (e.g., Dungeon1_RoomBoss/scripts.pory):
- Calls common template with `call` command
- Handles boss despawning and reward spawning after battle
- Can add custom pre/post-battle logic if needed

### Benefits

- ✅ **No code duplication** - Boss logic in one place
- ✅ **Easy to update** - Change affects all boss rooms
- ✅ **Flexible** - Wrapper scripts can customize behavior
- ✅ **Maintainable** - Developers only need to update one file

### Common Scripts Available

**Visibility Management:**
- `Common_DungeonBoss_ShowTrainerBoss` - Show trainer, hide Pokémon
- `Common_DungeonBoss_ShowPokemonBoss` - Show Pokémon, hide trainer
- `Common_DungeonBoss_HideRewards` - Hide all reward items
- `Common_DungeonBoss_ShowRewards` - Show all reward items

**Battle Scripts:**
- `Common_DungeonBoss_TrainerBattle` - Full trainer boss battle (with selectmons)
- `Common_DungeonBoss_TrainerVictory` - Post-victory cleanup for trainer boss
- `Common_DungeonBoss_PokemonBattle` - Full Pokémon boss battle (with totem boosts)
- `Common_DungeonBoss_PokemonVictoryEnd` - Post-victory cleanup for Pokémon boss

**Reward Scripts:**
- `Common_DungeonReward_Bronze` - Bronze tier reward (always available)
- `Common_DungeonReward_Silver` - Silver tier reward (locked until tier 2)
- `Common_DungeonReward_Gold` - Gold tier reward (locked until tier 3)

### Example Usage

```pory
// Dungeon1_RoomBoss/scripts.pory

script DungeonBoss_TrainerTest {
    // Call common template
    call(Common_DungeonBoss_TrainerBattle)

    // Check if player won
    if (var(VAR_TEMP_2) == 1) {
        // Player won - show victory text and spawn rewards
        call(Common_DungeonBoss_TrainerVictory)
        call(Common_DungeonBoss_ShowRewards)
    }

    releaseall
    end
}

script DungeonBoss_PokemonTest {
    // Call common template
    call(Common_DungeonBoss_PokemonBattle)

    // Check if player won (set by common script in VAR_TEMP_2)
    if (var(VAR_TEMP_2) == 1) {
        // Player won - show rewards
        call(Common_DungeonBoss_PokemonVictoryEnd)
        call(Common_DungeonBoss_ShowRewards)
    }

    release
    end
}
```

**Important:** Common scripts use `return`, NOT `end`, to pass control back to wrapper scripts!

---

# AI-Assisted Narrative Generation

## LLM Prompt for Generating Narrative Ideas

Use this prompt to generate creative, implementable narrative ideas for the dungeon system:

```
I'm developing a procedurally generated dungeon system for a Pokémon Emerald ROM hack. The system features daily rotating "narratives" - themed story scenarios that determine trainers, wild encounters, bosses, and rewards. I need creative ideas for new narratives.

# System Overview

**Dungeon Context:**
- Players enter a 5-room dungeon leading to a boss fight
- Each room contains 1-4 randomly spawned trainers from the narrative's pool
- Wild encounters are themed to the narrative
- Boss is narrative-specific (changes with rotation)
- Rewards are tier-based (Bronze/Silver/Gold) depending on score

**Three Dungeon Tiers:**
1. Early Cave (Level 20) - Beginner difficulty
2. Mid Forest (Level 40) - Intermediate difficulty
3. Late Mountain (Level 60) - End-game difficulty

# Narrative Structure

Each narrative must define:

## 1. Basic Information
- **Name**: Short, evocative title (e.g., "Team Magma's Search", "Professor's Expedition")
- **Description**: 1-2 sentence story hook explaining why these trainers/Pokémon are here
- **Dungeon Tier**: Which dungeon this narrative is for (Cave/Forest/Mountain)

## 2. Trainer Configuration
- **Trainer Types**: 2-4 different trainer classes that fit the theme
  - Each needs a trainer class (e.g., TRAINER_CLASS_TEAM_MAGMA, TRAINER_CLASS_HIKER)
  - Each needs a sprite (e.g., OBJ_EVENT_GFX_MAGMA_GRUNT_M, OBJ_EVENT_GFX_HIKER)
  - Trainers use randomized teams from the party pool (2-3 Pokémon each)

## 3. Party Pool
- **Species List**: 7-12 Pokémon species that fit the narrative theme
  - Must be thematically coherent (type-based, faction-based, or story-based)
  - Should have variety in roles (physical attackers, special attackers, tanks, etc.)
  - Examples: Fire/Ground types for Team Magma, Rock types for Hikers, etc.

## 4. Wild Encounter Table (12 slots)
- **Common (Slots 0-1)**: 20% each - Frequently encountered Pokémon
- **Uncommon (Slots 2-5)**: 10% each - Moderately rare
- **Rare (Slots 6-7)**: 5% each - Less common
- **Very Rare (Slots 8-9)**: 4% each - Rare encounters
- **Ultra Rare (Slots 10-11)**: 1% each - Extremely rare

Requirements:
- Level ranges should fit the dungeon tier (±2 levels from base)
- Should overlap with party pool for thematic consistency
- Can include evolutions/pre-evolutions for variety
- Should have 6-8 unique species across all slots

## 5. Boss Configuration
**Option A - Trainer Boss (Recommended):**
- Trainer class and name (e.g., "Team Magma Admin")
- Uses party pool for randomized team (4-6 Pokémon)
- Sprite/graphics ID

**Option B - Pokémon Boss (Simplified):**
- Single powerful Pokémon
- Level, held item, stat boosts

## 6. Reward Items (3 tiers)
- **Tier 1 (Bronze)**: Common/utility (0-44 points)
- **Tier 2 (Silver)**: Valuable (45-69 points)
- **Tier 3 (Gold)**: Rare/powerful (70+ points)
- Should thematically match the narrative

# Example Narrative

**Name:** "Team Magma's Search"
**Description:** "Team Magma seeks an ancient artifact deep in the cave!"
**Dungeon Tier:** Early Cave (Level 20)

**Trainers:**
- Team Magma Grunt (M) - OBJ_EVENT_GFX_TEAM_MAGMA_GRUNT_M
- Team Magma Grunt (F) - OBJ_EVENT_GFX_TEAM_MAGMA_GRUNT_F

**Party Pool:** Numel, Camerupt, Torkoal, Baltoy, Claydol, Houndour, Houndoom

**Wild Encounters:**
- Common: Numel (18-20)
- Uncommon: Torkoal, Baltoy (19-21)
- Rare: Camerupt (20-22)
- Very Rare: Houndour (21-23)
- Ultra Rare: Houndoom (22-24)

**Boss:** Team Magma Admin with 4-6 randomized Fire/Ground types

**Rewards:**
- Bronze: Charcoal
- Silver: Fire Stone
- Gold: Heat Rock

# Your Task

Generate 3-5 creative narrative ideas for [SPECIFY DUNGEON TIER]. For each narrative, provide:

1. **Narrative Concept**
   - Name
   - Description (story hook)
   - Core theme/inspiration

2. **Trainer Setup**
   - 2-4 trainer types with justification
   - Why they're in this dungeon

3. **Party Pool**
   - 7-12 species list
   - Explain the thematic connection
   - Type composition and strategy

4. **Wild Encounter Design**
   - 6-8 unique species
   - Rarity distribution logic
   - How they fit the environment

5. **Boss Concept**
   - Boss identity/title
   - Team composition (if trainer) or single Pokémon (if Pokémon boss)
   - What makes this boss memorable

6. **Reward Theming**
   - 3 items (Bronze/Silver/Gold)
   - Why these rewards fit the narrative

# Creative Guidelines

**DO:**
- Use existing Pokémon lore (Teams Magma/Aqua, researchers, explorers, rangers)
- Create interesting type combinations
- Think about environmental storytelling
- Consider NPC motivations (why are they here?)
- Mix common and rare Pokémon appropriately

**DON'T:**
- Create narratives that require new Pokémon species
- Suggest legendary Pokémon as common encounters
- Ignore the dungeon's environmental context (cave/forest/mountain)
- Make party pools too narrow (need variety for randomization)
- Suggest items that don't exist in Gen 3 (if working with vanilla items)

# Additional Context

- This is for Pokémon Emerald (Generation 3)
- System supports rotation - narratives should feel fresh and distinct
- Players will see these repeatedly, so variety and replayability matter
- Narratives can reference post-game content or rare events
- Can include humorous, mysterious, or serious tones

Please generate narrative ideas now!
```

## How to Use This Prompt

1. **Copy the entire prompt** to your preferred LLM (Claude, ChatGPT, etc.)
2. **Specify the dungeon tier** in the "Your Task" section:
   - `[SPECIFY DUNGEON TIER]` → "Early Cave", "Mid Forest", or "Late Mountain"
3. **Optional**: Add additional constraints:
   - "Focus on Team Aqua/Magma narratives"
   - "Create scientist/researcher themed narratives"
   - "Include a humorous narrative"
   - "Avoid using [specific types/Pokémon]"
4. **Review output** and select the most implementable ideas
5. **Refine** if needed by asking follow-up questions about specific aspects

## Tips for Best Results

- **Be specific** about which dungeon tier you're generating for
- **Request multiple iterations** if you want more variety
- **Ask for refinements** on specific aspects (e.g., "make the party pool more diverse")
- **Combine ideas** from different generated narratives
- **Validate** that all suggested Pokémon exist and fit the level range
- **Check feasibility** of trainer sprites (some may not exist in the base game)

---

# Developer Guides

## Creating a New Narrative

### Step 1: Define Party Pool (src/data/trainer_parties.h)

```c
// Team Magma party pool - fire/ground Pokemon
static const u16 sPartyPool_CaveMagma[] = {
    SPECIES_NUMEL,
    SPECIES_CAMERUPT,
    SPECIES_TORKOAL,
    SPECIES_BALTOY,
    SPECIES_CLAYDOL,
    SPECIES_HOUNDOUR,
    SPECIES_HOUNDOOM,
};
```

### Step 2: Create Template Trainers (src/data/trainers.party)

```c
[TRAINER_DUNGEON_MAGMA_GRUNT_M] =
{
    .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
    .trainerPic = TRAINER_PIC_MAGMA_GRUNT_M,
    .trainerName = _("Grunt"),
    .items = {},
    .doubleBattle = FALSE,
    .aiFlags = AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_TRY_TO_FAINT,
    .party = TRAINER_PARTY_FROM_POOL(sPartyPool_CaveMagma, 2, 3),  // 2-3 mons from pool
},

[TRAINER_DUNGEON_BOSS_MAGMA_ADMIN] =
{
    .trainerClass = TRAINER_CLASS_TEAM_MAGMA,
    .trainerPic = TRAINER_PIC_MAGMA_ADMIN,
    .trainerName = _("Admin"),
    .party = TRAINER_PARTY_FROM_POOL(sPartyPool_CaveMagma, 4, 6),  // 4-6 mons (boss)
},
```

### Step 3: Define Dialog Text (src/data/narratives/cave_narratives.h)

```c
// === TEAM MAGMA'S SEARCH - DIALOG TEXT ===

// Trainer dialog (3-5 variations recommended)
static const u8 sCaveMagma_TrainerIntro1[] = _("Team Magma will prevail!");
static const u8 sCaveMagma_TrainerIntro2[] = _("Out of my way, intruder!");
static const u8 sCaveMagma_TrainerIntro3[] = _("You'll never stop Team Magma!");

static const u8 sCaveMagma_TrainerDefeat1[] = _("Team Magma won't forget this...");
static const u8 sCaveMagma_TrainerDefeat2[] = _("Impossible!");
static const u8 sCaveMagma_TrainerDefeat3[] = _("I've failed the mission!");

// Boss dialog (2-3 variations recommended)
static const u8 sCaveMagma_BossIntro1[] = _(
    "You've made it this far...\n"
    "But this is where your run ends!"
);
static const u8 sCaveMagma_BossIntro2[] = _(
    "So, you're the one interfering\n"
    "with Team Magma's operations!"
);

static const u8 sCaveMagma_BossDefeat1[] = _("Impossible...!");
static const u8 sCaveMagma_BossDefeat2[] = _("You're stronger than I thought.");

static const u8 sCaveMagma_BossVictory1[] = _("Boss trainer defeated!");
static const u8 sCaveMagma_BossVictory2[] = _("Team Magma retreats in defeat!");

// Text arrays (use const pointers to const strings)
static const u8 * const sCaveMagma_TrainerIntroTexts[] = {
    sCaveMagma_TrainerIntro1,
    sCaveMagma_TrainerIntro2,
    sCaveMagma_TrainerIntro3,
};

static const u8 * const sCaveMagma_TrainerDefeatTexts[] = {
    sCaveMagma_TrainerDefeat1,
    sCaveMagma_TrainerDefeat2,
    sCaveMagma_TrainerDefeat3,
};

static const u8 * const sCaveMagma_BossIntroTexts[] = {
    sCaveMagma_BossIntro1,
    sCaveMagma_BossIntro2,
};

static const u8 * const sCaveMagma_BossDefeatTexts[] = {
    sCaveMagma_BossDefeat1,
    sCaveMagma_BossDefeat2,
};

static const u8 * const sCaveMagma_BossVictoryTexts[] = {
    sCaveMagma_BossVictory1,
    sCaveMagma_BossVictory2,
};
```

### Step 4: Define Narrative Structure (src/data/narratives/cave_narratives.h)

**Note:** Narratives are now organized in modular files by dungeon type:
- Cave narratives → `src/data/narratives/cave_narratives.h`
- Forest narratives → `src/data/narratives/forest_narratives.h`
- Mountain narratives → `src/data/narratives/mountain_narratives.h`

```c
// === TEAM MAGMA'S SEARCH ===

// Trainer pool - references the template trainers
static const struct DungeonTrainerEntry sCaveMagma_TrainerPool[] = {
    { .trainerId = TRAINER_DUNGEON_MAGMA_GRUNT_M, .graphicsId = OBJ_EVENT_GFX_TEAM_MAGMA_GRUNT_M },
    { .trainerId = TRAINER_DUNGEON_MAGMA_GRUNT_F, .graphicsId = OBJ_EVENT_GFX_TEAM_MAGMA_GRUNT_F },
};

// Wild encounters - 12 slots
static const struct WildPokemon sCaveMagma_LandMons[] = {
    { 18, 20, SPECIES_NUMEL },      // 20% - Slot 0
    { 18, 20, SPECIES_NUMEL },      // 20% - Slot 1
    { 19, 21, SPECIES_TORKOAL },    // 10% - Slot 2
    { 19, 21, SPECIES_TORKOAL },    // 10% - Slot 3
    { 18, 20, SPECIES_BALTOY },     // 10% - Slot 4
    { 19, 21, SPECIES_BALTOY },     // 10% - Slot 5
    { 20, 22, SPECIES_CAMERUPT },   // 5%  - Slot 6
    { 20, 22, SPECIES_CAMERUPT },   // 5%  - Slot 7
    { 21, 23, SPECIES_HOUNDOUR },   // 4%  - Slot 8 (rare)
    { 21, 23, SPECIES_HOUNDOUR },   // 4%  - Slot 9 (rare)
    { 22, 24, SPECIES_HOUNDOOM },   // 1%  - Slot 10 (very rare)
    { 22, 24, SPECIES_HOUNDOOM },   // 1%  - Slot 11 (very rare)
};

static const struct WildPokemonInfo sCaveMagma_LandMonsInfo = {
    .encounterRate = 4,  // 4/256 = ~1.5% per step
    .wildPokemon = sCaveMagma_LandMons
};

// Reward items - POOLS for randomization
static const u16 sCaveMagma_BronzeRewardPool[] = {
    ITEM_BURN_HEAL,
    ITEM_ICE_HEAL,
    ITEM_PARALYZE_HEAL,
};

static const u16 sCaveMagma_SilverRewardPool[] = {
    ITEM_TM_FLAMETHROWER,
    ITEM_TM_FIRE_BLAST,
    ITEM_TM_SUNNY_DAY,
};

static const u16 sCaveMagma_GoldRewardPool[] = {
    ITEM_CHARCOAL,
    ITEM_HEAT_ROCK,
};

static const u16 * const sCaveMagma_RewardPools[] = {
    sCaveMagma_BronzeRewardPool,
    sCaveMagma_SilverRewardPool,
    sCaveMagma_GoldRewardPool,
};

static const u8 sCaveMagma_RewardPoolSizes[] = {
    ARRAY_COUNT(sCaveMagma_BronzeRewardPool),
    ARRAY_COUNT(sCaveMagma_SilverRewardPool),
    ARRAY_COUNT(sCaveMagma_GoldRewardPool),
};

// Complete narrative definition
static const struct DungeonNarrative gNarrative_CaveMagma = {
    .id = NARRATIVE_CAVE_MAGMA,
    .name = _("Team Magma's Search"),
    .description = _("Team Magma seeks an ancient\nartifact deep in the cave!$"),

    // Trainers
    .trainerCount = ARRAY_COUNT(sCaveMagma_TrainerPool),
    .trainerPool = sCaveMagma_TrainerPool,

    // Wild encounters
    .landEncounters = &sCaveMagma_LandMonsInfo,
    .waterEncounters = NULL,

    // Boss
    .bossType = BOSS_TYPE_TRAINER,
    .boss = {
        .trainer = {
            .trainerId = TRAINER_DUNGEON_BOSS_MAGMA_ADMIN,
            .graphicsId = OBJ_EVENT_GFX_MAGMA_ADMIN,
        }
    },

    // Rewards
    .rewardItemPools = sCaveMagma_RewardPools,
    .rewardPoolSizes = sCaveMagma_RewardPoolSizes,
    .rewardTierCount = ARRAY_COUNT(sCaveMagma_RewardPools),

    // Dialog text
    .trainerIntroTexts = sCaveMagma_TrainerIntroTexts,
    .trainerIntroTextCount = ARRAY_COUNT(sCaveMagma_TrainerIntroTexts),
    .trainerDefeatTexts = sCaveMagma_TrainerDefeatTexts,
    .trainerDefeatTextCount = ARRAY_COUNT(sCaveMagma_TrainerDefeatTexts),
    .bossIntroTexts = sCaveMagma_BossIntroTexts,
    .bossIntroTextCount = ARRAY_COUNT(sCaveMagma_BossIntroTexts),
    .bossDefeatTexts = sCaveMagma_BossDefeatTexts,
    .bossDefeatTextCount = ARRAY_COUNT(sCaveMagma_BossDefeatTexts),
    .bossVictoryTexts = sCaveMagma_BossVictoryTexts,
    .bossVictoryTextCount = ARRAY_COUNT(sCaveMagma_BossVictoryTexts),
};
```

### Step 5: Add to Narrative Arrays (Two Steps)

**5a. Add to main narrative array** (src/data/dungeon_narratives.h):
```c
// At bottom of file, in gDungeonNarratives array
static const struct DungeonNarrative gDungeonNarratives[NARRATIVE_COUNT] = {
    [NARRATIVE_NONE] = gNarrative_None,
    [NARRATIVE_CAVE_TEST] = gNarrative_CaveTest,
    [NARRATIVE_CAVE_MAGMA] = gNarrative_CaveMagma,  // ← Add here
    // ... more narratives
};
```

**5b. Add to dungeon-specific pool** (src/data/dungeon_narratives.h):
```c
// Add to appropriate pool near top of file
static const u8 sCaveNarrativePool[] = {
    NARRATIVE_CAVE_TEST,
    NARRATIVE_CAVE_MAGMA,  // ← Add here
    // ... more cave narratives
};
```

**Note:** The modular narrative file (cave_narratives.h) is automatically included via `#include "narratives/cave_narratives.h"` in dungeon_narratives.h.

### Step 6: Add Enum (include/constants/dungeons.h)

```c
enum DungeonNarratives {
    NARRATIVE_NONE,
    NARRATIVE_CAVE_TEST,
    NARRATIVE_CAVE_MAGMA,  // ← Add here
    // ...
    NARRATIVE_COUNT
};
```

## Creating a Modifier

**File:** `src/data/dungeon_modifiers.h`

```c
// Define text strings
static const u8 sModifierSun_Name[] = _("Eternal Sunshine");
static const u8 sModifierSun_Description[] = _("Harsh sunlight shines\pthroughout the dungeon.$");

// Define modifier struct
static const struct DungeonModifier gModifier_PermanentSun = {
    .id = MODIFIER_PERMANENT_SUN,
    .name = sModifierSun_Name,
    .description = sModifierSun_Description,
    .weatherOrTerrain = STARTING_STATUS_SUN,
    .weatherDuration = 0,  // 0 = infinite
    .battleTypeFlags = 0,
    .levelModifier = 0,
    .expMultiplier = 1,
    .moneyMultiplier = 1,
};

// Add to global modifier array
static const struct DungeonModifier gDungeonModifiers[MODIFIER_COUNT] = {
    [MODIFIER_NONE] = gModifier_None,
    [MODIFIER_PERMANENT_SUN] = gModifier_PermanentSun,  // ← Add here
    // ...
};

// Add to dungeon-specific pool (in config/dungeon.h)
#define DUNGEON_CAVE_MODIFIERS \
    MODIFIER_PERMANENT_SUN, \    // ← Add here
    MODIFIER_PERMANENT_SANDSTORM, \
    // ...
```

## Encounter Slot Distribution

The 12-slot wild encounter system uses this distribution:
- **Slots 0-1**: 20% each (common)
- **Slots 2-5**: 10% each (uncommon)
- **Slots 6-7**: 5% each (rare)
- **Slots 8-9**: 4% each (very rare)
- **Slots 10-11**: 1% each (ultra rare)

---

## Future Work

### Potential Enhancements
- Pokémon as rewards instead of items
- Dynamic level scaling based on player's team average
- Modifier application hooks (level adjustment, EXP/money multipliers)
- Additional refresh modes (hourly, bi-weekly)
- Cross-dungeon completion tracking and meta-progression

### Content Expansion
- Complete forest and mountain dungeon maps
- Additional narratives for all three tiers (target: 5-10 per dungeon)
- More modifiers (terrain effects, ability changes, held item modifications)
- Seasonal or event-based narratives

---

**End of Documentation**
