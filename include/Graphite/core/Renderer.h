#pragma once

#include <Graphite/types/base.h>

namespace Graphite {

class Renderer {
  public:
    Renderer();
    ~Renderer();

    bool update();

    void clear(float red, float green, float blue);

    // bool load_shader(std::string shader);
    // bool load_texture(Texture texture);

  private:
};

} // namespace Graphite