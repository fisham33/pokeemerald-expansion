# Pokemon Emerald Music Converter

An automated tool for converting audio files to MIDI and integrating them into Pokemon Emerald Expansion romhacks.

## Features

- **Audio-to-MIDI Conversion**: Automatically convert MP3, WAV, OGG, FLAC files to MIDI using ML-based transcription
- **MIDI Analysis**: Analyze MIDI files for GBA compatibility (track count, polyphony, note ranges)
- **MIDI Optimization**: Automatically optimize MIDI files for GBA hardware constraints
- **Auto Integration**: Automatically update all required project files (songs.h, song_table.inc, midi.cfg)
- **Batch Processing**: Process multiple songs at once
- **Smart Naming**: Automatic filename sanitization and naming convention compliance

## Installation

### 1. Install Python Dependencies

```bash
cd tools/pokemon_music_converter
pip install -r requirements.txt
```

### 2. Install basic-pitch (Optional, for Audio-to-MIDI)

If you want to convert audio files (not just MIDI), install basic-pitch:

```bash
pip install basic-pitch
```

**Note**: basic-pitch requires TensorFlow and can be ~500MB. If you only work with MIDI files, you can skip this.

## Quick Start

### Workflow 1: Full Audio-to-MIDI Integration

Convert an audio file, optimize it, and integrate into your ROM:

```bash
python pokemon_music_converter.py convert my_song.mp3 --integrate --voicegroup 128
```

### Workflow 2: Integrate Existing MIDI

If you already have a MIDI file:

```bash
python pokemon_music_converter.py integrate my_song.mid --voicegroup 128
```

### Workflow 3: Batch Integration

Integrate multiple MIDI files at once:

```bash
python pokemon_music_converter.py batch-integrate *.mid --voicegroup 128
```

## Detailed Usage

### 1. Convert Audio to MIDI

```bash
# Basic conversion
python pokemon_music_converter.py convert my_song.mp3

# Convert with custom output name
python pokemon_music_converter.py convert my_song.mp3 -o custom_name.mid

# Convert and analyze
python pokemon_music_converter.py convert my_song.mp3 --analyze

# Convert and optimize
python pokemon_music_converter.py convert my_song.mp3 --optimize
```

**Supported audio formats**: MP3, WAV, OGG, FLAC, M4A

### 2. Analyze MIDI Files

Check if your MIDI is GBA-compatible:

```bash
python pokemon_music_converter.py analyze my_song.mid
```

**Output includes**:
- Track count
- Length
- Polyphony (simultaneous notes)
- Instrument list
- Note range
- Warnings about GBA compatibility issues

Example output:
```
============================================================
MIDI Analysis: my_song.mid
============================================================
Tracks:           8
Length:           120.50 seconds
Ticks per beat:   480
Tempo changes:    2
Total notes:      2450
Max polyphony:    6
Note range:       36-84
Instruments:      5
  0, 24, 32, 48, 56

✓ No issues detected
============================================================
```

### 3. Optimize MIDI for GBA

Reduce polyphony and optimize for GBA playback:

```bash
# Basic optimization (max 8 simultaneous notes)
python pokemon_music_converter.py optimize my_song.mid

# Custom polyphony limit
python pokemon_music_converter.py optimize my_song.mid --max-polyphony 6

# Specify output file
python pokemon_music_converter.py optimize my_song.mid -o optimized.mid
```

**What optimization does**:
- Limits polyphony to prevent audio glitches
- Maps instruments to GBA-compatible General MIDI instruments
- Removes empty tracks
- Cleans up unnecessary MIDI events

### 4. Integrate into Project

Add a MIDI file to your romhack project:

```bash
# Basic integration (uses default voicegroup 128)
python pokemon_music_converter.py integrate my_song.mid

# Specify voicegroup
python pokemon_music_converter.py integrate my_song.mid --voicegroup 128

# Custom song name
python pokemon_music_converter.py integrate my_song.mid --name mus_custom_battle

# Optimize before integrating
python pokemon_music_converter.py integrate my_song.mid --optimize --voicegroup 128
```

