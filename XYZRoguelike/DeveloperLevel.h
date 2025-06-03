#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "SoundPlayer.h"
#include "Enemy.h"
#include "Floor.h"
#include "Wall.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<Enemy> swordMan;
		std::unique_ptr<SoundPlayer> backgroundMusic;
	};
}