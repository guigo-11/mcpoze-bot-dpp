#include <mcpoze/mcpoze.h>
#include <iostream>

void debug_log(dpp::cluster& bot) 
{
    std::cout << "✅" << bot.me.global_name << "is ready!";
}