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

### #000 SPECIES_NONE
```c
// Graphics not found
```


## Pokémon #1-100

### #001 SPECIES_BULBASAUR
```c
[SPECIES_BULBASAUR] = {
    PALa(1, 1),    // white
    PALb(2, 2),    // cyan
    PALc(4, 1),    // green
    PALd(5, 1),    // black
    PALe(6, 1),    // orange
},
```

### #002 SPECIES_IVYSAUR
```c
[SPECIES_IVYSAUR] = {
    PALa(1, 1),    // white
    PALb(2, 3),    // pink
    PALc(5, 2),    // cyan
    PALd(7, 1),    // green
    PALe(8, 1),    // black
},
```

### #003 SPECIES_VENUSAUR
```c
[SPECIES_VENUSAUR] = {
    PALa(1, 4),    // black
    PALb(5, 2),    // red
    PALc(7, 1),    // dark brown
    PALd(8, 1),    // red
    PALe(9, 2),    // orange
},
```

### #004 SPECIES_CHARMANDER
```c
[SPECIES_CHARMANDER] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // white
    PALd(4, 5),    // yellow
    PALe(9, 1),    // dark brown
},
```

### #005 SPECIES_CHARMELEON
```c
[SPECIES_CHARMELEON] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 4),    // orange
    PALe(8, 2),    // yellow
},
```

### #006 SPECIES_CHARIZARD
```c
[SPECIES_CHARIZARD] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 4),    // yellow
},
```

### #007 SPECIES_SQUIRTLE
```c
[SPECIES_SQUIRTLE] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // orange
    PALd(4, 1),    // red
    PALe(5, 1),    // dark brown
},
```

### #008 SPECIES_WARTORTLE
```c
[SPECIES_WARTORTLE] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // red
    PALc(5, 1),    // orange
    PALd(6, 1),    // grey
    PALe(7, 1),    // dark brown
},
```

### #009 SPECIES_BLASTOISE
```c
[SPECIES_BLASTOISE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #010 SPECIES_CATERPIE
```c
[SPECIES_CATERPIE] = {
    PALa(1, 6),    // black
    PALb(7, 2),    // grey
    PALc(9, 2),    // yellow
    PALd(11, 1),    // brown
    PALe(12, 3),    // red
},
```

### #011 SPECIES_METAPOD
```c
[SPECIES_METAPOD] = {
    PALa(1, 6),    // dark grey
    PALb(7, 7),    // purple
    PALc(14, 1),    // white
    PALd(15, 1),    // black
},
```

### #012 SPECIES_BUTTERFREE
```c
[SPECIES_BUTTERFREE] = {
    PALa(1, 6),    // black
    PALb(7, 1),    // dark brown
    PALc(8, 1),    // red
    PALd(9, 2),    // purple
    PALe(11, 4),    // blue
},
```

### #013 SPECIES_WEEDLE
```c
[SPECIES_WEEDLE] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #014 SPECIES_KAKUNA
```c
[SPECIES_KAKUNA] = {
    PALa(1, 2),    // white
    PALb(3, 5),    // yellow
    PALc(8, 2),    // purple
    PALd(10, 1),    // grey
    PALe(11, 2),    // dark grey
},
```

### #015 SPECIES_BEEDRILL
```c
[SPECIES_BEEDRILL] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // yellow
    PALc(3, 4),    // yellow
    PALd(7, 3),    // light grey
    PALe(10, 1),    // grey
},
```

### #016 SPECIES_PIDGEY
```c
[SPECIES_PIDGEY] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // orange
},
```

### #017 SPECIES_PIDGEOTTO
```c
[SPECIES_PIDGEOTTO] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // light purple
    PALe(6, 2),    // yellow
},
```

### #018 SPECIES_PIDGEOT
```c
[SPECIES_PIDGEOT] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 4),    // white
    PALd(7, 3),    // red
    PALe(10, 5),    // purple
},
```

### #019 SPECIES_RATTATA
```c
[SPECIES_RATTATA] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // red
    PALc(3, 1),    // red
    PALd(4, 3),    // purple
    PALe(7, 1),    // dark brown
},
```

### #020 SPECIES_RATICATE
```c
[SPECIES_RATICATE] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // yellow
    PALc(3, 1),    // orange
    PALd(4, 1),    // brown
    PALe(5, 2),    // yellow
},
```

### #021 SPECIES_SPEAROW
```c
[SPECIES_SPEAROW] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // light pink
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // orange
},
```

### #022 SPECIES_FEAROW
```c
[SPECIES_FEAROW] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // light pink
    PALc(3, 1),    // orange
    PALd(4, 3),    // brown
    PALe(7, 1),    // light pink
},
```

### #023 SPECIES_EKANS
```c
[SPECIES_EKANS] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // orange
    PALc(3, 2),    // red
    PALd(5, 3),    // yellow
    PALe(8, 2),    // brown
},
```

### #024 SPECIES_ARBOK
```c
[SPECIES_ARBOK] = {
    PALa(1, 1),    // yellow
    PALb(2, 1),    // orange
    PALc(3, 1),    // orange
    PALd(4, 1),    // red
    PALe(5, 1),    // orange
},
```

### #025 SPECIES_PIKACHU
```c
[SPECIES_PIKACHU] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // yellow
    PALc(3, 3),    // yellow
    PALd(6, 2),    // dark brown
    PALe(8, 1),    // purple
},
```

### #026 SPECIES_RAICHU
```c
[SPECIES_RAICHU] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // white
    PALc(4, 5),    // orange
    PALd(9, 1),    // yellow
    PALe(10, 1),    // orange
},
```

### #027 SPECIES_SANDSHREW
```c
[SPECIES_SANDSHREW] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // purple
    PALc(3, 5),    // yellow
    PALd(8, 1),    // blue
    PALe(9, 1),    // dark blue
},
```

### #028 SPECIES_SANDSLASH
```c
[SPECIES_SANDSLASH] = {
    PALa(1, 1),    // yellow
    PALb(2, 2),    // yellow
    PALc(4, 2),    // brown
    PALd(6, 1),    // white
    PALe(7, 3),    // yellow
},
```

### #029 SPECIES_NIDORAN_F
```c
[SPECIES_NIDORAN_F] = {
    PALa(1, 4),    // light grey
    PALb(5, 1),    // blue
    PALc(6, 2),    // red
    PALd(8, 3),    // green
    PALe(11, 2),    // purple
},
```

### #030 SPECIES_NIDORINA
```c
[SPECIES_NIDORINA] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // blue
    PALd(5, 2),    // blue
    PALe(7, 1),    // purple
},
```

### #031 SPECIES_NIDOQUEEN
```c
[SPECIES_NIDOQUEEN] = {
    PALa(1, 1),    // white
    PALb(2, 4),    // light grey
    PALc(6, 1),    // brown
    PALd(7, 1),    // purple
    PALe(8, 1),    // orange
},
```

### #032 SPECIES_NIDORAN_M
```c
[SPECIES_NIDORAN_M] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // orange
    PALd(6, 2),    // cyan
    PALe(8, 1),    // black
},
```

### #033 SPECIES_NIDORINO
```c
[SPECIES_NIDORINO] = {
    PALa(1, 1),    // white
    PALb(2, 3),    // orange
    PALc(5, 2),    // cyan
    PALd(7, 1),    // green
    PALe(8, 1),    // brown
},
```

### #034 SPECIES_NIDOKING
```c
[SPECIES_NIDOKING] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 1),    // red
    PALd(6, 1),    // dark red
    PALe(7, 1),    // purple
},
```

### #035 SPECIES_CLEFAIRY
```c
[SPECIES_CLEFAIRY] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 2),    // red
    PALe(6, 1),    // grey
},
```

### #036 SPECIES_CLEFABLE
```c
[SPECIES_CLEFABLE] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // light pink
    PALe(5, 3),    // purple
},
```

### #037 SPECIES_VULPIX
```c
[SPECIES_VULPIX] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // orange
    PALd(6, 2),    // brown
    PALe(8, 3),    // orange
},
```

### #038 SPECIES_NINETALES
```c
[SPECIES_NINETALES] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // orange
    PALc(3, 2),    // red
    PALd(5, 1),    // purple
    PALe(6, 2),    // orange
},
```

### #039 SPECIES_JIGGLYPUFF
```c
[SPECIES_JIGGLYPUFF] = {
    PALa(1, 2),    // white
    PALb(3, 3),    // cyan
    PALc(6, 2),    // grey
    PALd(8, 1),    // light grey
    PALe(9, 2),    // dark brown
},
```

### #040 SPECIES_WIGGLYTUFF
```c
[SPECIES_WIGGLYTUFF] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // cyan
    PALd(5, 1),    // green
    PALe(6, 1),    // dark grey
},
```

### #041 SPECIES_ZUBAT
```c
[SPECIES_ZUBAT] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // purple
    PALe(6, 2),    // white
},
```

### #042 SPECIES_GOLBAT
```c
[SPECIES_GOLBAT] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // black
    PALd(5, 1),    // light cyan
    PALe(6, 2),    // cyan
},
```

### #043 SPECIES_ODDISH
```c
[SPECIES_ODDISH] = {
    PALa(1, 1),    // white
    PALb(2, 2),    // red
    PALc(4, 3),    // yellow
    PALd(7, 1),    // dark brown
    PALe(8, 3),    // purple
},
```

### #044 SPECIES_GLOOM
```c
[SPECIES_GLOOM] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // orange
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark brown
    PALe(6, 4),    // orange
},
```

### #045 SPECIES_VILEPLUME
```c
[SPECIES_VILEPLUME] = {
    PALa(1, 4),    // orange
    PALb(5, 1),    // purple
    PALc(6, 2),    // brown
    PALd(8, 1),    // dark brown
    PALe(9, 2),    // light pink
},
```

### #046 SPECIES_PARAS
```c
[SPECIES_PARAS] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // orange
},
```

### #047 SPECIES_PARASECT
```c
[SPECIES_PARASECT] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 2),    // yellow
    PALd(6, 1),    // orange
    PALe(7, 2),    // red
},
```

### #048 SPECIES_VENONAT
```c
[SPECIES_VENONAT] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // light pink
    PALd(5, 2),    // red
    PALe(7, 1),    // black
},
```

### #049 SPECIES_VENOMOTH
```c
[SPECIES_VENOMOTH] = {
    PALa(1, 6),    // white
    PALb(7, 1),    // dark brown
    PALc(8, 2),    // purple
    PALd(10, 1),    // dark grey
    PALe(11, 4),    // white
},
```

### #050 SPECIES_DIGLETT
```c
[SPECIES_DIGLETT] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // purple
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // yellow
},
```

### #051 SPECIES_DUGTRIO
```c
[SPECIES_DUGTRIO] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // purple
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // yellow
},
```

### #052 SPECIES_MEOWTH
```c
[SPECIES_MEOWTH] = {
    PALa(1, 2),    // white
    PALb(3, 2),    // yellow
    PALc(5, 1),    // dark brown
    PALd(6, 2),    // orange
    PALe(8, 1),    // dark grey
},
```

### #053 SPECIES_PERSIAN
```c
[SPECIES_PERSIAN] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // yellow
    PALd(5, 1),    // red
    PALe(6, 1),    // dark red
},
```

### #054 SPECIES_PSYDUCK
```c
[SPECIES_PSYDUCK] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // dark brown
    PALc(5, 2),    // white
    PALd(7, 1),    // grey
    PALe(8, 3),    // purple
},
```

### #055 SPECIES_GOLDUCK
```c
[SPECIES_GOLDUCK] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // orange
    PALc(4, 1),    // red
    PALd(5, 1),    // dark red
    PALe(6, 1),    // yellow
},
```

### #056 SPECIES_MANKEY
```c
[SPECIES_MANKEY] = {
    PALa(1, 5),    // white
    PALb(6, 1),    // red
    PALc(7, 1),    // dark grey
    PALd(8, 3),    // yellow
    PALe(11, 1),    // dark brown
},
```

### #057 SPECIES_PRIMEAPE
```c
[SPECIES_PRIMEAPE] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // orange
},
```

### #058 SPECIES_GROWLITHE
```c
[SPECIES_GROWLITHE] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 2),    // orange
    PALd(6, 1),    // dark brown
    PALe(7, 3),    // yellow
},
```

### #059 SPECIES_ARCANINE
```c
[SPECIES_ARCANINE] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // red
    PALd(5, 1),    // red
    PALe(6, 1),    // orange
},
```

### #060 SPECIES_POLIWAG
```c
[SPECIES_POLIWAG] = {
    PALa(1, 1),    // white
    PALb(2, 2),    // light grey
    PALc(4, 1),    // grey
    PALd(5, 2),    // purple
    PALe(7, 1),    // blue
},
```

### #061 SPECIES_POLIWHIRL
```c
[SPECIES_POLIWHIRL] = {
    PALa(1, 4),    // white
    PALb(5, 3),    // purple
    PALc(8, 2),    // grey
    PALd(10, 1),    // blue
    PALe(11, 4),    // cyan
},
```

### #062 SPECIES_POLIWRATH
```c
[SPECIES_POLIWRATH] = {
    PALa(1, 4),    // white
    PALb(5, 2),    // purple
    PALc(7, 1),    // blue
    PALd(8, 2),    // grey
    PALe(10, 1),    // dark grey
},
```

### #063 SPECIES_ABRA
```c
[SPECIES_ABRA] = {
    PALa(1, 3),    // purple
    PALb(4, 4),    // orange
    PALc(8, 1),    // purple
    PALd(9, 1),    // yellow
    PALe(10, 5),    // yellow
},
```

### #064 SPECIES_KADABRA
```c
[SPECIES_KADABRA] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 1),    // red
    PALd(6, 4),    // orange
    PALe(10, 1),    // white
},
```

### #065 SPECIES_ALAKAZAM
```c
[SPECIES_ALAKAZAM] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 2),    // orange
    PALd(7, 4),    // dark brown
    PALe(11, 1),    // yellow
},
```

### #066 SPECIES_MACHOP
```c
[SPECIES_MACHOP] = {
    PALa(1, 1),    // black
    PALb(2, 5),    // dark grey
    PALc(7, 1),    // purple
    PALd(8, 1),    // dark brown
    PALe(9, 3),    // grey
},
```

### #067 SPECIES_MACHOKE
```c
[SPECIES_MACHOKE] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 4),    // blue
    PALd(8, 1),    // dark brown
    PALe(9, 1),    // brown
},
```

### #068 SPECIES_MACHAMP
```c
[SPECIES_MACHAMP] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 3),    // grey
    PALd(7, 1),    // dark brown
    PALe(8, 3),    // brown
},
```

### #069 SPECIES_BELLSPROUT
```c
[SPECIES_BELLSPROUT] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // brown
    PALd(5, 1),    // dark brown
    PALe(6, 3),    // red
},
```

### #070 SPECIES_WEEPINBELL
```c
[SPECIES_WEEPINBELL] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // white
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // brown
    PALe(5, 3),    // yellow
},
```

### #071 SPECIES_VICTREEBEL
```c
[SPECIES_VICTREEBEL] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // light grey
    PALc(3, 1),    // white
    PALd(4, 2),    // dark brown
    PALe(6, 3),    // orange
},
```

### #072 SPECIES_TENTACOOL
```c
[SPECIES_TENTACOOL] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // white
    PALc(4, 1),    // blue
    PALd(5, 3),    // blue
    PALe(8, 2),    // dark brown
},
```

### #073 SPECIES_TENTACRUEL
```c
[SPECIES_TENTACRUEL] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light pink
    PALc(3, 1),    // red
    PALd(4, 2),    // red
    PALe(6, 1),    // yellow
},
```

### #074 SPECIES_GEODUDE
```c
[SPECIES_GEODUDE] = {
    PALa(1, 3),    // dark grey
    PALb(4, 3),    // grey
    PALc(7, 3),    // dark brown
    PALd(10, 2),    // white
    PALe(12, 1),    // grey
},
```

### #075 SPECIES_GRAVELER
```c
[SPECIES_GRAVELER] = {
    PALa(1, 1),    // black
    PALb(2, 5),    // dark grey
    PALc(7, 1),    // grey
    PALd(8, 2),    // light grey
    PALe(10, 2),    // black
},
```

### #076 SPECIES_GOLEM
```c
[SPECIES_GOLEM] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // red
    PALe(5, 1),    // dark red
},
```

### #077 SPECIES_PONYTA
```c
[SPECIES_PONYTA] = {
    PALa(1, 1),    // black
    PALb(2, 4),    // white
    PALc(6, 2),    // brown
    PALd(8, 3),    // red
    PALe(11, 1),    // yellow
},
```

### #078 SPECIES_RAPIDASH
```c
[SPECIES_RAPIDASH] = {
    PALa(1, 1),    // black
    PALb(2, 4),    // white
    PALc(6, 2),    // brown
    PALd(8, 1),    // red
    PALe(9, 2),    // red
},
```

### #079 SPECIES_SLOWPOKE
```c
[SPECIES_SLOWPOKE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 3),    // yellow
},
```

### #080 SPECIES_SLOWBRO
```c
[SPECIES_SLOWBRO] = {
    PALa(1, 4),    // white
    PALb(5, 1),    // brown
    PALc(6, 3),    // light grey
    PALd(9, 1),    // grey
    PALe(10, 1),    // red
},
```

### #081 SPECIES_MAGNEMITE
```c
[SPECIES_MAGNEMITE] = {
    PALa(1, 4),    // white
    PALb(5, 2),    // grey
    PALc(7, 1),    // orange
    PALd(8, 1),    // red
    PALe(9, 1),    // cyan
},
```

### #082 SPECIES_MAGNETON
```c
[SPECIES_MAGNETON] = {
    PALa(1, 4),    // white
    PALb(5, 2),    // grey
    PALc(7, 1),    // orange
    PALd(8, 1),    // red
    PALe(9, 1),    // cyan
},
```

### #083 SPECIES_FARFETCHD
```c
[SPECIES_FARFETCHD] = {
    PALa(1, 6),    // white
    PALb(7, 1),    // brown
    PALc(8, 1),    // yellow
    PALd(9, 1),    // green
    PALe(10, 1),    // dark green
},
```

### #084 SPECIES_DODUO
```c
[SPECIES_DODUO] = {
    PALa(1, 4),    // purple
    PALb(5, 3),    // orange
    PALc(8, 1),    // dark brown
    PALd(9, 2),    // yellow
    PALe(11, 1),    // grey
},
```

### #085 SPECIES_DODRIO
```c
[SPECIES_DODRIO] = {
    PALa(1, 3),    // yellow
    PALb(4, 1),    // dark brown
    PALc(5, 1),    // yellow
    PALd(6, 1),    // grey
    PALe(7, 1),    // brown
},
```

### #086 SPECIES_SEEL
```c
[SPECIES_SEEL] = {
    PALa(1, 2),    // light grey
    PALb(3, 1),    // cyan
    PALc(4, 1),    // grey
    PALd(5, 1),    // white
    PALe(6, 1),    // yellow
},
```

### #087 SPECIES_DEWGONG
```c
[SPECIES_DEWGONG] = {
    PALa(1, 2),    // light grey
    PALb(3, 2),    // cyan
    PALc(5, 1),    // grey
    PALd(6, 2),    // red
    PALe(8, 4),    // purple
},
```

### #088 SPECIES_GRIMER
```c
[SPECIES_GRIMER] = {
    PALa(1, 4),    // white
    PALb(5, 1),    // dark grey
    PALc(6, 6),    // light grey
    PALd(12, 3),    // purple
    PALe(15, 1),    // dark grey
},
```

### #089 SPECIES_MUK
```c
[SPECIES_MUK] = {
    PALa(1, 4),    // white
    PALb(5, 1),    // dark grey
    PALc(6, 6),    // light grey
    PALd(12, 1),    // blue
    PALe(13, 2),    // purple
},
```

### #090 SPECIES_SHELLDER
```c
[SPECIES_SHELLDER] = {
    PALa(1, 3),    // light grey
    PALb(4, 2),    // grey
    PALc(6, 1),    // pink
    PALd(7, 1),    // red
    PALe(8, 1),    // dark brown
},
```

### #091 SPECIES_CLOYSTER
```c
[SPECIES_CLOYSTER] = {
    PALa(1, 1),    // white
    PALb(2, 3),    // purple
    PALc(5, 1),    // dark brown
    PALd(6, 4),    // purple
    PALe(10, 1),    // light grey
},
```

### #092 SPECIES_GASTLY
```c
[SPECIES_GASTLY] = {
    PALa(1, 2),    // white
    PALb(3, 2),    // red
    PALc(5, 1),    // purple
    PALd(6, 1),    // purple
    PALe(7, 2),    // grey
},
```

### #093 SPECIES_HAUNTER
```c
[SPECIES_HAUNTER] = {
    PALa(1, 3),    // purple
    PALb(4, 2),    // grey
    PALc(6, 3),    // purple
    PALd(9, 1),    // purple
    PALe(10, 1),    // red
},
```

### #094 SPECIES_GENGAR
```c
[SPECIES_GENGAR] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 3),    // light pink
    PALd(7, 1),    // light grey
    PALe(8, 2),    // purple
},
```

### #095 SPECIES_ONIX
```c
[SPECIES_ONIX] = {
    PALa(1, 1),    // white
    PALb(2, 7),    // purple
    PALc(9, 1),    // dark grey
    PALd(10, 3),    // light grey
    PALe(13, 1),    // grey
},
```

### #096 SPECIES_DROWZEE
```c
[SPECIES_DROWZEE] = {
    PALa(1, 1),    // black
    PALb(2, 4),    // dark brown
    PALc(6, 4),    // dark brown
    PALd(10, 1),    // yellow
    PALe(11, 1),    // yellow
},
```

### #097 SPECIES_HYPNO
```c
[SPECIES_HYPNO] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark brown
    PALc(3, 3),    // orange
    PALd(6, 1),    // yellow
    PALe(7, 3),    // dark brown
},
```

### #098 SPECIES_KRABBY
```c
[SPECIES_KRABBY] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // purple
    PALc(4, 1),    // white
    PALd(5, 1),    // purple
    PALe(6, 1),    // grey
},
```

### #099 SPECIES_KINGLER
```c
[SPECIES_KINGLER] = {
    PALa(1, 1),    // yellow
    PALb(2, 1),    // orange
    PALc(3, 1),    // red
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // white
},
```

### #100 SPECIES_VOLTORB
```c
[SPECIES_VOLTORB] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 1),    // grey
    PALd(6, 3),    // purple
    PALe(9, 5),    // purple
},
```


## Pokémon #101-200

### #101 SPECIES_ELECTRODE
```c
[SPECIES_ELECTRODE] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // light grey
    PALc(5, 1),    // grey
    PALd(6, 1),    // purple
    PALe(7, 7),    // purple
},
```

### #102 SPECIES_EXEGGCUTE
```c
[SPECIES_EXEGGCUTE] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // yellow
    PALc(4, 1),    // orange
    PALd(5, 1),    // dark grey
    PALe(6, 5),    // purple
},
```

### #103 SPECIES_EXEGGUTOR
```c
[SPECIES_EXEGGUTOR] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // orange
    PALc(4, 2),    // brown
    PALd(6, 2),    // grey
    PALe(8, 1),    // dark brown
},
```

### #104 SPECIES_CUBONE
```c
[SPECIES_CUBONE] = {
    PALa(1, 3),    // orange
    PALb(4, 1),    // dark brown
    PALc(5, 3),    // white
    PALd(8, 1),    // grey
    PALe(9, 1),    // grey
},
```

### #105 SPECIES_MAROWAK
```c
[SPECIES_MAROWAK] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 1),    // grey
    PALd(6, 1),    // dark grey
    PALe(7, 2),    // grey
},
```

### #106 SPECIES_HITMONLEE
```c
[SPECIES_HITMONLEE] = {
    PALa(1, 5),    // yellow
    PALb(6, 1),    // white
    PALc(7, 1),    // light grey
    PALd(8, 1),    // grey
    PALe(9, 1),    // yellow
},
```

### #107 SPECIES_HITMONCHAN
```c
[SPECIES_HITMONCHAN] = {
    PALa(1, 4),    // white
    PALb(5, 1),    // grey
    PALc(6, 1),    // red
    PALd(7, 3),    // orange
    PALe(10, 1),    // dark brown
},
```

### #108 SPECIES_LICKITUNG
```c
[SPECIES_LICKITUNG] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // yellow
    PALe(5, 1),    // brown
},
```

### #109 SPECIES_KOFFING
```c
[SPECIES_KOFFING] = {
    PALa(1, 4),    // white
    PALb(5, 2),    // purple
    PALc(7, 1),    // purple
    PALd(8, 2),    // yellow
    PALe(10, 1),    // orange
},
```

### #110 SPECIES_WEEZING
```c
[SPECIES_WEEZING] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // yellow
    PALe(5, 2),    // purple
},
```

### #111 SPECIES_RHYHORN
```c
[SPECIES_RHYHORN] = {
    PALa(1, 5),    // light grey
    PALb(6, 1),    // brown
    PALc(7, 1),    // black
    PALd(8, 1),    // grey
    PALe(9, 5),    // purple
},
```

### #112 SPECIES_RHYDON
```c
[SPECIES_RHYDON] = {
    PALa(1, 3),    // white
    PALb(4, 1),    // grey
    PALc(5, 1),    // brown
    PALd(6, 1),    // red
    PALe(7, 2),    // dark brown
},
```

### #113 SPECIES_CHANSEY
```c
[SPECIES_CHANSEY] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // brown
    PALd(5, 2),    // orange
    PALe(7, 1),    // dark grey
},
```

### #114 SPECIES_TANGELA
```c
[SPECIES_TANGELA] = {
    PALa(1, 1),    // light cyan
    PALb(2, 2),    // cyan
    PALc(4, 1),    // black
    PALd(5, 4),    // purple
    PALe(9, 3),    // purple
},
```

### #115 SPECIES_KANGASKHAN
```c
[SPECIES_KANGASKHAN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // grey
    PALc(4, 2),    // yellow
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // white
},
```

### #116 SPECIES_HORSEA
```c
[SPECIES_HORSEA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 2),    // cyan
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // white
},
```

### #117 SPECIES_SEADRA
```c
[SPECIES_SEADRA] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // light cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // cyan
    PALe(6, 1),    // brown
},
```

### #118 SPECIES_GOLDEEN
```c
[SPECIES_GOLDEEN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 2),    // light grey
    PALe(6, 1),    // yellow
},
```

