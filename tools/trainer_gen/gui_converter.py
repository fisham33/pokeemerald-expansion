#!/usr/bin/env python3
"""
GUI for Pokemon Showdown Random Battle to trainers.party Converter
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import json
import os
import subprocess
import threading
from pathlib import Path


class ConverterGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Pokemon Movesets Converter - GUI")
        self.root.geometry("900x700")

        # Variables
        self.input_files_var = tk.StringVar(value="All available files")
        self.mode_var = tk.StringVar(value="pool")
        self.archetype_var = tk.StringVar(value="")
        self.output_file_var = tk.StringVar(value="converted_movesets.txt")
        self.pool_size_var = tk.IntVar(value=8)
        self.party_size_var = tk.IntVar(value=4)
        self.split_output_var = tk.BooleanVar(value=False)

        # Load available trainer archetypes
        self.trainer_archetypes = self.load_trainer_archetypes()

        self.create_widgets()

    def load_trainer_archetypes(self):
        """Load trainer archetypes from JSON file"""
        try:
            archetypes_path = Path(__file__).parent / 'trainer_archetypes.json'
            if archetypes_path.exists():
                with open(archetypes_path, 'r') as f:
                    data = json.load(f)
                    return list(data.get('archetypes', {}).keys())
        except Exception as e:
            print(f"Could not load trainer archetypes: {e}")
        return []

    def create_widgets(self):
        # Main container
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(0, weight=1)
        main_frame.rowconfigure(7, weight=1)

        # Title
        title_label = ttk.Label(main_frame, text="Pokemon Movesets Converter",
                               font=('Arial', 16, 'bold'))
        title_label.grid(row=0, column=0, columnspan=2, pady=10)

        # Input Files Section
        input_frame = ttk.LabelFrame(main_frame, text="Input Files", padding="10")
        input_frame.grid(row=1, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=5)
        input_frame.columnconfigure(1, weight=1)

        ttk.Label(input_frame, text="JSON Files:").grid(row=0, column=0, sticky=tk.W, padx=5)
        self.input_files_entry = ttk.Entry(input_frame, textvariable=self.input_files_var)
        self.input_files_entry.grid(row=0, column=1, sticky=(tk.W, tk.E), padx=5)
        ttk.Button(input_frame, text="Select Files", command=self.select_input_files).grid(
            row=0, column=2, padx=5)

        ttk.Label(input_frame, text="Available: gen9randomdoublesbattle.json, gen9randombattle.json, gen9babyrandombattle.json",
                 font=('Arial', 8), foreground='gray').grid(row=1, column=0, columnspan=3, sticky=tk.W, padx=5)

        # Conversion Mode Section
        mode_frame = ttk.LabelFrame(main_frame, text="Conversion Mode", padding="10")
        mode_frame.grid(row=2, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=5)

        modes = [
            ("Single entry per Pokemon (Basic)", "single"),
            ("All roles (Complete Sets)", "all-roles"),
            ("Pool format with tags (Recommended)", "pool"),
            ("Complete trainer pool (Auto-Generated)", "trainer-pool")
        ]

        for idx, (text, value) in enumerate(modes):
            ttk.Radiobutton(mode_frame, text=text, variable=self.mode_var,
                          value=value).grid(row=idx, column=0, sticky=tk.W, padx=5)

        # Archetype Filtering Section
        archetype_frame = ttk.LabelFrame(main_frame, text="Archetype Filtering (Optional)", padding="10")
        archetype_frame.grid(row=3, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=5)
        archetype_frame.columnconfigure(1, weight=1)

        ttk.Label(archetype_frame, text="Filter by:").grid(row=0, column=0, sticky=tk.W, padx=5)

        # Archetype type selection
        archetype_type_frame = ttk.Frame(archetype_frame)
        archetype_type_frame.grid(row=0, column=1, sticky=(tk.W, tk.E), padx=5)

        self.archetype_type_var = tk.StringVar(value="none")
        ttk.Radiobutton(archetype_type_frame, text="None", variable=self.archetype_type_var,
                       value="none", command=self.on_archetype_type_change).pack(side=tk.LEFT, padx=5)
        ttk.Radiobutton(archetype_type_frame, text="Types", variable=self.archetype_type_var,
                       value="types", command=self.on_archetype_type_change).pack(side=tk.LEFT, padx=5)
        ttk.Radiobutton(archetype_type_frame, text="Trainer Class", variable=self.archetype_type_var,
                       value="class", command=self.on_archetype_type_change).pack(side=tk.LEFT, padx=5)

        # Archetype input
        self.archetype_entry = ttk.Entry(archetype_frame, textvariable=self.archetype_var, state='disabled')
        self.archetype_entry.grid(row=1, column=0, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=5)

        # Archetype combobox for trainer classes
        self.archetype_combo = ttk.Combobox(archetype_frame, textvariable=self.archetype_var,
                                           values=self.trainer_archetypes, state='disabled')
        self.archetype_combo.grid(row=1, column=0, columnspan=2, sticky=(tk.W, tk.E), padx=5, pady=5)
        self.archetype_combo.grid_remove()

        ttk.Label(archetype_frame, text="Examples: Water,Electric or Fire,Ground,Rock",
                 font=('Arial', 8), foreground='gray').grid(row=2, column=0, columnspan=2, sticky=tk.W, padx=5)

        # Pool/Party Size Section
        size_frame = ttk.LabelFrame(main_frame, text="Pool Settings (for trainer-pool mode)", padding="10")
        size_frame.grid(row=4, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=5)

        ttk.Label(size_frame, text="Pool Size:").grid(row=0, column=0, sticky=tk.W, padx=5)
        pool_size_spin = ttk.Spinbox(size_frame, from_=4, to=20, textvariable=self.pool_size_var, width=10)
        pool_size_spin.grid(row=0, column=1, sticky=tk.W, padx=5)

        ttk.Label(size_frame, text="Party Size:").grid(row=0, column=2, sticky=tk.W, padx=20)
        party_size_spin = ttk.Spinbox(size_frame, from_=1, to=6, textvariable=self.party_size_var, width=10)
        party_size_spin.grid(row=0, column=3, sticky=tk.W, padx=5)

        # Output Options Section
        output_frame = ttk.LabelFrame(main_frame, text="Output Options", padding="10")
        output_frame.grid(row=5, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=5)
        output_frame.columnconfigure(1, weight=1)

        ttk.Label(output_frame, text="Output File:").grid(row=0, column=0, sticky=tk.W, padx=5)
        ttk.Entry(output_frame, textvariable=self.output_file_var).grid(
            row=0, column=1, sticky=(tk.W, tk.E), padx=5)
        ttk.Button(output_frame, text="Browse", command=self.select_output_file).grid(
            row=0, column=2, padx=5)

        ttk.Checkbutton(output_frame, text="Split output into separate files by format",
                       variable=self.split_output_var).grid(row=1, column=0, columnspan=3, sticky=tk.W, padx=5, pady=5)

        # Convert Button
        button_frame = ttk.Frame(main_frame)
        button_frame.grid(row=6, column=0, columnspan=2, pady=10)

        self.convert_btn = ttk.Button(button_frame, text="Convert", command=self.convert,
                                     style='Accent.TButton')
        self.convert_btn.pack(side=tk.LEFT, padx=5)

        ttk.Button(button_frame, text="Clear Output", command=self.clear_output).pack(side=tk.LEFT, padx=5)
        ttk.Button(button_frame, text="Open Output Folder", command=self.open_output_folder).pack(side=tk.LEFT, padx=5)

        # Output Text Area
        output_text_frame = ttk.LabelFrame(main_frame, text="Output / Progress", padding="5")
        output_text_frame.grid(row=7, column=0, columnspan=2, sticky=(tk.W, tk.E, tk.N, tk.S), pady=5)
        output_text_frame.columnconfigure(0, weight=1)
        output_text_frame.rowconfigure(0, weight=1)

        self.output_text = scrolledtext.ScrolledText(output_text_frame, wrap=tk.WORD,
                                                     height=15, font=('Courier', 9))
        self.output_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        # Status Bar
        self.status_var = tk.StringVar(value="Ready")
        status_bar = ttk.Label(main_frame, textvariable=self.status_var, relief=tk.SUNKEN, anchor=tk.W)
        status_bar.grid(row=8, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=(5, 0))

    def on_archetype_type_change(self):
        """Handle archetype type change"""
        arch_type = self.archetype_type_var.get()

        if arch_type == "none":
            self.archetype_entry.config(state='disabled')
            self.archetype_combo.grid_remove()
            self.archetype_entry.grid()
            self.archetype_var.set("")
        elif arch_type == "types":
            self.archetype_entry.config(state='normal')
            self.archetype_combo.grid_remove()
            self.archetype_entry.grid()
            self.archetype_var.set("")
        elif arch_type == "class":
            self.archetype_entry.grid_remove()
            self.archetype_combo.grid()
            self.archetype_combo.config(state='readonly')
            if self.trainer_archetypes:
                self.archetype_var.set(self.trainer_archetypes[0])

    def select_input_files(self):
        """Open file dialog to select input JSON files"""
        files = filedialog.askopenfilenames(
            title="Select JSON Files",
            filetypes=[("JSON files", "*.json"), ("All files", "*.*")],
            initialdir=Path(__file__).parent
        )

        if files:
            # Extract just the filenames
            filenames = [os.path.basename(f) for f in files]
            self.input_files_var.set(",".join(filenames))

    def select_output_file(self):
        """Open file dialog to select output file"""
        file = filedialog.asksaveasfilename(
            title="Select Output File",
            defaultextension=".txt",
            filetypes=[("Text files", "*.txt"), ("All files", "*.*")],
            initialdir=Path(__file__).parent,
            initialfile=self.output_file_var.get()
        )

        if file:
            self.output_file_var.set(file)

    def open_output_folder(self):
        """Open the output folder in file explorer"""
        output_dir = Path(__file__).parent

        # Open folder based on OS
        import platform
        system = platform.system()

        try:
            if system == "Windows":
                os.startfile(output_dir)
            elif system == "Darwin":  # macOS
                subprocess.run(["open", output_dir])
            else:  # Linux and others
                subprocess.run(["xdg-open", output_dir])
        except Exception as e:
            messagebox.showerror("Error", f"Could not open folder: {e}")

    def clear_output(self):
        """Clear the output text area"""
        self.output_text.delete(1.0, tk.END)

    def log_output(self, text):
        """Append text to output area"""
        self.output_text.insert(tk.END, text + "\n")
        self.output_text.see(tk.END)
        self.output_text.update()

    def convert(self):
        """Run the conversion"""
        # Disable convert button
        self.convert_btn.config(state='disabled')
        self.status_var.set("Converting...")
        self.clear_output()

        # Run conversion in a thread to keep GUI responsive
        thread = threading.Thread(target=self._run_conversion)
        thread.daemon = True
        thread.start()

    def _run_conversion(self):
        """Run the actual conversion (runs in separate thread)"""
        try:
            # Build command
            script_path = Path(__file__).parent / "convert_randbats_to_party.py"
            cmd = ["python3", str(script_path)]

            # Add mode
            cmd.extend(["--mode", self.mode_var.get()])

            # Add input files if specified
            input_files = self.input_files_var.get()
            if input_files and input_files != "All available files":
                cmd.extend(["--input", input_files])

            # Add archetype if specified
            archetype_type = self.archetype_type_var.get()
            if archetype_type != "none":
                archetype = self.archetype_var.get().strip()
                if archetype:
                    cmd.extend(["--archetype", archetype])

            # Add output file
            cmd.extend(["--output", self.output_file_var.get()])

            # Add pool/party size for trainer-pool mode
            if self.mode_var.get() == "trainer-pool":
                cmd.extend(["--pool-size", str(self.pool_size_var.get())])
                cmd.extend(["--party-size", str(self.party_size_var.get())])

            # Add split output option
            if self.split_output_var.get():
                cmd.append("--split-output")

            # Log command
            self.log_output(f"Running command: {' '.join(cmd)}\n")
            self.log_output("=" * 70)

            # Run the command
            process = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                cwd=Path(__file__).parent
            )

            # Stream output
            for line in process.stdout:
                self.log_output(line.rstrip())

            process.wait()

            if process.returncode == 0:
                self.log_output("\n" + "=" * 70)
                self.log_output("✓ Conversion completed successfully!")
                self.status_var.set("Conversion completed!")
                self.root.after(100, lambda: messagebox.showinfo(
                    "Success",
                    "Conversion completed successfully!\n\nCheck the output file(s) in the trainer_gen folder."
                ))
            else:
                self.log_output("\n" + "=" * 70)
                self.log_output("✗ Conversion failed!")
                self.status_var.set("Conversion failed!")
                self.root.after(100, lambda: messagebox.showerror(
                    "Error",
                    "Conversion failed! Check the output for details."
                ))

        except Exception as e:
            error_msg = f"Error during conversion: {e}"
            self.log_output(error_msg)
            self.status_var.set("Error occurred!")
            self.root.after(100, lambda: messagebox.showerror("Error", error_msg))

        finally:
            # Re-enable convert button
            self.root.after(100, lambda: self.convert_btn.config(state='normal'))
            if self.status_var.get().startswith("Converting"):
                self.status_var.set("Ready")


def main():
    """Main entry point"""
    root = tk.Tk()

    # Try to set a nice theme
    try:
        style = ttk.Style()
        available_themes = style.theme_names()

        # Prefer these themes in order
        preferred_themes = ['arc', 'clam', 'alt', 'default']
        for theme in preferred_themes:
            if theme in available_themes:
                style.theme_use(theme)
                break
    except:
        pass

    app = ConverterGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
