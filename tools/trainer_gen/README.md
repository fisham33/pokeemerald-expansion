# Random Doubles Battle to trainers.party Converter

Convert Pokemon Showdown's Random Doubles Battle data into `trainers.party` format with full Trainer Party Pool (TPP) support!

## Features

✅ **Graphical User Interface (GUI)** - easy-to-use GUI for all conversion options (NEW!)
✅ **Convert 1000+ Pokemon movesets** from Showdown's Random Battle formats
✅ **Multi-File Support** - processes Doubles, Singles, and Baby Random Battles
✅ **Archetype Filtering** - filter by Pokemon type or trainer class
✅ **Pokemon Database** - integrated Pokemon data with types and base stats
✅ **Set Variants** - generates 2 variants when Pokemon have multiple abilities/items/5+ moves
✅ **Automatic Tag Assignment** based on roles and abilities
✅ **Trainer Party Pool Support** with configurable pool sizes
✅ **Weather/Terrain Detection** automatically tags weather setters and abusers
✅ **Multiple Output Modes** for different use cases
✅ **Smart Role Mapping** converts Showdown roles to TPP tags
✅ **No Level Required** - levels are optional in trainers.party format

## Quick Start

### Using the GUI (Recommended)

The easiest way to use the converter is through the graphical user interface:

**Linux/Mac:**
```bash
cd tools/trainer_gen
./launch_gui.sh
```

**Windows:**
```bash
cd tools/trainer_gen
launch_gui.bat
```

**Or directly:**
```bash
cd tools/trainer_gen
python3 gui_converter.py
```

The GUI provides:
- Easy file selection for input JSON files
- Visual mode selection with descriptions
- Archetype filtering with dropdown for trainer classes
- Pool and party size controls
- Output file selection
- Real-time progress display
- Error handling with clear messages

### Using the Command Line

### 1. Get the JSON Data

Download one or more Random Battle data files:

```bash
cd tools/trainer_gen

# Random Doubles Battle (recommended for doubles)
curl -o gen9randomdoublesbattle.json https://pkmn.github.io/randbats/data/gen9randomdoublesbattle.json

# Random Singles Battle (for singles battles)
curl -o gen9randombattle.json https://pkmn.github.io/randbats/data/gen9randombattle.json

# Baby Random Battle (LC/lower level Pokemon)
curl -o gen9babyrandombattle.json https://pkmn.github.io/randbats/data/gen9babyrandombattle.json
```

Or save the files manually from your browser to `tools/trainer_gen/`

**Note:** The script will automatically detect and process ALL available JSON files in the directory!

### 2. Run the Converter

```bash
cd tools/trainer_gen
python3 convert_randbats_to_party.py --mode pool
```

The script will merge Pokemon from all available files into one `converted_movesets.txt`!

### 3. Generate Pokemon Database (Required for Archetype Filtering)

To use archetype filtering, first generate the Pokemon database:

```bash
cd tools/trainer_gen
python3 extract_pokemon_data.py
```

This creates `pokemon_data.json` with data for 1000+ Pokemon including types, base stats, and dex numbers extracted from your pokeemerald-expansion codebase.

## Archetype Filtering

Filter Pokemon by type or trainer class to create themed trainers!

### Filter by Type(s)

```bash
# Water-type Pokemon only
python3 convert_randbats_to_party.py --mode pool --archetype Water

# Multiple types (Water OR Electric)
python3 convert_randbats_to_party.py --mode pool --archetype Water,Electric

# Fire OR Ground OR Rock
python3 convert_randbats_to_party.py --mode pool --archetype Fire,Ground,Rock
```

### Filter by Trainer Class

The script includes 50+ predefined trainer archetypes:

```bash
# Hiker (Rock/Ground/Fighting types)
python3 convert_randbats_to_party.py --mode pool --archetype Hiker

# Swimmer (Water types)
python3 convert_randbats_to_party.py --mode pool --archetype Swimmer

# Hex Maniac (Ghost/Dark/Poison types)
python3 convert_randbats_to_party.py --mode pool --archetype "Hex Maniac"
```

**Available Trainer Classes:**
- **Type Specialists:** Swimmer (Water), Bird Keeper (Flying), Bug Catcher (Bug), Kindler (Fire), Psychic (Psychic), Dragon Tamer (Dragon), etc.
- **Multi-Type:** Hiker (Rock/Ground/Fighting), Scientist (Poison/Electric/Steel), Ninja (Poison/Dark), Hex Maniac (Ghost/Dark/Poison)
- **Generalists:** Ace Trainer, Cooltrainer, Pokemon Breeder (accepts any type)

See `trainer_archetypes.json` for the full list and their type preferences.