### #119 SPECIES_SEAKING
```c
[SPECIES_SEAKING] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // white
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #120 SPECIES_STARYU
```c
[SPECIES_STARYU] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // orange
    PALd(4, 1),    // black
    PALe(5, 1),    // brown
},
```

### #121 SPECIES_STARMIE
```c
[SPECIES_STARMIE] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // light purple
    PALc(4, 2),    // blue
    PALd(6, 1),    // black
    PALe(7, 1),    // dark brown
},
```

### #122 SPECIES_MR_MIME
```c
[SPECIES_MR_MIME] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // blue
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark brown
    PALe(6, 3),    // light grey
},
```

### #123 SPECIES_SCYTHER
```c
[SPECIES_SCYTHER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // green
    PALe(5, 1),    // white
},
```

### #124 SPECIES_JYNX
```c
[SPECIES_JYNX] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // white
    PALd(5, 1),    // black
    PALe(6, 1),    // grey
},
```

### #125 SPECIES_ELECTABUZZ
```c
[SPECIES_ELECTABUZZ] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // black
    PALc(3, 1),    // yellow
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark brown
},
```

### #126 SPECIES_MAGMAR
```c
[SPECIES_MAGMAR] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 1),    // white
    PALe(6, 1),    // red
},
```

### #127 SPECIES_PINSIR
```c
[SPECIES_PINSIR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 2),    // grey
    PALe(6, 1),    // white
},
```

### #128 SPECIES_TAUROS
```c
[SPECIES_TAUROS] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // black
    PALd(4, 1),    // black
    PALe(5, 3),    // grey
},
```

### #129 SPECIES_MAGIKARP
```c
[SPECIES_MAGIKARP] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 2),    // red
    PALd(5, 1),    // white
    PALe(6, 1),    // grey
},
```

### #130 SPECIES_GYARADOS
```c
[SPECIES_GYARADOS] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // blue
    PALd(4, 1),    // white
    PALe(5, 1),    // dark blue
},
```

### #131 SPECIES_LAPRAS
```c
[SPECIES_LAPRAS] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 2),    // cyan
    PALd(5, 1),    // cyan
    PALe(6, 1),    // light grey
},
```

### #132 SPECIES_DITTO
```c
[SPECIES_DITTO] = {
    PALa(1, 2),    // purple
    PALb(3, 2),    // white
    PALc(5, 1),    // blue
    PALd(6, 1),    // black
    PALe(7, 1),    // purple
},
```

### #133 SPECIES_EEVEE
```c
[SPECIES_EEVEE] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // orange
    PALc(4, 1),    // black
    PALd(5, 2),    // dark brown
    PALe(7, 2),    // grey
},
```

### #134 SPECIES_VAPOREON
```c
[SPECIES_VAPOREON] = {
    PALa(1, 2),    // dark blue
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #135 SPECIES_JOLTEON
```c
[SPECIES_JOLTEON] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 3),    // orange
    PALd(6, 2),    // yellow
    PALe(8, 1),    // dark blue
},
```

### #136 SPECIES_FLAREON
```c
[SPECIES_FLAREON] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // orange
    PALe(6, 1),    // black
},
```

### #137 SPECIES_PORYGON
```c
[SPECIES_PORYGON] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // black
    PALc(3, 1),    // red
    PALd(4, 2),    // light pink
    PALe(6, 1),    // white
},
```

### #138 SPECIES_OMANYTE
```c
[SPECIES_OMANYTE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // grey
    PALc(3, 2),    // yellow
    PALd(5, 1),    // white
    PALe(6, 1),    // black
},
```

### #139 SPECIES_OMASTAR
```c
[SPECIES_OMASTAR] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // black
    PALd(4, 2),    // grey
    PALe(6, 1),    // white
},
```

### #140 SPECIES_KABUTO
```c
[SPECIES_KABUTO] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // black
    PALd(5, 1),    // black
    PALe(6, 1),    // brown
},
```

### #141 SPECIES_KABUTOPS
```c
[SPECIES_KABUTOPS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // light grey
},
```

### #142 SPECIES_AERODACTYL
```c
[SPECIES_AERODACTYL] = {
    PALa(1, 2),    // grey
    PALb(3, 5),    // cyan
    PALc(8, 1),    // dark grey
    PALd(9, 1),    // white
    PALe(10, 1),    // light grey
},
```

### #143 SPECIES_SNORLAX
```c
[SPECIES_SNORLAX] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // blue
    PALc(6, 1),    // cyan
    PALd(7, 3),    // yellow
    PALe(10, 2),    // grey
},
```

### #144 SPECIES_ARTICUNO
```c
[SPECIES_ARTICUNO] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // blue
    PALd(4, 1),    // cyan
    PALe(5, 2),    // dark grey
},
```

### #145 SPECIES_ZAPDOS
```c
[SPECIES_ZAPDOS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // black
    PALe(5, 1),    // orange
},
```

### #146 SPECIES_MOLTRES
```c
[SPECIES_MOLTRES] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // red
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // yellow
    PALe(5, 1),    // black
},
```

### #147 SPECIES_DRATINI
```c
[SPECIES_DRATINI] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // white
    PALc(4, 1),    // grey
    PALd(5, 1),    // blue
    PALe(6, 1),    // dark blue
},
```

### #148 SPECIES_DRAGONAIR
```c
[SPECIES_DRAGONAIR] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark blue
},
```

### #149 SPECIES_DRAGONITE
```c
[SPECIES_DRAGONITE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // orange
    PALd(4, 3),    // yellow
    PALe(7, 1),    // dark brown
},
```

### #150 SPECIES_MEWTWO
```c
[SPECIES_MEWTWO] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // black
},
```

### #151 SPECIES_MEW
```c
[SPECIES_MEW] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // purple
    PALd(4, 1),    // brown
    PALe(5, 1),    // light pink
},
```

### #152 SPECIES_CHIKORITA
```c
[SPECIES_CHIKORITA] = {
    PALa(1, 2),    // green
    PALb(3, 2),    // green
    PALc(5, 1),    // black
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // grey
},
```

### #153 SPECIES_BAYLEEF
```c
[SPECIES_BAYLEEF] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // green
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // brown
    PALe(8, 2),    // yellow
},
```

### #154 SPECIES_MEGANIUM
```c
[SPECIES_MEGANIUM] = {
    PALa(1, 1),    // yellow
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // orange
    PALd(4, 1),    // green
    PALe(5, 1),    // dark green
},
```

### #155 SPECIES_CYNDAQUIL
```c
[SPECIES_CYNDAQUIL] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // red
    PALc(3, 3),    // dark grey
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark grey
},
```

### #156 SPECIES_QUILAVA
```c
[SPECIES_QUILAVA] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // red
    PALc(3, 2),    // yellow
    PALd(5, 2),    // blue
    PALe(7, 1),    // cyan
},
```

### #157 SPECIES_TYPHLOSION
```c
[SPECIES_TYPHLOSION] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // red
    PALc(3, 2),    // yellow
    PALd(5, 1),    // blue
    PALe(6, 1),    // black
},
```

### #158 SPECIES_TOTODILE
```c
[SPECIES_TOTODILE] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // cyan
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // white
    PALe(7, 1),    // blue
},
```

### #159 SPECIES_CROCONAW
```c
[SPECIES_CROCONAW] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // red
},
```

### #160 SPECIES_FERALIGATR
```c
[SPECIES_FERALIGATR] = {
    PALa(1, 1),    // dark red
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // blue
},
```

### #161 SPECIES_SENTRET
```c
[SPECIES_SENTRET] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // red
    PALe(7, 1),    // brown
},
```

### #162 SPECIES_FURRET
```c
[SPECIES_FURRET] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // brown
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // yellow
},
```

### #163 SPECIES_HOOTHOOT
```c
[SPECIES_HOOTHOOT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // brown
    PALd(6, 2),    // orange
    PALe(8, 1),    // dark brown
},
```

### #164 SPECIES_NOCTOWL
```c
[SPECIES_NOCTOWL] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // yellow
    PALd(4, 1),    // brown
    PALe(5, 1),    // yellow
},
```

### #165 SPECIES_LEDYBA
```c
[SPECIES_LEDYBA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 3),    // red
    PALd(7, 1),    // light grey
    PALe(8, 1),    // white
},
```

### #166 SPECIES_LEDIAN
```c
[SPECIES_LEDIAN] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // red
    PALd(4, 1),    // purple
    PALe(5, 1),    // dark brown
},
```

### #167 SPECIES_SPINARAK
```c
[SPECIES_SPINARAK] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // green
    PALc(6, 2),    // green
    PALd(8, 1),    // brown
    PALe(9, 1),    // orange
},
```

### #168 SPECIES_ARIADOS
```c
[SPECIES_ARIADOS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // black
    PALd(4, 1),    // orange
    PALe(5, 2),    // purple
},
```

### #169 SPECIES_CROBAT
```c
[SPECIES_CROBAT] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // purple
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // dark blue
},
```

### #170 SPECIES_CHINCHOU
```c
[SPECIES_CHINCHOU] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // cyan
    PALc(4, 1),    // orange
    PALd(5, 1),    // yellow
    PALe(6, 1),    // cyan
},
```

### #171 SPECIES_LANTURN
```c
[SPECIES_LANTURN] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 2),    // blue
    PALd(6, 1),    // grey
    PALe(7, 1),    // dark blue
},
```

### #172 SPECIES_PICHU
```c
[SPECIES_PICHU] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // brown
    PALc(5, 1),    // yellow
    PALd(6, 1),    // brown
    PALe(7, 1),    // yellow
},
```

### #173 SPECIES_CLEFFA
```c
[SPECIES_CLEFFA] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // light pink
    PALc(5, 3),    // dark brown
    PALd(8, 1),    // dark grey
    PALe(9, 1),    // orange
},
```

### #174 SPECIES_IGGLYBUFF
```c
[SPECIES_IGGLYBUFF] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // light pink
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // purple
},
```

### #175 SPECIES_TOGEPI
```c
[SPECIES_TOGEPI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // white
    PALd(4, 1),    // orange
    PALe(5, 1),    // brown
},
```

### #176 SPECIES_TOGETIC
```c
[SPECIES_TOGETIC] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // black
    PALd(4, 2),    // light grey
    PALe(6, 2),    // red
},
```

### #177 SPECIES_NATU
```c
[SPECIES_NATU] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 2),    // green
    PALd(6, 2),    // green
    PALe(8, 1),    // dark grey
},
```

### #178 SPECIES_XATU
```c
[SPECIES_XATU] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // green
    PALc(3, 1),    // dark green
    PALd(4, 1),    // brown
    PALe(5, 1),    // green
},
```

### #179 SPECIES_MAREEP
```c
[SPECIES_MAREEP] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // orange
    PALc(3, 1),    // white
    PALd(4, 1),    // yellow
    PALe(5, 1),    // brown
},
```

### #180 SPECIES_FLAAFFY
```c
[SPECIES_FLAAFFY] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // white
    PALe(5, 1),    // dark grey
},
```

### #181 SPECIES_AMPHAROS
```c
[SPECIES_AMPHAROS] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // yellow
    PALd(5, 1),    // brown
    PALe(6, 1),    // red
},
```

### #182 SPECIES_BELLOSSOM
```c
[SPECIES_BELLOSSOM] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // orange
},
```

### #183 SPECIES_MARILL
```c
[SPECIES_MARILL] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // cyan
    PALc(4, 1),    // dark blue
    PALd(5, 1),    // blue
    PALe(6, 3),    // dark red
},
```

### #184 SPECIES_AZUMARILL
```c
[SPECIES_AZUMARILL] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 3),    // dark red
},
```

### #185 SPECIES_SUDOWOODO
```c
[SPECIES_SUDOWOODO] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // yellow
    PALd(5, 1),    // brown
    PALe(6, 1),    // black
},
```

### #186 SPECIES_POLITOED
```c
[SPECIES_POLITOED] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // green
    PALd(6, 1),    // yellow
    PALe(7, 1),    // green
},
```

### #187 SPECIES_HOPPIP
```c
[SPECIES_HOPPIP] = {
    PALa(1, 3),    // green
    PALb(4, 1),    // dark brown
    PALc(5, 1),    // black
    PALd(6, 1),    // grey
    PALe(7, 1),    // purple
},
```

### #188 SPECIES_SKIPLOOM
```c
[SPECIES_SKIPLOOM] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 3),    // yellow
    PALd(6, 1),    // cyan
    PALe(7, 1),    // white
},
```

### #189 SPECIES_JUMPLUFF
```c
[SPECIES_JUMPLUFF] = {
    PALa(1, 2),    // brown
    PALb(3, 3),    // yellow
    PALc(6, 1),    // green
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // green
},
```

### #190 SPECIES_AIPOM
```c
[SPECIES_AIPOM] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // purple
    PALd(5, 1),    // black
    PALe(6, 2),    // grey
},
```

### #191 SPECIES_SUNKERN
```c
[SPECIES_SUNKERN] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // green
    PALc(3, 1),    // black
    PALd(4, 1),    // green
    PALe(5, 1),    // dark grey
},
```

### #192 SPECIES_SUNFLORA
```c
[SPECIES_SUNFLORA] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // yellow
},
```

### #193 SPECIES_YANMA
```c
[SPECIES_YANMA] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // light grey
    PALc(4, 1),    // yellow
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // red
},
```

### #194 SPECIES_WOOPER
```c
[SPECIES_WOOPER] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // purple
    PALc(3, 1),    // grey
    PALd(4, 2),    // blue
    PALe(6, 2),    // cyan
},
```

### #195 SPECIES_QUAGSIRE
```c
[SPECIES_QUAGSIRE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // cyan
    PALc(3, 3),    // cyan
    PALd(6, 2),    // dark grey
    PALe(8, 1),    // blue
},
```

### #196 SPECIES_ESPEON
```c
[SPECIES_ESPEON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light pink
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // purple
    PALe(6, 1),    // dark grey
},
```

### #197 SPECIES_UMBREON
```c
[SPECIES_UMBREON] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // yellow
},
```

### #198 SPECIES_MURKROW
```c
[SPECIES_MURKROW] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // dark grey
    PALe(6, 1),    // orange
},
```

### #199 SPECIES_SLOWKING
```c
[SPECIES_SLOWKING] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // white
},
```

### #200 SPECIES_MISDREAVUS
```c
[SPECIES_MISDREAVUS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // purple
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // blue
},
```


## Pokémon #201-300

### #201 SPECIES_UNOWN
```c
[SPECIES_UNOWN] = {
    PALa(1, 3),    // purple
    PALb(4, 2),    // light grey
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // light grey
    PALe(8, 2),    // grey
},
```

### #202 SPECIES_WOBBUFFET
```c
[SPECIES_WOBBUFFET] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 2),    // cyan
    PALd(5, 1),    // light cyan
    PALe(6, 1),    // dark grey
},
```

### #203 SPECIES_GIRAFARIG
```c
[SPECIES_GIRAFARIG] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 1),    // dark grey
},
```

### #204 SPECIES_PINECO
```c
[SPECIES_PINECO] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // blue
    PALc(5, 1),    // white
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // grey
},
```

### #205 SPECIES_FORRETRESS
```c
[SPECIES_FORRETRESS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // light grey
},
```

### #206 SPECIES_DUNSPARCE
```c
[SPECIES_DUNSPARCE] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // yellow
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // grey
    PALe(7, 3),    // light grey
},
```

### #207 SPECIES_GLIGAR
```c
[SPECIES_GLIGAR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // purple
    PALe(6, 1),    // grey
},
```

### #208 SPECIES_STEELIX
```c
[SPECIES_STEELIX] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // light grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // white
},
```

### #209 SPECIES_SNUBBULL
```c
[SPECIES_SNUBBULL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // orange
    PALd(4, 1),    // brown
    PALe(5, 1),    // grey
},
```

### #210 SPECIES_GRANBULL
```c
[SPECIES_GRANBULL] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 2),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // light grey
},
```

### #211 SPECIES_QWILFISH
```c
[SPECIES_QWILFISH] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // blue
    PALe(6, 1),    // light grey
},
```

### #212 SPECIES_SCIZOR
```c
[SPECIES_SCIZOR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // brown
    PALe(6, 1),    // grey
},
```

### #213 SPECIES_SHUCKLE
```c
[SPECIES_SHUCKLE] = {
    PALa(1, 1),    // orange
    PALb(2, 2),    // yellow
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #214 SPECIES_HERACROSS
```c
[SPECIES_HERACROSS] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // blue
    PALe(6, 1),    // dark brown
},
```

### #215 SPECIES_SNEASEL
```c
[SPECIES_SNEASEL] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // black
    PALc(4, 1),    // red
    PALd(5, 2),    // grey
    PALe(7, 1),    // black
},
```

### #216 SPECIES_TEDDIURSA
```c
[SPECIES_TEDDIURSA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // white
},
```

### #217 SPECIES_URSARING
```c
[SPECIES_URSARING] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // black
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #218 SPECIES_SLUGMA
```c
[SPECIES_SLUGMA] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // orange
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // red
},
```

### #219 SPECIES_MAGCARGO
```c
[SPECIES_MAGCARGO] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // orange
    PALc(4, 1),    // yellow
    PALd(5, 1),    // dark brown
    PALe(6, 2),    // grey
},
```

### #220 SPECIES_SWINUB
```c
[SPECIES_SWINUB] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // orange
},
```

### #221 SPECIES_PILOSWINE
```c
[SPECIES_PILOSWINE] = {
    PALa(1, 2),    // brown
    PALb(3, 3),    // grey
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // dark brown
    PALe(8, 1),    // purple
},
```

### #222 SPECIES_CORSOLA
```c
[SPECIES_CORSOLA] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // light pink
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // pink
    PALe(5, 2),    // purple
},
```

### #223 SPECIES_REMORAID
```c
[SPECIES_REMORAID] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 2),    // white
    PALe(6, 1),    // grey
},
```

### #224 SPECIES_OCTILLERY
```c
[SPECIES_OCTILLERY] = {
    PALa(1, 2),    // dark brown
    PALb(3, 2),    // orange
    PALc(5, 2),    // red
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // orange
},
```

### #225 SPECIES_DELIBIRD
```c
[SPECIES_DELIBIRD] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // white
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 2),    // red
},
```

### #226 SPECIES_MANTINE
```c
[SPECIES_MANTINE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // black
    PALc(5, 4),    // light grey
    PALd(9, 1),    // light grey
    PALe(10, 1),    // white
},
```

### #227 SPECIES_SKARMORY
```c
[SPECIES_SKARMORY] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // blue
    PALd(4, 2),    // light cyan
    PALe(6, 1),    // dark grey
},
```

### #228 SPECIES_HOUNDOUR
```c
[SPECIES_HOUNDOUR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // white
    PALe(6, 1),    // dark grey
},
```

### #229 SPECIES_HOUNDOOM
```c
[SPECIES_HOUNDOOM] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // white
    PALe(5, 4),    // black
},
```

### #230 SPECIES_KINGDRA
```c
[SPECIES_KINGDRA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 1),    // cyan
},
```

### #231 SPECIES_PHANPY
```c
[SPECIES_PHANPY] = {
    PALa(1, 2),    // green
    PALb(3, 2),    // light cyan
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // red
},
```

### #232 SPECIES_DONPHAN
```c
[SPECIES_DONPHAN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // cyan
    PALe(7, 1),    // white
},
```

### #233 SPECIES_PORYGON2
```c
[SPECIES_PORYGON2] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // blue
    PALd(5, 1),    // purple
    PALe(6, 1),    // white
},
```

### #234 SPECIES_STANTLER
```c
[SPECIES_STANTLER] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark grey
},
```

### #235 SPECIES_SMEARGLE
```c
[SPECIES_SMEARGLE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // light pink
    PALc(3, 2),    // dark brown
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #236 SPECIES_TYROGUE
```c
[SPECIES_TYROGUE] = {
    PALa(1, 2),    // purple
    PALb(3, 1),    // purple
    PALc(4, 1),    // white
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // white
},
```

### #237 SPECIES_HITMONTOP
```c
[SPECIES_HITMONTOP] = {
    PALa(1, 1),    // white
    PALb(2, 3),    // yellow
    PALc(5, 1),    // brown
    PALd(6, 4),    // cyan
    PALe(10, 1),    // red
},
```

### #238 SPECIES_SMOOCHUM
```c
[SPECIES_SMOOCHUM] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // black
    PALd(5, 1),    // brown
    PALe(6, 1),    // purple
},
```

### #239 SPECIES_ELEKID
```c
[SPECIES_ELEKID] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // yellow
    PALc(4, 1),    // orange
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #240 SPECIES_MAGBY
```c
[SPECIES_MAGBY] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // white
},
```

### #241 SPECIES_MILTANK
```c
[SPECIES_MILTANK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // white
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #242 SPECIES_BLISSEY
```c
[SPECIES_BLISSEY] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // light pink
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // light pink
    PALe(7, 1),    // white
},
```

### #243 SPECIES_RAIKOU
```c
[SPECIES_RAIKOU] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // purple
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // white
    PALe(6, 1),    // light grey
},
```

### #244 SPECIES_ENTEI
```c
[SPECIES_ENTEI] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 2),    // brown
    PALd(5, 1),    // yellow
    PALe(6, 1),    // dark grey
},
```

### #245 SPECIES_SUICUNE
```c
[SPECIES_SUICUNE] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // dark grey
    PALc(3, 4),    // cyan
    PALd(7, 2),    // purple
    PALe(9, 1),    // grey
},
```

### #246 SPECIES_LARVITAR
```c
[SPECIES_LARVITAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // green
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #247 SPECIES_PUPITAR
```c
[SPECIES_PUPITAR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // cyan
    PALd(5, 2),    // blue
    PALe(7, 1),    // white
},
```

### #248 SPECIES_TYRANITAR
```c
[SPECIES_TYRANITAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // green
},
```

### #249 SPECIES_LUGIA
```c
[SPECIES_LUGIA] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #250 SPECIES_HO_OH
```c
[SPECIES_HO_OH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // green
    PALc(3, 2),    // red
    PALd(5, 1),    // cyan
    PALe(6, 1),    // orange
},
```

### #251 SPECIES_CELEBI
```c
[SPECIES_CELEBI] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // green
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // blue
    PALe(6, 1),    // blue
},
```

### #252 SPECIES_TREECKO
```c
[SPECIES_TREECKO] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // green
    PALe(5, 1),    // yellow
},
```

### #253 SPECIES_GROVYLE
```c
[SPECIES_GROVYLE] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // green
},
```

### #254 SPECIES_SCEPTILE
```c
[SPECIES_SCEPTILE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // yellow
    PALc(3, 2),    // green
    PALd(5, 1),    // green
    PALe(6, 1),    // dark grey
},
```

### #255 SPECIES_TORCHIC
```c
[SPECIES_TORCHIC] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // black
    PALd(5, 1),    // brown
    PALe(6, 2),    // orange
},
```

### #256 SPECIES_COMBUSKEN
```c
[SPECIES_COMBUSKEN] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // orange
    PALd(4, 2),    // dark brown
    PALe(6, 2),    // orange
},
```

### #257 SPECIES_BLAZIKEN
```c
[SPECIES_BLAZIKEN] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // grey
    PALe(5, 2),    // red
},
```

### #258 SPECIES_MUDKIP
```c
[SPECIES_MUDKIP] = {
    PALa(1, 1),    // dark blue
    PALb(2, 2),    // cyan
    PALc(4, 1),    // blue
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // cyan
},
```

### #259 SPECIES_MARSHTOMP
```c
[SPECIES_MARSHTOMP] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 2),    // green
    PALe(6, 2),    // cyan
},
```

### #260 SPECIES_SWAMPERT
```c
[SPECIES_SWAMPERT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 4),    // grey
    PALc(6, 1),    // cyan
    PALd(7, 1),    // brown
    PALe(8, 2),    // orange
},
```

### #261 SPECIES_POOCHYENA
```c
[SPECIES_POOCHYENA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // orange
},
```

### #262 SPECIES_MIGHTYENA
```c
[SPECIES_MIGHTYENA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // grey
    PALd(5, 2),    // dark grey
    PALe(7, 1),    // red
},
```

### #263 SPECIES_ZIGZAGOON
```c
[SPECIES_ZIGZAGOON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 4),    // grey
},
```

### #264 SPECIES_LINOONE
```c
[SPECIES_LINOONE] = {
    PALa(1, 5),    // grey
    PALb(6, 2),    // dark grey
    PALc(8, 1),    // grey
    PALd(9, 1),    // blue
    PALe(10, 1),    // cyan
},
```

### #265 SPECIES_WURMPLE
```c
[SPECIES_WURMPLE] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // red
    PALd(5, 1),    // black
    PALe(6, 2),    // grey
},
```

### #266 SPECIES_SILCOON
```c
[SPECIES_SILCOON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // cyan
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #267 SPECIES_BEAUTIFLY
```c
[SPECIES_BEAUTIFLY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // black
    PALe(5, 3),    // grey
},
```

### #268 SPECIES_CASCOON
```c
[SPECIES_CASCOON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // blue
    PALd(4, 2),    // white
    PALe(6, 2),    // purple
},
```

### #269 SPECIES_DUSTOX
```c
[SPECIES_DUSTOX] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark grey
},
```

### #270 SPECIES_LOTAD
```c
[SPECIES_LOTAD] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 1),    // green
    PALd(4, 2),    // dark green
    PALe(6, 2),    // grey
},
```

### #271 SPECIES_LOMBRE
```c
[SPECIES_LOMBRE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 3),    // green
    PALd(6, 1),    // white
    PALe(7, 1),    // grey
},
```

### #272 SPECIES_LUDICOLO
```c
[SPECIES_LUDICOLO] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 3),    // yellow
    PALd(6, 2),    // grey
    PALe(8, 1),    // grey
},
```

### #273 SPECIES_SEEDOT
```c
[SPECIES_SEEDOT] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // black
    PALc(4, 2),    // light grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // grey
},
```

### #274 SPECIES_NUZLEAF
```c
[SPECIES_NUZLEAF] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // green
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // grey
    PALe(8, 1),    // dark brown
},
```

### #275 SPECIES_SHIFTRY
```c
[SPECIES_SHIFTRY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // brown
},
```

### #276 SPECIES_TAILLOW
```c
[SPECIES_TAILLOW] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // brown
    PALc(5, 2),    // black
    PALd(7, 1),    // light grey
    PALe(8, 1),    // white
},
```

### #277 SPECIES_SWELLOW
```c
[SPECIES_SWELLOW] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // red
    PALc(4, 3),    // grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // dark brown
},
```

### #278 SPECIES_WINGULL
```c
[SPECIES_WINGULL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // black
    PALc(3, 2),    // white
    PALd(5, 1),    // blue
    PALe(6, 2),    // cyan
},
```

### #279 SPECIES_PELIPPER
```c
[SPECIES_PELIPPER] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 2),    // light cyan
    PALe(6, 1),    // white
},
```

### #280 SPECIES_RALTS
```c
[SPECIES_RALTS] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // green
    PALe(6, 1),    // dark green
},
```

### #281 SPECIES_KIRLIA
```c
[SPECIES_KIRLIA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark green
    PALc(3, 2),    // purple
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // yellow
},
```

### #282 SPECIES_GARDEVOIR
```c
[SPECIES_GARDEVOIR] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // green
    PALc(3, 2),    // yellow
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #283 SPECIES_SURSKIT
```c
[SPECIES_SURSKIT] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // brown
},
```

### #284 SPECIES_MASQUERAIN
```c
[SPECIES_MASQUERAIN] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // black
    PALc(4, 1),    // orange
    PALd(5, 2),    // light grey
    PALe(7, 1),    // dark blue
},
```

### #285 SPECIES_SHROOMISH
```c
[SPECIES_SHROOMISH] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // light pink
    PALc(4, 1),    // black
    PALd(5, 4),    // grey
    PALe(9, 1),    // white
},
```

### #286 SPECIES_BRELOOM
```c
[SPECIES_BRELOOM] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // red
    PALe(6, 1),    // black
},
```

### #287 SPECIES_SLAKOTH
```c
[SPECIES_SLAKOTH] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 3),    // yellow
    PALd(6, 2),    // dark brown
    PALe(8, 1),    // light grey
},
```

### #288 SPECIES_VIGOROTH
```c
[SPECIES_VIGOROTH] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark grey
},
```

### #289 SPECIES_SLAKING
```c
[SPECIES_SLAKING] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark brown
    PALc(4, 1),    // light grey
    PALd(5, 2),    // grey
    PALe(7, 3),    // light grey
},
```

### #290 SPECIES_NINCADA
```c
[SPECIES_NINCADA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 2),    // grey
    PALe(6, 1),    // light grey
},
```

### #291 SPECIES_NINJASK
```c
[SPECIES_NINJASK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 1),    // black
    PALe(5, 3),    // brown
},
```

### #292 SPECIES_SHEDINJA
```c
[SPECIES_SHEDINJA] = {
    PALa(1, 2),    // cyan
    PALb(3, 2),    // white
    PALc(5, 1),    // grey
    PALd(6, 2),    // orange
    PALe(8, 1),    // dark grey
},
```

### #293 SPECIES_WHISMUR
```c
[SPECIES_WHISMUR] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light purple
    PALc(4, 1),    // yellow
    PALd(5, 1),    // brown
    PALe(6, 1),    // yellow
},
```

### #294 SPECIES_LOUDRED
```c
[SPECIES_LOUDRED] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 1),    // black
},
```

### #295 SPECIES_EXPLOUD
```c
[SPECIES_EXPLOUD] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // black
    PALd(4, 1),    // orange
    PALe(5, 1),    // grey
},
```

### #296 SPECIES_MAKUHITA
```c
[SPECIES_MAKUHITA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 3),    // orange
    PALe(7, 1),    // brown
},
```

### #297 SPECIES_HARIYAMA
```c
[SPECIES_HARIYAMA] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // orange
    PALc(3, 1),    // brown
    PALd(4, 2),    // orange
    PALe(6, 1),    // yellow
},
```

### #298 SPECIES_AZURILL
```c
[SPECIES_AZURILL] = {
    PALa(1, 4),    // blue
    PALb(5, 1),    // dark grey
    PALc(6, 1),    // red
    PALd(7, 1),    // orange
    PALe(8, 1),    // light cyan
},
```

### #299 SPECIES_NOSEPASS
```c
[SPECIES_NOSEPASS] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // cyan
    PALd(5, 1),    // light cyan
    PALe(6, 1),    // black
},
```

### #300 SPECIES_SKITTY
```c
[SPECIES_SKITTY] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 3),    // purple
},
```


## Pokémon #301-400

### #301 SPECIES_DELCATTY
```c
[SPECIES_DELCATTY] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // purple
    PALc(4, 1),    // black
    PALd(5, 1),    // blue
    PALe(6, 1),    // orange
},
```

### #302 SPECIES_SABLEYE
```c
[SPECIES_SABLEYE] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // blue
    PALc(3, 2),    // black
    PALd(5, 2),    // blue
    PALe(7, 2),    // cyan
},
```

### #303 SPECIES_MAWILE
```c
[SPECIES_MAWILE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // yellow
},
```

### #304 SPECIES_ARON
```c
[SPECIES_ARON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #305 SPECIES_LAIRON
```c
[SPECIES_LAIRON] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // white
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // grey
},
```

### #306 SPECIES_AGGRON
```c
[SPECIES_AGGRON] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // white
    PALd(5, 3),    // light grey
    PALe(8, 1),    // cyan
},
```

### #307 SPECIES_MEDITITE
```c
[SPECIES_MEDITITE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #308 SPECIES_MEDICHAM
```c
[SPECIES_MEDICHAM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // red
    PALd(6, 1),    // grey
    PALe(7, 1),    // light grey
},
```

### #309 SPECIES_ELECTRIKE
```c
[SPECIES_ELECTRIKE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // green
    PALe(6, 2),    // yellow
},
```

### #310 SPECIES_MANECTRIC
```c
[SPECIES_MANECTRIC] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 1),    // yellow
    PALd(4, 2),    // orange
    PALe(6, 1),    // dark grey
},
```

### #311 SPECIES_PLUSLE
```c
[SPECIES_PLUSLE] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // yellow
    PALe(6, 1),    // brown
},
```

### #312 SPECIES_MINUN
```c
[SPECIES_MINUN] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 1),    // yellow
},
```

### #313 SPECIES_VOLBEAT
```c
[SPECIES_VOLBEAT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 2),    // grey
    PALe(6, 2),    // orange
},
```

### #314 SPECIES_ILLUMISE
```c
[SPECIES_ILLUMISE] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // purple
    PALe(7, 1),    // white
},
```

### #315 SPECIES_ROSELIA
```c
[SPECIES_ROSELIA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // green
    PALc(3, 1),    // black
    PALd(4, 1),    // green
    PALe(5, 1),    // dark grey
},
```

### #316 SPECIES_GULPIN
```c
[SPECIES_GULPIN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // black
    PALd(4, 2),    // yellow
    PALe(6, 5),    // dark grey
},
```

### #317 SPECIES_SWALOT
```c
[SPECIES_SWALOT] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // blue
    PALc(5, 1),    // black
    PALd(6, 1),    // white
    PALe(7, 1),    // red
},
```

### #318 SPECIES_CARVANHA
```c
[SPECIES_CARVANHA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 3),    // yellow
    PALe(7, 2),    // dark brown
},
```

### #319 SPECIES_SHARPEDO
```c
[SPECIES_SHARPEDO] = {
    PALa(1, 1),    // dark grey
    PALb(2, 4),    // blue
    PALc(6, 1),    // light grey
    PALd(7, 1),    // yellow
    PALe(8, 1),    // white
},
```

### #320 SPECIES_WAILMER
```c
[SPECIES_WAILMER] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // cyan
    PALc(5, 1),    // black
    PALd(6, 1),    // black
    PALe(7, 2),    // light grey
},
```

### #321 SPECIES_WAILORD
```c
[SPECIES_WAILORD] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // black
    PALc(4, 1),    // blue
    PALd(5, 1),    // light grey
    PALe(6, 1),    // grey
},
```

### #322 SPECIES_NUMEL
```c
[SPECIES_NUMEL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 2),    // brown
    PALe(7, 2),    // cyan
},
```

### #323 SPECIES_CAMERUPT
```c
[SPECIES_CAMERUPT] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // white
    PALe(6, 1),    // dark brown
},
```

### #324 SPECIES_TORKOAL
```c
[SPECIES_TORKOAL] = {
    PALa(1, 1),    // light grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark brown
    PALe(6, 2),    // orange
},
```

### #325 SPECIES_SPOINK
```c
[SPECIES_SPOINK] = {
    PALa(1, 3),    // grey
    PALb(4, 1),    // brown
    PALc(5, 2),    // light pink
    PALd(7, 3),    // grey
    PALe(10, 1),    // dark grey
},
```

### #326 SPECIES_GRUMPIG
```c
[SPECIES_GRUMPIG] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // grey
},
```

### #327 SPECIES_SPINDA
```c
[SPECIES_SPINDA] = {
    PALa(1, 3),    // light grey
    PALb(4, 1),    // grey
    PALc(5, 5),    // orange
    PALd(10, 1),    // grey
    PALe(11, 1),    // purple
},
```

### #328 SPECIES_TRAPINCH
```c
[SPECIES_TRAPINCH] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // orange
    PALc(4, 1),    // brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #329 SPECIES_VIBRAVA
```c
[SPECIES_VIBRAVA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // black
    PALc(3, 4),    // grey
    PALd(7, 1),    // grey
    PALe(8, 1),    // grey
},
```

### #330 SPECIES_FLYGON
```c
[SPECIES_FLYGON] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // cyan
    PALe(6, 1),    // dark brown
},
```

### #331 SPECIES_CACNEA
```c
[SPECIES_CACNEA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 1),    // black
    PALe(6, 3),    // green
},
```

### #332 SPECIES_CACTURNE
```c
[SPECIES_CACTURNE] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // green
    PALc(5, 3),    // dark brown
    PALd(8, 1),    // green
    PALe(9, 1),    // green
},
```

### #333 SPECIES_SWABLU
```c
[SPECIES_SWABLU] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 1),    // cyan
    PALe(5, 1),    // dark grey
},
```

### #334 SPECIES_ALTARIA
```c
[SPECIES_ALTARIA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // black
    PALc(3, 1),    // cyan
    PALd(4, 1),    // cyan
    PALe(5, 1),    // black
},
```

### #335 SPECIES_ZANGOOSE
```c
[SPECIES_ZANGOOSE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // white
},
```

### #336 SPECIES_SEVIPER
```c
[SPECIES_SEVIPER] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // grey
    PALc(4, 1),    // orange
    PALd(5, 1),    // yellow
    PALe(6, 1),    // grey
},
```

### #337 SPECIES_LUNATONE
```c
[SPECIES_LUNATONE] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // yellow
    PALc(4, 1),    // brown
    PALd(5, 1),    // orange
    PALe(6, 2),    // dark grey
},
```

### #338 SPECIES_SOLROCK
```c
[SPECIES_SOLROCK] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 2),    // orange
    PALe(6, 1),    // yellow
},
```

### #339 SPECIES_BARBOACH
```c
[SPECIES_BARBOACH] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // cyan
    PALc(4, 1),    // black
    PALd(5, 1),    // cyan
    PALe(6, 2),    // dark grey
},
```

### #340 SPECIES_WHISCASH
```c
[SPECIES_WHISCASH] = {
    PALa(1, 2),    // orange
    PALb(3, 2),    // brown
    PALc(5, 1),    // blue
    PALd(6, 2),    // cyan
    PALe(8, 1),    // black
},
```

### #341 SPECIES_CORPHISH
```c
[SPECIES_CORPHISH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 1),    // purple
    PALd(4, 1),    // red
    PALe(5, 1),    // dark brown
},
```

### #342 SPECIES_CRAWDAUNT
```c
[SPECIES_CRAWDAUNT] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // brown
    PALc(3, 1),    // white
    PALd(4, 1),    // black
    PALe(5, 1),    // yellow
},
```

### #343 SPECIES_BALTOY
```c
[SPECIES_BALTOY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // yellow
    PALd(4, 2),    // green
    PALe(6, 1),    // grey
},
```

### #344 SPECIES_CLAYDOL
```c
[SPECIES_CLAYDOL] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // grey
    PALd(6, 2),    // light grey
    PALe(8, 1),    // white
},
```

### #345 SPECIES_LILEEP
```c
[SPECIES_LILEEP] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // purple
    PALc(5, 2),    // blue
    PALd(7, 1),    // black
    PALe(8, 2),    // dark grey
},
```

### #346 SPECIES_CRADILY
```c
[SPECIES_CRADILY] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 2),    // purple
    PALd(5, 1),    // black
    PALe(6, 1),    // purple
},
```

### #347 SPECIES_ANORITH
```c
[SPECIES_ANORITH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 3),    // grey
    PALd(6, 1),    // dark brown
    PALe(7, 2),    // red
},
```

