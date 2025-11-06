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

### #031 SPECIES_NIDOQUEEN
```c
[SPECIES_NIDOQUEEN] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Light blue/cream belly
    PALc(8, 3),    // Dark blue back plates
    PALd(11, 2),   // Ears and spikes
    PALe(13, 2),   // Eyes and claws
},
```

### #032 SPECIES_NIDORAN_M
```c
[SPECIES_NIDORAN_M] = {
    PALa(1, 4),    // Purple/magenta body
    PALb(5, 3),    // Lighter purple spots
    PALc(8, 2),    // Pink/red ears
    PALd(10, 3),   // Horn and spikes
    PALe(13, 2),   // Eyes and whiskers
},
```

### #033 SPECIES_NIDORINO
```c
[SPECIES_NIDORINO] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Lighter purple/white belly
    PALc(8, 3),    // Dark purple back spikes
    PALd(11, 2),   // Ears and horn
    PALe(13, 2),   // Eyes and details
},
```

### #034 SPECIES_NIDOKING
```c
[SPECIES_NIDOKING] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Light purple/cream belly
    PALc(8, 3),    // Dark purple back plates
    PALd(11, 2),   // Ears and horn
    PALe(13, 2),   // Eyes and claws
},
```

### #035 SPECIES_CLEFAIRY
```c
[SPECIES_CLEFAIRY] = {
    PALa(1, 4),    // Pink body
    PALb(5, 3),    // Lighter pink/cream details
    PALc(8, 2),    // Brown/tan feet
    PALd(10, 3),   // Ears and tail
    PALe(13, 2),   // Eyes and markings
},
```

### #036 SPECIES_CLEFABLE
```c
[SPECIES_CLEFABLE] = {
    PALa(1, 4),    // Pink body
    PALb(5, 3),    // Lighter pink wings/details
    PALc(8, 2),    // Brown feet
    PALd(10, 3),   // Ears and features
    PALe(13, 2),   // Eyes
},
```

### #037 SPECIES_VULPIX
```c
[SPECIES_VULPIX] = {
    PALa(1, 4),    // Orange/red-brown body
    PALb(5, 3),    // Cream/tan muzzle and tail tips
    PALc(8, 3),    // Red-orange fur highlights
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Darker fur accents
},
```

### #038 SPECIES_NINETALES
```c
[SPECIES_NINETALES] = {
    PALa(1, 4),    // Cream/tan body
    PALb(5, 3),    // Yellow/gold mane and tails
    PALc(8, 3),    // Orange tail tips
    PALd(11, 2),   // Red eyes
    PALe(13, 2),   // Highlights and details
},
```

### #039 SPECIES_JIGGLYPUFF
```c
[SPECIES_JIGGLYPUFF] = {
    PALa(1, 4),    // Pink body
    PALb(5, 3),    // Lighter pink/white features
    PALc(8, 2),    // Blue/teal eyes
    PALd(10, 3),   // Ears and tuft
    PALe(13, 2),   // Face details
},
```

### #040 SPECIES_WIGGLYTUFF
```c
[SPECIES_WIGGLYTUFF] = {
    PALa(1, 4),    // Pink body
    PALb(5, 3),    // White/cream fur
    PALc(8, 2),    // Blue eyes
    PALd(10, 3),   // Ears
    PALe(13, 2),   // Face markings
},
```

### #041 SPECIES_ZUBAT
```c
[SPECIES_ZUBAT] = {
    PALa(1, 4),    // Blue/purple body
    PALb(5, 3),    // Purple wing membrane
    PALc(8, 2),    // Dark blue/black wing edges
    PALd(10, 3),   // Mouth/fangs
    PALe(13, 2),   // Body highlights
},
```

### #042 SPECIES_GOLBAT
```c
[SPECIES_GOLBAT] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Blue wing membrane
    PALc(8, 3),    // Dark purple wing edges
    PALd(11, 2),   // Mouth/tongue
    PALe(13, 2),   // Eyes and fangs
},
```

### #043 SPECIES_ODDISH
```c
[SPECIES_ODDISH] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Green/dark green leaves
    PALc(8, 2),    // Leaf highlights
    PALd(10, 3),   // Eyes and feet
    PALe(13, 2),   // Details
},
```

