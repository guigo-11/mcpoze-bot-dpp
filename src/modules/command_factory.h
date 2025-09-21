#pragma once
#include "modules/module_registry.h"
#include <functional>
#include <mcpoze/mcpoze.h>

// Classe Command para registro manual
struct Command {
    Command(const char* name, const char* desc, std::function<void(const dpp::slashcommand_t&)> handler) {
        auto install = [name, handler = std::move(handler)](dpp::cluster& bot) {
            bot.on_slashcommand([name, handler](const dpp::slashcommand_t& event) {
                if (event.command.get_command_name() == name)
                    handler(event);
            });
        };
        auto create = [name, desc](dpp::cluster& bot) {
            if (dpp::run_once<struct register_cmd>()) {
                bot.global_command_create(dpp::slashcommand(name, desc, bot.me.id));
            }
        };
        ModuleRegister reg1(install);
        ReadyRegister reg2(create);
    }
};

// Macro para registro rápido de comandos
#define DEFINE_COMMAND(cmd_name, cmd_desc, handler_lambda) \
    namespace { \
        void __##cmd_name##_handler(const dpp::slashcommand_t& event) handler_lambda \
        auto __##cmd_name##_install = [](dpp::cluster& bot) { \
            bot.on_slashcommand([](const dpp::slashcommand_t& event) { \
                if (event.command.get_command_name() == #cmd_name) \
                    __##cmd_name##_handler(event); \
            }); \
        }; \
        auto __##cmd_name##_create = [](dpp::cluster& bot) { \
            if (dpp::run_once<struct register_cmd_##cmd_name>()) { \
                bot.global_command_create(dpp::slashcommand(#cmd_name, cmd_desc, bot.me.id)); \
            } \
        }; \
        ModuleRegister __##cmd_name##_reg(__##cmd_name##_install); \
        ReadyRegister __##cmd_name##_reg_ready(__##cmd_name##_create); \
    }