### #348 SPECIES_ARMALDO
```c
[SPECIES_ARMALDO] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // cyan
},
```

### #349 SPECIES_FEEBAS
```c
[SPECIES_FEEBAS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // brown
},
```

### #350 SPECIES_MILOTIC
```c
[SPECIES_MILOTIC] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // brown
    PALd(5, 2),    // yellow
    PALe(7, 1),    // blue
},
```

### #351 SPECIES_CASTFORM_NORMAL
```c
// Graphics not found
```

### #352 SPECIES_KECLEON
```c
[SPECIES_KECLEON] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // black
    PALc(4, 1),    // yellow
    PALd(5, 3),    // grey
    PALe(8, 4),    // yellow
},
```

### #353 SPECIES_SHUPPET
```c
[SPECIES_SHUPPET] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 2),    // cyan
    PALd(5, 2),    // grey
    PALe(7, 1),    // black
},
```

### #354 SPECIES_BANETTE
```c
[SPECIES_BANETTE] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // black
    PALd(6, 1),    // light grey
    PALe(7, 2),    // brown
},
```

### #355 SPECIES_DUSKULL
```c
[SPECIES_DUSKULL] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 4),    // light grey
},
```

### #356 SPECIES_DUSCLOPS
```c
[SPECIES_DUSCLOPS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 2),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #357 SPECIES_TROPIUS
```c
[SPECIES_TROPIUS] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // green
    PALe(6, 1),    // dark brown
},
```

### #358 SPECIES_CHIMECHO
```c
[SPECIES_CHIMECHO] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // yellow
},
```

### #359 SPECIES_ABSOL
```c
[SPECIES_ABSOL] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // blue
    PALc(5, 1),    // black
    PALd(6, 1),    // blue
    PALe(7, 1),    // white
},
```

### #360 SPECIES_WYNAUT
```c
[SPECIES_WYNAUT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // cyan
    PALc(5, 1),    // black
    PALd(6, 1),    // cyan
    PALe(7, 2),    // brown
},
```

### #361 SPECIES_SNORUNT
```c
[SPECIES_SNORUNT] = {
    PALa(1, 2),    // orange
    PALb(3, 2),    // yellow
    PALc(5, 1),    // black
    PALd(6, 1),    // orange
    PALe(7, 2),    // dark grey
},
```

### #362 SPECIES_GLALIE
```c
[SPECIES_GLALIE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 2),    // light grey
    PALd(6, 3),    // light grey
    PALe(9, 1),    // grey
},
```

### #363 SPECIES_SPHEAL
```c
[SPECIES_SPHEAL] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // blue
    PALc(4, 1),    // blue
    PALd(5, 1),    // light cyan
    PALe(6, 1),    // black
},
```

### #364 SPECIES_SEALEO
```c
[SPECIES_SEALEO] = {
    PALa(1, 3),    // blue
    PALb(4, 2),    // cyan
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // white
    PALe(8, 1),    // brown
},
```

### #365 SPECIES_WALREIN
```c
[SPECIES_WALREIN] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // black
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 2),    // white
},
```

### #366 SPECIES_CLAMPERL
```c
[SPECIES_CLAMPERL] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // blue
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // white
},
```

### #367 SPECIES_HUNTAIL
```c
[SPECIES_HUNTAIL] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // cyan
    PALe(5, 2),    // brown
},
```

### #368 SPECIES_GOREBYSS
```c
[SPECIES_GOREBYSS] = {
    PALa(1, 1),    // brown
    PALb(2, 4),    // white
    PALc(6, 1),    // black
    PALd(7, 1),    // purple
    PALe(8, 1),    // grey
},
```

### #369 SPECIES_RELICANTH
```c
[SPECIES_RELICANTH] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // grey
    PALd(5, 1),    // black
    PALe(6, 1),    // grey
},
```

### #370 SPECIES_LUVDISC
```c
[SPECIES_LUVDISC] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // light pink
    PALc(4, 1),    // black
    PALd(5, 3),    // purple
    PALe(8, 1),    // blue
},
```

### #371 SPECIES_BAGON
```c
[SPECIES_BAGON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // light grey
},
```

### #372 SPECIES_SHELGON
```c
[SPECIES_SHELGON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 4),    // light grey
    PALe(8, 1),    // yellow
},
```

### #373 SPECIES_SALAMENCE
```c
[SPECIES_SALAMENCE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 3),    // purple
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // blue
    PALe(8, 2),    // cyan
},
```

### #374 SPECIES_BELDUM
```c
[SPECIES_BELDUM] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 1),    // dark grey
},
```

### #375 SPECIES_METANG
```c
[SPECIES_METANG] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 1),    // dark blue
},
```

### #376 SPECIES_METAGROSS
```c
[SPECIES_METAGROSS] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // dark grey
    PALc(3, 4),    // cyan
    PALd(7, 2),    // light grey
    PALe(9, 1),    // grey
},
```

### #377 SPECIES_REGIROCK
```c
[SPECIES_REGIROCK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // orange
    PALd(5, 1),    // red
    PALe(6, 1),    // dark grey
},
```

### #378 SPECIES_REGICE
```c
[SPECIES_REGICE] = {
    PALa(1, 1),    // cyan
    PALb(2, 2),    // blue
    PALc(4, 1),    // black
    PALd(5, 1),    // light cyan
    PALe(6, 1),    // dark blue
},
```

### #379 SPECIES_REGISTEEL
```c
[SPECIES_REGISTEEL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // light grey
    PALe(6, 1),    // grey
},
```

### #380 SPECIES_LATIAS
```c
[SPECIES_LATIAS] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // white
    PALe(6, 1),    // brown
},
```

### #381 SPECIES_LATIOS
```c
[SPECIES_LATIOS] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // light grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // blue
    PALe(7, 1),    // dark grey
},
```

### #382 SPECIES_KYOGRE
```c
[SPECIES_KYOGRE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // blue
    PALe(5, 3),    // dark blue
},
```

### #383 SPECIES_GROUDON
```c
[SPECIES_GROUDON] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // light pink
    PALd(4, 1),    // red
    PALe(5, 1),    // orange
},
```

### #384 SPECIES_RAYQUAZA
```c
[SPECIES_RAYQUAZA] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // cyan
    PALc(4, 1),    // black
    PALd(5, 1),    // green
    PALe(6, 1),    // dark brown
},
```

### #385 SPECIES_JIRACHI
```c
[SPECIES_JIRACHI] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // black
    PALc(3, 3),    // yellow
    PALd(6, 1),    // cyan
    PALe(7, 1),    // blue
},
```

### #386 SPECIES_DEOXYS_NORMAL
```c
// Graphics not found
```

### #387 SPECIES_TURTWIG
```c
[SPECIES_TURTWIG] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // green
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #388 SPECIES_GROTLE
```c
[SPECIES_GROTLE] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark brown
    PALe(6, 2),    // grey
},
```

### #389 SPECIES_TORTERRA
```c
[SPECIES_TORTERRA] = {
    PALa(1, 3),    // black
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // grey
    PALe(7, 2),    // light grey
},
```

### #390 SPECIES_CHIMCHAR
```c
[SPECIES_CHIMCHAR] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // orange
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #391 SPECIES_MONFERNO
```c
[SPECIES_MONFERNO] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // brown
    PALd(4, 1),    // yellow
    PALe(5, 1),    // brown
},
```

### #392 SPECIES_INFERNAPE
```c
[SPECIES_INFERNAPE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // orange
},
```

### #393 SPECIES_PIPLUP
```c
[SPECIES_PIPLUP] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // cyan
    PALc(5, 3),    // cyan
    PALd(8, 2),    // grey
    PALe(10, 1),    // dark grey
},
```

### #394 SPECIES_PRINPLUP
```c
[SPECIES_PRINPLUP] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // dark blue
},
```

### #395 SPECIES_EMPOLEON
```c
[SPECIES_EMPOLEON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // brown
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark grey
},
```

### #396 SPECIES_STARLY
```c
[SPECIES_STARLY] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // light grey
},
```

### #397 SPECIES_STARAVIA
```c
[SPECIES_STARAVIA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // light grey
},
```

### #398 SPECIES_STARAPTOR
```c
[SPECIES_STARAPTOR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // grey
    PALe(6, 1),    // red
},
```

### #399 SPECIES_BIDOOF
```c
[SPECIES_BIDOOF] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // brown
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // yellow
},
```

### #400 SPECIES_BIBAREL
```c
[SPECIES_BIBAREL] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // brown
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // yellow
},
```


## Pokémon #401-500

### #401 SPECIES_KRICKETOT
```c
[SPECIES_KRICKETOT] = {
    PALa(1, 3),    // grey
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // brown
    PALd(6, 1),    // yellow
    PALe(7, 1),    // dark brown
},
```

### #402 SPECIES_KRICKETUNE
```c
[SPECIES_KRICKETUNE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 3),    // dark grey
    PALd(7, 1),    // white
    PALe(8, 1),    // grey
},
```

### #403 SPECIES_SHINX
```c
[SPECIES_SHINX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark grey
},
```

### #404 SPECIES_LUXIO
```c
[SPECIES_LUXIO] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 5),    // dark grey
    PALe(9, 1),    // cyan
},
```

### #405 SPECIES_LUXRAY
```c
[SPECIES_LUXRAY] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // grey
},
```

### #406 SPECIES_BUDEW
```c
[SPECIES_BUDEW] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // green
},
```

### #407 SPECIES_ROSERADE
```c
[SPECIES_ROSERADE] = {
    PALa(1, 1),    // green
    PALb(2, 2),    // white
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // black
    PALe(7, 1),    // green
},
```

### #408 SPECIES_CRANIDOS
```c
[SPECIES_CRANIDOS] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // white
    PALc(4, 1),    // dark blue
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // blue
},
```

### #409 SPECIES_RAMPARDOS
```c
[SPECIES_RAMPARDOS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light cyan
    PALe(5, 1),    // blue
},
```

### #410 SPECIES_SHIELDON
```c
[SPECIES_SHIELDON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #411 SPECIES_BASTIODON
```c
[SPECIES_BASTIODON] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #412 SPECIES_BURMY_PLANT
```c
// Graphics not found
```

### #413 SPECIES_WORMADAM_PLANT
```c
// Graphics not found
```

### #414 SPECIES_MOTHIM_PLANT
```c
// Graphics not found
```

### #415 SPECIES_COMBEE
```c
[SPECIES_COMBEE] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // light grey
    PALc(6, 1),    // orange
    PALd(7, 1),    // dark brown
    PALe(8, 1),    // yellow
},
```

### #416 SPECIES_VESPIQUEN
```c
[SPECIES_VESPIQUEN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark brown
},
```

### #417 SPECIES_PACHIRISU
```c
[SPECIES_PACHIRISU] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 2),    // blue
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #418 SPECIES_BUIZEL
```c
[SPECIES_BUIZEL] = {
    PALa(1, 2),    // brown
    PALb(3, 2),    // dark brown
    PALc(5, 1),    // blue
    PALd(6, 1),    // yellow
    PALe(7, 1),    // cyan
},
```

### #419 SPECIES_FLOATZEL
```c
[SPECIES_FLOATZEL] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // yellow
    PALe(6, 1),    // yellow
},
```

### #420 SPECIES_CHERUBI
```c
[SPECIES_CHERUBI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // green
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // green
    PALe(6, 1),    // dark grey
},
```

### #421 SPECIES_CHERRIM_OVERCAST
```c
// Graphics not found
```

### #422 SPECIES_SHELLOS_WEST
```c
// Graphics not found
```

### #423 SPECIES_GASTRODON_WEST
```c
// Graphics not found
```

### #424 SPECIES_AMBIPOM
```c
[SPECIES_AMBIPOM] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // orange
    PALe(7, 1),    // brown
},
```

### #425 SPECIES_DRIFLOON
```c
[SPECIES_DRIFLOON] = {
    PALa(1, 2),    // white
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // blue
    PALe(7, 1),    // blue
},
```

### #426 SPECIES_DRIFBLIM
```c
[SPECIES_DRIFBLIM] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // grey
},
```

### #427 SPECIES_BUNEARY
```c
[SPECIES_BUNEARY] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // grey
},
```

### #428 SPECIES_LOPUNNY
```c
[SPECIES_LOPUNNY] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 3),    // brown
},
```

### #429 SPECIES_MISMAGIUS
```c
[SPECIES_MISMAGIUS] = {
    PALa(1, 3),    // grey
    PALb(4, 2),    // dark grey
    PALc(6, 2),    // blue
    PALd(8, 1),    // orange
    PALe(9, 1),    // white
},
```

### #430 SPECIES_HONCHKROW
```c
[SPECIES_HONCHKROW] = {
    PALa(1, 6),    // blue
    PALb(7, 1),    // green
    PALc(8, 1),    // light grey
    PALd(9, 1),    // white
    PALe(10, 1),    // yellow
},
```

### #431 SPECIES_GLAMEOW
```c
[SPECIES_GLAMEOW] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 2),    // cyan
    PALe(6, 2),    // grey
},
```

### #432 SPECIES_PURUGLY
```c
[SPECIES_PURUGLY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // blue
    PALc(4, 1),    // blue
    PALd(5, 1),    // grey
    PALe(6, 1),    // purple
},
```

### #433 SPECIES_CHINGLING
```c
[SPECIES_CHINGLING] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // white
    PALc(5, 1),    // cyan
    PALd(6, 1),    // black
    PALe(7, 1),    // grey
},
```

### #434 SPECIES_STUNKY
```c
[SPECIES_STUNKY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // yellow
},
```

### #435 SPECIES_SKUNTANK
```c
[SPECIES_SKUNTANK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // blue
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // grey
    PALe(7, 1),    // yellow
},
```

### #436 SPECIES_BRONZOR
```c
[SPECIES_BRONZOR] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // blue
    PALc(4, 1),    // cyan
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // yellow
},
```

### #437 SPECIES_BRONZONG
```c
[SPECIES_BRONZONG] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // cyan
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // blue
    PALe(7, 3),    // cyan
},
```

### #438 SPECIES_BONSLY
```c
[SPECIES_BONSLY] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // green
    PALd(4, 1),    // green
    PALe(5, 1),    // black
},
```

### #439 SPECIES_MIME_JR
```c
[SPECIES_MIME_JR] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // white
    PALc(5, 1),    // black
    PALd(6, 3),    // black
    PALe(9, 1),    // dark brown
},
```

### #440 SPECIES_HAPPINY
```c
[SPECIES_HAPPINY] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // light pink
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 2),    // purple
},
```

### #441 SPECIES_CHATOT
```c
[SPECIES_CHATOT] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // black
    PALc(5, 1),    // light grey
    PALd(6, 1),    // light grey
    PALe(7, 1),    // purple
},
```

### #442 SPECIES_SPIRITOMB
```c
[SPECIES_SPIRITOMB] = {
    PALa(1, 2),    // purple
    PALb(3, 1),    // green
    PALc(4, 1),    // yellow
    PALd(5, 1),    // yellow
    PALe(6, 2),    // dark grey
},
```

### #443 SPECIES_GIBLE
```c
[SPECIES_GIBLE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // cyan
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #444 SPECIES_GABITE
```c
[SPECIES_GABITE] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // blue
    PALc(5, 1),    // cyan
    PALd(6, 1),    // blue
    PALe(7, 1),    // dark grey
},
```

### #445 SPECIES_GARCHOMP
```c
[SPECIES_GARCHOMP] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // orange
    PALc(3, 1),    // black
    PALd(4, 1),    // blue
    PALe(5, 1),    // yellow
},
```

### #446 SPECIES_MUNCHLAX
```c
[SPECIES_MUNCHLAX] = {
    PALa(1, 2),    // dark blue
    PALb(3, 1),    // blue
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // blue
    PALe(6, 1),    // light grey
},
```

### #447 SPECIES_RIOLU
```c
[SPECIES_RIOLU] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark blue
    PALc(4, 1),    // cyan
    PALd(5, 2),    // dark grey
    PALe(7, 2),    // brown
},
```

### #448 SPECIES_LUCARIO
```c
[SPECIES_LUCARIO] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 3),    // dark grey
},
```

### #449 SPECIES_HIPPOPOTAS
```c
[SPECIES_HIPPOPOTAS] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // dark brown
    PALc(5, 1),    // light grey
    PALd(6, 1),    // brown
    PALe(7, 2),    // grey
},
```

### #450 SPECIES_HIPPOWDON
```c
[SPECIES_HIPPOWDON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // orange
},
```

### #451 SPECIES_SKORUPI
```c
[SPECIES_SKORUPI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #452 SPECIES_DRAPION
```c
[SPECIES_DRAPION] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark grey
    PALc(5, 3),    // blue
    PALd(8, 1),    // blue
    PALe(9, 1),    // dark grey
},
```

### #453 SPECIES_CROAGUNK
```c
[SPECIES_CROAGUNK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // cyan
    PALd(5, 2),    // grey
    PALe(7, 1),    // yellow
},
```

### #454 SPECIES_TOXICROAK
```c
[SPECIES_TOXICROAK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // blue
    PALd(5, 2),    // dark grey
    PALe(7, 1),    // brown
},
```

### #455 SPECIES_CARNIVINE
```c
[SPECIES_CARNIVINE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 2),    // green
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // white
},
```

### #456 SPECIES_FINNEON
```c
[SPECIES_FINNEON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 1),    // dark grey
},
```

### #457 SPECIES_LUMINEON
```c
[SPECIES_LUMINEON] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // white
    PALd(5, 1),    // blue
    PALe(6, 2),    // dark grey
},
```

### #458 SPECIES_MANTYKE
```c
[SPECIES_MANTYKE] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // cyan
    PALc(4, 1),    // black
    PALd(5, 1),    // blue
    PALe(6, 1),    // black
},
```

### #459 SPECIES_SNOVER
```c
[SPECIES_SNOVER] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // white
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #460 SPECIES_ABOMASNOW
```c
[SPECIES_ABOMASNOW] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // green
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // green
    PALe(6, 4),    // white
},
```

### #461 SPECIES_WEAVILE
```c
[SPECIES_WEAVILE] = {
    PALa(1, 2),    // red
    PALb(3, 2),    // red
    PALc(5, 1),    // grey
    PALd(6, 1),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #462 SPECIES_MAGNEZONE
```c
[SPECIES_MAGNEZONE] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark grey
},
```

### #463 SPECIES_LICKILICKY
```c
[SPECIES_LICKILICKY] = {
    PALa(1, 2),    // brown
    PALb(3, 2),    // pink
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // white
},
```

### #464 SPECIES_RHYPERIOR
```c
[SPECIES_RHYPERIOR] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // white
    PALd(6, 1),    // grey
    PALe(7, 2),    // dark grey
},
```

### #465 SPECIES_TANGROWTH
```c
[SPECIES_TANGROWTH] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // dark brown
    PALc(4, 2),    // black
    PALd(6, 2),    // cyan
    PALe(8, 1),    // black
},
```

### #466 SPECIES_ELECTIVIRE
```c
[SPECIES_ELECTIVIRE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 2),    // brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #467 SPECIES_MAGMORTAR
```c
[SPECIES_MAGMORTAR] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 2),    // red
    PALd(6, 1),    // red
    PALe(7, 1),    // dark brown
},
```

### #468 SPECIES_TOGEKISS
```c
[SPECIES_TOGEKISS] = {
    PALa(1, 2),    // cyan
    PALb(3, 1),    // grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #469 SPECIES_YANMEGA
```c
[SPECIES_YANMEGA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // cyan
    PALe(5, 1),    // white
},
```

### #470 SPECIES_LEAFEON
```c
[SPECIES_LEAFEON] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // dark brown
    PALe(7, 2),    // black
},
```

### #471 SPECIES_GLACEON
```c
[SPECIES_GLACEON] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #472 SPECIES_GLISCOR
```c
[SPECIES_GLISCOR] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // purple
    PALc(3, 1),    // black
    PALd(4, 1),    // purple
    PALe(5, 1),    // blue
},
```

### #473 SPECIES_MAMOSWINE
```c
[SPECIES_MAMOSWINE] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // white
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #474 SPECIES_PORYGON_Z
```c
[SPECIES_PORYGON_Z] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // red
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // red
    PALe(6, 1),    // purple
},
```

### #475 SPECIES_GALLADE
```c
[SPECIES_GALLADE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 2),    // blue
    PALe(6, 2),    // grey
},
```

### #476 SPECIES_PROBOPASS
```c
[SPECIES_PROBOPASS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // purple
    PALd(6, 1),    // black
    PALe(7, 1),    // light grey
},
```

### #477 SPECIES_DUSKNOIR
```c
[SPECIES_DUSKNOIR] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // orange
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // grey
    PALe(7, 3),    // light grey
},
```

### #478 SPECIES_FROSLASS
```c
[SPECIES_FROSLASS] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // blue
    PALe(6, 1),    // white
},
```

### #479 SPECIES_ROTOM
```c
[SPECIES_ROTOM] = {
    PALa(1, 2),    // cyan
    PALb(3, 2),    // red
    PALc(5, 1),    // orange
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark grey
},
```

### #480 SPECIES_UXIE
```c
[SPECIES_UXIE] = {
    PALa(1, 2),    // brown
    PALb(3, 2),    // yellow
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // red
    PALe(7, 1),    // yellow
},
```

### #481 SPECIES_MESPRIT
```c
[SPECIES_MESPRIT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // purple
    PALd(5, 1),    // grey
    PALe(6, 1),    // red
},
```

### #482 SPECIES_AZELF
```c
[SPECIES_AZELF] = {
    PALa(1, 3),    // grey
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // dark brown
    PALd(6, 2),    // red
    PALe(8, 1),    // white
},
```

### #483 SPECIES_DIALGA
```c
[SPECIES_DIALGA] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 2),    // blue
},
```

### #484 SPECIES_PALKIA
```c
[SPECIES_PALKIA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 5),    // light grey
    PALd(8, 1),    // purple
    PALe(9, 1),    // grey
},
```

### #485 SPECIES_HEATRAN
```c
[SPECIES_HEATRAN] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // brown
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // light grey
},
```

### #486 SPECIES_REGIGIGAS
```c
[SPECIES_REGIGIGAS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // green
    PALc(3, 1),    // orange
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark grey
},
```

### #487 SPECIES_GIRATINA_ALTERED
```c
// Graphics not found
```

### #488 SPECIES_CRESSELIA
```c
[SPECIES_CRESSELIA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light pink
    PALd(4, 1),    // grey
    PALe(5, 1),    // yellow
},
```

### #489 SPECIES_PHIONE
```c
[SPECIES_PHIONE] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // cyan
    PALe(6, 2),    // light cyan
},
```

### #490 SPECIES_MANAPHY
```c
[SPECIES_MANAPHY] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // cyan
    PALc(3, 1),    // blue
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // light cyan
},
```

### #491 SPECIES_DARKRAI
```c
[SPECIES_DARKRAI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #492 SPECIES_SHAYMIN_LAND
```c
// Graphics not found
```

### #493 SPECIES_ARCEUS_NORMAL
```c
// Graphics not found
```

### #494 SPECIES_VICTINI
```c
[SPECIES_VICTINI] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // black
    PALd(5, 1),    // orange
    PALe(6, 1),    // dark brown
},
```

### #495 SPECIES_SNIVY
```c
[SPECIES_SNIVY] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark green
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // yellow
},
```

### #496 SPECIES_SERVINE
```c
[SPECIES_SERVINE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // green
    PALc(3, 1),    // yellow
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark green
},
```

### #497 SPECIES_SERPERIOR
```c
[SPECIES_SERPERIOR] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // blue
    PALd(5, 2),    // green
    PALe(7, 1),    // dark grey
},
```

### #498 SPECIES_TEPIG
```c
[SPECIES_TEPIG] = {
    PALa(1, 4),    // dark grey
    PALb(5, 3),    // brown
    PALc(8, 1),    // brown
    PALd(9, 2),    // orange
    PALe(11, 1),    // white
},
```

### #499 SPECIES_PIGNITE
```c
[SPECIES_PIGNITE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // white
    PALc(4, 1),    // grey
    PALd(5, 2),    // red
    PALe(7, 1),    // dark brown
},
```

### #500 SPECIES_EMBOAR
```c
[SPECIES_EMBOAR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // red
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark brown
},
```


## Pokémon #501-600

### #501 SPECIES_OSHAWOTT
```c
[SPECIES_OSHAWOTT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // blue
},
```

### #502 SPECIES_DEWOTT
```c
[SPECIES_DEWOTT] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 1),    // dark grey
},
```

### #503 SPECIES_SAMUROTT
```c
[SPECIES_SAMUROTT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #504 SPECIES_PATRAT
```c
[SPECIES_PATRAT] = {
    PALa(1, 2),    // brown
    PALb(3, 2),    // brown
    PALc(5, 2),    // dark grey
    PALd(7, 1),    // red
    PALe(8, 1),    // brown
},
```

### #505 SPECIES_WATCHOG
```c
[SPECIES_WATCHOG] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 2),    // dark brown
    PALe(6, 1),    // light grey
},
```

### #506 SPECIES_LILLIPUP
```c
[SPECIES_LILLIPUP] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // black
    PALd(4, 1),    // black
    PALe(5, 1),    // yellow
},
```

### #507 SPECIES_HERDIER
```c
[SPECIES_HERDIER] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // orange
    PALc(3, 2),    // black
    PALd(5, 1),    // yellow
    PALe(6, 1),    // dark grey
},
```

### #508 SPECIES_STOUTLAND
```c
[SPECIES_STOUTLAND] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // yellow
    PALc(4, 4),    // black
    PALd(8, 1),    // orange
    PALe(9, 1),    // white
},
```

### #509 SPECIES_PURRLOIN
```c
[SPECIES_PURRLOIN] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // purple
},
```

### #510 SPECIES_LIEPARD
```c
[SPECIES_LIEPARD] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // purple
    PALe(7, 2),    // orange
},
```

### #511 SPECIES_PANSAGE
```c
[SPECIES_PANSAGE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 2),    // dark green
    PALd(5, 2),    // yellow
    PALe(7, 1),    // cyan
},
```

### #512 SPECIES_SIMISAGE
```c
[SPECIES_SIMISAGE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 2),    // green
    PALd(5, 3),    // yellow
    PALe(8, 1),    // white
},
```

### #513 SPECIES_PANSEAR
```c
[SPECIES_PANSEAR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // black
    PALd(4, 1),    // red
    PALe(5, 1),    // orange
},
```

### #514 SPECIES_SIMISEAR
```c
[SPECIES_SIMISEAR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // red
    PALd(5, 1),    // orange
    PALe(6, 1),    // white
},
```

### #515 SPECIES_PANPOUR
```c
[SPECIES_PANPOUR] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // black
    PALc(3, 3),    // blue
    PALd(6, 1),    // light cyan
    PALe(7, 1),    // white
},
```

### #516 SPECIES_SIMIPOUR
```c
[SPECIES_SIMIPOUR] = {
    PALa(1, 2),    // dark blue
    PALb(3, 1),    // black
    PALc(4, 2),    // blue
    PALd(6, 1),    // light cyan
    PALe(7, 1),    // white
},
```

### #517 SPECIES_MUNNA
```c
[SPECIES_MUNNA] = {
    PALa(1, 2),    // purple
    PALb(3, 2),    // brown
    PALc(5, 1),    // light pink
    PALd(6, 1),    // purple
    PALe(7, 1),    // dark grey
},
```

### #518 SPECIES_MUSHARNA
```c
[SPECIES_MUSHARNA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 1),    // grey
},
```

### #519 SPECIES_PIDOVE
```c
[SPECIES_PIDOVE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // black
    PALd(4, 2),    // light grey
    PALe(6, 1),    // red
},
```

### #520 SPECIES_TRANQUILL
```c
[SPECIES_TRANQUILL] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // red
    PALe(6, 1),    // light grey
},
```

### #521 SPECIES_UNFEZANT
```c
[SPECIES_UNFEZANT] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 2),    // dark brown
    PALd(5, 1),    // green
    PALe(6, 1),    // dark brown
},
```

### #522 SPECIES_BLITZLE
```c
[SPECIES_BLITZLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // cyan
    PALe(5, 2),    // dark grey
},
```

### #523 SPECIES_ZEBSTRIKA
```c
[SPECIES_ZEBSTRIKA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // light grey
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // white
    PALe(7, 1),    // grey
},
```

### #524 SPECIES_ROGGENROLA
```c
[SPECIES_ROGGENROLA] = {
    PALa(1, 2),    // black
    PALb(3, 3),    // brown
    PALc(6, 2),    // blue
    PALd(8, 1),    // dark brown
    PALe(9, 1),    // brown
},
```

### #525 SPECIES_BOLDORE
```c
[SPECIES_BOLDORE] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // blue
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark brown
},
```

### #526 SPECIES_GIGALITH
```c
[SPECIES_GIGALITH] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // brown
    PALe(6, 3),    // black
},
```

### #527 SPECIES_WOOBAT
```c
[SPECIES_WOOBAT] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // dark grey
    PALc(6, 1),    // light cyan
    PALd(7, 2),    // cyan
    PALe(9, 1),    // dark brown
},
```

### #528 SPECIES_SWOOBAT
```c
[SPECIES_SWOOBAT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark grey
    PALc(5, 1),    // blue
    PALd(6, 2),    // grey
    PALe(8, 1),    // light cyan
},
```

### #529 SPECIES_DRILBUR
```c
[SPECIES_DRILBUR] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // white
    PALd(5, 1),    // light grey
    PALe(6, 1),    // light grey
},
```

### #530 SPECIES_EXCADRILL
```c
[SPECIES_EXCADRILL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 3),    // dark grey
},
```

### #531 SPECIES_AUDINO
```c
[SPECIES_AUDINO] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // brown
    PALc(5, 2),    // yellow
    PALd(7, 1),    // blue
    PALe(8, 1),    // dark grey
},
```

### #532 SPECIES_TIMBURR
```c
[SPECIES_TIMBURR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // purple
},
```

### #533 SPECIES_GURDURR
```c
[SPECIES_GURDURR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // red
    PALd(5, 2),    // dark brown
    PALe(7, 2),    // grey
},
```

### #534 SPECIES_CONKELDURR
```c
[SPECIES_CONKELDURR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // brown
},
```

### #535 SPECIES_TYMPOLE
```c
[SPECIES_TYMPOLE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // white
    PALc(5, 1),    // grey
    PALd(6, 1),    // black
    PALe(7, 3),    // blue
},
```

### #536 SPECIES_PALPITOAD
```c
[SPECIES_PALPITOAD] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // black
    PALc(3, 1),    // cyan
    PALd(4, 1),    // cyan
    PALe(5, 2),    // dark grey
},
```

### #537 SPECIES_SEISMITOAD
```c
[SPECIES_SEISMITOAD] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // black
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // green
    PALe(5, 1),    // cyan
},
```

### #538 SPECIES_THROH
```c
[SPECIES_THROH] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 1),    // light grey
},
```

### #539 SPECIES_SAWK
```c
[SPECIES_SAWK] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // blue
    PALd(4, 2),    // dark grey
    PALe(6, 1),    // blue
},
```

### #540 SPECIES_SEWADDLE
```c
[SPECIES_SEWADDLE] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark brown
    PALc(4, 3),    // green
    PALd(7, 1),    // yellow
    PALe(8, 1),    // yellow
},
```

### #541 SPECIES_SWADLOON
```c
[SPECIES_SWADLOON] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // green
    PALd(4, 1),    // green
    PALe(5, 3),    // black
},
```

### #542 SPECIES_LEAVANNY
```c
[SPECIES_LEAVANNY] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // brown
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // green
},
```

### #543 SPECIES_VENIPEDE
```c
[SPECIES_VENIPEDE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // red
    PALd(5, 2),    // purple
    PALe(7, 2),    // black
},
```

### #544 SPECIES_WHIRLIPEDE
```c
[SPECIES_WHIRLIPEDE] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // black
    PALc(4, 1),    // purple
    PALd(5, 2),    // grey
    PALe(7, 3),    // dark grey
},
```

### #545 SPECIES_SCOLIPEDE
```c
[SPECIES_SCOLIPEDE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // red
    PALd(4, 3),    // brown
    PALe(7, 1),    // black
},
```

### #546 SPECIES_COTTONEE
```c
[SPECIES_COTTONEE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 2),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // white
},
```

### #547 SPECIES_WHIMSICOTT
```c
[SPECIES_WHIMSICOTT] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // brown
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 4),    // dark grey
},
```

### #548 SPECIES_PETILIL
```c
[SPECIES_PETILIL] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // green
    PALe(6, 1),    // brown
},
```

### #549 SPECIES_LILLIGANT
```c
[SPECIES_LILLIGANT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 3),    // orange
    PALd(6, 1),    // yellow
    PALe(7, 2),    // black
},
```

### #550 SPECIES_BASCULIN_RED_STRIPED
```c
// Graphics not found
```

### #551 SPECIES_SANDILE
```c
[SPECIES_SANDILE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 2),    // dark brown
    PALe(6, 1),    // orange
},
```

### #552 SPECIES_KROKOROK
```c
[SPECIES_KROKOROK] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #553 SPECIES_KROOKODILE
```c
[SPECIES_KROOKODILE] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // dark grey
    PALc(5, 2),    // orange
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // grey
},
```

### #554 SPECIES_DARUMAKA
```c
[SPECIES_DARUMAKA] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // black
    PALc(4, 2),    // yellow
    PALd(6, 2),    // dark brown
    PALe(8, 1),    // dark brown
},
```

### #555 SPECIES_DARMANITAN_STANDARD
```c
// Graphics not found
```

### #556 SPECIES_MARACTUS
```c
[SPECIES_MARACTUS] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // purple
    PALc(3, 1),    // black
    PALd(4, 1),    // brown
    PALe(5, 1),    // yellow
},
```

### #557 SPECIES_DWEBBLE
```c
[SPECIES_DWEBBLE] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // white
    PALe(7, 1),    // dark grey
},
```

### #558 SPECIES_CRUSTLE
```c
[SPECIES_CRUSTLE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark grey
},
```

### #559 SPECIES_SCRAGGY
```c
[SPECIES_SCRAGGY] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // red
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // orange
},
```

### #560 SPECIES_SCRAFTY
```c
[SPECIES_SCRAFTY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 3),    // red
    PALe(7, 2),    // dark brown
},
```

### #561 SPECIES_SIGILYPH
```c
[SPECIES_SIGILYPH] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark red
    PALe(5, 1),    // yellow
},
```

### #562 SPECIES_YAMASK
```c
[SPECIES_YAMASK] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // dark red
    PALd(5, 1),    // red
    PALe(6, 1),    // black
},
```

### #563 SPECIES_COFAGRIGUS
```c
[SPECIES_COFAGRIGUS] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // blue
    PALc(4, 2),    // black
    PALd(6, 1),    // white
    PALe(7, 1),    // orange
},
```

### #564 SPECIES_TIRTOUGA
```c
[SPECIES_TIRTOUGA] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 2),    // dark grey
    PALd(5, 3),    // blue
    PALe(8, 1),    // light grey
},
```

### #565 SPECIES_CARRACOSTA
```c
[SPECIES_CARRACOSTA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // black
    PALd(4, 2),    // blue
    PALe(6, 2),    // black
},
```

### #566 SPECIES_ARCHEN
```c
[SPECIES_ARCHEN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark blue
    PALc(3, 1),    // red
    PALd(4, 1),    // blue
    PALe(5, 1),    // brown
},
```

### #567 SPECIES_ARCHEOPS
```c
[SPECIES_ARCHEOPS] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark blue
    PALc(4, 1),    // blue
    PALd(5, 1),    // white
    PALe(6, 1),    // grey
},
```

### #568 SPECIES_TRUBBISH
```c
[SPECIES_TRUBBISH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // black
    PALe(5, 1),    // cyan
},
```

### #569 SPECIES_GARBODOR
```c
[SPECIES_GARBODOR] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // black
    PALc(4, 1),    // grey
    PALd(5, 2),    // red
    PALe(7, 1),    // blue
},
```

### #570 SPECIES_ZORUA
```c
[SPECIES_ZORUA] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // grey
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // cyan
},
```

### #571 SPECIES_ZOROARK
```c
[SPECIES_ZOROARK] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // dark brown
    PALc(6, 1),    // red
    PALd(7, 3),    // grey
    PALe(10, 1),    // light grey
},
```

### #572 SPECIES_MINCCINO
```c
[SPECIES_MINCCINO] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 3),    // light grey
    PALd(6, 1),    // dark grey
    PALe(7, 5),    // red
},
```

### #573 SPECIES_CINCCINO
```c
[SPECIES_CINCCINO] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // grey
},
```

### #574 SPECIES_GOTHITA
```c
[SPECIES_GOTHITA] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // white
    PALe(7, 1),    // purple
},
```

### #575 SPECIES_GOTHORITA
```c
[SPECIES_GOTHORITA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // white
    PALe(5, 2),    // dark grey
},
```

### #576 SPECIES_GOTHITELLE
```c
[SPECIES_GOTHITELLE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #577 SPECIES_SOLOSIS
```c
[SPECIES_SOLOSIS] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // cyan
    PALc(4, 1),    // white
    PALd(5, 1),    // grey
    PALe(6, 1),    // yellow
},
```

### #578 SPECIES_DUOSION
```c
[SPECIES_DUOSION] = {
    PALa(1, 4),    // green
    PALb(5, 2),    // yellow
    PALc(7, 1),    // dark grey
    PALd(8, 1),    // cyan
    PALe(9, 1),    // white
},
```

### #579 SPECIES_REUNICLUS
```c
[SPECIES_REUNICLUS] = {
    PALa(1, 2),    // green
    PALb(3, 2),    // green
    PALc(5, 1),    // green
    PALd(6, 1),    // white
    PALe(7, 1),    // dark grey
},
```

### #580 SPECIES_DUCKLETT
```c
[SPECIES_DUCKLETT] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // cyan
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #581 SPECIES_SWANNA
```c
[SPECIES_SWANNA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 1),    // black
    PALe(5, 1),    // cyan
},
```

### #582 SPECIES_VANILLITE
```c
[SPECIES_VANILLITE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // grey
    PALc(3, 1),    // white
    PALd(4, 1),    // black
    PALe(5, 3),    // cyan
},
```

### #583 SPECIES_VANILLISH
```c
[SPECIES_VANILLISH] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // black
    PALe(5, 4),    // cyan
},
```

### #584 SPECIES_VANILLUXE
```c
[SPECIES_VANILLUXE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // cyan
    PALd(4, 1),    // grey
    PALe(5, 1),    // black
},
```

### #585 SPECIES_DEERLING_SPRING
```c
// Graphics not found
```

### #586 SPECIES_SAWSBUCK_SPRING
```c
// Graphics not found
```

### #587 SPECIES_EMOLGA
```c
[SPECIES_EMOLGA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark grey
    PALc(5, 1),    // orange
    PALd(6, 1),    // light grey
    PALe(7, 1),    // brown
},
```

### #588 SPECIES_KARRABLAST
```c
[SPECIES_KARRABLAST] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // blue
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // cyan
    PALe(7, 2),    // dark grey
},
```

### #589 SPECIES_ESCAVALIER
```c
[SPECIES_ESCAVALIER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // grey
    PALe(7, 2),    // dark grey
},
```

### #590 SPECIES_FOONGUS
```c
[SPECIES_FOONGUS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 3),    // brown
    PALe(7, 1),    // grey
},
```

### #591 SPECIES_AMOONGUSS
```c
[SPECIES_AMOONGUSS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // black
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark brown
},
```

### #592 SPECIES_FRILLISH
```c
[SPECIES_FRILLISH] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // cyan
    PALd(5, 1),    // cyan
    PALe(6, 1),    // cyan
},
```

### #593 SPECIES_JELLICENT
```c
[SPECIES_JELLICENT] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 3),    // blue
},
```

### #594 SPECIES_ALOMOMOLA
```c
[SPECIES_ALOMOMOLA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // light pink
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark brown
},
```

### #595 SPECIES_JOLTIK
```c
[SPECIES_JOLTIK] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // black
},
```

### #596 SPECIES_GALVANTULA
```c
[SPECIES_GALVANTULA] = {
    PALa(1, 2),    // dark blue
    PALb(3, 1),    // blue
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // orange
    PALe(7, 1),    // yellow
},
```

### #597 SPECIES_FERROSEED
```c
[SPECIES_FERROSEED] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // green
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #598 SPECIES_FERROTHORN
```c
[SPECIES_FERROTHORN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // black
},
```

