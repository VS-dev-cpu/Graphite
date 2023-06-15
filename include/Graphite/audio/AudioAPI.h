#pragma once

#include <stdint.h>

class AudioAPI {
  public:
    AudioAPI() { throw 1; }
    virtual ~AudioAPI() {}

    virtual bool update() { return false; }

  public:
    uint32_t width, height;

  private:
    // NONE

  private:
    // NONE
};