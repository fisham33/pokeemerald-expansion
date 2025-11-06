#include "global.h"
#include "constants/species.h"

struct PaletteVariant
{
  u8 start : 4;        // Start index of palette customisation range
  u8 length : 4;       // Length of customisation range
  u8 hue_amount : 3;   // Index into hue table [0,10,20,30,45,60,90,180]
  u8 chr_amount : 2;   // Index into chroma table [0,5,10,25]
  u8 lum_amount : 2;   // Index into luma table [0,5,10,25]
  u8 sv_down_only : 1; // If set, switch from +/- to "down only" for both C & L (C: -2*chr, L: -2*lum)
};

struct SpeciesVariant
{
  struct PaletteVariant pv1;
  struct PaletteVariant pv2;
};

// Precomputed hue-amount table
// Code uses hue in [0..255] instead of [0..360]
// {0,10,20,30,45,60,90,180} -> {0,7,14,21,32,43,64,128}
static const u8 sHueTable[8] = {0, 7, 14, 21, 32, 43, 64, 128};
static const u8 sCLTable[4] = {0, 5, 10, 25};

// return variant data or return default if species has no variants.
const struct SpeciesVariant *GetSpeciesVariants(u32 species);

void ApplyPaletteVariantToPaletteBuffer(u16 pal16[16], const struct PaletteVariant *pv, u16 prn16);
void ApplyCustomRestrictionToPaletteBuffer(u8 hMin, u8 hMax, u8 cMin, u8 cMax, u8 lMin, u8 lMax, u16 pal16[16]);
void ApplyMonSpeciesVariantToPaletteBuffer(u32 species, bool8 shiny, u32 PID, u16 pal16[16]);

// Species data helpers

#define HUE_INDEX(h) (            \
    ((h) == 0 ? 0 : (h) <= 10 ? 1 \
                : (h) <= 20   ? 2 \
                : (h) <= 30   ? 3 \
                : (h) <= 45   ? 4 \
                : (h) <= 60   ? 5 \
                : (h) <= 90   ? 6 \
                : /*(h)==180*/ 7))

#define CHR_INDEX(s) (           \
    ((s) == 0 ? 0 : (s) <= 5 ? 1 \
                : (s) <= 10  ? 2 \
                : /*(s)==25*/ 3))

#define LUM_INDEX(v) ( \
    ((v) == 0 ? 0      \
    : (v) <= 5 ? 1     \
    : (v) <= 10  ? 2   \
    : /*(v)==25*/ 3))

#define PAL1(s, l)  \
  .pv1.start = (s), \
  .pv1.length = (l)

#define PAL2(s, l)  \
  .pv2.start = (s), \
  .pv2.length = (l)

#define HCL1(h, s, v, f)          \
  .pv1.hue_amount = HUE_INDEX(h), \
  .pv1.chr_amount = CHR_INDEX(s), \
  .pv1.lum_amount = LUM_INDEX(v), \
  .pv1.sv_down_only = (f)

#define HCL2(h, s, v, f)          \
  .pv2.hue_amount = HUE_INDEX(h), \
  .pv2.chr_amount = CHR_INDEX(s), \
  .pv2.lum_amount = LUM_INDEX(v), \
  .pv2.sv_down_only = (f)

#define DEFAULT_SPECIES_VARIANT \
  {                             \
      PAL1(1, 15),              \
      HCL1(50, 0, 0, FALSE),    \
  }

/*
 * ==============================================
 * SPECIES VARIANTS CONFIGURATION
 * ==============================================
 *
 * This array defines color variations for Pokémon species.
 * Each species can have up to 2 palette regions (PAL1/PAL2) that will be varied.
 *
 * PALETTE FEATURE REFERENCE:
 * For a comprehensive list of palette features (body parts, colors, etc.) for each
 * Pokémon species, see: docs/PALETTE_FEATURES_REFERENCE.md
 *
 * This reference file shows all available palette regions (PALa, PALb, PALc, PALd, PALe)
 * for each species. Choose up to 2 regions to use as PAL1/PAL2 below.
 *
 * CONFIGURATION FORMAT:
 * [SPECIES_NAME] = {
 *     PAL1(start, length),     // First palette region to vary
 *     HCL1(hue, chr, lum, f),  // Variation amounts for PAL1
 *     PAL2(start, length),     // Second palette region to vary (optional)
 *     HCL2(hue, chr, lum, f),  // Variation amounts for PAL2 (optional)
 * },
 *
 * PARAMETERS:
 * - start: Starting palette index (0-15)
 * - length: Number of consecutive palette indices (1-15)
 * - hue: Hue shift in degrees {0, 10, 20, 30, 45, 60, 90, 180}
 * - chr: Chroma (saturation) variation {0, 5, 10, 25}
 * - lum: Luminance (brightness) variation {0, 5, 10, 25}
 * - f: FALSE = ±variation, TRUE = "down only" mode (darker/desaturated)
 *
 * EXAMPLE (from palette reference):
 * Pikachu has these available features:
 *   PALa(1, 5)  - Yellow body
 *   PALb(6, 3)  - Red cheeks
 *   PALc(9, 2)  - Brown stripes
 *   PALd(11, 2) - Black ear tips
 *
 * To vary the body and cheeks:
 * [SPECIES_PIKACHU] = {
 *     PAL1(1, 5),              // Yellow body
 *     HCL1(30, 10, 5, FALSE),  // Hue ±30°, chroma ±10, luminance ±5
 *     PAL2(6, 3),              // Red cheeks
 *     HCL2(20, 15, 0, FALSE),  // Hue ±20°, chroma ±15, no luminance change
 * },
 *
 * TIPS:
 * - Use matching HCL values for evolution chains to preserve colors across evolutions
 * - Start with PAL1 for the most prominent feature (usually body)
 * - Keep at least one defining feature unchanged for recognition
 * - Experiment with "down only" mode (TRUE) for shadow/alternate forms
 */

static const struct SpeciesVariant gSpeciesVariants[NUM_SPECIES] = {
    //[SPECIES_TYRANITAR] = {
    //  PAL1(11, 3),
    //  HCL1(180, 10, 5, TRUE),
    //  PAL2(1, 5),
    //  HCL2(180, 5, 5, FALSE),
    //},

};