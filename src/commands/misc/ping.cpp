#include "modules/command_factory.h"
#include "utils/utils.h"
#include <string>

static Command ping_cmd("ping", "Ping pong!", [](const dpp::slashcommand_t& event){
    event.reply(std::string("Pong ") + getRandomEmoji());
});