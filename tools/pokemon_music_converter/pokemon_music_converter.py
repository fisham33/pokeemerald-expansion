#!/usr/bin/env python3
"""
Pokemon Emerald Music Converter Tool
Converts audio files to MIDI and integrates them into Pokemon Emerald Expansion
"""

import os
import sys
import re
import argparse
import shutil
from pathlib import Path
from typing import List, Dict, Tuple, Optional
import subprocess

try:
    import mido
    from mido import MidiFile, MidiTrack, Message
except ImportError:
    print("ERROR: mido library not found. Please install: pip install mido")
    sys.exit(1)


class MusicConverter:
    """Main converter class for Pokemon Emerald music"""

    # GBA/MIDI instrument mapping (General MIDI to commonly used GBA instruments)
    GBA_INSTRUMENT_MAP = {
        # Pianos
        0: 0,   # Acoustic Grand Piano
        1: 0,   # Bright Acoustic Piano
        2: 0,   # Electric Grand Piano
        3: 1,   # Honky-tonk Piano
        4: 1,   # Electric Piano 1
        5: 1,   # Electric Piano 2
        6: 6,   # Harpsichord
        7: 7,   # Clavinet
        # Chromatic Percussion
        8: 8,   # Celesta
        9: 9,   # Glockenspiel
        10: 10, # Music Box
        11: 11, # Vibraphone
        12: 12, # Marimba
        13: 13, # Xylophone
        14: 14, # Tubular Bells
        15: 15, # Dulcimer
        # Organs
        16: 16, # Drawbar Organ
        17: 17, # Percussive Organ
        18: 18, # Rock Organ
        19: 19, # Church Organ
        20: 20, # Reed Organ
        21: 21, # Accordion
        22: 22, # Harmonica
        23: 23, # Tango Accordion
        # Guitars
        24: 24, # Acoustic Guitar (nylon)
        25: 25, # Acoustic Guitar (steel)
        26: 26, # Electric Guitar (jazz)
        27: 27, # Electric Guitar (clean)
        28: 28, # Electric Guitar (muted)
        29: 29, # Overdriven Guitar
        30: 30, # Distortion Guitar
        31: 31, # Guitar harmonics
        # Bass
        32: 32, # Acoustic Bass
        33: 33, # Electric Bass (finger)
        34: 34, # Electric Bass (pick)
        35: 35, # Fretless Bass
        36: 36, # Slap Bass 1
        37: 37, # Slap Bass 2
        38: 38, # Synth Bass 1
        39: 39, # Synth Bass 2
        # Strings
        40: 40, # Violin
        41: 41, # Viola
        42: 42, # Cello
        43: 43, # Contrabass
        44: 44, # Tremolo Strings
        45: 45, # Pizzicato Strings
        46: 46, # Orchestral Harp
        47: 47, # Timpani
        # Ensemble
        48: 48, # String Ensemble 1
        49: 49, # String Ensemble 2
        50: 50, # Synth Strings 1
        51: 51, # Synth Strings 2
        52: 52, # Choir Aahs
        53: 53, # Voice Oohs
        54: 54, # Synth Voice
        55: 55, # Orchestra Hit
        # Brass
        56: 56, # Trumpet
        57: 57, # Trombone
        58: 58, # Tuba
        59: 59, # Muted Trumpet
        60: 60, # French Horn
        61: 61, # Brass Section
        62: 62, # Synth Brass 1
        63: 63, # Synth Brass 2
        # Reed
        64: 64, # Soprano Sax
        65: 65, # Alto Sax
        66: 66, # Tenor Sax
        67: 67, # Baritone Sax
        68: 68, # Oboe
        69: 69, # English Horn
        70: 70, # Bassoon
        71: 71, # Clarinet
        # Pipe
        72: 72, # Piccolo
        73: 73, # Flute
        74: 74, # Recorder
        75: 75, # Pan Flute
        76: 76, # Blown Bottle
        77: 77, # Shakuhachi
        78: 78, # Whistle
        79: 79, # Ocarina
        # Synth Lead
        80: 80, # Lead 1 (square)
        81: 81, # Lead 2 (sawtooth)
        82: 82, # Lead 3 (calliope)
        83: 83, # Lead 4 (chiff)
        84: 84, # Lead 5 (charang)
        85: 85, # Lead 6 (voice)
        86: 86, # Lead 7 (fifths)
        87: 87, # Lead 8 (bass + lead)
        # Synth Pad
        88: 88, # Pad 1 (new age)
        89: 89, # Pad 2 (warm)
        90: 90, # Pad 3 (polysynth)
        91: 91, # Pad 4 (choir)
        92: 92, # Pad 5 (bowed)
        93: 93, # Pad 6 (metallic)
        94: 94, # Pad 7 (halo)
        95: 95, # Pad 8 (sweep)
        # Synth Effects
        96: 96, # FX 1 (rain)
        97: 97, # FX 2 (soundtrack)
        98: 98, # FX 3 (crystal)
        99: 99, # FX 4 (atmosphere)
        100: 100, # FX 5 (brightness)
        101: 101, # FX 6 (goblins)
        102: 102, # FX 7 (echoes)
        103: 103, # FX 8 (sci-fi)
        # Ethnic
        104: 104, # Sitar
        105: 105, # Banjo
        106: 106, # Shamisen
        107: 107, # Koto
        108: 108, # Kalimba
        109: 109, # Bag pipe
        110: 110, # Fiddle
        111: 111, # Shanai
        # Percussive
        112: 112, # Tinkle Bell
        113: 113, # Agogo
        114: 114, # Steel Drums
        115: 115, # Woodblock
        116: 116, # Taiko Drum
        117: 117, # Melodic Tom
        118: 118, # Synth Drum
        119: 119, # Reverse Cymbal
        # Sound effects
        120: 120, # Guitar Fret Noise
        121: 121, # Breath Noise
        122: 122, # Seashore
        123: 123, # Bird Tweet
        124: 124, # Telephone Ring
        125: 125, # Helicopter
        126: 126, # Applause
        127: 127, # Gunshot
    }

    def __init__(self, project_root: Path):
        """Initialize converter with project root directory"""
        self.project_root = Path(project_root)
        self.sound_dir = self.project_root / "sound"
        self.midi_dir = self.sound_dir / "songs" / "midi"
        self.songs_h = self.project_root / "include" / "constants" / "songs.h"
        self.song_table_inc = self.sound_dir / "song_table.inc"
        self.midi_cfg = self.midi_dir / "midi.cfg"

        # Verify paths exist
        if not self.sound_dir.exists():
            raise FileNotFoundError(f"Sound directory not found: {self.sound_dir}")
        if not self.midi_dir.exists():
            self.midi_dir.mkdir(parents=True, exist_ok=True)

    def sanitize_filename(self, filename: str) -> str:
        """Convert filename to Pokemon Emerald naming convention"""
        # Remove extension
        name = Path(filename).stem
        # Convert to lowercase
        name = name.lower()
        # Replace spaces and special chars with underscores
        name = re.sub(r'[^a-z0-9_]', '_', name)
        # Remove multiple consecutive underscores
        name = re.sub(r'_+', '_', name)
        # Remove leading/trailing underscores
        name = name.strip('_')
        # Ensure it starts with mus_ if it doesn't
        if not name.startswith('mus_') and not name.startswith('se_'):
            name = f'mus_{name}'
        return name

    def audio_to_midi(self, audio_file: Path, output_midi: Path) -> bool:
        """
        Convert audio file to MIDI using basic-pitch
        Returns True if successful, False otherwise
        """
        try:
            # Check if basic-pitch is available
            result = subprocess.run(
                ['basic-pitch', '--version'],
                capture_output=True,
                text=True
            )
            if result.returncode != 0:
                print("WARNING: basic-pitch not found. Please install it:")
                print("  pip install basic-pitch")
                return False
        except FileNotFoundError:
            print("WARNING: basic-pitch not found. Please install it:")
            print("  pip install basic-pitch")
            return False

        print(f"Converting {audio_file.name} to MIDI...")
        try:
            # Run basic-pitch
            result = subprocess.run(
                [
                    'basic-pitch',
                    str(output_midi.parent),
                    str(audio_file),
                    '--save-midi',
                    '--no-onset',
                    '--no-note'
                ],
                capture_output=True,
                text=True,
                timeout=300  # 5 minute timeout
            )

            if result.returncode != 0:
                print(f"ERROR converting {audio_file.name}: {result.stderr}")
                return False

            # basic-pitch creates a file with _basic_pitch suffix
            generated_midi = output_midi.parent / f"{output_midi.stem}_basic_pitch.mid"
            if generated_midi.exists():
                # Rename to expected output
                shutil.move(str(generated_midi), str(output_midi))
                print(f"  ✓ Converted to {output_midi.name}")
                return True
            else:
                print(f"ERROR: Expected output file not found: {generated_midi}")
                return False

        except subprocess.TimeoutExpired:
            print(f"ERROR: Conversion timed out for {audio_file.name}")
            return False
        except Exception as e:
            print(f"ERROR converting {audio_file.name}: {e}")
            return False

    def analyze_midi(self, midi_file: Path) -> Dict:
        """
        Analyze MIDI file and return statistics
        """
        try:
            mid = MidiFile(midi_file)
        except Exception as e:
            return {"error": str(e)}

        stats = {
            "tracks": len(mid.tracks),
            "length": mid.length,
            "ticks_per_beat": mid.ticks_per_beat,
            "tempo_changes": 0,
            "instruments": set(),
            "note_count": 0,
            "polyphony": 0,
            "min_note": 127,
            "max_note": 0,
            "warnings": []
        }

        # Analyze each track
        max_simultaneous = 0
        for i, track in enumerate(mid.tracks):
            active_notes = set()
            current_instrument = 0

            for msg in track:
                if msg.type == 'program_change':
                    current_instrument = msg.program
                    stats["instruments"].add(current_instrument)
                elif msg.type == 'set_tempo':
                    stats["tempo_changes"] += 1
                elif msg.type == 'note_on' and msg.velocity > 0:
                    stats["note_count"] += 1
                    active_notes.add(msg.note)
                    stats["min_note"] = min(stats["min_note"], msg.note)
                    stats["max_note"] = max(stats["max_note"], msg.note)
                    max_simultaneous = max(max_simultaneous, len(active_notes))
                elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
                    active_notes.discard(msg.note)

        stats["polyphony"] = max_simultaneous
        stats["instruments"] = sorted(list(stats["instruments"]))

        # Generate warnings
        if stats["tracks"] > 16:
            stats["warnings"].append(f"High track count ({stats['tracks']}). GBA supports max 16 tracks.")
        if stats["polyphony"] > 8:
            stats["warnings"].append(f"High polyphony ({stats['polyphony']}). May cause audio issues on GBA.")
        if stats["note_count"] > 10000:
            stats["warnings"].append(f"High note count ({stats['note_count']}). File may be too large.")
        if stats["min_note"] < 21 or stats["max_note"] > 108:
            stats["warnings"].append(f"Note range {stats['min_note']}-{stats['max_note']} may be outside GBA range (21-108).")

        return stats

    def optimize_midi(self, midi_file: Path, output_file: Path, max_polyphony: int = 8) -> bool:
        """
        Optimize MIDI file for GBA playback
        - Reduce polyphony
        - Map instruments to GBA-compatible ones
        - Remove empty tracks
        """
        try:
            mid = MidiFile(midi_file)
        except Exception as e:
            print(f"ERROR reading MIDI: {e}")
            return False

        new_mid = MidiFile(ticks_per_beat=mid.ticks_per_beat)

        for track_idx, track in enumerate(mid.tracks):
            new_track = MidiTrack()
            active_notes = {}  # note -> (time, velocity)
            current_time = 0

            for msg in track:
                current_time += msg.time
                new_msg = msg.copy()

                # Map instruments to GBA equivalents
                if msg.type == 'program_change':
                    if msg.program in self.GBA_INSTRUMENT_MAP:
                        new_msg.program = self.GBA_INSTRUMENT_MAP[msg.program]

                # Polyphony limiting
                elif msg.type == 'note_on' and msg.velocity > 0:
                    # If we're at max polyphony, remove oldest note
                    if len(active_notes) >= max_polyphony:
                        # Find oldest note
                        oldest_note = min(active_notes.items(), key=lambda x: x[1][0])[0]
                        # Add note_off for oldest note
                        note_off = Message('note_off', note=oldest_note, velocity=0, time=0)
                        new_track.append(note_off)
                        del active_notes[oldest_note]

                    active_notes[msg.note] = (current_time, msg.velocity)

                elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
                    if msg.note in active_notes:
                        del active_notes[msg.note]

                new_track.append(new_msg)

            # Only add track if it has content
            if len(new_track) > 0:
                new_mid.tracks.append(new_track)

        try:
            new_mid.save(output_file)
            print(f"  ✓ Optimized MIDI saved to {output_file.name}")
            return True
        except Exception as e:
            print(f"ERROR saving optimized MIDI: {e}")
            return False

    def get_next_song_id(self) -> Tuple[int, str]:
        """
        Parse songs.h to find the next available song ID
        Returns (id, constant_name)
        """
        if not self.songs_h.exists():
            raise FileNotFoundError(f"songs.h not found: {self.songs_h}")

        with open(self.songs_h, 'r') as f:
            content = f.read()

        # Find END_MUS
        match = re.search(r'#define\s+END_MUS\s+MUS_(\w+)', content)
        if not match:
            raise ValueError("Could not find END_MUS in songs.h")

        last_song_name = match.group(1)

        # Find the ID of the last song
        pattern = rf'#define\s+MUS_{re.escape(last_song_name)}\s+(\d+)'
        match = re.search(pattern, content)
        if not match:
            raise ValueError(f"Could not find ID for MUS_{last_song_name}")

        last_id = int(match.group(1))
        next_id = last_id + 1

        return next_id, last_song_name

    def generate_constant_name(self, song_name: str) -> str:
        """Generate MUS_ constant name from song filename"""
        # Remove mus_ prefix if present
        name = song_name
        if name.startswith('mus_'):
            name = name[4:]
        # Convert to uppercase
        return f"MUS_{name.upper()}"

    def add_to_songs_h(self, song_name: str, song_id: int) -> bool:
        """Add song constant definition to songs.h"""
        if not self.songs_h.exists():
            print(f"ERROR: songs.h not found: {self.songs_h}")
            return False

        try:
            with open(self.songs_h, 'r') as f:
                lines = f.readlines()

            # Find END_MUS line
            end_mus_idx = None
            for i, line in enumerate(lines):
                if re.search(r'#define\s+END_MUS\s+MUS_', line):
                    end_mus_idx = i
                    break

            if end_mus_idx is None:
                print("ERROR: Could not find END_MUS in songs.h")
                return False

            # Generate new constant
            const_name = self.generate_constant_name(song_name)
            new_line = f"#define {const_name:<30} {song_id} // Custom song\n"

            # Insert before END_MUS
            lines.insert(end_mus_idx, new_line)

            # Update END_MUS to point to new song
            lines[end_mus_idx + 1] = re.sub(
                r'(#define\s+END_MUS\s+)MUS_\w+',
                r'\1' + const_name,
                lines[end_mus_idx + 1]
            )

            # Write back
            with open(self.songs_h, 'w') as f:
                f.writelines(lines)

            print(f"  ✓ Added {const_name} to songs.h")
            return True

        except Exception as e:
            print(f"ERROR updating songs.h: {e}")
            return False

    def add_to_song_table(self, song_name: str) -> bool:
        """Add song entry to song_table.inc"""
        if not self.song_table_inc.exists():
            print(f"ERROR: song_table.inc not found: {self.song_table_inc}")
            return False

        try:
            with open(self.song_table_inc, 'r') as f:
                content = f.read()

            # Add entry at the end (before any closing markers if present)
            const_name = self.generate_constant_name(song_name)
            # Use lowercase for the actual song name in the table
            entry = f"\tsong {song_name}, 2, 2\n"

            # Append to end of file
            content += entry

            with open(self.song_table_inc, 'w') as f:
                f.write(content)

            print(f"  ✓ Added {song_name} to song_table.inc")
            return True

        except Exception as e:
            print(f"ERROR updating song_table.inc: {e}")
            return False

    def add_to_midi_cfg(self, song_name: str, voicegroup: str = "128",
                       reverb: str = "50", volume: str = "080", priority: str = "5") -> bool:
        """Add MIDI configuration entry"""
        if not self.midi_cfg.exists():
            print(f"ERROR: midi.cfg not found: {self.midi_cfg}")
            return False

        try:
            with open(self.midi_cfg, 'r') as f:
                lines = f.readlines()

            # Generate config entry
            midi_filename = f"{song_name}.mid"
            entry = f"{midi_filename:<30} -E -R{reverb} -G{voicegroup} -V{volume} -P{priority}\n"

            # Append to end
            lines.append(entry)

            with open(self.midi_cfg, 'w') as f:
                f.writelines(lines)

            print(f"  ✓ Added {song_name} to midi.cfg (voicegroup: {voicegroup})")
            return True

        except Exception as e:
            print(f"ERROR updating midi.cfg: {e}")
            return False

    def integrate_song(self, midi_file: Path, song_name: str, voicegroup: str = "128") -> bool:
        """
        Fully integrate a song into the project
        - Copy MIDI to sound/songs/midi/
        - Update songs.h
        - Update song_table.inc
        - Update midi.cfg
        """
        print(f"\nIntegrating {song_name}...")

        # Copy MIDI file
        dest_midi = self.midi_dir / f"{song_name}.mid"
        try:
            shutil.copy(str(midi_file), str(dest_midi))
            print(f"  ✓ Copied MIDI to {dest_midi}")
        except Exception as e:
            print(f"ERROR copying MIDI: {e}")
            return False

        # Get next song ID
        try:
            song_id, _ = self.get_next_song_id()
        except Exception as e:
            print(f"ERROR getting next song ID: {e}")
            return False

        # Update all files
        success = True
        success &= self.add_to_songs_h(song_name, song_id)
        success &= self.add_to_song_table(song_name)
        success &= self.add_to_midi_cfg(song_name, voicegroup)

        if success:
            print(f"\n✓ Successfully integrated {song_name}!")
            print(f"  Song ID: {song_id}")
            print(f"  Constant: {self.generate_constant_name(song_name)}")
            print(f"  MIDI file: {dest_midi}")
        else:
            print(f"\n✗ Failed to fully integrate {song_name}")

        return success

    def print_analysis(self, stats: Dict, midi_file: Path):
        """Pretty print MIDI analysis"""
        print(f"\n{'='*60}")
        print(f"MIDI Analysis: {midi_file.name}")
        print(f"{'='*60}")

        if "error" in stats:
            print(f"ERROR: {stats['error']}")
            return

        print(f"Tracks:           {stats['tracks']}")
        print(f"Length:           {stats['length']:.2f} seconds")
        print(f"Ticks per beat:   {stats['ticks_per_beat']}")
        print(f"Tempo changes:    {stats['tempo_changes']}")
        print(f"Total notes:      {stats['note_count']}")
        print(f"Max polyphony:    {stats['polyphony']}")
        print(f"Note range:       {stats['min_note']}-{stats['max_note']}")
        print(f"Instruments:      {len(stats['instruments'])}")
        if stats['instruments']:
            print(f"  {', '.join(str(i) for i in stats['instruments'])}")

        if stats['warnings']:
            print(f"\n⚠ WARNINGS:")
            for warning in stats['warnings']:
                print(f"  - {warning}")
        else:
            print(f"\n✓ No issues detected")

        print(f"{'='*60}\n")


