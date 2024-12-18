# CS2 Resolution Wrapper

A simple wrapper that automatically manages CS2 resolution settings and restores them after quitting. 

# MUST DO
```
# Make sure you have .url shortcut on your desktop for cs2
```

## Prerequisites

- GCC compiler installed
- Steam must be running before launching wrapper
- CS2 shortcut URL file (typically found in Steam installation folder)

## Default Resolution Values

- Default target resolution: 1440x1080 (4:3)
- Default source resolution: 1920x1080 (16:9)

## Important Note
1. Open the source file
2. Locate the CS2 shortcut URL path variable
3. Compile the modified code

Additionally, if your monitor's native resolution is not 1920x1080, you'll need to modify the resolution values as well.

## Usage

1. Compile the source code using GCC
2. Launch Steam
3. Run the compiled wrapper instead of starting cs2
4. The wrapper will:
   - Check if Steam is running
   - Change to 4:3 resolution
   - Launch CS2
   - Monitor the game process
   - Restore original resolution when CS2 exits
   - Close automatically

## Requirements

- GCC compiler installed

## Building from Source

```
# CHANGE THE CS2 SHORTCUT URL PATH IN SOURCE CODE
CMD> .\compile.bat
```
