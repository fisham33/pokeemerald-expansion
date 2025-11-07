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

## Pokémon #152-160 (Gen 2 Starters)

### #152 SPECIES_CHIKORITA
```c
[SPECIES_CHIKORITA] = {
    PALa(1, 4),    // Green body
    PALb(5, 2),    // Black outlines and details
    PALc(7, 4),    // Light green/yellow leaf
    PALd(11, 2),   // White/grey eyes
    PALe(13, 3),   // Pink/red inner mouth
},
```

### #153 SPECIES_BAYLEEF
```c
[SPECIES_BAYLEEF] = {
    PALa(1, 4),    // Green body
    PALb(5, 1),    // Black outlines
    PALc(6, 5),    // Brown stem and yellow leaves
    PALd(11, 1),   // White highlights
    PALe(12, 4),   // Red/orange neck buds and eyes
},
```

### #154 SPECIES_MEGANIUM
```c
[SPECIES_MEGANIUM] = {
    PALa(1, 3),    // Yellow antennae
    PALb(4, 4),    // Green body and leaves
    PALc(8, 2),    // Black outlines and white
    PALd(10, 4),   // Pink flower petals
    PALe(14, 2),   // Grey shading
},
```

### #155 SPECIES_CYNDAQUIL
```c
[SPECIES_CYNDAQUIL] = {
    PALa(1, 2),    // Red/orange back flames
    PALb(3, 3),    // Blue-teal body
    PALc(6, 3),    // Yellow flame spots and black
    PALd(9, 1),    // Dark blue shading
    PALe(10, 6),   // Cream/yellow belly
},
```

### #156 SPECIES_QUILAVA
```c
[SPECIES_QUILAVA] = {
    PALa(1, 4),    // Red/orange/yellow flames
    PALb(5, 3),    // Blue body
    PALc(8, 2),    // Black and dark red
    PALd(10, 1),   // White highlights
    PALe(11, 5),   // Cream/yellow belly
},
```

### #157 SPECIES_TYPHLOSION
```c
[SPECIES_TYPHLOSION] = {
    PALa(1, 4),    // Red/orange/yellow flames
    PALb(5, 3),    // Blue body
    PALc(8, 3),    // Cream belly
    PALd(11, 3),   // Black and white accents
    PALe(14, 2),   // Black and blue shading
},
```

### #158 SPECIES_TOTODILE
```c
[SPECIES_TOTODILE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 3),    // Black, white, and grey
    PALc(8, 1),    // Additional grey
    PALd(9, 4),    // Red spikes and mouth
    PALe(13, 3),   // Yellow belly
},
```

### #159 SPECIES_CROCONAW
```c
[SPECIES_CROCONAW] = {
    PALa(1, 2),    // Red and orange accents
    PALb(3, 3),    // Black and red spikes
    PALc(6, 4),    // Blue body
    PALd(10, 3),   // White and dark red
    PALe(13, 3),   // Yellow belly
},
```

### #160 SPECIES_FERALIGATR
```c
[SPECIES_FERALIGATR] = {
    PALa(1, 4),    // Dark red and pink spikes
    PALb(5, 4),    // Blue body
    PALc(9, 2),    // White and grey
    PALd(11, 4),   // Yellow belly
    PALe(15, 1),   // Black shading
},
```

---

## Pokémon #252-260 (Gen 3 Starters)

### #252 SPECIES_TREECKO
```c
[SPECIES_TREECKO] = {
    PALa(1, 2),    // Dark green body
    PALb(3, 3),    // Light green/yellow belly
    PALc(6, 4),    // Orange/yellow eyes and belly details
    PALd(10, 3),   // Pink/red mouth
    PALe(13, 3),   // Medium green shading
},
```

### #253 SPECIES_GROVYLE
```c
[SPECIES_GROVYLE] = {
    PALa(1, 4),    // Dark green body
    PALb(5, 4),    // Medium to light green shading
    PALc(9, 2),    // Orange/brown details
    PALd(11, 2),   // Yellow/white highlights
    PALe(13, 3),   // Red mouth and green accents
},
```

### #254 SPECIES_SCEPTILE
```c
[SPECIES_SCEPTILE] = {
    PALa(1, 1),    // Dark green
    PALb(2, 5),    // Light green body and leaves
    PALc(7, 3),    // Orange/yellow eyes and accents
    PALd(10, 3),   // Red mouth and orbs
    PALe(13, 3),   // Green shading details
},
```

