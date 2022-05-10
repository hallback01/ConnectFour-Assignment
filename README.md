# FourInARow-Assignment
An artificial intelligence assignment in school. I chose to recreate the game "four in a row", using Godot 3.4.4 with c++(GDNative) as the scripting langauges.

# Build script source (debug)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build --config Debug

# Build script source (release)
cmake -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release