# Pokémon Palette Features Reference

This document provides a comprehensive reference of palette features (body parts, colors, etc.) for each Pokémon species, to help developers easily configure the Colour Variants feature.

## How to Use This Reference

1. Find your desired Pokémon species in this document
2. Review the available palette features (PALa, PALb, PALc, etc.) with their descriptions
3. Choose up to 2 features you want to make variable in your game
4. Copy the chosen features as PAL1/PAL2 into `include/variant_colours.h` in the `gSpeciesVariants` array
5. Add corresponding HCL1/HCL2 values to define the variation amounts

## Example Usage

If you see this reference entry:
```c
[SPECIES_PIKACHU] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 3),    // Red cheeks
    PALc(9, 2),    // Brown stripes
    PALd(13, 2),   // Black ear tips
},
```

And you want to vary the body color and cheeks, you would add to `variant_colours.h`:
```c
[SPECIES_PIKACHU] = {
    PAL1(1, 5),              // Yellow body
    HCL1(30, 10, 5, FALSE),  // Vary hue slightly, chroma and luminance
    PAL2(6, 3),              // Red cheeks
    HCL2(20, 15, 0, FALSE),  // Vary hue and chroma, keep luminance
},
```

---

## Generation I

### SPECIES_BULBASAUR
```c
[SPECIES_BULBASAUR] = {
    PALa(1, 4),    // Teal/cyan body
    PALb(5, 3),    // Green bulb base
    PALc(8, 3),    // Dark green bulb spots
    PALd(11, 3),   // Eyes and mouth
    PALe(14, 1),   // White highlights
},
```

### SPECIES_IVYSAUR
```c
[SPECIES_IVYSAUR] = {
    PALa(1, 4),    // Teal/cyan body
    PALb(5, 3),    // Green bulb/flower base
    PALc(8, 3),    // Dark green leaves
    PALd(11, 2),   // Pink flower petals
    PALe(13, 2),   // Eyes and markings
},
```

### SPECIES_VENUSAUR
```c
[SPECIES_VENUSAUR] = {
    PALa(1, 4),    // Teal/cyan body
    PALb(5, 3),    // Green stem and leaves
    PALc(8, 3),    // Pink/red flower petals
    PALd(11, 2),   // Yellow flower center
    PALe(13, 2),   // Eyes and markings
},
```

### SPECIES_CHARMANDER
```c
[SPECIES_CHARMANDER] = {
    PALa(1, 5),    // Orange body
    PALb(6, 3),    // Cream/yellow belly
    PALc(9, 2),    // Eyes
    PALd(11, 3),   // Tail flame (red-orange-yellow)
    PALe(14, 1),   // White highlights
},
```

### SPECIES_CHARMELEON
```c
[SPECIES_CHARMELEON] = {
    PALa(1, 5),    // Red body
    PALb(6, 3),    // Cream/yellow belly
    PALc(9, 2),    // Eyes
    PALd(11, 3),   // Tail flame and horn
    PALe(14, 1),   // White highlights
},
```

### SPECIES_CHARIZARD
```c
[SPECIES_CHARIZARD] = {
    PALa(1, 5),    // Orange body
    PALb(6, 3),    // Cream/yellow belly
    PALc(9, 3),    // Teal/blue wings inner
    PALd(12, 2),   // Eyes and claws
    PALe(14, 1),   // Tail flame
},
```

### SPECIES_SQUIRTLE
```c
[SPECIES_SQUIRTLE] = {
    PALa(1, 4),    // Light blue body
    PALb(5, 3),    // Cream/yellow belly and tail
    PALc(8, 3),    // Blue/brown shell
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // White highlights and teeth
},
```

### SPECIES_WARTORTLE
```c
[SPECIES_WARTORTLE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Cream belly
    PALc(8, 3),    // Purple/brown shell
    PALd(11, 2),   // Ears and tail fur
    PALe(13, 2),   // Eyes and teeth
},
```

### SPECIES_BLASTOISE
```c
[SPECIES_BLASTOISE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Cream belly
    PALc(8, 3),    // Brown shell
    PALd(11, 2),   // Cannon barrels (metal)
    PALe(13, 2),   // Eyes and details
},
```