### #255 SPECIES_TORCHIC
```c
[SPECIES_TORCHIC] = {
    PALa(1, 3),    // Orange/brown body
    PALb(4, 4),    // Black and red/orange accents
    PALc(8, 2),    // Light orange feathers
    PALd(10, 1),   // White highlights
    PALe(11, 5),   // Yellow/orange/brown variations
},
```

### #256 SPECIES_COMBUSKEN
```c
[SPECIES_COMBUSKEN] = {
    PALa(1, 2),    // Red/orange body
    PALb(3, 3),    // Black and darker red
    PALc(6, 3),    // Yellow/orange feathers
    PALd(9, 2),    // Red and white
    PALe(11, 5),   // Grey and tan shading
},
```

### #257 SPECIES_BLAZIKEN
```c
[SPECIES_BLAZIKEN] = {
    PALa(1, 2),    // Red body
    PALb(3, 3),    // Grey/tan feathers
    PALc(6, 3),    // Red and orange flames
    PALd(9, 2),    // Brown/dark and white
    PALe(11, 5),   // Yellow/orange/blue/white accents
},
```

### #258 SPECIES_MUDKIP
```c
[SPECIES_MUDKIP] = {
    PALa(1, 4),    // Blue body (dark to light)
    PALb(5, 4),    // Light blue/purple highlights
    PALc(9, 1),    // Light blue accent
    PALd(10, 4),   // Orange fin and belly
    PALe(14, 2),   // Grey/black shading
},
```

### #259 SPECIES_MARSHTOMP
```c
[SPECIES_MARSHTOMP] = {
    PALa(1, 2),    // Grey/black outlines
    PALb(3, 2),    // Grey body
    PALc(5, 4),    // Teal/cyan fins and gills
    PALd(9, 3),    // Orange/brown accents
    PALe(12, 4),   // Pink mouth and grey shading
},
```

### #260 SPECIES_SWAMPERT
```c
[SPECIES_SWAMPERT] = {
    PALa(1, 2),    // Black outlines
    PALb(3, 4),    // Grey/blue body
    PALc(7, 3),    // Orange/brown details
    PALd(10, 1),   // Light blue accent
    PALe(11, 5),   // Pink mouth, grey, and white shading
},
```

---

## Pokémon #387-395 (Gen 4 Starters)

### #387 SPECIES_TURTWIG
```c
[SPECIES_TURTWIG] = {
    PALa(1, 2),    // Green body
    PALb(3, 1),    // Light green shell
    PALc(4, 3),    // Brown/orange shell base
    PALd(7, 5),    // Green/yellow shell and body shading
    PALe(12, 4),   // Yellow twig and white highlights
},
```

### #388 SPECIES_GROTLE
```c
[SPECIES_GROTLE] = {
    PALa(1, 2),    // Green body
    PALb(3, 2),    // Light green shell
    PALc(5, 3),    // Brown shell base
    PALd(8, 5),    // Yellow/green tree and foliage
    PALe(13, 3),   // White and grey shading
},
```

### #389 SPECIES_TORTERRA
```c
[SPECIES_TORTERRA] = {
    PALa(1, 4),    // Dark green body
    PALb(5, 4),    // Grey shell and shading
    PALc(9, 3),    // Brown shell base
    PALd(12, 1),   // Dark green accent
    PALe(13, 3),   // Grey/brown shell details
},
```

### #390 SPECIES_CHIMCHAR
```c
[SPECIES_CHIMCHAR] = {
    PALa(1, 4),    // Orange/brown body
    PALb(5, 4),    // Cream/tan belly and face
    PALc(9, 1),    // Light orange accent
    PALd(10, 3),   // Red/pink face and flame
    PALe(13, 3),   // White, grey, and yellow details
},
```

### #391 SPECIES_MONFERNO
```c
[SPECIES_MONFERNO] = {
    PALa(1, 3),    // Red/brown body
    PALb(4, 3),    // Cream/tan belly
    PALc(7, 2),    // Yellow/orange flame
    PALd(9, 4),    // Blue flame base and details
    PALe(13, 3),   // Black, white, and grey shading
},
```

