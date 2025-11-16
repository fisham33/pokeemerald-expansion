# Technical Reference - GBA Music System

This document explains how music works in Pokemon Emerald Expansion at a technical level.

## GBA Audio Hardware

The Game Boy Advance has a custom audio processor with these specifications:

### Hardware Limits
- **6 audio channels total**:
  - 4 channels: Programmable Wave (used by Direct Sound)
  - 2 channels: DMA (Direct Memory Access) for sampled audio
- **Sample Rate**: Typically 13379 Hz - 32768 Hz
- **Bit Depth**: 8-bit samples
- **ROM Size Constraint**: Music must fit within available ROM space (~32MB total, shared with all game data)

### Practical Limits for Music
- **Max simultaneous notes (polyphony)**: ~8-12 notes (depends on sample complexity)
- **Max tracks per song**: 16 (software limit)
- **Max instruments**: 128 (General MIDI standard)
- **File size per song**: Aim for <500KB

## How Music is Stored

Pokemon Emerald uses a custom music engine called **m4a** (MusicPlayer2000/MP2K):

### File Structure

1. **MIDI Files** (`sound/songs/midi/*.mid`)
   - Standard MIDI format
   - Converted to `.s` assembly during build
   - Contains note data, timing, and instrument assignments

2. **Voicegroups** (`sound/voicegroups/*.s`)
   - Define instrument samples
   - Map MIDI program numbers to actual audio samples
   - Contain loop points, pitch, and envelope data

3. **Direct Sound Samples** (`sound/direct_sound_samples/`)
   - Raw audio samples (WAV format, typically 13379 Hz, 8-bit mono)
   - Used by voicegroups

## Build Process

When you run `make`, here's what happens to music:

```
1. mid2agb tool reads .mid files and midi.cfg
2. Converts MIDI to .s assembly files
3. Each .s file contains:
   - Note events (note on/off, timing)
   - Control changes (volume, pan)
   - Program changes (instrument selection)
4. GCC assembles .s files to .o object files
5. Linker combines everything into final ROM
```

### midi.cfg Format

Each line in `midi.cfg` configures one MIDI file:

```
mus_song_name.mid: -E -R50 -G128 -V080 -P5
```

