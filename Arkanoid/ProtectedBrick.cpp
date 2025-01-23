#include "ProtectedBrick.h"
#include "GameSettings.h"
#include "GameMath.h"

namespace Arkanoid
{
	void ProtectedBrick::Initialization(sf::Vector2f newPosition, sf::Vector2f sizeBrick, GameResources& resources, sf::Color color)
	{
		ProtectedBrick::typeBrick = GameSettings::TypeBrick::Protected;
		holdsPunches = PROTECTED_BRICK_HOLDS_PUNCHES;
		textureBrickBroken = resources.brickClassicTexture;
		SpriteObject::Initialization(newPosition, sizeBrick, resources.brickProtectedTexture, color);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	}

	void ProtectedBrick::RandomColoring()
	{
		objectSprite.setColor(sf::Color(50 + rand() % 205, 50 + rand() % 205, 50 + rand() % 205));
	}

	void ProtectedBrick::Punch()
	{
		if(holdsPunches > 0) 
		{
			--holdsPunches;
			objectSprite.setTexture(textureBrickBroken);
		}

	}

	void ProtectedBrick::Punch(bool glassBrickBonusActivated)
	{
		if (glassBrickBonusActivated) 
		{
			holdsPunches = 0;
		}

		else 
		{
			Punch();
		}
	}

	bool ProtectedBrick::isDestroyed()
	{
		return holdsPunches <= 0;
	}
}