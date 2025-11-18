# mGBA Live Gameplay Tracker - Design Document

## Executive Summary

**Feasibility: ✅ HIGHLY FEASIBLE**

This project is not only possible but follows well-established patterns in the Pokemon ROM hacking community. Similar tools like Ironmon-Tracker and yPokeStats already implement this functionality. Your pokeemerald-expansion codebase provides excellent foundation with well-defined data structures and automatic symbol file generation.

**Estimated Effort: 2-3 weeks for MVP, 4-6 weeks for polished release**

---

## 1. Project Overview

### 1.1 Goals
- Read live gameplay data from mGBA emulator using Lua scripting
- Capture player's current party (species, level, moves, stats)
- Display boxed Pokemon data
- Track badge collection progress
- Present data in a simple, real-time updating frontend

### 1.2 Key Challenge: Dynamic Memory Addresses
You correctly identified that memory addresses change with every recompile. The solution is **symbol files** (.sym), which map human-readable variable names to their runtime memory addresses.

---

## 2. Technical Architecture

### 2.1 System Components

```
┌─────────────────┐
│   mGBA Emulator │
│  (Running ROM)  │
└────────┬────────┘
         │ Memory Access
         ↓
┌─────────────────┐
│  Lua Script     │◄──── Reads symbol mappings
│  (Memory Reader)│      from .sym file
└────────┬────────┘
         │ JSON/WebSocket
         ↓
┌─────────────────┐
│   Web Frontend  │
│  (HTML/CSS/JS)  │
└─────────────────┘
```

### 2.2 Data Flow

1. **Build Phase**: Compile ROM → Generate .sym file mapping symbols to addresses
2. **Runtime Phase**: Lua script reads .sym → Maps variable names to addresses
3. **Memory Reading**: Lua accesses memory using resolved addresses
4. **Data Export**: Lua formats and sends data to frontend
5. **Display**: Frontend updates UI in real-time

---

## 3. Memory Structure Analysis

### 3.1 Key Data Structures

Based on analysis of your codebase:

#### Player Party (`gPlayerParty`)
**Location**: `include/pokemon.h:677-680`
```c
extern u8 gPlayerPartyCount;              // Number of Pokemon in party (0-6)
extern struct Pokemon gPlayerParty[6];    // Party array
```

**Structure Size**: ~100 bytes per Pokemon
- `struct BoxPokemon box` (80 bytes) - Core data
- Level, HP, stats (20 bytes) - Battle-ready info

#### PC Box Storage (`gPokemonStoragePtr`)
**Location**: `include/pokemon_storage_system.h:20-27`
```c
extern struct PokemonStorage *gPokemonStoragePtr;

struct PokemonStorage {
    u8 currentBox;                                    // 0-13
    struct BoxPokemon boxes[14][30];                  // 14 boxes × 30 slots
    u8 boxNames[14][9];                               // Box names
    u8 boxWallpapers[14];                             // Cosmetic data
};
```

**Total Pokemon Storage**: 420 Pokemon (14 boxes × 30 slots)

#### Badge Data (`gSaveBlock1Ptr->flags`)
**Location**: `include/constants/flags.h`
```c
extern const u16 gBadgeFlags[NUM_BADGES];

// Access via:
bool FlagGet(u16 flagId);
// e.g., FlagGet(FLAG_BADGE01_GET) → true if Stone Badge obtained
```

**Structure**: Stored as bit flags in SaveBlock1

### 3.2 Memory Regions

| Data Type | Memory Region | Access Method |
|-----------|---------------|---------------|
| Player Party | IWRAM | Direct pointer `gPlayerParty` |
| PC Boxes | EWRAM | Indirect `gPokemonStoragePtr->boxes` |
| Badges | EWRAM | Bit flags in `gSaveBlock1Ptr->flags` |
| Save Data | EWRAM | `gSaveBlock1Ptr`, `gSaveBlock2Ptr` |

---

## 4. Symbol File Solution

### 4.1 What are Symbol Files?

Symbol files map human-readable names to memory addresses:

```
# Example pokeemerald.sym format
02024744 g gPlayerPartyCount
02024748 g gPlayerParty
0203CC40 g gPokemonStoragePtr
02026E50 g gSaveBlock1Ptr
```

