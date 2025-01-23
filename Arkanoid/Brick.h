#pragma once
#include "BaseBrick.h"
#include "Resources.h"
#include "GameSettings.h"
namespace Arkanoid
{
	class Brick : public BaseBrick
	{
	private:

		GameResources resources;
		bool isBrickDestroy = false;
		GameSettings::TypeBrick typeBrick;
	public:
		void Initialization(sf::Vector2f newPosition, sf::Vector2f sizeBrick, GameResources& resources, sf::Color color) override;
		void RandomColoring() override;
		void Draw(sf::RenderWindow& window)  override;
		void Punch() override;
		void Punch(bool glassBrickBonusActivated) override;
		bool isDestroyed() override;
		virtual GameSettings::TypeBrick GetTypeBrick() override
		{
			return typeBrick;
		};
	};
}

