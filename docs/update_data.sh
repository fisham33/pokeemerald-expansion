#!/bin/bash
# Update pokemon_data.json in the web directory

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_FILE="$SCRIPT_DIR/../pokemon_data.json"
DEST_FILE="$SCRIPT_DIR/pokemon_data.json"

if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file not found at $SOURCE_FILE"
    echo "Please run 'python3 extract_pokemon_data.py' first"
    exit 1
fi

cp "$SOURCE_FILE" "$DEST_FILE"
echo "✓ Updated pokemon_data.json in web directory"
echo "  Source: $SOURCE_FILE"
echo "  Destination: $DEST_FILE"
echo ""
echo "You can now commit and push to update GitHub Pages"