### SPECIES_PIKACHU
```c
[SPECIES_PIKACHU] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 3),    // Red cheeks
    PALc(9, 2),    // Brown stripes (back/tail)
    PALd(11, 2),   // Black ear tips
    PALe(13, 2),   // Eyes and mouth
},
```

### SPECIES_RAICHU
```c
[SPECIES_RAICHU] = {
    PALa(1, 5),    // Orange/yellow body
    PALb(6, 3),    // White/cream belly
    PALc(9, 2),    // Brown details
    PALd(11, 2),   // Black ears
    PALe(13, 2),   // Eyes and tail
},
```

### SPECIES_MEOWTH
```c
[SPECIES_MEOWTH] = {
    PALa(1, 4),    // Cream/beige body
    PALb(5, 3),    // Brown stripes
    PALc(8, 2),    // Gold charm
    PALd(10, 2),   // Pink nose and ears
    PALe(12, 3),   // Eyes and whiskers
},
```

### SPECIES_PSYDUCK
```c
[SPECIES_PSYDUCK] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 2),    // Cream/beige bill
    PALc(8, 2),    // Black eyes
    PALd(10, 3),   // Limb shading
    PALe(13, 2),   // White highlights
},
```

### SPECIES_EEVEE
```c
[SPECIES_EEVEE] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream neck ruff
    PALc(8, 2),    // Tail tip (cream/brown)
    PALd(10, 3),   // Ear details
    PALe(13, 2),   // Eyes
},
```

### SPECIES_VAPOREON
```c
[SPECIES_VAPOREON] = {
    PALa(1, 5),    // Light blue body
    PALb(6, 3),    // Dark blue fins/ruff
    PALc(9, 2),    // Fin membrane details
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // White highlights
},
```

### SPECIES_JOLTEON
```c
[SPECIES_JOLTEON] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 3),    // White spikes/ruff
    PALc(9, 2),    // Spike shadows
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Dark details
},
```

### SPECIES_FLAREON
```c
[SPECIES_FLAREON] = {
    PALa(1, 5),    // Orange/red body
    PALb(6, 3),    // Yellow/cream ruff
    PALc(9, 2),    // Flame tail details
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Dark nose and paws
},
```

---

## Generation II

### SPECIES_CHIKORITA
```c
[SPECIES_CHIKORITA] = {
    PALa(1, 4),    // Light green body
    PALb(5, 3),    // Dark green leaf
    PALc(8, 2),    // Leaf collar
    PALd(10, 2),   // Eyes
    PALe(12, 3),   // Neck markings
},
```

### SPECIES_CYNDAQUIL
```c
[SPECIES_CYNDAQUIL] = {
    PALa(1, 5),    // Teal/blue body
    PALb(6, 3),    // Cream/yellow belly
    PALc(9, 3),    // Back flames (red/orange/yellow)
    PALd(12, 2),   // Eyes
    PALe(14, 1),   // White highlights
},
```

### SPECIES_TOTODILE
```c
[SPECIES_TOTODILE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Yellow/cream belly
    PALc(8, 2),    // Red spines/back
    PALd(10, 2),   // Eyes
    PALe(12, 3),   // Teeth and claws
},
```

### SPECIES_PICHU
```c
[SPECIES_PICHU] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 2),    // Pink cheeks
    PALc(8, 2),    // Black ear tips
    PALd(10, 2),   // Tail markings
    PALe(12, 3),   // Eyes and details
},
```

### SPECIES_MAREEP
```c
[SPECIES_MAREEP] = {
    PALa(1, 4),    // White wool
    PALb(5, 3),    // Blue body/face
    PALc(8, 2),    // Yellow/orange tail orb
    PALd(10, 3),   // Black stripes/hooves
    PALe(13, 2),   // Eyes
},
```

### SPECIES_TYRANITAR
```c
[SPECIES_TYRANITAR] = {
    PALa(1, 5),    // Green body/scales
    PALb(6, 3),    // Purple/grey belly
    PALc(9, 2),    // Shell/armor plates
    PALd(11, 3),   // Blue chest diamonds
    PALe(14, 1),   // Eyes and details
},
```

---

## Generation III

### SPECIES_TREECKO
```c
[SPECIES_TREECKO] = {
    PALa(1, 5),    // Green body
    PALb(6, 3),    // Yellow/cream belly
    PALc(9, 2),    // Red tail
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Dark green accents
},
```

