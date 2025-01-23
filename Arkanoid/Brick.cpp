#include "Brick.h"
#include "GameMath.h"
#include "Constants.h"
#include "Ball.h"
namespace Roguelike
{
	void Brick::Initialization(sf::Vector2f newPosition, sf::Vector2f sizeBrick, GameResources& resources, sf::Color color)
	{
		Brick::typeBrick = GameSettings::TypeBrick::Standart;
		SpriteObject::Initialization(newPosition, sizeBrick, resources.brickClassicTexture, color);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	}
	void Brick::RandomColoring()
	{
		objectSprite.setColor(sf::Color(50 + rand() % 205, 50 + rand() % 205, 50 + rand() % 205));
	}
	void Brick::Draw(sf::RenderWindow& window)
	{
		window.draw(objectSprite);
	
	}
	void Brick::Punch()
	{
		Brick::isBrickDestroy = true;
	}
	void Brick::Punch(bool glassBrickBonusActivated)
	{
		Punch();
	}
	bool Brick::isDestroyed()
	{
		return Brick::isBrickDestroy;
	}
}