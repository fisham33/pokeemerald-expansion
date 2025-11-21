@echo off
echo === Building Standalone .exe ===
echo.

:: Ensure venv exists
if not exist "venv\Scripts\python.exe" (
    echo Running install first...
    call install_windows.bat
)

:: Install PyInstaller
echo Installing PyInstaller...
venv\Scripts\pip install pyinstaller

:: Build the executable
echo Building executable...
venv\Scripts\pyinstaller --onefile --name pokemon_music_converter pokemon_music_converter.py

echo.
echo === Build Complete! ===
echo.
echo Your standalone .exe is at: dist\pokemon_music_converter.exe
echo You can copy this file anywhere and run it without Python!
echo.
pause
