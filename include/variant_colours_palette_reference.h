/*
 * Pokémon Palette Features Reference
 *
 * This file provides a comprehensive reference of palette features for Pokémon species
 * to help configure the Colour Variants feature.
 *
 * IMPORTANT: This is a REFERENCE FILE ONLY - do NOT include it in your builds!
 *
 * HOW TO USE:
 * 1. Find your desired species below
 * 2. Review the available palette features (PALa, PALb, PALc, PALd, PALe)
 * 3. Choose up to 2 features to make variable
 * 4. Copy the chosen features as PAL1/PAL2 into variant_colours.h
 * 5. Add HCL1/HCL2 values to define variation amounts
 *
 * EXAMPLE:
 * If you see:
 *     [SPECIES_PIKACHU] = {
 *         PALa(1, 5),    // Yellow body
 *         PALb(6, 3),    // Red cheeks
 *         PALc(9, 2),    // Brown stripes
 *     },
 *
 * And you want to vary body and cheeks, add to variant_colours.h:
 *     [SPECIES_PIKACHU] = {
 *         PAL1(1, 5),              // Yellow body
 *         HCL1(30, 10, 5, FALSE),  // Hue ±30, Chroma ±10, Luminance ±5
 *         PAL2(6, 3),              // Red cheeks
 *         HCL2(20, 15, 0, FALSE),  // Hue ±20, Chroma ±15, no Luminance change
 *     },
 *
 * HCL VALUES:
 * - Hue: {0, 10, 20, 30, 45, 60, 90, 180}      (color shift in degrees)
 * - Chroma: {0, 5, 10, 25}                     (saturation variation)
 * - Luminance: {0, 5, 10, 25}                  (brightness variation)
 * - Final parameter: FALSE = ±variation, TRUE = "down only" mode
 */

#ifndef GUARD_VARIANT_COLOURS_PALETTE_REFERENCE_H
#define GUARD_VARIANT_COLOURS_PALETTE_REFERENCE_H

// This file is for reference only - these macros match the naming in the documentation
#define PALa(start, length)  // Alternative palette region 'a'
#define PALb(start, length)  // Alternative palette region 'b'
#define PALc(start, length)  // Alternative palette region 'c'
#define PALd(start, length)  // Alternative palette region 'd'
#define PALe(start, length)  // Alternative palette region 'e'

/*
 * ===========================
 * GENERATION I - KANTO POKÉMON
 * ===========================
 */

// BULBASAUR LINE
static const char* PALETTE_REFERENCE_BULBASAUR[] = {
    "[SPECIES_BULBASAUR] = {",
    "    PALa(1, 4),    // Teal/cyan body",
    "    PALb(5, 3),    // Green bulb base",
    "    PALc(8, 3),    // Dark green bulb spots",
    "    PALd(11, 3),   // Eyes and mouth",
    "    PALe(14, 1),   // White highlights",
    "},",
};

static const char* PALETTE_REFERENCE_IVYSAUR[] = {
    "[SPECIES_IVYSAUR] = {",
    "    PALa(1, 4),    // Teal/cyan body",
    "    PALb(5, 3),    // Green bulb/flower base",
    "    PALc(8, 3),    // Dark green leaves",
    "    PALd(11, 2),   // Pink flower petals",
    "    PALe(13, 2),   // Eyes and markings",
    "},",
};

static const char* PALETTE_REFERENCE_VENUSAUR[] = {
    "[SPECIES_VENUSAUR] = {",
    "    PALa(1, 4),    // Teal/cyan body",
    "    PALb(5, 3),    // Green stem and leaves",
    "    PALc(8, 3),    // Pink/red flower petals",
    "    PALd(11, 2),   // Yellow flower center",
    "    PALe(13, 2),   // Eyes and markings",
    "},",
};

// CHARMANDER LINE
static const char* PALETTE_REFERENCE_CHARMANDER[] = {
    "[SPECIES_CHARMANDER] = {",
    "    PALa(1, 5),    // Orange body",
    "    PALb(6, 3),    // Cream/yellow belly",
    "    PALc(9, 2),    // Eyes",
    "    PALd(11, 3),   // Tail flame (red-orange-yellow)",
    "    PALe(14, 1),   // White highlights",
    "},",
};

static const char* PALETTE_REFERENCE_CHARMELEON[] = {
    "[SPECIES_CHARMELEON] = {",
    "    PALa(1, 5),    // Red body",
    "    PALb(6, 3),    // Cream/yellow belly",
    "    PALc(9, 2),    // Eyes",
    "    PALd(11, 3),   // Tail flame and horn",
    "    PALe(14, 1),   // White highlights",
    "},",
};

