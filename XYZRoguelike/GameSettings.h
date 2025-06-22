#pragma once
#include <string>

namespace XYZRoguelike {
class GameWorld {
   private:
    GameWorld() = default;

   public:
    static GameWorld& Instance() {
        static GameWorld gameWorld;
        return gameWorld;
    }

    // Resources path
    const std::string RESOURCES_PATH = "Resources/";
    const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
    const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
    const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
    const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

    // Game settings constants
    const unsigned int SCREEN_WIDTH = 800;
    const unsigned int SCREEN_HEIGHT = 600;
    const float TIME_PER_FRAME = 1.f / 60.f;  // 60 fps

    const char* PLAYER_NAME = "Player";

    const std::string GAME_NAME = "Roguelike";
};
}  // namespace XYZRoguelike

#define SETTINGS GameWorld::Instance()