### Select Specific Input Files

Use `-i` to specify which JSON files to process:

```bash
# Only Doubles format
python3 convert_randbats_to_party.py --mode pool -i gen9randomdoublesbattle.json

# Doubles and Singles (comma-separated)
python3 convert_randbats_to_party.py --mode pool -i gen9randomdoublesbattle.json,gen9randombattle.json

# Combine archetype with file selection
python3 convert_randbats_to_party.py --mode pool --archetype Hiker -i gen9randomdoublesbattle.json
```

## Usage Modes

### Mode 1: Single Entry Per Pokemon (Basic)
```bash
python3 convert_randbats_to_party.py --mode single
```
- Generates one moveset per Pokemon
- No tags included
- Perfect for simple trainer teams
- Output: One entry per Pokemon with 4 random moves

### Mode 2: All Roles (Complete Sets)
```bash
python3 convert_randbats_to_party.py --mode all-roles
```
- Generates entries for ALL roles each Pokemon can have
- Includes tags for each role
- Great for understanding all possibilities
- Output: Multiple entries per Pokemon (e.g., Abomasnow gets "Doubles Bulky Attacker" with appropriate tags)

### Mode 3: Pool Format (Recommended)
```bash
python3 convert_randbats_to_party.py --mode pool
```
- Generates Pokemon with **TPP tags** assigned
- Tags based on roles and abilities
- Ready to copy into trainer pools
- Output: One entry per Pokemon with intelligent tags like `Tags: Lead / Weather Setter`

**Example Output:**
```
Ninetales-Alola @ Light Clay
Ability: Snow Warning
Tera Type: Ice
Tags: Weather Setter
- Aurora Veil
- Blizzard
- Moonblast
- Protect

Arctozolt @ Life Orb
Ability: Slush Rush
Tera Type: Ice
Tags: Weather Abuser
- Bolt Beak
- Freeze-Dry
- Icicle Crash
- Protect
```

### Mode 4: Complete Trainer Pool (Auto-Generated)
```bash
python3 convert_randbats_to_party.py --mode trainer-pool --pool-size 12 --party-size 4
```
- Generates a **complete trainer** with pool configuration
- Automatically selects Pokemon from level range
- Includes proper pool rules setup
- Perfect for quick trainer creation

**Example Output:**
```
=== TRAINER_EXAMPLE_DOUBLES ===
Name: Example Doubles
Class: Ace Trainer
Pic: Ace Trainer
Gender: Male
Music: Male
Double Battle: Yes
AI: Check Bad Move / Try To Faint / Check Viability
Party Size: 4
Pool Rules: Weather Doubles

Torkoal @ Sitrus Berry
Ability: Drought
Tags: Weather Setter
- Heat Wave
- Body Press
- Protect
- Will-O-Wisp

Venusaur @ Life Orb
Ability: Chlorophyll
Tags: Weather Abuser
- Giga Drain
- Earth Power
- Sludge Bomb
- Protect

... (8 more Pokemon in pool)
```

## Command-Line Options

```bash
python3 convert_randbats_to_party.py [OPTIONS]
```

### Options:
- `--input`, `-i` - Input JSON files (comma-separated). Leave blank to use all available files
- `--mode {single|all-roles|pool|trainer-pool}` - Conversion mode (default: pool)
- `--archetype` - Filter Pokemon by type or trainer class (e.g., "Water,Electric" or "Hiker")
- `--output`, `-o` - Output file (default: converted_movesets.txt)
- `--pool-size` - Pool size for trainer-pool mode (default: 8)
- `--party-size` - Party size for trainer-pool mode (default: 4)
- `--level-min` - Minimum level for trainer-pool mode (default: auto-detect)
- `--level-max` - Maximum level for trainer-pool mode (default: auto-detect)
- `--split-output` - Split output into separate files by format (singles/doubles/babies)
- `--use-species-enabled` - Filter Pokemon based on species_enabled.h configuration

**Level Range Auto-Detection (trainer-pool mode):**
- Baby Random Battles: levels 5-15
- Doubles/Singles Random Battles: levels 75-85
- Other files: levels 1-100

**Species Filtering (--use-species-enabled):**

This feature respects your `include/config/species_enabled.h` configuration, only including Pokemon from enabled families and generations. This is useful if you've disabled certain Pokemon families or entire generations in your ROM hack.

Requirements:
- Run `python3 extract_pokemon_data.py` first to generate `pokemon_data.json` with family information
- The converter will read your `species_enabled.h` file automatically

