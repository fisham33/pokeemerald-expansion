#!/usr/bin/env python3
"""
GUI for Pokemon Stat Filter Tool
"""

import tkinter as tk
from tkinter import ttk, scrolledtext
import json
from pathlib import Path
import sys

# Add parent directory to path to import filter_pokemon
sys.path.insert(0, str(Path(__file__).parent))
from filter_pokemon import filter_pokemon


class FilterGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Pokemon Stat Filter")
        self.root.geometry("900x700")

        # Load Pokemon data
        self.pokemon_data = None
        self.load_data()

        # Create UI
        self.create_widgets()

    def load_data(self):
        """Load Pokemon data from JSON file"""
        data_file = Path(__file__).parent / 'pokemon_data.json'
        if not data_file.exists():
            tk.messagebox.showerror("Error", f"Pokemon data not found at {data_file}\n\nPlease run 'python3 extract_pokemon_data.py' first.")
            return

        with open(data_file, 'r') as f:
            self.pokemon_data = json.load(f)

    def create_widgets(self):
        """Create all GUI widgets"""
        # Main container
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)

        # Title
        title_label = ttk.Label(main_frame, text="Pokemon Stat Filter",
                               font=('Arial', 16, 'bold'))
        title_label.grid(row=0, column=0, columnspan=4, pady=10)

        # Filters Frame
        filters_frame = ttk.LabelFrame(main_frame, text="Filters", padding="10")
        filters_frame.grid(row=1, column=0, columnspan=4, sticky=(tk.W, tk.E), pady=5)

        row = 0

        # Generation filter
        ttk.Label(filters_frame, text="Generation:").grid(row=row, column=0, sticky=tk.W, padx=5, pady=3)
        self.gen_var = tk.StringVar()
        gen_entry = ttk.Entry(filters_frame, textvariable=self.gen_var, width=10)
        gen_entry.grid(row=row, column=1, sticky=tk.W, padx=5, pady=3)
        ttk.Label(filters_frame, text="(1-9)").grid(row=row, column=2, sticky=tk.W, padx=5, pady=3)
        row += 1

        # Type filter
        ttk.Label(filters_frame, text="Type(s):").grid(row=row, column=0, sticky=tk.W, padx=5, pady=3)
        self.type_var = tk.StringVar()
        type_entry = ttk.Entry(filters_frame, textvariable=self.type_var, width=30)
        type_entry.grid(row=row, column=1, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=3)
        ttk.Label(filters_frame, text="(comma-separated: Fire, Dragon)").grid(row=row, column=3, sticky=tk.W, padx=5, pady=3)
        row += 1

        # Ability filter
        ttk.Label(filters_frame, text="Ability:").grid(row=row, column=0, sticky=tk.W, padx=5, pady=3)
        self.ability_var = tk.StringVar()
        ability_entry = ttk.Entry(filters_frame, textvariable=self.ability_var, width=30)
        ability_entry.grid(row=row, column=1, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=3)
        ttk.Label(filters_frame, text="(partial match)").grid(row=row, column=3, sticky=tk.W, padx=5, pady=3)
        row += 1

        # BST Range
        ttk.Label(filters_frame, text="BST Range:").grid(row=row, column=0, sticky=tk.W, padx=5, pady=3)
        bst_frame = ttk.Frame(filters_frame)
        bst_frame.grid(row=row, column=1, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=3)

        self.min_bst_var = tk.StringVar()
        ttk.Label(bst_frame, text="Min:").pack(side=tk.LEFT, padx=2)
        ttk.Entry(bst_frame, textvariable=self.min_bst_var, width=8).pack(side=tk.LEFT, padx=2)
        ttk.Label(bst_frame, text="Max:").pack(side=tk.LEFT, padx=2)
        self.max_bst_var = tk.StringVar()
        ttk.Entry(bst_frame, textvariable=self.max_bst_var, width=8).pack(side=tk.LEFT, padx=2)
        row += 1

        # Individual stat ranges
        stats = [
            ('HP', 'hp'),
            ('Attack', 'atk'),
            ('Defense', 'def'),
            ('Sp. Atk', 'spa'),
            ('Sp. Def', 'spd'),
            ('Speed', 'spe')
        ]

        self.stat_vars = {}
        for stat_label, stat_key in stats:
            ttk.Label(filters_frame, text=f"{stat_label}:").grid(row=row, column=0, sticky=tk.W, padx=5, pady=3)
            stat_frame = ttk.Frame(filters_frame)
            stat_frame.grid(row=row, column=1, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=3)

            min_var = tk.StringVar()
            max_var = tk.StringVar()
            self.stat_vars[f'min_{stat_key}'] = min_var
            self.stat_vars[f'max_{stat_key}'] = max_var

            ttk.Label(stat_frame, text="Min:").pack(side=tk.LEFT, padx=2)
            ttk.Entry(stat_frame, textvariable=min_var, width=8).pack(side=tk.LEFT, padx=2)
            ttk.Label(stat_frame, text="Max:").pack(side=tk.LEFT, padx=2)
            ttk.Entry(stat_frame, textvariable=max_var, width=8).pack(side=tk.LEFT, padx=2)
            row += 1

        # Buttons
        button_frame = ttk.Frame(main_frame)
        button_frame.grid(row=2, column=0, columnspan=4, pady=10)

        self.filter_btn = ttk.Button(button_frame, text="Filter", command=self.apply_filter,
                                     style='Accent.TButton')
        self.filter_btn.pack(side=tk.LEFT, padx=5)

        ttk.Button(button_frame, text="Clear", command=self.clear_filters).pack(side=tk.LEFT, padx=5)
        ttk.Button(button_frame, text="Show All", command=self.show_all).pack(side=tk.LEFT, padx=5)

        # Results Frame
        results_frame = ttk.LabelFrame(main_frame, text="Results", padding="5")
        results_frame.grid(row=3, column=0, columnspan=4, sticky=(tk.W, tk.E, tk.N, tk.S), pady=5)
        results_frame.columnconfigure(0, weight=1)
        results_frame.rowconfigure(0, weight=1)
        main_frame.rowconfigure(3, weight=1)

        # Results text area with scrollbar
        self.results_text = scrolledtext.ScrolledText(results_frame, wrap=tk.WORD,
                                                      height=20, font=('Courier', 9))
        self.results_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        # Status bar
        self.status_var = tk.StringVar(value="Ready")
        status_bar = ttk.Label(main_frame, textvariable=self.status_var, relief=tk.SUNKEN)
        status_bar.grid(row=4, column=0, columnspan=4, sticky=(tk.W, tk.E))

    def get_int_value(self, var):
        """Get integer value from StringVar, return None if empty or invalid"""
        val = var.get().strip()
        if not val:
            return None
        try:
            return int(val)
        except ValueError:
            return None

    def apply_filter(self):
        """Apply filters and display results"""
        if not self.pokemon_data:
            self.results_text.delete(1.0, tk.END)
            self.results_text.insert(1.0, "Error: Pokemon data not loaded.")
            return

        # Parse generation
        generation = self.get_int_value(self.gen_var)

        # Parse types
        types_str = self.type_var.get().strip()
        types = [t.strip() for t in types_str.split(',')] if types_str else None

        # Parse ability
        ability = self.ability_var.get().strip() if self.ability_var.get().strip() else None

        # Parse BST range
        min_bst = self.get_int_value(self.min_bst_var)
        max_bst = self.get_int_value(self.max_bst_var)

        # Parse stat ranges
        stat_filters = {}
        for key, var in self.stat_vars.items():
            val = self.get_int_value(var)
            if val is not None:
                stat_filters[key] = val

        # Call filter function
        try:
            results = filter_pokemon(
                self.pokemon_data,
                generation=generation,
                types=types,
                ability=ability,
                min_bst=min_bst,
                max_bst=max_bst,
                **stat_filters
            )

            # Display results
            self.display_results(results)
            self.status_var.set(f"Found {len(results)} Pokemon")

        except Exception as e:
            self.results_text.delete(1.0, tk.END)
            self.results_text.insert(1.0, f"Error: {str(e)}")
            self.status_var.set("Error occurred")

    def display_results(self, results):
        """Display filtered Pokemon results"""
        self.results_text.delete(1.0, tk.END)

        if not results:
            self.results_text.insert(1.0, "No Pokemon found matching the criteria.")
            return

        output = []
        output.append("=" * 80)
        output.append(f"Found {len(results)} Pokemon")
        output.append("=" * 80)
        output.append("")

        for i, pokemon in enumerate(results, 1):
            stats = pokemon.get('baseStats', {})
            bst = pokemon.get('bst', 0)
            gen = pokemon.get('generation', 0)
            types = pokemon.get('types', [])
            types_str = '/'.join(types) if types else 'Unknown'
            abilities = pokemon.get('abilities', [])
            hidden = pokemon.get('hiddenAbility', '')

            output.append(f"{i:3d}. {pokemon['name']:<25} ({pokemon['species']})")
            output.append(f"     Gen: {gen}  Types: {types_str:<20} BST: {bst}")
            output.append(f"     HP: {stats.get('hp', 0):3d}  Atk: {stats.get('atk', 0):3d}  Def: {stats.get('def', 0):3d}  "
                         f"SpA: {stats.get('spa', 0):3d}  SpD: {stats.get('spd', 0):3d}  Spe: {stats.get('spe', 0):3d}")

            # Show abilities
            abilities_str = ', '.join(abilities) if abilities else 'None'
            if hidden:
                abilities_str += f" (Hidden: {hidden})"
            output.append(f"     Abilities: {abilities_str}")
            output.append("")

        self.results_text.insert(1.0, '\n'.join(output))

    def clear_filters(self):
        """Clear all filter inputs"""
        self.gen_var.set('')
        self.type_var.set('')
        self.ability_var.set('')
        self.min_bst_var.set('')
        self.max_bst_var.set('')

        for var in self.stat_vars.values():
            var.set('')

        self.results_text.delete(1.0, tk.END)
        self.status_var.set("Filters cleared")

    def show_all(self):
        """Show all Pokemon (no filters)"""
        self.clear_filters()

        if not self.pokemon_data:
            return

        results = self.pokemon_data['pokemon']
        self.display_results(results)
        self.status_var.set(f"Showing all {len(results)} Pokemon")


def main():
    root = tk.Tk()
    app = FilterGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
