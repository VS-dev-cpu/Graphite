# Game-Engine
## Pre-Alpha Version
> WARNING: The Current Version is a work in progress version!
> With the first stable version, i'll make a dev branch

> It will probably called "[Graphite](https://en.wikipedia.org/wiki/Graphite)", but you can suggest other ones [here](https://github.com/VS-dev-cpu/Game-Engine/issues/2)

## About

I like to compare this engine to [Bevy](https://bevyengine.org/), as it will only be a library for C++, but later i may as well make a GUI for it.

It will...
- be modular (user-definable Renderer, Physics Engine, etc.)
- target middle-tear hardware
- use OpenGL with GLFW (CUSTOMIZABLE)
- support several Audio APIs (OpenAL, XAudio2, SDL Mixer) (CUSTOMIZABLE)
- be scriptable in C++ and [Lua](https://www.lua.org/about.html) (CUSTOMIZABLE)
- have cross-platform Support ([Windows](https://www.mingw-w64.org/), [Linux](https://gcc.gnu.org/), [Web/HTML5](https://emscripten.org/), [Android](https://developer.android.com/))
- use [ReactPhysics3D](https://reactphysics3d.com/) as a Physics Engine (CUSTOMIZABLE)

... these are just my plans, it may (and probably will) change

I also do [Youtube Devlogs](https://www.youtube.com/channel/UCR8z9TUZnUDvs0XR0DUEnmw) about my progress, so check it out if you are interested!

## Usage

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
