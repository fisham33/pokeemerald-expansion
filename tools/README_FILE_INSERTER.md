# Pokeemerald-Expansion File Inserter GUI

A graphical user interface tool for easily inserting various file types into pokeemerald-expansion projects.

## Features

The File Inserter GUI helps you add the following content to your ROM hack:

### 1. **Pokemon Graphics**
- Front sprites (animated)
- Back sprites
- Icons
- Palettes (normal and shiny)
- Footprints
- Overworld sprites
- Option to copy from existing Pokemon as a template

### 2. **Trainer Pictures**
- Front battle sprites
- Palettes
- Automatic file organization

### 3. **Item Graphics**
- Item icons
- Icon palettes

### 4. **Overworld Sprites**
- NPC/object sprites
- Configurable sprite dimensions
- Palette support

### 5. **Audio Files**
- Pokemon cries (MP3/WAV → AIF conversion guidance)
- Music (MIDI files)
- Sound effects

## Requirements

- Python 3.6 or higher
- tkinter (usually included with Python)
- A pokeemerald-expansion project

## Installation

No installation needed! The script is located in the `tools/` directory of your pokeemerald-expansion project.

## Usage

### Running the GUI

From your pokeemerald-expansion project root:

```bash
python3 tools/file_inserter_gui.py
```

Or make it executable and run directly:

```bash
chmod +x tools/file_inserter_gui.py
./tools/file_inserter_gui.py
```

### Using the Interface

1. **Select a Tab**: Choose the type of content you want to insert (Pokemon, Trainer Pic, Item, Overworld Sprite, or Audio)

2. **Enter Information**: Provide the required name/identifier for your content

3. **Browse for Files**: Click "Browse" buttons to select your graphics or audio files

4. **Insert**: Click the insert button to copy files to the correct locations

5. **Follow Next Steps**: The operation log will show you what manual steps remain to complete the insertion

### Pokemon Tab

**Fields:**
- **Species Name**: Lowercase name (e.g., "pikachu", "charizard")
- **Graphics Files**: Optional - provide any combination of:
  - Front sprite (anim_front.png)
  - Back sprite (back.png)
  - Icon (icon.png)
  - Normal palette (normal.pal)
  - Shiny palette (shiny.pal)
  - Footprint (footprint.png)
  - Overworld sprite (overworld.png)
  - Overworld palettes

**Options:**
- **Copy from existing Pokemon**: Copies all graphics from an existing Pokemon as a starting template

**After Insertion:**
You'll still need to manually:
1. Add species constant to `include/constants/species.h`
2. Add species data to `src/data/pokemon/species_info.h`
3. Add graphics references to `src/data/graphics/pokemon.h`
4. Add animation data (see tutorial)
5. Add learnsets, evolutions, etc.

See `docs/tutorials/how_to_new_pokemon.md` for complete details.

### Trainer Pic Tab

**Fields:**
- **Trainer Pic Name**: Lowercase name (e.g., "cool_trainer_m")
- **Front Pic**: PNG file (max 16 colors, first color becomes transparent)
- **Palette**: PAL file (optional if palette is embedded in PNG)

**After Insertion:**
You'll still need to manually:
1. Add graphics references to `src/data/graphics/trainers.h`
2. Add trainer sprite entry to the gTrainerSprites table
3. Add TRAINER_PIC constant to `include/constants/trainers.h`

See `docs/tutorials/how_to_trainer_front_pic.md` for complete details.

### Item Tab

**Fields:**
- **Item Name**: Lowercase name (e.g., "super_potion")
- **Icon**: PNG file
- **Palette**: PAL file

**After Insertion:**
You'll still need to manually:
1. Add item constant to `include/constants/items.h`
2. Add item data to `src/data/items.h`
3. Add graphics references to `src/data/graphics/items.h`

### Overworld Sprite Tab

**Fields:**
- **Sprite Name**: Lowercase name (e.g., "nurse_joy")
- **Sprite**: PNG file (4-bit color depth)
- **Palette**: PAL file
- **Frame Width/Height**: Sprite dimensions in 8x8 pixel tiles (usually 4x4)

**After Insertion:**
You'll still need to manually:
1. Add sprite references to `src/data/object_events/object_event_graphics.h`
2. Add build rule to `spritesheet_rules.mk`
3. Add pic table to `src/data/object_events/object_event_pic_tables.h`
4. Add graphics info to `src/data/object_events/object_event_graphics_info.h`
5. Add constant to `include/constants/event_objects.h`

### Audio Tab

