# ConnectFour-Assignment
An artificial intelligence assignment in school. I chose to recreate the classical game "connect four", using Godot 3.4.4 with c++(GDNative) as the scripting langauge.

The technology used to implement the AI is minimax.

# Build requirements
Python 3.4 or higher (required for godot-cpp)

CMake 3.6 or higher

A C++ compiler with at least the c++14 standard. Tested with MSVC(On windows 10) and Clang(On macOS).

# Build script source (debug)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build --config Debug

# Build script source (release)
cmake -B build -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release

# File Structure
The Godot project is located in the folder "ConnectFour".

The Scripts are located in the folder "scripts-source".

# Repository cloning
If you wish to clone this. Do it recursively.

git clone https://github.com/hallback01/ConnectFour-Assignment.git --recursive

# Attribution
Noto Sans Font https://fonts.google.com/noto/specimen/Noto+Sans
