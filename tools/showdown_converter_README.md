# Pokemon Showdown Team Converter

A tool to convert Pokemon parties from the `trainers.party` file format used in pokeemerald-expansion to Pokemon Showdown's importable format.

## Features

- Converts trainer parties to Pokemon Showdown format
- Removes trainer-specific metadata (Name, Class, Pic, Gender, Music, AI, etc.)
- Removes pokeemerald-expansion specific fields (Tags, Party Size, Pool Rules, etc.)
- Preserves Pokemon Showdown compatible fields:
  - Species (with nicknames and gender)
  - Held items
  - Ability
  - Level
  - Moves
  - IVs
  - EVs (if specified)
  - Nature (if specified)
  - Ball (if specified)
  - Happiness (if specified)
  - Shiny status (if specified)
- Both command-line and GUI interfaces

## Usage

### Command Line

Run from the pokeemerald-expansion root directory:

```bash
# Convert a specific trainer
python3 tools/showdown_converter.py TRAINER_ROXANNE_1

# Search for trainers
python3 tools/showdown_converter.py --search ROXANNE

# List all trainers
python3 tools/showdown_converter.py --list

# Use a different trainers.party file
python3 tools/showdown_converter.py --file path/to/trainers.party TRAINER_ID

# Show help
python3 tools/showdown_converter.py --help
```

### GUI Mode

Launch the graphical interface (requires tkinter):

```bash
python3 tools/showdown_converter.py --gui
```

Or simply:

```bash
python3 tools/showdown_converter.py
```

The GUI provides:
- Searchable list of all trainers
- Live preview of converted teams
- Copy to clipboard functionality

## Example

Input (from trainers.party):
```
=== TRAINER_ROXANNE_1 ===
Name: ROXANNE
Class: Leader
Pic: Leader Roxanne
Gender: Female
Music: Female
AI: Check Bad Move / Try To Faint / Check Viability

Rolycoly @ Oran Berry
Ability: Steam Engine
Level: 15
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Stealth Rock
- Rock Tomb
```

Output (Pokemon Showdown format):
```
=== ROXANNE (TRAINER_ROXANNE_1) ===

Rolycoly @ Oran Berry
Ability: Steam Engine
Level: 15
IVs: 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- Stealth Rock
- Rock Tomb
```

You can copy this output directly into Pokemon Showdown's team builder!

## Requirements

- Python 3.6+
- tkinter (optional, for GUI mode)

## How It Works

The converter:
1. Parses the `trainers.party` file
2. Identifies trainer blocks using the `=== TRAINER_XXX ===` markers
3. Extracts Pokemon data while filtering out:
   - Trainer metadata fields
   - pokeemerald-expansion specific fields
4. Outputs clean Pokemon Showdown format

The output can be directly imported into Pokemon Showdown's team builder without modification.
