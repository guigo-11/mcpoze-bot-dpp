#include "module_registry.h"
#include <mutex>

namespace dpp { class cluster; }

ModuleRegistry& ModuleRegistry::instance()
{
    static ModuleRegistry inst;
    return inst;
}

void ModuleRegistry::add_module(ModuleFn fn) {
    modules_.push_back(std::move(fn));
}

void ModuleRegistry::add_ready_callback(ModuleFn fn) {
    ready_callbacks_.push_back(std::move(fn));
}

void ModuleRegistry::run_ready_callbacks(dpp::cluster& bot) {
    for (auto &r : ready_callbacks_) r(bot);
}

void ModuleRegistry::register_all(dpp::cluster& bot) {
    for (auto &m : modules_) m(bot);
}