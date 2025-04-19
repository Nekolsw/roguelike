#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "SoundPlayer.h"
#include "Enemy.h"
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
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<Enemy> enemy;
		std::vector<std::unique_ptr<Wall>> walls; 
		std::unique_ptr<SoundPlayer> backgroundMusic;
	};
}