### SPECIES_TORCHIC
```c
[SPECIES_TORCHIC] = {
    PALa(1, 5),    // Orange/yellow body
    PALb(6, 2),    // Yellow accents
    PALc(8, 2),    // Orange beak/feet
    PALd(10, 2),   // Eyes
    PALe(12, 3),   // Feather details
},
```

### SPECIES_MUDKIP
```c
[SPECIES_MUDKIP] = {
    PALa(1, 4),    // Light blue body
    PALb(5, 3),    // Orange/coral cheeks and tail fin
    PALc(8, 2),    // Dark blue back fin
    PALd(10, 2),   // Eyes
    PALe(12, 3),   // White belly
},
```

### SPECIES_POOCHYENA
```c
[SPECIES_POOCHYENA] = {
    PALa(1, 4),    // Grey body
    PALb(5, 3),    // Black fur patches
    PALc(8, 2),    // Red eyes
    PALd(10, 2),   // Yellow sclera
    PALe(12, 3),   // Teeth and claws
},
```

### SPECIES_ZIGZAGOON
```c
[SPECIES_ZIGZAGOON] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream/white zigzag stripes
    PALc(8, 2),    // Black nose
    PALd(10, 3),   // Eyes
    PALe(13, 2),   // Ear details
},
```

### SPECIES_WURMPLE
```c
[SPECIES_WURMPLE] = {
    PALa(1, 4),    // Pink/magenta body
    PALb(5, 3),    // White segments
    PALc(8, 2),    // Yellow spike base
    PALd(10, 2),   // Black spike tips
    PALe(12, 3),   // Eyes and feet
},
```

### SPECIES_RALTS
```c
[SPECIES_RALTS] = {
    PALa(1, 4),    // White body
    PALb(5, 3),    // Green hair
    PALc(8, 2),    // Red horn
    PALd(10, 2),   // Eyes
    PALe(12, 3),   // Pink cheeks
},
```

### SPECIES_GARDEVOIR
```c
[SPECIES_GARDEVOIR] = {
    PALa(1, 4),    // White body/gown
    PALb(5, 3),    // Green hair
    PALc(8, 3),    // Red chest horn
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Pink accents
},
```

### SPECIES_ARON
```c
[SPECIES_ARON] = {
    PALa(1, 5),    // Grey/silver body armor
    PALb(6, 3),    // Dark grey/black armor plates
    PALc(9, 2),    // Blue/teal face
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Metal highlights
},
```

### SPECIES_AGGRON
```c
[SPECIES_AGGRON] = {
    PALa(1, 5),    // Grey steel body
    PALb(6, 3),    // Black armor accents
    PALc(9, 3),    // Silver/white horns and plates
    PALd(12, 2),   // Eyes
    PALe(14, 1),   // Metal shine highlights
},
```

---

## Notes for Developers

### Tips for Choosing Palette Features

1. **Most Recognizable Features First**: Choose features that are most iconic to the Pokémon (e.g., Pikachu's yellow body, Charmander's tail flame)
2. **Complementary Variations**: Select features that will create interesting combinations when varied together
3. **Preserve Recognition**: Avoid varying ALL defining features - keep some consistent so the Pokémon remains recognizable
4. **Evolution Chains**: Use the same HCL values for evolution chains to preserve color shifts across evolutions

### Palette Index Determination

To find palette indices for unlisted Pokémon:

1. Open `graphics/pokemon/[species]/anim_front.png` in an image editor that supports indexed color (e.g., GIMP)
2. View the color palette (Windows → Dockable Dialogs → Colormap in GIMP)
3. Identify which palette indices (0-15) correspond to which features
4. Group adjacent indices that belong to the same feature (e.g., light/dark shades of the same body part)

### Color Groups Best Practices

- **Start**: First palette index of the feature (0-15)
- **Length**: Number of consecutive palette indices for that feature (1-15)
- Features should use **adjacent palette indices** for best results
- Index 0 is typically reserved for transparency/background

---

## Contributing

To add more Pokémon to this reference:

1. Analyze the Pokémon's sprite palette using GIMP or similar tool
2. Identify distinct features (body parts, markings, etc.)
3. Add an entry following the format above
4. Use clear, descriptive comments for each palette feature
5. List features in order of visual importance/size

This reference is maintained as part of the Colour Variants feature documentation.
