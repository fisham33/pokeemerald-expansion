#!/usr/bin/env python3
"""
Generate palette features documentation for all Pokemon species.
This script analyzes palette files and creates documentation entries.
"""

import os
import re
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Tuple, Optional

# Base directory
BASE_DIR = Path(__file__).parent.parent
SPECIES_HEADER = BASE_DIR / "include" / "constants" / "species.h"
GRAPHICS_DIR = BASE_DIR / "graphics" / "pokemon"
OUTPUT_FILE = BASE_DIR / "docs" / "PALETTE_FEATURES_REFERENCE.md"

# Color names based on RGB values
COLOR_NAMES = {
    'red': [(180, 0, 0), (255, 100, 100)],
    'orange': [(200, 100, 0), (255, 180, 100)],
    'yellow': [(200, 200, 0), (255, 255, 150)],
    'green': [(0, 150, 0), (150, 255, 150)],
    'cyan': [(0, 150, 150), (150, 255, 255)],
    'blue': [(0, 0, 150), (150, 150, 255)],
    'purple': [(150, 0, 150), (255, 150, 255)],
    'pink': [(255, 150, 180), (255, 200, 220)],
    'brown': [(100, 50, 0), (180, 120, 80)],
    'grey': [(80, 80, 80), (180, 180, 180)],
    'white': [(220, 220, 220), (255, 255, 255)],
    'black': [(0, 0, 0), (50, 50, 50)],
}


def parse_species_header() -> List[Tuple[int, str, str]]:
    """Parse species.h and return list of (id, constant_name, display_name)."""
    species_list = []

    with open(SPECIES_HEADER, 'r') as f:
        content = f.read()

    # Match #define SPECIES_NAME value
    pattern = r'#define\s+(SPECIES_\w+)\s+(\d+)'
    matches = re.findall(pattern, content)

    for const_name, species_id in matches:
        # Skip special cases
        if const_name in ['SPECIES_EGG', 'SPECIES_SHINY_TAG']:
            continue

        species_id = int(species_id)
        # Convert SPECIES_PIKACHU to "Pikachu"
        display_name = const_name.replace('SPECIES_', '').replace('_', ' ').title()
        species_list.append((species_id, const_name, display_name))

    return sorted(species_list, key=lambda x: x[0])


def find_graphics_dir(species_const: str) -> Optional[Path]:
    """Find the graphics directory for a species."""
    # Convert SPECIES_PIKACHU to pikachu
    base_name = species_const.replace('SPECIES_', '').lower()

    # Try direct match first
    direct_path = GRAPHICS_DIR / base_name
    if (direct_path / "normal.pal").exists():
        return direct_path

    # Try with underscores replaced by slashes (for forms)
    # e.g., SPECIES_MEOWSTIC_F -> meowstic/f
    parts = base_name.split('_')
    if len(parts) > 1:
        for i in range(len(parts) - 1, 0, -1):
            test_path = GRAPHICS_DIR / '/'.join(parts[:i]) / '/'.join(parts[i:])
            if (test_path / "normal.pal").exists():
                return test_path

    return None


def parse_palette_file(pal_path: Path) -> List[Tuple[int, int, int]]:
    """Parse a JASC-PAL palette file and return list of RGB tuples."""
    with open(pal_path, 'r') as f:
        lines = f.readlines()

    # Skip header (JASC-PAL, 0100, color count)
    colors = []
    for line in lines[3:]:
        line = line.strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) >= 3:
            try:
                r, g, b = int(parts[0]), int(parts[1]), int(parts[2])
                colors.append((r, g, b))
            except ValueError:
                continue

    return colors


def get_color_name(rgb: Tuple[int, int, int]) -> str:
    """Get a descriptive color name from RGB values."""
    r, g, b = rgb

    # Special cases
    if r == 0 and g == 0 and b == 0:
        return "black"
    if r > 240 and g > 240 and b > 240:
        return "white"
    if abs(r - g) < 30 and abs(g - b) < 30 and abs(r - b) < 30:
        if r < 80:
            return "dark grey"
        elif r < 160:
            return "grey"
        else:
            return "light grey"

    # Find best matching color
    best_match = "unknown"
    best_score = float('inf')

    for color_name, ranges in COLOR_NAMES.items():
        for color_min, color_max in [ranges]:
            # Calculate distance from range
            distance = 0
            for i in range(3):
                if rgb[i] < color_min[i]:
                    distance += (color_min[i] - rgb[i]) ** 2
                elif rgb[i] > color_max[i]:
                    distance += (rgb[i] - color_max[i]) ** 2

            if distance < best_score:
                best_score = distance
                best_match = color_name

    # Add brightness qualifier
    brightness = (r + g + b) / 3
    if brightness < 80 and best_match not in ['black', 'dark grey']:
        return f"dark {best_match}"
    elif brightness > 200 and best_match not in ['white', 'yellow']:
        return f"light {best_match}"

    return best_match


def analyze_palette(colors: List[Tuple[int, int, int]]) -> List[Tuple[int, int, str]]:
    """
    Analyze palette and return segments with descriptions.
    Returns: List of (start_index, length, description)
    """
    if len(colors) < 2:
        return []

    # Skip index 0 (usually transparent/background)
    segments = []

    # Group consecutive similar colors
    current_start = 1
    current_length = 1

    for i in range(2, len(colors)):
        prev_color = colors[i-1]
        curr_color = colors[i]

        # Calculate color similarity
        color_dist = sum((a - b) ** 2 for a, b in zip(prev_color, curr_color)) ** 0.5

        # If colors are similar (distance < 80), extend current group
        if color_dist < 80:
            current_length += 1
        else:
            # Save current segment
            if current_length > 0:
                # Get representative color (first in segment)
                repr_color = colors[current_start]
                color_desc = get_color_name(repr_color)
                segments.append((current_start, current_length, color_desc))

            # Start new segment
            current_start = i
            current_length = 1

    # Don't forget the last segment
    if current_length > 0:
        repr_color = colors[current_start]
        color_desc = get_color_name(repr_color)
        segments.append((current_start, current_length, color_desc))

    return segments


