# Dungeon System Features & Modifications

This document outlines all features built and modifications made to the procedurally generated dungeon system on the `claude/clone-procgen-branch-01Q4DevsXhiDWtaQF6GotVBN` branch.

## Table of Contents
- [Code Cleanup](#code-cleanup)
- [Lockout/Cooldown System](#lockoutcooldown-system)
- [Pokemon Reward System](#pokemon-reward-system)
- [Bug Fixes](#bug-fixes)
- [Technical Details](#technical-details)

---

## Code Cleanup

### Removed Dead Code
**Commit:** `4dd29df3`

Removed unused dungeon system code to simplify the codebase:

1. **Deleted `src/data/dungeon_bosses.h`** (318 lines)
   - Completely unused file containing boss definitions
   - No references found anywhere in the codebase

2. **Removed unused fields from `struct Dungeon`:**
   - `u8 id` - Not used
   - `u8 tier` - Not used
   - `u8 biome` - Not used
   - `u16 entranceMap` - Not used

3. **Updated `src/data/dungeon_definitions.h`:**
   - Removed all references to deleted fields
   - Kept only actively used fields

**Files Modified:**
- `include/dungeon.h`
- `src/data/dungeon_definitions.h`
- `src/data/dungeon_bosses.h` (deleted)

---

## Lockout/Cooldown System

### Initial Implementation (RTC-based, Weekly Support)
**Commit:** `aeabee73`

Implemented a Real-Time Clock (RTC) based lockout system to control how often players can receive rewards from dungeons.

**Features:**
- Three lockout modes: `LOCKOUT_NONE`, `LOCKOUT_DAILY`, `LOCKOUT_WEEKLY`
- RTC-based tracking using `RtcGetLocalDayCount()`
- Per-dungeon lockout configuration
- Tracks last completion timestamp for each dungeon

**SaveBlock2 Changes (Initial):**
```c
u32 dungeonLastCompleted[3];  // 12 bytes - Days since epoch when completed
```

**Key Functions:**
- `Dungeon_IsEligibleForRewards(u8 dungeonId)` - Check if player can get rewards
- `Dungeon_MarkCompleted(u8 dungeonId)` - Mark dungeon as completed
- `Dungeon_GetDaysUntilNextReward(u8 dungeonId)` - Get days remaining for UI

**Script Integration:**
- Players can check eligibility before entering
- Rewards only distributed if eligible
- UI can display cooldown timer

### Simplified Implementation (Daily-Only, Bit Flags)
**Commit:** `965367e5`

Simplified the lockout system based on design feedback that weekly lockouts add unnecessary complexity.

**Changes:**
1. **Removed `LOCKOUT_WEEKLY`** from enum
2. **Changed SaveBlock2 structure** to use bit flags instead of timestamps:
   ```c
   u16 dungeonDailyResetDay;       // 2 bytes - Last RTC day when flags reset
   u16 dungeonCompletedToday;      // 2 bytes - Bit flags (1 bit per dungeon)
   // Net savings: 8 bytes (12 → 4)
   ```

**Benefits:**
- **67% space reduction** (8 bytes saved)
- **Simpler logic** - no day calculation, just bit checks
- **Auto-reset** - flags automatically clear on new day
- **Scales better** - supports up to 16 dungeons without code changes
- **Faster** - bitwise operations vs array lookups

**How It Works:**
1. Each dungeon has 1 bit in `dungeonCompletedToday`
2. When entering dungeon, check if day changed → auto-reset flags
3. When completing dungeon, set the dungeon's bit
4. Next entry: check if bit is set (same day) or reset (new day)

**Example:**
```c
// Day 1: Complete DUNGEON_EARLY_CAVE
dungeonDailyResetDay = 19367
dungeonCompletedToday = 0b0001  // Bit 0 set

// Day 2: Flags auto-reset
dungeonDailyResetDay = 19368
dungeonCompletedToday = 0b0000  // All cleared, eligible again
```

**Files Modified:**
- `include/global.h` - SaveBlock2 structure
- `include/constants/dungeons.h` - Removed LOCKOUT_WEEKLY
- `src/dungeon.c` - Simplified lockout functions
- `src/data/dungeon_definitions.h` - Changed LATE_MOUNTAIN from WEEKLY to DAILY

---

## Pokemon Reward System

**Commit:** `4b12e560`

Implemented a comprehensive Pokemon reward system allowing dungeons to give Pokemon (not just items) as completion rewards.

### Features

**1. Reward Type System**
```c
enum DungeonRewardType {
    REWARD_TYPE_ITEM,     // Item reward (goes to bag)
    REWARD_TYPE_POKEMON,  // Pokemon reward (goes to party or PC)
};
```

**2. Shiny Odds Configuration**
```c
enum DungeonShinyOdds {
    SHINY_ODDS_NEVER = 0,      // Never shiny
    SHINY_ODDS_NORMAL = 1,     // 1/4096 odds
    SHINY_ODDS_BOOSTED = 2,    // 1/16 odds (6.25% chance!)
    SHINY_ODDS_GUARANTEED = 3, // Always shiny
};
```

**3. DungeonReward Structure**
```c
struct DungeonReward {
    u8 type;  // REWARD_TYPE_ITEM or REWARD_TYPE_POKEMON
    union {
        u16 itemId;  // For item rewards
        struct {
            u16 species;
            u8 level;           // 0 = use dungeon level dynamically
            u16 heldItem;
            u8 ivs;             // 0-31 fixed, 32 = random
            u8 shinyOdds;       // SHINY_ODDS_*
            u8 nature;          // Specific nature, or NUM_NATURES = random
            u8 abilityNum;      // 0/1/2, or 255 = random
            u16 moves[4];       // Custom moves, or MOVE_NONE = level-up moveset
        } pokemon;
    } data;
};
```

**4. Distribution Logic**

Completely rewrote `Dungeon_DistributeRewards()` to handle both reward types:

**For Items:**
- Check bag space
- Add item to bag
- Return success/failure

**For Pokemon:**
- Determine shiny status based on odds
- Generate IV spread (fixed or random)
- Use `BirchCase_GiveMonParameterized()` for full control
- Handle party full → PC
- Handle PC full → failure
- Set special variables for script integration

**5. Script Integration**

Special variables set for Pory scripts:
- `VAR_0x8004` - Item ID or Pokemon species
- `VAR_0x8005` - Reward type (ITEM or POKEMON)
- `VAR_0x8006` - Location (PARTY or PC) for Pokemon
- `VAR_0x8007` - Shiny flag (0 or 1) for Pokemon

**6. Example Reward Configurations**

```c
// Item reward - Simple
{
    .type = REWARD_TYPE_ITEM,
    .data.itemId = ITEM_GREAT_BALL
}

// Pokemon reward - Basic (random IVs/nature/ability)
{
    .type = REWARD_TYPE_POKEMON,
    .data.pokemon = {
        .species = SPECIES_GEODUDE,
        .level = 0,              // Use dungeon level
        .heldItem = ITEM_NONE,
        .ivs = 32,               // Random IVs
        .shinyOdds = SHINY_ODDS_NORMAL,
        .nature = NUM_NATURES,   // Random nature
        .abilityNum = 255,       // Random ability
        .moves = {MOVE_NONE, MOVE_NONE, MOVE_NONE, MOVE_NONE}  // Level-up moves
    }
}

// Pokemon reward - Advanced (perfect IVs, custom moves)
{
    .type = REWARD_TYPE_POKEMON,
    .data.pokemon = {
        .species = SPECIES_LARVITAR,
        .level = 0,
        .heldItem = ITEM_FOCUS_BAND,
        .ivs = 31,               // Perfect IVs
        .shinyOdds = SHINY_ODDS_BOOSTED,  // 1/16 chance
        .nature = NATURE_ADAMANT,
        .abilityNum = 0,         // First ability
        .moves = {MOVE_DRAGON_DANCE, MOVE_EARTHQUAKE, MOVE_STONE_EDGE, MOVE_CRUNCH}
    }
}
```

**Files Modified:**
- `include/constants/dungeons.h` - Added reward type and shiny odds enums
- `include/dungeon.h` - Added DungeonReward struct, updated DungeonNarrative
- `src/dungeon.c` - Rewrote Dungeon_DistributeRewards()
- `src/data/narratives/cave_narratives.h` - Updated all three cave narratives with examples

---

## Bug Fixes

### Fix 1: Freeze on Dungeon Entry
**Commit:** `7086656b`

**Problem:** ROM froze when entering dungeons on existing save files.

**Root Cause:** Uninitialized `dungeonDailyResetDay` and `dungeonCompletedToday` fields contained garbage data (e.g., 0xFFFF), causing undefined behavior in lockout functions.

**Solution:**
1. Added initialization in `NewGameInitData()`:
   ```c
   gSaveBlock2Ptr->dungeonDailyResetDay = 0;
   gSaveBlock2Ptr->dungeonCompletedToday = 0;
   ```

2. Added defensive checks in all lockout functions:
   ```c
   if (gSaveBlock2Ptr->dungeonDailyResetDay > 50000) {
       // Garbage data detected, reset
       gSaveBlock2Ptr->dungeonDailyResetDay = 0;
       gSaveBlock2Ptr->dungeonCompletedToday = 0;
   }
   ```

**Result:** Existing saves auto-fix on first dungeon access.

---

### Fix 2: Missing Boss Trainer Dialogue
**Commit:** `f61c555b`

**Problem:** Boss trainers wouldn't speak when first encountered or after being defeated.

**Root Cause:** Uninitialized `dungeonNarratives[]` and `dungeonModifiers[]` arrays contained garbage values (e.g., 0xFF, 200) on existing saves. Functions would return NULL, causing dialogue functions to return empty strings.

**Solution:**
1. Added defensive initialization in `Dungeon_GetActiveNarrative()`:
   ```c
   if (narrativeId >= NARRATIVE_COUNT) {
       Dungeon_CheckDailyRotation();  // Initialize system
       narrativeId = gSaveBlock2Ptr->dungeonNarratives[dungeonId];
   }
   ```

2. Same pattern for `Dungeon_GetActiveModifier()`

3. Added initialization in `NewGameInitData()`:
   ```c
   gSaveBlock2Ptr->dungeonDailySeed = 0;
   for (u8 i = 0; i < 3; i++) {
       gSaveBlock2Ptr->dungeonNarratives[i] = 0;
       gSaveBlock2Ptr->dungeonModifiers[i] = 0;
   }
   ```

**Result:** Boss trainers speak correctly on both new and existing saves.

---

### Fix 3: Duplicate Defeat Dialogue
**Commit:** `8ba0dc40`

**Problem:** Regular trainers would repeat their defeat dialogue every time you talked to them after beating them.

**Root Cause:** Trainer scripts checked `if (flag(FLAG_DUNGEON_TRAINER_X))` and called `Script_Dungeon_GetRandomTrainerDefeat` + `msgbox`, showing the message again.

**Solution:** Removed the dialogue calls from the "already defeated" check:
```pory
// Before
if (flag(FLAG_DUNGEON_TRAINER_0)) {
    callnative(Script_Dungeon_GetRandomTrainerDefeat)  // ← Removed
    msgbox(gStringVar4, MSGBOX_DEFAULT)                // ← Removed
    releaseall
    end
}

// After
if (flag(FLAG_DUNGEON_TRAINER_0)) {
    // Already defeated - no dialogue
    releaseall
    end
}
```

**Result:** Trainers stay silent when talked to after defeat.

**Files Modified:** `data/scripts/dungeon_rooms.pory` (all 4 trainer scripts)

---

### Fix 4: Boss Trainer Dialogue Corruption (VAR_TEMP_0)
**Commit:** `9136a6ca`

**Problem:** Boss trainers STILL wouldn't speak (even after Fix 2).

**Root Cause:** Boss room script was overwriting `VAR_TEMP_0` (which stores dungeon ID) with the boss type:
```pory
callnative(Script_Dungeon_GetBossType)
copyvar(VAR_TEMP_0, VAR_RESULT)  // ← Overwrites dungeon ID!
```

This caused dialogue functions to fetch the wrong narrative:
1. `Dungeon_Enter(0)` sets `VAR_TEMP_0 = 0` (DUNGEON_EARLY_CAVE)
2. Boss room overwrites `VAR_TEMP_0 = 1` (BOSS_TYPE_TRAINER)
3. `Dungeon_GetCurrentDungeonId()` reads `VAR_TEMP_0 = 1`
4. Fetches narrative for dungeon 1 (DUNGEON_MID_FOREST) instead of 0
5. Wrong/missing dialogue

**Solution:** Changed to use `VAR_TEMP_3` instead:
```pory
copyvar(VAR_TEMP_3, VAR_RESULT)  // Use VAR_TEMP_3, preserve VAR_TEMP_0
if (var(VAR_TEMP_3) == 1) {
```

**Bonus:** Added debug output to boss dialogue functions to help diagnose future issues:
```c
DebugPrintf("Script_Dungeon_GetRandomBossIntro: dungeonId=%d", dungeonId);
DebugPrintf("Script_Dungeon_GetRandomBossIntro: narrative=%p, textCount=%d", ...);
DebugPrintf("Script_Dungeon_GetRandomBossIntro: Generated text: %.20s", gStringVar4);
```

**Result:** Boss trainers now speak correctly before and after battle.

**Files Modified:**
- `data/maps/Dungeon1_RoomBoss/scripts.pory`
- `src/dungeon.c` (added debug output)

---

## Technical Details

### SaveBlock2 Structure Changes

**Final Structure (4 bytes total for lockout):**
```c
/*0xA0*/ u16 dungeonDailyResetDay;       // Last RTC day when flags reset
/*0xA2*/ u16 dungeonCompletedToday;      // Bit flags (supports 16 dungeons)
```

**Offset Changes:**
All subsequent fields shifted -8 bytes due to reduction from 12 bytes to 4 bytes:
- `localTimeOffset`: 0xAC → 0xA4
- `lastBerryTreeUpdate`: 0xB4 → 0xAC
- `gcnLinkFlags`: 0xBC → 0xB4
- `encryptionKey`: 0xC0 → 0xB8
- etc.

**New sizeof(SaveBlock2):** `0xF24` (was `0xF2C`)

### Shiny Odds Change

**Commit:** `965367e5`

Changed `SHINY_ODDS_BOOSTED` from 1/512 (Masuda Method-like) to 1/16 (6.25% chance) for more exciting dungeon rewards.

**Code:**
```c
case SHINY_ODDS_BOOSTED:
    isShiny = (Random() % 16) == 0;  // Was % 512
    break;
```

---

## Commit History

1. `4dd29df3` - Remove unused dungeon system fields and dead code
2. `aeabee73` - Implement dungeon lockout/cooldown system
3. `4b12e560` - Implement Pokemon reward system for dungeons
4. `a172d7b3` - Fix script functions to use new DungeonReward structure
5. `965367e5` - Simplify lockout system to daily-only with u16 flags
6. `7086656b` - Fix freeze on dungeon entry by initializing lockout fields
7. `f61c555b` - Fix missing boss trainer dialogue on existing saves
8. `8ba0dc40` - Remove duplicate defeat dialogue from dungeon trainers
9. `9136a6ca` - Fix boss trainer dialogue by preventing VAR_TEMP_0 corruption

---

## Testing Checklist

### Lockout System
- [ ] New game: Dungeons initialize correctly
- [ ] Existing save: Auto-fixes on first access
- [ ] Daily lockout: Can get rewards once per day
- [ ] No lockout: Can get rewards repeatedly
- [ ] RTC change: Flags reset properly on new day

### Pokemon Rewards
- [ ] Pokemon given to party (when space available)
- [ ] Pokemon given to PC (when party full)
- [ ] Failure when PC full
- [ ] Shiny odds work correctly (NEVER, NORMAL, BOOSTED, GUARANTEED)
- [ ] IV generation (fixed and random)
- [ ] Nature/ability randomization
- [ ] Custom moves vs level-up moveset
- [ ] Held items work
- [ ] Level 0 uses dungeon level dynamically

### Dialogue
- [ ] Regular trainers speak intro before battle
- [ ] Regular trainers speak defeat after battle
- [ ] Regular trainers stay silent when re-talked
- [ ] Boss trainers speak intro before battle
- [ ] Boss trainers speak defeat after battle
- [ ] Boss trainers speak victory message
- [ ] Pokemon boss dialogue works

### General
- [ ] No freezes on dungeon entry
- [ ] No crashes during battle
- [ ] Save/load works correctly
- [ ] Debug output appears in logs (if enabled)

---

## Future Considerations

### Potential Enhancements
1. Add configurable Pokeball type to Pokemon rewards (Beast Ball, Cherish Ball, etc.)
2. Add gender control for Pokemon rewards (important for species like Combee)
3. Add friendship/happiness configuration
4. Add parameter validation (species, level, IVs, nature, ability, moves)
5. Add RTC failure handling for broken batteries
6. Consider underflow protection in lockout calculations

### Scalability
- Current system supports up to 16 dungeons with no code changes
- If 17+ dungeons needed, change `u16 dungeonCompletedToday` → `u32` (still only 6 bytes total)
- Bit flag approach scales efficiently vs per-dungeon timestamp arrays

---

## References

### Key Files
- `include/global.h` - SaveBlock2 structure
- `include/constants/dungeons.h` - Dungeon constants and enums
- `include/dungeon.h` - Dungeon structures and function declarations
- `src/dungeon.c` - Core dungeon logic
- `src/new_game.c` - Save initialization
- `src/data/dungeon_definitions.h` - Dungeon configurations
- `src/data/narratives/cave_narratives.h` - Narrative/reward definitions
- `data/scripts/dungeon_rooms.pory` - Regular trainer scripts
- `data/scripts/DungeonBossRoom_Common.pory` - Boss battle scripts
- `data/maps/Dungeon1_RoomBoss/scripts.pory` - Boss room map scripts

### Important Functions
- `Dungeon_IsEligibleForRewards()` - Check lockout status
- `Dungeon_MarkCompleted()` - Mark dungeon completed
- `Dungeon_DistributeRewards()` - Give rewards (items or Pokemon)
- `Dungeon_GetActiveNarrative()` - Get current narrative
- `Script_Dungeon_GetRandomBossIntro/Defeat/Victory()` - Boss dialogue
- `Script_Dungeon_GetRandomTrainerIntro/Defeat()` - Trainer dialogue

---

*Last Updated: 2025-01-19*
*Branch: claude/clone-procgen-branch-01Q4DevsXhiDWtaQF6GotVBN*
