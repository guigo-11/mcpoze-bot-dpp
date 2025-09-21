#include "modules/module_registry.h"
#include "utils/utils.h"
#include <mcpoze/mcpoze.h>
#include <vector>
#include <random>

std::vector<dpp::presence> status = {
    dpp::presence(
        dpp::ps_online,
        dpp::at_listening,
        "Olá putas! " + getRandomEmoji()
    ),
    dpp::presence(
        dpp::ps_idle,
        dpp::at_competing,
        "pela sua irmã 🤣"
    ),
    dpp::presence(
        dpp::ps_dnd,
        dpp::at_game,
        "Grand Theft Auto VI"
    ),
    dpp::presence(
        dpp::ps_online,
        dpp::at_game,
        "Hollow Knight: Silksong"
    )
};


static void set_status(dpp::cluster& bot) 
{
    auto update = [&bot]() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<std::size_t> dis(0, status.size() - 1);
        bot.set_presence(status[dis(gen)]);
    };

    update();
  
    bot.start_timer([&bot, update](dpp::timer timer) {
        update();
    }, 60000);
}

static ReadyRegister reg(set_status);