### #392 SPECIES_INFERNAPE
```c
[SPECIES_INFERNAPE] = {
    PALa(1, 3),    // Brown body and eyes
    PALb(4, 2),    // Blue head flame
    PALc(6, 3),    // Red/orange body flames
    PALd(9, 1),    // Yellow flame tips
    PALe(10, 6),   // Cream/tan belly and white highlights
},
```

### #393 SPECIES_PIPLUP
```c
[SPECIES_PIPLUP] = {
    PALa(1, 5),    // Blue body (dark to light)
    PALb(6, 4),    // White/grey belly and accents
    PALc(10, 1),   // Black outlines
    PALd(11, 4),   // Yellow/orange beak and feet
    PALe(15, 1),   // Grey shading
},
```

### #394 SPECIES_PRINPLUP
```c
[SPECIES_PRINPLUP] = {
    PALa(1, 4),    // Cream/tan head crest
    PALb(5, 1),    // Black outlines
    PALc(6, 5),    // Blue body
    PALd(11, 3),   // White/grey highlights
    PALe(14, 2),   // Light blue/white shading
},
```

### #395 SPECIES_EMPOLEON
```c
[SPECIES_EMPOLEON] = {
    PALa(1, 4),    // Cream/tan head crest
    PALb(5, 1),    // Black outlines
    PALc(6, 3),    // Dark blue body
    PALd(9, 4),    // Light blue body and highlights
    PALe(13, 3),   // White and grey shading
},
```

---

## Pokémon #495-503 (Gen 5 Starters)

### #495 SPECIES_SNIVY
```c
[SPECIES_SNIVY] = {
    PALa(1, 2),    // Dark green body
    PALb(3, 1),    // Black outlines
    PALc(4, 5),    // Yellow leaf/tail details
    PALd(9, 4),    // Brown/orange accents
    PALe(13, 3),   // Light green and white highlights
},
```

### #496 SPECIES_SERVINE
```c
[SPECIES_SERVINE] = {
    PALa(1, 2),    // Dark green body
    PALb(3, 3),    // Yellow leaf collar
    PALc(6, 2),    // Light green body shading
    PALd(8, 5),    // Black, white, and cream details
    PALe(13, 3),   // Yellow/brown leaf accents
},
```

### #497 SPECIES_SERPERIOR
```c
[SPECIES_SERPERIOR] = {
    PALa(1, 3),    // Cream/yellow leaf patterns
    PALb(4, 3),    // Green body
    PALc(7, 2),    // Black/dark outlines
    PALd(9, 4),    // White and light green highlights
    PALe(13, 4),   // Orange/red eyes and dark green accents
},
```

### #498 SPECIES_TEPIG
```c
[SPECIES_TEPIG] = {
    PALa(1, 5),    // Black and brown body
    PALb(6, 5),    // Orange/red body and ears
    PALc(11, 2),   // Yellow/orange flame and accents
    PALd(13, 3),   // White and cream highlights
},
```

### #499 SPECIES_PIGNITE
```c
[SPECIES_PIGNITE] = {
    PALa(1, 4),    // Black and brown body
    PALb(5, 4),    // Orange/red body and flame
    PALc(9, 3),    // Yellow flame collar
    PALd(12, 4),   // Red flame details and grey/brown shading
},
```

### #500 SPECIES_EMBOAR
```c
[SPECIES_EMBOAR] = {
    PALa(1, 3),    // Red body and eyes
    PALb(4, 2),    // Dark grey/black shading
    PALc(6, 3),    // Orange/red flame beard
    PALd(9, 4),    // Yellow flame accents
    PALe(13, 3),   // White, red, and brown details
},
```

### #501 SPECIES_OSHAWOTT
```c
[SPECIES_OSHAWOTT] = {
    PALa(1, 3),    // Grey scalchop and details
    PALb(4, 3),    // Blue body
    PALc(7, 1),    // Black outlines
    PALd(8, 2),    // Brown/orange nose
    PALe(10, 6),   // White, cyan, and cream highlights
},
```

### #502 SPECIES_DEWOTT
```c
[SPECIES_DEWOTT] = {
    PALa(1, 2),    // Blue body
    PALb(3, 3),    // Black, white, and red accents
    PALc(6, 3),    // Grey/blue body shading
    PALd(9, 3),    // Yellow/brown details
    PALe(12, 4),   // White, grey, and light blue highlights
},
```

