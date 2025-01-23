#include "SpriteObject.h"
#include "GameMath.h"
namespace Arkanoid
{

	void SpriteObject::Initialization(sf::Vector2f newPosition, sf::Vector2f newScale, sf::Texture& texture, sf::Color color)
	{
		texture.setSmooth(true);
		objectSprite.setTexture(texture);
		objectSprite.setPosition(newPosition);
		objectSprite.setColor(color);
		SetSpriteRelativeOrigin(objectSprite, { 1.0f, 1.0f });
		scale = newScale;
		SetSpriteSize(objectSprite, { scale.x, scale.y });
		
	}

	void SpriteObject::Draw(sf::RenderWindow& window)
	{
		window.draw(objectSprite);
	}
	sf::Vector2f SpriteObject::GetScale()
	{
		return scale;
	}
	void SpriteObject::SetScaleObject(sf::Vector2f scaleObject)
	{
		scale = scaleObject;
	}
	sf::Vector2f SpriteObject::GetPosition()
	{
		return objectSprite.getPosition();
	}
	void SpriteObject::SetPosition(sf::Vector2f position)
	{
		objectSprite.setPosition(position);
	}
}