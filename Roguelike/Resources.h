#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"

namespace Roguelike
{
	struct GameResources {
		sf::Texture wallTexture;
		sf::SoundBuffer ballHit, gameOver, menuHover, menuEnter;
		sf::Font fontText;
	};

	void InitializingResources(GameResources& resources);


}
