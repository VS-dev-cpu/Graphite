#pragma once

#include <Graphite/types/base.h>

// Simple Game Object
class Object {
  public:
    Object() {}
    ~Object() {}

  private:
    // Parent Object
    Object *parent = nullptr;

    // Child Object(s)
    std::vector<Object *> children;
};