#ifndef GUARD_CONFIG_VARIANT_COLOURS_H
#define GUARD_CONFIG_VARIANT_COLOURS_H

// Variant Colours
#define P_ENABLE_VARIANT_COLOURS TRUE // Enables the variant colours feature, including random variations and custom palettes.

// Feature detection flag - Indicates that the palette modification system is available.
// This allows other features (like Nuzlocke visual death) to conditionally compile
// their palette modification code only when this system is present.
#define PALETTE_SYSTEM_AVAILABLE

#endif // GUARD_CONFIG_VARIANT_COLOURS_H