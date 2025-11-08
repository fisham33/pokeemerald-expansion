# Random Doubles Battle to trainers.party Converter

Convert Pokemon Showdown's Random Doubles Battle data into `trainers.party` format with full Trainer Party Pool (TPP) support!

## Features

✅ **Convert 600+ Pokemon movesets** from Showdown's Random Battle formats
✅ **Multi-File Support** - processes Doubles, Singles, and Baby Random Battles
✅ **Set Variants** - generates 2 variants when Pokemon have multiple abilities/items/5+ moves
✅ **Automatic Tag Assignment** based on roles and abilities
✅ **Trainer Party Pool Support** with configurable pool sizes
✅ **Weather/Terrain Detection** automatically tags weather setters and abusers
✅ **Multiple Output Modes** for different use cases
✅ **Smart Role Mapping** converts Showdown roles to TPP tags
✅ **No Level Required** - levels are optional in trainers.party format

## Quick Start

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
- `--mode {single|all-roles|pool|trainer-pool}` - Conversion mode (default: single)
- `--input`, `-i` - Input JSON file (default: gen9randomdoublesbattle.json)
- `--output`, `-o` - Output file (default: converted_movesets.txt)
- `--pool-size` - Pool size for trainer-pool mode (default: 8)
- `--party-size` - Party size for trainer-pool mode (default: 4)

### Examples:
```bash
# Generate pool entries with custom output file
python3 convert_randbats_to_party.py --mode pool -o my_pool.txt

# Generate trainer with larger pool
python3 convert_randbats_to_party.py --mode trainer-pool --pool-size 16 --party-size 6

# Process custom JSON file
python3 convert_randbats_to_party.py --mode pool -i custom_data.json
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

## Files Created

- `converted_movesets.txt` - The output file with converted Pokemon
- `gen9randomdoublesbattle.json` - Downloaded Showdown data (not tracked by git)

## See Also

- [Trainer Party Pool Documentation](../../docs/tutorials/how_to_trainer_party_pool.md)
- [trainers.party Format Documentation](../../src/data/trainers.party)
