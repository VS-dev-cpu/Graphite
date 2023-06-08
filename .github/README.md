# Graphite - Game Engine

## About

I like to compare this engine to [Bevy](https://bevyengine.org/), as it will only be a library for C++, but later i may as well make a GUI for it.

It will...
- be modular (everything is scriptable)
- target lower-end hardware
- be scriptable in C++ and [Lua](https://www.lua.org/about.html) (and Custom Script Modules)
- have cross-platform support ([Windows](https://www.mingw-w64.org/), [Linux](https://gcc.gnu.org/), [Web/HTML5](https://emscripten.org/), [Android](https://developer.android.com/))
- use [ReactPhysics3D](https://reactphysics3d.com/) as a Physics Engine (or custom)

... these are just plans, they may (and probably will) change

I use [Visual Studio Codium](https://vscodium.com/) with the following extensions: [clangd](https://open-vsx.org/extension/llvm-vs-code-extensions/vscode-clangd), [CMake](https://open-vsx.org/extension/twxs/cmake), [CMake IntelliSense](https://open-vsx.org/extension/KylinIdeTeam/cmake-intellisence), [CMake Tools](https://open-vsx.org/extension/ms-vscode/cmake-tools), [Todo Tree](https://open-vsx.org/vscode/item?itemName=Gruntfuggly.todo-tree)

## Documentation

### Setup

#### Linux (Debian Based)

1. Install Build Tools

""sudo apt install build-essentials git cmake ninja-build mingw-w64 make libglfw3""

2. Clone the Repo
> git clone https://github.com/VS-dev-cpu/Graphite

3. Build Physics Engine
> TODO

#### Linux (Arch Based)

1. Install Build Tools
> sudo pacman -S git cmake ninja mingw-w64-gcc make glfw-x11

2. Clone the Repo
> git clone https://github.com/VS-dev-cpu/Graphite

3. Build Physics Engine
> git clone https://github.com/DanielChappuis/reactphysics3d.git

> cd reactphysics3d

> cmake

> make

> sudo make install

#### Windows

Coming Later!

#### MacOS

I don't own a Mac Device, but pull requests are welcomed!

### Usage

Coming Soon!

## License

This Project is licensed under the [zlib License](https://opensource.org/license/zlib-license-php/)