**What integration does**:
1. Copies MIDI to `sound/songs/midi/`
2. Adds constant definition to `include/constants/songs.h`
3. Adds song entry to `sound/song_table.inc`
4. Adds MIDI config to `sound/songs/midi/midi.cfg`
5. Assigns next available song ID

### 5. Batch Processing

Process multiple songs at once:

```bash
# Integrate all MIDI files in current directory
python pokemon_music_converter.py batch-integrate *.mid --voicegroup 128

# With optimization
python pokemon_music_converter.py batch-integrate *.mid --optimize --voicegroup 128

# Specific files
python pokemon_music_converter.py batch-integrate song1.mid song2.mid song3.mid --voicegroup 128
```

## Understanding Voicegroups

Voicegroups define the instrument soundbank used for your music. Common options:

- **128**: Universal voicegroup (recommended for custom music)
- **0-127**: Standard GBA voicegroups (use if you know what you're doing)

To use the universal voicegroup:
1. Get it from: https://github.com/aichiya/pokeemerald-expansion/tree/pokeemerald-expansion-universal-voicegroup
2. Note the voicegroup number when you install it
3. Use that number with `--voicegroup`

## File Naming Conventions

The tool automatically handles naming:

- Spaces → underscores: `My Song.mid` → `mus_my_song.mid`
- Special characters removed: `Song #1!.mid` → `mus_song_1.mid`
- Adds `mus_` prefix if missing
- Converts to lowercase

You can override with `--name`:
```bash
python pokemon_music_converter.py integrate song.mid --name mus_custom_name
```

## GBA Music Limitations

Keep these constraints in mind:

| Constraint | Limit | What Happens If Exceeded |
|------------|-------|--------------------------|
| **Tracks** | 16 max | Game may crash or glitch |
| **Polyphony** | ~8-12 notes | Audio distortion/glitches |
| **File Size** | ~500KB | May not fit in ROM |
| **Note Range** | MIDI 21-108 | Notes outside range won't play |
| **Instruments** | 128 (GM) | Non-GM instruments map to GM |

Use `analyze` and `optimize` commands to check and fix these issues.

## Audio-to-MIDI Quality Tips

Automated audio-to-MIDI conversion has limitations. For best results:

### ✅ Good Audio Sources
- Solo instruments
- Clear melodies
- Simple chiptune/8-bit music
- Game soundtracks (especially GBA/NDS era)
- Music with distinct notes (not heavy reverb/distortion)

### ❌ Difficult Audio Sources
- Heavy orchestral arrangements
- Complex polyphonic music
- Songs with heavy effects/reverb
- Vocals (will be transcribed but may sound strange)
- Music with lots of percussion

### Improving Results
1. **Pre-process audio**: Use audio editing software to isolate melodic parts
2. **Split tracks**: Convert drum, bass, melody separately then combine
3. **Manual cleanup**: After conversion, open MIDI in a DAW (FL Studio, Ableton, Reaper) and clean up
4. **Use existing MIDIs**: Check the GBA Music Pack (linked in resources) first
5. **Reference the Pokemon Emerald soundfont**: Test playback with the soundfont to hear how it will sound

## Example Workflows

### Example 1: Simple MIDI Integration
You have a MIDI file ready to use:
```bash
python pokemon_music_converter.py integrate route_theme.mid --voicegroup 128
```

### Example 2: Convert and Integrate Audio
You have an MP3 of a song:
```bash
# Step 1: Convert to MIDI
python pokemon_music_converter.py convert battle_theme.mp3

# Step 2: Analyze the result
python pokemon_music_converter.py analyze mus_battle_theme.mid

# Step 3: Optimize if needed
python pokemon_music_converter.py optimize mus_battle_theme.mid

# Step 4: Integrate
python pokemon_music_converter.py integrate mus_battle_theme_optimized.mid --voicegroup 128
```

Or do it all in one step:
```bash
python pokemon_music_converter.py convert battle_theme.mp3 --integrate --voicegroup 128
```

### Example 3: Batch Add Music Pack
You downloaded the GBA Music Pack:
```bash
# Navigate to the music pack directory
cd ~/Downloads/GBA_Music_Pack

# Integrate all MIDIs
python /path/to/pokemon_music_converter.py batch-integrate *.mid --voicegroup 128
```

### Example 4: Manual Refinement Workflow
For best quality, manually refine the MIDI:
```bash
# Step 1: Convert audio to MIDI
python pokemon_music_converter.py convert my_song.mp3

# Step 2: Open in DAW and manually edit
# (open mus_my_song.mid in FL Studio, fix wrong notes, adjust timing, etc.)

# Step 3: Optimize the refined MIDI
python pokemon_music_converter.py optimize mus_my_song_refined.mid

# Step 4: Integrate
python pokemon_music_converter.py integrate mus_my_song_refined_optimized.mid --voicegroup 128
```

## After Integration

After running the integration command, you need to rebuild your ROM:

```bash
# From the pokeemerald-expansion root directory
make clean
make
```

The song will be available in-game with the constant printed by the tool (e.g., `MUS_MY_SONG`).

## Using Your Music In-Game

After integration, use the constant in your scripts:

```c
// In a map script (.pory file)
setvar VAR_TEMP_0, MUS_MY_CUSTOM_SONG
special PlayBGM

// Or directly
playbgm MUS_MY_CUSTOM_SONG
```

Or in C code:
```c
#include "constants/songs.h"

PlayNewMapMusic(MUS_MY_CUSTOM_SONG);
```

## Troubleshooting

### "basic-pitch not found"
- Install it: `pip install basic-pitch`
- Or skip audio conversion and work with MIDI files only

### "mido library not found"
- Install requirements: `pip install -r requirements.txt`

### "songs.h not found" or other file errors
- Make sure you're running from the pokeemerald-expansion root directory
- Or use `--project-root /path/to/pokeemerald-expansion`

### Music sounds wrong in-game
- Try optimizing the MIDI: `python pokemon_music_converter.py optimize song.mid`
- Check polyphony: `python pokemon_music_converter.py analyze song.mid`
- Make sure you're using the correct voicegroup
- Test with the Pokemon Emerald soundfont in a MIDI player

### Compilation errors after integration
- Make sure to run `make clean` before `make`
- Check that all entries were added correctly to songs.h, song_table.inc, and midi.cfg
- Verify MIDI file is valid: `python pokemon_music_converter.py analyze yourfile.mid`

### File too large / ROM full
- Optimize MIDI to reduce size
- Use lower polyphony: `--max-polyphony 4`
- Shorten the loop points in your MIDI
- Remove unused instruments/tracks

## Resources

- **Pokemon Emerald Soundfont**: https://www.mediafire.com/file/ysbtegcf4tc6uxd/Pokemon_Emerald_Soundfont_%2528Updated_April_20%252C_2021%2529.sf2/file
- **MIDI Instrument List**: https://www.ccarh.org/courses/253/handout/gminstruments/
- **GBA Music Pack**: https://www.pokecommunity.com/threads/rom-hacking-music-pack-160-midi-songs-ready-to-use-with-sappy.527582/
- **Universal Voicegroup**: https://github.com/aichiya/pokeemerald-expansion/tree/pokeemerald-expansion-universal-voicegroup

## Advanced Usage

### Custom Project Location
```bash
python pokemon_music_converter.py --project-root /path/to/pokeemerald-expansion integrate song.mid
```

### MIDI Configuration Options

You can manually edit `sound/songs/midi/midi.cfg` after integration to adjust:

- **-E**: Echo/reverb enable
- **-R50**: Reverb level (0-127)
- **-G128**: Voicegroup number
- **-V080**: Volume (0-127, in hex)
- **-P5**: Priority (0-15)

Example entry:
```
mus_my_song.mid: -E -R50 -G128 -V090 -P5
```

## Contributing

Found a bug or want to add features? Contributions welcome!

## License

This tool is provided as-is for use with Pokemon Emerald Expansion projects.

## Credits

- Uses `basic-pitch` by Spotify for audio-to-MIDI conversion
- Uses `mido` for MIDI file manipulation
- Created for the Pokemon Emerald Expansion community
