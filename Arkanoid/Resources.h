#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"

namespace Roguelike
{
	struct GameResources {
		sf::Texture ballTexture, ballTextureDamage_1, ballTextureDamage_2, ballTextureDamage_3, ballTextureDestroy, wallTexture, platformTexture, brickClassicTexture, brickProtectedTexture, 
			fireBallBonusTexture, glassBrickBonusTexture, IncreasingPlatformBonusTexture;
		sf::SoundBuffer ballHit, gameOver, menuHover, menuEnter;
		sf::Font fontText;
	};

	void InitializingResources(GameResources& resources);


}
