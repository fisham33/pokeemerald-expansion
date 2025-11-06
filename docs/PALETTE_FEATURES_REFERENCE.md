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

## Pokémon #1-30

### #001 SPECIES_BULBASAUR
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

### #009 SPECIES_BLASTOISE
```c
[SPECIES_BLASTOISE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Cream belly
    PALc(8, 3),    // Brown shell
    PALd(11, 2),   // Cannon barrels (metal)
    PALe(13, 2),   // Eyes and details
},
```

### #010 SPECIES_CATERPIE
```c
[SPECIES_CATERPIE] = {
    PALa(1, 4),    // Green body
    PALb(5, 3),    // Yellow belly segments
    PALc(8, 2),    // Pink/red antenna
    PALd(10, 3),   // Eyes (white and black)
    PALe(13, 2),   // Feet
},
```

### #011 SPECIES_METAPOD
```c
[SPECIES_METAPOD] = {
    PALa(1, 5),    // Green shell/body
    PALb(6, 3),    // Dark green shell shading
    PALc(9, 2),    // Eyes
    PALd(11, 3),   // Shell highlights
    PALe(14, 1),   // White shine
},
```

### #012 SPECIES_BUTTERFREE
```c
[SPECIES_BUTTERFREE] = {
    PALa(1, 3),    // Purple/blue body
    PALb(4, 4),    // White wings
    PALc(8, 3),    // Black wing markings
    PALd(11, 2),   // Red/pink eyes
    PALe(13, 2),   // Antennae and feet
},
```

### #013 SPECIES_WEEDLE
```c
[SPECIES_WEEDLE] = {
    PALa(1, 4),    // Brown/tan body
    PALb(5, 3),    // Yellow/cream segments
    PALc(8, 2),    // Pink nose
    PALd(10, 3),   // Red stinger/horn
    PALe(13, 2),   // Eyes and feet
},
```

### #014 SPECIES_KAKUNA
```c
[SPECIES_KAKUNA] = {
    PALa(1, 5),    // Yellow shell/body
    PALb(6, 3),    // Dark yellow/gold shading
    PALc(9, 2),    // Eyes
    PALd(11, 3),   // Shell details
    PALe(14, 1),   // Highlights
},
```

### #015 SPECIES_BEEDRILL
```c
[SPECIES_BEEDRILL] = {
    PALa(1, 4),    // Yellow body segments
    PALb(5, 3),    // Black stripes
    PALc(8, 3),    // White/grey wings
    PALd(11, 2),   // Red eyes
    PALe(13, 2),   // Stingers
},
```

### #016 SPECIES_PIDGEY
```c
[SPECIES_PIDGEY] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream/tan belly and face
    PALc(8, 2),    // Pink/red crest
    PALd(10, 3),   // Wing feathers (dark brown)
    PALe(13, 2),   // Eyes and beak
},
```

### #017 SPECIES_PIDGEOTTO
```c
[SPECIES_PIDGEOTTO] = {
    PALa(1, 4),    // Brown body and wings
    PALb(5, 3),    // Cream/pink belly
    PALc(8, 2),    // Red/pink crest
    PALd(10, 3),   // Dark wing tips
    PALe(13, 2),   // Eyes and talons
},
```

### #018 SPECIES_PIDGEOT
```c
[SPECIES_PIDGEOT] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream belly and neck
    PALc(8, 3),    // Red/yellow head crest
    PALd(11, 2),   // Wing patterns
    PALe(13, 2),   // Eyes and talons
},
```

### #019 SPECIES_RATTATA
```c
[SPECIES_RATTATA] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Cream/white belly and face
    PALc(8, 2),    // Red eyes
    PALd(10, 3),   // Whiskers and teeth
    PALe(13, 2),   // Feet and tail
},
```

### #020 SPECIES_RATICATE
```c
[SPECIES_RATICATE] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream/tan belly
    PALc(8, 3),    // Yellow whiskers and teeth
    PALd(11, 2),   // Red eyes
    PALe(13, 2),   // Feet and ears
},
```

### #021 SPECIES_SPEAROW
```c
[SPECIES_SPEAROW] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream/beige belly and face
    PALc(8, 2),    // Pink/red crest
    PALd(10, 3),   // Wings and tail
    PALe(13, 2),   // Eyes and beak
},
```

### #022 SPECIES_FEAROW
```c
[SPECIES_FEAROW] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Cream neck and underside
    PALc(8, 3),    // Red crest and beak
    PALd(11, 2),   // Wing feathers
    PALe(13, 2),   // Eyes and talons
},
```

### #023 SPECIES_EKANS
```c
[SPECIES_EKANS] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Yellow belly bands
    PALc(8, 2),    // Dark purple patterns
    PALd(10, 3),   // Eyes and tongue
    PALe(13, 2),   // Rattle tail
},
```

### #024 SPECIES_ARBOK
```c
[SPECIES_ARBOK] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Yellow belly and bands
    PALc(8, 3),    // Black hood pattern
    PALd(11, 2),   // Red/pink pattern accents
    PALe(13, 2),   // Eyes and tongue
},
```

### #025 SPECIES_PIKACHU
```c
[SPECIES_PIKACHU] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 3),    // Red cheeks
    PALc(9, 2),    // Brown stripes (back/tail)
    PALd(11, 2),   // Black ear tips
    PALe(13, 2),   // Eyes and mouth
},
```

### #026 SPECIES_RAICHU
```c
[SPECIES_RAICHU] = {
    PALa(1, 5),    // Orange/yellow body
    PALb(6, 3),    // White/cream belly
    PALc(9, 2),    // Brown details
    PALd(11, 2),   // Black ears and tail
    PALe(13, 2),   // Eyes
},
```

### #027 SPECIES_SANDSHREW
```c
[SPECIES_SANDSHREW] = {
    PALa(1, 4),    // Yellow/tan body
    PALb(5, 3),    // Brown back scales
    PALc(8, 3),    // Cream/white belly
    PALd(11, 2),   // Claws
    PALe(13, 2),   // Eyes
},
```

### #028 SPECIES_SANDSLASH
```c
[SPECIES_SANDSLASH] = {
    PALa(1, 4),    // Yellow/tan body
    PALb(5, 3),    // Brown back spikes
    PALc(8, 3),    // Cream belly
    PALd(11, 2),   // Dark spike tips
    PALe(13, 2),   // Eyes and claws
},
```

### #029 SPECIES_NIDORAN_F
```c
[SPECIES_NIDORAN_F] = {
    PALa(1, 4),    // Blue/cyan body
    PALb(5, 3),    // Lighter blue spots
    PALc(8, 2),    // Pink ears
    PALd(10, 3),   // Spikes/horn
    PALe(13, 2),   // Eyes and whiskers
},
```

### #030 SPECIES_NIDORINA
```c
[SPECIES_NIDORINA] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Lighter blue/white belly
    PALc(8, 3),    // Dark blue back spikes
    PALd(11, 2),   // Ears and horn
    PALe(13, 2),   // Eyes and details
},
```

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