**Format**: `[8-digit hex address] [type] [symbol name]`

### 4.2 Generation Process

Your Makefile already supports symbol file generation:

```bash
make              # Build ROM → pokeemerald.gba
make syms         # Generate symbol file → pokeemerald.sym
```

**Generation Command** (line 520):
```bash
$(OBJDUMP) -t $(ELF) | sort -u | grep -E "^0[2389]" | \
perl -p -e 's/^(\w{8}) (\w).{6} \S+\t(\w{8}) (\S+)$/\1 \2 \3 \4/g' > pokeemerald.sym
```

This extracts symbols from the ELF file and formats them for emulator use.

### 4.3 Address Stability

**Key Insight**: Addresses change between builds BUT symbol files are regenerated automatically.

**Workflow**:
1. Modify code → Recompile ROM
2. Run `make syms` → New symbol file with updated addresses
3. Lua script reloads .sym → Uses new addresses
4. No manual intervention required!

---

## 5. mGBA Lua Scripting

### 5.1 Capabilities

mGBA (v0.10+) provides comprehensive Lua scripting:

- **Memory Access**: Read/write via address spaces and memory domains
- **Callbacks**: Frame updates, save events, button presses
- **Data Types**: Read bytes, words, longs, strings
- **No Restrictions**: Full access to IWRAM, EWRAM, ROM, SRAM

### 5.2 Basic Memory Reading

```lua
-- Example: Read a u32 value
local memory = emu:getMemoryBlock("iwram")
local value = memory:read32(0x00024744)  -- Offset from IWRAM base

-- Example: Read a string
local str = memory:readString(offset, length)
```

### 5.3 Symbol File Parser (Lua)

```lua
-- Load and parse .sym file
function loadSymbols(symFile)
    local symbols = {}
    for line in io.lines(symFile) do
        local addr, typ, name = line:match("(%x+)%s+(%w)%s+(%S+)")
        if addr then
            symbols[name] = tonumber(addr, 16)
        end
    end
    return symbols
end

-- Usage
local syms = loadSymbols("pokeemerald.sym")
local partyAddr = syms["gPlayerParty"]
```

### 5.4 Pokemon Data Reading

```lua
-- Read Pokemon struct
function readPokemon(memory, offset)
    local mon = {}

    -- Read from struct BoxPokemon (first 80 bytes)
    mon.personality = memory:read32(offset + 0)
    mon.otId = memory:read32(offset + 4)
    mon.nickname = memory:readString(offset + 8, 10)

    -- Read substructs (encrypted, needs decryption)
    -- ... species, moves, EVs, IVs ...

    -- Read from struct Pokemon (next 20 bytes)
    mon.level = memory:read8(offset + 84)
    mon.hp = memory:read16(offset + 86)
    mon.maxHP = memory:read16(offset + 88)
    mon.attack = memory:read16(offset + 90)
    -- ... remaining stats ...

    return mon
end
```

**Important**: Pokemon data substructures are encrypted. You'll need to implement the decryption algorithm (well-documented in the community).

---

## 6. Data Extraction Details

### 6.1 Party Pokemon

**Memory Layout**:
```
gPlayerPartyCount: 1 byte  → Number of Pokemon (0-6)
gPlayerParty[0]:   100 bytes → First Pokemon
gPlayerParty[1]:   100 bytes → Second Pokemon
...
gPlayerParty[5]:   100 bytes → Sixth Pokemon
```

**Key Fields** (from `struct Pokemon`):
- `species` (u16): Pokemon ID (Bulbasaur=1, etc.)
- `level` (u8): Current level
- `moves[4]` (u16 array): Four move IDs
- `hp`, `maxHP`: Current/max hit points
- `attack`, `defense`, `speed`, `spAttack`, `spDefense`: Stats
- `nickname`: 10-character name
- `experience`: Total EXP

### 6.2 PC Box Pokemon

**Memory Layout**:
```
gPokemonStoragePtr->currentBox: 1 byte → Active box (0-13)
gPokemonStoragePtr->boxes[box][slot]: 80 bytes per Pokemon
```