Parameters:
- **-E**: Enable reverb/echo
- **-R[0-127]**: Reverb level (50 is common)
- **-G[number]**: Voicegroup to use
- **-V[000-127]**: Volume (in hex: 080 = 128 decimal)
- **-P[0-15]**: Priority (higher = more important, won't be interrupted)

## Integration Files

### 1. include/constants/songs.h

Defines C constants for song IDs:

```c
#define MUS_ROUTE101    359
#define MUS_MY_SONG     560  // Custom song
#define END_MUS         MUS_MY_SONG
```

- Songs start at ID 350 (after sound effects)
- `END_MUS` marks the last song
- Sequential numbering required

### 2. sound/song_table.inc

Assembly table that maps song IDs to actual song data:

```assembly
.align 2
gSongTable::
    song mus_route101, 2, 2
    song mus_my_song, 2, 2
```

Format: `song <name>, <ms>, <me>`
- `name`: Song identifier (matches MIDI filename without .mid)
- `ms`: Unknown (always 2 for music, 1 for SE)
- `me`: Unknown (always 2 for music, 1 for SE)

### 3. sound/songs/midi/midi.cfg

Build configuration for mid2agb tool (explained above).

### 4. ld_script_modern.ld

Linker script that includes song object files:

```ld
.rodata :
ALIGN(4)
{
    sound/songs/*.o(.rodata);  // Automatically includes all song .o files
} > ROM =0
```

The linker automatically includes all `.o` files from `sound/songs/`, so you don't need to manually add entries here.

## Voicegroups Explained

A voicegroup is a collection of instrument samples. Each MIDI program number (0-127) can map to a different sample.

### Standard Voicegroups
- **0-127**: Game's built-in voicegroups (various instrument sets)
- Each game area/context may use different voicegroups

### Universal Voicegroup
The "universal voicegroup" (typically 128) is a community-created voicegroup that:
- Contains a wide variety of instruments
- Supports most General MIDI instruments
- Makes MIDI files more portable
- Recommended for custom music

Get it from: https://github.com/aichiya/pokeemerald-expansion/tree/pokeemerald-expansion-universal-voicegroup

### Creating Custom Voicegroups

1. Create a new file in `sound/voicegroups/`
2. Define instrument mappings:
```assembly
.align 2
voicegroup128::
    voice keysplit_all, 60, 127, 0  @ 0: Piano
    voice direct_sound_sample_0, 60, 127, 0  @ 1: Bright Piano
    @ ... more instruments
```

3. Reference in `midi.cfg` with `-G128`

## MIDI to GBA Conversion Details

### What Gets Converted

✅ **Supported:**
- Note on/off events
- Tempo changes
- Program changes (instrument selection)
- Volume (CC 7)
- Pan (CC 10)
- Expression (CC 11)
- Pitch bend

❌ **Not Supported:**
- Complex effects (reverb depth, chorus)
- Some CCs (modulation wheel has limited support)
- SysEx messages
- Lyrics/metadata

### Channel Mapping

MIDI Channel → GBA Track
- MIDI supports 16 channels
- GBA m4a supports 16 tracks
- Usually 1:1 mapping
- Channel 10 (drums) may need special handling

### Polyphony Management

The GBA can't play unlimited simultaneous notes:

**Hardware limit**: ~8-12 notes
**Why**: Each note requires a DMA channel or wave channel

**What happens if exceeded:**
- Notes get cut off (oldest or lowest priority)
- Audio distortion/crackling
- Potential crashes

**Solution**: Use the optimizer (`--max-polyphony 8`)

## Optimization Techniques

### 1. Reduce Polyphony
- Limit simultaneous notes
- Remove doubled notes
- Simplify chords (use 2-3 note chords instead of 4+)

### 2. Reduce Track Count
- Merge similar instruments
- Remove silent/empty tracks
- Combine percussion into one track

### 3. Simplify Timing
- Quantize notes to 16th or 32nd notes
- Remove very short notes (<50ms)
- Avoid excessive tempo changes

### 4. Instrument Selection
- Use simpler waveforms (square, saw) for leads
- Avoid complex multi-sample instruments
- Test with Pokemon Emerald soundfont

### 5. Loop Points
- Add loop markers in MIDI
- Use `loopstart` and `loopend` CC events
- Keeps file size down (no need to repeat)

## Debugging Music Issues

### Music Doesn't Play
1. Check song ID is defined in `songs.h`
2. Verify entry in `song_table.inc`
3. Check MIDI file exists in `sound/songs/midi/`
4. Ensure entry in `midi.cfg`
5. Run `make clean && make`

### Music Sounds Wrong
1. Check voicegroup number
2. Analyze MIDI: `pokemon_music_converter.py analyze song.mid`
3. Test with Pokemon Emerald soundfont
4. Check for polyphony issues
5. Verify instrument mappings

### Compilation Errors
```
Error: symbol 'mus_song_name' not found
```
→ Missing entry in `song_table.inc` or filename mismatch

```
Error: undefined reference to 'mus_song_name'
```
→ Missing in `songs.h` or typo in constant name

```
ld: region 'ROM' overflowed
```
→ ROM is full, remove other songs or compress

### Runtime Issues
- **Music cuts out**: Polyphony too high
- **Crackling**: Sample rate mismatch
- **Wrong instruments**: Incorrect voicegroup
- **Game crashes**: File corrupted or too large

## Advanced: Manual MIDI Editing

For best results, manually edit MIDI in a DAW:

### Recommended DAWs
- **FL Studio**: Great piano roll
- **Reaper**: Lightweight, free trial
- **LMMS**: Free, open-source
- **GarageBand**: Mac users

### What to Edit
1. **Quantize timing**: Align notes to grid
2. **Fix wrong notes**: AI conversion isn't perfect
3. **Adjust velocity**: Make dynamics more natural
4. **Add CC events**: Volume curves, pan
5. **Set instruments**: Match General MIDI
6. **Add loops**: Use CC markers

### Testing
1. Export as MIDI
2. Test with Pokemon Emerald soundfont in a MIDI player
3. Analyze: `pokemon_music_converter.py analyze song.mid`
4. If issues, optimize: `pokemon_music_converter.py optimize song.mid`
5. Integrate and test in-game

## Performance Optimization

### File Size Reduction
- Shorter songs = smaller files
- Fewer instruments = smaller voicegroup
- Lower sample rate = smaller samples (but lower quality)
- Use loops instead of repeating sections

### In-Game Performance
- Lower priority songs can be interrupted
- Higher priority (P15) won't be cut off
- Balance priority across songs
- Battle music typically high priority

## Resources for Advanced Users

### Tools
- **Sappy**: Traditional GBA music editor
- **mid2agb**: MIDI to GBA converter (included in decomp)
- **VGMTrans**: Extract music from other GBA games
- **Polyphone**: Soundfont editor

### Documentation
- [GBATEK](https://problemkaputt.de/gbatek.htm): GBA hardware reference
- [MP2K Engine](https://www.romhacking.net/documents/462/): Music engine docs
- [pret pokeemerald](https://github.com/pret/pokeemerald): Decomp project

### Communities
- [PokeCommunity ROM Hacking](https://www.pokecommunity.com/forumdisplay.php?f=289)
- [pret Discord](https://discord.gg/6EU5jXU)
- [/r/PokemonROMhacks](https://reddit.com/r/PokemonROMhacks)

## Appendix: General MIDI Instrument List

The tool maps MIDI program numbers to GBA instruments. Standard GM instruments:

### 0-7: Piano
0. Acoustic Grand Piano
1. Bright Acoustic Piano
2. Electric Grand Piano
3. Honky-tonk Piano
4. Electric Piano 1
5. Electric Piano 2
6. Harpsichord
7. Clavinet

### 8-15: Chromatic Percussion
8. Celesta
9. Glockenspiel
10. Music Box
11. Vibraphone
12. Marimba
13. Xylophone
14. Tubular Bells
15. Dulcimer

### 16-23: Organ
16. Drawbar Organ
17. Percussive Organ
18. Rock Organ
19. Church Organ
20. Reed Organ
21. Accordion
22. Harmonica
23. Tango Accordion

### 24-31: Guitar
24. Nylon String Guitar
25. Steel String Guitar
26. Jazz Electric Guitar
27. Clean Electric Guitar
28. Muted Electric Guitar
29. Overdriven Guitar
30. Distortion Guitar
31. Guitar Harmonics

### 32-39: Bass
32. Acoustic Bass
33. Electric Bass (finger)
34. Electric Bass (pick)
35. Fretless Bass
36. Slap Bass 1
37. Slap Bass 2
38. Synth Bass 1
39. Synth Bass 2

### 40-47: Strings
40. Violin
41. Viola
42. Cello
43. Contrabass
44. Tremolo Strings
45. Pizzicato Strings
46. Orchestral Harp
47. Timpani

### 48-55: Ensemble
48. String Ensemble 1
49. String Ensemble 2
50. Synth Strings 1
51. Synth Strings 2
52. Choir Aahs
53. Voice Oohs
54. Synth Voice
55. Orchestra Hit

### 56-63: Brass
56. Trumpet
57. Trombone
58. Tuba
59. Muted Trumpet
60. French Horn
61. Brass Section
62. Synth Brass 1
63. Synth Brass 2

### 64-71: Reed
64. Soprano Sax
65. Alto Sax
66. Tenor Sax
67. Baritone Sax
68. Oboe
69. English Horn
70. Bassoon
71. Clarinet

### 72-79: Pipe
72. Piccolo
73. Flute
74. Recorder
75. Pan Flute
76. Blown Bottle
77. Shakuhachi
78. Whistle
79. Ocarina

### 80-87: Synth Lead
80. Lead 1 (square)
81. Lead 2 (sawtooth)
82. Lead 3 (calliope)
83. Lead 4 (chiff)
84. Lead 5 (charang)
85. Lead 6 (voice)
86. Lead 7 (fifths)
87. Lead 8 (bass+lead)

### 88-95: Synth Pad
88. Pad 1 (new age)
89. Pad 2 (warm)
90. Pad 3 (polysynth)
91. Pad 4 (choir)
92. Pad 5 (bowed)
93. Pad 6 (metallic)
94. Pad 7 (halo)
95. Pad 8 (sweep)

### 96-103: Synth Effects
96. FX 1 (rain)
97. FX 2 (soundtrack)
98. FX 3 (crystal)
99. FX 4 (atmosphere)
100. FX 5 (brightness)
101. FX 6 (goblins)
102. FX 7 (echoes)
103. FX 8 (sci-fi)

### 104-111: Ethnic
104. Sitar
105. Banjo
106. Shamisen
107. Koto
108. Kalimba
109. Bag pipe
110. Fiddle
111. Shanai

### 112-119: Percussive
112. Tinkle Bell
113. Agogo
114. Steel Drums
115. Woodblock
116. Taiko Drum
117. Melodic Tom
118. Synth Drum
119. Reverse Cymbal

### 120-127: Sound Effects
120. Guitar Fret Noise
121. Breath Noise
122. Seashore
123. Bird Tweet
124. Telephone Ring
125. Helicopter
126. Applause
127. Gunshot

### Channel 10: Percussion/Drums
MIDI Channel 10 is reserved for drums. Each note number maps to a different drum sound:

- 35: Acoustic Bass Drum
- 36: Bass Drum 1
- 37: Side Stick
- 38: Acoustic Snare
- 39: Hand Clap
- 40: Electric Snare
- 41-43: Low/Mid/High Tom
- 42: Closed Hi-Hat
- 44: Pedal Hi-Hat
- 46: Open Hi-Hat
- 49: Crash Cymbal 1
- 51: Ride Cymbal 1
- ... (many more)

Full list: https://www.cs.cmu.edu/~music/cmp/archives/cmsip/readings/GMSpecs_Patches.htm
