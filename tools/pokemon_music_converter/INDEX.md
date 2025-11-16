# Pokemon Music Converter - Documentation Index

Welcome! This tool helps you add custom music to your Pokemon Emerald romhack.

## Quick Navigation

### 🚀 Getting Started
**→ [QUICKSTART.md](QUICKSTART.md)** - Start here! 5-minute setup and common commands

### 📖 Full Documentation
**→ [README.md](README.md)** - Complete guide with detailed examples and workflows

### ⚙️ Technical Details
**→ [TECHNICAL.md](TECHNICAL.md)** - How GBA music works, advanced optimization, debugging

### 💡 Examples
**→ [examples.sh](examples.sh)** - Copy-paste ready command examples

---

## What This Tool Does

```
Audio File (MP3/WAV/etc.)  →  MIDI File  →  GBA ROM Music
         ↓                       ↓              ↓
   [basic-pitch]          [Optimizer]    [Auto Integration]
```

1. **Convert**: Audio → MIDI using ML transcription
2. **Analyze**: Check GBA compatibility (polyphony, tracks, instruments)
3. **Optimize**: Fix issues automatically (reduce polyphony, map instruments)
4. **Integrate**: Update all project files automatically

---

## Installation

```bash
# 1. Install Python dependencies
cd tools/pokemon_music_converter
pip install -r requirements.txt

# 2. Optional: For audio-to-MIDI conversion
pip install basic-pitch
```

---

## Most Common Commands

### Already have MIDI? Just add it:
```bash
python pokemon_music_converter.py integrate my_song.mid --voicegroup 128
```

### Have MP3/WAV? Full auto conversion:
```bash
python pokemon_music_converter.py convert my_song.mp3 --integrate --voicegroup 128
```

### Multiple files? Batch process:
```bash
python pokemon_music_converter.py batch-integrate *.mid --voicegroup 128
```

---

## Documentation Overview

| File | Description | When to Read |
|------|-------------|--------------|
| **QUICKSTART.md** | 5-minute guide, essential commands | First time setup |
| **README.md** | Complete reference, all features | When you need details |
| **TECHNICAL.md** | GBA music system internals | Advanced users, debugging |
| **examples.sh** | Copy-paste command examples | Quick reference |
| **requirements.txt** | Python dependencies | Installation |
| **pokemon_music_converter.py** | The actual tool | (Don't edit unless contributing) |

---

## Feature Summary

✅ **Audio-to-MIDI Conversion**
- MP3, WAV, OGG, FLAC support
- ML-based transcription (basic-pitch)
- Best for: simple melodies, chiptune, game music

✅ **MIDI Analysis**
- Track count, polyphony, note range
- Instrument list
- GBA compatibility warnings

✅ **MIDI Optimization**
- Polyphony limiting (prevent audio glitches)
- Instrument mapping (GM to GBA)
- Empty track removal

✅ **Auto Integration**
- Updates `songs.h`, `song_table.inc`, `midi.cfg`
- Assigns song IDs automatically
- Copies files to correct locations

✅ **Batch Processing**
- Process multiple songs at once
- Perfect for music packs

---

## Workflow Examples

### Workflow 1: Quick MIDI Integration
```bash
python pokemon_music_converter.py integrate song.mid --voicegroup 128
make clean && make
```

### Workflow 2: Audio → MIDI → ROM
```bash
python pokemon_music_converter.py convert song.mp3 --integrate --voicegroup 128
make clean && make
```

### Workflow 3: Manual Control
```bash
# Convert
python pokemon_music_converter.py convert song.mp3

# Analyze
python pokemon_music_converter.py analyze mus_song.mid

# Edit in FL Studio/DAW (optional)

# Optimize
python pokemon_music_converter.py optimize mus_song.mid

# Integrate
python pokemon_music_converter.py integrate mus_song_optimized.mid --voicegroup 128

# Build
make clean && make
```

---

## After Integration

Your song gets a constant like `MUS_MY_SONG`. Use it in your romhack:

**Map scripts (.pory):**
```ruby
playbgm MUS_MY_SONG
```

**C code:**
```c
#include "constants/songs.h"
PlayNewMapMusic(MUS_MY_SONG);
```

---

## Help & Support

### Command Help
```bash
python pokemon_music_converter.py --help
python pokemon_music_converter.py convert --help
python pokemon_music_converter.py analyze --help
# etc.
```

### Troubleshooting

| Problem | Solution |
|---------|----------|
| "mido not found" | `pip install mido` |
| "basic-pitch not found" | `pip install basic-pitch` (only if converting audio) |
| Music sounds bad | Use optimize command, reduce polyphony |
| Compilation errors | Run `make clean && make`, check file entries |
| File too large | Optimize with lower polyphony, shorten song |

See **TECHNICAL.md** for advanced debugging.

---

## Resources

- **Pokemon Emerald Soundfont**: [Download](https://www.mediafire.com/file/ysbtegcf4tc6uxd/)
- **GBA Music Pack** (160 ready-to-use MIDIs): [PokeCommunity](https://www.pokecommunity.com/threads/527582/)
- **Universal Voicegroup**: [GitHub](https://github.com/aichiya/pokeemerald-expansion/tree/pokeemerald-expansion-universal-voicegroup)
- **MIDI Instruments Reference**: [GM Instruments](https://www.ccarh.org/courses/253/handout/gminstruments/)

---

## Tips for Success

1. ✅ **Start with MIDI files** (GBA Music Pack) before trying audio conversion
2. ✅ **Always analyze** before integrating (`analyze` command)
3. ✅ **Use universal voicegroup** (128) for custom music
4. ✅ **Test in-game** after integration
5. ✅ **Keep backups** of original files
6. ⚠️ **Audio conversion isn't perfect** - expect to manually refine in a DAW
7. ⚠️ **Simple melodies convert better** than complex orchestral pieces

---

## Contributing

Want to improve this tool? Suggestions and pull requests welcome!

---

**Ready to start? → [QUICKSTART.md](QUICKSTART.md)**

For questions, check the [README.md](README.md) or [TECHNICAL.md](TECHNICAL.md) documentation.