Example:
```c
// In species_enabled.h:
#define P_GEN_1_POKEMON                  TRUE
#define P_GEN_2_POKEMON                  FALSE  // Gen 2 disabled
#define P_FAMILY_CHARMANDER              FALSE  // Charmander family disabled
```

Then run:
```bash
python3 convert_randbats_to_party.py --mode pool --use-species-enabled
```

This will exclude all Gen 2 Pokemon and the Charmander family from the output, matching your ROM hack's configuration.

### Examples:
```bash
# Generate pool entries with custom output file
python3 convert_randbats_to_party.py --mode pool -o my_pool.txt

# Generate trainer with larger pool
python3 convert_randbats_to_party.py --mode trainer-pool --pool-size 16 --party-size 6

# Generate trainer pool from baby battles with Rock types (auto-detects levels 5-15)
python3 convert_randbats_to_party.py --mode trainer-pool --archetype Rock -i gen9babyrandombattle.json

# Generate trainer pool with custom level range
python3 convert_randbats_to_party.py --mode trainer-pool --level-min 50 --level-max 60

# Filter by enabled species only (respects species_enabled.h)
python3 convert_randbats_to_party.py --mode pool --use-species-enabled

# Combine species filtering with archetype filtering
python3 convert_randbats_to_party.py --mode pool --use-species-enabled --archetype Water

# Split output into separate files by format
python3 convert_randbats_to_party.py --mode pool --split-output
# Creates: converted_movesets_doubles.txt, converted_movesets_singles.txt, converted_movesets_babies.txt

# Generate all roles with split output
python3 convert_randbats_to_party.py --mode all-roles --split-output
```

## Set Variants

When a Pokemon has **multiple abilities**, **multiple items**, or **5+ moves**, the converter automatically creates **2 variants**:

**Example - Charizard with 2 abilities:**
```
Charizard @ Life Orb
Ability: Blaze
Tera Type: Dragon
- Heat Wave
- Hurricane
- Protect
- Scorching Sands

Charizard @ Life Orb
Ability: Solar Power
Tera Type: Fire
- Heat Wave
- Hurricane
- Will-O-Wisp
- Protect
```

**Example - Gholdengo with multiple items:**
```
Gholdengo @ Choice Scarf
Ability: Good as Gold
Tera Type: Fairy
- Make It Rain
- Shadow Ball
- Focus Blast
- Dazzling Gleam

Gholdengo @ Life Orb
Ability: Good as Gold
Tera Type: Steel
- Make It Rain
- Shadow Ball
- Protect
- Thunderbolt
```

This gives you more variety in your trainer pools!

## Set Comments

The converter automatically adds **helpful comments** above each Pokemon set to identify the role and source format:

**Combined Output (default):**
```
/* Doubles */
/* Doubles Bulky Attacker */
Torkoal @ Sitrus Berry
Ability: Drought
Tera Type: Dragon
Tags: Weather Setter
- Heat Wave
- Body Press
- Protect
- Will-O-Wisp

/* Singles */
/* Setup Sweeper */
Dragonite @ Weakness Policy
Ability: Multiscale
Tera Type: Normal
Tags: Ace
- Dragon Dance
- Extreme Speed
- Earthquake
- Outrage
```

**Split Output (--split-output flag):**
```
/* Doubles Bulky Attacker */
Torkoal @ Sitrus Berry
Ability: Drought
Tera Type: Dragon
Tags: Weather Setter
- Heat Wave
- Body Press
- Protect
- Will-O-Wisp
```

The format identifier comment (`/* Doubles */`, `/* Singles */`, `/* Babies */`) is only added when combining all formats into one file. When using `--split-output`, only the role comment is included since each file contains only one format.

## Tag Assignment

The converter automatically assigns tags based on:

### Role-Based Tags:
- **Lead**: Fast attackers, weather setters
- **Ace**: Setup sweepers, wallbreakers
- **Support**: Support role Pokemon

### Ability-Based Tags:
- **Weather Setter**: Drought, Drizzle, Snow Warning, Sand Stream, terrain setters
- **Weather Abuser**: Chlorophyll, Swift Swim, Sand Rush, Slush Rush, Solar Power, etc.

### Example Tag Mappings:
```
Ninetales-Alola (Snow Warning) → Weather Setter
Arctozolt (Slush Rush) → Weather Abuser
Incineroar (Intimidate) → Support
Urshifu (Unseen Fist) → Ace
```

## Integration with trainers.party

### Using Pool Entries:

1. Run converter in `pool` mode:
```bash
python3 convert_randbats_to_party.py --mode pool
```

2. Open `converted_movesets.txt` and find Pokemon you want

