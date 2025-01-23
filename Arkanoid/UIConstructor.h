#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "UIMath.h"
#include "Resources.h"
namespace Arkanoid
{

	void SetTextScreen(sf::Text& textScreen, std::string stringScreen, int textSize, sf::Color textColor,
		sf::Font& font, UIPosition2D gameTextPosition, UIPosition2D textRevelationOrigin, bool isTextBold = false);

	void SetRectangleShape(sf::RectangleShape& rectangle, UIPosition2D size, sf::Color colorBackground, UIPosition2D origin, UIPosition2D position, sf::Color colorOutliner, float outlinerThickness);

	void UpdateRectangleShape(sf::RectangleShape& rectangle, UIPosition2D position);

	void UpdateTextScreen(sf::Text& textScreen, std::string textString);

	void UpdateTextScreen(sf::Text& textScreen, UIPosition2D gameTextPosition);
}
