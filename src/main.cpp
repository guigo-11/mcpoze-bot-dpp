#include <mcpoze/mcpoze.h>

#include <string>
#include "utils/utils.h"
#include "modules/module_registry.h"

using json = nlohmann::json;

int main(int argc, char const *argv[]) {
    json configdocument;
    std::ifstream configfile("../config.json");
    configfile >> configdocument;

    const std::string BOT_TOKEN = configdocument["token"];

    dpp::cluster bot(BOT_TOKEN);

    bot.on_log(dpp::utility::cout_logger());

    ModuleRegistry::instance().register_all(bot);

    bot.on_ready([&bot](const dpp::ready_t& event) {
        ModuleRegistry::instance().run_ready_callbacks(bot);
    });

    bot.start(dpp::st_wait);

    return 0;
}