**Considerations**:
- 420 total Pokemon (14 boxes × 30 slots)
- Each is `struct BoxPokemon` (80 bytes, no battle stats)
- Empty slots have species = 0
- Reading all boxes: ~33KB of data

**Optimization**: Only read non-empty slots or current box.

### 6.3 Badges

**Implementation**:
```lua
-- Badge flag IDs (from constants/flags.h)
local BADGE_FLAGS = {
    FLAG_BADGE01_GET,  -- Stone Badge
    FLAG_BADGE02_GET,  -- Knuckle Badge
    -- ... up to 8 ...
}

function getBadges(memory, flagsBaseAddr)
    local badges = {}
    for i, flag in ipairs(BADGE_FLAGS) do
        local byteOffset = math.floor(flag / 8)
        local bitOffset = flag % 8
        local byte = memory:read8(flagsBaseAddr + byteOffset)
        badges[i] = (byte & (1 << bitOffset)) ~= 0
    end
    return badges
end
```

**Location**: `gSaveBlock1Ptr->flags[NUM_FLAG_BYTES]` (offset 0x1270)

---

## 7. Pokemon Data Decryption

### 7.1 Encryption Overview

Pokemon data is stored in 4 substructures (12 bytes each) in a scrambled order:
- **Growth**: Species, item, experience, PP bonuses
- **Attacks**: Moves and PP
- **EVs & Condition**: Effort values and contest stats
- **Miscellaneous**: Ribbons, IVs, abilities

**Encryption Key**: `personality XOR otId`

### 7.2 Decryption Algorithm

```lua
function decryptPokemon(encryptedData, personality, otId)
    local key = personality ~ otId  -- XOR
    local decrypted = {}

    -- Decrypt 4 substructs (12 bytes each)
    for i = 0, 47, 4 do
        local value = encryptedData[i] ~ (key & 0xFFFF)
        key = (key * 0x41C64E6D + 0x6073) & 0xFFFFFFFF  -- PRNG
        decrypted[i] = value
    end

    -- Unscramble based on personality % 24
    local order = SUBSTRUCT_ORDER[personality % 24]
    return unscramble(decrypted, order)
end
```

**Reference**: This is a standard Gen 3 algorithm, well-documented in:
- `src/pokemon.c:DecryptBoxMon()` in your codebase
- Bulbapedia: "Pokemon data structure (Generation III)"

### 7.3 Species & Move Names

**Challenge**: Memory stores IDs, not names.

**Solution**: Embed lookup tables in Lua script.

```lua
local SPECIES_NAMES = {
    [1] = "Bulbasaur",
    [2] = "Ivysaur",
    [3] = "Venusaur",
    -- ... 898+ species ...
}

local MOVE_NAMES = {
    [1] = "Pound",
    [2] = "Karate Chop",
    -- ... 919+ moves ...
}
```

**Alternative**: Parse from ROM data (species names at fixed offsets).

---

## 8. Frontend Design

### 8.1 Technology Options

#### Option A: Embedded HTML (Simplest)
- mGBA can render HTML in overlay windows
- Lua → JavaScript bridge via mGBA APIs
- **Pros**: No external server, single-file solution
- **Cons**: Limited styling, mGBA-specific

#### Option B: HTTP Server (Most Flexible)
- Lua script runs HTTP server (use `socket` library)
- Serves JSON API: `/api/party`, `/api/boxes`, `/api/badges`
- Separate web page polls or uses WebSocket
- **Pros**: Any browser, modern web tech (React/Vue/Svelte)
- **Cons**: Requires external libraries, more complexity

#### Option C: File Export (Simplest)
- Lua writes JSON to file every frame/second
- HTML page reads file via `fetch()` (needs local server)
- **Pros**: Minimal Lua code
- **Cons**: File I/O overhead, polling delay

**Recommendation**: Start with Option C for MVP, migrate to Option B for polish.

### 8.2 UI Layout Mockup

