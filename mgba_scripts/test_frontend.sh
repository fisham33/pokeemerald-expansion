#!/bin/bash
# Test the frontend with sample data

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "=== Pokemon Tracker Frontend Test ==="
echo ""
echo "This script will:"
echo "1. Copy sample data to tracker_data.json"
echo "2. Start a local web server"
echo "3. Open the tracker in your browser"
echo ""

# Copy sample data
if [ -f "$SCRIPT_DIR/tracker_data_sample.json" ]; then
    cp "$SCRIPT_DIR/tracker_data_sample.json" "$SCRIPT_DIR/tracker_data.json"
    echo "✓ Sample data copied"
else
    echo "✗ Error: tracker_data_sample.json not found"
    exit 1
fi

# Check for Python
if command -v python3 &> /dev/null; then
    PYTHON=python3
elif command -v python &> /dev/null; then
    PYTHON=python
else
    echo "✗ Python not found. Please install Python to run the test server."
    echo ""
    echo "Alternatively, you can:"
    echo "1. Open frontend/index.html directly in your browser"
    echo "2. Or use another web server (Node.js http-server, etc.)"
    exit 1
fi

echo "✓ Using $PYTHON"
echo ""
echo "Starting web server on http://localhost:8000"
echo "Press Ctrl+C to stop the server"
echo ""
echo "Opening browser in 2 seconds..."
echo ""

# Start server in background
cd "$SCRIPT_DIR/frontend"

# Try to open browser
sleep 2
if command -v xdg-open &> /dev/null; then
    xdg-open "http://localhost:8000" &
elif command -v open &> /dev/null; then
    open "http://localhost:8000" &
elif command -v start &> /dev/null; then
    start "http://localhost:8000" &
else
    echo "Please open http://localhost:8000 in your browser"
fi

# Start server (this will block)
$PYTHON -m http.server 8000