static const char* PALETTE_REFERENCE_CHARIZARD[] = {
    "[SPECIES_CHARIZARD] = {",
    "    PALa(1, 5),    // Orange body",
    "    PALb(6, 3),    // Cream/yellow belly",
    "    PALc(9, 3),    // Teal/blue wings inner",
    "    PALd(12, 2),   // Eyes and claws",
    "    PALe(14, 1),   // Tail flame",
    "},",
};

// SQUIRTLE LINE
static const char* PALETTE_REFERENCE_SQUIRTLE[] = {
    "[SPECIES_SQUIRTLE] = {",
    "    PALa(1, 4),    // Light blue body",
    "    PALb(5, 3),    // Cream/yellow belly and tail",
    "    PALc(8, 3),    // Blue/brown shell",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // White highlights and teeth",
    "},",
};

static const char* PALETTE_REFERENCE_WARTORTLE[] = {
    "[SPECIES_WARTORTLE] = {",
    "    PALa(1, 4),    // Blue body",
    "    PALb(5, 3),    // Cream belly",
    "    PALc(8, 3),    // Purple/brown shell",
    "    PALd(11, 2),   // Ears and tail fur",
    "    PALe(13, 2),   // Eyes and teeth",
    "},",
};

static const char* PALETTE_REFERENCE_BLASTOISE[] = {
    "[SPECIES_BLASTOISE] = {",
    "    PALa(1, 4),    // Blue body",
    "    PALb(5, 3),    // Cream belly",
    "    PALc(8, 3),    // Brown shell",
    "    PALd(11, 2),   // Cannon barrels (metal)",
    "    PALe(13, 2),   // Eyes and details",
    "},",
};

// PIKACHU LINE
static const char* PALETTE_REFERENCE_PICHU[] = {
    "[SPECIES_PICHU] = {",
    "    PALa(1, 5),    // Yellow body",
    "    PALb(6, 2),    // Pink cheeks",
    "    PALc(8, 2),    // Black ear tips",
    "    PALd(10, 2),   // Tail markings",
    "    PALe(12, 3),   // Eyes and details",
    "},",
};

static const char* PALETTE_REFERENCE_PIKACHU[] = {
    "[SPECIES_PIKACHU] = {",
    "    PALa(1, 5),    // Yellow body",
    "    PALb(6, 3),    // Red cheeks",
    "    PALc(9, 2),    // Brown stripes (back/tail base)",
    "    PALd(11, 2),   // Black ear tips",
    "    PALe(13, 2),   // Eyes and mouth",
    "},",
};

static const char* PALETTE_REFERENCE_RAICHU[] = {
    "[SPECIES_RAICHU] = {",
    "    PALa(1, 5),    // Orange/yellow body",
    "    PALb(6, 3),    // White/cream belly",
    "    PALc(9, 2),    // Brown details",
    "    PALd(11, 2),   // Black ears",
    "    PALe(13, 2),   // Eyes and tail",
    "},",
};

// EEVEE LINE
static const char* PALETTE_REFERENCE_EEVEE[] = {
    "[SPECIES_EEVEE] = {",
    "    PALa(1, 4),    // Brown body",
    "    PALb(5, 3),    // Cream neck ruff",
    "    PALc(8, 2),    // Tail tip (cream/brown)",
    "    PALd(10, 3),   // Ear details",
    "    PALe(13, 2),   // Eyes",
    "},",
};

static const char* PALETTE_REFERENCE_VAPOREON[] = {
    "[SPECIES_VAPOREON] = {",
    "    PALa(1, 5),    // Light blue body",
    "    PALb(6, 3),    // Dark blue fins/ruff",
    "    PALc(9, 2),    // Fin membrane details",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // White highlights",
    "},",
};

static const char* PALETTE_REFERENCE_JOLTEON[] = {
    "[SPECIES_JOLTEON] = {",
    "    PALa(1, 5),    // Yellow body",
    "    PALb(6, 3),    // White spikes/ruff",
    "    PALc(9, 2),    // Spike shadows",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // Dark details",
    "},",
};

static const char* PALETTE_REFERENCE_FLAREON[] = {
    "[SPECIES_FLAREON] = {",
    "    PALa(1, 5),    // Orange/red body",
    "    PALb(6, 3),    // Yellow/cream ruff",
    "    PALc(9, 2),    // Flame tail details",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // Dark nose and paws",
    "},",
};