**Fields:**
- **Audio Type**: Pokemon Cry, Music (MIDI), or Sound Effect
- **Audio Name**: Lowercase name
- **Audio File**: Audio file (MP3/WAV for cries, MID for music, etc.)

**After Insertion:**

For **Pokemon Cries**:
1. Convert to AIF using ffmpeg (command provided in log)
2. Add cry to `sound/direct_sound_data.inc`
3. Add cry ID to `include/constants/cries.h`
4. Add cry to `sound/cry_tables.inc`

For **Music**:
1. Add song to `sound/song_table.inc`
2. Add song constant to `include/constants/songs.h`

For **Sound Effects**:
1. Add sound effect to `sound/song_table.inc`
2. Add SE constant to `include/constants/songs.h`

## Tips

- **File Formats**: Always use the correct file formats:
  - PNG for sprites/icons (4-bit or 8-bit indexed color)
  - PAL or GBAPAL for palettes
  - MID for music
  - MP3/WAV/AIF for cries and sound effects

- **Naming Conventions**: Use lowercase with underscores (e.g., "my_pokemon", "cool_trainer")

- **Color Limits**:
  - Pokemon sprites: 15 colors + transparency (16 total)
  - Trainer sprites: 15 colors + transparency (16 total)
  - Overworld sprites: 15 colors + transparency (16 total)

- **Backup**: Always backup your project before mass insertions

- **Log Window**: Check the operation log for detailed next steps after each insertion

## What This Tool Does vs. What You Must Do

### ✓ Automated by the Tool

The tool **automatically** handles:
- ✓ Copying files to the correct project directories
- ✓ Organizing graphics with proper naming conventions
- ✓ Creating directory structures if they don't exist
- ✓ Validating file paths and names

After each insertion, you'll see a **"✓ AUTOMATED STEPS COMPLETED"** section showing exactly what was done.

### ⚠ Manual Steps Required

The tool **CANNOT** do these automatically - you must edit code files manually:
- ⚠ Adding constants to header files (.h)
- ⚠ Adding data structures to C files (.c, .h)
- ⚠ Updating build rules (Makefile, spritesheet_rules.mk)
- ⚠ Adding game logic (stats, moves, abilities, etc.)
- ⚠ Converting audio formats (ffmpeg for cries)

After each insertion, you'll see a **"⚠ MANUAL STEPS REQUIRED"** section with:
- Numbered step-by-step instructions
- Exact file paths to edit
- Ready-to-use code snippets you can copy/paste
- Specific locations within files to make changes

### Example Output

When you insert a Pokemon, the log shows:

```
═══ ✓ AUTOMATED STEPS COMPLETED ═══
[SUCCESS] Files copied to: graphics/pokemon/pikachu/
[SUCCESS] Graphics files: anim_front.png, back.png, icon.png
[SUCCESS] ✓ File organization complete!

═══ ⚠ MANUAL STEPS REQUIRED ═══
[WARNING] The tool CANNOT do these automatically - you must edit code files:
[MANUAL]   1. Add species constant to include/constants/species.h
[CODE]      #define SPECIES_PIKACHU  XXXX  // Replace XXXX with next number
[MANUAL]   2. Add graphics references to src/data/graphics/pokemon.h
[CODE]      const u32 gMonFrontPic_Pikachu[] = INCBIN_U32("graphics/pokemon/pikachu/anim_front.4bpp.lz");
[MANUAL]   3. Add species entry to src/data/pokemon/species_info.h
... (and so on)
```

**Color-coded log entries** make it easy to distinguish:
- 🟢 Green = What was automated
- 🔴 Red = What you must do manually
- 🔵 Blue = Section headers
- 🟢 Green monospace = Code snippets to copy

Think of this tool as a **smart file organizer** that:
1. Handles the tedious file copying
2. Gives you exact instructions for code integration
3. Provides ready-to-use code snippets

## Troubleshooting

**"Could not find pokeemerald-expansion project root!"**
- Make sure you're running the script from within your pokeemerald-expansion project directory

**"File not found" errors**
- Check that your file paths are correct
- Make sure the source files actually exist

**Graphics not appearing in game**
- Remember this tool only copies files! You must still add the C code references
- Check the tutorial files in `docs/tutorials/` for complete instructions

## Support

For issues or questions:
- Check the pokeemerald-expansion documentation in `docs/`
- Refer to the tutorials in `docs/tutorials/`
- Visit the pokeemerald-expansion GitHub repository

## Contributing

This tool is part of the pokeemerald-expansion project. To contribute improvements:
1. Fork the repository
2. Make your changes
3. Submit a pull request

## License

This tool is part of pokeemerald-expansion and follows the same license.
