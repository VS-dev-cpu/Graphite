# Game-Engine
## Pre-Alpha Version
> WARNING: The Current Version is a work in progress version!
> With the first stable version, i'll make a dev branch

> It will probably called "[Graphite](https://en.wikipedia.org/wiki/Graphite)", but you can suggest other ones [here](https://github.com/VS-dev-cpu/Game-Engine/issues/2)

## About

I like to compare this engine to [Bevy](https://bevyengine.org/), as it will only be a library for C++, but later i may as well make a GUI for it.

It will...
- use the [Artifex](https://github.com/VS-dev-cpu/Artifex) 2D Engine for Rendering
- be modular (everything is scriptable)
- target middle-tear hardware
- be scriptable in C++ and [Lua](https://www.lua.org/about.html) (and Custom Script Modules)
- have cross-platform Support ([Windows](https://www.mingw-w64.org/), [Linux](https://gcc.gnu.org/), [Web/HTML5](https://emscripten.org/), [Android](https://developer.android.com/))
- use [ReactPhysics3D](https://reactphysics3d.com/) as a Physics Engine (or other)

... these are just plans, they may (and probably will) change

I also make [Youtube Devlogs](https://www.youtube.com/channel/UCR8z9TUZnUDvs0XR0DUEnmw) about my progress, so check it out if you are interested!

## Documentation

### Setup

#### Linux (Manjaro, Arch Based)

1. Install (Build) Tools
> sudo pacman -S git cmake ninja mingw-w64-gcc make glfw-x11

2. Clone the Repo
> git clone https://github.com/VS-dev-cpu/Game-Engine

3. Build Physics Engine
> git clone https://github.com/DanielChappuis/reactphysics3d.git

> cd reactphysics3d

> cmake

> make

> sudo make install

#### Windows

Coming Later!

#### MacOS

I don't own a Mac Device, but if you do and want to make support for it, please contact me (or make a pull request)!

### Usage

Coming Soon!

## License

This Project is licensed under the [zlib License](https://opensource.org/license/zlib-license-php/)

It is free-to-use, modify and/or use commercially
(this means, for example you can make a game with this engine and put it on Steam without having to pay me anything or open-source the game)