### #503 SPECIES_SAMUROTT
```c
[SPECIES_SAMUROTT] = {
    PALa(1, 6),    // Black, brown, and yellow armor
    PALb(7, 2),    // Dark grey/black shading
    PALc(9, 3),    // White and cyan highlights
    PALd(12, 2),   // Blue body and red accents
    PALe(14, 2),   // Grey/blue shading
},
```

---

## Pokémon #650-658 (Gen 6 Starters)

### #650 SPECIES_CHESPIN
```c
[SPECIES_CHESPIN] = {
    PALa(1, 2),    // Green body
    PALb(3, 3),    // Light green/yellow belly
    PALc(6, 4),    // Brown shell/quills
    PALd(10, 2),   // Dark grey/brown details
    PALe(12, 4),   // Red/orange accents and white
},
```

### #651 SPECIES_QUILLADIN
```c
[SPECIES_QUILLADIN] = {
    PALa(1, 3),    // Red/orange shell spikes
    PALb(4, 2),    // Dark brown/black outlines
    PALc(6, 4),    // Green body and shell
    PALd(10, 3),   // Brown/tan details
    PALe(13, 3),   // Grey and white highlights
},
```

### #652 SPECIES_CHESNAUGHT
```c
[SPECIES_CHESNAUGHT] = {
    PALa(1, 3),    // Brown/tan armor
    PALb(4, 2),    // Black outlines
    PALc(6, 2),    // Red/pink shell spikes
    PALd(8, 4),    // Green body and dark brown
    PALe(12, 4),   // White and grey shading
},
```

### #653 SPECIES_FENNEKIN
```c
[SPECIES_FENNEKIN] = {
    PALa(1, 2),    // Orange/yellow fur
    PALb(3, 2),    // Black outlines
    PALc(5, 4),    // Red/orange body and ears
    PALd(9, 3),    // Grey/black details
    PALe(12, 4),   // White and cream highlights
},
```

### #654 SPECIES_BRAIXEN
```c
[SPECIES_BRAIXEN] = {
    PALa(1, 4),    // Orange/yellow fur and stick
    PALb(5, 4),    // Red/orange body
    PALc(9, 3),    // White and grey fur
    PALd(12, 4),   // Black/brown details and yellow accent
},
```

### #655 SPECIES_DELPHOX
```c
[SPECIES_DELPHOX] = {
    PALa(1, 4),    // Red/orange body and black
    PALb(5, 3),    // Orange/yellow fur and stick
    PALc(8, 4),    // White and grey highlights
    PALd(12, 2),   // Brown/tan details
    PALe(14, 2),   // Red/pink eyes and accents
},
```

### #656 SPECIES_FROAKIE
```c
[SPECIES_FROAKIE] = {
    PALa(1, 5),    // Blue body (dark to light)
    PALb(6, 1),    // Yellow bubbles
    PALc(7, 5),    // Grey/white/black details
    PALd(12, 1),   // Black outlines
},
```

### #657 SPECIES_FROGADIER
```c
[SPECIES_FROGADIER] = {
    PALa(1, 2),    // Dark blue body
    PALb(3, 4),    // Blue body shading
    PALc(7, 6),    // Grey/white foam and highlights
    PALd(13, 1),   // Yellow bubbles
},
```

### #658 SPECIES_GRENINJA
```c
[SPECIES_GRENINJA] = {
    PALa(1, 3),    // Dark blue body
    PALb(4, 2),    // Brown/tan details
    PALc(6, 3),    // Light blue tongue/scarf
    PALd(9, 4),    // Grey/white highlights
    PALe(13, 3),   // Pink/red tongue and black
},
```

---

## Pokémon #722-730 (Gen 7 Starters)

### #722 SPECIES_ROWLET
```c
[SPECIES_ROWLET] = {
    PALa(1, 3),    // Brown/tan body
    PALb(4, 3),    // White/cream belly and face
    PALc(7, 2),    // Black outlines
    PALd(9, 3),    // Orange/brown beak and feet
    PALe(12, 4),   // Green leaves and shading
},
```

### #723 SPECIES_DARTRIX
```c
[SPECIES_DARTRIX] = {
    PALa(1, 2),    // Green leaves
    PALb(3, 2),    // Brown body
    PALc(5, 2),    // Green body shading
    PALd(7, 8),    // Black, white, grey feathers and details
},
```

