#!/usr/bin/env python3
"""
Pokemon Showdown Team Converter
Converts trainers.party format to Pokemon Showdown importable format
"""

import re
import sys
import argparse
from typing import List, Dict, Optional

try:
    import tkinter as tk
    from tkinter import ttk, scrolledtext, messagebox
    TKINTER_AVAILABLE = True
except ImportError:
    TKINTER_AVAILABLE = False


class TrainerParser:
    """Parser for trainers.party file format"""

    # Fields that are trainer metadata and should be excluded from Pokemon export
    TRAINER_FIELDS = {
        'Name:', 'Class:', 'Pic:', 'Gender:', 'Music:', 'Double Battle:',
        'AI:', 'Items:', 'Battle Type:', 'Mugshot:', 'Starting Status:',
        'Party Size:', 'Pool Rules:'
    }

    # Fields that are pokeemerald-expansion specific and should be excluded
    EXPANSION_FIELDS = {
        'Tags:', 'Dynamax Level:', 'Gigantamax:', 'Tera Type:'
    }

    def __init__(self, trainers_party_content: str):
        self.content = trainers_party_content
        self.trainers = self._parse_trainers()

    def _parse_trainers(self) -> Dict[str, Dict]:
        """Parse the trainers.party file and extract all trainers"""
        trainers = {}

        # Split by trainer definitions
        trainer_blocks = re.split(r'^=== (TRAINER_\w+) ===$', self.content, flags=re.MULTILINE)

        # trainer_blocks will be: ['', 'TRAINER_NAME', 'content', 'TRAINER_NAME2', 'content2', ...]
        for i in range(1, len(trainer_blocks), 2):
            if i + 1 < len(trainer_blocks):
                trainer_id = trainer_blocks[i]
                trainer_content = trainer_blocks[i + 1]

                parsed = self._parse_trainer_block(trainer_id, trainer_content)
                if parsed:
                    trainers[trainer_id] = parsed

        return trainers

    def _parse_trainer_block(self, trainer_id: str, content: str) -> Optional[Dict]:
        """Parse a single trainer block"""
        lines = content.strip().split('\n')

        trainer_info = {
            'id': trainer_id,
            'name': '',
            'pokemon': []
        }

        current_pokemon = None
        pokemon_lines = []

        for line in lines:
            line = line.rstrip()

            # Skip empty lines and comments
            if not line or line.startswith('/*') or line.startswith('*/'):
                continue

            # Check if this is a trainer metadata field
            is_trainer_field = any(line.startswith(field) for field in self.TRAINER_FIELDS)

            if is_trainer_field:
                # Extract trainer name
                if line.startswith('Name:'):
                    trainer_info['name'] = line.split(':', 1)[1].strip()
                continue

            # Check if this is the start of a new Pokemon (species line)
            # Species lines don't start with a field indicator and aren't blank
            if not any(line.startswith(field) for field in self.EXPANSION_FIELDS) and \
               not line.startswith(('-', 'Level:', 'Ability:', 'IVs:', 'EVs:',
                                   'Nature:', 'Shiny:', 'Happiness:', 'Ball:')):
                # Save previous Pokemon if exists
                if current_pokemon is not None and pokemon_lines:
                    trainer_info['pokemon'].append('\n'.join(pokemon_lines))

                # Start new Pokemon
                current_pokemon = line
                pokemon_lines = [line]
            else:
                # Continue building current Pokemon
                if current_pokemon is not None:
                    # Skip expansion-specific fields
                    if not any(line.startswith(field) for field in self.EXPANSION_FIELDS):
                        pokemon_lines.append(line)

        # Add the last Pokemon
        if current_pokemon is not None and pokemon_lines:
            trainer_info['pokemon'].append('\n'.join(pokemon_lines))

        return trainer_info if trainer_info['pokemon'] else None

    def get_trainer_list(self) -> List[str]:
        """Get list of all trainer IDs"""
        return sorted(self.trainers.keys())

    def get_trainer_display_name(self, trainer_id: str) -> str:
        """Get display name for a trainer"""
        trainer = self.trainers.get(trainer_id)
        if trainer:
            name = trainer.get('name', '')
            if name:
                return f"{trainer_id} - {name}"
        return trainer_id

    def export_trainer_to_showdown(self, trainer_id: str) -> str:
        """Export a trainer's party to Pokemon Showdown format"""
        trainer = self.trainers.get(trainer_id)
        if not trainer:
            return ""

        output_lines = []

        # Add a comment header
        name = trainer.get('name', trainer_id)
        output_lines.append(f"=== {name} ({trainer_id}) ===")
        output_lines.append("")

        # Export each Pokemon
        for pokemon in trainer['pokemon']:
            output_lines.append(pokemon)
            output_lines.append("")  # Blank line between Pokemon

        return '\n'.join(output_lines)

