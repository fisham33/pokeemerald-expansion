# Pokemon Emerald Live Tracker for mGBA

A real-time gameplay tracker that reads Pokemon Emerald memory via mGBA's Lua scripting API and displays your party, badges, and PC boxes in a live web interface.

![Version](https://img.shields.io/badge/version-1.0.0-blue)
![mGBA](https://img.shields.io/badge/mGBA-0.10+-green)
![Platform](https://img.shields.io/badge/platform-GBA-red)

## Features

- ✅ **Real-time Party Tracking**: See your current team with levels, moves, stats, and HP
- ✅ **Badge Progress**: Track your Hoenn badge collection
- ✅ **PC Box Overview**: View Pokemon stored in boxes
- ✅ **Shiny Detection**: Automatically detect and highlight shiny Pokemon
- ✅ **Live Updates**: Refreshes every second while playing
- ✅ **Beautiful UI**: Modern dark-themed interface optimized for visibility

## Screenshots

The frontend displays:
- Trainer information (name, gender, play time)
- All 8 Hoenn badges with visual indicators
- Party Pokemon with full stats, moves, and HP bars
- PC box summaries
- Debug information and connection status

## Prerequisites

1. **mGBA v0.10 or higher** (Lua scripting support required)
   - Download: https://mgba.io/downloads.html

2. **Built Pokemon Emerald ROM** (pokeemerald-expansion)
   - You must have already compiled your ROM

3. **Modern web browser**
   - Chrome, Firefox, Edge, or Safari

## Installation & Setup

### Step 1: Build Your ROM

```bash
# Navigate to your pokeemerald-expansion directory
cd /path/to/pokeemerald-expansion

# Build the ROM
make clean
make

# Generate symbol file (CRITICAL!)
make syms
```

This will create:
- `pokeemerald.gba` - Your ROM file
- `pokeemerald.sym` - Symbol file mapping variables to memory addresses

### Step 2: Verify Symbol File

```bash
# Check that the symbol file was created
ls -lh pokeemerald.sym

# Should see a file ~50-100KB in size
# Example output:
# -rw-r--r-- 1 user user 87K Nov 18 13:47 pokeemerald.sym
```

### Step 3: Copy Symbol File

Copy the `.sym` file to the `mgba_scripts/` directory:

```bash
cp pokeemerald.sym mgba_scripts/
```

**IMPORTANT**: The Lua script expects `pokeemerald.sym` in the same directory as `tracker.lua`.

### Step 4: Generate Data Tables (First Time Only)

```bash
cd mgba_scripts
./generate_data_tables.sh
```

This creates:
- `modules/species_data.lua` - All 1600+ Pokemon names
- `modules/move_data.lua` - All 900+ move names

### Step 5: Load in mGBA

1. Open mGBA
2. Load your ROM: `File > Load ROM` → Select `pokeemerald.gba`
3. Load the Lua script:
   - `Tools > Scripting...`
   - Click `File > Load script...`
   - Navigate to `mgba_scripts/tracker.lua`
   - Click `Open`

4. Check the mGBA console for initialization messages:
   ```
   === Pokemon Emerald Live Tracker ===
   Initializing...
   Loading symbol file: pokeemerald.sym
   Loaded 1234 symbols
   Memory regions initialized
   Tracker initialized successfully!
   Output file: tracker_data.json
   ```

### Step 6: Open Frontend

1. Navigate to `mgba_scripts/frontend/`
2. Open `index.html` in your web browser
   - **Windows**: Double-click `index.html`
   - **Mac/Linux**: Right-click → Open With → Browser
   - Or drag-and-drop into browser window

3. You should see the tracker interface with "Connected" status

### Step 7: Start Playing!

- Start or load your Pokemon Emerald save
- The tracker will update every second automatically
- Watch your party, badges, and boxes update in real-time!

## File Structure

```
mgba_scripts/
├── tracker.lua                 # Main Lua script
├── generate_data_tables.sh     # Data table generator
├── pokeemerald.sym             # Symbol file (YOU MUST COPY THIS)
├── tracker_data.json           # Generated data (created by script)
├── modules/
│   ├── pokemon_decrypt.lua     # Pokemon data decryption
│   ├── species_data.lua        # Pokemon name lookup (auto-generated)
│   └── move_data.lua           # Move name lookup (auto-generated)
└── frontend/
    ├── index.html              # Web interface
    ├── style.css               # Styling
    └── script.js               # Frontend logic
```

## Configuration

Edit `tracker.lua` to customize settings:

```lua
local CONFIG = {
    SYM_FILE = "pokeemerald.sym",       -- Symbol file path
    OUTPUT_FILE = "tracker_data.json",   -- Output path
    UPDATE_INTERVAL = 60,                -- Frames (60 = 1 second)
    ENABLE_DEBUG = true,                 -- Console logging
    ENABLE_BOXES = true,                 -- Read PC boxes (slower)
    MAX_BOXES = 14,                      -- Number of boxes
    BOX_SLOTS = 30,                      -- Slots per box
}
```

## Troubleshooting

### "Symbol not found" errors

**Cause**: Symbol file is missing or outdated.

**Fix**:
```bash
# Regenerate symbol file
cd /path/to/pokeemerald-expansion
make syms
cp pokeemerald.sym mgba_scripts/
```

### "Could not open symbol file" error

**Cause**: `pokeemerald.sym` is not in the correct location.

**Fix**: Copy the `.sym` file to the same directory as `tracker.lua`:
```bash
cp pokeemerald.sym mgba_scripts/
```

### Frontend shows "Disconnected"

**Cause**:
1. Lua script not running
2. `tracker_data.json` not being created
3. Browser security blocking file access

**Fix**:
1. Check mGBA console for error messages
2. Verify `tracker_data.json` exists in `mgba_scripts/`
3. Try opening frontend from a local web server:
   ```bash
   cd mgba_scripts/frontend
   python3 -m http.server 8000
   # Then open: http://localhost:8000
   ```

### No Pokemon showing in party

**Cause**:
1. No save file loaded
2. Symbol addresses incorrect
3. Memory reading error

**Fix**:
1. Load a save game with Pokemon in party
2. Rebuild ROM and regenerate symbol file
3. Check mGBA console for errors

### Wrong Pokemon names/moves

**Cause**: Data tables not generated or outdated.

**Fix**:
```bash
cd mgba_scripts
./generate_data_tables.sh
```

Then restart the Lua script in mGBA.

### Crashes or freezes

**Cause**: Incompatible mGBA version or corrupted ROM.

**Fix**:
1. Update to mGBA 0.10.2 or later
2. Rebuild ROM from clean state:
   ```bash
   make clean
   make
   make syms
   ```

## Advanced Usage

### Running a Local Web Server

For better file access and no CORS issues:

```bash
cd mgba_scripts/frontend

# Python 3
python3 -m http.server 8000

# Python 2
python -m SimpleHTTPServer 8000

# Node.js (with http-server)
npx http-server -p 8000
```

Then open: http://localhost:8000

### Reading PC Boxes

By default, only the current box is read to improve performance. To read all boxes:

1. Edit `tracker.lua`
2. Modify the `readBoxes()` function to loop through all boxes
3. Increase `UPDATE_INTERVAL` to reduce CPU usage

### Exporting to Other Formats

The `tracker_data.json` file can be consumed by any application. Example uses:
- Stream overlays (OBS, etc.)
- Discord bots
- Mobile apps
- Statistics tracking

### Debugging

Open browser console (F12) and use:

```javascript
// Get current data
window.TrackerDebug.getData()

// Force immediate update
window.TrackerDebug.forceUpdate()

// Stop/start updates
window.TrackerDebug.toggleUpdates()

// View config
window.TrackerDebug.getConfig()
```

In mGBA console:
- Enable `ENABLE_DEBUG` in tracker.lua
- Watch for memory read operations
- Check symbol resolution

## Updating After Code Changes

Every time you modify your pokeemerald-expansion code:

```bash
# 1. Rebuild
make clean
make

# 2. Regenerate symbols
make syms

# 3. Copy new symbol file
cp pokeemerald.sym mgba_scripts/

# 4. Reload Lua script in mGBA
#    Tools > Scripting > File > Reload script
```

**Memory addresses change with every recompile**, so the symbol file must be regenerated!

## Performance Tips

1. **Reduce update frequency**: Set `UPDATE_INTERVAL` to 120 (2 seconds) or higher
2. **Disable box reading**: Set `ENABLE_BOXES = false` in config
3. **Close unused browser tabs**: The frontend uses minimal resources
4. **Use mGBA's frame limiter**: Helps maintain stable timing

## Known Limitations

1. **PC Boxes**: Only current box is read by default (performance)
2. **Encryption**: Pokemon data must be decrypted (slightly slower)
3. **Symbol dependency**: Requires rebuild + regenerate after code changes
4. **mGBA only**: Does not work with other emulators (VBA, BizHawk, etc.)
5. **Local files**: Browser security may require local web server

## Future Enhancements

Potential features for future versions:
- [ ] Pokemon sprites in UI
- [ ] Type effectiveness calculator
- [ ] EV/IV display and tracker
- [ ] Battle statistics
- [ ] WebSocket for instant updates
- [ ] Mobile-responsive design
- [ ] Export to spreadsheet/database
- [ ] Nuzlocke mode tracking

## Credits

- **mGBA**: endrift and contributors (https://mgba.io/)
- **pokeemerald-expansion**: RH-Hideout team (https://github.com/rh-hideout/pokeemerald-expansion)
- **Gen 3 Data Structures**: pret team and Bulbapedia contributors

## License

This project is provided as-is for use with pokeemerald-expansion.

The Pokemon trademark and all Pokemon names are property of Nintendo/Game Freak/The Pokemon Company.

## Support

For issues:
1. Check this README's troubleshooting section
2. Verify mGBA version is 0.10+
3. Ensure symbol file is regenerated after builds
4. Check mGBA console for error messages
5. Open an issue with:
   - mGBA version
   - Error messages from console
   - Steps to reproduce

## Version History

### v1.0.0 (2025-11-18)
- Initial release
- Party Pokemon tracking
- Badge tracking
- PC box overview
- Real-time updates
- Web frontend
- Symbol file integration

---

**Enjoy tracking your Pokemon adventure! 🎮✨**