### #599 SPECIES_KLINK
```c
[SPECIES_KLINK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #600 SPECIES_KLANG
```c
[SPECIES_KLANG] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // light grey
    PALe(7, 1),    // white
},
```


## Pokémon #601-700

### #601 SPECIES_KLINKLANG
```c
[SPECIES_KLINKLANG] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // light grey
    PALe(7, 1),    // white
},
```

### #602 SPECIES_TYNAMO
```c
[SPECIES_TYNAMO] = {
    PALa(1, 2),    // light grey
    PALb(3, 1),    // light grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #603 SPECIES_EELEKTRIK
```c
[SPECIES_EELEKTRIK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // brown
    PALc(3, 1),    // yellow
    PALd(4, 3),    // dark grey
    PALe(7, 1),    // dark brown
},
```

### #604 SPECIES_EELEKTROSS
```c
[SPECIES_EELEKTROSS] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // blue
    PALc(4, 1),    // cyan
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #605 SPECIES_ELGYEM
```c
[SPECIES_ELGYEM] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // cyan
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // dark grey
    PALe(8, 1),    // black
},
```

### #606 SPECIES_BEHEEYEM
```c
[SPECIES_BEHEEYEM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // orange
    PALc(3, 2),    // dark brown
    PALd(5, 4),    // dark grey
    PALe(9, 1),    // grey
},
```

### #607 SPECIES_LITWICK
```c
[SPECIES_LITWICK] = {
    PALa(1, 1),    // dark blue
    PALb(2, 3),    // blue
    PALc(5, 1),    // black
    PALd(6, 1),    // grey
    PALe(7, 1),    // white
},
```

### #608 SPECIES_LAMPENT
```c
[SPECIES_LAMPENT] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // blue
    PALe(6, 2),    // grey
},
```

### #609 SPECIES_CHANDELURE
```c
[SPECIES_CHANDELURE] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // purple
    PALc(4, 3),    // dark grey
    PALd(7, 2),    // light grey
    PALe(9, 1),    // grey
},
```

### #610 SPECIES_AXEW
```c
[SPECIES_AXEW] = {
    PALa(1, 5),    // dark grey
    PALb(6, 2),    // green
    PALc(8, 1),    // dark red
    PALd(9, 1),    // white
    PALe(10, 1),    // cyan
},
```

### #611 SPECIES_FRAXURE
```c
[SPECIES_FRAXURE] = {
    PALa(1, 2),    // black
    PALb(3, 4),    // grey
    PALc(7, 1),    // black
    PALd(8, 1),    // red
    PALe(9, 1),    // dark grey
},
```

### #612 SPECIES_HAXORUS
```c
[SPECIES_HAXORUS] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // dark red
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark red
    PALe(6, 1),    // black
},
```

### #613 SPECIES_CUBCHOO
```c
[SPECIES_CUBCHOO] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // blue
    PALc(3, 1),    // light cyan
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // black
},
```

### #614 SPECIES_BEARTIC
```c
[SPECIES_BEARTIC] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #615 SPECIES_CRYOGONAL
```c
[SPECIES_CRYOGONAL] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // white
    PALe(6, 1),    // black
},
```

### #616 SPECIES_SHELMET
```c
[SPECIES_SHELMET] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // black
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #617 SPECIES_ACCELGOR
```c
[SPECIES_ACCELGOR] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // green
},
```

### #618 SPECIES_STUNFISK
```c
[SPECIES_STUNFISK] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 3),    // dark grey
    PALe(7, 2),    // brown
},
```

### #619 SPECIES_MIENFOO
```c
[SPECIES_MIENFOO] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // grey
    PALe(6, 1),    // grey
},
```

### #620 SPECIES_MIENSHAO
```c
[SPECIES_MIENSHAO] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // black
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #621 SPECIES_DRUDDIGON
```c
[SPECIES_DRUDDIGON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // blue
    PALc(5, 3),    // black
    PALd(8, 1),    // white
    PALe(9, 1),    // yellow
},
```

### #622 SPECIES_GOLETT
```c
[SPECIES_GOLETT] = {
    PALa(1, 2),    // dark green
    PALb(3, 1),    // cyan
    PALc(4, 3),    // green
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // blue
},
```

### #623 SPECIES_GOLURK
```c
[SPECIES_GOLURK] = {
    PALa(1, 3),    // dark blue
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // blue
    PALd(6, 2),    // cyan
    PALe(8, 1),    // yellow
},
```

### #624 SPECIES_PAWNIARD
```c
[SPECIES_PAWNIARD] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 1),    // red
    PALd(4, 1),    // white
    PALe(5, 1),    // dark brown
},
```

### #625 SPECIES_BISHARP
```c
[SPECIES_BISHARP] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // brown
    PALc(4, 1),    // yellow
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #626 SPECIES_BOUFFALANT
```c
[SPECIES_BOUFFALANT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // black
    PALc(4, 1),    // black
    PALd(5, 2),    // brown
    PALe(7, 1),    // grey
},
```

### #627 SPECIES_RUFFLET
```c
[SPECIES_RUFFLET] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // grey
    PALd(4, 1),    // white
    PALe(5, 1),    // grey
},
```

### #628 SPECIES_BRAVIARY
```c
[SPECIES_BRAVIARY] = {
    PALa(1, 3),    // black
    PALb(4, 2),    // dark grey
    PALc(6, 1),    // grey
    PALd(7, 1),    // grey
    PALe(8, 2),    // light grey
},
```

### #629 SPECIES_VULLABY
```c
[SPECIES_VULLABY] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // purple
    PALd(6, 1),    // grey
    PALe(7, 1),    // white
},
```

### #630 SPECIES_MANDIBUZZ
```c
[SPECIES_MANDIBUZZ] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark brown
    PALc(4, 1),    // white
    PALd(5, 1),    // grey
    PALe(6, 1),    // brown
},
```

### #631 SPECIES_HEATMOR
```c
[SPECIES_HEATMOR] = {
    PALa(1, 3),    // brown
    PALb(4, 1),    // grey
    PALc(5, 3),    // red
    PALd(8, 1),    // white
    PALe(9, 1),    // black
},
```

### #632 SPECIES_DURANT
```c
[SPECIES_DURANT] = {
    PALa(1, 3),    // grey
    PALb(4, 3),    // dark grey
    PALc(7, 1),    // grey
    PALd(8, 1),    // dark brown
    PALe(9, 1),    // red
},
```

### #633 SPECIES_DEINO
```c
[SPECIES_DEINO] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // dark grey
    PALc(6, 1),    // blue
    PALd(7, 1),    // blue
    PALe(8, 1),    // brown
},
```

### #634 SPECIES_ZWEILOUS
```c
[SPECIES_ZWEILOUS] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // blue
    PALd(6, 1),    // dark blue
    PALe(7, 1),    // blue
},
```

### #635 SPECIES_HYDREIGON
```c
[SPECIES_HYDREIGON] = {
    PALa(1, 3),    // dark grey
    PALb(4, 3),    // grey
    PALc(7, 1),    // dark brown
    PALd(8, 1),    // dark blue
    PALe(9, 4),    // blue
},
```

### #636 SPECIES_LARVESTA
```c
[SPECIES_LARVESTA] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // grey
    PALd(6, 1),    // white
    PALe(7, 1),    // light grey
},
```

### #637 SPECIES_VOLCARONA
```c
[SPECIES_VOLCARONA] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // dark brown
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // orange
    PALe(7, 1),    // grey
},
```

### #638 SPECIES_COBALION
```c
[SPECIES_COBALION] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // black
    PALc(4, 1),    // yellow
    PALd(5, 3),    // dark grey
    PALe(8, 1),    // cyan
},
```

### #639 SPECIES_TERRAKION
```c
[SPECIES_TERRAKION] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #640 SPECIES_VIRIZION
```c
[SPECIES_VIRIZION] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // green
    PALc(4, 1),    // green
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark grey
},
```

### #641 SPECIES_TORNADUS_INCARNATE
```c
// Graphics not found
```

### #642 SPECIES_THUNDURUS_INCARNATE
```c
// Graphics not found
```

### #643 SPECIES_RESHIRAM
```c
[SPECIES_RESHIRAM] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 1),    // black
    PALd(4, 1),    // cyan
    PALe(5, 2),    // white
},
```

### #644 SPECIES_ZEKROM
```c
[SPECIES_ZEKROM] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // cyan
},
```

### #645 SPECIES_LANDORUS_INCARNATE
```c
// Graphics not found
```

### #646 SPECIES_KYUREM
```c
[SPECIES_KYUREM] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // cyan
    PALd(4, 1),    // white
    PALe(5, 1),    // grey
},
```

### #647 SPECIES_KELDEO_ORDINARY
```c
// Graphics not found
```

### #648 SPECIES_MELOETTA_ARIA
```c
// Graphics not found
```

### #649 SPECIES_GENESECT
```c
[SPECIES_GENESECT] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // light purple
    PALd(6, 1),    // dark brown
    PALe(7, 2),    // orange
},
```

### #650 SPECIES_CHESPIN
```c
[SPECIES_CHESPIN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // green
    PALd(5, 1),    // yellow
    PALe(6, 1),    // black
},
```

### #651 SPECIES_QUILLADIN
```c
[SPECIES_QUILLADIN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 2),    // dark grey
    PALd(5, 2),    // dark brown
    PALe(7, 1),    // green
},
```

### #652 SPECIES_CHESNAUGHT
```c
[SPECIES_CHESNAUGHT] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // grey
    PALe(5, 1),    // red
},
```

### #653 SPECIES_FENNEKIN
```c
[SPECIES_FENNEKIN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 2),    // yellow
    PALd(5, 1),    // dark brown
    PALe(6, 2),    // red
},
```

### #654 SPECIES_BRAIXEN
```c
[SPECIES_BRAIXEN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark brown
},
```

### #655 SPECIES_DELPHOX
```c
[SPECIES_DELPHOX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 1),    // red
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // brown
},
```

### #656 SPECIES_FROAKIE
```c
[SPECIES_FROAKIE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // black
    PALd(4, 1),    // blue
    PALe(5, 1),    // yellow
},
```

### #657 SPECIES_FROGADIER
```c
[SPECIES_FROGADIER] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // dark blue
    PALc(5, 1),    // cyan
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // blue
},
```

### #658 SPECIES_GRENINJA
```c
[SPECIES_GRENINJA] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // white
    PALe(6, 1),    // blue
},
```

### #659 SPECIES_BUNNELBY
```c
[SPECIES_BUNNELBY] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // brown
    PALc(4, 1),    // black
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #660 SPECIES_DIGGERSBY
```c
[SPECIES_DIGGERSBY] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // dark brown
    PALe(7, 1),    // brown
},
```

### #661 SPECIES_FLETCHLING
```c
[SPECIES_FLETCHLING] = {
    PALa(1, 3),    // black
    PALb(4, 2),    // dark brown
    PALc(6, 1),    // grey
    PALd(7, 1),    // red
    PALe(8, 1),    // grey
},
```

### #662 SPECIES_FLETCHINDER
```c
[SPECIES_FLETCHINDER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // yellow
},
```

### #663 SPECIES_TALONFLAME
```c
[SPECIES_TALONFLAME] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // black
    PALc(5, 1),    // black
    PALd(6, 2),    // red
    PALe(8, 1),    // orange
},
```

### #664 SPECIES_SCATTERBUG_ICY_SNOW
```c
// Graphics not found
```

### #665 SPECIES_SPEWPA_ICY_SNOW
```c
// Graphics not found
```

### #666 SPECIES_VIVILLON_ICY_SNOW
```c
// Graphics not found
```

### #667 SPECIES_LITLEO
```c
[SPECIES_LITLEO] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // red
    PALd(4, 1),    // orange
    PALe(5, 1),    // grey
},
```

### #668 SPECIES_PYROAR
```c
[SPECIES_PYROAR] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // yellow
    PALd(4, 2),    // red
    PALe(6, 2),    // dark grey
},
```

### #669 SPECIES_FLABEBE_RED
```c
// Graphics not found
```

### #670 SPECIES_FLOETTE_RED
```c
// Graphics not found
```

### #671 SPECIES_FLORGES_RED
```c
// Graphics not found
```

### #672 SPECIES_SKIDDO
```c
[SPECIES_SKIDDO] = {
    PALa(1, 2),    // dark grey
    PALb(3, 5),    // black
    PALc(8, 1),    // black
    PALd(9, 2),    // green
    PALe(11, 1),    // light grey
},
```

### #673 SPECIES_GOGOAT
```c
[SPECIES_GOGOAT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // dark grey
    PALc(6, 1),    // green
    PALd(7, 1),    // dark brown
    PALe(8, 1),    // dark green
},
```

### #674 SPECIES_PANCHAM
```c
[SPECIES_PANCHAM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // light grey
    PALc(3, 1),    // light grey
    PALd(4, 3),    // dark grey
    PALe(7, 1),    // black
},
```

### #675 SPECIES_PANGORO
```c
[SPECIES_PANGORO] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // black
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 3),    // dark grey
},
```

### #676 SPECIES_FURFROU_NATURAL
```c
// Graphics not found
```

### #677 SPECIES_ESPURR
```c
[SPECIES_ESPURR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 1),    // black
    PALd(4, 1),    // grey
    PALe(5, 1),    // cyan
},
```

### #678 SPECIES_MEOWSTIC_M
```c
// Graphics not found
```

### #679 SPECIES_HONEDGE
```c
[SPECIES_HONEDGE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // yellow
},
```

### #680 SPECIES_DOUBLADE
```c
[SPECIES_DOUBLADE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark brown
},
```

### #681 SPECIES_AEGISLASH_SHIELD
```c
// Graphics not found
```

### #682 SPECIES_SPRITZEE
```c
[SPECIES_SPRITZEE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // black
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #683 SPECIES_AROMATISSE
```c
[SPECIES_AROMATISSE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // black
    PALd(4, 1),    // yellow
    PALe(5, 1),    // black
},
```

### #684 SPECIES_SWIRLIX
```c
[SPECIES_SWIRLIX] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 3),    // light pink
    PALe(7, 1),    // dark grey
},
```

### #685 SPECIES_SLURPUFF
```c
[SPECIES_SLURPUFF] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // light pink
},
```

### #686 SPECIES_INKAY
```c
[SPECIES_INKAY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // white
    PALc(3, 1),    // black
    PALd(4, 1),    // light grey
    PALe(5, 1),    // grey
},
```

### #687 SPECIES_MALAMAR
```c
[SPECIES_MALAMAR] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 1),    // blue
    PALd(4, 1),    // grey
    PALe(5, 1),    // cyan
},
```

### #688 SPECIES_BINACLE
```c
[SPECIES_BINACLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // black
},
```

### #689 SPECIES_BARBARACLE
```c
[SPECIES_BARBARACLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // black
},
```

### #690 SPECIES_SKRELP
```c
[SPECIES_SKRELP] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // brown
    PALc(4, 1),    // cyan
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #691 SPECIES_DRAGALGE
```c
[SPECIES_DRAGALGE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // red
},
```

### #692 SPECIES_CLAUNCHER
```c
[SPECIES_CLAUNCHER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // black
    PALd(4, 1),    // black
    PALe(5, 1),    // cyan
},
```

### #693 SPECIES_CLAWITZER
```c
[SPECIES_CLAWITZER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 1),    // orange
    PALd(4, 2),    // black
    PALe(6, 1),    // blue
},
```

### #694 SPECIES_HELIOPTILE
```c
[SPECIES_HELIOPTILE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // yellow
},
```

### #695 SPECIES_HELIOLISK
```c
[SPECIES_HELIOLISK] = {
    PALa(1, 1),    // yellow
    PALb(2, 1),    // grey
    PALc(3, 3),    // dark brown
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark brown
},
```

### #696 SPECIES_TYRUNT
```c
[SPECIES_TYRUNT] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 1),    // orange
    PALd(4, 1),    // dark grey
    PALe(5, 3),    // brown
},
```

### #697 SPECIES_TYRANTRUM
```c
[SPECIES_TYRANTRUM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // black
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #698 SPECIES_AMAURA
```c
[SPECIES_AMAURA] = {
    PALa(1, 1),    // light cyan
    PALb(2, 1),    // cyan
    PALc(3, 1),    // yellow
    PALd(4, 1),    // black
    PALe(5, 1),    // light pink
},
```

### #699 SPECIES_AURORUS
```c
[SPECIES_AURORUS] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // light pink
    PALe(5, 1),    // black
},
```

### #700 SPECIES_SYLVEON
```c
[SPECIES_SYLVEON] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // purple
    PALe(5, 1),    // cyan
},
```


## Pokémon #701-800

### #701 SPECIES_HAWLUCHA
```c
[SPECIES_HAWLUCHA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // cyan
},
```

### #702 SPECIES_DEDENNE
```c
[SPECIES_DEDENNE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // white
    PALe(6, 2),    // dark brown
},
```

### #703 SPECIES_CARBINK
```c
[SPECIES_CARBINK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // cyan
    PALd(5, 1),    // white
    PALe(6, 1),    // blue
},
```

### #704 SPECIES_GOOMY
```c
[SPECIES_GOOMY] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // grey
    PALd(5, 2),    // dark grey
    PALe(7, 1),    // green
},
```

### #705 SPECIES_SLIGGOO
```c
[SPECIES_SLIGGOO] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #706 SPECIES_GOODRA
```c
[SPECIES_GOODRA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // purple
    PALd(5, 1),    // grey
    PALe(6, 1),    // green
},
```

### #707 SPECIES_KLEFKI
```c
[SPECIES_KLEFKI] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // cyan
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // white
    PALe(7, 1),    // purple
},
```

### #708 SPECIES_PHANTUMP
```c
[SPECIES_PHANTUMP] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // dark grey
    PALc(6, 1),    // brown
    PALd(7, 3),    // dark green
    PALe(10, 1),    // dark brown
},
```

### #709 SPECIES_TREVENANT
```c
[SPECIES_TREVENANT] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // black
    PALc(5, 5),    // dark brown
    PALd(10, 1),    // purple
    PALe(11, 1),    // grey
},
```

### #710 SPECIES_PUMPKABOO_AVERAGE
```c
// Graphics not found
```

### #711 SPECIES_GOURGEIST_AVERAGE
```c
// Graphics not found
```

### #712 SPECIES_BERGMITE
```c
[SPECIES_BERGMITE] = {
    PALa(1, 4),    // white
    PALb(5, 2),    // white
    PALc(7, 1),    // grey
    PALd(8, 1),    // dark grey
    PALe(9, 2),    // purple
},
```

### #713 SPECIES_AVALUGG
```c
[SPECIES_AVALUGG] = {
    PALa(1, 4),    // light grey
    PALb(5, 1),    // dark grey
    PALc(6, 2),    // purple
    PALd(8, 2),    // yellow
    PALe(10, 1),    // white
},
```

### #714 SPECIES_NOIBAT
```c
[SPECIES_NOIBAT] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // purple
    PALc(3, 1),    // black
    PALd(4, 1),    // blue
    PALe(5, 1),    // purple
},
```

### #715 SPECIES_NOIVERN
```c
[SPECIES_NOIVERN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // dark grey
    PALc(6, 2),    // black
    PALd(8, 1),    // blue
    PALe(9, 2),    // grey
},
```

### #716 SPECIES_XERNEAS_NEUTRAL
```c
// Graphics not found
```

### #717 SPECIES_YVELTAL
```c
[SPECIES_YVELTAL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // light grey
},
```

### #718 SPECIES_ZYGARDE_50
```c
// Graphics not found
```

### #719 SPECIES_DIANCIE
```c
[SPECIES_DIANCIE] = {
    PALa(1, 4),    // white
    PALb(5, 1),    // grey
    PALc(6, 1),    // purple
    PALd(7, 1),    // blue
    PALe(8, 1),    // grey
},
```

### #720 SPECIES_HOOPA_CONFINED
```c
// Graphics not found
```

### #721 SPECIES_VOLCANION
```c
[SPECIES_VOLCANION] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // yellow
    PALc(4, 2),    // brown
    PALd(6, 1),    // brown
    PALe(7, 1),    // blue
},
```

### #722 SPECIES_ROWLET
```c
[SPECIES_ROWLET] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // grey
},
```

### #723 SPECIES_DARTRIX
```c
[SPECIES_DARTRIX] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // green
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // green
    PALe(5, 1),    // brown
},
```

### #724 SPECIES_DECIDUEYE
```c
[SPECIES_DECIDUEYE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // grey
},
```

### #725 SPECIES_LITTEN
```c
[SPECIES_LITTEN] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #726 SPECIES_TORRACAT
```c
[SPECIES_TORRACAT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // red
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark grey
},
```

### #727 SPECIES_INCINEROAR
```c
[SPECIES_INCINEROAR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // red
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark red
},
```

### #728 SPECIES_POPPLIO
```c
[SPECIES_POPPLIO] = {
    PALa(1, 1),    // dark blue
    PALb(2, 2),    // blue
    PALc(4, 1),    // grey
    PALd(5, 1),    // purple
    PALe(6, 1),    // cyan
},
```

### #729 SPECIES_BRIONNE
```c
[SPECIES_BRIONNE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 2),    // light grey
    PALe(6, 1),    // cyan
},
```

### #730 SPECIES_PRIMARINA
```c
[SPECIES_PRIMARINA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // grey
    PALc(3, 2),    // cyan
    PALd(5, 2),    // cyan
    PALe(7, 1),    // dark grey
},
```

### #731 SPECIES_PIKIPEK
```c
[SPECIES_PIKIPEK] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // grey
    PALe(6, 1),    // white
},
```

### #732 SPECIES_TRUMBEAK
```c
[SPECIES_TRUMBEAK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 2),    // grey
},
```

### #733 SPECIES_TOUCANNON
```c
[SPECIES_TOUCANNON] = {
    PALa(1, 4),    // dark grey
    PALb(5, 2),    // dark grey
    PALc(7, 1),    // red
    PALd(8, 1),    // blue
    PALe(9, 1),    // orange
},
```

### #734 SPECIES_YUNGOOS
```c
[SPECIES_YUNGOOS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 3),    // orange
    PALe(7, 1),    // purple
},
```

### #735 SPECIES_GUMSHOOS
```c
[SPECIES_GUMSHOOS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark grey
},
```

### #736 SPECIES_GRUBBIN
```c
[SPECIES_GRUBBIN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // light grey
    PALd(4, 2),    // red
    PALe(6, 1),    // dark grey
},
```

### #737 SPECIES_CHARJABUG
```c
[SPECIES_CHARJABUG] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // dark grey
    PALc(6, 1),    // white
    PALd(7, 1),    // blue
    PALe(8, 1),    // light grey
},
```

### #738 SPECIES_VIKAVOLT
```c
[SPECIES_VIKAVOLT] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // dark blue
    PALc(5, 1),    // light grey
    PALd(6, 1),    // white
    PALe(7, 1),    // light grey
},
```

### #739 SPECIES_CRABRAWLER
```c
[SPECIES_CRABRAWLER] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark blue
    PALd(4, 2),    // cyan
    PALe(6, 1),    // dark grey
},
```

### #740 SPECIES_CRABOMINABLE
```c
[SPECIES_CRABOMINABLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 3),    // blue
},
```

### #741 SPECIES_ORICORIO_BAILE
```c
// Graphics not found
```

### #742 SPECIES_CUTIEFLY
```c
[SPECIES_CUTIEFLY] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // white
    PALc(3, 2),    // purple
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #743 SPECIES_RIBOMBEE
```c
[SPECIES_RIBOMBEE] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 2),    // dark grey
    PALe(6, 1),    // yellow
},
```

### #744 SPECIES_ROCKRUFF
```c
[SPECIES_ROCKRUFF] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 1),    // purple
},
```

### #745 SPECIES_LYCANROC_MIDDAY
```c
// Graphics not found
```

### #746 SPECIES_WISHIWASHI_SOLO
```c
// Graphics not found
```

### #747 SPECIES_MAREANIE
```c
[SPECIES_MAREANIE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 1),    // purple
    PALe(5, 1),    // orange
},
```

### #748 SPECIES_TOXAPEX
```c
[SPECIES_TOXAPEX] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // orange
    PALd(5, 2),    // cyan
    PALe(7, 3),    // grey
},
```

### #749 SPECIES_MUDBRAY
```c
[SPECIES_MUDBRAY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark grey
},
```

### #750 SPECIES_MUDSDALE
```c
[SPECIES_MUDSDALE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // grey
    PALd(4, 1),    // orange
    PALe(5, 2),    // brown
},
```

### #751 SPECIES_DEWPIDER
```c
[SPECIES_DEWPIDER] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // light grey
    PALc(4, 1),    // green
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // yellow
},
```

### #752 SPECIES_ARAQUANID
```c
[SPECIES_ARAQUANID] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light cyan
    PALc(4, 1),    // white
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #753 SPECIES_FOMANTIS
```c
[SPECIES_FOMANTIS] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // black
    PALe(6, 2),    // cyan
},
```