### #724 SPECIES_DECIDUEYE
```c
[SPECIES_DECIDUEYE] = {
    PALa(1, 3),    // Brown/tan feathers
    PALb(4, 1),    // Black outlines
    PALc(5, 3),    // Red/orange accents
    PALd(8, 4),    // Green hood and leaves
    PALe(12, 4),   // White/grey/brown details
},
```

### #725 SPECIES_LITTEN
```c
[SPECIES_LITTEN] = {
    PALa(1, 2),    // Dark grey/black fur
    PALb(3, 3),    // Grey stripes and shading
    PALc(6, 2),    // Red/cream details
    PALd(8, 4),    // Red stripes and yellow eyes
    PALe(12, 4),   // White, grey, and black details
},
```

### #726 SPECIES_TORRACAT
```c
[SPECIES_TORRACAT] = {
    PALa(1, 4),    // Black/grey body
    PALb(5, 2),    // Red stripes
    PALc(7, 1),    // Orange/brown accent
    PALd(8, 5),    // Grey/white fur and yellow bell
},
```

### #727 SPECIES_INCINEROAR
```c
[SPECIES_INCINEROAR] = {
    PALa(1, 3),    // Black/red body
    PALb(4, 2),    // Dark grey/black shading
    PALc(6, 3),    // Red/yellow flame belt
    PALd(9, 4),    // White, grey, and green accents
    PALe(13, 3),   // Grey/black details and orange
},
```

### #728 SPECIES_POPPLIO
```c
[SPECIES_POPPLIO] = {
    PALa(1, 5),    // Blue body and purple accents
    PALb(6, 2),    // Pink/purple details
    PALc(8, 1),    // Light blue shading
    PALd(9, 4),    // White and grey highlights
    PALe(13, 3),   // Dark blue/cyan details
},
```

### #729 SPECIES_BRIONNE
```c
[SPECIES_BRIONNE] = {
    PALa(1, 5),    // Blue body and grey details
    PALb(6, 3),    // White and light blue highlights
    PALc(9, 2),    // Cyan/blue accents
    PALd(11, 2),   // Black and pink details
    PALe(13, 3),   // Pink/purple frills and grey
},
```

### #730 SPECIES_PRIMARINA
```c
[SPECIES_PRIMARINA] = {
    PALa(1, 2),    // Blue body
    PALb(3, 5),    // Grey/blue and light blue shading
    PALc(8, 1),    // Black outlines
    PALd(9, 4),    // Pink/purple hair and accents
    PALe(13, 3),   // White and blue details
},
```

---

## Pokémon #810-818 (Gen 8 Starters)

### #810 SPECIES_GROOKEY
```c
[SPECIES_GROOKEY] = {
    PALa(1, 2),    // Green body
    PALb(3, 2),    // Light green/yellow highlights
    PALc(5, 2),    // Brown/tan details
    PALd(7, 4),    // Yellow stick and orange/brown accents
    PALe(11, 5),   // White, grey, and orange details
},
```

### #811 SPECIES_THWACKEY
```c
[SPECIES_THWACKEY] = {
    PALa(1, 2),    // Dark green body
    PALb(3, 3),    // Black, green, and yellow accents
    PALc(6, 2),    // Yellow/green leaves
    PALd(8, 6),    // Brown/tan sticks and cream highlights
    PALe(14, 2),   // Yellow and brown details
},
```

### #812 SPECIES_RILLABOOM
```c
[SPECIES_RILLABOOM] = {
    PALa(1, 4),    // Dark green body
    PALb(5, 5),    // Black, brown, and cream fur
    PALc(10, 2),   // Orange/red drum details
    PALd(12, 4),   // White, yellow, and brown highlights
},
```

### #813 SPECIES_SCORBUNNY
```c
[SPECIES_SCORBUNNY] = {
    PALa(1, 3),    // Red/orange body
    PALb(4, 2),    // Black and yellow details
    PALc(6, 5),    // White/grey/cream fur
    PALd(11, 2),   // White and orange highlights
    PALe(13, 1),   // Red/orange accent
},
```

### #814 SPECIES_RABOOT
```c
[SPECIES_RABOOT] = {
    PALa(1, 3),    // Grey/tan hoodie
    PALb(4, 4),    // Black, yellow, and white details
    PALc(8, 3),    // Red/orange body
    PALd(11, 1),   // Orange accent
    PALe(12, 3),   // Black/dark grey shading
},
```

