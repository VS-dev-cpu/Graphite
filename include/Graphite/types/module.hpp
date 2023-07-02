#pragma once

#include <string>

namespace Graphite {

// Engine Pre-Definition
class Engine;

// A Game Engine Module
class Module {
  public:
    // ---- Variables ----

    Engine *engine = nullptr; // hosting Game Engine
    uint id = 0;              // module's ID (inside Game Engine)

    // ---- Management ----

    virtual void init(){};    // called on init
    virtual void destroy(){}; // called before destroying

    // ---- Updates ----

    virtual void update(float deltaTime){}; // called on update
    virtual void
    fixedUpdate(double deltaTime){}; // called on in every 16 ms (60 fps)

    // ---- Event Callbacks ----

    virtual void onKeyPress(uint pressedKey){}; // called on key press
    virtual void
    onKeyRelease(uint releasedKey){}; // called on every key release
    virtual void onMouseMovement(float mouseX,
                                 float mouseY){}; // called on mouse movement
    virtual void
    onSceneChange(std::string newScene){}; // called on scene change
};

} // namespace Graphite