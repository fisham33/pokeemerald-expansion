--[[
    Pokemon Data Decryption Module

    Implements the Generation 3 Pokemon data encryption/decryption algorithm.
    Pokemon data is stored in 4 substructures (12 bytes each) that are:
    1. XOR encrypted with a key derived from personality and OT ID
    2. Scrambled in one of 24 possible orders based on personality % 24
--]]

local M = {}

-- Substruct order table (24 possible orders based on personality % 24)
local SUBSTRUCT_ORDERS = {
    {0, 1, 2, 3},  -- 0
    {0, 1, 3, 2},  -- 1
    {0, 2, 1, 3},  -- 2
    {0, 2, 3, 1},  -- 3
    {0, 3, 1, 2},  -- 4
    {0, 3, 2, 1},  -- 5
    {1, 0, 2, 3},  -- 6
    {1, 0, 3, 2},  -- 7
    {1, 2, 0, 3},  -- 8
    {1, 2, 3, 0},  -- 9
    {1, 3, 0, 2},  -- 10
    {1, 3, 2, 0},  -- 11
    {2, 0, 1, 3},  -- 12
    {2, 0, 3, 1},  -- 13
    {2, 1, 0, 3},  -- 14
    {2, 1, 3, 0},  -- 15
    {2, 3, 0, 1},  -- 16
    {2, 3, 1, 0},  -- 17
    {3, 0, 1, 2},  -- 18
    {3, 0, 2, 1},  -- 19
    {3, 1, 0, 2},  -- 20
    {3, 1, 2, 0},  -- 21
    {3, 2, 0, 1},  -- 22
    {3, 2, 1, 0},  -- 23
}

--[[
    Bit manipulation helpers
--]]

-- Ensure value fits in 32-bit unsigned
local function u32(val)
    return val & 0xFFFFFFFF
end

-- Ensure value fits in 16-bit unsigned
local function u16(val)
    return val & 0xFFFF
end

-- Read 16-bit value from byte table (little-endian)
local function read16FromBytes(bytes, offset)
    local low = bytes[offset] or 0
    local high = bytes[offset + 1] or 0
    return (high << 8) | low
end

-- Read 32-bit value from byte table (little-endian)
local function read32FromBytes(bytes, offset)
    local b0 = bytes[offset] or 0
    local b1 = bytes[offset + 1] or 0
    local b2 = bytes[offset + 2] or 0
    local b3 = bytes[offset + 3] or 0
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
end

--[[
    Pokemon PRNG (used for encryption)
--]]

local function prng(seed)
    return u32((seed * 0x41C64E6D) + 0x6073)
end

--[[
    Decryption Functions
--]]

-- Decrypt the 48 bytes of Pokemon substructure data
function M.decryptPokemon(encryptedBytes, personality, otId)
    if not encryptedBytes or #encryptedBytes ~= 48 then
        return nil
    end

    -- Calculate encryption key
    local key = u32(personality ~ otId)

    -- Decrypt 48 bytes (12 words of 32-bit)
    local decrypted = {}
    for i = 0, 47, 4 do
        -- Read encrypted 32-bit word
        local encrypted = read32FromBytes(encryptedBytes, i)

        -- Decrypt with current key
        local decryptedWord = u32(encrypted ~ key)

        -- Store as bytes (little-endian)
        decrypted[i] = decryptedWord & 0xFF
        decrypted[i + 1] = (decryptedWord >> 8) & 0xFF
        decrypted[i + 2] = (decryptedWord >> 16) & 0xFF
        decrypted[i + 3] = (decryptedWord >> 24) & 0xFF

        -- Advance PRNG for next key
        key = prng(key)
    end

    -- Unscramble substructures
    local order = SUBSTRUCT_ORDERS[(personality % 24) + 1]
    local unscrambled = {}

    for i = 0, 3 do
        local srcOffset = order[i + 1] * 12
        local dstOffset = i * 12

        for j = 0, 11 do
            unscrambled[dstOffset + j] = decrypted[srcOffset + j]
        end
    end

    -- Parse substructures
    return M.parseSubstructures(unscrambled)
end