// OTHER GEN I
static const char* PALETTE_REFERENCE_MEOWTH[] = {
    "[SPECIES_MEOWTH] = {",
    "    PALa(1, 4),    // Cream/beige body",
    "    PALb(5, 3),    // Brown stripes",
    "    PALc(8, 2),    // Gold charm",
    "    PALd(10, 2),   // Pink nose and ears",
    "    PALe(12, 3),   // Eyes and whiskers",
    "},",
};

static const char* PALETTE_REFERENCE_PSYDUCK[] = {
    "[SPECIES_PSYDUCK] = {",
    "    PALa(1, 5),    // Yellow body",
    "    PALb(6, 2),    // Cream/beige bill",
    "    PALc(8, 2),    // Black eyes",
    "    PALd(10, 3),   // Limb shading",
    "    PALe(13, 2),   // White highlights",
    "},",
};

/*
 * ===========================
 * GENERATION II - JOHTO POKÉMON
 * ===========================
 */

// JOHTO STARTERS
static const char* PALETTE_REFERENCE_CHIKORITA[] = {
    "[SPECIES_CHIKORITA] = {",
    "    PALa(1, 4),    // Light green body",
    "    PALb(5, 3),    // Dark green leaf",
    "    PALc(8, 2),    // Leaf collar",
    "    PALd(10, 2),   // Eyes",
    "    PALe(12, 3),   // Neck markings",
    "},",
};

static const char* PALETTE_REFERENCE_CYNDAQUIL[] = {
    "[SPECIES_CYNDAQUIL] = {",
    "    PALa(1, 5),    // Teal/blue body",
    "    PALb(6, 3),    // Cream/yellow belly",
    "    PALc(9, 3),    // Back flames (red/orange/yellow)",
    "    PALd(12, 2),   // Eyes",
    "    PALe(14, 1),   // White highlights",
    "},",
};

static const char* PALETTE_REFERENCE_TOTODILE[] = {
    "[SPECIES_TOTODILE] = {",
    "    PALa(1, 4),    // Blue body",
    "    PALb(5, 3),    // Yellow/cream belly",
    "    PALc(8, 2),    // Red spines/back",
    "    PALd(10, 2),   // Eyes",
    "    PALe(12, 3),   // Teeth and claws",
    "},",
};

// OTHER GEN II
static const char* PALETTE_REFERENCE_MAREEP[] = {
    "[SPECIES_MAREEP] = {",
    "    PALa(1, 4),    // White wool",
    "    PALb(5, 3),    // Blue body/face",
    "    PALc(8, 2),    // Yellow/orange tail orb",
    "    PALd(10, 3),   // Black stripes/hooves",
    "    PALe(13, 2),   // Eyes",
    "},",
};

static const char* PALETTE_REFERENCE_TYRANITAR[] = {
    "[SPECIES_TYRANITAR] = {",
    "    PALa(1, 5),    // Green body/scales",
    "    PALb(6, 3),    // Purple/grey belly armor",
    "    PALc(9, 2),    // Shell/armor plates",
    "    PALd(11, 3),   // Blue chest diamonds",
    "    PALe(14, 1),   // Eyes and details",
    "},",
};

/*
 * ===========================
 * GENERATION III - HOENN POKÉMON
 * ===========================
 */

// HOENN STARTERS
static const char* PALETTE_REFERENCE_TREECKO[] = {
    "[SPECIES_TREECKO] = {",
    "    PALa(1, 5),    // Green body",
    "    PALb(6, 3),    // Yellow/cream belly",
    "    PALc(9, 2),    // Red tail",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // Dark green accents",
    "},",
};

static const char* PALETTE_REFERENCE_TORCHIC[] = {
    "[SPECIES_TORCHIC] = {",
    "    PALa(1, 5),    // Orange/yellow body",
    "    PALb(6, 2),    // Yellow accents",
    "    PALc(8, 2),    // Orange beak/feet",
    "    PALd(10, 2),   // Eyes",
    "    PALe(12, 3),   // Feather details",
    "},",
};

static const char* PALETTE_REFERENCE_MUDKIP[] = {
    "[SPECIES_MUDKIP] = {",
    "    PALa(1, 4),    // Light blue body",
    "    PALb(5, 3),    // Orange/coral cheeks and tail fin",
    "    PALc(8, 2),    // Dark blue back fin",
    "    PALd(10, 2),   // Eyes",
    "    PALe(12, 3),   // White belly",
    "},",
};

// HOENN EARLY ROUTE
static const char* PALETTE_REFERENCE_POOCHYENA[] = {
    "[SPECIES_POOCHYENA] = {",
    "    PALa(1, 4),    // Grey body",
    "    PALb(5, 3),    // Black fur patches",
    "    PALc(8, 2),    // Red eyes",
    "    PALd(10, 2),   // Yellow sclera",
    "    PALe(12, 3),   // Teeth and claws",
    "},",
};