### #754 SPECIES_LURANTIS
```c
[SPECIES_LURANTIS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // black
    PALd(4, 1),    // light pink
    PALe(5, 1),    // cyan
},
```

### #755 SPECIES_MORELULL
```c
[SPECIES_MORELULL] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // grey
    PALc(3, 1),    // light pink
    PALd(4, 1),    // dark grey
    PALe(5, 3),    // purple
},
```

### #756 SPECIES_SHIINOTIC
```c
[SPECIES_SHIINOTIC] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // purple
},
```

### #757 SPECIES_SALANDIT
```c
[SPECIES_SALANDIT] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // red
    PALc(5, 1),    // grey
    PALd(6, 3),    // dark grey
    PALe(9, 2),    // purple
},
```

### #758 SPECIES_SALAZZLE
```c
[SPECIES_SALAZZLE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // purple
},
```

### #759 SPECIES_STUFFUL
```c
[SPECIES_STUFFUL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // brown
},
```

### #760 SPECIES_BEWEAR
```c
[SPECIES_BEWEAR] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // pink
    PALc(3, 1),    // grey
    PALd(4, 1),    // white
    PALe(5, 1),    // dark grey
},
```

### #761 SPECIES_BOUNSWEET
```c
[SPECIES_BOUNSWEET] = {
    PALa(1, 3),    // black
    PALb(4, 1),    // dark grey
    PALc(5, 3),    // purple
    PALd(8, 1),    // purple
    PALe(9, 1),    // white
},
```

### #762 SPECIES_STEENEE
```c
[SPECIES_STEENEE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // yellow
    PALe(6, 1),    // white
},
```

### #763 SPECIES_TSAREENA
```c
[SPECIES_TSAREENA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // purple
    PALd(4, 1),    // yellow
    PALe(5, 1),    // red
},
```

### #764 SPECIES_COMFEY
```c
[SPECIES_COMFEY] = {
    PALa(1, 1),    // dark green
    PALb(2, 2),    // yellow
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 1),    // yellow
},
```

### #765 SPECIES_ORANGURU
```c
[SPECIES_ORANGURU] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // green
    PALd(4, 1),    // white
    PALe(5, 1),    // light grey
},
```

### #766 SPECIES_PASSIMIAN
```c
[SPECIES_PASSIMIAN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // light grey
    PALd(6, 3),    // dark grey
    PALe(9, 1),    // white
},
```

### #767 SPECIES_WIMPOD
```c
[SPECIES_WIMPOD] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 4),    // grey
    PALe(8, 1),    // light grey
},
```

### #768 SPECIES_GOLISOPOD
```c
[SPECIES_GOLISOPOD] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 2),    // green
    PALe(6, 1),    // blue
},
```

### #769 SPECIES_SANDYGAST
```c
[SPECIES_SANDYGAST] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark brown
},
```

### #770 SPECIES_PALOSSAND
```c
[SPECIES_PALOSSAND] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // red
    PALd(4, 1),    // red
    PALe(5, 1),    // dark brown
},
```

### #771 SPECIES_PYUKUMUKU
```c
[SPECIES_PYUKUMUKU] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // dark grey
},
```

### #772 SPECIES_TYPE_NULL
```c
[SPECIES_TYPE_NULL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #773 SPECIES_SILVALLY_NORMAL
```c
// Graphics not found
```

### #774 SPECIES_MINIOR_METEOR_RED
```c
// Graphics not found
```

### #775 SPECIES_KOMALA
```c
[SPECIES_KOMALA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 1),    // yellow
},
```

### #776 SPECIES_TURTONATOR
```c
[SPECIES_TURTONATOR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark brown
    PALc(5, 2),    // red
    PALd(7, 1),    // yellow
    PALe(8, 1),    // orange
},
```

### #777 SPECIES_TOGEDEMARU
```c
[SPECIES_TOGEDEMARU] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // orange
},
```

### #778 SPECIES_MIMIKYU_DISGUISED
```c
// Graphics not found
```

### #779 SPECIES_BRUXISH
```c
[SPECIES_BRUXISH] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // purple
    PALd(6, 1),    // brown
    PALe(7, 1),    // purple
},
```

### #780 SPECIES_DRAMPA
```c
[SPECIES_DRAMPA] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // grey
    PALe(5, 1),    // blue
},
```

### #781 SPECIES_DHELMISE
```c
[SPECIES_DHELMISE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // black
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // cyan
},
```

### #782 SPECIES_JANGMO_O
```c
[SPECIES_JANGMO_O] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // white
    PALe(5, 1),    // grey
},
```

### #783 SPECIES_HAKAMO_O
```c
[SPECIES_HAKAMO_O] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 2),    // grey
},
```

### #784 SPECIES_KOMMO_O
```c
[SPECIES_KOMMO_O] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // orange
    PALe(5, 1),    // red
},
```

### #785 SPECIES_TAPU_KOKO
```c
[SPECIES_TAPU_KOKO] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark brown
},
```

### #786 SPECIES_TAPU_LELE
```c
[SPECIES_TAPU_LELE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // purple
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // purple
    PALe(6, 1),    // white
},
```

### #787 SPECIES_TAPU_BULU
```c
[SPECIES_TAPU_BULU] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // brown
    PALd(5, 1),    // yellow
    PALe(6, 4),    // dark grey
},
```

### #788 SPECIES_TAPU_FINI
```c
[SPECIES_TAPU_FINI] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 3),    // dark grey
    PALd(6, 1),    // blue
    PALe(7, 1),    // cyan
},
```

### #789 SPECIES_COSMOG
```c
[SPECIES_COSMOG] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // cyan
    PALd(4, 1),    // white
    PALe(5, 1),    // dark brown
},
```

### #790 SPECIES_COSMOEM
```c
[SPECIES_COSMOEM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // orange
},
```

### #791 SPECIES_SOLGALEO
```c
[SPECIES_SOLGALEO] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // yellow
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // orange
    PALe(7, 1),    // grey
},
```

### #792 SPECIES_LUNALA
```c
[SPECIES_LUNALA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // blue
},
```

### #793 SPECIES_NIHILEGO
```c
[SPECIES_NIHILEGO] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark blue
    PALe(6, 2),    // blue
},
```

### #794 SPECIES_BUZZWOLE
```c
[SPECIES_BUZZWOLE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // red
    PALc(4, 1),    // grey
    PALd(5, 1),    // black
    PALe(6, 1),    // dark red
},
```

### #795 SPECIES_PHEROMOSA
```c
[SPECIES_PHEROMOSA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // orange
},
```

### #796 SPECIES_XURKITREE
```c
[SPECIES_XURKITREE] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // white
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // dark grey
},
```

### #797 SPECIES_CELESTEELA
```c
[SPECIES_CELESTEELA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // green
    PALc(3, 1),    // cyan
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #798 SPECIES_KARTANA
```c
[SPECIES_KARTANA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // brown
},
```

### #799 SPECIES_GUZZLORD
```c
[SPECIES_GUZZLORD] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // yellow
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #800 SPECIES_NECROZMA
```c
[SPECIES_NECROZMA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 2),    // dark grey
    PALd(6, 1),    // cyan
    PALe(7, 1),    // red
},
```


## Pokémon #801-900

### #801 SPECIES_MAGEARNA
```c
[SPECIES_MAGEARNA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // orange
    PALd(4, 1),    // light grey
    PALe(5, 1),    // purple
},
```

### #802 SPECIES_MARSHADOW
```c
[SPECIES_MARSHADOW] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 2),    // dark grey
    PALd(6, 2),    // grey
    PALe(8, 1),    // yellow
},
```

### #803 SPECIES_POIPOLE
```c
[SPECIES_POIPOLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // purple
},
```

### #804 SPECIES_NAGANADEL
```c
[SPECIES_NAGANADEL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // purple
},
```

### #805 SPECIES_STAKATAKA
```c
[SPECIES_STAKATAKA] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // grey
    PALc(5, 4),    // dark grey
    PALd(9, 1),    // dark grey
    PALe(10, 1),    // blue
},
```

### #806 SPECIES_BLACEPHALON
```c
[SPECIES_BLACEPHALON] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // white
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #807 SPECIES_ZERAORA
```c
[SPECIES_ZERAORA] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // yellow
    PALc(4, 1),    // blue
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // cyan
},
```

### #808 SPECIES_MELTAN
```c
[SPECIES_MELTAN] = {
    PALa(1, 2),    // orange
    PALb(3, 1),    // orange
    PALc(4, 1),    // yellow
    PALd(5, 1),    // white
    PALe(6, 1),    // dark brown
},
```

### #809 SPECIES_MELMETAL
```c
[SPECIES_MELMETAL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // orange
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // orange
},
```

### #810 SPECIES_GROOKEY
```c
[SPECIES_GROOKEY] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // green
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // yellow
},
```

### #811 SPECIES_THWACKEY
```c
[SPECIES_THWACKEY] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // green
    PALc(4, 1),    // yellow
    PALd(5, 1),    // green
    PALe(6, 1),    // white
},
```

### #812 SPECIES_RILLABOOM
```c
[SPECIES_RILLABOOM] = {
    PALa(1, 1),    // black
    PALb(2, 3),    // dark green
    PALc(5, 1),    // dark brown
    PALd(6, 1),    // grey
    PALe(7, 1),    // dark grey
},
```

### #813 SPECIES_SCORBUNNY
```c
[SPECIES_SCORBUNNY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // yellow
    PALe(6, 2),    // light grey
},
```

### #814 SPECIES_RABOOT
```c
[SPECIES_RABOOT] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // yellow
},
```

### #815 SPECIES_CINDERACE
```c
[SPECIES_CINDERACE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 1),    // light grey
    PALe(5, 2),    // yellow
},
```

### #816 SPECIES_SOBBLE
```c
[SPECIES_SOBBLE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // yellow
    PALc(3, 1),    // brown
    PALd(4, 2),    // blue
    PALe(6, 2),    // cyan
},
```

### #817 SPECIES_DRIZZILE
```c
[SPECIES_DRIZZILE] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // blue
    PALd(4, 1),    // purple
    PALe(5, 2),    // blue
},
```

### #818 SPECIES_INTELEON
```c
[SPECIES_INTELEON] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // brown
    PALc(3, 2),    // yellow
    PALd(5, 2),    // blue
    PALe(7, 1),    // cyan
},
```

### #819 SPECIES_SKWOVET
```c
[SPECIES_SKWOVET] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // grey
    PALc(6, 2),    // grey
    PALd(8, 1),    // orange
    PALe(9, 1),    // orange
},
```

### #820 SPECIES_GREEDENT
```c
[SPECIES_GREEDENT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // brown
    PALc(5, 1),    // black
    PALd(6, 2),    // brown
    PALe(8, 5),    // orange
},
```

### #821 SPECIES_ROOKIDEE
```c
[SPECIES_ROOKIDEE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // blue
    PALd(5, 2),    // black
    PALe(7, 1),    // light grey
},
```

### #822 SPECIES_CORVISQUIRE
```c
[SPECIES_CORVISQUIRE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 2),    // blue
    PALd(6, 2),    // black
    PALe(8, 1),    // dark brown
},
```

### #823 SPECIES_CORVIKNIGHT
```c
[SPECIES_CORVIKNIGHT] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // dark grey
    PALc(4, 3),    // blue
    PALd(7, 1),    // purple
    PALe(8, 1),    // red
},
```

### #824 SPECIES_BLIPBUG
```c
[SPECIES_BLIPBUG] = {
    PALa(1, 3),    // black
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // grey
    PALd(6, 1),    // light grey
    PALe(7, 2),    // grey
},
```

### #825 SPECIES_DOTTLER
```c
[SPECIES_DOTTLER] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // orange
    PALc(3, 1),    // blue
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // yellow
},
```

### #826 SPECIES_ORBEETLE
```c
[SPECIES_ORBEETLE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark blue
    PALc(3, 2),    // red
    PALd(5, 1),    // blue
    PALe(6, 1),    // dark grey
},
```

### #827 SPECIES_NICKIT
```c
[SPECIES_NICKIT] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // brown
    PALc(5, 1),    // black
    PALd(6, 1),    // red
    PALe(7, 1),    // light grey
},
```

### #828 SPECIES_THIEVUL
```c
[SPECIES_THIEVUL] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // dark brown
    PALc(6, 1),    // red
    PALd(7, 1),    // grey
    PALe(8, 1),    // brown
},
```

### #829 SPECIES_GOSSIFLEUR
```c
[SPECIES_GOSSIFLEUR] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // yellow
},
```

### #830 SPECIES_ELDEGOSS
```c
[SPECIES_ELDEGOSS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // grey
    PALc(3, 2),    // light grey
    PALd(5, 2),    // green
    PALe(7, 1),    // dark grey
},
```

### #831 SPECIES_WOOLOO
```c
[SPECIES_WOOLOO] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // light grey
    PALc(5, 2),    // black
    PALd(7, 1),    // dark grey
    PALe(8, 2),    // grey
},
```

### #832 SPECIES_DUBWOOL
```c
[SPECIES_DUBWOOL] = {
    PALa(1, 4),    // black
    PALb(5, 2),    // grey
    PALc(7, 2),    // light grey
    PALd(9, 2),    // grey
    PALe(11, 2),    // dark grey
},
```

### #833 SPECIES_CHEWTLE
```c
[SPECIES_CHEWTLE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // cyan
},
```

### #834 SPECIES_DREDNAW
```c
[SPECIES_DREDNAW] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // orange
    PALd(4, 1),    // light pink
    PALe(5, 1),    // orange
},
```

### #835 SPECIES_YAMPER
```c
[SPECIES_YAMPER] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // orange
    PALd(4, 1),    // brown
    PALe(5, 1),    // yellow
},
```

### #836 SPECIES_BOLTUND
```c
[SPECIES_BOLTUND] = {
    PALa(1, 2),    // orange
    PALb(3, 1),    // yellow
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #837 SPECIES_ROLYCOLY
```c
[SPECIES_ROLYCOLY] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // light grey
    PALc(5, 3),    // dark grey
    PALd(8, 2),    // dark grey
    PALe(10, 1),    // red
},
```

### #838 SPECIES_CARKOL
```c
[SPECIES_CARKOL] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // dark brown
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // red
    PALe(8, 4),    // grey
},
```

### #839 SPECIES_COALOSSAL
```c
[SPECIES_COALOSSAL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 5),    // grey
    PALc(7, 4),    // grey
    PALd(11, 1),    // red
    PALe(12, 2),    // orange
},
```

### #840 SPECIES_APPLIN
```c
[SPECIES_APPLIN] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // green
    PALc(3, 1),    // green
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #841 SPECIES_FLAPPLE
```c
[SPECIES_FLAPPLE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // green
},
```

### #842 SPECIES_APPLETUN
```c
[SPECIES_APPLETUN] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark green
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // green
},
```

### #843 SPECIES_SILICOBRA
```c
[SPECIES_SILICOBRA] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // black
    PALc(5, 1),    // white
    PALd(6, 4),    // yellow
    PALe(10, 1),    // dark grey
},
```

### #844 SPECIES_SANDACONDA
```c
[SPECIES_SANDACONDA] = {
    PALa(1, 2),    // brown
    PALb(3, 4),    // dark grey
    PALc(7, 2),    // dark grey
    PALd(9, 1),    // white
    PALe(10, 1),    // grey
},
```

### #845 SPECIES_CRAMORANT
```c
[SPECIES_CRAMORANT] = {
    PALa(1, 3),    // dark blue
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // brown
    PALd(6, 1),    // green
    PALe(7, 1),    // yellow
},
```

### #846 SPECIES_ARROKUDA
```c
[SPECIES_ARROKUDA] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // orange
    PALd(4, 2),    // dark brown
    PALe(6, 1),    // yellow
},
```

### #847 SPECIES_BARRASKEWDA
```c
[SPECIES_BARRASKEWDA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // brown
    PALc(3, 2),    // red
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // dark brown
},
```

### #848 SPECIES_TOXEL
```c
[SPECIES_TOXEL] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 1),    // purple
},
```

### #849 SPECIES_TOXTRICITY_AMPED
```c
// Graphics not found
```

### #850 SPECIES_SIZZLIPEDE
```c
[SPECIES_SIZZLIPEDE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // yellow
},
```

### #851 SPECIES_CENTISKORCH
```c
[SPECIES_CENTISKORCH] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // yellow
    PALc(4, 3),    // dark brown
    PALd(7, 2),    // red
    PALe(9, 4),    // black
},
```

### #852 SPECIES_CLOBBOPUS
```c
[SPECIES_CLOBBOPUS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // purple
    PALe(5, 2),    // red
},
```

### #853 SPECIES_GRAPPLOCT
```c
[SPECIES_GRAPPLOCT] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark blue
    PALe(5, 1),    // blue
},
```

### #854 SPECIES_SINISTEA_PHONY
```c
// Graphics not found
```

### #855 SPECIES_POLTEAGEIST_PHONY
```c
// Graphics not found
```

### #856 SPECIES_HATENNA
```c
[SPECIES_HATENNA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // cyan
    PALe(5, 1),    // purple
},
```

### #857 SPECIES_HATTREM
```c
[SPECIES_HATTREM] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // white
    PALc(3, 4),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // blue
},
```

### #858 SPECIES_HATTERENE
```c
[SPECIES_HATTERENE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // cyan
    PALe(6, 2),    // light grey
},
```

### #859 SPECIES_IMPIDIMP
```c
[SPECIES_IMPIDIMP] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // brown
    PALc(3, 2),    // light pink
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // blue
},
```

### #860 SPECIES_MORGREM
```c
[SPECIES_MORGREM] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 3),    // black
    PALd(6, 1),    // red
    PALe(7, 1),    // dark grey
},
```

### #861 SPECIES_GRIMMSNARL
```c
[SPECIES_GRIMMSNARL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // green
    PALc(3, 2),    // black
    PALd(5, 1),    // blue
    PALe(6, 1),    // green
},
```

### #862 SPECIES_OBSTAGOON
```c
[SPECIES_OBSTAGOON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark grey
    PALc(5, 1),    // light grey
    PALd(6, 1),    // light grey
    PALe(7, 1),    // grey
},
```

### #863 SPECIES_PERRSERKER
```c
[SPECIES_PERRSERKER] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // dark grey
},
```

### #864 SPECIES_CURSOLA
```c
[SPECIES_CURSOLA] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 2),    // light grey
    PALe(6, 1),    // grey
},
```

### #865 SPECIES_SIRFETCHD
```c
[SPECIES_SIRFETCHD] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // white
},
```

### #866 SPECIES_MR_RIME
```c
[SPECIES_MR_RIME] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 1),    // purple
},
```

### #867 SPECIES_RUNERIGUS
```c
[SPECIES_RUNERIGUS] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // light grey
    PALc(4, 2),    // grey
    PALd(6, 1),    // light grey
    PALe(7, 2),    // red
},
```

### #868 SPECIES_MILCERY
```c
[SPECIES_MILCERY] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // yellow
    PALc(4, 1),    // white
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // white
},
```

### #869 SPECIES_ALCREMIE_STRAWBERRY_VANILLA_CREAM
```c
// Graphics not found
```

### #870 SPECIES_FALINKS
```c
[SPECIES_FALINKS] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // red
    PALd(4, 1),    // orange
    PALe(5, 1),    // red
},
```

### #871 SPECIES_PINCURCHIN
```c
[SPECIES_PINCURCHIN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark grey
},
```

### #872 SPECIES_SNOM
```c
[SPECIES_SNOM] = {
    PALa(1, 1),    // blue
    PALb(2, 3),    // cyan
    PALc(5, 1),    // grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // light grey
},
```

### #873 SPECIES_FROSMOTH
```c
[SPECIES_FROSMOTH] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // light grey
    PALc(5, 1),    // white
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // grey
},
```

### #874 SPECIES_STONJOURNER
```c
[SPECIES_STONJOURNER] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // dark grey
    PALc(5, 2),    // grey
    PALd(7, 2),    // light grey
    PALe(9, 1),    // yellow
},
```

### #875 SPECIES_EISCUE_ICE
```c
// Graphics not found
```

### #876 SPECIES_INDEEDEE_M
```c
// Graphics not found
```

### #877 SPECIES_MORPEKO_FULL_BELLY
```c
// Graphics not found
```

### #878 SPECIES_CUFANT
```c
[SPECIES_CUFANT] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 2),    // green
},
```

### #879 SPECIES_COPPERAJAH
```c
[SPECIES_COPPERAJAH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // orange
},
```

### #880 SPECIES_DRACOZOLT
```c
[SPECIES_DRACOZOLT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // brown
    PALc(3, 1),    // yellow
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark brown
},
```

### #881 SPECIES_ARCTOZOLT
```c
[SPECIES_ARCTOZOLT] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // orange
    PALe(6, 1),    // cyan
},
```

### #882 SPECIES_DRACOVISH
```c
[SPECIES_DRACOVISH] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // red
    PALd(4, 1),    // cyan
    PALe(5, 1),    // blue
},
```

### #883 SPECIES_ARCTOVISH
```c
[SPECIES_ARCTOVISH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // cyan
    PALd(5, 1),    // blue
    PALe(6, 1),    // light grey
},
```

### #884 SPECIES_DURALUDON
```c
[SPECIES_DURALUDON] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // yellow
},
```

### #885 SPECIES_DREEPY
```c
[SPECIES_DREEPY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // purple
    PALd(4, 1),    // grey
    PALe(5, 1),    // red
},
```

### #886 SPECIES_DRAKLOAK
```c
[SPECIES_DRAKLOAK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 2),    // dark grey
    PALd(5, 2),    // grey
    PALe(7, 1),    // purple
},
```

### #887 SPECIES_DRAGAPULT
```c
[SPECIES_DRAGAPULT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 2),    // purple
    PALe(7, 2),    // cyan
},
```

### #888 SPECIES_ZACIAN_HERO
```c
// Graphics not found
```

### #889 SPECIES_ZAMAZENTA_HERO
```c
// Graphics not found
```

### #890 SPECIES_ETERNATUS
```c
[SPECIES_ETERNATUS] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 3),    // red
    PALe(7, 1),    // dark blue
},
```

### #891 SPECIES_KUBFU
```c
[SPECIES_KUBFU] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // light grey
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // white
    PALe(7, 1),    // light grey
},
```

### #892 SPECIES_URSHIFU_SINGLE_STRIKE
```c
// Graphics not found
```

### #893 SPECIES_ZARUDE
```c
[SPECIES_ZARUDE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // light grey
    PALd(6, 2),    // dark grey
    PALe(8, 1),    // red
},
```

### #894 SPECIES_REGIELEKI
```c
[SPECIES_REGIELEKI] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // white
},
```

### #895 SPECIES_REGIDRAGO
```c
[SPECIES_REGIDRAGO] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // blue
    PALd(6, 1),    // dark brown
    PALe(7, 2),    // red
},
```

### #896 SPECIES_GLASTRIER
```c
[SPECIES_GLASTRIER] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // black
    PALc(3, 1),    // light cyan
    PALd(4, 1),    // white
    PALe(5, 1),    // blue
},
```

### #897 SPECIES_SPECTRIER
```c
[SPECIES_SPECTRIER] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // grey
    PALe(6, 1),    // black
},
```

### #898 SPECIES_CALYREX
```c
[SPECIES_CALYREX] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 2),    // black
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark green
},
```

### #899 SPECIES_WYRDEER
```c
[SPECIES_WYRDEER] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // orange
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark grey
},
```

### #900 SPECIES_KLEAVOR
```c
[SPECIES_KLEAVOR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // grey
    PALe(6, 1),    // yellow
},
```


## Pokémon #901-1000

### #901 SPECIES_URSALUNA
```c
[SPECIES_URSALUNA] = {
    PALa(1, 6),    // dark grey
    PALb(7, 1),    // green
    PALc(8, 2),    // grey
    PALd(10, 1),    // grey
    PALe(11, 1),    // dark grey
},
```

### #902 SPECIES_BASCULEGION_M
```c
// Graphics not found
```

### #903 SPECIES_SNEASLER
```c
[SPECIES_SNEASLER] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // brown
    PALc(5, 1),    // brown
    PALd(6, 2),    // red
    PALe(8, 1),    // orange
},
```

### #904 SPECIES_OVERQWIL
```c
[SPECIES_OVERQWIL] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // brown
    PALc(6, 1),    // grey
    PALd(7, 5),    // blue
    PALe(12, 1),    // yellow
},
```

### #905 SPECIES_ENAMORUS_INCARNATE
```c
// Graphics not found
```

### #906 SPECIES_VENUSAUR_MEGA
```c
[SPECIES_VENUSAUR_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // pink
    PALc(3, 1),    // orange
    PALd(4, 1),    // white
    PALe(5, 1),    // brown
},
```

### #907 SPECIES_CHARIZARD_MEGA_X
```c
// Graphics not found
```

### #908 SPECIES_CHARIZARD_MEGA_Y
```c
// Graphics not found
```

### #909 SPECIES_BLASTOISE_MEGA
```c
[SPECIES_BLASTOISE_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // white
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #910 SPECIES_BEEDRILL_MEGA
```c
[SPECIES_BEEDRILL_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // light grey
},
```

### #911 SPECIES_PIDGEOT_MEGA
```c
[SPECIES_PIDGEOT_MEGA] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // blue
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // yellow
},
```

### #912 SPECIES_ALAKAZAM_MEGA
```c
[SPECIES_ALAKAZAM_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // light grey
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // brown
    PALe(8, 1),    // yellow
},
```

### #913 SPECIES_SLOWBRO_MEGA
```c
[SPECIES_SLOWBRO_MEGA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // pink
    PALe(6, 2),    // white
},
```

### #914 SPECIES_GENGAR_MEGA
```c
[SPECIES_GENGAR_MEGA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // blue
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // brown
},
```

### #915 SPECIES_KANGASKHAN_MEGA
```c
[SPECIES_KANGASKHAN_MEGA] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // yellow
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // yellow
    PALe(7, 1),    // white
},
```

### #916 SPECIES_PINSIR_MEGA
```c
[SPECIES_PINSIR_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // light grey
    PALd(5, 1),    // orange
    PALe(6, 1),    // white
},
```

### #917 SPECIES_GYARADOS_MEGA
```c
[SPECIES_GYARADOS_MEGA] = {
    PALa(1, 1),    // dark blue
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // orange
    PALe(6, 1),    // blue
},
```

### #918 SPECIES_AERODACTYL_MEGA
```c
[SPECIES_AERODACTYL_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // cyan
    PALd(5, 1),    // grey
    PALe(6, 1),    // black
},
```

### #919 SPECIES_MEWTWO_MEGA_X
```c
// Graphics not found
```

### #920 SPECIES_MEWTWO_MEGA_Y
```c
// Graphics not found
```

### #921 SPECIES_AMPHAROS_MEGA
```c
[SPECIES_AMPHAROS_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // red
    PALe(5, 2),    // white
},
```

### #922 SPECIES_STEELIX_MEGA
```c
[SPECIES_STEELIX_MEGA] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // blue
    PALc(3, 2),    // light grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #923 SPECIES_SCIZOR_MEGA
```c
[SPECIES_SCIZOR_MEGA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // grey
},
```

### #924 SPECIES_HERACROSS_MEGA
```c
[SPECIES_HERACROSS_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // cyan
    PALd(6, 1),    // red
    PALe(7, 1),    // yellow
},
```

### #925 SPECIES_HOUNDOOM_MEGA
```c
[SPECIES_HOUNDOOM_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 2),    // white
    PALd(5, 1),    // light grey
    PALe(6, 3),    // dark grey
},
```

### #926 SPECIES_TYRANITAR_MEGA
```c
[SPECIES_TYRANITAR_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // green
    PALe(5, 1),    // dark brown
},
```

### #927 SPECIES_SCEPTILE_MEGA
```c
[SPECIES_SCEPTILE_MEGA] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // green
    PALc(4, 1),    // green
    PALd(5, 1),    // black
    PALe(6, 1),    // yellow
},
```

### #928 SPECIES_BLAZIKEN_MEGA
```c
[SPECIES_BLAZIKEN_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // orange
},
```

### #929 SPECIES_SWAMPERT_MEGA
```c
[SPECIES_SWAMPERT_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // orange
},
```

### #930 SPECIES_GARDEVOIR_MEGA
```c
[SPECIES_GARDEVOIR_MEGA] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // green
    PALc(3, 2),    // yellow
    PALd(5, 1),    // blue
    PALe(6, 1),    // light grey
},
```

### #931 SPECIES_SABLEYE_MEGA
```c
[SPECIES_SABLEYE_MEGA] = {
    PALa(1, 1),    // red
    PALb(2, 3),    // red
    PALc(5, 2),    // black
    PALd(7, 1),    // dark blue
    PALe(8, 1),    // blue
},
```

### #932 SPECIES_MAWILE_MEGA
```c
[SPECIES_MAWILE_MEGA] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // grey
    PALd(5, 1),    // orange
    PALe(6, 2),    // brown
},
```

### #933 SPECIES_AGGRON_MEGA
```c
[SPECIES_AGGRON_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // white
    PALd(4, 1),    // grey
    PALe(5, 3),    // light grey
},
```

### #934 SPECIES_MEDICHAM_MEGA
```c
[SPECIES_MEDICHAM_MEGA] = {
    PALa(1, 2),    // black
    PALb(3, 3),    // brown
    PALc(6, 1),    // orange
    PALd(7, 1),    // purple
    PALe(8, 1),    // cyan
},
```

### #935 SPECIES_MANECTRIC_MEGA
```c
[SPECIES_MANECTRIC_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // black
    PALd(4, 1),    // yellow
    PALe(5, 1),    // brown
},
```

### #936 SPECIES_SHARPEDO_MEGA
```c
[SPECIES_SHARPEDO_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // blue
    PALc(5, 1),    // light grey
    PALd(6, 1),    // yellow
    PALe(7, 1),    // dark grey
},
```

### #937 SPECIES_CAMERUPT_MEGA
```c
[SPECIES_CAMERUPT_MEGA] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // orange
    PALc(4, 2),    // yellow
    PALd(6, 3),    // grey
    PALe(9, 2),    // red
},
```

### #938 SPECIES_ALTARIA_MEGA
```c
[SPECIES_ALTARIA_MEGA] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // blue
    PALc(3, 3),    // light grey
    PALd(6, 1),    // blue
    PALe(7, 1),    // cyan
},
```

### #939 SPECIES_BANETTE_MEGA
```c
[SPECIES_BANETTE_MEGA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // orange
    PALe(6, 1),    // brown
},
```

### #940 SPECIES_ABSOL_MEGA
```c
[SPECIES_ABSOL_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 1),    // grey
    PALe(5, 1),    // blue
},
```

### #941 SPECIES_GLALIE_MEGA
```c
[SPECIES_GLALIE_MEGA] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // cyan
    PALe(6, 1),    // grey
},
```

### #942 SPECIES_SALAMENCE_MEGA
```c
[SPECIES_SALAMENCE_MEGA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 2),    // brown
    PALd(5, 3),    // dark grey
    PALe(8, 1),    // cyan
},
```

### #943 SPECIES_METAGROSS_MEGA
```c
[SPECIES_METAGROSS_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // blue
},
```

### #944 SPECIES_LATIAS_MEGA
```c
[SPECIES_LATIAS_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 4),    // blue
},
```

### #945 SPECIES_LATIOS_MEGA
```c
[SPECIES_LATIOS_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 4),    // blue
},
```

### #946 SPECIES_LOPUNNY_MEGA
```c
[SPECIES_LOPUNNY_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 2),    // dark grey
    PALd(5, 2),    // brown
    PALe(7, 1),    // grey
},
```

### #947 SPECIES_GARCHOMP_MEGA
```c
[SPECIES_GARCHOMP_MEGA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // orange
    PALd(4, 1),    // black
    PALe(5, 1),    // yellow
},
```

### #948 SPECIES_LUCARIO_MEGA
```c
[SPECIES_LUCARIO_MEGA] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // blue
    PALe(5, 2),    // grey
},
```

### #949 SPECIES_ABOMASNOW_MEGA
```c
[SPECIES_ABOMASNOW_MEGA] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // white
    PALd(5, 3),    // cyan
    PALe(8, 1),    // dark grey
},
```

### #950 SPECIES_GALLADE_MEGA
```c
[SPECIES_GALLADE_MEGA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // blue
    PALc(5, 1),    // grey
    PALd(6, 1),    // cyan
    PALe(7, 1),    // white
},
```

### #951 SPECIES_AUDINO_MEGA
```c
[SPECIES_AUDINO_MEGA] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // yellow
    PALc(4, 2),    // brown
    PALd(6, 1),    // light pink
    PALe(7, 1),    // grey
},
```

