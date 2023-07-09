#pragma once

#include <Graphite/types/module.hpp>
#include <mathutil/common.hpp>

#include <atomic>
#include <mutex>
#include <vector>

namespace Graphite {

enum class ModulePriority { NONE, FIRST, LAST };
typedef std::vector<unsigned int> ModuleDependencies;

class ModuleManager {
  public:
    // Initialize Module Manager
    ModuleManager();

    // Destroy Modules & Module Manager
    ~ModuleManager();

    // Add Module
    unsigned int add(Module *module,
                     ModulePriority priority = ModulePriority::NONE,
                     ModuleDependencies dependencies = {});

    // Update Modules
    void update();

  public:
  private:
    // Module Management
    std::vector<Module *> modules;

    // Timing
    float last, now;

  private:
};

} // namespace Graphite