```
┌────────────────────────────────────────┐
│  Pokemon Emerald - Live Tracker        │
├────────────────────────────────────────┤
│  👤 Trainer: ASH    🕐 Playtime: 12:34 │
│  💰 Money: $12,500  🏆 Badges: 5/8     │
├────────────────────────────────────────┤
│  🎒 Party (6):                          │
│  ┌─────────────────────────────────┐  │
│  │ [🔥] Blaziken      Lv 45  ♂      │  │
│  │ Moves: Blaze Kick, Sky Uppercut │  │
│  │        Slash, Flamethrower       │  │
│  │ HP: 142/142  Atk:120  Def:70    │  │
│  └─────────────────────────────────┘  │
│  ┌─────────────────────────────────┐  │
│  │ [💧] Swampert      Lv 43  ♂      │  │
│  │ ...                              │  │
│  └─────────────────────────────────┘  │
│  ... 4 more ...                        │
├────────────────────────────────────────┤
│  📦 PC Boxes (420 slots):              │
│  Box 1: [🌱][⚡][💧]...  (18/30)     │
│  Box 2: [🔥][❄️]...      (7/30)     │
│  ...                                   │
├────────────────────────────────────────┤
│  🏅 Badges:                             │
│  [✓] Stone  [✓] Knuckle  [✓] Dynamo   │
│  [✓] Heat   [✓] Balance  [ ] Feather  │
│  [ ] Mind   [ ] Rain                   │
└────────────────────────────────────────┘
```

### 8.3 Styling Approach

**CSS Framework**: Tailwind CSS or Bootstrap
**Theme**: Dark mode (common for gaming tools)
**Responsive**: Desktop-first (mobile optional)
**Type Icons**: Embed sprite sheet or use Unicode emoji

---

## 9. Implementation Phases

### Phase 1: Symbol File Integration (3-5 days)
**Deliverables**:
- Lua script to parse .sym files
- Map key symbols: `gPlayerParty`, `gPlayerPartyCount`, `gPokemonStoragePtr`
- Test memory reads with hardcoded offsets

**Validation**: Print party count and first Pokemon's level to console.

### Phase 2: Party Data Reader (5-7 days)
**Deliverables**:
- Implement Pokemon struct parser
- Decrypt Pokemon substructures
- Extract species, level, moves, stats
- Species/move name lookup tables

**Validation**: Print full party roster with names and moves.

### Phase 3: Badge & Box Reader (3-5 days)
**Deliverables**:
- Read badge flags from SaveBlock1
- Parse PC box data (at least current box)
- Filter empty slots

**Validation**: Display badge count and box occupancy.

### Phase 4: Basic Frontend (5-7 days)
**Deliverables**:
- HTML/CSS page with layout
- JSON export from Lua (file or HTTP)
- JavaScript to parse and render data
- Auto-refresh every 1-2 seconds

**Validation**: See live party updates as you play.

### Phase 5: Polish & Features (7-10 days)
**Deliverables**:
- Full box viewer with pagination
- Pokemon sprites (from ROM or online)
- Type icons and stat bars
- Shiny detection (personality-based)
- IV/EV display
- WebSocket for real-time updates

**Validation**: Production-ready tool.

---

## 10. Effort Estimation

### 10.1 MVP (Phases 1-4)
**Time**: 2-3 weeks (20-30 hours)
**Complexity**: Medium
**Skills**: Lua, C structs, HTML/CSS/JS basics

**Breakdown**:
- Symbol parsing: 4 hours
- Party reader: 12 hours (includes decryption)
- Badges & boxes: 6 hours
- Frontend: 8 hours

### 10.2 Full Release (Phases 1-5)
**Time**: 4-6 weeks (40-60 hours)
**Complexity**: Medium-High
**Skills**: + Advanced JavaScript, API design, asset handling

**Additional**:
- Sprites & assets: 10 hours
- WebSocket/HTTP server: 8 hours
- UI polish: 8 hours
- Testing & debugging: 8 hours

### 10.3 Skill Requirements

| Skill | Level | Alternatives |
|-------|-------|--------------|
| Lua | Beginner+ | Python (via mGBA HTTP) |
| C struct knowledge | Basic | Use existing projects as reference |
| Web dev (HTML/CSS/JS) | Intermediate | Use template/framework |
| Binary/hex manipulation | Basic | Use Lua libraries |

**Learning Curve**: If unfamiliar with Lua, add 1 week for learning.

---

## 11. Risks & Mitigations