### #952 SPECIES_DIANCIE_MEGA
```c
[SPECIES_DIANCIE_MEGA] = {
    PALa(1, 4),    // grey
    PALb(5, 1),    // yellow
    PALc(6, 1),    // grey
    PALd(7, 1),    // purple
    PALe(8, 1),    // light grey
},
```

### #953 SPECIES_RAYQUAZA_MEGA
```c
[SPECIES_RAYQUAZA_MEGA] = {
    PALa(1, 3),    // orange
    PALb(4, 1),    // dark brown
    PALc(5, 1),    // orange
    PALd(6, 1),    // grey
    PALe(7, 1),    // black
},
```

### #954 SPECIES_KYOGRE_PRIMAL
```c
[SPECIES_KYOGRE_PRIMAL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // black
    PALe(5, 2),    // yellow
},
```

### #955 SPECIES_GROUDON_PRIMAL
```c
[SPECIES_GROUDON_PRIMAL] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // red
    PALd(5, 1),    // yellow
    PALe(6, 1),    // orange
},
```

### #956 SPECIES_RATTATA_ALOLA
```c
[SPECIES_RATTATA_ALOLA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // grey
},
```

### #957 SPECIES_RATICATE_ALOLA
```c
[SPECIES_RATICATE_ALOLA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // grey
    PALc(6, 2),    // dark grey
    PALd(8, 1),    // white
    PALe(9, 1),    // grey
},
```

### #958 SPECIES_RAICHU_ALOLA
```c
[SPECIES_RAICHU_ALOLA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 3),    // brown
},
```

### #959 SPECIES_SANDSHREW_ALOLA
```c
[SPECIES_SANDSHREW_ALOLA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 2),    // light cyan
    PALe(6, 1),    // dark grey
},
```

### #960 SPECIES_SANDSLASH_ALOLA
```c
[SPECIES_SANDSLASH_ALOLA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // light cyan
    PALd(5, 5),    // cyan
    PALe(10, 3),    // light grey
},
```

### #961 SPECIES_VULPIX_ALOLA
```c
[SPECIES_VULPIX_ALOLA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #962 SPECIES_NINETALES_ALOLA
```c
[SPECIES_NINETALES_ALOLA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // cyan
    PALd(4, 2),    // blue
    PALe(6, 1),    // dark grey
},
```

### #963 SPECIES_DIGLETT_ALOLA
```c
[SPECIES_DIGLETT_ALOLA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 2),    // dark brown
    PALd(5, 2),    // orange
    PALe(7, 1),    // white
},
```

### #964 SPECIES_DUGTRIO_ALOLA
```c
[SPECIES_DUGTRIO_ALOLA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 2),    // orange
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // white
},
```

### #965 SPECIES_MEOWTH_ALOLA
```c
[SPECIES_MEOWTH_ALOLA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // brown
},
```

### #966 SPECIES_PERSIAN_ALOLA
```c
[SPECIES_PERSIAN_ALOLA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 5),    // dark grey
    PALc(7, 1),    // grey
    PALd(8, 1),    // blue
    PALe(9, 1),    // white
},
```

### #967 SPECIES_GEODUDE_ALOLA
```c
[SPECIES_GEODUDE_ALOLA] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // cyan
    PALc(4, 2),    // dark grey
    PALd(6, 2),    // dark grey
    PALe(8, 2),    // light grey
},
```

### #968 SPECIES_GRAVELER_ALOLA
```c
[SPECIES_GRAVELER_ALOLA] = {
    PALa(1, 3),    // grey
    PALb(4, 2),    // dark grey
    PALc(6, 1),    // light grey
    PALd(7, 2),    // dark grey
    PALe(9, 2),    // orange
},
```

### #969 SPECIES_GOLEM_ALOLA
```c
[SPECIES_GOLEM_ALOLA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 1),    // orange
},
```

### #970 SPECIES_GRIMER_ALOLA
```c
[SPECIES_GRIMER_ALOLA] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // black
    PALc(5, 1),    // green
    PALd(6, 1),    // black
    PALe(7, 1),    // white
},
```

### #971 SPECIES_MUK_ALOLA
```c
[SPECIES_MUK_ALOLA] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // brown
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // purple
},
```

### #972 SPECIES_EXEGGUTOR_ALOLA
```c
[SPECIES_EXEGGUTOR_ALOLA] = {
    PALa(1, 2),    // black
    PALb(3, 3),    // grey
    PALc(6, 1),    // brown
    PALd(7, 1),    // purple
    PALe(8, 1),    // purple
},
```

### #973 SPECIES_MAROWAK_ALOLA
```c
[SPECIES_MAROWAK_ALOLA] = {
    PALa(1, 1),    // cyan
    PALb(2, 2),    // cyan
    PALc(4, 1),    // green
    PALd(5, 1),    // grey
    PALe(6, 1),    // dark grey
},
```

### #974 SPECIES_MEOWTH_GALAR
```c
[SPECIES_MEOWTH_GALAR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 2),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // light grey
},
```

### #975 SPECIES_PONYTA_GALAR
```c
[SPECIES_PONYTA_GALAR] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // cyan
    PALc(3, 1),    // cyan
    PALd(4, 1),    // purple
    PALe(5, 2),    // light purple
},
```

### #976 SPECIES_RAPIDASH_GALAR
```c
[SPECIES_RAPIDASH_GALAR] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // blue
},
```

### #977 SPECIES_SLOWPOKE_GALAR
```c
[SPECIES_SLOWPOKE_GALAR] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // yellow
    PALd(4, 1),    // brown
    PALe(5, 1),    // purple
},
```

### #978 SPECIES_SLOWBRO_GALAR
```c
[SPECIES_SLOWBRO_GALAR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // purple
    PALe(5, 1),    // light grey
},
```

### #979 SPECIES_FARFETCHD_GALAR
```c
[SPECIES_FARFETCHD_GALAR] = {
    PALa(1, 4),    // grey
    PALb(5, 2),    // grey
    PALc(7, 2),    // light grey
    PALd(9, 1),    // grey
    PALe(10, 2),    // yellow
},
```

### #980 SPECIES_WEEZING_GALAR
```c
[SPECIES_WEEZING_GALAR] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // brown
    PALc(4, 2),    // light grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // grey
},
```

### #981 SPECIES_MR_MIME_GALAR
```c
// Graphics not found
```

### #982 SPECIES_ARTICUNO_GALAR
```c
[SPECIES_ARTICUNO_GALAR] = {
    PALa(1, 2),    // black
    PALb(3, 1),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // blue
    PALe(6, 1),    // dark grey
},
```

### #983 SPECIES_ZAPDOS_GALAR
```c
[SPECIES_ZAPDOS_GALAR] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // red
    PALe(6, 1),    // dark grey
},
```

### #984 SPECIES_MOLTRES_GALAR
```c
[SPECIES_MOLTRES_GALAR] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // purple
    PALd(4, 2),    // grey
    PALe(6, 1),    // light pink
},
```

### #985 SPECIES_SLOWKING_GALAR
```c
[SPECIES_SLOWKING_GALAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // purple
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // blue
    PALe(6, 1),    // white
},
```

### #986 SPECIES_CORSOLA_GALAR
```c
[SPECIES_CORSOLA_GALAR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 3),    // light grey
},
```

### #987 SPECIES_ZIGZAGOON_GALAR
```c
[SPECIES_ZIGZAGOON_GALAR] = {
    PALa(1, 5),    // dark grey
    PALb(6, 1),    // light grey
    PALc(7, 1),    // light grey
    PALd(8, 1),    // red
    PALe(9, 1),    // white
},
```

### #988 SPECIES_LINOONE_GALAR
```c
[SPECIES_LINOONE_GALAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 1),    // light grey
},
```

### #989 SPECIES_DARUMAKA_GALAR
```c
[SPECIES_DARUMAKA_GALAR] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // cyan
    PALe(5, 1),    // green
},
```

### #990 SPECIES_DARMANITAN_GALAR_STANDARD
```c
// Graphics not found
```

### #991 SPECIES_YAMASK_GALAR
```c
[SPECIES_YAMASK_GALAR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // purple
    PALe(6, 1),    // black
},
```

### #992 SPECIES_STUNFISK_GALAR
```c
[SPECIES_STUNFISK_GALAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #993 SPECIES_GROWLITHE_HISUI
```c
[SPECIES_GROWLITHE_HISUI] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // light grey
},
```

### #994 SPECIES_ARCANINE_HISUI
```c
[SPECIES_ARCANINE_HISUI] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // dark brown
},
```

### #995 SPECIES_VOLTORB_HISUI
```c
[SPECIES_VOLTORB_HISUI] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 3),    // red
    PALd(6, 2),    // orange
    PALe(8, 1),    // light grey
},
```

### #996 SPECIES_ELECTRODE_HISUI
```c
[SPECIES_ELECTRODE_HISUI] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // yellow
    PALc(4, 2),    // orange
    PALd(6, 1),    // white
    PALe(7, 1),    // dark grey
},
```

### #997 SPECIES_TYPHLOSION_HISUI
```c
[SPECIES_TYPHLOSION_HISUI] = {
    PALa(1, 2),    // purple
    PALb(3, 1),    // purple
    PALc(4, 1),    // red
    PALd(5, 1),    // grey
    PALe(6, 1),    // black
},
```

### #998 SPECIES_QWILFISH_HISUI
```c
[SPECIES_QWILFISH_HISUI] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 4),    // dark grey
    PALd(7, 1),    // purple
    PALe(8, 1),    // grey
},
```

### #999 SPECIES_SNEASEL_HISUI
```c
[SPECIES_SNEASEL_HISUI] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // red
},
```

### #1000 SPECIES_SAMUROTT_HISUI
```c
[SPECIES_SAMUROTT_HISUI] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // brown
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 1),    // dark brown
},
```


## Pokémon #1001-1100

### #1001 SPECIES_LILLIGANT_HISUI
```c
[SPECIES_LILLIGANT_HISUI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // purple
    PALd(4, 1),    // purple
    PALe(5, 1),    // yellow
},
```

### #1002 SPECIES_ZORUA_HISUI
```c
[SPECIES_ZORUA_HISUI] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // purple
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #1003 SPECIES_ZOROARK_HISUI
```c
[SPECIES_ZOROARK_HISUI] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 4),    // dark brown
    PALd(8, 1),    // yellow
    PALe(9, 3),    // grey
},
```

### #1004 SPECIES_BRAVIARY_HISUI
```c
[SPECIES_BRAVIARY_HISUI] = {
    PALa(1, 1),    // orange
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // blue
},
```

### #1005 SPECIES_SLIGGOO_HISUI
```c
[SPECIES_SLIGGOO_HISUI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // grey
},
```

### #1006 SPECIES_GOODRA_HISUI
```c
[SPECIES_GOODRA_HISUI] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // white
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // grey
},
```

### #1007 SPECIES_AVALUGG_HISUI
```c
[SPECIES_AVALUGG_HISUI] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // brown
    PALe(6, 1),    // light grey
},
```

### #1008 SPECIES_DECIDUEYE_HISUI
```c
[SPECIES_DECIDUEYE_HISUI] = {
    PALa(1, 6),    // black
    PALb(7, 6),    // dark brown
    PALc(13, 1),    // light grey
    PALd(14, 1),    // dark grey
    PALe(15, 1),    // light grey
},
```

### #1009 SPECIES_PIKACHU_COSPLAY
```c
[SPECIES_PIKACHU_COSPLAY] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // grey
    PALc(5, 1),    // orange
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // yellow
},
```

### #1010 SPECIES_PIKACHU_ROCK_STAR
```c
// Graphics not found
```

### #1011 SPECIES_PIKACHU_BELLE
```c
[SPECIES_PIKACHU_BELLE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // yellow
    PALc(3, 1),    // red
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark grey
},
```

### #1012 SPECIES_PIKACHU_POP_STAR
```c
// Graphics not found
```

### #1013 SPECIES_PIKACHU_PHD
```c
[SPECIES_PIKACHU_PHD] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // orange
    PALc(5, 1),    // dark brown
    PALd(6, 1),    // dark brown
    PALe(7, 1),    // grey
},
```

### #1014 SPECIES_PIKACHU_LIBRE
```c
[SPECIES_PIKACHU_LIBRE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // grey
    PALd(5, 1),    // orange
    PALe(6, 1),    // dark brown
},
```

### #1015 SPECIES_PIKACHU_ORIGINAL
```c
[SPECIES_PIKACHU_ORIGINAL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // red
},
```

### #1016 SPECIES_PIKACHU_HOENN
```c
[SPECIES_PIKACHU_HOENN] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // grey
    PALd(4, 1),    // red
    PALe(5, 1),    // dark grey
},
```

### #1017 SPECIES_PIKACHU_SINNOH
```c
[SPECIES_PIKACHU_SINNOH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // grey
    PALd(4, 1),    // red
    PALe(5, 1),    // dark grey
},
```

### #1018 SPECIES_PIKACHU_UNOVA
```c
[SPECIES_PIKACHU_UNOVA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // red
},
```

### #1019 SPECIES_PIKACHU_KALOS
```c
[SPECIES_PIKACHU_KALOS] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // grey
},
```

### #1020 SPECIES_PIKACHU_ALOLA
```c
[SPECIES_PIKACHU_ALOLA] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // red
    PALe(5, 1),    // light grey
},
```

### #1021 SPECIES_PIKACHU_PARTNER
```c
[SPECIES_PIKACHU_PARTNER] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // light grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // red
},
```

### #1022 SPECIES_PIKACHU_WORLD
```c
[SPECIES_PIKACHU_WORLD] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // dark grey
    PALc(5, 2),    // grey
    PALd(7, 1),    // green
    PALe(8, 1),    // dark brown
},
```

### #1023 SPECIES_PICHU_SPIKY_EARED
```c
// Graphics not found
```

### #1024 SPECIES_UNOWN_B
```c
// Graphics not found
```

### #1025 SPECIES_UNOWN_C
```c
// Graphics not found
```

### #1026 SPECIES_UNOWN_D
```c
// Graphics not found
```

### #1027 SPECIES_UNOWN_E
```c
// Graphics not found
```

### #1028 SPECIES_UNOWN_F
```c
// Graphics not found
```

### #1029 SPECIES_UNOWN_G
```c
// Graphics not found
```

### #1030 SPECIES_UNOWN_H
```c
// Graphics not found
```

### #1031 SPECIES_UNOWN_I
```c
// Graphics not found
```

### #1032 SPECIES_UNOWN_J
```c
// Graphics not found
```

### #1033 SPECIES_UNOWN_K
```c
// Graphics not found
```

### #1034 SPECIES_UNOWN_L
```c
// Graphics not found
```

### #1035 SPECIES_UNOWN_M
```c
// Graphics not found
```

### #1036 SPECIES_UNOWN_N
```c
// Graphics not found
```

### #1037 SPECIES_UNOWN_O
```c
// Graphics not found
```

### #1038 SPECIES_UNOWN_P
```c
// Graphics not found
```

### #1039 SPECIES_UNOWN_Q
```c
// Graphics not found
```

### #1040 SPECIES_UNOWN_R
```c
// Graphics not found
```

### #1041 SPECIES_UNOWN_S
```c
// Graphics not found
```

### #1042 SPECIES_UNOWN_T
```c
// Graphics not found
```

### #1043 SPECIES_UNOWN_U
```c
// Graphics not found
```

### #1044 SPECIES_UNOWN_V
```c
// Graphics not found
```

### #1045 SPECIES_UNOWN_W
```c
// Graphics not found
```

### #1046 SPECIES_UNOWN_X
```c
// Graphics not found
```

### #1047 SPECIES_UNOWN_Y
```c
// Graphics not found
```

### #1048 SPECIES_UNOWN_Z
```c
// Graphics not found
```

### #1049 SPECIES_UNOWN_EXCLAMATION
```c
// Graphics not found
```

### #1050 SPECIES_UNOWN_QUESTION
```c
// Graphics not found
```

### #1051 SPECIES_CASTFORM_SUNNY
```c
[SPECIES_CASTFORM_SUNNY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 3),    // red
    PALc(5, 1),    // purple
    PALd(6, 4),    // yellow
    PALe(10, 1),    // brown
},
```

### #1052 SPECIES_CASTFORM_RAINY
```c
[SPECIES_CASTFORM_RAINY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // blue
    PALc(5, 1),    // light purple
    PALd(6, 4),    // white
    PALe(10, 1),    // grey
},
```

### #1053 SPECIES_CASTFORM_SNOWY
```c
[SPECIES_CASTFORM_SNOWY] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // blue
    PALc(4, 6),    // purple
    PALd(10, 1),    // grey
    PALe(11, 1),    // white
},
```

### #1054 SPECIES_DEOXYS_ATTACK
```c
[SPECIES_DEOXYS_ATTACK] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // orange
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // cyan
    PALe(7, 1),    // purple
},
```

### #1055 SPECIES_DEOXYS_DEFENSE
```c
[SPECIES_DEOXYS_DEFENSE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // yellow
    PALe(6, 2),    // cyan
},
```

### #1056 SPECIES_DEOXYS_SPEED
```c
[SPECIES_DEOXYS_SPEED] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // blue
    PALc(4, 1),    // dark brown
    PALd(5, 1),    // orange
    PALe(6, 1),    // dark grey
},
```

### #1057 SPECIES_BURMY_SANDY
```c
[SPECIES_BURMY_SANDY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // grey
},
```

### #1058 SPECIES_BURMY_TRASH
```c
[SPECIES_BURMY_TRASH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // grey
},
```

### #1059 SPECIES_WORMADAM_SANDY
```c
[SPECIES_WORMADAM_SANDY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // grey
},
```

### #1060 SPECIES_WORMADAM_TRASH
```c
[SPECIES_WORMADAM_TRASH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // grey
    PALe(6, 4),    // purple
},
```

### #1061 SPECIES_CHERRIM_SUNSHINE
```c
[SPECIES_CHERRIM_SUNSHINE] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // light pink
    PALc(4, 1),    // dark grey
    PALd(5, 2),    // purple
    PALe(7, 1),    // purple
},
```

### #1062 SPECIES_SHELLOS_EAST
```c
[SPECIES_SHELLOS_EAST] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // cyan
},
```

### #1063 SPECIES_GASTRODON_EAST
```c
[SPECIES_GASTRODON_EAST] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // green
    PALc(5, 1),    // green
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // green
},
```

### #1064 SPECIES_ROTOM_HEAT
```c
[SPECIES_ROTOM_HEAT] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // purple
    PALc(4, 1),    // white
    PALd(5, 2),    // red
    PALe(7, 1),    // orange
},
```

### #1065 SPECIES_ROTOM_WASH
```c
[SPECIES_ROTOM_WASH] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 2),    // red
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // orange
},
```

### #1066 SPECIES_ROTOM_FROST
```c
[SPECIES_ROTOM_FROST] = {
    PALa(1, 2),    // purple
    PALb(3, 2),    // red
    PALc(5, 1),    // orange
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark grey
},
```

### #1067 SPECIES_ROTOM_FAN
```c
[SPECIES_ROTOM_FAN] = {
    PALa(1, 1),    // orange
    PALb(2, 2),    // yellow
    PALc(4, 1),    // white
    PALd(5, 2),    // red
    PALe(7, 1),    // orange
},
```

### #1068 SPECIES_ROTOM_MOW
```c
[SPECIES_ROTOM_MOW] = {
    PALa(1, 2),    // dark green
    PALb(3, 2),    // red
    PALc(5, 1),    // orange
    PALd(6, 1),    // orange
    PALe(7, 1),    // dark grey
},
```

### #1069 SPECIES_DIALGA_ORIGIN
```c
[SPECIES_DIALGA_ORIGIN] = {
    PALa(1, 3),    // dark blue
    PALb(4, 1),    // red
    PALc(5, 8),    // blue
    PALd(13, 1),    // dark grey
    PALe(14, 1),    // light cyan
},
```

### #1070 SPECIES_PALKIA_ORIGIN
```c
[SPECIES_PALKIA_ORIGIN] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // purple
    PALc(5, 1),    // light grey
    PALd(6, 1),    // purple
    PALe(7, 1),    // white
},
```

### #1071 SPECIES_GIRATINA_ORIGIN
```c
[SPECIES_GIRATINA_ORIGIN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // red
    PALc(4, 1),    // brown
    PALd(5, 2),    // dark brown
    PALe(7, 1),    // dark grey
},
```

### #1072 SPECIES_SHAYMIN_SKY
```c
[SPECIES_SHAYMIN_SKY] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // green
    PALd(4, 1),    // grey
    PALe(5, 1),    // grey
},
```

### #1073 SPECIES_ARCEUS_FIGHTING
```c
[SPECIES_ARCEUS_FIGHTING] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1074 SPECIES_ARCEUS_FLYING
```c
[SPECIES_ARCEUS_FLYING] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1075 SPECIES_ARCEUS_POISON
```c
[SPECIES_ARCEUS_POISON] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #1076 SPECIES_ARCEUS_GROUND
```c
[SPECIES_ARCEUS_GROUND] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1077 SPECIES_ARCEUS_ROCK
```c
[SPECIES_ARCEUS_ROCK] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #1078 SPECIES_ARCEUS_BUG
```c
[SPECIES_ARCEUS_BUG] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #1079 SPECIES_ARCEUS_GHOST
```c
[SPECIES_ARCEUS_GHOST] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #1080 SPECIES_ARCEUS_STEEL
```c
[SPECIES_ARCEUS_STEEL] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1081 SPECIES_ARCEUS_FIRE
```c
[SPECIES_ARCEUS_FIRE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1082 SPECIES_ARCEUS_WATER
```c
[SPECIES_ARCEUS_WATER] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1083 SPECIES_ARCEUS_GRASS
```c
[SPECIES_ARCEUS_GRASS] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1084 SPECIES_ARCEUS_ELECTRIC
```c
[SPECIES_ARCEUS_ELECTRIC] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1085 SPECIES_ARCEUS_PSYCHIC
```c
[SPECIES_ARCEUS_PSYCHIC] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1086 SPECIES_ARCEUS_ICE
```c
[SPECIES_ARCEUS_ICE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1087 SPECIES_ARCEUS_DRAGON
```c
[SPECIES_ARCEUS_DRAGON] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1088 SPECIES_ARCEUS_DARK
```c
[SPECIES_ARCEUS_DARK] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 2),    // dark grey
},
```

### #1089 SPECIES_ARCEUS_FAIRY
```c
[SPECIES_ARCEUS_FAIRY] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // dark grey
},
```

### #1090 SPECIES_BASCULIN_BLUE_STRIPED
```c
// Graphics not found
```

### #1091 SPECIES_BASCULIN_WHITE_STRIPED
```c
// Graphics not found
```

### #1092 SPECIES_DARMANITAN_ZEN
```c
[SPECIES_DARMANITAN_ZEN] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // cyan
    PALc(3, 2),    // brown
    PALd(5, 1),    // orange
    PALe(6, 1),    // black
},
```

### #1093 SPECIES_DARMANITAN_GALAR_ZEN
```c
// Graphics not found
```

### #1094 SPECIES_DEERLING_SUMMER
```c
[SPECIES_DEERLING_SUMMER] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // black
    PALc(3, 1),    // dark green
    PALd(4, 1),    // orange
    PALe(5, 1),    // yellow
},
```

### #1095 SPECIES_DEERLING_AUTUMN
```c
[SPECIES_DEERLING_AUTUMN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // black
    PALc(3, 2),    // brown
    PALd(5, 1),    // yellow
    PALe(6, 1),    // dark brown
},
```

### #1096 SPECIES_DEERLING_WINTER
```c
[SPECIES_DEERLING_WINTER] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // brown
    PALd(4, 1),    // orange
    PALe(5, 1),    // yellow
},
```

### #1097 SPECIES_SAWSBUCK_SUMMER
```c
[SPECIES_SAWSBUCK_SUMMER] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // dark green
    PALc(5, 1),    // yellow
    PALd(6, 3),    // black
    PALe(9, 1),    // black
},
```

### #1098 SPECIES_SAWSBUCK_AUTUMN
```c
[SPECIES_SAWSBUCK_AUTUMN] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // red
    PALc(5, 1),    // black
    PALd(6, 1),    // yellow
    PALe(7, 3),    // black
},
```

### #1099 SPECIES_SAWSBUCK_WINTER
```c
[SPECIES_SAWSBUCK_WINTER] = {
    PALa(1, 4),    // grey
    PALb(5, 1),    // white
    PALc(6, 1),    // light grey
    PALd(7, 1),    // black
    PALe(8, 1),    // yellow
},
```

### #1100 SPECIES_TORNADUS_THERIAN
```c
[SPECIES_TORNADUS_THERIAN] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // blue
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // grey
    PALe(6, 1),    // white
},
```


## Pokémon #1101-1200

### #1101 SPECIES_THUNDURUS_THERIAN
```c
[SPECIES_THUNDURUS_THERIAN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 2),    // dark grey
    PALd(5, 1),    // light grey
    PALe(6, 2),    // blue
},
```

### #1102 SPECIES_LANDORUS_THERIAN
```c
[SPECIES_LANDORUS_THERIAN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // red
    PALd(5, 1),    // black
    PALe(6, 1),    // grey
},
```

### #1103 SPECIES_ENAMORUS_THERIAN
```c
[SPECIES_ENAMORUS_THERIAN] = {
    PALa(1, 2),    // dark brown
    PALb(3, 5),    // dark brown
    PALc(8, 1),    // yellow
    PALd(9, 2),    // purple
    PALe(11, 1),    // light grey
},
```

### #1104 SPECIES_KYUREM_WHITE
```c
[SPECIES_KYUREM_WHITE] = {
    PALa(1, 1),    // light cyan
    PALb(2, 1),    // cyan
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #1105 SPECIES_KYUREM_BLACK
```c
[SPECIES_KYUREM_BLACK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light cyan
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // cyan
    PALe(6, 3),    // dark grey
},
```

### #1106 SPECIES_KELDEO_RESOLUTE
```c
[SPECIES_KELDEO_RESOLUTE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // orange
    PALe(5, 1),    // blue
},
```

### #1107 SPECIES_MELOETTA_PIROUETTE
```c
[SPECIES_MELOETTA_PIROUETTE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // grey
    PALd(5, 2),    // brown
    PALe(7, 1),    // orange
},
```

### #1108 SPECIES_GENESECT_DOUSE
```c
// Graphics not found
```

### #1109 SPECIES_GENESECT_SHOCK
```c
// Graphics not found
```

### #1110 SPECIES_GENESECT_BURN
```c
// Graphics not found
```

### #1111 SPECIES_GENESECT_CHILL
```c
// Graphics not found
```

### #1112 SPECIES_GRENINJA_BOND
```c
// Graphics not found
```

### #1113 SPECIES_GRENINJA_ASH
```c
[SPECIES_GRENINJA_ASH] = {
    PALa(1, 1),    // white
    PALb(2, 1),    // dark blue
    PALc(3, 1),    // black
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // brown
},
```

### #1114 SPECIES_VIVILLON_POLAR
```c
[SPECIES_VIVILLON_POLAR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark blue
    PALc(5, 1),    // light grey
    PALd(6, 1),    // black
    PALe(7, 1),    // white
},
```

### #1115 SPECIES_VIVILLON_TUNDRA
```c
[SPECIES_VIVILLON_TUNDRA] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // light cyan
    PALc(6, 1),    // white
    PALd(7, 1),    // black
    PALe(8, 1),    // brown
},
```

### #1116 SPECIES_VIVILLON_CONTINENTAL
```c
[SPECIES_VIVILLON_CONTINENTAL] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // brown
    PALc(5, 1),    // orange
    PALd(6, 1),    // yellow
    PALe(7, 1),    // black
},
```

### #1117 SPECIES_VIVILLON_GARDEN
```c
[SPECIES_VIVILLON_GARDEN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 4),    // black
    PALc(7, 1),    // black
    PALd(8, 1),    // brown
    PALe(9, 2),    // yellow
},
```

### #1118 SPECIES_VIVILLON_ELEGANT
```c
[SPECIES_VIVILLON_ELEGANT] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // white
    PALc(4, 1),    // orange
    PALd(5, 1),    // purple
    PALe(6, 1),    // black
},
```

### #1119 SPECIES_VIVILLON_MEADOW
```c
[SPECIES_VIVILLON_MEADOW] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // brown
    PALc(5, 2),    // purple
    PALd(7, 1),    // black
    PALe(8, 1),    // brown
},
```

### #1120 SPECIES_VIVILLON_MODERN
```c
[SPECIES_VIVILLON_MODERN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // light grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // cyan
    PALe(6, 1),    // red
},
```

### #1121 SPECIES_VIVILLON_MARINE
```c
[SPECIES_VIVILLON_MARINE] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // blue
    PALc(5, 2),    // cyan
    PALd(7, 1),    // black
    PALe(8, 1),    // brown
},
```

### #1122 SPECIES_VIVILLON_ARCHIPELAGO
```c
[SPECIES_VIVILLON_ARCHIPELAGO] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // dark red
    PALc(6, 1),    // green
    PALd(7, 1),    // yellow
    PALe(8, 1),    // brown
},
```

### #1123 SPECIES_VIVILLON_HIGH_PLAINS
```c
// Graphics not found
```

### #1124 SPECIES_VIVILLON_SANDSTORM
```c
[SPECIES_VIVILLON_SANDSTORM] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // orange
    PALc(5, 1),    // brown
    PALd(6, 1),    // black
    PALe(7, 1),    // brown
},
```

### #1125 SPECIES_VIVILLON_RIVER
```c
[SPECIES_VIVILLON_RIVER] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // orange
    PALc(5, 1),    // black
    PALd(6, 1),    // yellow
    PALe(7, 1),    // dark brown
},
```

### #1126 SPECIES_VIVILLON_MONSOON
```c
[SPECIES_VIVILLON_MONSOON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // light grey
    PALc(4, 1),    // white
    PALd(5, 1),    // black
    PALe(6, 1),    // grey
},
```

### #1127 SPECIES_VIVILLON_SAVANNA
```c
[SPECIES_VIVILLON_SAVANNA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // blue
    PALc(4, 1),    // cyan
    PALd(5, 1),    // grey
    PALe(6, 1),    // yellow
},
```

### #1128 SPECIES_VIVILLON_SUN
```c
[SPECIES_VIVILLON_SUN] = {
    PALa(1, 3),    // dark grey
    PALb(4, 2),    // red
    PALc(6, 1),    // black
    PALd(7, 1),    // yellow
    PALe(8, 1),    // brown
},
```

### #1129 SPECIES_VIVILLON_OCEAN
```c
[SPECIES_VIVILLON_OCEAN] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark brown
    PALc(4, 1),    // red
    PALd(5, 3),    // orange
    PALe(8, 1),    // black
},
```

### #1130 SPECIES_VIVILLON_JUNGLE
```c
[SPECIES_VIVILLON_JUNGLE] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // cyan
    PALc(6, 1),    // black
    PALd(7, 1),    // brown
    PALe(8, 1),    // yellow
},
```

### #1131 SPECIES_VIVILLON_FANCY
```c
[SPECIES_VIVILLON_FANCY] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // green
    PALc(4, 1),    // green
    PALd(5, 1),    // purple
    PALe(6, 1),    // yellow
},
```

### #1132 SPECIES_VIVILLON_POKEBALL
```c
// Graphics not found
```

### #1133 SPECIES_FLABEBE_YELLOW
```c
[SPECIES_FLABEBE_YELLOW] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #1134 SPECIES_FLABEBE_ORANGE
```c
[SPECIES_FLABEBE_ORANGE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #1135 SPECIES_FLABEBE_BLUE
```c
[SPECIES_FLABEBE_BLUE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #1136 SPECIES_FLABEBE_WHITE
```c
[SPECIES_FLABEBE_WHITE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // white
},
```

### #1137 SPECIES_FLOETTE_YELLOW
```c
[SPECIES_FLOETTE_YELLOW] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // brown
},
```

### #1138 SPECIES_FLOETTE_ORANGE
```c
[SPECIES_FLOETTE_ORANGE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // orange
    PALe(6, 1),    // yellow
},
```

### #1139 SPECIES_FLOETTE_BLUE
```c
[SPECIES_FLOETTE_BLUE] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // blue
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // dark blue
    PALe(5, 1),    // brown
},
```

### #1140 SPECIES_FLOETTE_WHITE
```c
[SPECIES_FLOETTE_WHITE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // brown
},
```

### #1141 SPECIES_FLOETTE_ETERNAL
```c
[SPECIES_FLOETTE_ETERNAL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // dark brown
    PALd(5, 2),    // red
    PALe(7, 1),    // grey
},
```

### #1142 SPECIES_FLORGES_YELLOW
```c
[SPECIES_FLORGES_YELLOW] = {
    PALa(1, 2),    // orange
    PALb(3, 3),    // yellow
    PALc(6, 1),    // black
    PALd(7, 1),    // green
    PALe(8, 1),    // dark grey
},
```

### #1143 SPECIES_FLORGES_ORANGE
```c
[SPECIES_FLORGES_ORANGE] = {
    PALa(1, 2),    // brown
    PALb(3, 3),    // orange
    PALc(6, 1),    // black
    PALd(7, 1),    // green
    PALe(8, 1),    // dark grey
},
```

### #1144 SPECIES_FLORGES_BLUE
```c
[SPECIES_FLORGES_BLUE] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // blue
    PALc(4, 1),    // cyan
    PALd(5, 1),    // white
    PALe(6, 1),    // black
},
```

### #1145 SPECIES_FLORGES_WHITE
```c
[SPECIES_FLORGES_WHITE] = {
    PALa(1, 2),    // light grey
    PALb(3, 3),    // light grey
    PALc(6, 1),    // black
    PALd(7, 1),    // green
    PALe(8, 1),    // dark grey
},
```

### #1146 SPECIES_FURFROU_HEART
```c
[SPECIES_FURFROU_HEART] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // light grey
    PALc(4, 2),    // grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // brown
},
```

### #1147 SPECIES_FURFROU_STAR
```c
[SPECIES_FURFROU_STAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #1148 SPECIES_FURFROU_DIAMOND
```c
[SPECIES_FURFROU_DIAMOND] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 2),    // light grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // brown
},
```

### #1149 SPECIES_FURFROU_DEBUTANTE
```c
[SPECIES_FURFROU_DEBUTANTE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // light grey
    PALe(5, 1),    // grey
},
```

### #1150 SPECIES_FURFROU_MATRON
```c
[SPECIES_FURFROU_MATRON] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // light grey
    PALc(4, 2),    // grey
    PALd(6, 2),    // purple
    PALe(8, 1),    // dark grey
},
```

### #1151 SPECIES_FURFROU_DANDY
```c
[SPECIES_FURFROU_DANDY] = {
    PALa(1, 1),    // light grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // grey
    PALd(4, 2),    // light grey
    PALe(6, 4),    // dark grey
},
```

### #1152 SPECIES_FURFROU_LA_REINE
```c
// Graphics not found
```

### #1153 SPECIES_FURFROU_KABUKI
```c
[SPECIES_FURFROU_KABUKI] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // light grey
    PALc(6, 1),    // dark grey
    PALd(7, 2),    // dark brown
    PALe(9, 1),    // blue
},
```

### #1154 SPECIES_FURFROU_PHARAOH
```c
[SPECIES_FURFROU_PHARAOH] = {
    PALa(1, 1),    // dark grey
    PALb(2, 4),    // light grey
    PALc(6, 1),    // black
    PALd(7, 1),    // blue
    PALe(8, 1),    // dark grey
},
```

### #1155 SPECIES_MEOWSTIC_F
```c
[SPECIES_MEOWSTIC_F] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // black
    PALc(3, 1),    // white
    PALd(4, 1),    // light grey
    PALe(5, 1),    // black
},
```

### #1156 SPECIES_AEGISLASH_BLADE
```c
[SPECIES_AEGISLASH_BLADE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 2),    // grey
},
```

### #1157 SPECIES_PUMPKABOO_SMALL
```c
// Graphics not found
```

### #1158 SPECIES_PUMPKABOO_LARGE
```c
// Graphics not found
```

### #1159 SPECIES_PUMPKABOO_SUPER
```c
// Graphics not found
```

### #1160 SPECIES_GOURGEIST_SMALL
```c
// Graphics not found
```

### #1161 SPECIES_GOURGEIST_LARGE
```c
// Graphics not found
```

### #1162 SPECIES_GOURGEIST_SUPER
```c
// Graphics not found
```

### #1163 SPECIES_XERNEAS_ACTIVE
```c
[SPECIES_XERNEAS_ACTIVE] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // blue
    PALe(6, 2),    // yellow
},
```

### #1164 SPECIES_ZYGARDE_10_AURA_BREAK
```c
// Graphics not found
```

### #1165 SPECIES_ZYGARDE_10_POWER_CONSTRUCT
```c
// Graphics not found
```

### #1166 SPECIES_ZYGARDE_50_POWER_CONSTRUCT
```c
// Graphics not found
```

### #1167 SPECIES_ZYGARDE_COMPLETE
```c
[SPECIES_ZYGARDE_COMPLETE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // black
    PALd(5, 2),    // green
    PALe(7, 1),    // white
},
```

### #1168 SPECIES_HOOPA_UNBOUND
```c
[SPECIES_HOOPA_UNBOUND] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // black
    PALc(4, 1),    // white
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // purple
},
```

### #1169 SPECIES_ORICORIO_POM_POM
```c
// Graphics not found
```

### #1170 SPECIES_ORICORIO_PAU
```c
[SPECIES_ORICORIO_PAU] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #1171 SPECIES_ORICORIO_SENSU
```c
[SPECIES_ORICORIO_SENSU] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light cyan
    PALc(3, 1),    // cyan
    PALd(4, 2),    // purple
    PALe(6, 1),    // dark grey
},
```