### #815 SPECIES_CINDERACE
```c
[SPECIES_CINDERACE] = {
    PALa(1, 3),    // Grey/white fur
    PALb(4, 2),    // Black and white highlights
    PALc(6, 5),    // Yellow/red/orange flame markings
    PALd(11, 2),   // White and blue eyes
    PALe(13, 3),   // Black, brown, and dark details
},
```

### #816 SPECIES_SOBBLE
```c
[SPECIES_SOBBLE] = {
    PALa(1, 2),    // Blue body and yellow details
    PALb(3, 8),    // Light blue body and grey/white highlights
    PALc(11, 4),   // White, grey, and light blue shading
    PALd(15, 1),   // Black outlines
},
```

### #817 SPECIES_DRIZZILE
```c
[SPECIES_DRIZZILE] = {
    PALa(1, 4),    // Dark blue and purple details
    PALb(5, 4),    // Blue/cyan body
    PALc(9, 2),    // Green/yellow accents
    PALd(11, 4),   // Black, white, and grey highlights
    PALe(15, 1),   // Green detail
},
```

### #818 SPECIES_INTELEON
```c
[SPECIES_INTELEON] = {
    PALa(1, 2),    // Dark blue body
    PALb(3, 5),    // Yellow/tan/brown details
    PALc(8, 3),    // Blue/cyan body shading
    PALd(11, 1),   // Yellow accent
    PALe(12, 4),   // White, grey, and black details
},
```

---

## Legendary Pokémon - Gen 1

### #144 SPECIES_ARTICUNO
```c
[SPECIES_ARTICUNO] = {
    PALa(1, 4),    // Blue body (dark to light)
    PALb(5, 4),    // Black, dark blue, and light blue details
    PALc(9, 1),    // White highlights
    PALd(10, 4),   // Red eyes and brown beak
    PALe(14, 2),   // Light blue/grey shading
},
```

### #145 SPECIES_ZAPDOS
```c
[SPECIES_ZAPDOS] = {
    PALa(1, 5),    // Yellow/orange body and beak
    PALb(6, 3),    // Black outlines
    PALc(9, 5),    // White and yellow highlights
    PALd(14, 2),   // Grey shading and red eyes
},
```

### #146 SPECIES_MOLTRES
```c
[SPECIES_MOLTRES] = {
    PALa(1, 5),    // Red/orange flames and body
    PALb(6, 4),    // Yellow/orange flame tips
    PALc(10, 2),   // Black outlines
    PALd(12, 4),   // Brown/tan beak and feet
},
```

### #150 SPECIES_MEWTWO
```c
[SPECIES_MEWTWO] = {
    PALa(1, 5),    // Purple/grey body
    PALb(6, 1),    // White highlights
    PALc(7, 3),    // Purple psychic accents
    PALd(10, 2),   // White and purple highlights
    PALe(12, 4),   // Grey/white shading
},
```

### #151 SPECIES_MEW
```c
[SPECIES_MEW] = {
    PALa(1, 5),    // Pink body
    PALb(6, 2),    // Black outlines and white
    PALc(8, 3),    // Blue eyes
    PALd(11, 1),   // Brown/tan details
},
```

---

## Legendary Pokémon - Gen 2

### #243 SPECIES_RAIKOU
```c
[SPECIES_RAIKOU] = {
    PALa(1, 4),    // Purple mane/accents
    PALb(5, 4),    // Black, white, and grey body
    PALc(9, 1),    // White highlights
    PALd(10, 5),   // Yellow thunder markings
    PALe(15, 1),   // Grey shading
},
```

### #244 SPECIES_ENTEI
```c
[SPECIES_ENTEI] = {
    PALa(1, 5),    // Brown/tan body
    PALb(6, 2),    // Black outlines and yellow
    PALc(8, 2),    // Red body and flames
    PALd(10, 4),   // Grey/white smoke and highlights
    PALe(14, 2),   // Grey/brown shading
},
```

### #245 SPECIES_SUICUNE
```c
[SPECIES_SUICUNE] = {
    PALa(1, 4),    // Blue body
    PALb(5, 4),    // Purple mane/accents
    PALc(9, 3),    // Grey/white highlights
    PALd(12, 2),   // Red eyes and ribbons
    PALe(14, 2),   // Light blue/white shading
},
```

