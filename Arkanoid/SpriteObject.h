#pragma once
#include <SFML/Graphics.hpp>
#include "VectorMain.h"
#include "GameObject.h"
namespace Arkanoid
{

	class SpriteObject : public GameObject
	{
	public:
		void Initialization(sf::Vector2f newPosition, sf::Vector2f newScale, sf::Texture& texture, sf::Color color) override;

		void Draw(sf::RenderWindow& window)  override;
		sf::Vector2f GetScale() override;
		void SetScaleObject(sf::Vector2f scaleObject) override;
		sf::Vector2f GetPosition() override;
		void SetPosition( sf::Vector2f position) override;
	};

}