### #1172 SPECIES_ROCKRUFF_OWN_TEMPO
```c
// Graphics not found
```

### #1173 SPECIES_LYCANROC_MIDNIGHT
```c
[SPECIES_LYCANROC_MIDNIGHT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // brown
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark brown
    PALe(6, 2),    // light grey
},
```

### #1174 SPECIES_LYCANROC_DUSK
```c
[SPECIES_LYCANROC_DUSK] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // brown
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // light grey
},
```

### #1175 SPECIES_WISHIWASHI_SCHOOL
```c
[SPECIES_WISHIWASHI_SCHOOL] = {
    PALa(1, 1),    // dark blue
    PALb(2, 3),    // cyan
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // cyan
    PALe(7, 2),    // blue
},
```

### #1176 SPECIES_SILVALLY_FIGHTING
```c
[SPECIES_SILVALLY_FIGHTING] = {
    PALa(1, 2),    // orange
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1177 SPECIES_SILVALLY_FLYING
```c
[SPECIES_SILVALLY_FLYING] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1178 SPECIES_SILVALLY_POISON
```c
[SPECIES_SILVALLY_POISON] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1179 SPECIES_SILVALLY_GROUND
```c
[SPECIES_SILVALLY_GROUND] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1180 SPECIES_SILVALLY_ROCK
```c
[SPECIES_SILVALLY_ROCK] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1181 SPECIES_SILVALLY_BUG
```c
[SPECIES_SILVALLY_BUG] = {
    PALa(1, 1),    // green
    PALb(2, 1),    // yellow
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1182 SPECIES_SILVALLY_GHOST
```c
[SPECIES_SILVALLY_GHOST] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // light purple
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1183 SPECIES_SILVALLY_STEEL
```c
[SPECIES_SILVALLY_STEEL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1184 SPECIES_SILVALLY_FIRE
```c
[SPECIES_SILVALLY_FIRE] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // red
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1185 SPECIES_SILVALLY_WATER
```c
[SPECIES_SILVALLY_WATER] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1186 SPECIES_SILVALLY_GRASS
```c
[SPECIES_SILVALLY_GRASS] = {
    PALa(1, 2),    // green
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1187 SPECIES_SILVALLY_ELECTRIC
```c
[SPECIES_SILVALLY_ELECTRIC] = {
    PALa(1, 2),    // orange
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1188 SPECIES_SILVALLY_PSYCHIC
```c
[SPECIES_SILVALLY_PSYCHIC] = {
    PALa(1, 2),    // purple
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1189 SPECIES_SILVALLY_ICE
```c
[SPECIES_SILVALLY_ICE] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // light cyan
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1190 SPECIES_SILVALLY_DRAGON
```c
[SPECIES_SILVALLY_DRAGON] = {
    PALa(1, 2),    // cyan
    PALb(3, 1),    // grey
    PALc(4, 3),    // light grey
    PALd(7, 1),    // dark grey
    PALe(8, 1),    // red
},
```

### #1191 SPECIES_SILVALLY_DARK
```c
[SPECIES_SILVALLY_DARK] = {
    PALa(1, 3),    // dark grey
    PALb(4, 3),    // light grey
    PALc(7, 1),    // dark grey
    PALd(8, 1),    // red
    PALe(9, 2),    // dark grey
},
```

### #1192 SPECIES_SILVALLY_FAIRY
```c
[SPECIES_SILVALLY_FAIRY] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // light pink
    PALc(3, 1),    // grey
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1193 SPECIES_MINIOR_METEOR_ORANGE
```c
// Graphics not found
```

### #1194 SPECIES_MINIOR_METEOR_YELLOW
```c
// Graphics not found
```

### #1195 SPECIES_MINIOR_METEOR_GREEN
```c
// Graphics not found
```

### #1196 SPECIES_MINIOR_METEOR_BLUE
```c
// Graphics not found
```

### #1197 SPECIES_MINIOR_METEOR_INDIGO
```c
// Graphics not found
```

### #1198 SPECIES_MINIOR_METEOR_VIOLET
```c
// Graphics not found
```

### #1199 SPECIES_MINIOR_CORE_RED
```c
[SPECIES_MINIOR_CORE_RED] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 2),    // purple
    PALe(6, 5),    // red
},
```

### #1200 SPECIES_MINIOR_CORE_ORANGE
```c
[SPECIES_MINIOR_CORE_ORANGE] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 6),    // orange
},
```


## Pokémon #1201-1300

### #1201 SPECIES_MINIOR_CORE_YELLOW
```c
[SPECIES_MINIOR_CORE_YELLOW] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 6),    // yellow
},
```

### #1202 SPECIES_MINIOR_CORE_GREEN
```c
[SPECIES_MINIOR_CORE_GREEN] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // yellow
    PALe(5, 6),    // green
},
```

### #1203 SPECIES_MINIOR_CORE_BLUE
```c
[SPECIES_MINIOR_CORE_BLUE] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 7),    // white
    PALe(11, 5),    // black
},
```

### #1204 SPECIES_MINIOR_CORE_INDIGO
```c
[SPECIES_MINIOR_CORE_INDIGO] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // cyan
    PALe(5, 6),    // cyan
},
```

### #1205 SPECIES_MINIOR_CORE_VIOLET
```c
[SPECIES_MINIOR_CORE_VIOLET] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // white
    PALe(5, 6),    // purple
},
```

### #1206 SPECIES_MIMIKYU_BUSTED
```c
[SPECIES_MIMIKYU_BUSTED] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // grey
},
```

### #1207 SPECIES_NECROZMA_DUSK_MANE
```c
// Graphics not found
```

### #1208 SPECIES_NECROZMA_DAWN_WINGS
```c
// Graphics not found
```

### #1209 SPECIES_NECROZMA_ULTRA
```c
[SPECIES_NECROZMA_ULTRA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // yellow
    PALe(5, 2),    // orange
},
```

### #1210 SPECIES_MAGEARNA_ORIGINAL
```c
// Graphics not found
```

### #1211 SPECIES_CRAMORANT_GULPING
```c
[SPECIES_CRAMORANT_GULPING] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 2),    // brown
    PALe(6, 1),    // dark blue
},
```

### #1212 SPECIES_CRAMORANT_GORGING
```c
[SPECIES_CRAMORANT_GORGING] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // yellow
    PALd(4, 1),    // brown
    PALe(5, 1),    // dark blue
},
```

### #1213 SPECIES_TOXTRICITY_LOW_KEY
```c
// Graphics not found
```

### #1214 SPECIES_SINISTEA_ANTIQUE
```c
// Graphics not found
```

### #1215 SPECIES_POLTEAGEIST_ANTIQUE
```c
// Graphics not found
```

### #1216 SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM
```c
// Graphics not found
```

### #1217 SPECIES_ALCREMIE_STRAWBERRY_MATCHA_CREAM
```c
// Graphics not found
```

### #1218 SPECIES_ALCREMIE_STRAWBERRY_MINT_CREAM
```c
// Graphics not found
```

### #1219 SPECIES_ALCREMIE_STRAWBERRY_LEMON_CREAM
```c
// Graphics not found
```

### #1220 SPECIES_ALCREMIE_STRAWBERRY_SALTED_CREAM
```c
// Graphics not found
```

### #1221 SPECIES_ALCREMIE_STRAWBERRY_RUBY_SWIRL
```c
// Graphics not found
```

### #1222 SPECIES_ALCREMIE_STRAWBERRY_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1223 SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1224 SPECIES_EISCUE_NOICE
```c
// Graphics not found
```

### #1225 SPECIES_INDEEDEE_F
```c
[SPECIES_INDEEDEE_F] = {
    PALa(1, 1),    // black
    PALb(2, 3),    // grey
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // purple
    PALe(8, 1),    // white
},
```

### #1226 SPECIES_MORPEKO_HANGRY
```c
[SPECIES_MORPEKO_HANGRY] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // blue
    PALd(5, 1),    // blue
    PALe(6, 1),    // dark grey
},
```

### #1227 SPECIES_ZACIAN_CROWNED
```c
// Graphics not found
```

### #1228 SPECIES_ZAMAZENTA_CROWNED
```c
// Graphics not found
```

### #1229 SPECIES_ETERNATUS_ETERNAMAX
```c
[SPECIES_ETERNATUS_ETERNAMAX] = {
    PALa(1, 3),    // dark blue
    PALb(4, 1),    // purple
    PALc(5, 1),    // purple
    PALd(6, 1),    // white
    PALe(7, 2),    // brown
},
```

### #1230 SPECIES_URSHIFU_RAPID_STRIKE
```c
// Graphics not found
```

### #1231 SPECIES_ZARUDE_DADA
```c
[SPECIES_ZARUDE_DADA] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark grey
    PALc(5, 1),    // white
    PALd(6, 3),    // light grey
    PALe(9, 1),    // red
},
```

### #1232 SPECIES_CALYREX_ICE
```c
[SPECIES_CALYREX_ICE] = {
    PALa(1, 1),    // light grey
    PALb(2, 2),    // black
    PALc(4, 1),    // grey
    PALd(5, 1),    // light cyan
    PALe(6, 1),    // dark green
},
```

### #1233 SPECIES_CALYREX_SHADOW
```c
[SPECIES_CALYREX_SHADOW] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark green
    PALd(4, 1),    // grey
    PALe(5, 1),    // light grey
},
```

### #1234 SPECIES_BASCULEGION_F
```c
[SPECIES_BASCULEGION_F] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // cyan
},
```

### #1235 SPECIES_ALCREMIE_BERRY_VANILLA_CREAM
```c
// Graphics not found
```

### #1236 SPECIES_ALCREMIE_BERRY_RUBY_CREAM
```c
// Graphics not found
```

### #1237 SPECIES_ALCREMIE_BERRY_MATCHA_CREAM
```c
// Graphics not found
```

### #1238 SPECIES_ALCREMIE_BERRY_MINT_CREAM
```c
// Graphics not found
```

### #1239 SPECIES_ALCREMIE_BERRY_LEMON_CREAM
```c
// Graphics not found
```

### #1240 SPECIES_ALCREMIE_BERRY_SALTED_CREAM
```c
// Graphics not found
```

### #1241 SPECIES_ALCREMIE_BERRY_RUBY_SWIRL
```c
// Graphics not found
```

### #1242 SPECIES_ALCREMIE_BERRY_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1243 SPECIES_ALCREMIE_BERRY_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1244 SPECIES_ALCREMIE_LOVE_VANILLA_CREAM
```c
// Graphics not found
```

### #1245 SPECIES_ALCREMIE_LOVE_RUBY_CREAM
```c
// Graphics not found
```

### #1246 SPECIES_ALCREMIE_LOVE_MATCHA_CREAM
```c
// Graphics not found
```

### #1247 SPECIES_ALCREMIE_LOVE_MINT_CREAM
```c
// Graphics not found
```

### #1248 SPECIES_ALCREMIE_LOVE_LEMON_CREAM
```c
// Graphics not found
```

### #1249 SPECIES_ALCREMIE_LOVE_SALTED_CREAM
```c
// Graphics not found
```

### #1250 SPECIES_ALCREMIE_LOVE_RUBY_SWIRL
```c
// Graphics not found
```

### #1251 SPECIES_ALCREMIE_LOVE_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1252 SPECIES_ALCREMIE_LOVE_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1253 SPECIES_ALCREMIE_STAR_VANILLA_CREAM
```c
// Graphics not found
```

### #1254 SPECIES_ALCREMIE_STAR_RUBY_CREAM
```c
// Graphics not found
```

### #1255 SPECIES_ALCREMIE_STAR_MATCHA_CREAM
```c
// Graphics not found
```

### #1256 SPECIES_ALCREMIE_STAR_MINT_CREAM
```c
// Graphics not found
```

### #1257 SPECIES_ALCREMIE_STAR_LEMON_CREAM
```c
// Graphics not found
```

### #1258 SPECIES_ALCREMIE_STAR_SALTED_CREAM
```c
// Graphics not found
```

### #1259 SPECIES_ALCREMIE_STAR_RUBY_SWIRL
```c
// Graphics not found
```

### #1260 SPECIES_ALCREMIE_STAR_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1261 SPECIES_ALCREMIE_STAR_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1262 SPECIES_ALCREMIE_CLOVER_VANILLA_CREAM
```c
// Graphics not found
```

### #1263 SPECIES_ALCREMIE_CLOVER_RUBY_CREAM
```c
// Graphics not found
```

### #1264 SPECIES_ALCREMIE_CLOVER_MATCHA_CREAM
```c
// Graphics not found
```

### #1265 SPECIES_ALCREMIE_CLOVER_MINT_CREAM
```c
// Graphics not found
```

### #1266 SPECIES_ALCREMIE_CLOVER_LEMON_CREAM
```c
// Graphics not found
```

### #1267 SPECIES_ALCREMIE_CLOVER_SALTED_CREAM
```c
// Graphics not found
```

### #1268 SPECIES_ALCREMIE_CLOVER_RUBY_SWIRL
```c
// Graphics not found
```

### #1269 SPECIES_ALCREMIE_CLOVER_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1270 SPECIES_ALCREMIE_CLOVER_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1271 SPECIES_ALCREMIE_FLOWER_VANILLA_CREAM
```c
// Graphics not found
```

### #1272 SPECIES_ALCREMIE_FLOWER_RUBY_CREAM
```c
// Graphics not found
```

### #1273 SPECIES_ALCREMIE_FLOWER_MATCHA_CREAM
```c
// Graphics not found
```

### #1274 SPECIES_ALCREMIE_FLOWER_MINT_CREAM
```c
// Graphics not found
```

### #1275 SPECIES_ALCREMIE_FLOWER_LEMON_CREAM
```c
// Graphics not found
```

### #1276 SPECIES_ALCREMIE_FLOWER_SALTED_CREAM
```c
// Graphics not found
```

### #1277 SPECIES_ALCREMIE_FLOWER_RUBY_SWIRL
```c
// Graphics not found
```

### #1278 SPECIES_ALCREMIE_FLOWER_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1279 SPECIES_ALCREMIE_FLOWER_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1280 SPECIES_ALCREMIE_RIBBON_VANILLA_CREAM
```c
// Graphics not found
```

### #1281 SPECIES_ALCREMIE_RIBBON_RUBY_CREAM
```c
// Graphics not found
```

### #1282 SPECIES_ALCREMIE_RIBBON_MATCHA_CREAM
```c
// Graphics not found
```

### #1283 SPECIES_ALCREMIE_RIBBON_MINT_CREAM
```c
// Graphics not found
```

### #1284 SPECIES_ALCREMIE_RIBBON_LEMON_CREAM
```c
// Graphics not found
```

### #1285 SPECIES_ALCREMIE_RIBBON_SALTED_CREAM
```c
// Graphics not found
```

### #1286 SPECIES_ALCREMIE_RIBBON_RUBY_SWIRL
```c
// Graphics not found
```

### #1287 SPECIES_ALCREMIE_RIBBON_CARAMEL_SWIRL
```c
// Graphics not found
```

### #1288 SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL
```c
// Graphics not found
```

### #1289 SPECIES_SPRIGATITO
```c
[SPECIES_SPRIGATITO] = {
    PALa(1, 1),    // black
    PALb(2, 2),    // green
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // green
    PALe(6, 1),    // white
},
```

### #1290 SPECIES_FLORAGATO
```c
[SPECIES_FLORAGATO] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // white
    PALd(6, 1),    // dark grey
    PALe(7, 2),    // grey
},
```

### #1291 SPECIES_MEOWSCARADA
```c
[SPECIES_MEOWSCARADA] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // dark grey
    PALd(5, 2),    // dark grey
    PALe(7, 1),    // purple
},
```

### #1292 SPECIES_FUECOCO
```c
[SPECIES_FUECOCO] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // yellow
    PALc(4, 2),    // dark brown
    PALd(6, 1),    // orange
    PALe(7, 1),    // white
},
```

### #1293 SPECIES_CROCALOR
```c
[SPECIES_CROCALOR] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // yellow
    PALc(4, 1),    // white
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #1294 SPECIES_SKELEDIRGE
```c
[SPECIES_SKELEDIRGE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // red
    PALc(3, 1),    // light grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // light grey
},
```

### #1295 SPECIES_QUAXLY
```c
[SPECIES_QUAXLY] = {
    PALa(1, 4),    // dark blue
    PALb(5, 1),    // white
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // light cyan
    PALe(8, 1),    // cyan
},
```

### #1296 SPECIES_QUAXWELL
```c
[SPECIES_QUAXWELL] = {
    PALa(1, 1),    // dark blue
    PALb(2, 2),    // blue
    PALc(4, 2),    // blue
    PALd(6, 1),    // cyan
    PALe(7, 1),    // dark grey
},
```

### #1297 SPECIES_QUAQUAVAL
```c
[SPECIES_QUAQUAVAL] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // cyan
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // white
    PALe(6, 1),    // white
},
```

### #1298 SPECIES_LECHONK
```c
[SPECIES_LECHONK] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // dark grey
    PALc(6, 1),    // orange
    PALd(7, 1),    // brown
    PALe(8, 1),    // white
},
```

### #1299 SPECIES_OINKOLOGNE_M
```c
// Graphics not found
```

### #1300 SPECIES_OINKOLOGNE_F
```c
[SPECIES_OINKOLOGNE_F] = {
    PALa(1, 6),    // dark grey
    PALb(7, 3),    // grey
    PALc(10, 1),    // light grey
    PALd(11, 1),    // purple
    PALe(12, 1),    // dark grey
},
```


## Pokémon #1301-1400

### #1301 SPECIES_TAROUNTULA
```c
[SPECIES_TAROUNTULA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // dark brown
},
```

### #1302 SPECIES_SPIDOPS
```c
[SPECIES_SPIDOPS] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // green
    PALc(3, 1),    // white
    PALd(4, 1),    // dark brown
    PALe(5, 1),    // dark grey
},
```

### #1303 SPECIES_NYMBLE
```c
[SPECIES_NYMBLE] = {
    PALa(1, 2),    // grey
    PALb(3, 2),    // blue
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // light grey
    PALe(8, 3),    // brown
},
```

### #1304 SPECIES_LOKIX
```c
[SPECIES_LOKIX] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // black
    PALe(6, 3),    // grey
},
```

### #1305 SPECIES_PAWMI
```c
[SPECIES_PAWMI] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // blue
    PALc(4, 2),    // brown
    PALd(6, 2),    // red
    PALe(8, 1),    // yellow
},
```

### #1306 SPECIES_PAWMO
```c
[SPECIES_PAWMO] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // blue
    PALc(4, 7),    // brown
    PALd(11, 1),    // dark grey
    PALe(12, 2),    // white
},
```

### #1307 SPECIES_PAWMOT
```c
[SPECIES_PAWMOT] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // orange
    PALd(6, 1),    // dark green
    PALe(7, 1),    // green
},
```

### #1308 SPECIES_TANDEMAUS
```c
[SPECIES_TANDEMAUS] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 1),    // dark grey
    PALe(5, 3),    // light grey
},
```

### #1309 SPECIES_MAUSHOLD_THREE
```c
// Graphics not found
```

### #1310 SPECIES_MAUSHOLD_FOUR
```c
// Graphics not found
```

### #1311 SPECIES_FIDOUGH
```c
[SPECIES_FIDOUGH] = {
    PALa(1, 2),    // grey
    PALb(3, 1),    // white
    PALc(4, 1),    // orange
    PALd(5, 1),    // yellow
    PALe(6, 2),    // dark brown
},
```

### #1312 SPECIES_DACHSBUN
```c
[SPECIES_DACHSBUN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // orange
    PALe(5, 2),    // dark grey
},
```

### #1313 SPECIES_SMOLIV
```c
[SPECIES_SMOLIV] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // grey
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // dark green
    PALe(7, 4),    // green
},
```

### #1314 SPECIES_DOLLIV
```c
[SPECIES_DOLLIV] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // green
    PALc(3, 2),    // black
    PALd(5, 3),    // yellow
    PALe(8, 1),    // dark grey
},
```

### #1315 SPECIES_ARBOLIVA
```c
[SPECIES_ARBOLIVA] = {
    PALa(1, 2),    // dark green
    PALb(3, 2),    // green
    PALc(5, 1),    // dark grey
    PALd(6, 1),    // green
    PALe(7, 2),    // dark brown
},
```

### #1316 SPECIES_SQUAWKABILLY_GREEN
```c
// Graphics not found
```

### #1317 SPECIES_SQUAWKABILLY_BLUE
```c
[SPECIES_SQUAWKABILLY_BLUE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // cyan
    PALd(5, 1),    // dark blue
    PALe(6, 1),    // light grey
},
```

### #1318 SPECIES_SQUAWKABILLY_YELLOW
```c
[SPECIES_SQUAWKABILLY_YELLOW] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // yellow
    PALd(5, 1),    // brown
    PALe(6, 1),    // light grey
},
```

### #1319 SPECIES_SQUAWKABILLY_WHITE
```c
[SPECIES_SQUAWKABILLY_WHITE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // light grey
    PALd(5, 1),    // grey
    PALe(6, 2),    // light grey
},
```

### #1320 SPECIES_NACLI
```c
[SPECIES_NACLI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // brown
    PALd(4, 3),    // light grey
    PALe(7, 1),    // dark grey
},
```

### #1321 SPECIES_NACLSTACK
```c
[SPECIES_NACLSTACK] = {
    PALa(1, 4),    // grey
    PALb(5, 2),    // light grey
    PALc(7, 1),    // white
    PALd(8, 2),    // grey
    PALe(10, 1),    // grey
},
```

### #1322 SPECIES_GARGANACL
```c
[SPECIES_GARGANACL] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // white
    PALd(4, 4),    // grey
    PALe(8, 3),    // dark grey
},
```

### #1323 SPECIES_CHARCADET
```c
[SPECIES_CHARCADET] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // blue
    PALc(3, 1),    // purple
    PALd(4, 3),    // dark brown
    PALe(7, 1),    // dark grey
},
```

### #1324 SPECIES_ARMAROUGE
```c
[SPECIES_ARMAROUGE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // red
    PALc(3, 1),    // purple
    PALd(4, 1),    // yellow
    PALe(5, 1),    // orange
},
```

### #1325 SPECIES_CERULEDGE
```c
[SPECIES_CERULEDGE] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // light purple
    PALc(3, 1),    // cyan
    PALd(4, 1),    // white
    PALe(5, 1),    // blue
},
```

### #1326 SPECIES_TADBULB
```c
[SPECIES_TADBULB] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // yellow
    PALd(4, 1),    // yellow
    PALe(5, 1),    // white
},
```

### #1327 SPECIES_BELLIBOLT
```c
[SPECIES_BELLIBOLT] = {
    PALa(1, 2),    // red
    PALb(3, 1),    // orange
    PALc(4, 1),    // grey
    PALd(5, 1),    // yellow
    PALe(6, 1),    // white
},
```

### #1328 SPECIES_WATTREL
```c
[SPECIES_WATTREL] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // white
    PALc(5, 1),    // light grey
    PALd(6, 1),    // dark grey
    PALe(7, 1),    // yellow
},
```

### #1329 SPECIES_KILOWATTREL
```c
[SPECIES_KILOWATTREL] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // yellow
    PALc(5, 1),    // orange
    PALd(6, 1),    // white
    PALe(7, 2),    // dark grey
},
```

### #1330 SPECIES_MASCHIFF
```c
[SPECIES_MASCHIFF] = {
    PALa(1, 8),    // dark grey
    PALb(9, 1),    // brown
    PALc(10, 1),    // orange
    PALd(11, 1),    // yellow
    PALe(12, 1),    // dark grey
},
```

### #1331 SPECIES_MABOSSTIFF
```c
[SPECIES_MABOSSTIFF] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // light grey
    PALc(3, 1),    // grey
    PALd(4, 1),    // light grey
    PALe(5, 4),    // dark grey
},
```

### #1332 SPECIES_SHROODLE
```c
[SPECIES_SHROODLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // grey
    PALe(5, 3),    // grey
},
```

### #1333 SPECIES_GRAFAIAI
```c
[SPECIES_GRAFAIAI] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 2),    // dark grey
},
```

### #1334 SPECIES_BRAMBLIN
```c
[SPECIES_BRAMBLIN] = {
    PALa(1, 2),    // brown
    PALb(3, 2),    // grey
    PALc(5, 1),    // brown
    PALd(6, 1),    // dark grey
    PALe(7, 3),    // orange
},
```

### #1335 SPECIES_BRAMBLEGHAST
```c
[SPECIES_BRAMBLEGHAST] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 3),    // brown
    PALd(6, 1),    // grey
    PALe(7, 6),    // orange
},
```

### #1336 SPECIES_TOEDSCOOL
```c
[SPECIES_TOEDSCOOL] = {
    PALa(1, 1),    // brown
    PALb(2, 3),    // pink
    PALc(5, 1),    // brown
    PALd(6, 2),    // orange
    PALe(8, 1),    // dark grey
},
```

### #1337 SPECIES_TOEDSCRUEL
```c
[SPECIES_TOEDSCRUEL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // grey
    PALc(4, 1),    // grey
    PALd(5, 2),    // yellow
    PALe(7, 1),    // dark grey
},
```

### #1338 SPECIES_KLAWF
```c
[SPECIES_KLAWF] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark brown
    PALc(4, 1),    // white
    PALd(5, 1),    // light grey
    PALe(6, 1),    // dark grey
},
```

### #1339 SPECIES_CAPSAKID
```c
[SPECIES_CAPSAKID] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // green
    PALe(5, 1),    // light grey
},
```

### #1340 SPECIES_SCOVILLAIN
```c
[SPECIES_SCOVILLAIN] = {
    PALa(1, 1),    // dark green
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // green
    PALd(5, 1),    // dark brown
    PALe(6, 1),    // black
},
```

### #1341 SPECIES_RELLOR
```c
[SPECIES_RELLOR] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // light grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // orange
},
```

### #1342 SPECIES_RABSCA
```c
[SPECIES_RABSCA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark blue
    PALd(4, 1),    // red
    PALe(5, 1),    // white
},
```

### #1343 SPECIES_FLITTLE
```c
[SPECIES_FLITTLE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // brown
    PALe(5, 1),    // yellow
},
```

### #1344 SPECIES_ESPATHRA
```c
[SPECIES_ESPATHRA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // cyan
},
```

### #1345 SPECIES_TINKATINK
```c
[SPECIES_TINKATINK] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // light grey
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // purple
},
```

### #1346 SPECIES_TINKATUFF
```c
[SPECIES_TINKATUFF] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // light grey
    PALc(3, 1),    // purple
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // black
},
```

### #1347 SPECIES_TINKATON
```c
[SPECIES_TINKATON] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // light grey
    PALc(3, 1),    // purple
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // white
},
```

### #1348 SPECIES_WIGLETT
```c
[SPECIES_WIGLETT] = {
    PALa(1, 1),    // grey
    PALb(2, 3),    // light grey
    PALc(5, 1),    // dark grey
    PALd(6, 2),    // brown
    PALe(8, 2),    // purple
},
```

### #1349 SPECIES_WUGTRIO
```c
[SPECIES_WUGTRIO] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // white
    PALe(5, 1),    // red
},
```

### #1350 SPECIES_BOMBIRDIER
```c
[SPECIES_BOMBIRDIER] = {
    PALa(1, 6),    // dark grey
    PALb(7, 1),    // red
    PALc(8, 2),    // grey
    PALd(10, 1),    // dark grey
    PALe(11, 2),    // light grey
},
```

