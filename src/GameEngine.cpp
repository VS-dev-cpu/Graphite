#include <GameEngine/GameEngine.h>

namespace GameEngine {
// Initialize Engine
GameEngine::GameEngine(std::string name, bool fullscreen, int width, int height)
    : me(name, fullscreen, width, height) {
    LOG::SYSTEM("GameEngine", "Initialized");
}

// Destroy Engine
GameEngine::~GameEngine() { LOG::SYSTEM("GameEngine", "Destroyed"); }

// Start Engine
void GameEngine::start() {
    // Initialize Modules
    for (auto module : modules)
        module->init();

    LOG::SYSTEM("GameEngine", "Started Successfully");

    // Main Loop
    double past = now = time();
    while (me.running) {
        // Calculate DeltaTime
        past = now;
        now = time();
        deltaTime = now - past;

        double start = time(); // [MainTime] Start

        // Update Modules
        for (auto module : modules)
            module->update(deltaTime);

        // Update Render Queue
        me.update();
    }
}

uint GameEngine::add(Module *module) {
    modules.push_back(module);

    module->engine = this;
    return module->id = modules.size() - 1;
}
} // namespace GameEngine