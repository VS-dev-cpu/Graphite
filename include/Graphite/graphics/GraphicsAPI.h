#pragma once

#include <stdint.h>

class GraphicsAPI {
  public:
    GraphicsAPI() { throw 1; }
    virtual ~GraphicsAPI() {}

    virtual bool update() { return false; }

  public:
    uint32_t width, height;

  private:
    // NONE

  private:
    // NONE
};