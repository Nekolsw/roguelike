#pragma once

#include "AISwordMan.h"
#include "Enemy.h"
#include "Floor.h"
#include "NPCSpawner.h"
#include "Player.h"
#include "Scene.h"
#include "SoundPlayer.h"
#include "Wall.h"

#include <array>
#include <iostream>

using namespace XYZEngine;

namespace XYZRoguelike {
class DeveloperLevel : public Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;

   private:
    std::unique_ptr<SoundPlayer> backgroundMusic;
};
}  // namespace XYZRoguelike