#pragma once
#include "BaseBrick.h"
#include "Constants.h"
namespace Roguelike
{
	class ProtectedBrick : public BaseBrick
	{
	private:
		int holdsPunches = PROTECTED_BRICK_HOLDS_PUNCHES;
		sf::Texture textureBrickBroken;
		GameResources resources;
		bool isBrickDestroy = false;
		GameSettings::TypeBrick typeBrick;
	public:
		void Initialization(sf::Vector2f newPosition, sf::Vector2f sizeBrick, GameResources& resources, sf::Color color) override;
		void RandomColoring() override;
		void Punch() override;
		void Punch(bool glassBrickBonusActivated) override;
		bool isDestroyed() override;
		virtual GameSettings::TypeBrick GetTypeBrick() override
		{
			return typeBrick;
		};
	};
}