### Risk 1: Pokemon Decryption Complexity
**Impact**: High (can't read species/moves)
**Mitigation**:
- Use reference implementation from `src/pokemon.c:DecryptBoxMon()`
- Port C code to Lua directly
- Test with known Pokemon from save editor

### Risk 2: Symbol File Changes
**Impact**: Medium (breaks on recompile)
**Mitigation**:
- Document `make syms` workflow clearly
- Auto-detect .sym file changes and reload
- Fallback to heuristic search if symbol missing

### Risk 3: mGBA API Limitations
**Impact**: Low (API is mature)
**Mitigation**:
- Test memory reads early
- Use mGBA forums/Discord for support
- Reference existing projects (Ironmon-Tracker source)

### Risk 4: Frontend Performance
**Impact**: Low (data size is small)
**Mitigation**:
- Throttle updates to 1-2 Hz
- Only send changed data (diff algorithm)
- Use efficient rendering (Virtual DOM or direct manipulation)

---

## 12. Reference Projects

### Existing Implementations

1. **Ironmon-Tracker**
   - Language: Lua (BizHawk emulator)
   - Features: Party tracking, route progress, statistics
   - Relevance: Similar goals, different emulator

2. **yPokeStats**
   - GitHub: [yling/yPokeStats](https://github.com/yling/yPokeStats)
   - Language: Lua
   - Features: Multi-gen support, party display
   - Relevance: Direct inspiration

3. **Pokélink**
   - Features: Export Pokemon to external apps
   - Relevance: Demonstrates real-time data extraction

4. **mGBA-http**
   - GitHub: [nikouu/mGBA-http](https://github.com/nikouu/mGBA-http)
   - Features: HTTP API for mGBA
   - Relevance: Shows HTTP server approach

### Documentation

- **mGBA Scripting Docs**: `https://mgba.io/docs/scripting.html`
- **Bulbapedia Gen 3 Structures**: Comprehensive Pokemon data format
- **pokeemerald Source**: Your own codebase is the best reference!

---

## 13. Recommended Approach

### 13.1 Start Small
1. Build ROM with `make && make syms`
2. Write minimal Lua to read `gPlayerPartyCount`
3. Print to mGBA console
4. Iterate from there

### 13.2 Test with Known Data
- Use save editor to create test party
- Verify Lua reads match expected values
- Reduces debugging guesswork

### 13.3 Use Existing Code
- Port `DecryptBoxMon()` from `src/pokemon.c`
- Copy species/move tables from `include/constants/`
- Don't reinvent the wheel!

### 13.4 Prototype First
- Console output before GUI
- File export before HTTP server
- Ugly but functional > Beautiful but broken

---

## 14. Example Starter Code

### 14.1 Minimal Lua Script

```lua
-- mgba_tracker.lua
-- Place in mGBA scripts folder

-- Load symbol file
function loadSymbols(path)
    local syms = {}
    for line in io.lines(path) do
        local addr, name = line:match("(%x+)%s+%w%s+(%S+)")
        if addr then syms[name] = tonumber(addr, 16) end
    end
    return syms
end

-- Initialize
local syms = loadSymbols("pokeemerald.sym")
local mem = emu:getMemoryBlock("iwram")

-- Main loop
callbacks:add("frame", function()
    -- Read party count
    local partyCountAddr = syms["gPlayerPartyCount"]
    local partyAddr = syms["gPlayerParty"]

    if not partyCountAddr or not partyAddr then
        console:log("Symbols not found!")
        return
    end

    -- Convert to IWRAM offset (subtract 0x02000000)
    local partyCountOffset = partyCountAddr - 0x02000000
    local partyOffset = partyAddr - 0x02000000

    local count = mem:read8(partyCountOffset)
    console:log("Party size: " .. count)

    -- Read first Pokemon's level (offset 84 in struct)
    if count > 0 then
        local level = mem:read8(partyOffset + 84)
        console:log("First Pokemon level: " .. level)
    end
end)
```

### 14.2 Run Instructions

```bash
# Build ROM and symbols
make clean
make
make syms

# Open mGBA
mgba-qt pokeemerald.gba

# Load script: Tools → Scripting → Load script → mgba_tracker.lua
# Open Console: Tools → Scripting → Open console
# Start playing, watch console output
```

---

## 15. Success Metrics

### MVP Success
- ✅ Display all 6 party Pokemon with species names and levels
- ✅ Show 4 moves per Pokemon
- ✅ Badge count display
- ✅ Updates within 2 seconds of in-game changes

### Full Release Success
- ✅ All MVP features
- ✅ PC box viewer with search/filter
- ✅ Pokemon sprites and type icons
- ✅ IV/EV display
- ✅ Real-time updates (<500ms latency)
- ✅ Stable across recompiles (symbol reload)

---

## 16. Conclusion

This project is **highly feasible** and follows proven patterns. The key innovations required:

1. ✅ **Symbol file integration** - Solves address volatility
2. ✅ **Pokemon decryption** - Well-documented algorithm
3. ✅ **mGBA Lua scripting** - Mature API with examples

**Your Advantages**:
- Well-structured codebase (pokeemerald-expansion)
- Automatic symbol generation (`make syms`)
- Active community with reference implementations

**Recommended Path**:
1. Week 1: Learn mGBA Lua basics, implement symbol parsing
2. Week 2: Party reader with decryption
3. Week 3: Basic web frontend with file export
4. Week 4+: Polish, boxes, sprites, real-time updates

**Final Estimate**: 2-3 weeks for MVP, 4-6 weeks for polished tool.

---

## Appendix A: File Reference

### Key Source Files

| File | Purpose |
|------|---------|
| `include/pokemon.h` | Pokemon structs, party globals |
| `include/global.h` | SaveBlock definitions |
| `include/pokemon_storage_system.h` | PC box structures |
| `include/constants/flags.h` | Badge flag IDs |
| `src/pokemon.c` | Decryption algorithms |
| `Makefile` | Symbol file generation (line 519-520) |

### Build Artifacts

| File | Generated By | Purpose |
|------|--------------|---------|
| `pokeemerald.gba` | `make` | Final ROM |
| `pokeemerald.elf` | `make` | ELF with symbols |
| `pokeemerald.map` | `make` | Linker memory map |
| `pokeemerald.sym` | `make syms` | Symbol → address mapping |

---

## Appendix B: Memory Map Reference

### GBA Memory Regions

| Region | Address Range | Purpose |
|--------|---------------|---------|
| BIOS | 0x00000000-0x00003FFF | System ROM |
| EWRAM | 0x02000000-0x0203FFFF | External work RAM (256KB) |
| IWRAM | 0x03000000-0x03007FFF | Internal work RAM (32KB) |
| I/O | 0x04000000-0x040003FF | Hardware registers |
| PAL RAM | 0x05000000-0x050003FF | Palette memory |
| VRAM | 0x06000000-0x06017FFF | Video RAM |
| OAM | 0x07000000-0x070003FF | Object attribute memory |
| ROM | 0x08000000-0x0DFFFFFF | Game pak (up to 96MB) |
| SRAM | 0x0E000000-0x0E00FFFF | Save data (64KB) |

### Likely Locations

- `gPlayerParty`: IWRAM (fast access)
- `gPokemonStoragePtr`: Points to EWRAM (large data)
- `gSaveBlock1Ptr`: Points to EWRAM (persistent data)

**Note**: Exact addresses in .sym file depend on your build configuration.

---

## Appendix C: Resources

### Documentation
- mGBA Scripting: https://mgba.io/docs/scripting.html
- Gen 3 Data Structures: https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon_data_structure_(Generation_III)
- Gen 3 Save Structure: https://bulbapedia.bulbagarden.net/wiki/Save_data_structure_(Generation_III)

### Community
- mGBA Discord: #scripting channel
- PokeCommunity: ROM hacking forums
- pret Discord: pokeemerald decomp support

### Tools
- mGBA: https://mgba.io/downloads.html (use v0.10+ for Lua)
- PKHeX: Save editor for testing (https://projectpokemon.org/home/files/file/1-pkhex/)
- Tilemap Studio: Sprite extraction

---

**Document Version**: 1.0
**Last Updated**: 2025-11-18
**Author**: Claude (Anthropic)
**Target Audience**: pokeemerald-expansion developers
