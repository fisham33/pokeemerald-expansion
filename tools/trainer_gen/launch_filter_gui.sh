#!/bin/bash
# Launch the Pokemon Filter GUI

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Run the GUI
cd "$SCRIPT_DIR"
python3 gui_filter.py