### #044 SPECIES_GLOOM
```c
[SPECIES_GLOOM] = {
    PALa(1, 4),    // Blue/dark blue body
    PALb(5, 3),    // Red/brown flower petals
    PALc(8, 3),    // Dark red petal spots
    PALd(11, 2),   // Yellow stigma/drool
    PALe(13, 2),   // Eyes and mouth
},
```

### #045 SPECIES_VILEPLUME
```c
[SPECIES_VILEPLUME] = {
    PALa(1, 4),    // Red/dark red body
    PALb(5, 3),    // Red flower petals
    PALc(8, 3),    // White/cream spots on petals
    PALd(11, 2),   // Yellow stigma
    PALe(13, 2),   // Eyes and feet
},
```

### #046 SPECIES_PARAS
```c
[SPECIES_PARAS] = {
    PALa(1, 4),    // Orange body/shell
    PALb(5, 3),    // Red/orange mushroom caps
    PALc(8, 2),    // White mushroom spots
    PALd(10, 3),   // Eyes and claws
    PALe(13, 2),   // Legs
},
```

### #047 SPECIES_PARASECT
```c
[SPECIES_PARASECT] = {
    PALa(1, 4),    // Orange/yellow body
    PALb(5, 3),    // Red/orange mushroom cap
    PALc(8, 3),    // White/cream mushroom spots
    PALd(11, 2),   // Eyes (white/blank)
    PALe(13, 2),   // Claws and legs
},
```

### #048 SPECIES_VENONAT
```c
[SPECIES_VENONAT] = {
    PALa(1, 4),    // Purple body/fur
    PALb(5, 3),    // Red/pink eyes
    PALc(8, 2),    // White eye highlights
    PALd(10, 3),   // Purple fur details
    PALe(13, 2),   // Mouth and feet
},
```

### #049 SPECIES_VENOMOTH
```c
[SPECIES_VENOMOTH] = {
    PALa(1, 4),    // Purple body
    PALb(5, 3),    // Light purple/pink wings
    PALc(8, 3),    // Dark purple wing patterns
    PALd(11, 2),   // Red eyes
    PALe(13, 2),   // Antennae and details
},
```

### #050 SPECIES_DIGLETT
```c
[SPECIES_DIGLETT] = {
    PALa(1, 4),    // Brown body
    PALb(5, 3),    // Pink nose
    PALc(8, 2),    // Darker brown shading
    PALd(10, 3),   // Eyes and mouth
    PALe(13, 2),   // Highlights
},
```

### #051 SPECIES_DUGTRIO
```c
[SPECIES_DUGTRIO] = {
    PALa(1, 4),    // Brown bodies
    PALb(5, 3),    // Pink noses
    PALc(8, 2),    // Dark brown shading
    PALd(10, 3),   // Eyes and mouths
    PALe(13, 2),   // Body highlights
},
```

### #052 SPECIES_MEOWTH
```c
[SPECIES_MEOWTH] = {
    PALa(1, 4),    // Cream/beige body
    PALb(5, 3),    // Brown stripes
    PALc(8, 2),    // Gold charm
    PALd(10, 2),   // Pink nose and ears
    PALe(12, 3),   // Eyes and whiskers
},
```

### #053 SPECIES_PERSIAN
```c
[SPECIES_PERSIAN] = {
    PALa(1, 4),    // Cream/tan body
    PALb(5, 3),    // Brown/tan accents
    PALc(8, 2),    // Red gem on forehead
    PALd(10, 3),   // Whiskers and ears
    PALe(13, 2),   // Eyes and details
},
```

### #054 SPECIES_PSYDUCK
```c
[SPECIES_PSYDUCK] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 2),    // Cream/beige bill
    PALc(8, 2),    // Black eyes
    PALd(10, 3),   // Limb shading
    PALe(13, 2),   // White highlights
},
```

### #055 SPECIES_GOLDUCK
```c
[SPECIES_GOLDUCK] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Cream/tan bill and hands
    PALc(8, 3),    // Red gem on forehead
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Webbed feet details
},
```

### #056 SPECIES_MANKEY
```c
[SPECIES_MANKEY] = {
    PALa(1, 4),    // Cream/tan body
    PALb(5, 3),    // Brown/tan fur patches
    PALc(8, 2),    // Pink nose and ears
    PALd(10, 3),   // Eyes and mouth
    PALe(13, 2),   // Hands and feet
},
```

