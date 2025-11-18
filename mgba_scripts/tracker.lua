--[[
    Pokemon Emerald Live Tracker for mGBA

    This script reads live gameplay data from Pokemon Emerald and exports it
    to JSON for display in a web frontend.

    Usage:
    1. Build your ROM: make && make syms
    2. Place pokeemerald.sym in the same directory as this script
    3. Load ROM in mGBA
    4. Load this script: Tools -> Scripting -> Load script
    5. Open frontend/index.html in a browser

    The script will create/update tracker_data.json every second.
--]]

-- Configuration
local CONFIG = {
    SYM_FILE = "pokeemerald.sym",           -- Symbol file path
    OUTPUT_FILE = "tracker_data.json",       -- JSON output file
    UPDATE_INTERVAL = 60,                    -- Frames between updates (60 = 1 second)
    ENABLE_DEBUG = true,                     -- Print debug messages
    ENABLE_BOXES = true,                     -- Read PC boxes (slower)
    MAX_BOXES = 14,                          -- Number of PC boxes
    BOX_SLOTS = 30,                          -- Slots per box
}

-- Load modules
local pokemon_decrypt = require("modules.pokemon_decrypt")
local species_data = require("modules.species_data")
local move_data = require("modules.move_data")

-- Global state
local symbols = {}
local frameCounter = 0
local memoryRegions = {}
local lastError = nil

--[[
    Utility Functions
--]]

-- Debug logging
local function debug(msg)
    if CONFIG.ENABLE_DEBUG then
        console:log("[Tracker] " .. msg)
    end
end

-- Error logging
local function logError(msg)
    console:error("[Tracker ERROR] " .. msg)
    lastError = msg
end

-- Convert number to hex string
local function toHex(num)
    return string.format("0x%08X", num)
end

--[[
    Symbol File Parser
--]]

-- Load and parse symbol file
local function loadSymbols(filename)
    debug("Loading symbol file: " .. filename)
    local syms = {}
    local count = 0

    local file = io.open(filename, "r")
    if not file then
        logError("Could not open symbol file: " .. filename)
        return nil
    end

    for line in file:lines() do
        -- Format: "ADDRESS TYPE SIZE NAME" or "ADDRESS TYPE NAME"
        -- Example: "02024744 g gPlayerParty"
        local addr, typ, name = line:match("(%x+)%s+(%w)%s+%S*%s*(%S+)")
        if not addr then
            -- Try simpler format
            addr, typ, name = line:match("(%x+)%s+(%w)%s+(%S+)")
        end

        if addr and name then
            syms[name] = tonumber(addr, 16)
            count = count + 1
        end
    end

    file:close()
    debug(string.format("Loaded %d symbols", count))
    return syms
end

-- Get symbol address with error checking
local function getSymbol(name)
    local addr = symbols[name]
    if not addr then
        logError("Symbol not found: " .. name)
        return nil
    end
    return addr
end

--[[
    Memory Access Functions
--]]

-- Initialize memory regions
local function initMemory()
    if not emu then
        logError("Emulator not initialized")
        return false
    end

    memoryRegions = {
        iwram = emu:getMemoryBlock("iwram"),
        ewram = emu:getMemoryBlock("wram"),
        rom = emu:getMemoryBlock("cart0"),
    }

    if not memoryRegions.iwram or not memoryRegions.ewram then
        logError("Could not access memory regions")
        return false
    end

    debug("Memory regions initialized")
    return true
end

-- Convert GBA address to memory region and offset
local function addressToRegion(addr)
    if addr >= 0x02000000 and addr < 0x02040000 then
        -- EWRAM
        return memoryRegions.ewram, addr - 0x02000000
    elseif addr >= 0x03000000 and addr < 0x03008000 then
        -- IWRAM
        return memoryRegions.iwram, addr - 0x03000000
    elseif addr >= 0x08000000 and addr < 0x0E000000 then
        -- ROM
        return memoryRegions.rom, addr - 0x08000000
    else
        return nil, nil
    end
end

-- Safe memory read functions
local function read8(addr)
    local region, offset = addressToRegion(addr)
    if not region then return 0 end
    return region:read8(offset)
end

local function read16(addr)
    local region, offset = addressToRegion(addr)
    if not region then return 0 end
    return region:read16(offset)
end

local function read32(addr)
    local region, offset = addressToRegion(addr)
    if not region then return 0 end
    return region:read32(offset)
end

local function readString(addr, maxLen)
    local region, offset = addressToRegion(addr)
    if not region then return "" end

    local str = {}
    for i = 0, maxLen - 1 do
        local byte = region:read8(offset + i)
        if byte == 0 or byte == 0xFF then break end
        table.insert(str, string.char(byte))
    end
    return table.concat(str)
end

-- Read bytes into table
local function readBytes(addr, count)
    local region, offset = addressToRegion(addr)
    if not region then return {} end

    local bytes = {}
    for i = 0, count - 1 do
        bytes[i] = region:read8(offset + i)
    end
    return bytes
end

--[[
    Pokemon Data Reading
--]]

