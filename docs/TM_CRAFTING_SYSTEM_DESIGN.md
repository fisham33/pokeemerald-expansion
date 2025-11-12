# TM Crafting System Design Document

## Overview

This document describes the implementation of a TM (Technical Machine) crafting system inspired by Pokémon Scarlet and Violet. The system allows players to craft TMs using materials dropped by wild Pokémon and a currency cost (League Points or PokéDollars).

## Table of Contents

1. [System Overview](#system-overview)
2. [Core Mechanics](#core-mechanics)
3. [Technical Architecture](#technical-architecture)
4. [Data Structures](#data-structures)
5. [Implementation Details](#implementation-details)
6. [UI/UX Design](#uiux-design)
7. [Integration Points](#integration-points)
8. [Testing Strategy](#testing-strategy)

---

## System Overview

### Concept
The TM crafting system introduces renewable TMs through a crafting mechanic where:
- Wild Pokémon drop **materials** when defeated or caught
- Players collect these materials and use them to craft TMs
- Each TM recipe requires specific materials and a currency cost
- TMs must be "unlocked" before they can be crafted

### Key Features
1. **Material System**: New item category for crafting materials
2. **Recipe System**: Database of TM recipes with material requirements
3. **Crafting UI**: Dedicated menu for browsing and crafting TMs
4. **Material Drops**: Wild Pokémon drop materials based on their species
5. **Recipe Unlocking**: TMs must be found/obtained once before crafting is available

---

## Core Mechanics

### 1. Material Drops

**How Materials Drop:**
- When a wild Pokémon is defeated or caught, it has a chance to drop materials
- Materials are species-specific (e.g., "Rattata Fang", "Pikachu Fur", "Geodude Rock")
- Drop rates can be influenced by:
  - Base drop rate (e.g., 50-100% per encounter)
  - Item effects (e.g., "Amulet Coin" equivalent for materials)
  - Special abilities (e.g., "Pickup" ability)

**Material Types:**
- Each Pokémon species has 1-2 associated material types
- Materials are named after the Pokémon (e.g., "Shinx Fang", "Starly Feather")
- Evolutionary families share materials (e.g., Shinx, Luxio, and Luxray all drop "Shinx Fang")

**Implementation:**
```
Upon wild battle victory or capture:
1. Check if Pokémon drops materials
2. Roll drop chance (base 75%)
3. Determine quantity (1-3 items, weighted toward 1-2)
4. Add material to player's bag
5. Display "You obtained [quantity]x [Material Name]!"
```

### 2. Recipe System

**Recipe Structure:**
Each TM recipe consists of:
- **Output**: The TM being crafted (e.g., TM01 - Focus Blast)
- **Materials**: 1-4 different material requirements with quantities
- **Cost**: League Points or PokéDollars (typically 800-10000 depending on TM power)
- **Unlock Status**: Whether the player has unlocked this recipe

**Recipe Unlocking:**
- Recipes start locked (cannot be crafted)
- Unlocked when the player:
  - Obtains the TM from the world (found, given by NPC, etc.)
  - Receives it as a gift/reward
  - Already has the TM in their bag
- Once unlocked, the recipe remains unlocked permanently (saved in save data)

**Example Recipe:**
```
TM01 - Focus Blast
Materials:
  - Machop Muscle x5
  - Meditite Gem x3
Cost: 5000 PokéDollars
Status: Unlocked/Locked
```

### 3. Crafting Process

**Workflow:**
1. Player accesses TM Machine (at Pokémon Centers or via Key Item)
2. Browse available recipes (filter: All, Craftable, Locked)
3. Select a TM to view details:
   - TM name and move
   - Required materials and quantities
   - Currency cost
   - Owned vs. required quantities
   - Unlock status
4. If unlocked and materials available, select "Craft"
5. Confirmation prompt
6. Materials and currency deducted
7. TM added to bag
8. Success message displayed

---

## Technical Architecture

### File Structure

```
New Files:
├── include/
│   ├── tm_crafting.h              # Main crafting system header
│   └── constants/
│       └── tm_materials.h         # Material item constants
├── src/
│   ├── tm_crafting.c              # Core crafting logic
│   ├── tm_crafting_menu.c         # UI and menu system
│   └── data/
│       ├── tm_materials.h         # Material drop data
│       └── tm_recipes.h           # Recipe definitions

Modified Files:
├── include/
│   ├── constants/items.h          # Add material item IDs
│   ├── global.h                   # Extend SaveBlock1
│   ├── item_menu.h                # Add crafting menu callbacks
│   └── field_specials.h           # Add field script functions
├── src/
│   ├── battle_script_commands.c   # Add material drop logic
│   ├── item.c                     # Material item handling
│   ├── pokemon.c                  # Link species to materials
│   ├── data/items.h               # Define material items
│   └── scrcmd.c                   # Add script commands
```

---

## Data Structures

### 1. Material Items (New Item Category)

Materials are regular items stored in the bag (KEY_ITEMS or new MATERIALS pocket).

```c
// In include/constants/items.h
#define ITEM_MATERIAL_START 2000

#define ITEM_RATTATA_FANG       (ITEM_MATERIAL_START + 0)
#define ITEM_PIKACHU_FUR        (ITEM_MATERIAL_START + 1)
#define ITEM_GEODUDE_ROCK       (ITEM_MATERIAL_START + 2)
#define ITEM_MACHOP_MUSCLE      (ITEM_MATERIAL_START + 3)
// ... etc for all material types

#define ITEM_MATERIAL_END       (ITEM_MATERIAL_START + 200)
```

```c
// In src/data/items.h
[ITEM_RATTATA_FANG] = {
    .name = _("Rattata Fang"),
    .price = 0,  // Cannot be sold
    .description = COMPOUND_STRING("A fang from a Rattata.\nUsed for crafting TMs."),
    .pocket = POCKET_KEY_ITEMS,
    .type = ITEM_USE_BAG_MENU,
    .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    .iconPic = gItemIcon_RattataFang,
    .iconPalette = gItemIconPalette_RattataFang,
},
```

### 2. TM Recipe Structure

```c
// In include/tm_crafting.h
struct TMRecipeMaterial {
    u16 itemId;      // Material item ID
    u8 quantity;     // Quantity needed
};

struct TMRecipe {
    u16 tmItemId;                           // Output TM
    u16 cost;                               // Currency cost
    u8 materialCount;                       // Number of materials needed
    struct TMRecipeMaterial materials[4];   // Up to 4 materials
};
```

```c
// In src/data/tm_recipes.h
const struct TMRecipe gTMRecipes[] = {
    [TMHM_INDEX_FOCUS_BLAST] = {
        .tmItemId = ITEM_TM01,
        .cost = 5000,
        .materialCount = 2,
        .materials = {
            {ITEM_MACHOP_MUSCLE, 5},
            {ITEM_MEDITITE_GEM, 3},
        }
    },
    [TMHM_INDEX_DRAGON_CLAW] = {
        .tmItemId = ITEM_TM02,
        .cost = 3000,
        .materialCount = 2,
        .materials = {
            {ITEM_BAGON_SCALE, 3},
            {ITEM_DRATINI_SCALE, 3},
        }
    },
    // ... etc
};
```

### 3. Material Drop Data

```c
// In src/data/tm_materials.h
struct MaterialDrop {
    u16 itemId;      // Material item ID
    u8 minQuantity;  // Minimum drop quantity
    u8 maxQuantity;  // Maximum drop quantity
    u8 dropChance;   // Drop chance (0-100)
};

const struct MaterialDrop gSpeciesMaterialDrops[][2] = {
    [SPECIES_RATTATA] = {
        {ITEM_RATTATA_FANG, 1, 2, 75},
        {ITEM_NONE, 0, 0, 0}
    },
    [SPECIES_RATICATE] = {
        {ITEM_RATTATA_FANG, 1, 3, 75},
        {ITEM_NONE, 0, 0, 0}
    },
    [SPECIES_PIKACHU] = {
        {ITEM_PIKACHU_FUR, 1, 2, 75},
        {ITEM_NONE, 0, 0, 0}
    },
    // ... etc
};
```

### 4. Save Data Extension

```c
// In include/global.h (extend SaveBlock1)
struct TMCraftingData {
    u8 unlockedRecipes[(TM_COUNT + 7) / 8];  // Bitfield for unlocked recipes
    // Each bit represents whether that TM recipe is unlocked
};

struct SaveBlock1 {
    // ... existing fields ...
    struct Bag bag;
    struct TMCraftingData tmCrafting;  // NEW
    // ... other fields ...
};
```

**Helper Functions:**
```c
bool8 IsTMRecipeUnlocked(u8 tmIndex);
void UnlockTMRecipe(u8 tmIndex);
```

---

## Implementation Details

### Phase 1: Material System

**1.1: Define Material Items**
- Add material item constants to `include/constants/items.h`
- Define item data in `src/data/items.h`
- Create material icons (or reuse existing generic icons)

**1.2: Link Materials to Species**
- Create `gSpeciesMaterialDrops` array mapping species to materials
- Define drop rates and quantities

**1.3: Implement Material Drop Logic**
- Hook into wild battle victory/capture
- Add function `TryDropMaterialFromSpecies(u16 species)`
- Add materials to bag using `AddBagItem()`
- Display notification message

```c
// In src/tm_crafting.c
void TryDropMaterialFromWildPokemon(u16 species) {
    const struct MaterialDrop *drops = gSpeciesMaterialDrops[species];

    for (int i = 0; i < 2; i++) {
        if (drops[i].itemId == ITEM_NONE)
            break;

        if (Random() % 100 < drops[i].dropChance) {
            u8 quantity = RandomRange(drops[i].minQuantity, drops[i].maxQuantity);

            if (AddBagItem(drops[i].itemId, quantity)) {
                // Queue notification message
                ShowMaterialDropMessage(drops[i].itemId, quantity);
            }
        }
    }
}
```

**1.4: Integration Point**
- Call material drop function in `src/battle_script_commands.c`
- Add to wild battle victory handling (after catching or defeating)

```c
// In battle_script_commands.c (after wild battle ends)
if (gBattleTypeFlags & BATTLE_TYPE_TRAINER) {
    // Trainer battle - no materials
} else {
    // Wild battle - drop materials
    u16 species = GetMonData(&gEnemyParty[gBattlerPartyIndexes[B_POSITION_OPPONENT_LEFT]], MON_DATA_SPECIES);
    TryDropMaterialFromWildPokemon(species);
}
```

### Phase 2: Recipe System

**2.1: Define TM Recipes**
- Create `gTMRecipes` array in `src/data/tm_recipes.h`
- Map each TM to required materials and cost
- Balance costs and material requirements

**2.2: Implement Recipe Unlocking**
- Add `struct TMCraftingData` to SaveBlock1
- Implement unlock/check functions
- Hook into `AddBagItem()` to auto-unlock when TM obtained

```c
// In src/tm_crafting.c
bool8 IsTMRecipeUnlocked(u8 tmIndex) {
    u8 byte = tmIndex / 8;
    u8 bit = tmIndex % 8;
    return (gSaveBlock1Ptr->tmCrafting.unlockedRecipes[byte] >> bit) & 1;
}

void UnlockTMRecipe(u8 tmIndex) {
    u8 byte = tmIndex / 8;
    u8 bit = tmIndex % 8;
    gSaveBlock1Ptr->tmCrafting.unlockedRecipes[byte] |= (1 << bit);
}

// Hook in AddBagItem (src/item.c)
bool32 AddBagItem(u16 itemId, u16 count) {
    // ... existing logic ...

    // Check if this is a TM and unlock recipe
    if (itemId >= ITEM_TM01 && itemId <= ITEM_TM_LAST) {
        u8 tmIndex = GetItemTMHMIndex(itemId);
        if (tmIndex != TMHM_INDEX_NONE) {
            UnlockTMRecipe(tmIndex);
        }
    }

    // ... rest of function ...
}
```

**2.3: Recipe Query Functions**
```c
// In src/tm_crafting.c
const struct TMRecipe* GetTMRecipe(u8 tmIndex);
bool8 CanCraftTM(u8 tmIndex);  // Check materials + money + unlock status
bool8 HasRequiredMaterials(const struct TMRecipe *recipe);
u16 GetOwnedMaterialCount(u16 materialItemId);
```

### Phase 3: Crafting Logic

**3.1: Core Crafting Function**
```c
// In src/tm_crafting.c
bool8 CraftTM(u8 tmIndex) {
    const struct TMRecipe *recipe = GetTMRecipe(tmIndex);

    if (!recipe)
        return FALSE;

    // Validate can craft
    if (!IsTMRecipeUnlocked(tmIndex))
        return FALSE;

    if (!HasRequiredMaterials(recipe))
        return FALSE;

    if (GetMoney(&gSaveBlock1Ptr->money) < recipe->cost)
        return FALSE;

    // Check bag space for output TM
    if (!CheckBagHasSpace(recipe->tmItemId, 1))
        return FALSE;

    // Deduct materials
    for (int i = 0; i < recipe->materialCount; i++) {
        if (!RemoveBagItem(recipe->materials[i].itemId, recipe->materials[i].quantity))
            return FALSE;  // Shouldn't happen but safety check
    }

    // Deduct money
    RemoveMoney(&gSaveBlock1Ptr->money, recipe->cost);

    // Add TM to bag
    if (!AddBagItem(recipe->tmItemId, 1))
        return FALSE;  // Shouldn't happen but safety check

    return TRUE;
}
```

### Phase 4: UI/Menu System

**4.1: TM Crafting Menu Structure**

Menu hierarchy:
```
Main Menu
├── Browse by Type (Normal, Fire, Water, etc.)
├── Browse All
├── Craftable Only
├── Favorites/Bookmarked
└── Exit
```

**4.2: TM List Display**
- Scrollable list of TMs with status indicators
- Show TM name, move name
- Icons indicating:
  - 🔒 Locked (recipe not unlocked)
  - ✓ Craftable (have all materials + money)
  - ⭐ Bookmarked/Favorite
  - ❌ Cannot craft (missing materials or money)

**4.3: TM Detail View**
When a TM is selected:
```
┌────────────────────────────────┐
│ TM01 - Focus Blast             │
│ Type: Fighting | Power: 120    │
├────────────────────────────────┤
│ Materials Required:             │
│ ⚫ Machop Muscle    5/5  ✓     │
│ ⚫ Meditite Gem     2/3  ✗     │
│                                 │
│ Cost: 5000₽ (Have: 12000₽) ✓  │
├────────────────────────────────┤
│ Status: Cannot Craft           │
│ (Need 1 more Meditite Gem)     │
│                                 │
│ [Craft] [Bookmark] [Back]      │
└────────────────────────────────┘
```

**4.4: Menu Implementation**
```c
// In src/tm_crafting_menu.c
struct TMCraftingMenu {
    struct ListMenu *listMenu;
    u16 cursorPos;
    u16 scrollOffset;
    u8 filterMode;  // ALL, CRAFTABLE, LOCKED, BOOKMARKED
    u8 state;       // LIST, DETAIL, CRAFTING
};

// Main callback functions
void CB2_InitTMCraftingMenu(void);
void Task_TMCraftingMenuMain(u8 taskId);
void DisplayTMList(void);
void DisplayTMDetail(u8 tmIndex);
void HandleTMCraftingInput(void);
```

**4.5: Access Points**
- Add "TM Machine" option to Pokémon Center PC menu
- Add "TM Crafter" Key Item that opens menu from bag
- Add script command for NPCs to open crafting menu

### Phase 5: Integration & Polish

**5.1: Script Commands**
```c
// In src/scrcmd.c
// Open TM crafting menu
bool8 ScrCmd_OpenTMCraftingMenu(struct ScriptContext *ctx) {
    SetMainCallback2(CB2_InitTMCraftingMenu);
    return TRUE;
}

// Check if TM recipe is unlocked
bool8 ScrCmd_IsTMRecipeUnlocked(struct ScriptContext *ctx) {
    u16 tmIndex = ScriptReadHalfword(ctx);
    gSpecialVar_Result = IsTMRecipeUnlocked(tmIndex);
    return FALSE;
}

// Unlock TM recipe manually (for story events)
bool8 ScrCmd_UnlockTMRecipe(struct ScriptContext *ctx) {
    u16 tmIndex = ScriptReadHalfword(ctx);
    UnlockTMRecipe(tmIndex);
    return FALSE;
}
```

**5.2: Configuration Options**
Add config flags to `include/config.h`:
```c
// TM Crafting System
#define TM_CRAFTING_ENABLED TRUE
#define TM_CRAFTING_USES_LEAGUE_POINTS FALSE  // Use money instead
#define TM_MATERIAL_BASE_DROP_RATE 75
#define TM_CRAFTING_AUTO_UNLOCK TRUE  // Auto-unlock when TM obtained
```

**5.3: Balance Considerations**
- Material quantities: Generally 1-5 per material type
- Currency costs: 800-10000 based on TM power/rarity
- Drop rates: 50-100% depending on difficulty
- Drop quantities: 1-3 per encounter, weighted toward lower

---

## UI/UX Design

### Visual Design

**List View:**
```
┌─────────────── TM MACHINE ───────────────┐
│ Filter: [All] Craftable Locked           │
├──────────────────────────────────────────┤
│ ✓ TM01   Focus Blast        Fighting     │
│ ⭐ TM02   Dragon Claw        Dragon       │
│ 🔒 TM03   Water Pulse        Water        │
│ ❌ TM04   Calm Mind          Psychic      │
│   TM05   Roar               Normal        │
│   TM06   Toxic              Poison        │
│ > TM07   Hail               Ice           │
│   TM08   Bulk Up            Fighting      │
│   ...                                      │
├──────────────────────────────────────────┤
│ ↑↓: Select  A: Details  B: Back          │
└──────────────────────────────────────────┘
```

**Detail View:**
```
┌─────────────────────────────────────────┐
│ TM01 - Focus Blast                       │
│ Type: Fighting | BP: 120 | Acc: 70%     │
│                                           │
│ The user heightens its mental focus      │
│ and unleashes its power.                 │
├─────────────────────────────────────────┤
│ MATERIALS REQUIRED:                       │
│                                           │
│ ⚫ Machop Muscle    (5/5)  ✓             │
│ ⚫ Meditite Gem     (3/3)  ✓             │
│                                           │
│ COST: 5000₽ (Current: 12000₽) ✓         │
├─────────────────────────────────────────┤
│ STATUS: Ready to craft!                  │
│                                           │
│ [A: Craft]  [X: Bookmark]  [B: Back]    │
└─────────────────────────────────────────┘
```

**Crafting Animation:**
```
┌─────────────────────────────────────────┐
│                                           │
│          ⚙️ CRAFTING TM01 ⚙️              │
│                                           │
│              [Progress Bar]               │
│                                           │
│        Combining materials...             │
│                                           │
└─────────────────────────────────────────┘

Success screen:
┌─────────────────────────────────────────┐
│                                           │
│              ✨ SUCCESS! ✨               │
│                                           │
│         Crafted TM01 Focus Blast!        │
│                                           │
│         Added to TM/HM pocket.           │
│                                           │
│            [Press A to continue]          │
└─────────────────────────────────────────┘
```

### User Flow

**Opening the Menu:**
1. Player interacts with TM Machine (at Pokémon Center or via Key Item)
2. Menu opens showing TM list
3. Default filter: "All"

**Browsing TMs:**
1. Use D-Pad Up/Down to scroll through TMs
2. L/R buttons to switch filter modes
3. Select button to bookmark/unbookmark
4. A button to view details
5. B button to exit

**Crafting a TM:**
1. Select TM from list (A button)
2. View detail screen with requirements
3. If craftable, press A to confirm
4. Confirmation dialog: "Craft TM01 for 5000₽?"
5. Crafting animation plays
6. Success message displayed
7. Return to TM list (newly crafted TM highlighted)

**Error States:**
- "Recipe not unlocked! Find this TM first."
- "Not enough materials! You need 2 more Machop Muscle."
- "Not enough money! You need 3000₽ more."
- "Not enough bag space! Make room in your TM/HM pocket."

---

## Integration Points

### 1. Battle System
- **File:** `src/battle_script_commands.c`
- **Function:** Add material drop after wild battle ends
- **Hook Point:** After capture or defeat, before returning to overworld

### 2. Bag/Item System
- **File:** `src/item.c`
- **Function:** Auto-unlock recipes when TM obtained
- **Hook Point:** In `AddBagItem()` after successful addition

### 3. Pokémon Center
- **File:** Map scripts for Pokémon Centers
- **Function:** Add TM Machine interaction point
- **Implementation:** Add object event with script trigger

### 4. Save System
- **File:** `src/save.c`
- **Function:** Save/load TM crafting data
- **Hook Point:** Already handled via SaveBlock1 extension

### 5. Menu System
- **File:** `src/item_menu.c` or new file
- **Function:** Implement crafting menu UI
- **Hook Point:** Create new CB2 callback for main menu loop

---

## Testing Strategy

### Unit Tests

**Material Drop Tests:**
- Verify materials drop at correct rate
- Test drop quantity ranges
- Confirm evolutionary families share materials
- Test drop with special conditions (abilities, items)

**Recipe System Tests:**
- Verify recipe data integrity
- Test unlock/lock functionality
- Confirm unlock persistence across save/load
- Test recipe queries (can craft, has materials, etc.)

**Crafting Logic Tests:**
- Test successful crafting flow
- Test insufficient materials error
- Test insufficient money error
- Test locked recipe error
- Test bag full error
- Verify transactional integrity (rollback on failure)

### Integration Tests

**Battle Integration:**
- Defeat wild Pokémon and confirm material drop
- Catch wild Pokémon and confirm material drop
- Test with different species
- Test with evolved forms

**Bag Integration:**
- Obtain TM and verify recipe unlock
- Test material storage in bag
- Test TM storage after crafting
- Verify item limits respected

**UI Tests:**
- Open crafting menu
- Navigate through TM list
- Filter TMs by status
- Select and view TM details
- Craft TM successfully
- Handle error states gracefully
- Bookmark/unbookmark TMs
- Exit menu properly

**Save/Load Tests:**
- Craft TMs and save game
- Load game and verify crafted TMs present
- Verify unlocked recipes persist
- Verify material quantities persist

### Playtesting Checklist

- [ ] Material drops feel rewarding (not too rare/common)
- [ ] Crafting costs are balanced
- [ ] UI is intuitive and easy to navigate
- [ ] Error messages are clear
- [ ] No softlocks or crashes
- [ ] Performance is smooth (no lag)
- [ ] Fits thematically with game world
- [ ] Progression feels satisfying

---

## Configuration & Balancing

### Material Requirements by TM Tier

**Low-Power TMs (30-60 BP):**
- 1-2 material types
- 2-5 of each material
- Cost: 800-2000₽

**Mid-Power TMs (70-90 BP):**
- 2-3 material types
- 3-6 of each material
- Cost: 3000-5000₽

**High-Power TMs (100+ BP):**
- 3-4 material types
- 5-8 of each material
- Cost: 7000-10000₽

### Material Distribution Guidelines

**Common Pokémon → Common Materials:**
- Early-game encounters (Routes 1-3)
- High availability
- Used in many recipes

**Rare Pokémon → Rare Materials:**
- Late-game encounters
- Low availability
- Used in powerful TM recipes

**Type-Specific Materials:**
- Fire types drop "ember", "coal", "flame" materials
- Water types drop "scale", "fin", "shell" materials
- Rock types drop "stone", "pebble", "gem" materials

---

## Future Enhancements

### Phase 2 Features (Post-Launch)

1. **Bulk Crafting**: Craft multiple TMs at once
2. **Material Trading**: Trade materials with NPCs
3. **Material Shops**: Buy materials (expensive)
4. **Crafting Quests**: NPCs request crafted TMs for rewards
5. **Rare Materials**: Very low drop rate materials for special TMs
6. **Crafting Bonuses**: Reduce costs with achievements/badges
7. **Material Storage Expansion**: Increase bag capacity for materials
8. **Recipe Discovery**: Find rare recipes in the world
9. **Multi-Currency Support**: Use Battle Points, Coins, etc.

### Optional Variations

**Difficulty Modes:**
- Easy: Lower material requirements, higher drop rates
- Normal: Balanced (default)
- Hard: Higher material requirements, lower drop rates

**Game Mode Toggles:**
- Classic Mode: Disable crafting, use traditional TM system
- Crafting Mode: Enable full crafting system (default)

---

## Appendix

### Example Material List (Partial)

| Material Item ID | Name | Dropped By |
|-----------------|------|------------|
| 2000 | Rattata Fang | Rattata, Raticate |
| 2001 | Pikachu Fur | Pikachu, Raichu |
| 2002 | Geodude Rock | Geodude, Graveler, Golem |
| 2003 | Machop Muscle | Machop, Machoke, Machamp |
| 2004 | Meditite Gem | Meditite, Medicham |
| 2005 | Abra Spoon | Abra, Kadabra, Alakazam |
| 2006 | Zubat Wing | Zubat, Golbat, Crobat |
| 2007 | Magikarp Scale | Magikarp, Gyarados |
| 2008 | Dratini Scale | Dratini, Dragonair, Dragonite |
| 2009 | Bagon Scale | Bagon, Shelgon, Salamence |

### Example Recipe List (Partial)

| TM | Move | Materials | Cost |
|----|------|-----------|------|
| TM01 | Focus Blast | Machop Muscle x5, Meditite Gem x3 | 5000₽ |
| TM02 | Dragon Claw | Bagon Scale x3, Dratini Scale x3 | 3000₽ |
| TM03 | Water Pulse | Magikarp Scale x4, Horsea Fin x2 | 2000₽ |
| TM04 | Calm Mind | Abra Spoon x5, Ralts Gem x3 | 4000₽ |
| TM05 | Roar | Poochyena Fang x3 | 800₽ |

### Technical Reference

**Key Constants:**
```c
#define TM_MATERIAL_COUNT 200        // Total material types
#define TM_RECIPE_COUNT 77           // Total TM recipes (adjust to TM count)
#define MAX_MATERIALS_PER_RECIPE 4   // Max materials per TM
#define MATERIAL_DROP_BASE_RATE 75   // Base drop chance %
```

**Key Functions:**
```c
// Material system
void TryDropMaterialFromWildPokemon(u16 species);
void ShowMaterialDropMessage(u16 itemId, u8 quantity);

// Recipe system
const struct TMRecipe* GetTMRecipe(u8 tmIndex);
bool8 IsTMRecipeUnlocked(u8 tmIndex);
void UnlockTMRecipe(u8 tmIndex);

// Crafting logic
bool8 CanCraftTM(u8 tmIndex);
bool8 CraftTM(u8 tmIndex);
bool8 HasRequiredMaterials(const struct TMRecipe *recipe);

// UI
void CB2_InitTMCraftingMenu(void);
void Task_TMCraftingMenuMain(u8 taskId);
```

---

## Implementation Timeline

### Week 1: Foundation
- Define material items and constants
- Implement material drop data structures
- Add save data structure for recipe unlocks

### Week 2: Core Systems
- Implement material drop logic in battles
- Create recipe system and data
- Implement unlock/lock functionality

### Week 3: Crafting Logic
- Implement core crafting function
- Add validation and error handling
- Integrate with bag/item system

### Week 4: UI Development
- Design and implement menu system
- Create TM list and detail views
- Add filtering and bookmarking

### Week 5: Integration & Polish
- Add script commands
- Integrate with Pokémon Centers
- Create crafting animations
- Add sound effects

### Week 6: Testing & Balancing
- Unit and integration testing
- Playtest and balance tuning
- Bug fixing
- Documentation

---

## Conclusion

This TM crafting system adds significant replay value and resource management depth to the game. By requiring players to battle specific Pokémon to gather materials, it encourages exploration and engagement with the game's encounters. The unlocking mechanism ensures players must first discover TMs before mass-producing them, maintaining progression pacing.

The system is designed to integrate seamlessly with pokeemerald-expansion's existing architecture, using established patterns for items, menus, and save data. With proper balancing, it will enhance the player experience without disrupting core gameplay.

---

**Document Version:** 1.0
**Created:** 2025-11-12
**Status:** Draft - Ready for Review
