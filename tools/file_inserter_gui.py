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
        self.log_text.tag_config("success", foreground="green")
        self.log_text.tag_config("warning", foreground="orange")
        self.log_text.tag_config("error", foreground="red")

        self.log_text.insert(tk.END, f"[{level}] {message}\n", color_tag)
        self.log_text.see(tk.END)
        self.log_text.config(state=tk.DISABLED)

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

            self.log(f"Pokemon graphics inserted successfully to: {pokemon_dir}", "SUCCESS")
            self.log("NEXT STEPS:", "INFO")
            self.log("1. Add species constant to include/constants/species.h", "INFO")
            self.log("2. Add species data to src/data/pokemon/species_info.h", "INFO")
            self.log("3. Add graphics references to src/data/graphics/pokemon.h", "INFO")
            self.log("See docs/tutorials/how_to_new_pokemon.md for details", "INFO")

            messagebox.showinfo("Success", f"Pokemon graphics inserted!\n\nLocation: {pokemon_dir}\n\nCheck the log for next steps.")

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

            self.log("Trainer graphics inserted successfully!", "SUCCESS")
            self.log("NEXT STEPS:", "INFO")
            self.log("1. Add graphics references to src/data/graphics/trainers.h", "INFO")
            self.log("2. Add trainer sprite entry to src/data/graphics/trainers.h", "INFO")
            self.log("3. Add TRAINER_PIC constant to include/constants/trainers.h", "INFO")
            self.log("See docs/tutorials/how_to_trainer_front_pic.md for details", "INFO")

            messagebox.showinfo("Success", "Trainer graphics inserted!\n\nCheck the log for next steps.")

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

            self.log("Item graphics inserted successfully!", "SUCCESS")
            self.log("NEXT STEPS:", "INFO")
            self.log("1. Add item constant to include/constants/items.h", "INFO")
            self.log("2. Add item data to src/data/items.h", "INFO")
            self.log("3. Add graphics references to src/data/graphics/items.h", "INFO")

            messagebox.showinfo("Success", "Item graphics inserted!\n\nCheck the log for next steps.")

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

            self.log("Overworld sprite inserted successfully!", "SUCCESS")
            self.log("NEXT STEPS:", "INFO")
            self.log("1. Add sprite references to src/data/object_events/object_event_graphics.h", "INFO")
            self.log(f"2. Add build rule to spritesheet_rules.mk with -mwidth {width} -mheight {height}", "INFO")
            self.log("3. Add pic table to src/data/object_events/object_event_pic_tables.h", "INFO")
            self.log("4. Add graphics info to src/data/object_events/object_event_graphics_info.h", "INFO")
            self.log("5. Add constant to include/constants/event_objects.h", "INFO")

            messagebox.showinfo("Success", "Overworld sprite inserted!\n\nCheck the log for next steps.")

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
                self.log(f"Copied cry file to {dest}", "SUCCESS")

                self.log("NEXT STEPS:", "INFO")
                self.log(f"1. Convert to AIF: ffmpeg -i {dest} -c:a pcm_s8 -ac 1 -ar 13379 sound/direct_sound_samples/cries/{audio_name}.aif", "INFO")
                self.log("2. Add cry to sound/direct_sound_data.inc", "INFO")
                self.log("3. Add cry ID to include/constants/cries.h", "INFO")
                self.log("4. Add cry to sound/cry_tables.inc", "INFO")

            elif audio_type == "music":
                # Copy to songs/midi directory
                dest = self.project_root / "sound" / "songs" / "midi" / f"{audio_name}.mid"
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(audio_file, dest)
                self.log(f"Copied MIDI file to {dest}", "SUCCESS")

                self.log("NEXT STEPS:", "INFO")
                self.log("1. Add song to sound/song_table.inc", "INFO")
                self.log("2. Add song constant to include/constants/songs.h", "INFO")

            else:  # sfx
                # Copy to songs directory
                dest = self.project_root / "sound" / "songs" / f"se_{audio_name}.s"
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(audio_file, dest)
                self.log(f"Copied SFX file to {dest}", "SUCCESS")

                self.log("NEXT STEPS:", "INFO")
                self.log("1. Add sound effect to sound/song_table.inc", "INFO")
                self.log("2. Add SE constant to include/constants/songs.h", "INFO")

            self.log("Audio file inserted successfully!", "SUCCESS")
            messagebox.showinfo("Success", "Audio file inserted!\n\nCheck the log for next steps.")

        except Exception as e:
            self.log(f"Error inserting audio file: {e}", "ERROR")
            messagebox.showerror("Error", f"Failed to insert audio file:\n{e}")


def main():
    root = tk.Tk()
    app = FileInserterGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