### #249 SPECIES_LUGIA
```c
[SPECIES_LUGIA] = {
    PALa(1, 4),    // Light blue/grey body
    PALb(5, 7),    // Black, white, and grey details
    PALc(12, 3),   // Red/pink eyes and blue accents
    PALd(15, 1),   // Blue shading
},
```

### #250 SPECIES_HO_OH
```c
[SPECIES_HO_OH] = {
    PALa(1, 2),    // Green tail feathers
    PALb(3, 3),    // Red body and wings
    PALc(6, 2),    // White and green highlights
    PALd(8, 1),    // Black outlines
    PALe(9, 7),   // Orange/yellow/brown plumage and details
},
```

### #251 SPECIES_CELEBI
```c
[SPECIES_CELEBI] = {
    PALa(1, 6),    // Green body
    PALb(7, 1),    // Dark green shading
    PALc(8, 5),    // Blue eyes and grey/white highlights
    PALd(13, 2),   // Yellow/cream accents
    PALe(15, 2),   // Grey/white and red details
},
```

---

## Legendary Pokémon - Gen 3

### #377 SPECIES_REGIROCK
```c
[SPECIES_REGIROCK] = {
    PALa(1, 2),    // Black outlines
    PALb(3, 5),    // Orange/brown rock body
    PALc(8, 5),    // Grey/tan rock shading and highlights
    PALd(13, 1),   // Black details
},
```

### #378 SPECIES_REGICE
```c
[SPECIES_REGICE] = {
    PALa(1, 4),    // Blue ice body (dark to light)
    PALb(5, 4),    // Black, white, and light blue highlights
    PALc(9, 3),    // Yellow eyes and accents
},
```

### #379 SPECIES_REGISTEEL
```c
[SPECIES_REGISTEEL] = {
    PALa(1, 4),    // Grey/black steel body
    PALb(5, 5),    // Silver/white metal shading
    PALc(10, 3),   // Red/pink eyes
    PALd(13, 2),   // Grey/blue metal accents
},
```

### #380 SPECIES_LATIAS
```c
[SPECIES_LATIAS] = {
    PALa(1, 5),    // Purple/blue/white feathers and body
    PALb(6, 5),    // Red body and accents
    PALc(11, 2),   // Yellow/orange details
    PALd(13, 3),   // White highlights and blue eyes
},
```

### #381 SPECIES_LATIOS
```c
[SPECIES_LATIOS] = {
    PALa(1, 6),    // Grey/purple/white body
    PALb(7, 5),    // Black, blue, and cyan details
    PALc(12, 2),   // Red eyes and accents
    PALd(14, 2),   // White highlights
},
```

### #382 SPECIES_KYOGRE
```c
[SPECIES_KYOGRE] = {
    PALa(1, 4),    // Dark grey/blue body
    PALb(5, 5),    // Blue markings and highlights
    PALc(10, 2),   // Red eyes and pink accents
    PALd(12, 3),   // Light blue/cyan highlights
    PALe(15, 1),   // Yellow detail
},
```

### #383 SPECIES_GROUDON
```c
[SPECIES_GROUDON] = {
    PALa(1, 8),    // Black, red, and orange body
    PALb(9, 2),    // Yellow/grey details
    PALc(11, 5),   // White and grey armor plates
},
```

### #384 SPECIES_RAYQUAZA
```c
[SPECIES_RAYQUAZA] = {
    PALa(1, 4),    // Green body (dark to light)
    PALb(5, 4),    // Black and dark green accents
    PALc(9, 4),    // Pink/red mouth and highlights
    PALd(13, 3),   // Yellow eyes and white/blue details
},
```

### #385 SPECIES_JIRACHI
```c
[SPECIES_JIRACHI] = {
    PALa(1, 5),    // Brown/tan tags and yellow body
    PALb(6, 5),    // Blue/cyan head ribbons
    PALc(11, 3),   // White and grey highlights
},
```

### #386 SPECIES_DEOXYS
```c
[SPECIES_DEOXYS] = {
    PALa(1, 4),    // Red/orange body
    PALb(5, 5),    // Blue/cyan crystals and grey details
    PALc(10, 4),   // Purple/pink accents
    PALd(14, 2),   // Grey/brown shading
},
```

---

## Legendary Pokémon - Gen 4

