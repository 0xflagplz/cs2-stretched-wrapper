# CS2 Resolution Wrapper

A simple wrapper that automatically manages CS2 resolution settings and restores them after quitting. 

# MUST DO
```
# CHANGE THE CS2 DIR IN SOURCE CODE
```

## Features

- Automatically sets CS2 to 4:3 borderless window mode (1440x1080 by default)
- Monitors CS2 process and restores original resolution when game exits
- No installation required - single standalone executable
- No dependencies
- Non-persistent - leaves no traces after execution

## Prerequisites

- GCC compiler installed
- Steam must be running before launching wrapper

## Default Resolution Values

- Default target resolution: 1440x1080 (4:3)
- Default source resolution: 1920x1080 (16:9)

## Important Note

If your monitor's native resolution is not 1920x1080, you'll need to modify the resolution values in the source code before compiling:

1. Open the source file
2. Locate the resolution variables
3. Update them to match your setup
4. Compile the modified code

## Usage

1. Compile the source code using GCC
2. Launch Steam
3. Run the compiled wrapper
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
# CHANGE THE CS2 DIR IN SOURCE CODE
CMD> .\compile.bat
```