### #057 SPECIES_PRIMEAPE
```c
[SPECIES_PRIMEAPE] = {
    PALa(1, 4),    // Cream/tan body
    PALb(5, 3),    // Brown fur
    PALc(8, 3),    // Pink nose, hands, and feet
    PALd(11, 2),   // Red angry eyes
    PALe(13, 2),   // Shackles/bands
},
```

### #058 SPECIES_GROWLITHE
```c
[SPECIES_GROWLITHE] = {
    PALa(1, 4),    // Orange body
    PALb(5, 3),    // Cream/tan stripes and muzzle
    PALc(8, 3),    // Black stripes
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Tail and details
},
```

### #059 SPECIES_ARCANINE
```c
[SPECIES_ARCANINE] = {
    PALa(1, 4),    // Orange body
    PALb(5, 3),    // Cream/tan mane and stripes
    PALc(8, 3),    // Black stripes
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Details and highlights
},
```

### #060 SPECIES_POLIWAG
```c
[SPECIES_POLIWAG] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // White belly
    PALc(8, 2),    // Black/dark blue spiral
    PALd(10, 3),   // Eyes and mouth
    PALe(13, 2),   // Tail and details
},
```

### #061 SPECIES_POLIWHIRL
```c
[SPECIES_POLIWHIRL] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // White belly
    PALc(8, 3),    // Black spiral pattern
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Hands and feet
},
```

### #062 SPECIES_POLIWRATH
```c
[SPECIES_POLIWRATH] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // White belly and gloves
    PALc(8, 3),    // Black spiral pattern
    PALd(11, 2),   // Eyes
    PALe(13, 2),   // Details
},
```

### #063 SPECIES_ABRA
```c
[SPECIES_ABRA] = {
    PALa(1, 4),    // Yellow/gold body
    PALb(5, 3),    // Brown/tan chest and joints
    PALc(8, 2),    // Tail
    PALd(10, 3),   // Ears and armor
    PALe(13, 2),   // Eyes (closed) and details
},
```

### #064 SPECIES_KADABRA
```c
[SPECIES_KADABRA] = {
    PALa(1, 4),    // Yellow/gold body
    PALb(5, 3),    // Brown chest and joints
    PALc(8, 3),    // Silver spoon
    PALd(11, 2),   // Red star on forehead
    PALe(13, 2),   // Eyes and whiskers
},
```

### #065 SPECIES_ALAKAZAM
```c
[SPECIES_ALAKAZAM] = {
    PALa(1, 4),    // Yellow/gold body
    PALb(5, 3),    // Brown chest and joints
    PALc(8, 3),    // Silver spoons
    PALd(11, 2),   // Red star on forehead
    PALe(13, 2),   // Eyes and mustache
},
```

### #066 SPECIES_MACHOP
```c
[SPECIES_MACHOP] = {
    PALa(1, 4),    // Grey/blue body
    PALb(5, 3),    // Darker grey markings
    PALc(8, 2),    // Red eyes
    PALd(10, 3),   // Black briefs/belt
    PALe(13, 2),   // Teeth and details
},
```

### #067 SPECIES_MACHOKE
```c
[SPECIES_MACHOKE] = {
    PALa(1, 4),    // Grey/blue body
    PALb(5, 3),    // Darker grey markings
    PALc(8, 3),    // Red eyes
    PALd(11, 2),   // Black belt/briefs
    PALe(13, 2),   // Teeth and muscles
},
```

### #068 SPECIES_MACHAMP
```c
[SPECIES_MACHAMP] = {
    PALa(1, 4),    // Grey/blue body
    PALb(5, 3),    // Darker grey markings
    PALc(8, 3),    // Red eyes
    PALd(11, 2),   // Black belt/briefs
    PALe(13, 2),   // Teeth and details
},
```

### #069 SPECIES_BELLSPROUT
```c
[SPECIES_BELLSPROUT] = {
    PALa(1, 4),    // Yellow/green body
    PALb(5, 3),    // Green leaves
    PALc(8, 2),    // Brown stem/roots
    PALd(10, 3),   // Eyes and mouth
    PALe(13, 2),   // Leaf details
},
```

### #070 SPECIES_WEEPINBELL
```c
[SPECIES_WEEPINBELL] = {
    PALa(1, 4),    // Yellow body
    PALb(5, 3),    // Green leaves/mouth
    PALc(8, 2),    // Pink/red mouth interior
    PALd(10, 3),   // Brown spots
    PALe(13, 2),   // Eyes and details
},
```

---

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
