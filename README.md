# FourInARow-Assignment
An artificial intelligence assignment in school. I chose to recreate the game "four in a row", using Godot 3.4.4 with c++(GDNative) as the scripting langauge.

# Build requirements
Python 3.4 or higher

CMake 3.18 or higher

A C++ with at least the 2014 standard. Tested with MSVC(On windows 10) and Clang(On macOS)

# Build script source (debug)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build --config Debug

# Build script source (release)
cmake -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release

# File Structure
The Godot project is located in the folder "FourInARow".

The Scripts are located in the folder "scripts-source".

# Repository cloning
If you wish to clone this. Do it recursively.

git clone https://github.com/hallback01/FourInARow-Assignment.git --recursive