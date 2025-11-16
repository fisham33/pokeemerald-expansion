# Quick Start Guide - Pokemon Emerald Music Converter

## 5-Minute Setup

### 1. Install Dependencies
```bash
cd tools/pokemon_music_converter
pip install -r requirements.txt

# Optional: For audio-to-MIDI conversion
pip install basic-pitch
```

### 2. Choose Your Workflow

#### Already Have MIDI Files?
```bash
# Single file
python pokemon_music_converter.py integrate my_song.mid --voicegroup 128

# Multiple files
python pokemon_music_converter.py batch-integrate *.mid --voicegroup 128

# Done! Rebuild your ROM
cd ../..
make clean && make
```

#### Have Audio Files (MP3, WAV, etc.)?
```bash
# Full auto conversion + integration
python pokemon_music_converter.py convert my_song.mp3 --integrate --voicegroup 128

# Done! Rebuild your ROM
cd ../..
make clean && make
```

#### Want Manual Control?
```bash
# Step 1: Convert
python pokemon_music_converter.py convert my_song.mp3

# Step 2: Analyze (check for issues)
python pokemon_music_converter.py analyze mus_my_song.mid

# Step 3: Optimize (fix issues)
python pokemon_music_converter.py optimize mus_my_song.mid

# Step 4: Manually edit in DAW if needed
# (Open mus_my_song_optimized.mid in FL Studio, etc.)

# Step 5: Integrate
python pokemon_music_converter.py integrate mus_my_song_optimized.mid --voicegroup 128

# Done! Rebuild your ROM
cd ../..
make clean && make
```

## Common Commands

| What You Want | Command |
|---------------|---------|
| Add a MIDI file | `python pokemon_music_converter.py integrate song.mid --voicegroup 128` |
| Convert MP3 to MIDI | `python pokemon_music_converter.py convert song.mp3` |
| Check MIDI compatibility | `python pokemon_music_converter.py analyze song.mid` |
| Fix MIDI for GBA | `python pokemon_music_converter.py optimize song.mid` |
| Add multiple MIDIs | `python pokemon_music_converter.py batch-integrate *.mid --voicegroup 128` |
| Full auto workflow | `python pokemon_music_converter.py convert song.mp3 --integrate --voicegroup 128` |

## After Integration

### 1. Rebuild ROM
```bash
cd /path/to/pokeemerald-expansion
make clean
make
```

### 2. Use in Scripts
The tool will print your song's constant (e.g., `MUS_MY_SONG`). Use it like this:

**In map scripts (.pory files):**
```ruby
playbgm MUS_MY_SONG
```

**In C code:**
```c
#include "constants/songs.h"
PlayNewMapMusic(MUS_MY_SONG);
```

## Troubleshooting

### "mido not found"
```bash
pip install mido
```

### "basic-pitch not found" (only if converting audio)
```bash
pip install basic-pitch
```

### Music sounds bad
```bash
# Optimize the MIDI
python pokemon_music_converter.py optimize song.mid --max-polyphony 6

# Then re-integrate
python pokemon_music_converter.py integrate song_optimized.mid --voicegroup 128
```

### Need to change voicegroup later
Edit `sound/songs/midi/midi.cfg` and find your song's entry. Change the `-G128` number.

## Tips

1. **Use the Universal Voicegroup** (voicegroup 128) for most custom music
2. **Start with MIDI files** from the GBA Music Pack instead of converting audio
3. **Always analyze before integrating** to catch compatibility issues early
4. **Keep backups** of your original audio/MIDI files
5. **Test in-game** after integration to hear how it actually sounds

## Next Steps

- Read [README.md](README.md) for detailed documentation
- Check out the [GBA Music Pack](https://www.pokecommunity.com/threads/rom-hacking-music-pack-160-midi-songs-ready-to-use-with-sappy.527582/) for ready-to-use MIDIs
- Download the [Pokemon Emerald Soundfont](https://www.mediafire.com/file/ysbtegcf4tc6uxd/) to preview how your music will sound