def generate_species_entry(species_id: int, species_const: str, display_name: str) -> str:
    """Generate documentation entry for a species."""
    # Find graphics directory
    graphics_dir = find_graphics_dir(species_const)

    if graphics_dir is None:
        # Species has no graphics, return placeholder
        return f"### #{species_id:03d} {species_const}\n```c\n// Graphics not found\n```\n"

    # Parse palette
    pal_path = graphics_dir / "normal.pal"
    try:
        colors = parse_palette_file(pal_path)
    except Exception as e:
        return f"### #{species_id:03d} {species_const}\n```c\n// Error reading palette: {e}\n```\n"

    if len(colors) < 2:
        return f"### #{species_id:03d} {species_const}\n```c\n// Invalid palette\n```\n"

    # Analyze palette segments
    segments = analyze_palette(colors)

    # Generate entry
    entry = f"### #{species_id:03d} {species_const}\n```c\n[{species_const}] = {{\n"

    # Add up to 5 segments as PALa-PALe
    pal_labels = ['PALa', 'PALb', 'PALc', 'PALd', 'PALe']
    for i, (start, length, color_desc) in enumerate(segments[:5]):
        label = pal_labels[i]
        entry += f"    {label}({start}, {length}),    // {color_desc}\n"

    entry += "},\n```\n"

    return entry


def generate_documentation():
    """Generate complete documentation file."""
    print("Parsing species header...")
    species_list = parse_species_header()
    print(f"Found {len(species_list)} species definitions")

    # Read existing header from current file
    header = """# Pokémon Palette Features Reference

This document provides a comprehensive reference of palette features (body parts, colors, etc.) for each Pokémon species, to help developers easily configure the Colour Variants feature.

## How to Use This Reference

1. Find your desired Pokémon species in this document
2. Review the available palette features (PALa, PALb, PALc, etc.) with their descriptions
3. Choose up to 2 features you want to make variable in your game
4. Copy the chosen features as PAL1/PAL2 into `include/variant_colours.h` in the `gSpeciesVariants` array
5. Add corresponding HCL1/HCL2 values to define the variation amounts

## Example Usage

If you see this reference entry:
```c
[SPECIES_PIKACHU] = {
    PALa(1, 5),    // Yellow body
    PALb(6, 3),    // Red cheeks
    PALc(9, 2),    // Brown stripes
    PALd(13, 2),   // Black ear tips
},
```

And you want to vary the body color and cheeks, you would add to `variant_colours.h`:
```c
[SPECIES_PIKACHU] = {
    PAL1(1, 5),              // Yellow body
    HCL1(30, 10, 5, FALSE),  // Vary hue slightly, chroma and luminance
    PAL2(6, 3),              // Red cheeks
    HCL2(20, 15, 0, FALSE),  // Vary hue and chroma, keep luminance
},
```

---

"""

    footer = """
---

## Notes for Developers

### Tips for Choosing Palette Features

1. **Most Recognizable Features First**: Choose features that are most iconic to the Pokémon (e.g., Pikachu's yellow body, Charmander's tail flame)
2. **Complementary Variations**: Select features that will create interesting combinations when varied together
3. **Preserve Recognition**: Avoid varying ALL defining features - keep some consistent so the Pokémon remains recognizable
4. **Evolution Chains**: Use the same HCL values for evolution chains to preserve color shifts across evolutions

### Palette Index Determination

The color descriptions in this document are automatically generated based on palette analysis. For more accurate descriptions:

1. Open `graphics/pokemon/[species]/anim_front.png` in an image editor that supports indexed color (e.g., GIMP)
2. View the color palette (Windows → Dockable Dialogs → Colormap in GIMP)
3. Identify which palette indices (0-15) correspond to which features
4. Group adjacent indices that belong to the same feature (e.g., light/dark shades of the same body part)

### Color Groups Best Practices

- **Start**: First palette index of the feature (0-15)
- **Length**: Number of consecutive palette indices for that feature (1-15)
- Features should use **adjacent palette indices** for best results
- Index 0 is typically reserved for transparency/background

---

## Contributing

To improve descriptions in this reference:

1. Analyze the Pokémon's sprite palette using GIMP or similar tool
2. Identify distinct features (body parts, markings, etc.)
3. Update the entry with more descriptive comments
4. Use clear, descriptive comments for each palette feature
5. List features in order of visual importance/size

This reference is maintained as part of the Colour Variants feature documentation.
"""

    # Generate entries grouped by 100s
    output = header

    current_group_start = 1
    for species_id, species_const, display_name in species_list:
        # Add group header every 100 species
        if species_id > current_group_start + 99:
            current_group_start = ((species_id - 1) // 100) * 100 + 1

        if species_id == current_group_start or species_id == 1:
            group_end = min(current_group_start + 99, species_list[-1][0])
            output += f"\n## Pokémon #{current_group_start}-{group_end}\n\n"

        # Generate entry
        print(f"Processing {species_const} (#{species_id})...")
        entry = generate_species_entry(species_id, species_const, display_name)
        output += entry + "\n"

    output += footer

    # Write output file
    print(f"\nWriting to {OUTPUT_FILE}...")
    with open(OUTPUT_FILE, 'w') as f:
        f.write(output)

    print(f"Done! Generated documentation for {len(species_list)} species.")


if __name__ == "__main__":
    generate_documentation()