def main():
    parser = argparse.ArgumentParser(
        description='Pokemon Emerald Music Converter - Convert audio to MIDI and integrate into ROM',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Convert audio to MIDI and analyze
  %(prog)s convert my_song.mp3

  # Analyze existing MIDI
  %(prog)s analyze my_song.mid

  # Optimize MIDI for GBA
  %(prog)s optimize my_song.mid -o optimized.mid

  # Integrate MIDI into project (full integration)
  %(prog)s integrate my_song.mid --voicegroup 128

  # Full workflow: convert, optimize, and integrate
  %(prog)s convert my_song.mp3 --integrate --voicegroup 128

  # Batch process multiple files
  %(prog)s batch-integrate *.mid --voicegroup 128
        """
    )

    parser.add_argument(
        '--project-root',
        type=Path,
        default=Path.cwd(),
        help='Path to pokeemerald-expansion root (default: current directory)'
    )

    subparsers = parser.add_subparsers(dest='command', help='Command to run')

    # Convert command
    convert_parser = subparsers.add_parser('convert', help='Convert audio file to MIDI')
    convert_parser.add_argument('input', type=Path, help='Input audio file')
    convert_parser.add_argument('-o', '--output', type=Path, help='Output MIDI file (optional)')
    convert_parser.add_argument('--analyze', action='store_true', help='Analyze after conversion')
    convert_parser.add_argument('--optimize', action='store_true', help='Optimize after conversion')
    convert_parser.add_argument('--integrate', action='store_true', help='Integrate into project after conversion')
    convert_parser.add_argument('--voicegroup', default='128', help='Voicegroup number for integration (default: 128)')
    convert_parser.add_argument('--name', help='Custom song name (default: derived from filename)')

    # Analyze command
    analyze_parser = subparsers.add_parser('analyze', help='Analyze MIDI file')
    analyze_parser.add_argument('input', type=Path, help='Input MIDI file')

    # Optimize command
    optimize_parser = subparsers.add_parser('optimize', help='Optimize MIDI for GBA')
    optimize_parser.add_argument('input', type=Path, help='Input MIDI file')
    optimize_parser.add_argument('-o', '--output', type=Path, help='Output MIDI file (default: input_optimized.mid)')
    optimize_parser.add_argument('--max-polyphony', type=int, default=8, help='Maximum polyphony (default: 8)')

    # Integrate command
    integrate_parser = subparsers.add_parser('integrate', help='Integrate MIDI into project')
    integrate_parser.add_argument('input', type=Path, help='Input MIDI file')
    integrate_parser.add_argument('--voicegroup', default='128', help='Voicegroup number (default: 128)')
    integrate_parser.add_argument('--name', help='Custom song name (default: derived from filename)')
    integrate_parser.add_argument('--optimize', action='store_true', help='Optimize before integration')

    # Batch integrate command
    batch_parser = subparsers.add_parser('batch-integrate', help='Integrate multiple MIDI files')
    batch_parser.add_argument('inputs', nargs='+', type=Path, help='Input MIDI files')
    batch_parser.add_argument('--voicegroup', default='128', help='Voicegroup number (default: 128)')
    batch_parser.add_argument('--optimize', action='store_true', help='Optimize before integration')

    args = parser.parse_args()

    if not args.command:
        parser.print_help()
        return 1

    # Initialize converter
    try:
        converter = MusicConverter(args.project_root)
    except Exception as e:
        print(f"ERROR: {e}")
        return 1

    # Execute command
    if args.command == 'convert':
        if not args.input.exists():
            print(f"ERROR: Input file not found: {args.input}")
            return 1

        # Determine output filename
        if args.output:
            output_midi = args.output
        else:
            song_name = converter.sanitize_filename(args.input.name)
            output_midi = args.input.parent / f"{song_name}.mid"

        # Convert
        success = converter.audio_to_midi(args.input, output_midi)
        if not success:
            return 1

        # Analyze
        if args.analyze or args.integrate:
            stats = converter.analyze_midi(output_midi)
            converter.print_analysis(stats, output_midi)

        # Optimize
        if args.optimize or args.integrate:
            optimized_path = output_midi.parent / f"{output_midi.stem}_optimized.mid"
            success = converter.optimize_midi(output_midi, optimized_path)
            if success:
                output_midi = optimized_path

        # Integrate
        if args.integrate:
            song_name = args.name or converter.sanitize_filename(args.input.name)
            success = converter.integrate_song(output_midi, song_name, args.voicegroup)
            return 0 if success else 1

    elif args.command == 'analyze':
        if not args.input.exists():
            print(f"ERROR: Input file not found: {args.input}")
            return 1

        stats = converter.analyze_midi(args.input)
        converter.print_analysis(stats, args.input)

    elif args.command == 'optimize':
        if not args.input.exists():
            print(f"ERROR: Input file not found: {args.input}")
            return 1

        output = args.output or args.input.parent / f"{args.input.stem}_optimized.mid"
        success = converter.optimize_midi(args.input, output, args.max_polyphony)
        return 0 if success else 1

    elif args.command == 'integrate':
        if not args.input.exists():
            print(f"ERROR: Input file not found: {args.input}")
            return 1

        midi_file = args.input

        # Optimize if requested
        if args.optimize:
            optimized_path = args.input.parent / f"{args.input.stem}_optimized.mid"
            success = converter.optimize_midi(args.input, optimized_path)
            if success:
                midi_file = optimized_path
            else:
                return 1

        song_name = args.name or converter.sanitize_filename(args.input.name)
        success = converter.integrate_song(midi_file, song_name, args.voicegroup)
        return 0 if success else 1

    elif args.command == 'batch-integrate':
        total = len(args.inputs)
        successful = 0

        for midi_file in args.inputs:
            if not midi_file.exists():
                print(f"WARNING: File not found, skipping: {midi_file}")
                continue

            # Optionally optimize
            if args.optimize:
                optimized_path = midi_file.parent / f"{midi_file.stem}_optimized.mid"
                if converter.optimize_midi(midi_file, optimized_path):
                    midi_file = optimized_path

            song_name = converter.sanitize_filename(midi_file.name)
            if converter.integrate_song(midi_file, song_name, args.voicegroup):
                successful += 1

        print(f"\n{'='*60}")
        print(f"Batch integration complete: {successful}/{total} successful")
        print(f"{'='*60}")

        return 0 if successful == total else 1

    return 0


if __name__ == '__main__':
    sys.exit(main())
