#include <GameEngine/core/PhysicsEngine/PhysicsEngine.h>

Physics::Physics()
{
    // TODO: Ability to change settings on init
    PhysicsWorld::WorldSettings settings;
    settings.isSleepingEnabled = true;
    settings.gravity = Vector3(0, -9.81, 0);

    world = common.createPhysicsWorld(settings);

    past = now = time();
}

Physics::~Physics()
{
    common.destroyPhysicsWorld(world);
}

void Physics::update()
{
    past = now;
    now = time();
    float deltaTime = now - past;

    world->update(deltaTime);
}

int Physics::addRigidBody()
{
    Vector3 position(0.0, 3.0, 0.0);
    Quaternion orientation = Quaternion::identity();
    Transform transform(position, orientation);

    rigidbody.push_back(world->createRigidBody(transform));
    return rigidbody.size() - 1;
}