-- Read a single Pokemon from memory
local function readPokemon(baseAddr)
    local mon = {
        species = 0,
        level = 0,
        hp = 0,
        maxHP = 0,
        attack = 0,
        defense = 0,
        speed = 0,
        spAttack = 0,
        spDefense = 0,
        moves = {},
        nickname = "",
        personality = 0,
        otId = 0,
        experience = 0,
        friendship = 0,
        isShiny = false,
    }

    -- Read BoxPokemon portion (first 80 bytes)
    mon.personality = read32(baseAddr + 0)
    mon.otId = read32(baseAddr + 4)
    mon.nickname = readString(baseAddr + 8, 10)

    -- Read encrypted substructures (48 bytes from offset 32)
    local encryptedData = readBytes(baseAddr + 32, 48)

    -- Decrypt Pokemon data
    local decrypted = pokemon_decrypt.decryptPokemon(encryptedData, mon.personality, mon.otId)
    if decrypted then
        mon.species = decrypted.species or 0
        mon.moves = decrypted.moves or {0, 0, 0, 0}
        mon.experience = decrypted.experience or 0
        mon.friendship = decrypted.friendship or 0
        mon.evs = decrypted.evs or {0, 0, 0, 0, 0, 0}
        mon.ivs = decrypted.ivs or {0, 0, 0, 0, 0, 0}
    end

    -- Read Pokemon portion (battle stats, starting at offset 80)
    mon.level = read8(baseAddr + 84)
    mon.hp = read16(baseAddr + 86)
    mon.maxHP = read16(baseAddr + 88)
    mon.attack = read16(baseAddr + 90)
    mon.defense = read16(baseAddr + 92)
    mon.speed = read16(baseAddr + 94)
    mon.spAttack = read16(baseAddr + 96)
    mon.spDefense = read16(baseAddr + 98)

    -- Calculate if shiny (simplified check)
    mon.isShiny = pokemon_decrypt.isShiny(mon.personality, mon.otId)

    return mon
end

-- Read party Pokemon
local function readParty()
    local partyCountAddr = getSymbol("gPlayerPartyCount")
    local partyAddr = getSymbol("gPlayerParty")

    if not partyCountAddr or not partyAddr then
        return nil
    end

    local count = read8(partyCountAddr)
    if count > 6 then count = 6 end

    local party = {}
    for i = 0, count - 1 do
        local monAddr = partyAddr + (i * 100)  -- Each Pokemon is 100 bytes
        local mon = readPokemon(monAddr)

        if mon.species > 0 then
            -- Add human-readable names
            mon.speciesName = species_data.getName(mon.species)
            mon.moveNames = {}
            for j, moveId in ipairs(mon.moves) do
                mon.moveNames[j] = move_data.getName(moveId)
            end
            table.insert(party, mon)
        end
    end

    return party
end

-- Read PC boxes
local function readBoxes()
    if not CONFIG.ENABLE_BOXES then
        return {}
    end

    local storagePtrAddr = getSymbol("gPokemonStoragePtr")
    if not storagePtrAddr then
        return {}
    end

    local storageAddr = read32(storagePtrAddr)
    if storageAddr == 0 then
        return {}
    end

    local currentBox = read8(storageAddr + 0)
    local boxes = {}

    -- Only read current box for performance
    local boxOffset = storageAddr + 4 + (currentBox * 30 * 80)  -- Skip currentBox byte + previous boxes
    local box = {
        number = currentBox,
        pokemon = {}
    }

    for slot = 0, CONFIG.BOX_SLOTS - 1 do
        local monAddr = boxOffset + (slot * 80)  -- BoxPokemon is 80 bytes
        local species = read16(monAddr + 32)  -- Species is in encrypted data, simplified read

        if species > 0 and species < 9999 then
            -- For box Pokemon, we only have BoxPokemon struct (80 bytes, no battle stats)
            -- For simplicity, read basic info only
            local mon = {
                species = species,
                speciesName = species_data.getName(species),
                slot = slot
            }
            table.insert(box.pokemon, mon)
        end
    end

    boxes[currentBox] = box
    return boxes
end

-- Read badge data
local function readBadges()
    local saveBlock1Addr = getSymbol("gSaveBlock1Ptr")
    if not saveBlock1Addr then
        return {}
    end

    local sb1Addr = read32(saveBlock1Addr)
    if sb1Addr == 0 then
        return {}
    end

    -- Flags start at offset 0x1270 in SaveBlock1
    local flagsAddr = sb1Addr + 0x1270

    -- Badge flag IDs (these are constants from your codebase)
    local BADGE_FLAGS = {
        0x867,  -- FLAG_BADGE01_GET (Stone Badge)
        0x868,  -- FLAG_BADGE02_GET (Knuckle Badge)
        0x869,  -- FLAG_BADGE03_GET (Dynamo Badge)
        0x86A,  -- FLAG_BADGE04_GET (Heat Badge)
        0x86B,  -- FLAG_BADGE05_GET (Balance Badge)
        0x86C,  -- FLAG_BADGE06_GET (Feather Badge)
        0x86D,  -- FLAG_BADGE07_GET (Mind Badge)
        0x86E,  -- FLAG_BADGE08_GET (Rain Badge)
    }

    local badges = {}
    for i, flagId in ipairs(BADGE_FLAGS) do
        local byteOffset = math.floor(flagId / 8)
        local bitOffset = flagId % 8
        local byte = read8(flagsAddr + byteOffset)
        badges[i] = ((byte >> bitOffset) & 1) == 1
    end

    return badges
