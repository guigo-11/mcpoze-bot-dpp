#pragma once
#include <functional>
#include <vector>

namespace dpp { class cluster; }

using ModuleFn = std::function<void(dpp::cluster&)>;

class ModuleRegistry {
    public:
        static ModuleRegistry& instance();
        void add_module(ModuleFn fn);
        void add_ready_callback(ModuleFn fn);
        void register_all(dpp::cluster& bot);
        void run_ready_callbacks(dpp::cluster& bot);

    private:
        std::vector<ModuleFn> modules_;
        std::vector<ModuleFn> ready_callbacks_;
};

struct ModuleRegister {
    ModuleRegister(ModuleFn fn) { ModuleRegistry::instance().add_module(fn); }
};
struct ReadyRegister {
    ReadyRegister(ModuleFn fn) { ModuleRegistry::instance().add_ready_callback(fn); }
};