# GUI class - only available if tkinter is installed
if TKINTER_AVAILABLE:
    class ShowdownConverterGUI:
        """GUI for the Pokemon Showdown converter"""
        
        def __init__(self, root: tk.Tk):
            self.root = root
            self.root.title("Pokemon Showdown Team Converter")
            self.root.geometry("1000x700")
            
            self.parser: Optional[TrainerParser] = None
            self.trainers_party_path = "src/data/trainers.party"
            
            self._create_widgets()
            self._load_trainers_file()
        
        def _create_widgets(self):
            """Create the GUI widgets"""
            # Main container
            main_frame = ttk.Frame(self.root, padding="10")
            main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
            
            self.root.columnconfigure(0, weight=1)
            self.root.rowconfigure(0, weight=1)
            main_frame.columnconfigure(0, weight=1)
            main_frame.rowconfigure(2, weight=1)
            
            # Title
            title_label = ttk.Label(
                main_frame,
                text="Pokemon Showdown Team Converter",
                font=('Helvetica', 16, 'bold')
            )
            title_label.grid(row=0, column=0, pady=(0, 10), sticky=tk.W)
            
            # Instructions
            instructions = (
                "Select a trainer from the list below to convert their party to Pokemon Showdown format.\\n"
                "The converted team can be copied and pasted directly into Pokemon Showdown's team builder."
            )
            instructions_label = ttk.Label(main_frame, text=instructions, wraplength=900)
            instructions_label.grid(row=1, column=0, pady=(0, 10), sticky=tk.W)
            
            # Content frame (split into left and right)
            content_frame = ttk.Frame(main_frame)
            content_frame.grid(row=2, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
            content_frame.columnconfigure(1, weight=1)
            content_frame.rowconfigure(0, weight=1)
            
            # Left panel - Trainer list
            left_panel = ttk.Frame(content_frame)
            left_panel.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(0, 10))
            left_panel.rowconfigure(1, weight=1)
            
            ttk.Label(left_panel, text="Trainers:", font=('Helvetica', 12, 'bold')).grid(
                row=0, column=0, sticky=tk.W, pady=(0, 5)
            )
            
            # Search box
            search_frame = ttk.Frame(left_panel)
            search_frame.grid(row=1, column=0, sticky=(tk.W, tk.E), pady=(0, 5))
            search_frame.columnconfigure(0, weight=1)
            
            ttk.Label(search_frame, text="Search:").grid(row=0, column=0, sticky=tk.W)
            self.search_var = tk.StringVar()
            self.search_var.trace('w', lambda *args: self._filter_trainer_list())
            search_entry = ttk.Entry(search_frame, textvariable=self.search_var)
            search_entry.grid(row=1, column=0, sticky=(tk.W, tk.E), pady=(2, 0))
            
            # Trainer listbox with scrollbar
            list_frame = ttk.Frame(left_panel)
            list_frame.grid(row=2, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
            list_frame.columnconfigure(0, weight=1)
            list_frame.rowconfigure(0, weight=1)
            
            scrollbar = ttk.Scrollbar(list_frame)
            scrollbar.grid(row=0, column=1, sticky=(tk.N, tk.S))
            
            self.trainer_listbox = tk.Listbox(
                list_frame,
                yscrollcommand=scrollbar.set,
                width=40,
                exportselection=False
            )
            self.trainer_listbox.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
            scrollbar.config(command=self.trainer_listbox.yview)
            
            self.trainer_listbox.bind('<<ListboxSelect>>', self._on_trainer_select)
            
            # Right panel - Output
            right_panel = ttk.Frame(content_frame)
            right_panel.grid(row=0, column=1, sticky=(tk.W, tk.E, tk.N, tk.S))
            right_panel.columnconfigure(0, weight=1)
            right_panel.rowconfigure(1, weight=1)
            
            output_header = ttk.Frame(right_panel)
            output_header.grid(row=0, column=0, sticky=(tk.W, tk.E), pady=(0, 5))
            output_header.columnconfigure(0, weight=1)
            
            ttk.Label(output_header, text="Showdown Format:", font=('Helvetica', 12, 'bold')).grid(
                row=0, column=0, sticky=tk.W
            )
            
            copy_button = ttk.Button(
                output_header,
                text="Copy to Clipboard",
                command=self._copy_to_clipboard
            )
            copy_button.grid(row=0, column=1, sticky=tk.E)
            
            # Output text area
            self.output_text = scrolledtext.ScrolledText(
                right_panel,
                wrap=tk.WORD,
                width=60,
                height=20,
                font=('Courier', 10)
            )
            self.output_text.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
            
            # Bottom status bar
            self.status_var = tk.StringVar(value="Ready")
            status_bar = ttk.Label(
                main_frame,
                textvariable=self.status_var,
                relief=tk.SUNKEN,
                anchor=tk.W
            )
            status_bar.grid(row=3, column=0, sticky=(tk.W, tk.E), pady=(10, 0))
        
        def _load_trainers_file(self):
            """Load and parse the trainers.party file"""
            try:
                with open(self.trainers_party_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                self.parser = TrainerParser(content)
                self._populate_trainer_list()
                self.status_var.set(
                    f"Loaded {len(self.parser.trainers)} trainers from {self.trainers_party_path}"
                )
            except FileNotFoundError:
                messagebox.showerror(
                    "File Not Found",
                    f"Could not find {self.trainers_party_path}\\n\\n"
                    "Make sure you're running this from the pokeemerald-expansion root directory."
                )
                self.status_var.set("Error: trainers.party not found")
            except Exception as e:
                messagebox.showerror("Error", f"Failed to load trainers.party: {e}")
                self.status_var.set(f"Error: {e}")
        
        def _populate_trainer_list(self, filter_text: str = ""):
            """Populate the trainer listbox"""
            self.trainer_listbox.delete(0, tk.END)
            
            if not self.parser:
                return
            
            filter_text = filter_text.lower()
            
            for trainer_id in self.parser.get_trainer_list():
                display_name = self.parser.get_trainer_display_name(trainer_id)
                
                if not filter_text or filter_text in display_name.lower():
                    self.trainer_listbox.insert(tk.END, display_name)
        
        def _filter_trainer_list(self):
            """Filter the trainer list based on search text"""
            search_text = self.search_var.get()
            self._populate_trainer_list(search_text)
        
        def _on_trainer_select(self, event):
            """Handle trainer selection"""
            selection = self.trainer_listbox.curselection()
            if not selection:
                return
            
            display_name = self.trainer_listbox.get(selection[0])
            # Extract trainer ID from display name
            trainer_id = display_name.split(' - ')[0]
            
            if self.parser:
                showdown_format = self.parser.export_trainer_to_showdown(trainer_id)
                self.output_text.delete('1.0', tk.END)
                self.output_text.insert('1.0', showdown_format)
                self.status_var.set(f"Converted {trainer_id}")
        
        def _copy_to_clipboard(self):
            """Copy the output to clipboard"""
            output = self.output_text.get('1.0', tk.END).strip()
            if output:
                self.root.clipboard_clear()
                self.root.clipboard_append(output)
                self.status_var.set("Copied to clipboard!")
                messagebox.showinfo("Success", "Team copied to clipboard!")
            else:
                messagebox.showwarning("No Content", "No team to copy. Please select a trainer first.")


def main_cli():
    """Command-line interface"""
    parser = argparse.ArgumentParser(
        description='Convert Pokemon trainers.party format to Pokemon Showdown format'
    )
    parser.add_argument(
        'trainer_id',
        nargs='?',
        help='Trainer ID to convert (e.g., TRAINER_ROXANNE_1)'
    )
    parser.add_argument(
        '--file',
        default='src/data/trainers.party',
        help='Path to trainers.party file (default: src/data/trainers.party)'
    )
    parser.add_argument(
        '--list',
        action='store_true',
        help='List all available trainers'
    )
    parser.add_argument(
        '--gui',
        action='store_true',
        help='Launch GUI interface'
    )
    parser.add_argument(
        '--search',
        help='Search for trainers matching a pattern'
    )
    
    args = parser.parse_args()
    
    # Load trainers file
    try:
        with open(args.file, 'r', encoding='utf-8') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Error: Could not find {args.file}", file=sys.stderr)
        print("Make sure you're running this from the pokeemerald-expansion root directory.", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"Error loading file: {e}", file=sys.stderr)
        return 1
    
    trainer_parser = TrainerParser(content)
    
    # List trainers
    if args.list:
        print(f"Found {len(trainer_parser.trainers)} trainers:")
        for trainer_id in trainer_parser.get_trainer_list():
            display_name = trainer_parser.get_trainer_display_name(trainer_id)
            print(f"  {display_name}")
        return 0
    
    # Search trainers
    if args.search:
        search_term = args.search.lower()
        matching = [
            tid for tid in trainer_parser.get_trainer_list()
            if search_term in trainer_parser.get_trainer_display_name(tid).lower()
        ]
        print(f"Found {len(matching)} trainers matching '{args.search}':")
        for trainer_id in matching:
            display_name = trainer_parser.get_trainer_display_name(trainer_id)
            print(f"  {display_name}")
        return 0
    
    # GUI mode
    if args.gui:
        if not TKINTER_AVAILABLE:
            print("Error: tkinter is not available. Cannot launch GUI.", file=sys.stderr)
            print("Use command-line mode instead (see --help for options)", file=sys.stderr)
            return 1
        root = tk.Tk()
        app = ShowdownConverterGUI(root)
        root.mainloop()
        return 0
    
    # Convert specific trainer
    if args.trainer_id:
        if args.trainer_id not in trainer_parser.trainers:
            print(f"Error: Trainer '{args.trainer_id}' not found", file=sys.stderr)
            print("Use --list to see all available trainers", file=sys.stderr)
            return 1
        
        output = trainer_parser.export_trainer_to_showdown(args.trainer_id)
        print(output)
        return 0
    
    # No action specified - try GUI, fall back to help
    if TKINTER_AVAILABLE:
        root = tk.Tk()
        app = ShowdownConverterGUI(root)
        root.mainloop()
        return 0
    else:
        print("GUI not available. Use --help to see command-line options.", file=sys.stderr)
        parser.print_help()
        return 1


if __name__ == "__main__":
    sys.exit(main_cli())