### #480 SPECIES_UXIE
```c
[SPECIES_UXIE] = {
    PALa(1, 5),    // Brown/tan/yellow body
    PALb(6, 4),    // Black and red eyes
    PALc(10, 4),   // Blue/grey tails
    PALd(14, 2),   // Brown/grey shading
},
```

### #481 SPECIES_MESPRIT
```c
[SPECIES_MESPRIT] = {
    PALa(1, 6),    // Black, pink/magenta body
    PALb(7, 5),    // Brown/grey details
    PALc(12, 4),   // Blue/grey tails and yellow/brown accents
},
```

### #482 SPECIES_AZELF
```c
[SPECIES_AZELF] = {
    PALa(1, 4),    // Blue body (dark to light)
    PALb(5, 4),    // Black, brown, and red eyes
    PALc(9, 4),    // White and light blue tails
    PALd(13, 3),   // Yellow/brown and grey accents
},
```

### #483 SPECIES_DIALGA
```c
[SPECIES_DIALGA] = {
    PALa(1, 4),    // Grey/blue metal body
    PALb(5, 6),    // Blue time crystals and armor
    PALc(11, 3),   // Red chest diamond and eyes
    PALd(14, 2),   // Blue/grey shading
},
```

### #484 SPECIES_PALKIA
```c
[SPECIES_PALKIA] = {
    PALa(1, 7),    // Purple/grey/white body
    PALb(8, 3),    // Pink/purple space crystals
    PALc(11, 2),   // White highlights
    PALd(13, 3),   // Red pearls and pink details
},
```

### #485 SPECIES_GIRATINA
```c
[SPECIES_GIRATINA] = {
    PALa(1, 4),    // Dark grey/black body
    PALb(5, 6),    // Red eyes and yellow/gold accents
    PALc(11, 2),   // Grey/white shading
    PALd(13, 3),   // Black and grey details
},
```

### #486 SPECIES_HEATRAN
```c
[SPECIES_HEATRAN] = {
    PALa(1, 4),    // Brown/dark body and pink accents
    PALb(5, 8),    // Grey/white metal shell and orange/yellow lava
    PALc(13, 3),   // Red/orange fire details
},
```

### #487 SPECIES_REGIGIGAS
```c
[SPECIES_REGIGIGAS] = {
    PALa(1, 4),    // Brown/tan moss and green body
    PALb(5, 3),    // Black and dark green details
    PALc(8, 5),    // White/grey body
    PALd(13, 3),   // Yellow/blue crystals and red eyes
},
```

### #488 SPECIES_CRESSELIA
```c
[SPECIES_CRESSELIA] = {
    PALa(1, 5),    // Brown/tan/yellow body
    PALb(6, 6),    // Pink/purple crescent wings
    PALc(12, 4),   // Blue eyes and white/grey highlights
},
```

### #489 SPECIES_PHIONE
```c
[SPECIES_PHIONE] = {
    PALa(1, 7),    // Blue body (dark to light)
    PALb(8, 2),    // Black and white
    PALc(10, 3),   // Grey/white highlights
    PALd(13, 3),   // Red/pink/orange accents
},
```

### #490 SPECIES_MANAPHY
```c
[SPECIES_MANAPHY] = {
    PALa(1, 7),    // Blue body (dark to light)
    PALb(8, 3),    // Black, white, and yellow antennae
    PALc(11, 2),   // White highlights
    PALd(12, 3),   // Red/pink/orange accents
},
```

### #491 SPECIES_DARKRAI
```c
[SPECIES_DARKRAI] = {
    PALa(1, 6),    // Black/grey/white shadowy body
    PALb(7, 3),    // Red eyes and accents
    PALc(10, 3),   // Cyan/blue nightmare smoke
    PALd(13, 1),   // Red detail
},
```

### #492 SPECIES_SHAYMIN
```c
[SPECIES_SHAYMIN] = {
    PALa(1, 6),    // Green body and flowers
    PALb(7, 4),    // Pink/purple flowers
    PALc(11, 2),   // Black and white
    PALd(13, 3),   // Green/brown/grey details
},
```

### #493 SPECIES_ARCEUS
```c
[SPECIES_ARCEUS] = {
    PALa(1, 5),    // Grey/white body
    PALb(6, 5),    // Yellow/gold ring and eyes
    PALc(11, 2),   // Red/pink gem
    PALd(13, 3),   // Green accents and yellow/white highlights
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
