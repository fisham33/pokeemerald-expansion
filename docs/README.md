# Pokemon Stat Filter - Web Version

A web-based Pokemon filtering tool that can be hosted on GitHub Pages.

## Features

- Filter Pokemon by:
  - Generation (1-9)
  - Type (Fire, Dragon, etc.)
  - Ability (Intimidate, Levitate, etc.)
  - Base Stat Total (BST) range
  - Individual stat ranges (HP, Attack, Defense, Sp. Atk, Sp. Def, Speed)

- Beautiful, responsive design
- Fast client-side filtering
- No backend required

## Local Development

1. Copy `pokemon_data.json` to this directory:
   ```bash
   cp ../pokemon_data.json .
   ```

2. Start a local web server:
   ```bash
   # Python 3
   python3 -m http.server 8000

   # Python 2
   python -m SimpleHTTPServer 8000

   # Node.js
   npx http-server
   ```

3. Open http://localhost:8000 in your browser

## GitHub Pages Deployment

1. Ensure `pokemon_data.json` is in this directory

2. Push to GitHub

3. Enable GitHub Pages in repository settings:
   - Go to Settings → Pages
   - Source: Deploy from a branch
   - Branch: main (or your branch name)
   - Folder: /tools/trainer_gen/web

4. Your site will be available at:
   `https://<username>.github.io/<repository>/tools/trainer_gen/web/`

## File Structure

```
web/
├── index.html          # Main HTML page
├── styles.css          # Styles and theming
├── filter.js           # Filtering logic
├── pokemon_data.json   # Pokemon database (needs to be copied)
└── README.md           # This file
```

## Usage

1. **Basic Filtering:**
   - Enter values in any filter fields
   - Click "Filter" to apply filters
   - Results update instantly

2. **Type Filtering:**
   - Enter comma-separated types: `Fire, Dragon`
   - Matches Pokemon with ANY of the specified types

3. **Ability Filtering:**
   - Enter ability name (partial match works)
   - Searches both normal and hidden abilities

4. **Stat Ranges:**
   - Leave fields empty to skip that filter
   - Enter only min or only max as needed
   - Combine multiple stat filters

5. **Buttons:**
   - **Filter** - Apply current filter criteria
   - **Clear** - Reset all filters
   - **Show All** - Display all Pokemon

## Examples

- Gen 9 Pokemon: Set Generation to `9`
- Fire types: Set Types to `Fire`
- Intimidate users: Set Ability to `Intimidate`
- BST 500-600: Set Min BST to `500`, Max BST to `600`
- Fast attackers: Set Min Speed to `100`, Min Attack to `100`

## Browser Compatibility

- Chrome/Edge: ✅ Fully supported
- Firefox: ✅ Fully supported
- Safari: ✅ Fully supported
- Mobile browsers: ✅ Responsive design

## License

This tool uses data from pokeemerald-expansion. See the main repository for license information.
