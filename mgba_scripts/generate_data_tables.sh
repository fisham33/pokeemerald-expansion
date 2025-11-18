#!/bin/bash
# Generate Lua data tables from pokeemerald-expansion header files

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INCLUDE_DIR="$SCRIPT_DIR/../include/constants"

echo "Generating species_data.lua..."
cat > "$SCRIPT_DIR/modules/species_data.lua" << 'EOF'
--[[
    Pokemon Species Data
    Auto-generated from include/constants/species.h
--]]

local M = {}

-- Species ID to name mapping
local SPECIES_NAMES = {
EOF

# Extract species names and IDs
grep "^#define SPECIES_" "$INCLUDE_DIR/species.h" | \
    grep -v "SPECIES_TABLES_TERMIN" | \
    while read -r line; do
        # Parse: #define SPECIES_NAME ID
        name=$(echo "$line" | awk '{print $2}' | sed 's/SPECIES_//')
        id=$(echo "$line" | awk '{print $3}')

        # Skip if ID is not a number (aliases)
        if [[ "$id" =~ ^[0-9]+$ ]]; then
            # Convert UPPERCASE_NAME to Proper Case
            proper_name=$(echo "$name" | tr '_' ' ' | awk '{for(i=1;i<=NF;i++)sub(/./,toupper(substr($i,1,1)),$i)}1' | tr ' ' '-')
            # Handle special cases
            proper_name=$(echo "$proper_name" | sed 's/-F$/♀/' | sed 's/-M$/♂/')
            echo "    [$id] = \"$proper_name\","
        fi
    done >> "$SCRIPT_DIR/modules/species_data.lua"

cat >> "$SCRIPT_DIR/modules/species_data.lua" << 'EOF'
}

-- Get species name by ID
function M.getName(speciesId)
    return SPECIES_NAMES[speciesId] or ("Unknown #" .. speciesId)
end

-- Get all species (for debugging)
function M.getAll()
    return SPECIES_NAMES
end

return M
EOF

echo "Generating move_data.lua..."
cat > "$SCRIPT_DIR/modules/move_data.lua" << 'EOF'
--[[
    Pokemon Move Data
    Auto-generated from include/constants/moves.h
--]]

local M = {}

-- Move ID to name mapping
local MOVE_NAMES = {
EOF

# Extract move names and IDs (skip aliases)
grep "^#define MOVE_[A-Z_]* [0-9]" "$INCLUDE_DIR/moves.h" | \
    while read -r line; do
        # Parse: #define MOVE_NAME ID
        name=$(echo "$line" | awk '{print $2}' | sed 's/MOVE_//')
        id=$(echo "$line" | awk '{print $3}')

        if [[ "$id" =~ ^[0-9]+$ ]]; then
            # Convert UPPERCASE_NAME to Proper Case
            proper_name=$(echo "$name" | tr '_' ' ' | awk '{for(i=1;i<=NF;i++)sub(/./,toupper(substr($i,1,1)),$i)}1')
            # Remove extra spaces
            proper_name=$(echo "$proper_name" | sed 's/  */ /g')
            echo "    [$id] = \"$proper_name\","
        fi
    done >> "$SCRIPT_DIR/modules/move_data.lua"

cat >> "$SCRIPT_DIR/modules/move_data.lua" << 'EOF'
}

-- Get move name by ID
function M.getName(moveId)
    if moveId == 0 then
        return "-"
    end
    return MOVE_NAMES[moveId] or ("Unknown #" .. moveId)
end

-- Get all moves (for debugging)
function M.getAll()
    return MOVE_NAMES
end

return M
EOF

echo "Generation complete!"
echo "Created:"
echo "  - $SCRIPT_DIR/modules/species_data.lua"
echo "  - $SCRIPT_DIR/modules/move_data.lua"
