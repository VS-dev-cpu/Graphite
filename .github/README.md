# Game-Engine
## Pre-Alpha Version

> WARNING: The Current Version is a work in progress version!
> With the first stable version, ill make a dev branch

This Game-Engine will be a more code-oriented Engine than others, like [Unity](https://unity.com/), [Unreal](https://www.unrealengine.com/en-US) or [Godot](https://godotengine.org/)

Just like Bevy to Rust,
it will be a library for C++.

At some point, it will have a GUI as well

It will...
- be modular
- target middle-tear hardware
- support multiple Graphics APIs (OpenGL, Vulkan, DirectX)
- support several Audio APIs (OpenAL, XAudio2, SDL Mixer)
- be scriptable in C++ and [Lua](https://www.lua.org/about.html)
- have cross-platform Support ([Windows](https://www.mingw-w64.org/), [Linux](https://gcc.gnu.org/), [Web/HTML5](https://emscripten.org/), [Android](https://developer.android.com))
- use [ReactPhysics3D](https://reactphysics3d.com)

... these are just my plans for it, but it may (and probably will) change
I also run a YouTube channel where I post devlogs about the engine, there you can get the latest news about it's state.

If you want to support me, you can subscribe on my channel, and you can also consider being my patreon, but even just a comment is more support than you think!

here is [My Channel](https://www.youtube.com/channel/UCR8z9TUZnUDvs0XR0DUEnmw), if you are interested in my project

Thank you for reading it this far, see y'all in the next devlog!

# Usage

## Setup

### Linux

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