### #1351 SPECIES_FINIZEN
```c
[SPECIES_FINIZEN] = {
    PALa(1, 1),    // blue
    PALb(2, 2),    // cyan
    PALc(4, 1),    // cyan
    PALd(5, 2),    // light grey
    PALe(7, 1),    // cyan
},
```

### #1352 SPECIES_PALAFIN_ZERO
```c
// Graphics not found
```

### #1353 SPECIES_PALAFIN_HERO
```c
[SPECIES_PALAFIN_HERO] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // cyan
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // dark blue
},
```

### #1354 SPECIES_VAROOM
```c
[SPECIES_VAROOM] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // light grey
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // grey
    PALe(8, 1),    // light grey
},
```

### #1355 SPECIES_REVAVROOM
```c
[SPECIES_REVAVROOM] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 2),    // dark grey
    PALd(7, 3),    // grey
    PALe(10, 1),    // purple
},
```

### #1356 SPECIES_CYCLIZAR
```c
[SPECIES_CYCLIZAR] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // orange
},
```

### #1357 SPECIES_ORTHWORM
```c
[SPECIES_ORTHWORM] = {
    PALa(1, 1),    // brown
    PALb(2, 2),    // red
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // purple
    PALe(6, 1),    // grey
},
```

### #1358 SPECIES_GLIMMET
```c
[SPECIES_GLIMMET] = {
    PALa(1, 2),    // blue
    PALb(3, 1),    // cyan
    PALc(4, 1),    // blue
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // blue
},
```

### #1359 SPECIES_GLIMMORA
```c
[SPECIES_GLIMMORA] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // cyan
    PALd(4, 1),    // blue
    PALe(5, 1),    // black
},
```

### #1360 SPECIES_GREAVARD
```c
[SPECIES_GREAVARD] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // red
    PALc(5, 1),    // yellow
    PALd(6, 1),    // blue
    PALe(7, 1),    // purple
},
```

### #1361 SPECIES_HOUNDSTONE
```c
[SPECIES_HOUNDSTONE] = {
    PALa(1, 5),    // grey
    PALb(6, 1),    // dark grey
    PALc(7, 6),    // light grey
    PALd(13, 3),    // black
},
```

### #1362 SPECIES_FLAMIGO
```c
[SPECIES_FLAMIGO] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // red
    PALc(3, 2),    // light grey
    PALd(5, 1),    // purple
    PALe(6, 2),    // dark grey
},
```

### #1363 SPECIES_CETODDLE
```c
[SPECIES_CETODDLE] = {
    PALa(1, 2),    // grey
    PALb(3, 3),    // light grey
    PALc(6, 1),    // purple
    PALd(7, 1),    // grey
    PALe(8, 1),    // white
},
```

### #1364 SPECIES_CETITAN
```c
[SPECIES_CETITAN] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // white
    PALc(3, 1),    // grey
    PALd(4, 2),    // purple
    PALe(6, 2),    // purple
},
```

### #1365 SPECIES_VELUZA
```c
[SPECIES_VELUZA] = {
    PALa(1, 1),    // blue
    PALb(2, 1),    // light purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // purple
    PALe(5, 2),    // grey
},
```

### #1366 SPECIES_DONDOZO
```c
[SPECIES_DONDOZO] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // dark blue
    PALe(6, 1),    // cyan
},
```

### #1367 SPECIES_TATSUGIRI_CURLY
```c
// Graphics not found
```

### #1368 SPECIES_TATSUGIRI_DROOPY
```c
[SPECIES_TATSUGIRI_DROOPY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // red
    PALc(4, 1),    // red
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // grey
},
```

### #1369 SPECIES_TATSUGIRI_STRETCHY
```c
[SPECIES_TATSUGIRI_STRETCHY] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // yellow
    PALd(4, 1),    // orange
    PALe(5, 1),    // dark grey
},
```

### #1370 SPECIES_ANNIHILAPE
```c
[SPECIES_ANNIHILAPE] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 2),    // light grey
},
```

### #1371 SPECIES_CLODSIRE
```c
[SPECIES_CLODSIRE] = {
    PALa(1, 1),    // purple
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 2),    // light grey
    PALe(6, 7),    // grey
},
```

### #1372 SPECIES_FARIGIRAF
```c
[SPECIES_FARIGIRAF] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // dark grey
    PALc(4, 2),    // brown
    PALd(6, 1),    // yellow
    PALe(7, 1),    // yellow
},
```

### #1373 SPECIES_DUDUNSPARCE_TWO_SEGMENT
```c
// Graphics not found
```

### #1374 SPECIES_DUDUNSPARCE_THREE_SEGMENT
```c
// Graphics not found
```

### #1375 SPECIES_KINGAMBIT
```c
[SPECIES_KINGAMBIT] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // brown
},
```

### #1376 SPECIES_GREAT_TUSK
```c
[SPECIES_GREAT_TUSK] = {
    PALa(1, 4),    // black
    PALb(5, 2),    // red
    PALc(7, 1),    // brown
    PALd(8, 1),    // red
    PALe(9, 1),    // yellow
},
```

### #1377 SPECIES_SCREAM_TAIL
```c
[SPECIES_SCREAM_TAIL] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light pink
    PALc(4, 1),    // dark brown
    PALd(5, 2),    // light pink
    PALe(7, 1),    // dark grey
},
```

### #1378 SPECIES_BRUTE_BONNET
```c
[SPECIES_BRUTE_BONNET] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 1),    // grey
    PALd(4, 1),    // red
    PALe(5, 1),    // light grey
},
```

### #1379 SPECIES_FLUTTER_MANE
```c
[SPECIES_FLUTTER_MANE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // purple
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // purple
    PALe(5, 1),    // dark brown
},
```

### #1380 SPECIES_SLITHER_WING
```c
[SPECIES_SLITHER_WING] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // orange
    PALc(3, 1),    // yellow
    PALd(4, 1),    // yellow
    PALe(5, 1),    // dark grey
},
```

### #1381 SPECIES_SANDY_SHOCKS
```c
[SPECIES_SANDY_SHOCKS] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // grey
    PALc(5, 1),    // red
    PALd(6, 1),    // light grey
    PALe(7, 1),    // grey
},
```

### #1382 SPECIES_IRON_TREADS
```c
[SPECIES_IRON_TREADS] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // dark brown
    PALc(5, 3),    // dark grey
    PALd(8, 1),    // dark red
    PALe(9, 2),    // red
},
```

### #1383 SPECIES_IRON_BUNDLE
```c
[SPECIES_IRON_BUNDLE] = {
    PALa(1, 2),    // dark grey
    PALb(3, 1),    // grey
    PALc(4, 4),    // dark brown
    PALd(8, 1),    // yellow
    PALe(9, 1),    // blue
},
```

### #1384 SPECIES_IRON_HANDS
```c
[SPECIES_IRON_HANDS] = {
    PALa(1, 5),    // dark grey
    PALb(6, 3),    // brown
    PALc(9, 2),    // grey
    PALd(11, 1),    // dark grey
    PALe(12, 3),    // light grey
},
```

### #1385 SPECIES_IRON_JUGULIS
```c
[SPECIES_IRON_JUGULIS] = {
    PALa(1, 4),    // dark grey
    PALb(5, 5),    // dark brown
    PALc(10, 1),    // blue
    PALd(11, 3),    // purple
    PALe(14, 1),    // dark grey
},
```

### #1386 SPECIES_IRON_MOTH
```c
[SPECIES_IRON_MOTH] = {
    PALa(1, 4),    // dark grey
    PALb(5, 2),    // dark brown
    PALc(7, 2),    // orange
    PALd(9, 1),    // orange
    PALe(10, 1),    // yellow
},
```

### #1387 SPECIES_IRON_THORNS
```c
[SPECIES_IRON_THORNS] = {
    PALa(1, 8),    // dark grey
    PALb(9, 1),    // green
    PALc(10, 2),    // green
    PALd(12, 1),    // green
    PALe(13, 1),    // dark grey
},
```

### #1388 SPECIES_FRIGIBAX
```c
[SPECIES_FRIGIBAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 4),    // brown
    PALc(6, 3),    // grey
    PALd(9, 1),    // dark grey
    PALe(10, 4),    // cyan
},
```

### #1389 SPECIES_ARCTIBAX
```c
[SPECIES_ARCTIBAX] = {
    PALa(1, 5),    // dark brown
    PALb(6, 2),    // orange
    PALc(8, 3),    // grey
    PALd(11, 1),    // dark grey
    PALe(12, 3),    // light cyan
},
```

### #1390 SPECIES_BAXCALIBUR
```c
[SPECIES_BAXCALIBUR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 2),    // light grey
    PALd(5, 2),    // dark grey
    PALe(7, 1),    // cyan
},
```

### #1391 SPECIES_GIMMIGHOUL_CHEST
```c
// Graphics not found
```

### #1392 SPECIES_GIMMIGHOUL_ROAMING
```c
[SPECIES_GIMMIGHOUL_ROAMING] = {
    PALa(1, 3),    // black
    PALb(4, 1),    // grey
    PALc(5, 1),    // yellow
    PALd(6, 1),    // grey
    PALe(7, 1),    // dark grey
},
```

### #1393 SPECIES_GHOLDENGO
```c
[SPECIES_GHOLDENGO] = {
    PALa(1, 4),    // dark brown
    PALb(5, 7),    // dark brown
    PALc(12, 1),    // blue
    PALd(13, 1),    // dark grey
    PALe(14, 1),    // light grey
},
```

### #1394 SPECIES_WO_CHIEN
```c
[SPECIES_WO_CHIEN] = {
    PALa(1, 10),    // dark grey
    PALb(11, 1),    // orange
    PALc(12, 2),    // grey
    PALd(14, 1),    // dark grey
    PALe(15, 1),    // white
},
```

### #1395 SPECIES_CHIEN_PAO
```c
[SPECIES_CHIEN_PAO] = {
    PALa(1, 2),    // blue
    PALb(3, 2),    // light grey
    PALc(5, 1),    // white
    PALd(6, 1),    // light grey
    PALe(7, 1),    // grey
},
```

### #1396 SPECIES_TING_LU
```c
[SPECIES_TING_LU] = {
    PALa(1, 5),    // dark grey
    PALb(6, 2),    // brown
    PALc(8, 1),    // red
    PALd(9, 3),    // brown
    PALe(12, 2),    // orange
},
```

### #1397 SPECIES_CHI_YU
```c
[SPECIES_CHI_YU] = {
    PALa(1, 3),    // black
    PALb(4, 1),    // dark grey
    PALc(5, 1),    // red
    PALd(6, 2),    // yellow
    PALe(8, 1),    // dark brown
},
```

### #1398 SPECIES_ROARING_MOON
```c
[SPECIES_ROARING_MOON] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark blue
    PALc(5, 2),    // brown
    PALd(7, 1),    // yellow
    PALe(8, 1),    // purple
},
```

### #1399 SPECIES_IRON_VALIANT
```c
[SPECIES_IRON_VALIANT] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // red
    PALc(5, 3),    // grey
    PALd(8, 1),    // purple
    PALe(9, 3),    // blue
},
```

### #1400 SPECIES_KORAIDON
```c
[SPECIES_KORAIDON] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // grey
    PALc(5, 1),    // orange
    PALd(6, 2),    // brown
    PALe(8, 1),    // yellow
},
```


## Pokémon #1401-1500

### #1401 SPECIES_MIRAIDON
```c
[SPECIES_MIRAIDON] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // yellow
    PALc(5, 2),    // dark blue
    PALd(7, 2),    // blue
    PALe(9, 1),    // blue
},
```

### #1402 SPECIES_TAUROS_PALDEA_COMBAT
```c
// Graphics not found
```

### #1403 SPECIES_TAUROS_PALDEA_BLAZE
```c
// Graphics not found
```

### #1404 SPECIES_TAUROS_PALDEA_AQUA
```c
// Graphics not found
```

### #1405 SPECIES_WOOPER_PALDEA
```c
[SPECIES_WOOPER_PALDEA] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // purple
    PALc(3, 2),    // grey
    PALd(5, 1),    // dark grey
    PALe(6, 2),    // light grey
},
```

### #1406 SPECIES_WALKING_WAKE
```c
[SPECIES_WALKING_WAKE] = {
    PALa(1, 3),    // dark brown
    PALb(4, 1),    // red
    PALc(5, 1),    // orange
    PALd(6, 1),    // yellow
    PALe(7, 6),    // grey
},
```

### #1407 SPECIES_IRON_LEAVES
```c
[SPECIES_IRON_LEAVES] = {
    PALa(1, 5),    // black
    PALb(6, 1),    // red
    PALc(7, 1),    // red
    PALd(8, 2),    // grey
    PALe(10, 2),    // light grey
},
```

### #1408 SPECIES_DIPPLIN
```c
[SPECIES_DIPPLIN] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // black
    PALc(4, 3),    // dark brown
    PALd(7, 2),    // green
    PALe(9, 2),    // orange
},
```

### #1409 SPECIES_POLTCHAGEIST_COUNTERFEIT
```c
// Graphics not found
```

### #1410 SPECIES_POLTCHAGEIST_ARTISAN
```c
// Graphics not found
```

### #1411 SPECIES_SINISTCHA_UNREMARKABLE
```c
// Graphics not found
```

### #1412 SPECIES_SINISTCHA_MASTERPIECE
```c
// Graphics not found
```

### #1413 SPECIES_OKIDOGI
```c
[SPECIES_OKIDOGI] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // brown
    PALc(5, 2),    // dark brown
    PALd(7, 1),    // grey
    PALe(8, 1),    // green
},
```

### #1414 SPECIES_MUNKIDORI
```c
[SPECIES_MUNKIDORI] = {
    PALa(1, 3),    // dark grey
    PALb(4, 1),    // dark brown
    PALc(5, 1),    // blue
    PALd(6, 1),    // light cyan
    PALe(7, 1),    // purple
},
```

### #1415 SPECIES_FEZANDIPITI
```c
[SPECIES_FEZANDIPITI] = {
    PALa(1, 6),    // dark grey
    PALb(7, 1),    // red
    PALc(8, 1),    // grey
    PALd(9, 1),    // brown
    PALe(10, 1),    // yellow
},
```

### #1416 SPECIES_OGERPON_TEAL
```c
// Graphics not found
```

### #1417 SPECIES_OGERPON_WELLSPRING
```c
[SPECIES_OGERPON_WELLSPRING] = {
    PALa(1, 4),    // dark grey
    PALb(5, 1),    // green
    PALc(6, 1),    // orange
    PALd(7, 1),    // yellow
    PALe(8, 3),    // dark blue
},
```

### #1418 SPECIES_OGERPON_HEARTHFLAME
```c
[SPECIES_OGERPON_HEARTHFLAME] = {
    PALa(1, 2),    // dark grey
    PALb(3, 2),    // dark brown
    PALc(5, 1),    // dark brown
    PALd(6, 2),    // red
    PALe(8, 1),    // green
},
```

### #1419 SPECIES_OGERPON_CORNERSTONE
```c
[SPECIES_OGERPON_CORNERSTONE] = {
    PALa(1, 6),    // dark grey
    PALb(7, 2),    // green
    PALc(9, 1),    // orange
    PALd(10, 1),    // yellow
    PALe(11, 1),    // cyan
},
```

### #1420 SPECIES_OGERPON_TEAL_TERA
```c
// Graphics not found
```

### #1421 SPECIES_OGERPON_WELLSPRING_TERA
```c
// Graphics not found
```

### #1422 SPECIES_OGERPON_HEARTHFLAME_TERA
```c
// Graphics not found
```

### #1423 SPECIES_OGERPON_CORNERSTONE_TERA
```c
// Graphics not found
```

### #1424 SPECIES_URSALUNA_BLOODMOON
```c
[SPECIES_URSALUNA_BLOODMOON] = {
    PALa(1, 6),    // black
    PALb(7, 2),    // red
    PALc(9, 1),    // green
    PALd(10, 1),    // grey
    PALe(11, 1),    // purple
},
```

### #1425 SPECIES_ARCHALUDON
```c
[SPECIES_ARCHALUDON] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // brown
    PALd(5, 1),    // yellow
    PALe(6, 1),    // black
},
```

### #1426 SPECIES_HYDRAPPLE
```c
[SPECIES_HYDRAPPLE] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // dark brown
    PALc(3, 2),    // black
    PALd(5, 5),    // dark brown
    PALe(10, 1),    // green
},
```

### #1427 SPECIES_GOUGING_FIRE
```c
[SPECIES_GOUGING_FIRE] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // yellow
},
```

### #1428 SPECIES_RAGING_BOLT
```c
[SPECIES_RAGING_BOLT] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // dark blue
    PALd(5, 1),    // brown
    PALe(6, 1),    // white
},
```

### #1429 SPECIES_IRON_BOULDER
```c
[SPECIES_IRON_BOULDER] = {
    PALa(1, 6),    // dark grey
    PALb(7, 2),    // white
    PALc(9, 1),    // red
    PALd(10, 1),    // light grey
    PALe(11, 1),    // orange
},
```

### #1430 SPECIES_IRON_CROWN
```c
[SPECIES_IRON_CROWN] = {
    PALa(1, 1),    // cyan
    PALb(2, 1),    // cyan
    PALc(3, 1),    // white
    PALd(4, 1),    // dark grey
    PALe(5, 1),    // orange
},
```

### #1431 SPECIES_TERAPAGOS_NORMAL
```c
// Graphics not found
```

### #1432 SPECIES_TERAPAGOS_TERASTAL
```c
[SPECIES_TERAPAGOS_TERASTAL] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // red
    PALc(3, 1),    // yellow
    PALd(4, 3),    // dark blue
    PALe(7, 1),    // purple
},
```

### #1433 SPECIES_TERAPAGOS_STELLAR
```c
[SPECIES_TERAPAGOS_STELLAR] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // blue
    PALc(5, 2),    // purple
    PALd(7, 1),    // red
    PALe(8, 2),    // blue
},
```

### #1434 SPECIES_PECHARUNT
```c
[SPECIES_PECHARUNT] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // dark grey
    PALc(4, 1),    // purple
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // purple
},
```

### #1435 SPECIES_LUGIA_SHADOW
```c
// Graphics not found
```

### #1436 SPECIES_MOTHIM_SANDY
```c
// Graphics not found
```

### #1437 SPECIES_MOTHIM_TRASH
```c
// Graphics not found
```

### #1438 SPECIES_SCATTERBUG_POLAR
```c
// Graphics not found
```

### #1439 SPECIES_SCATTERBUG_TUNDRA
```c
// Graphics not found
```

### #1440 SPECIES_SCATTERBUG_CONTINENTAL
```c
// Graphics not found
```

### #1441 SPECIES_SCATTERBUG_GARDEN
```c
// Graphics not found
```

### #1442 SPECIES_SCATTERBUG_ELEGANT
```c
// Graphics not found
```

### #1443 SPECIES_SCATTERBUG_MEADOW
```c
// Graphics not found
```

### #1444 SPECIES_SCATTERBUG_MODERN
```c
// Graphics not found
```

### #1445 SPECIES_SCATTERBUG_MARINE
```c
// Graphics not found
```

### #1446 SPECIES_SCATTERBUG_ARCHIPELAGO
```c
// Graphics not found
```

### #1447 SPECIES_SCATTERBUG_HIGH_PLAINS
```c
// Graphics not found
```

### #1448 SPECIES_SCATTERBUG_SANDSTORM
```c
// Graphics not found
```

### #1449 SPECIES_SCATTERBUG_RIVER
```c
// Graphics not found
```

### #1450 SPECIES_SCATTERBUG_MONSOON
```c
// Graphics not found
```

### #1451 SPECIES_SCATTERBUG_SAVANNA
```c
// Graphics not found
```

### #1452 SPECIES_SCATTERBUG_SUN
```c
// Graphics not found
```

### #1453 SPECIES_SCATTERBUG_OCEAN
```c
// Graphics not found
```

### #1454 SPECIES_SCATTERBUG_JUNGLE
```c
// Graphics not found
```

### #1455 SPECIES_SCATTERBUG_FANCY
```c
// Graphics not found
```

### #1456 SPECIES_SCATTERBUG_POKEBALL
```c
// Graphics not found
```

### #1457 SPECIES_SPEWPA_POLAR
```c
// Graphics not found
```

### #1458 SPECIES_SPEWPA_TUNDRA
```c
// Graphics not found
```

### #1459 SPECIES_SPEWPA_CONTINENTAL
```c
// Graphics not found
```

### #1460 SPECIES_SPEWPA_GARDEN
```c
// Graphics not found
```

### #1461 SPECIES_SPEWPA_ELEGANT
```c
// Graphics not found
```

### #1462 SPECIES_SPEWPA_MEADOW
```c
// Graphics not found
```

### #1463 SPECIES_SPEWPA_MODERN
```c
// Graphics not found
```

### #1464 SPECIES_SPEWPA_MARINE
```c
// Graphics not found
```

### #1465 SPECIES_SPEWPA_ARCHIPELAGO
```c
// Graphics not found
```

### #1466 SPECIES_SPEWPA_HIGH_PLAINS
```c
// Graphics not found
```

### #1467 SPECIES_SPEWPA_SANDSTORM
```c
// Graphics not found
```

### #1468 SPECIES_SPEWPA_RIVER
```c
// Graphics not found
```

### #1469 SPECIES_SPEWPA_MONSOON
```c
// Graphics not found
```

### #1470 SPECIES_SPEWPA_SAVANNA
```c
// Graphics not found
```

### #1471 SPECIES_SPEWPA_SUN
```c
// Graphics not found
```

### #1472 SPECIES_SPEWPA_OCEAN
```c
// Graphics not found
```

### #1473 SPECIES_SPEWPA_JUNGLE
```c
// Graphics not found
```

### #1474 SPECIES_SPEWPA_FANCY
```c
// Graphics not found
```

### #1475 SPECIES_SPEWPA_POKEBALL
```c
// Graphics not found
```

### #1476 SPECIES_RATICATE_ALOLA_TOTEM
```c
// Graphics not found
```

### #1477 SPECIES_GUMSHOOS_TOTEM
```c
// Graphics not found
```

### #1478 SPECIES_VIKAVOLT_TOTEM
```c
// Graphics not found
```

### #1479 SPECIES_LURANTIS_TOTEM
```c
// Graphics not found
```

### #1480 SPECIES_SALAZZLE_TOTEM
```c
// Graphics not found
```

### #1481 SPECIES_MIMIKYU_TOTEM_DISGUISED
```c
// Graphics not found
```

### #1482 SPECIES_KOMMO_O_TOTEM
```c
// Graphics not found
```

### #1483 SPECIES_MAROWAK_ALOLA_TOTEM
```c
// Graphics not found
```

### #1484 SPECIES_RIBOMBEE_TOTEM
```c
// Graphics not found
```

### #1485 SPECIES_ARAQUANID_TOTEM
```c
// Graphics not found
```

### #1486 SPECIES_TOGEDEMARU_TOTEM
```c
// Graphics not found
```

### #1487 SPECIES_PIKACHU_STARTER
```c
// Graphics not found
```

### #1488 SPECIES_EEVEE_STARTER
```c
// Graphics not found
```

### #1489 SPECIES_VENUSAUR_GMAX
```c
[SPECIES_VENUSAUR_GMAX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // black
    PALd(4, 1),    // red
    PALe(5, 2),    // green
},
```

### #1490 SPECIES_BLASTOISE_GMAX
```c
[SPECIES_BLASTOISE_GMAX] = {
    PALa(1, 1),    // black
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // blue
    PALd(5, 1),    // light grey
    PALe(6, 2),    // dark grey
},
```

### #1491 SPECIES_CHARIZARD_GMAX
```c
[SPECIES_CHARIZARD_GMAX] = {
    PALa(1, 1),    // red
    PALb(2, 2),    // yellow
    PALc(4, 1),    // yellow
    PALd(5, 1),    // dark grey
    PALe(6, 1),    // dark brown
},
```

### #1492 SPECIES_BUTTERFREE_GMAX
```c
[SPECIES_BUTTERFREE_GMAX] = {
    PALa(1, 3),    // grey
    PALb(4, 2),    // cyan
    PALc(6, 5),    // light cyan
    PALd(11, 1),    // green
    PALe(12, 2),    // pink
},
```

### #1493 SPECIES_PIKACHU_GMAX
```c
[SPECIES_PIKACHU_GMAX] = {
    PALa(1, 1),    // yellow
    PALb(2, 1),    // yellow
    PALc(3, 1),    // white
    PALd(4, 3),    // dark grey
    PALe(7, 1),    // orange
},
```

### #1494 SPECIES_MEOWTH_GMAX
```c
[SPECIES_MEOWTH_GMAX] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // yellow
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // orange
    PALe(5, 1),    // yellow
},
```

### #1495 SPECIES_MACHAMP_GMAX
```c
[SPECIES_MACHAMP_GMAX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 3),    // orange
    PALd(6, 1),    // blue
    PALe(7, 1),    // dark grey
},
```

### #1496 SPECIES_GENGAR_GMAX
```c
[SPECIES_GENGAR_GMAX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 5),    // blue
    PALd(8, 2),    // red
    PALe(10, 1),    // purple
},
```

### #1497 SPECIES_KINGLER_GMAX
```c
[SPECIES_KINGLER_GMAX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // white
    PALe(5, 2),    // brown
},
```

### #1498 SPECIES_LAPRAS_GMAX
```c
[SPECIES_LAPRAS_GMAX] = {
    PALa(1, 2),    // cyan
    PALb(3, 1),    // grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // blue
    PALe(6, 1),    // black
},
```

### #1499 SPECIES_EEVEE_GMAX
```c
[SPECIES_EEVEE_GMAX] = {
    PALa(1, 2),    // dark brown
    PALb(3, 1),    // brown
    PALc(4, 2),    // grey
    PALd(6, 2),    // yellow
    PALe(8, 1),    // orange
},
```

### #1500 SPECIES_SNORLAX_GMAX
```c
[SPECIES_SNORLAX_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // white
    PALc(3, 1),    // light grey
    PALd(4, 1),    // yellow
    PALe(5, 1),    // black
},
```


## Pokémon #1501-1523

### #1501 SPECIES_GARBODOR_GMAX
```c
[SPECIES_GARBODOR_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // light grey
    PALd(4, 1),    // grey
    PALe(5, 1),    // grey
},
```

### #1502 SPECIES_MELMETAL_GMAX
```c
[SPECIES_MELMETAL_GMAX] = {
    PALa(1, 1),    // grey
    PALb(2, 2),    // light grey
    PALc(4, 1),    // dark grey
    PALd(5, 1),    // white
    PALe(6, 3),    // grey
},
```

### #1503 SPECIES_RILLABOOM_GMAX
```c
[SPECIES_RILLABOOM_GMAX] = {
    PALa(1, 1),    // dark brown
    PALb(2, 2),    // black
    PALc(4, 1),    // grey
    PALd(5, 2),    // dark green
    PALe(7, 1),    // brown
},
```

### #1504 SPECIES_CINDERACE_GMAX
```c
[SPECIES_CINDERACE_GMAX] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // light grey
    PALd(4, 2),    // dark brown
    PALe(6, 1),    // yellow
},
```

### #1505 SPECIES_INTELEON_GMAX
```c
[SPECIES_INTELEON_GMAX] = {
    PALa(1, 1),    // dark blue
    PALb(2, 1),    // cyan
    PALc(3, 1),    // dark grey
    PALd(4, 1),    // cyan
    PALe(5, 2),    // light cyan
},
```

### #1506 SPECIES_CORVIKNIGHT_GMAX
```c
[SPECIES_CORVIKNIGHT_GMAX] = {
    PALa(1, 2),    // black
    PALb(3, 2),    // grey
    PALc(5, 1),    // red
    PALd(6, 5),    // dark grey
    PALe(11, 1),    // blue
},
```

### #1507 SPECIES_ORBEETLE_GMAX
```c
[SPECIES_ORBEETLE_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 3),    // dark brown
    PALc(5, 1),    // brown
    PALd(6, 1),    // orange
    PALe(7, 1),    // cyan
},
```

### #1508 SPECIES_DREDNAW_GMAX
```c
[SPECIES_DREDNAW_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // grey
    PALc(3, 1),    // dark brown
    PALd(4, 1),    // brown
    PALe(5, 1),    // white
},
```

### #1509 SPECIES_COALOSSAL_GMAX
```c
[SPECIES_COALOSSAL_GMAX] = {
    PALa(1, 12),    // dark grey
    PALb(13, 1),    // orange
    PALc(14, 1),    // yellow
    PALd(15, 1),    // red
},
```

### #1510 SPECIES_FLAPPLE_GMAX
```c
[SPECIES_FLAPPLE_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // brown
    PALc(4, 1),    // orange
    PALd(5, 1),    // brown
    PALe(6, 1),    // yellow
},
```

### #1511 SPECIES_APPLETUN_GMAX
```c
[SPECIES_APPLETUN_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 2),    // brown
    PALc(4, 1),    // orange
    PALd(5, 1),    // brown
    PALe(6, 1),    // yellow
},
```

### #1512 SPECIES_SANDACONDA_GMAX
```c
[SPECIES_SANDACONDA_GMAX] = {
    PALa(1, 2),    // brown
    PALb(3, 1),    // dark grey
    PALc(4, 1),    // white
    PALd(5, 2),    // grey
    PALe(7, 1),    // yellow
},
```

### #1513 SPECIES_TOXTRICITY_AMPED_GMAX
```c
// Graphics not found
```

### #1514 SPECIES_TOXTRICITY_LOW_KEY_GMAX
```c
// Graphics not found
```

### #1515 SPECIES_CENTISKORCH_GMAX
```c
[SPECIES_CENTISKORCH_GMAX] = {
    PALa(1, 1),    // red
    PALb(2, 1),    // orange
    PALc(3, 1),    // black
    PALd(4, 1),    // yellow
    PALe(5, 4),    // dark grey
},
```

### #1516 SPECIES_HATTERENE_GMAX
```c
[SPECIES_HATTERENE_GMAX] = {
    PALa(1, 1),    // dark grey
    PALb(2, 1),    // blue
    PALc(3, 3),    // white
    PALd(6, 2),    // light pink
    PALe(8, 1),    // light grey
},
```

### #1517 SPECIES_GRIMMSNARL_GMAX
```c
[SPECIES_GRIMMSNARL_GMAX] = {
    PALa(1, 4),    // dark grey
    PALb(5, 2),    // black
    PALc(7, 1),    // green
    PALd(8, 1),    // red
    PALe(9, 1),    // green
},
```

### #1518 SPECIES_ALCREMIE_GMAX
```c
[SPECIES_ALCREMIE_GMAX] = {
    PALa(1, 1),    // grey
    PALb(2, 1),    // dark grey
    PALc(3, 2),    // yellow
    PALd(5, 1),    // yellow
    PALe(6, 1),    // yellow
},
```

### #1519 SPECIES_COPPERAJAH_GMAX
```c
[SPECIES_COPPERAJAH_GMAX] = {
    PALa(1, 1),    // brown
    PALb(2, 1),    // dark grey
    PALc(3, 1),    // red
    PALd(4, 2),    // black
    PALe(6, 1),    // grey
},
```

### #1520 SPECIES_DURALUDON_GMAX
```c
[SPECIES_DURALUDON_GMAX] = {
    PALa(1, 2),    // dark grey
    PALb(3, 3),    // light grey
    PALc(6, 1),    // dark grey
    PALd(7, 1),    // light grey
    PALe(8, 1),    // dark grey
},
```

### #1521 SPECIES_URSHIFU_SINGLE_STRIKE_GMAX
```c
// Graphics not found
```

### #1522 SPECIES_URSHIFU_RAPID_STRIKE_GMAX
```c
// Graphics not found
```

### #1523 SPECIES_MIMIKYU_BUSTED_TOTEM
```c
// Graphics not found
```


---

## Notes for Developers

### Tips for Choosing Palette Features

1. **Most Recognizable Features First**: Choose features that are most iconic to the Pokémon (e.g., Pikachu's yellow body, Charmander's tail flame)
2. **Complementary Variations**: Select features that will create interesting combinations when varied together
3. **Preserve Recognition**: Avoid varying ALL defining features - keep some consistent so the Pokémon remains recognizable
4. **Evolution Chains**: Use the same HCL values for evolution chains to preserve color shifts across evolutions

### Palette Index Determination

The color descriptions in this document are automatically generated based on palette analysis. For more accurate descriptions:

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

To improve descriptions in this reference:

1. Analyze the Pokémon's sprite palette using GIMP or similar tool
2. Identify distinct features (body parts, markings, etc.)
3. Update the entry with more descriptive comments
4. Use clear, descriptive comments for each palette feature
5. List features in order of visual importance/size

This reference is maintained as part of the Colour Variants feature documentation.
