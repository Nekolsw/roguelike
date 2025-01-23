#pragma once
#include "SpriteObject.h"
#include "Resources.h"
#include "GameSettings.h"

namespace Arkanoid
{
	class BaseBrick : public SpriteObject
	{
	protected:
	public:
		virtual void Initialization(sf::Vector2f newPosition, sf::Vector2f sizeBrick, GameResources& resources, sf::Color color) = 0;
		virtual void RandomColoring() = 0;
		virtual void Punch() = 0;
		virtual void Punch(bool glassBrickBonusActivated) = 0;
		virtual bool isDestroyed() = 0;
		virtual GameSettings::TypeBrick GetTypeBrick() = 0;
	};

}