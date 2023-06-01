#pragma once

namespace Graphite {

class Renderer {
  public:
    Renderer() {}
    virtual ~Renderer() {}

    virtual bool update() { return false; }
    virtual void clear() {}

  private:
};

} // namespace Graphite