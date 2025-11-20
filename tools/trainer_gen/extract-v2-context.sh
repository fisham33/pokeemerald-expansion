#!/bin/bash
# Extract context files for V2 rebuild prompt

OUTPUT="v2-context.txt"

echo "Extracting context files for V2 rebuild..."

{
  echo "=========================================="
  echo "POKEMON DATA STRUCTURE (first 100 lines)"
  echo "=========================================="
  head -100 ../tools/trainer_gen/pokemon_data.json
  echo ""
  echo ""

  echo "=========================================="
  echo "MOVE DATA STRUCTURE (first 100 lines)"
  echo "=========================================="
  head -100 ../tools/trainer_gen/move_data.json
  echo ""
  echo ""

  echo "=========================================="
  echo "CURRENT FILTER LOGIC (filterPokemon function)"
  echo "=========================================="
  sed -n '103,157p' ../tools/trainer_gen/web/filter.js
  echo ""
  echo ""

  echo "=========================================="
  echo "HTML STRUCTURE"
  echo "=========================================="
  cat ../tools/trainer_gen/web/index.html
  echo ""
  echo ""

  echo "=========================================="
  echo "STYLES (complete CSS)"
  echo "=========================================="
  cat ../tools/trainer_gen/web/styles.css
  echo ""

} > "$OUTPUT"

echo ""
echo "✓ Context extracted to: $OUTPUT"
echo "  File size: $(wc -c < $OUTPUT | numfmt --to=iec-i --suffix=B --format="%.1f")"
echo "  Lines: $(wc -l < $OUTPUT)"
echo ""
echo "Next steps:"
echo "  1. Review: cat $OUTPUT"
echo "  2. Provide this file + docs/REBUILD_PROMPT_V2.md to AI"
echo "  3. AI will build the modular V2 application"
echo ""
