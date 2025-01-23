#include <SFML/Graphics.hpp>
#include "GameMath.h"

namespace Arkanoid
{
	void SetSpriteSize(sf::Sprite& sprite, sf::Vector2f size)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { size.x/ spriteRect.width, size.y / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, sf::Vector2f origin)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(origin.x * spriteRect.width, origin.y * spriteRect.height);
	}
}