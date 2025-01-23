#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObject.h"
#include "Constants.h"
#include "BaseBonus.h"
#include "Resources.h"
namespace Roguelike
{
	class Platform : public SpriteObject
	{
	private:
		GameResources resources;
		float directionSpeed = PLATFORM_SPEED;
		float durationInIncreasedSize = 0;
		sf::Vector2f positionPlaform;
	public:
		void Initialization(sf::Vector2f newPosition, GameResources& resources, sf::Color color);
		void Update(float& deltaTime);
		void TookSizeIncreaseBonus();
		bool Collision(BaseBonus& bonus, SpriteObject& platform);
		float GetDirectionSpeed();
	};
}

