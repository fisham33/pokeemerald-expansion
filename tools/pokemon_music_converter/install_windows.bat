@echo off
echo === Pokemon Music Converter - Windows Setup ===
echo.

:: Check for Python
python --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: Python not found. Please install Python 3.8+ from python.org
    echo Make sure to check "Add Python to PATH" during installation!
    pause
    exit /b 1
)

:: Create virtual environment
echo Creating virtual environment...
python -m venv venv
if errorlevel 1 (
    echo ERROR: Failed to create virtual environment
    pause
    exit /b 1
)

:: Install dependencies
echo Installing dependencies...
venv\Scripts\pip install -r requirements.txt
if errorlevel 1 (
    echo ERROR: Failed to install dependencies
    pause
    exit /b 1
)

echo.
echo === Setup Complete! ===
echo.
echo You can now use: music_converter.bat [command] [options]
echo.
echo Examples:
echo   music_converter.bat analyze my_song.mid
echo   music_converter.bat integrate my_song.mid --voicegroup 128
echo   music_converter.bat --help
echo.
pause
