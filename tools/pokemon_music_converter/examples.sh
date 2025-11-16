#!/bin/bash
# Pokemon Music Converter - Example Workflows
# This file contains example commands you can copy and modify

CONVERTER="python3 pokemon_music_converter.py"

echo "=== Pokemon Music Converter - Example Commands ==="
echo ""
echo "Copy and paste these commands to get started!"
echo ""

# Example 1: Analyze existing ROM music
echo "# Example 1: Analyze an existing song in the ROM"
echo "$CONVERTER analyze ../../sound/songs/midi/mus_route101.mid"
echo ""

# Example 2: Integrate a single MIDI
echo "# Example 2: Integrate a single MIDI file"
echo "$CONVERTER integrate my_song.mid --voicegroup 128"
echo ""

# Example 3: Convert audio to MIDI
echo "# Example 3: Convert audio (MP3/WAV) to MIDI"
echo "$CONVERTER convert my_song.mp3"
echo ""

# Example 4: Full workflow - convert and integrate
echo "# Example 4: Full workflow - convert audio and integrate automatically"
echo "$CONVERTER convert my_song.mp3 --integrate --voicegroup 128"
echo ""

# Example 5: Batch integrate multiple MIDIs
echo "# Example 5: Integrate multiple MIDI files at once"
echo "$CONVERTER batch-integrate song1.mid song2.mid song3.mid --voicegroup 128"
echo ""

# Example 6: Integrate all MIDIs in a directory
echo "# Example 6: Integrate all .mid files in current directory"
echo "$CONVERTER batch-integrate *.mid --voicegroup 128"
echo ""

# Example 7: Optimize a MIDI that has issues
echo "# Example 7: Optimize a MIDI file for GBA compatibility"
echo "$CONVERTER optimize problematic_song.mid"
echo ""

# Example 8: Custom polyphony optimization
echo "# Example 8: Optimize with custom polyphony limit"
echo "$CONVERTER optimize complex_song.mid --max-polyphony 4 -o simple_song.mid"
echo ""

# Example 9: Convert, analyze, and optimize manually
echo "# Example 9: Manual workflow with full control"
echo "$CONVERTER convert original.mp3"
echo "$CONVERTER analyze mus_original.mid"
echo "$CONVERTER optimize mus_original.mid"
echo "$CONVERTER integrate mus_original_optimized.mid --voicegroup 128"
echo ""

# Example 10: Custom song name
echo "# Example 10: Use a custom name for your song"
echo "$CONVERTER integrate mysong.mid --name mus_custom_battle_theme --voicegroup 128"
echo ""

# Example 11: Download and integrate GBA Music Pack
echo "# Example 11: Integrate GBA Music Pack files"
echo "# First, download from: https://www.pokecommunity.com/threads/527582/"
echo "# Then navigate to the extracted folder and run:"
echo "cd ~/Downloads/GBA_Music_Pack"
echo "$CONVERTER batch-integrate *.mid --voicegroup 128"
echo ""

# Example 12: Test project location
echo "# Example 12: Use with a different project location"
echo "$CONVERTER --project-root /path/to/my/romhack integrate song.mid --voicegroup 128"
echo ""

echo "=== Ready to start! ==="
echo "Pick an example above and modify it for your needs."
echo ""
echo "For more help, run: $CONVERTER --help"