-- Parse the four 12-byte substructures
function M.parseSubstructures(data)
    local pokemon = {}

    -- Growth substruct (offset 0-11)
    pokemon.species = read16FromBytes(data, 0)
    pokemon.heldItem = read16FromBytes(data, 2)
    pokemon.experience = read32FromBytes(data, 4)
    pokemon.ppBonuses = data[8] or 0
    pokemon.friendship = data[9] or 0

    -- Attacks substruct (offset 12-23)
    pokemon.moves = {}
    pokemon.moves[1] = read16FromBytes(data, 12)
    pokemon.moves[2] = read16FromBytes(data, 14)
    pokemon.moves[3] = read16FromBytes(data, 16)
    pokemon.moves[4] = read16FromBytes(data, 18)
    pokemon.pp = {}
    pokemon.pp[1] = data[20] or 0
    pokemon.pp[2] = data[21] or 0
    pokemon.pp[3] = data[22] or 0
    pokemon.pp[4] = data[23] or 0

    -- EVs & Condition substruct (offset 24-35)
    pokemon.evs = {}
    pokemon.evs[1] = data[24] or 0  -- HP
    pokemon.evs[2] = data[25] or 0  -- Attack
    pokemon.evs[3] = data[26] or 0  -- Defense
    pokemon.evs[4] = data[27] or 0  -- Speed
    pokemon.evs[5] = data[28] or 0  -- Sp. Attack
    pokemon.evs[6] = data[29] or 0  -- Sp. Defense
    pokemon.coolness = data[30] or 0
    pokemon.beauty = data[31] or 0
    pokemon.cuteness = data[32] or 0
    pokemon.smartness = data[33] or 0
    pokemon.toughness = data[34] or 0
    pokemon.feel = data[35] or 0

    -- Misc substruct (offset 36-47)
    pokemon.pokerus = data[36] or 0
    pokemon.metLocation = data[37] or 0
    local origins = read16FromBytes(data, 38)
    pokemon.metLevel = origins & 0x7F
    pokemon.metGame = (origins >> 7) & 0xF
    pokemon.pokeball = (origins >> 11) & 0xF
    pokemon.otGender = (origins >> 15) & 1

    local ivsEggAbility = read32FromBytes(data, 40)
    pokemon.ivs = {}
    pokemon.ivs[1] = ivsEggAbility & 31        -- HP
    pokemon.ivs[2] = (ivsEggAbility >> 5) & 31  -- Attack
    pokemon.ivs[3] = (ivsEggAbility >> 10) & 31 -- Defense
    pokemon.ivs[4] = (ivsEggAbility >> 15) & 31 -- Speed
    pokemon.ivs[5] = (ivsEggAbility >> 20) & 31 -- Sp. Attack
    pokemon.ivs[6] = (ivsEggAbility >> 25) & 31 -- Sp. Defense
    pokemon.isEgg = ((ivsEggAbility >> 30) & 1) == 1
    pokemon.abilityNum = (ivsEggAbility >> 31) & 1

    local ribbons = read32FromBytes(data, 44)
    pokemon.ribbons = ribbons
    pokemon.obedient = ((ribbons >> 31) & 1) == 1

    return pokemon
end

--[[
    Shiny Calculation
--]]

-- Check if a Pokemon is shiny based on personality and OT ID
function M.isShiny(personality, otId)
    -- Split into trainer ID and secret ID
    local tid = otId & 0xFFFF
    local sid = (otId >> 16) & 0xFFFF

    -- Split personality into high and low words
    local pidHigh = (personality >> 16) & 0xFFFF
    local pidLow = personality & 0xFFFF

    -- XOR all four values
    local shinyValue = tid ~ sid ~ pidHigh ~ pidLow

    -- Shiny if result < 8
    return shinyValue < 8
end

--[[
    Gender Calculation
--]]

-- Determine gender based on species gender ratio and personality
-- genderRatio: 0 = 100% male, 254 = 100% female, 255 = genderless, others = threshold
function M.getGender(personality, genderRatio)
    if genderRatio == 255 then
        return "genderless"
    elseif genderRatio == 254 then
        return "female"
    elseif genderRatio == 0 then
        return "male"
    else
        local genderValue = personality & 0xFF
        return genderValue < genderRatio and "female" or "male"
    end
end

--[[
    Nature Calculation
--]]

local NATURES = {
    "Hardy", "Lonely", "Brave", "Adamant", "Naughty",
    "Bold", "Docile", "Relaxed", "Impish", "Lax",
    "Timid", "Hasty", "Serious", "Jolly", "Naive",
    "Modest", "Mild", "Quiet", "Bashful", "Rash",
    "Calm", "Gentle", "Sassy", "Careful", "Quirky"
}

function M.getNature(personality)
    local natureIndex = (personality % 25) + 1
    return NATURES[natureIndex]
end

return M
