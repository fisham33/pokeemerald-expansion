@echo off
:: Pokemon Music Converter - Windows Wrapper
:: Usage: music_converter.bat [command] [options]

setlocal

:: Get the directory where this batch file is located
set "SCRIPT_DIR=%~dp0"

:: Check if venv exists
if not exist "%SCRIPT_DIR%venv\Scripts\python.exe" (
    echo ERROR: Virtual environment not found.
    echo Please run install_windows.bat first!
    exit /b 1
)

:: Run the converter with all arguments
"%SCRIPT_DIR%venv\Scripts\python.exe" "%SCRIPT_DIR%pokemon_music_converter.py" %*