end

-- Read trainer info
local function readTrainerInfo()
    local saveBlock2Addr = getSymbol("gSaveBlock2Ptr")
    if not saveBlock2Addr then
        return {}
    end

    local sb2Addr = read32(saveBlock2Addr)
    if sb2Addr == 0 then
        return {}
    end

    return {
        name = readString(sb2Addr + 0, 7),
        gender = read8(sb2Addr + 8),
        playTime = {
            hours = read16(sb2Addr + 0x0E),
            minutes = read8(sb2Addr + 0x10),
            seconds = read8(sb2Addr + 0x11),
        }
    }
end

--[[
    JSON Export
--]]

-- Escape string for JSON
local function jsonEscape(str)
    str = string.gsub(str, "\\", "\\\\")
    str = string.gsub(str, '"', '\\"')
    str = string.gsub(str, "\n", "\\n")
    str = string.gsub(str, "\r", "\\r")
    str = string.gsub(str, "\t", "\\t")
    return str
end

-- Convert table to JSON string (simple implementation)
local function toJSON(obj, indent)
    indent = indent or 0
    local spaces = string.rep("  ", indent)
    local nextSpaces = string.rep("  ", indent + 1)

    if type(obj) == "table" then
        -- Check if array or object
        local isArray = true
        local count = 0
        for k, v in pairs(obj) do
            count = count + 1
            if type(k) ~= "number" or k ~= count then
                isArray = false
                break
            end
        end

        if isArray and count > 0 then
            -- Array
            local parts = {}
            for i, v in ipairs(obj) do
                table.insert(parts, toJSON(v, indent + 1))
            end
            return "[\n" .. nextSpaces .. table.concat(parts, ",\n" .. nextSpaces) .. "\n" .. spaces .. "]"
        else
            -- Object
            local parts = {}
            for k, v in pairs(obj) do
                local key = '"' .. jsonEscape(tostring(k)) .. '"'
                table.insert(parts, key .. ": " .. toJSON(v, indent + 1))
            end
            if #parts == 0 then
                return "{}"
            end
            return "{\n" .. nextSpaces .. table.concat(parts, ",\n" .. nextSpaces) .. "\n" .. spaces .. "}"
        end
    elseif type(obj) == "string" then
        return '"' .. jsonEscape(obj) .. '"'
    elseif type(obj) == "number" then
        return tostring(obj)
    elseif type(obj) == "boolean" then
        return obj and "true" or "false"
    else
        return "null"
    end
end

-- Export data to JSON file
local function exportData(data)
    local json = toJSON(data)
    local file = io.open(CONFIG.OUTPUT_FILE, "w")
    if not file then
        logError("Could not open output file: " .. CONFIG.OUTPUT_FILE)
        return false
    end

    file:write(json)
    file:close()
    return true
end

--[[
    Main Update Loop
--]]

-- Collect all tracker data
local function collectData()
    local data = {
        timestamp = os.time(),
        trainer = readTrainerInfo(),
        party = readParty(),
        badges = readBadges(),
        boxes = readBoxes(),
        error = lastError,
    }

    -- Calculate badge count
    local badgeCount = 0
    for _, has in ipairs(data.badges) do
        if has then badgeCount = badgeCount + 1 end
    end
    data.badgeCount = badgeCount

    return data
end

-- Frame callback
local function onFrame()
    frameCounter = frameCounter + 1

    if frameCounter >= CONFIG.UPDATE_INTERVAL then
        frameCounter = 0

        local data = collectData()
        if exportData(data) then
            debug("Data exported successfully")
        end
    end
end

--[[
    Initialization
--]]

-- Initialize the tracker
local function init()
    console:log("=== Pokemon Emerald Live Tracker ===")
    console:log("Initializing...")

    -- Load symbols
    symbols = loadSymbols(CONFIG.SYM_FILE)
    if not symbols then
        logError("Failed to load symbols. Make sure " .. CONFIG.SYM_FILE .. " exists.")
        return false
    end

    -- Initialize memory
    if not initMemory() then
        return false
    end

    -- Register frame callback
    callbacks:add("frame", onFrame)

    console:log("Tracker initialized successfully!")
    console:log("Output file: " .. CONFIG.OUTPUT_FILE)
    console:log("Update interval: " .. CONFIG.UPDATE_INTERVAL .. " frames")
    console:log("")

    -- Do initial export
    local data = collectData()
    exportData(data)

    return true
end

-- Start the tracker
if emu then
    init()
else
    console:error("This script must be run with a game loaded!")
end
