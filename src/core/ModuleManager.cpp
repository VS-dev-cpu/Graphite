#include <Graphite/core/ModuleManager.hpp>

using namespace Graphite;

ModuleManager::ModuleManager() {}

ModuleManager::~ModuleManager() {
    for (auto m : modules) {
        m->destroy();
        delete m;
    }

    modules.clear();
}

unsigned int ModuleManager::add(Module *module, ModulePriority priority,
                                ModuleDependencies dependencies) {

    // TODO: handle priority & dependencies

    modules.push_back(module);
    return modules.size();
}

void ModuleManager::update() {
    last = now;
    now = time();
    float deltaTime = now - last;

    for (auto m : modules)
        m->update(deltaTime);
}