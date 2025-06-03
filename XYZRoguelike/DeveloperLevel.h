#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Floor.h"
#include "SoundPlayer.h"
#include "SwordMan.h"
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
		std::vector<std::unique_ptr<Floor>> floors;
		std::vector<std::unique_ptr<Wall>> walls;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<SwordMan> swordMan;
		std::unique_ptr<SoundPlayer> backgroundMusic;
	};
}