static const char* PALETTE_REFERENCE_ZIGZAGOON[] = {
    "[SPECIES_ZIGZAGOON] = {",
    "    PALa(1, 4),    // Brown body",
    "    PALb(5, 3),    // Cream/white zigzag stripes",
    "    PALc(8, 2),    // Black nose",
    "    PALd(10, 3),   // Eyes",
    "    PALe(13, 2),   // Ear details",
    "},",
};

static const char* PALETTE_REFERENCE_WURMPLE[] = {
    "[SPECIES_WURMPLE] = {",
    "    PALa(1, 4),    // Pink/magenta body",
    "    PALb(5, 3),    // White segments",
    "    PALc(8, 2),    // Yellow spike base",
    "    PALd(10, 2),   // Black spike tips",
    "    PALe(12, 3),   // Eyes and feet",
    "},",
};

// RALTS LINE
static const char* PALETTE_REFERENCE_RALTS[] = {
    "[SPECIES_RALTS] = {",
    "    PALa(1, 4),    // White body",
    "    PALb(5, 3),    // Green hair",
    "    PALc(8, 2),    // Red horn",
    "    PALd(10, 2),   // Eyes",
    "    PALe(12, 3),   // Pink cheeks",
    "},",
};

static const char* PALETTE_REFERENCE_GARDEVOIR[] = {
    "[SPECIES_GARDEVOIR] = {",
    "    PALa(1, 4),    // White body/gown",
    "    PALb(5, 3),    // Green hair",
    "    PALc(8, 3),    // Red chest horn",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // Pink accents",
    "},",
};

// ARON LINE
static const char* PALETTE_REFERENCE_ARON[] = {
    "[SPECIES_ARON] = {",
    "    PALa(1, 5),    // Grey/silver body armor",
    "    PALb(6, 3),    // Dark grey/black armor plates",
    "    PALc(9, 2),    // Blue/teal face",
    "    PALd(11, 2),   // Eyes",
    "    PALe(13, 2),   // Metal highlights",
    "},",
};

static const char* PALETTE_REFERENCE_AGGRON[] = {
    "[SPECIES_AGGRON] = {",
    "    PALa(1, 5),    // Grey steel body",
    "    PALb(6, 3),    // Black armor accents",
    "    PALc(9, 3),    // Silver/white horns and plates",
    "    PALd(12, 2),   // Eyes",
    "    PALe(14, 1),   // Metal shine highlights",
    "},",
};

/*
 * ===========================
 * USAGE EXAMPLES
 * ===========================
 */

/*
 * EXAMPLE 1: Simple body and accent variation
 *
 * [SPECIES_PIKACHU] = {
 *     PAL1(1, 5),              // Yellow body - choose PALa from reference
 *     HCL1(30, 10, 5, FALSE),  // Vary hue ±30°, chroma ±10, luminance ±5
 *     PAL2(6, 3),              // Red cheeks - choose PALb from reference
 *     HCL2(20, 15, 0, FALSE),  // Vary hue ±20°, chroma ±15, keep luminance
 * },
 */

/*
 * EXAMPLE 2: Body variation with color preservation
 *
 * [SPECIES_BULBASAUR] = {
 *     PAL1(1, 4),              // Teal body - choose PALa from reference
 *     HCL1(45, 10, 10, FALSE), // Wide hue shift for different body colors
 *     PAL2(5, 3),              // Green bulb - choose PALb from reference
 *     HCL2(20, 5, 5, FALSE),   // Subtle bulb color variation
 * },
 */

/*
 * EXAMPLE 3: Desaturation effect using "down only" mode
 *
 * [SPECIES_CHARMANDER] = {
 *     PAL1(1, 5),              // Orange body
 *     HCL1(10, 25, 0, TRUE),   // TRUE = "down only": body gets darker/desaturated
 *     PAL2(11, 3),             // Tail flame
 *     HCL2(30, 10, 10, FALSE), // Flame varies normally
 * },
 */

/*
 * EXAMPLE 4: Preserve color, vary brightness
 *
 * [SPECIES_EEVEE] = {
 *     PAL1(1, 4),             // Brown body
 *     HCL1(0, 0, 25, FALSE),  // No hue/chroma change, luminance ±25
 *     PAL2(5, 3),             // Cream ruff
 *     HCL2(10, 5, 10, FALSE), // Slight variation on ruff
 * },
 */

#endif // GUARD_VARIANT_COLOURS_PALETTE_REFERENCE_H
