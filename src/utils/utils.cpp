#include <vector>
#include <random>

std::string getRandomEmoji() {
    static const std::vector<std::string> emojiList = {
        "😭","😄","😌","🤓","😎","😤","🤖","🌏","📸","💿","👋","🌊","✨","🤣","😂"
    };
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(emojiList.size() - 1));
    return emojiList[dis(gen)];
}