3. Copy into your trainer definition:
```
=== TRAINER_MY_DOUBLES ===
Name: MY DOUBLES
Class: Ace Trainer
Pic: Ace Trainer
Gender: Male
Music: Male
Double Battle: Yes
AI: Check Bad Move / Try To Faint / Check Viability
Party Size: 4
Pool Rules: Weather Doubles

Torkoal @ Sitrus Berry
Ability: Drought
Tags: Weather Setter
- Heat Wave
- Protect
- Body Press
- Will-O-Wisp

... (paste more Pokemon from converted_movesets.txt)
```

4. The game will randomly select 4 Pokemon from your pool following the Weather Doubles rules!

## Pool Rules Available

When creating trainers with pools, you can use these pool rules:

- `Basic` - Basic lead/ace selection for singles
- `Doubles` - Lead/ace selection for doubles (2 leads, 2 aces)
- `Weather Singles` - Weather setter + abuser for singles
- `Weather Doubles` - Weather setter + abuser for doubles
- `Support Doubles` - Includes support Pokemon for doubles

## Tips & Tricks

### Creating Themed Pools:
```bash
# 1. Generate all Pokemon with tags
python3 convert_randbats_to_party.py --mode pool

# 2. Search the output for specific themes:
#    - Search "Weather Setter" for rain/sun/sand/snow setters
#    - Search "Weather Abuser" for sweepers
#    - Search "Support" for utility Pokemon
#    - Search "Ace" for late-game threats

# 3. Mix and match to create your perfect pool!
```

### Varying Move Selection:
The script randomly selects 4 moves from each Pokemon's available moveset. Run it multiple times to get different move combinations!

### Level Filtering:
Edit the `level_range` in trainer-pool mode to target specific level ranges:
```python
level_range=(75, 85)  # Only Pokemon between levels 75-85
```

## Troubleshooting

**Q: "Failed to load data"**
A: Make sure `gen9randomdoublesbattle.json` is in the `tools/trainer_gen/` directory

**Q: "No tags assigned to my Pokemon"**
A: Some Pokemon may not have obvious roles. You can manually add tags in the output file.

**Q: "How do I customize tag assignment?"**
A: Edit the `ROLE_TO_TAGS` dictionary in the script to change which roles get which tags.

## Advanced: Customizing Tag Assignment

Edit `convert_randbats_to_party.py` to customize:

```python
ROLE_TO_TAGS = {
    "Doubles Fast Attacker": ["Lead"],
    "Doubles Setup Sweeper": ["Ace"],
    "Doubles Support": ["Support"],
    # Add your custom mappings here!
}
```

## GUI Guide

### Main Features

The GUI application (`gui_converter.py`) provides a user-friendly interface for all converter features:

#### Input Files
- Select specific JSON files or use all available files in the directory
- File picker dialog for easy selection
- Supports: gen9randomdoublesbattle.json, gen9randombattle.json, gen9babyrandombattle.json

#### Conversion Modes
1. **Single entry per Pokemon (Basic)** - One moveset per Pokemon, no tags
2. **All roles (Complete Sets)** - All roles with tags for each Pokemon
3. **Pool format with tags (Recommended)** - Pokemon with TPP tags for manual pool creation
4. **Complete trainer pool (Auto-Generated)** - Full trainer with configured pool

#### Archetype Filtering
- **None** - Process all Pokemon
- **Types** - Filter by Pokemon types (e.g., "Water,Electric")
- **Trainer Class** - Select from 50+ predefined trainer archetypes (dropdown menu)

#### Pool Settings
- Configure pool size (4-20 Pokemon)
- Configure party size (1-6 Pokemon)
- Only used in "trainer-pool" mode

#### Output Options
- Choose output filename
- Option to split output into separate files by format
- "Open Output Folder" button for quick access to results

#### Progress Display
- Real-time output from the converter
- Status bar showing current operation
- Success/error notifications
- Clear output button for multiple runs

### Screenshots & Tips

**Tip:** The GUI automatically streams the converter's output in real-time, so you can see exactly what's happening during conversion.

**Tip:** Use "Open Output Folder" after conversion to quickly access your generated files.

**Tip:** The trainer class dropdown is populated from `trainer_archetypes.json`, making it easy to create themed trainers.

## Files Created

- `converted_movesets.txt` - The output file with converted Pokemon
- `gen9randomdoublesbattle.json` - Downloaded Showdown data (not tracked by git)
- `gui_converter.py` - GUI application for the converter
- `launch_gui.sh` - Linux/Mac launcher for the GUI
- `launch_gui.bat` - Windows launcher for the GUI

## See Also

- [Trainer Party Pool Documentation](../../docs/tutorials/how_to_trainer_party_pool.md)
- [trainers.party Format Documentation](../../src/data/trainers.party)
