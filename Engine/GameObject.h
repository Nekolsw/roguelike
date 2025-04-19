#pragma once
#include <SFML/Graphics.hpp>
namespace Engine
{
	class GameObject
	{
	protected:
		sf::Vector2f scale;
	protected:
		sf::Sprite objectSprite;
	public:

		virtual void Initialization(sf::Vector2f newPosition, sf::Vector2f scale, sf::Texture& texture, sf::Color color) = 0;
		
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual sf::Vector2f GetScale() = 0;
		virtual void SetScaleObject(sf::Vector2f scaleObject) = 0;
		virtual sf::Vector2f GetPosition() = 0;
		virtual void SetPosition(sf::Vector2f position) = 0;
	};
}
