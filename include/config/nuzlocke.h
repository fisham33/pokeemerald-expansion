#ifndef GUARD_CONFIG_NUZLOCKE_H
#define GUARD_CONFIG_NUZLOCKE_H

// Nuzlocke config

// Activation flag - Nuzlocke rules (encounter tracking, catch restrictions, permadeath)
// will only apply after this flag is set. This prevents encounters from being "wasted"
// before the player can actually catch Pokémon.
//
// To use this feature, replace the 0 with the flag ID you're assigning it to.
// Common options:
//   - FLAG_SYS_POKEDEX_GET: Activate when player receives Pokédex (recommended default)
//   - FLAG_BADGE01_GET: Activate after first gym badge
//   - 0: Disable requirement (activate immediately with Nuzlocke mode)
//
#define I_NUZLOCKE_ACTIVATION_FLAG    FLAG_SYS_POKEDEX_GET

// Shiny Clause - If TRUE, shiny Pokémon can always be caught regardless of other rules
// (doesn't consume the location's encounter slot)
#define I_NUZLOCKE_SHINY_CLAUSE       TRUE

// Duplicate Clause - If TRUE, encountering a species you already own doesn't consume
// the location's encounter slot, allowing you to keep searching for new species
#define I_NUZLOCKE_DUPLICATE_CLAUSE   TRUE

// Permadeath - If TRUE, fainted Pokémon are marked as dead and become unusable
// If FALSE, Nuzlocke only enforces catch restrictions without permadeath
#define I_NUZLOCKE_PERMADEATH         TRUE

// If TRUE, prevent double wild battles on first encounters per location
#define I_NUZLOCKE_PREVENT_DOUBLES    TRUE

// Whiteout recovery option - If TRUE, player can choose to disable Nuzlocke mode
// after whiting out. If FALSE, whiteout in Nuzlocke = traditional game over
#define I_NUZLOCKE_WHITEOUT_OPTION    TRUE

// Visual indicators - If TRUE, dead Pokémon display with a grey palette everywhere
// (party menu, PC, summary screen, battle).
// Note: Requires the palette modification system (PALETTE_SYSTEM_AVAILABLE) from the
// variant_colours branch. If that system is not present, this feature will be disabled
// at compile-time regardless of this setting.
#define I_NUZLOCKE_VISUAL_DEATH       FALSE

// Location merging - If TRUE, related locations share encounter slots
// Example: Underwater Route 124 = Route 124 surface
// If FALSE, they're treated as separate locations with separate encounters
#define I_NUZLOCKE_LOCATION_MERGE     FALSE

// Trainer Card cosmetic - If TRUE, show "NUZLOCKE POKÉDEX" on Trainer Card
// If FALSE, show normal "POKÉDEX" text
#define I_NUZLOCKE_TRAINER_CARD       TRUE

#endif // GUARD_CONFIG_NUZLOCKE_H
