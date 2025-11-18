#!/usr/bin/env python3
"""
Pokeemerald-Expansion File Insertion GUI
A graphical tool for inserting various file types into pokeemerald-expansion projects.

Supports:
- Pokemon graphics (sprites, palettes, icons, footprints, overworld)
- Trainer pictures
- Items (icons and palettes)
- Overworld object sprites
- Audio files (cries, music, sound effects)
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import os
import shutil
import re
from pathlib import Path
from typing import Optional, List, Tuple
import json

class FileInserterGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Pokeemerald-Expansion File Inserter")
        self.root.geometry("900x700")

        # Find project root
        self.project_root = self.find_project_root()
        if not self.project_root:
            messagebox.showerror("Error", "Could not find pokeemerald-expansion project root!")
            self.root.destroy()
            return

        # Track operations for undo
        self.operations_log = []

        self.setup_ui()

    def find_project_root(self) -> Optional[Path]:
        """Find the pokeemerald-expansion project root directory."""
        current = Path.cwd()

        # Check current directory and parents
        for path in [current] + list(current.parents):
            if (path / "Makefile").exists() and (path / "graphics").exists():
                return path

        return None

    def setup_ui(self):
        """Set up the user interface."""
        # Create notebook for tabs
        self.notebook = ttk.Notebook(self.root)
        self.notebook.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)

        # Create tabs
        self.create_pokemon_tab()
        self.create_trainer_tab()
        self.create_item_tab()
        self.create_overworld_tab()
        self.create_audio_tab()

        # Create log panel
        self.create_log_panel()

        # Status bar
        self.status_var = tk.StringVar()
        self.status_var.set(f"Project: {self.project_root}")
        status_bar = ttk.Label(self.root, textvariable=self.status_var, relief=tk.SUNKEN)
        status_bar.pack(side=tk.BOTTOM, fill=tk.X)

    def create_pokemon_tab(self):
        """Create the Pokemon insertion tab."""
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text="Pokemon")

        # Species name input
        ttk.Label(frame, text="Species Name (lowercase):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.pokemon_name_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.pokemon_name_var, width=30).grid(row=0, column=1, padx=5, pady=5)

        # File selection section
        files_frame = ttk.LabelFrame(frame, text="Graphics Files", padding=10)
        files_frame.grid(row=1, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        self.pokemon_files = {}
        file_types = [
            ("Front Sprite (anim_front.png)", "anim_front"),
            ("Back Sprite (back.png)", "back"),
            ("Icon (icon.png)", "icon"),
            ("Normal Palette (normal.pal)", "normal_pal"),
            ("Shiny Palette (shiny.pal)", "shiny_pal"),
            ("Footprint (footprint.png)", "footprint"),
            ("Overworld (overworld.png)", "overworld"),
            ("Overworld Normal Palette (overworld_normal.pal)", "overworld_normal_pal"),
            ("Overworld Shiny Palette (overworld_shiny.pal)", "overworld_shiny_pal"),
        ]

        for i, (label, key) in enumerate(file_types):
            ttk.Label(files_frame, text=label).grid(row=i, column=0, sticky=tk.W, padx=5, pady=2)
            path_var = tk.StringVar()
            self.pokemon_files[key] = path_var
            ttk.Entry(files_frame, textvariable=path_var, width=40).grid(row=i, column=1, padx=5, pady=2)
            ttk.Button(files_frame, text="Browse",
                      command=lambda k=key: self.browse_file(self.pokemon_files[k])).grid(row=i, column=2, padx=5, pady=2)

        # Options
        options_frame = ttk.LabelFrame(frame, text="Options", padding=10)
        options_frame.grid(row=2, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        self.copy_from_existing_var = tk.BooleanVar(value=False)
        ttk.Checkbutton(options_frame, text="Copy from existing Pokemon",
                       variable=self.copy_from_existing_var,
                       command=self.toggle_copy_from_existing).grid(row=0, column=0, sticky=tk.W)

        ttk.Label(options_frame, text="Copy from:").grid(row=1, column=0, sticky=tk.W, padx=20)
        self.copy_source_var = tk.StringVar()
        self.copy_source_entry = ttk.Entry(options_frame, textvariable=self.copy_source_var, width=20, state=tk.DISABLED)
        self.copy_source_entry.grid(row=1, column=1, padx=5)

        # Insert button
        ttk.Button(frame, text="Insert Pokemon Graphics",
                  command=self.insert_pokemon,
                  style="Accent.TButton").grid(row=3, column=0, columnspan=3, pady=10)

    def create_trainer_tab(self):
        """Create the trainer picture insertion tab."""
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text="Trainer Pic")

        # Trainer name
        ttk.Label(frame, text="Trainer Pic Name:").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.trainer_name_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.trainer_name_var, width=30).grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(frame, text="(e.g., 'cool_trainer_m')").grid(row=0, column=2, sticky=tk.W, padx=5, pady=5)

        # File selection
        files_frame = ttk.LabelFrame(frame, text="Graphics Files", padding=10)
        files_frame.grid(row=1, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        ttk.Label(files_frame, text="Front Pic (PNG):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.trainer_front_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.trainer_front_var, width=40).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.trainer_front_var)).grid(row=0, column=2, padx=5, pady=5)

        ttk.Label(files_frame, text="Palette (PAL):").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.trainer_pal_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.trainer_pal_var, width=40).grid(row=1, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.trainer_pal_var)).grid(row=1, column=2, padx=5, pady=5)

        # Info
        info_text = ("NOTE: Trainer sprites must be PNG with max 16 colors.\n"
                    "The first palette color becomes transparent in-game.")
        ttk.Label(frame, text=info_text, foreground="blue").grid(row=2, column=0, columnspan=3, pady=10)

        # Insert button
        ttk.Button(frame, text="Insert Trainer Picture",
                  command=self.insert_trainer,
                  style="Accent.TButton").grid(row=3, column=0, columnspan=3, pady=10)

    def create_item_tab(self):
        """Create the item insertion tab."""
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text="Item")

        # Item name
        ttk.Label(frame, text="Item Name (lowercase):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.item_name_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.item_name_var, width=30).grid(row=0, column=1, padx=5, pady=5)

        # File selection
        files_frame = ttk.LabelFrame(frame, text="Graphics Files", padding=10)
        files_frame.grid(row=1, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        ttk.Label(files_frame, text="Icon (PNG):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.item_icon_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.item_icon_var, width=40).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.item_icon_var)).grid(row=0, column=2, padx=5, pady=5)

        ttk.Label(files_frame, text="Palette (PAL):").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.item_pal_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.item_pal_var, width=40).grid(row=1, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.item_pal_var)).grid(row=1, column=2, padx=5, pady=5)

        # Insert button
        ttk.Button(frame, text="Insert Item Graphics",
                  command=self.insert_item,
                  style="Accent.TButton").grid(row=2, column=0, columnspan=3, pady=10)

    def create_overworld_tab(self):
        """Create the overworld sprite insertion tab."""
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text="Overworld Sprite")

        # Sprite name
        ttk.Label(frame, text="Sprite Name:").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.ow_name_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.ow_name_var, width=30).grid(row=0, column=1, padx=5, pady=5)

        # File selection
        files_frame = ttk.LabelFrame(frame, text="Graphics Files", padding=10)
        files_frame.grid(row=1, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        ttk.Label(files_frame, text="Sprite (PNG, 4-bit):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.ow_sprite_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.ow_sprite_var, width=40).grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.ow_sprite_var)).grid(row=0, column=2, padx=5, pady=5)

        ttk.Label(files_frame, text="Palette (PAL):").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.ow_pal_var = tk.StringVar()
        ttk.Entry(files_frame, textvariable=self.ow_pal_var, width=40).grid(row=1, column=1, padx=5, pady=5)
        ttk.Button(files_frame, text="Browse",
                  command=lambda: self.browse_file(self.ow_pal_var)).grid(row=1, column=2, padx=5, pady=5)

        # Size configuration
        size_frame = ttk.LabelFrame(frame, text="Sprite Configuration", padding=10)
        size_frame.grid(row=2, column=0, columnspan=3, sticky=tk.EW, padx=5, pady=5)

        ttk.Label(size_frame, text="Frame Width (tiles):").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.ow_width_var = tk.StringVar(value="4")
        ttk.Entry(size_frame, textvariable=self.ow_width_var, width=10).grid(row=0, column=1, padx=5, pady=5)

        ttk.Label(size_frame, text="Frame Height (tiles):").grid(row=0, column=2, sticky=tk.W, padx=5, pady=5)
        self.ow_height_var = tk.StringVar(value="4")
        ttk.Entry(size_frame, textvariable=self.ow_height_var, width=10).grid(row=0, column=3, padx=5, pady=5)

        ttk.Label(size_frame, text="(1 tile = 8x8 pixels)").grid(row=1, column=0, columnspan=4, pady=2)

        # Insert button
        ttk.Button(frame, text="Insert Overworld Sprite",
                  command=self.insert_overworld,
                  style="Accent.TButton").grid(row=3, column=0, columnspan=3, pady=10)

    def create_audio_tab(self):
        """Create the audio file insertion tab."""
        frame = ttk.Frame(self.notebook)
        self.notebook.add(frame, text="Audio")

        # Audio type selection
        ttk.Label(frame, text="Audio Type:").grid(row=0, column=0, sticky=tk.W, padx=5, pady=5)
        self.audio_type_var = tk.StringVar(value="cry")
        audio_types = [("Pokemon Cry", "cry"), ("Music (MIDI)", "music"), ("Sound Effect", "sfx")]

        for i, (label, value) in enumerate(audio_types):
            ttk.Radiobutton(frame, text=label, variable=self.audio_type_var,
                           value=value).grid(row=0, column=i+1, padx=5, pady=5)

        # Name
        ttk.Label(frame, text="Audio Name:").grid(row=1, column=0, sticky=tk.W, padx=5, pady=5)
        self.audio_name_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.audio_name_var, width=30).grid(row=1, column=1, padx=5, pady=5)

        # File selection
        ttk.Label(frame, text="Audio File:").grid(row=2, column=0, sticky=tk.W, padx=5, pady=5)
        self.audio_file_var = tk.StringVar()
        ttk.Entry(frame, textvariable=self.audio_file_var, width=40).grid(row=2, column=1, columnspan=2, padx=5, pady=5)
        ttk.Button(frame, text="Browse",
                  command=lambda: self.browse_file(self.audio_file_var)).grid(row=2, column=3, padx=5, pady=5)

        # Info
        info_text = ("NOTE: For cries, use MP3/WAV files. They will be converted to AIF format.\n"
                    "For music, use MIDI files (.mid). For SFX, use appropriate format.")
        ttk.Label(frame, text=info_text, foreground="blue").grid(row=3, column=0, columnspan=4, pady=10)

        # Insert button
        ttk.Button(frame, text="Insert Audio File",
                  command=self.insert_audio,
                  style="Accent.TButton").grid(row=4, column=0, columnspan=4, pady=10)

    def create_log_panel(self):
        """Create the log output panel."""
        log_frame = ttk.LabelFrame(self.root, text="Operation Log", padding=5)
        log_frame.pack(fill=tk.BOTH, expand=False, padx=10, pady=5)

        self.log_text = scrolledtext.ScrolledText(log_frame, height=8, width=80, state=tk.DISABLED)
        self.log_text.pack(fill=tk.BOTH, expand=True)

        # Clear log button
        ttk.Button(log_frame, text="Clear Log", command=self.clear_log).pack(side=tk.RIGHT, padx=5, pady=5)

    def log(self, message: str, level: str = "INFO"):
        """Add a message to the log."""
        self.log_text.config(state=tk.NORMAL)
        timestamp = ""
        color_tag = level.lower()

        # Configure tags for different log levels
        self.log_text.tag_config("info", foreground="black")
        self.log_text.tag_config("success", foreground="green", font=("TkDefaultFont", 9, "bold"))
        self.log_text.tag_config("warning", foreground="orange")
        self.log_text.tag_config("error", foreground="red", font=("TkDefaultFont", 9, "bold"))
        self.log_text.tag_config("section", foreground="blue", font=("TkDefaultFont", 10, "bold"))
        self.log_text.tag_config("manual", foreground="darkred", font=("TkDefaultFont", 9))
        self.log_text.tag_config("code", foreground="darkgreen", font=("Courier", 8))

        self.log_text.insert(tk.END, f"[{level}] {message}\n", color_tag)
        self.log_text.see(tk.END)
        self.log_text.config(state=tk.DISABLED)

    def log_section(self, title: str):
        """Add a section header to the log."""
        self.log("", "INFO")  # Blank line
        self.log(f"═══ {title} ═══", "SECTION")

    def log_manual_step(self, step_num: int, description: str):
        """Add a manual step to the log."""
        self.log(f"  {step_num}. {description}", "MANUAL")

    def log_code(self, code: str):
        """Add a code snippet to the log."""
        self.log(f"     {code}", "CODE")

    def clear_log(self):
        """Clear the log panel."""
        self.log_text.config(state=tk.NORMAL)
        self.log_text.delete(1.0, tk.END)
        self.log_text.config(state=tk.DISABLED)

    def browse_file(self, var: tk.StringVar):
        """Open file browser and set the result to the given variable."""
        filename = filedialog.askopenfilename(
            title="Select File",
            initialdir=str(self.project_root)
        )
        if filename:
            var.set(filename)

    def toggle_copy_from_existing(self):
        """Toggle the copy from existing Pokemon option."""
        if self.copy_from_existing_var.get():
            self.copy_source_entry.config(state=tk.NORMAL)
        else:
            self.copy_source_entry.config(state=tk.DISABLED)

    def insert_pokemon(self):
        """Insert Pokemon graphics into the project."""
        species_name = self.pokemon_name_var.get().strip().lower()

        if not species_name:
            messagebox.showerror("Error", "Please enter a species name!")
            return

        # Validate name (only lowercase letters and underscores)
        if not re.match(r'^[a-z_]+$', species_name):
            messagebox.showerror("Error", "Species name must only contain lowercase letters and underscores!")
            return

        self.log(f"Inserting Pokemon graphics for: {species_name}", "INFO")

        try:
            # Create directory
            pokemon_dir = self.project_root / "graphics" / "pokemon" / species_name

            if self.copy_from_existing_var.get():
                # Copy from existing
                source_species = self.copy_source_var.get().strip().lower()
                if not source_species:
                    messagebox.showerror("Error", "Please specify a Pokemon to copy from!")
                    return

                source_dir = self.project_root / "graphics" / "pokemon" / source_species
                if not source_dir.exists():
                    messagebox.showerror("Error", f"Source Pokemon '{source_species}' not found!")
                    return

                shutil.copytree(source_dir, pokemon_dir, dirs_exist_ok=True)
                self.log(f"Copied graphics from {source_species}", "SUCCESS")
            else:
                pokemon_dir.mkdir(parents=True, exist_ok=True)

            # Copy individual files
            file_mapping = {
                "anim_front": "anim_front.png",
                "back": "back.png",
                "icon": "icon.png",
                "normal_pal": "normal.pal",
                "shiny_pal": "shiny.pal",
                "footprint": "footprint.png",
                "overworld": "overworld.png",
                "overworld_normal_pal": "overworld_normal.pal",
                "overworld_shiny_pal": "overworld_shiny.pal",
            }

            for key, dest_name in file_mapping.items():
                source_path = self.pokemon_files[key].get().strip()
                if source_path and os.path.exists(source_path):
                    dest_path = pokemon_dir / dest_name
                    shutil.copy2(source_path, dest_path)
                    self.log(f"Copied {dest_name}", "SUCCESS")

            # Summary of what was done
            self.log_section("✓ AUTOMATED STEPS COMPLETED")
            self.log(f"Files copied to: graphics/pokemon/{species_name}/", "SUCCESS")

            files_copied = []
            for key, dest_name in file_mapping.items():
                if self.pokemon_files[key].get().strip():
                    files_copied.append(dest_name)

            if files_copied:
                self.log(f"Graphics files: {', '.join(files_copied)}", "SUCCESS")

            if self.copy_from_existing_var.get():
                self.log(f"Template copied from: {source_species}", "SUCCESS")

            self.log("✓ File organization complete!", "SUCCESS")

            # Clear manual steps
            self.log_section("⚠ MANUAL STEPS REQUIRED")
            self.log("The tool CANNOT do these automatically - you must edit code files:", "WARNING")

            species_upper = species_name.upper()
            species_title = species_name.replace('_', ' ').title().replace(' ', '')

            self.log_manual_step(1, f"Add species constant to include/constants/species.h")
            self.log_code(f"#define SPECIES_{species_upper}  XXXX  // Replace XXXX with next number")
            self.log_code(f"// Also update #define SPECIES_EGG to be (SPECIES_{species_upper} + 1)")

            self.log_manual_step(2, f"Add graphics references to src/data/graphics/pokemon.h")
            self.log_code(f"const u32 gMonFrontPic_{species_title}[] = INCBIN_U32(\"graphics/pokemon/{species_name}/anim_front.4bpp.lz\");")
            self.log_code(f"const u32 gMonBackPic_{species_title}[] = INCBIN_U32(\"graphics/pokemon/{species_name}/back.4bpp.lz\");")
            self.log_code(f"const u16 gMonPalette_{species_title}[] = INCBIN_U16(\"graphics/pokemon/{species_name}/normal.gbapal\");")
            self.log_code(f"const u16 gMonShinyPalette_{species_title}[] = INCBIN_U16(\"graphics/pokemon/{species_name}/shiny.gbapal\");")
            self.log_code(f"const u8 gMonIcon_{species_title}[] = INCBIN_U8(\"graphics/pokemon/{species_name}/icon.4bpp\");")
            self.log_code(f"const u8 gMonFootprint_{species_title}[] = INCBIN_U8(\"graphics/pokemon/{species_name}/footprint.1bpp\");")

            self.log_manual_step(3, f"Add species entry to src/data/pokemon/species_info.h")
            self.log_code(f"[SPECIES_{species_upper}] = {{")
            self.log_code(f"    .baseHP = 100,  // Set your stats")
            self.log_code(f"    .types = MON_TYPES(TYPE_NORMAL),")
            self.log_code(f"    .speciesName = _(\"YourName\"),")
            self.log_code(f"    .frontPic = gMonFrontPic_{species_title},")
            self.log_code(f"    .palette = gMonPalette_{species_title},")
            self.log_code(f"    // ... etc (see tutorial)")
            self.log_code(f"}},")

            self.log_manual_step(4, f"Add to National Dex in include/constants/pokedex.h")
            self.log_code(f"NATIONAL_DEX_{species_upper},")

            self.log_manual_step(5, f"Add level-up learnset to src/data/pokemon/level_up_learnsets/gen_9.h")
            self.log_manual_step(6, f"Add teachable learnset to src/data/pokemon/teachable_learnsets.h")

            self.log("", "INFO")
            self.log("📖 Full tutorial: docs/tutorials/how_to_new_pokemon.md", "INFO")
            self.log("", "INFO")

            messagebox.showinfo("Success",
                f"✓ FILES COPIED SUCCESSFULLY!\n\n"
                f"Location: graphics/pokemon/{species_name}/\n\n"
                f"⚠ IMPORTANT: Manual code editing required!\n"
                f"Check the Operation Log below for detailed steps.\n\n"
                f"The tool has organized your files, but you must\n"
                f"still edit the C code to integrate the Pokemon.")

        except Exception as e:
            self.log(f"Error inserting Pokemon graphics: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert Pokemon graphics:\n{e}")

    def insert_trainer(self):
        """Insert trainer picture into the project."""
        trainer_name = self.trainer_name_var.get().strip().lower()

        if not trainer_name:
            messagebox.showerror("Error", "Please enter a trainer name!")
            return

        front_pic = self.trainer_front_var.get().strip()
        palette = self.trainer_pal_var.get().strip()

        if not front_pic or not os.path.exists(front_pic):
            messagebox.showerror("Error", "Please select a valid front pic file!")
            return

        self.log(f"Inserting trainer picture: {trainer_name}", "INFO")

        try:
            # Copy front pic
            dest_front = self.project_root / "graphics" / "trainers" / "front_pics" / f"{trainer_name}.png"
            dest_front.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(front_pic, dest_front)
            self.log(f"Copied front pic to {dest_front}", "SUCCESS")

            # Copy palette if provided
            if palette and os.path.exists(palette):
                dest_pal = self.project_root / "graphics" / "trainers" / "palettes" / f"{trainer_name}.gbapal"
                dest_pal.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(palette, dest_pal)
                self.log(f"Copied palette to {dest_pal}", "SUCCESS")

            # Summary of what was done
            self.log_section("✓ AUTOMATED STEPS COMPLETED")
            self.log(f"Front pic copied to: graphics/trainers/front_pics/{trainer_name}.png", "SUCCESS")
            if palette and os.path.exists(palette):
                self.log(f"Palette copied to: graphics/trainers/palettes/{trainer_name}.gbapal", "SUCCESS")
            self.log("✓ File organization complete!", "SUCCESS")

            # Clear manual steps
            self.log_section("⚠ MANUAL STEPS REQUIRED")
            self.log("The tool CANNOT do these automatically - you must edit code files:", "WARNING")

            trainer_upper = trainer_name.upper()
            trainer_title = trainer_name.replace('_', ' ').title().replace(' ', '')

            self.log_manual_step(1, f"Add graphics references to src/data/graphics/trainers.h")
            self.log("   Find the section near the bottom with other trainers and add:")
            self.log_code(f"const u32 gTrainerFrontPic_{trainer_title}[] = INCBIN_U32(\"graphics/trainers/front_pics/{trainer_name}.4bpp.smol\");")
            self.log_code(f"const u16 gTrainerPalette_{trainer_title}[] = INCBIN_U16(\"graphics/trainers/palettes/{trainer_name}.gbapal\");")

            self.log_manual_step(2, f"Add trainer sprite to gTrainerSprites[] in src/data/graphics/trainers.h")
            self.log("   Find the const struct TrainerSprite gTrainerSprites[] array and add:")
            self.log_code(f"TRAINER_SPRITE(TRAINER_PIC_{trainer_upper}, gTrainerFrontPic_{trainer_title}, gTrainerPalette_{trainer_title}),")

            self.log_manual_step(3, f"Add constant to include/constants/trainers.h")
            self.log("   Find the #define TRAINER_PIC_XXX section and add:")
            self.log_code(f"#define TRAINER_PIC_{trainer_upper}  XX  // Replace XX with next number in sequence")

            self.log("", "INFO")
            self.log("📖 Full tutorial: docs/tutorials/how_to_trainer_front_pic.md", "INFO")
            self.log("", "INFO")

            messagebox.showinfo("Success",
                f"✓ FILES COPIED SUCCESSFULLY!\n\n"
                f"Front pic: graphics/trainers/front_pics/{trainer_name}.png\n\n"
                f"⚠ IMPORTANT: Manual code editing required!\n"
                f"Check the Operation Log below for detailed steps.\n\n"
                f"The tool has organized your files, but you must\n"
                f"edit 2 C files to integrate the trainer pic.")

        except Exception as e:
            self.log(f"Error inserting trainer graphics: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert trainer graphics:\n{e}")

    def insert_item(self):
        """Insert item graphics into the project."""
        item_name = self.item_name_var.get().strip().lower()

        if not item_name:
            messagebox.showerror("Error", "Please enter an item name!")
            return

        icon = self.item_icon_var.get().strip()
        palette = self.item_pal_var.get().strip()

        if not icon or not os.path.exists(icon):
            messagebox.showerror("Error", "Please select a valid icon file!")
            return

        self.log(f"Inserting item graphics: {item_name}", "INFO")

        try:
            # Copy icon
            dest_icon = self.project_root / "graphics" / "items" / "icons" / f"{item_name}.png"
            dest_icon.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(icon, dest_icon)
            self.log(f"Copied icon to {dest_icon}", "SUCCESS")

            # Copy palette if provided
            if palette and os.path.exists(palette):
                dest_pal = self.project_root / "graphics" / "items" / "icon_palettes" / f"{item_name}.gbapal"
                dest_pal.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(palette, dest_pal)
                self.log(f"Copied palette to {dest_pal}", "SUCCESS")

            # Summary of what was done
            self.log_section("✓ AUTOMATED STEPS COMPLETED")
            self.log(f"Icon copied to: graphics/items/icons/{item_name}.png", "SUCCESS")
            if palette and os.path.exists(palette):
                self.log(f"Palette copied to: graphics/items/icon_palettes/{item_name}.gbapal", "SUCCESS")
            self.log("✓ File organization complete!", "SUCCESS")

            # Clear manual steps
            self.log_section("⚠ MANUAL STEPS REQUIRED")
            self.log("The tool CANNOT do these automatically - you must edit code files:", "WARNING")

            item_upper = item_name.upper()
            item_title = item_name.replace('_', ' ').title().replace(' ', '')

            self.log_manual_step(1, f"Add item constant to include/constants/items.h")
            self.log("   Find the appropriate section (Medicine, Balls, etc.) and add:")
            self.log_code(f"#define ITEM_{item_upper}  XXXX  // Replace XXXX with next number")

            self.log_manual_step(2, f"Add graphics references to src/data/graphics/items.h")
            self.log("   Add near other similar items:")
            self.log_code(f"const u32 gItemIcon_{item_title}[] = INCBIN_U32(\"graphics/items/icons/{item_name}.4bpp.smol\");")
            self.log_code(f"const u16 gItemIconPalette_{item_title}[] = INCBIN_U16(\"graphics/items/icon_palettes/{item_name}.gbapal\");")

            self.log_manual_step(3, f"Add item data to src/data/items.h")
            self.log("   Find the [ITEM_XXX] section and add a new entry:")
            self.log_code(f"[ITEM_{item_upper}] =")
            self.log_code(f"{{")
            self.log_code(f"    .name = _(\"YourItem\"),")
            self.log_code(f"    .price = 200,")
            self.log_code(f"    .description = COMPOUND_STRING(\"Description here\"),")
            self.log_code(f"    .pocket = POCKET_ITEMS,")
            self.log_code(f"    .type = ITEM_USE_BAG_MENU,")
            self.log_code(f"    .iconPic = gItemIcon_{item_title},")
            self.log_code(f"    .iconPalette = gItemIconPalette_{item_title},")
            self.log_code(f"}},")

            self.log("", "INFO")
            self.log("", "INFO")

            messagebox.showinfo("Success",
                f"✓ FILES COPIED SUCCESSFULLY!\n\n"
                f"Icon: graphics/items/icons/{item_name}.png\n\n"
                f"⚠ IMPORTANT: Manual code editing required!\n"
                f"Check the Operation Log below for detailed steps.\n\n"
                f"You must edit 3 files to integrate the item.")

        except Exception as e:
            self.log(f"Error inserting item graphics: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert item graphics:\n{e}")

    def insert_overworld(self):
        """Insert overworld sprite into the project."""
        sprite_name = self.ow_name_var.get().strip().lower()

        if not sprite_name:
            messagebox.showerror("Error", "Please enter a sprite name!")
            return

        sprite_file = self.ow_sprite_var.get().strip()
        palette_file = self.ow_pal_var.get().strip()

        if not sprite_file or not os.path.exists(sprite_file):
            messagebox.showerror("Error", "Please select a valid sprite file!")
            return

        try:
            width = int(self.ow_width_var.get())
            height = int(self.ow_height_var.get())
        except ValueError:
            messagebox.showerror("Error", "Width and height must be numbers!")
            return

        self.log(f"Inserting overworld sprite: {sprite_name}", "INFO")

        try:
            # Copy sprite
            dest_sprite = self.project_root / "graphics" / "object_events" / "pics" / "people" / f"{sprite_name}.png"
            dest_sprite.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(sprite_file, dest_sprite)
            self.log(f"Copied sprite to {dest_sprite}", "SUCCESS")

            # Copy palette if provided
            if palette_file and os.path.exists(palette_file):
                dest_pal = self.project_root / "graphics" / "object_events" / "palettes" / f"{sprite_name}.gbapal"
                dest_pal.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(palette_file, dest_pal)
                self.log(f"Copied palette to {dest_pal}", "SUCCESS")

            # Summary of what was done
            self.log_section("✓ AUTOMATED STEPS COMPLETED")
            self.log(f"Sprite copied to: graphics/object_events/pics/people/{sprite_name}.png", "SUCCESS")
            if palette_file and os.path.exists(palette_file):
                self.log(f"Palette copied to: graphics/object_events/palettes/{sprite_name}.gbapal", "SUCCESS")
            self.log("✓ File organization complete!", "SUCCESS")

            # Clear manual steps
            self.log_section("⚠ MANUAL STEPS REQUIRED")
            self.log("The tool CANNOT do these automatically - you must edit code files:", "WARNING")

            sprite_upper = sprite_name.upper()
            sprite_title = sprite_name.replace('_', ' ').title().replace(' ', '')

            self.log_manual_step(1, f"Add sprite references to src/data/object_events/object_event_graphics.h")
            self.log("   Add near the end of the file:")
            self.log_code(f"const u32 gObjectEventPic_{sprite_title}[] = INCBIN_U32(\"graphics/object_events/pics/people/{sprite_name}.4bpp\");")
            self.log_code(f"const u16 gObjectEventPal_{sprite_title}[] = INCBIN_U16(\"graphics/object_events/palettes/{sprite_name}.gbapal\");")

            self.log_manual_step(2, f"Add build rule to spritesheet_rules.mk")
            self.log(f"   Add this rule (dimensions are {width}x{height} tiles = {width*8}x{height*8} pixels):")
            self.log_code(f"$(OBJEVENTGFXDIR)/people/{sprite_name}.4bpp: %.4bpp: %.png")
            self.log_code(f"\t$(GFX) $< $@ -mwidth {width} -mheight {height}")

            self.log_manual_step(3, f"Add palette tag to src/event_object_movement.c (if using unique palette)")
            self.log_code(f"#define OBJ_EVENT_PAL_{sprite_upper} 0x11XX  // Pick unused palette tag")
            self.log("   Then add to sObjectEventSpritePalettes[] array:")
            self.log_code(f"{{gObjectEventPal_{sprite_title}, OBJ_EVENT_PAL_{sprite_upper}}},")

            self.log_manual_step(4, f"Add pic table to src/data/object_events/object_event_pic_tables.h")
            self.log_code(f"const struct SpriteFrameImage gObjectEventPicTable_{sprite_title}[] = {{")
            self.log_code(f"    overworld_frame(gObjectEventPic_{sprite_title}, {width}, {height}, 0),")
            self.log_code(f"    overworld_frame(gObjectEventPic_{sprite_title}, {width}, {height}, 1),")
            self.log_code(f"    // ... add more frames as needed")
            self.log_code(f"}};")

            self.log_manual_step(5, f"Add graphics info to src/data/object_events/object_event_graphics_info.h")
            self.log_code(f"const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{sprite_title} = {{")
            self.log_code(f"    .tileTag = 0xFFFF,")
            self.log_code(f"    .paletteTag = OBJ_EVENT_PAL_{sprite_upper},  // or OBJ_EVENT_PAL_TAG_NPC_1")
            self.log_code(f"    .width = {width*8}, .height = {height*8},")
            self.log_code(f"    .pics = gObjectEventPicTable_{sprite_title},")
            self.log_code(f"    // ... other fields")
            self.log_code(f"}};")

            self.log_manual_step(6, f"Add to object_event_graphics_info_pointers.h")
            self.log_code(f"const struct ObjectEventGraphicsInfo *const gObjectEventGraphicsInfoPointers[] = {{")
            self.log_code(f"    // ... existing entries")
            self.log_code(f"    [OBJ_EVENT_GFX_{sprite_upper}] = &gObjectEventGraphicsInfo_{sprite_title},")
            self.log_code(f"}};")

            self.log_manual_step(7, f"Add constant to include/constants/event_objects.h")
            self.log_code(f"#define OBJ_EVENT_GFX_{sprite_upper}  XXX  // Use next available number")
            self.log_code(f"// Also update #define NUM_OBJ_EVENT_GFX")

            self.log("", "INFO")
            self.log("⚠ This is the most complex insertion type!", "WARNING")
            self.log("   Consider reviewing existing entries as templates.", "INFO")
            self.log("", "INFO")

            messagebox.showinfo("Success",
                f"✓ FILES COPIED SUCCESSFULLY!\n\n"
                f"Sprite: graphics/object_events/pics/people/{sprite_name}.png\n\n"
                f"⚠ IMPORTANT: Manual code editing required!\n"
                f"This is COMPLEX - you must edit 6+ files!\n\n"
                f"Check the Operation Log for detailed steps.")

        except Exception as e:
            self.log(f"Error inserting overworld sprite: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert overworld sprite:\n{e}")

    def insert_audio(self):
        """Insert audio file into the project."""
        audio_type = self.audio_type_var.get()
        audio_name = self.audio_name_var.get().strip().lower()
        audio_file = self.audio_file_var.get().strip()

        if not audio_name:
            messagebox.showerror("Error", "Please enter an audio name!")
            return

        if not audio_file or not os.path.exists(audio_file):
            messagebox.showerror("Error", "Please select a valid audio file!")
            return

        self.log(f"Inserting audio file: {audio_name} (type: {audio_type})", "INFO")

        try:
            if audio_type == "cry":
                # Copy to cries directory
                dest = self.project_root / "sound" / "direct_sound_samples" / "cries" / f"{audio_name}{Path(audio_file).suffix}"
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(audio_file, dest)

                self.log_section("✓ AUTOMATED STEPS COMPLETED")
                self.log(f"Cry file copied to: sound/direct_sound_samples/cries/{audio_name}{Path(audio_file).suffix}", "SUCCESS")
                self.log("✓ File organization complete!", "SUCCESS")

                self.log_section("⚠ MANUAL STEPS REQUIRED")
                self.log("The tool CANNOT do these automatically - you must convert and edit code:", "WARNING")

                cry_upper = audio_name.upper()
                cry_title = audio_name.replace('_', ' ').title().replace(' ', '')

                self.log_manual_step(1, f"Convert audio to AIF format using ffmpeg")
                self.log("   Run this command in your terminal:")
                self.log_code(f"ffmpeg -i sound/direct_sound_samples/cries/{audio_name}{Path(audio_file).suffix} -c:a pcm_s8 -ac 1 -ar 13379 sound/direct_sound_samples/cries/{audio_name}.aif")
                self.log("   Then delete the original MP3/WAV file after verifying the AIF works")

                self.log_manual_step(2, f"Add cry to sound/direct_sound_data.inc")
                self.log("   Add before the bottom of the file:")
                self.log_code(f"    .align 2")
                self.log_code(f"Cry_{cry_title}::")
                self.log_code(f"    .incbin \"sound/direct_sound_samples/cries/{audio_name}.bin\"")

                self.log_manual_step(3, f"Add cry constant to include/constants/cries.h")
                self.log("   Add in the enum PokemonCry section, before CRY_COUNT:")
                self.log_code(f"    CRY_{cry_upper},")

                self.log_manual_step(4, f"Add cry to both tables in sound/cry_tables.inc")
                self.log("   Add to the cry table:")
                self.log_code(f"    cry Cry_{cry_title}")
                self.log("   AND add to the cry_reverse table:")
                self.log_code(f"    cry_reverse Cry_{cry_title}")

                self.log_manual_step(5, f"Reference in your Pokemon's species data")
                self.log("   In src/data/pokemon/species_info.h:")
                self.log_code(f"    .cryId = CRY_{cry_upper},")

            elif audio_type == "music":
                # Copy to songs/midi directory
                dest = self.project_root / "sound" / "songs" / "midi" / f"{audio_name}.mid"
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(audio_file, dest)

                self.log_section("✓ AUTOMATED STEPS COMPLETED")
                self.log(f"MIDI file copied to: sound/songs/midi/{audio_name}.mid", "SUCCESS")
                self.log("✓ File organization complete!", "SUCCESS")

                self.log_section("⚠ MANUAL STEPS REQUIRED")
                self.log("The tool CANNOT do these automatically - you must edit code:", "WARNING")

                music_upper = audio_name.upper()

                self.log_manual_step(1, f"Add song to sound/song_table.inc")
                self.log("   Add before the end of the table:")
                self.log_code(f"    song mus_{audio_name}, 0, 0")

                self.log_manual_step(2, f"Add song constant to include/constants/songs.h")
                self.log("   Add in the appropriate section:")
                self.log_code(f"#define MUS_{music_upper}  XXX  // Use next available number")

            else:  # sfx
                # Copy to songs directory
                dest = self.project_root / "sound" / "songs" / f"se_{audio_name}.s"
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(audio_file, dest)

                self.log_section("✓ AUTOMATED STEPS COMPLETED")
                self.log(f"SFX file copied to: sound/songs/se_{audio_name}.s", "SUCCESS")
                self.log("✓ File organization complete!", "SUCCESS")

                self.log_section("⚠ MANUAL STEPS REQUIRED")
                self.log("The tool CANNOT do these automatically - you must edit code:", "WARNING")

                sfx_upper = audio_name.upper()

                self.log_manual_step(1, f"Add sound effect to sound/song_table.inc")
                self.log("   Add in the SE section:")
                self.log_code(f"    song se_{audio_name}, 1, 1")

                self.log_manual_step(2, f"Add SE constant to include/constants/songs.h")
                self.log("   Add in the sound effects section:")
                self.log_code(f"#define SE_{sfx_upper}  XXX  // Use next available number")

            self.log("", "INFO")
            messagebox.showinfo("Success",
                f"✓ FILE COPIED SUCCESSFULLY!\n\n"
                f"⚠ IMPORTANT: Manual steps required!\n"
                f"Check the Operation Log below for detailed steps.\n\n"
                f"Audio files require format conversion and code edits.")

        except Exception as e:
            self.log(f"Error inserting audio file: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert audio file:\n{e}")


def main():
    root = tk.Tk()
    app = FileInserterGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
