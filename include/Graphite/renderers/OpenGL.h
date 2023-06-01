#pragma once

#include "Graphite/core/ResourceManager.h"
#include "Graphite/types/base.h"
#include <Graphite/core/Renderer.h>

namespace Graphite {

class OpenGL : public Renderer {
  public:
    OpenGL();
    ~OpenGL();

    bool update();

    // void clear(float red, float green, float blue);

    // bool load_shader(std::string shader);
    // bool load_texture(Texture texture);

  private:
};

} // namespace Graphite