#pragma once

// Original Documentation:
// https://www.reactphysics3d.com/documentation/manual/ReactPhysics3D-UserManual.pdf

#include <Graphite/core/log.h>

#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

#include <vector>

namespace Graphite {

// Wrapper for the ReactPhysics3D Physics Engine
class Physics {
  public:
    Physics();
    ~Physics();

    void update();

    int addRigidBody();

  public:
    float now;
    PhysicsWorld *world = nullptr;

    std::vector<RigidBody *> rigidbody;

  private:
    PhysicsCommon common;

    float past;

  private:
    // Return Time in Milliseconds
    float time() {
        struct timespec res;
        clock_gettime(CLOCK_MONOTONIC, &res);
        return (1000.0f * res.tv_sec + (float)res.tv_nsec / 1e6) / 1000.0f;
    }
};

} // namespace Graphite