#include "UIConstructor.h"
namespace Roguelike
{
	void SetTextScreen(sf::Text& textScreen, std::string stringScreen, int textSize, sf::Color textColor, sf::Font& font, UIPosition2D gameTextPosition, UIPosition2D textRevelationOrigin, bool isTextBold)
	{
		textScreen.setString(stringScreen);
		textScreen.setCharacterSize(textSize);
		textScreen.setFillColor(textColor);
		textScreen.setFont(font);
		if (isTextBold)
		{
			textScreen.setStyle(sf::Text::Bold);
		}
		else
		{
			textScreen.setStyle(sf::Text::Regular);
		}
		SetTextRelativeOrigin(textScreen, textRevelationOrigin);
		textScreen.setPosition({ gameTextPosition.x, gameTextPosition.y });
	}

	void SetRectangleShape(sf::RectangleShape& rectangle, UIPosition2D size, sf::Color colorBackground, UIPosition2D origin, UIPosition2D position, sf::Color colorOutliner, float outlinerThickness)
	{
		rectangle.setSize({ size.x, size.y });
		rectangle.setFillColor(colorBackground);
		rectangle.setOrigin({ origin.x, origin.y });
		rectangle.setPosition({ position.x, position.y });
		rectangle.setOutlineThickness(outlinerThickness);
		rectangle.setOutlineColor(colorOutliner);
	}
	void UpdateRectangleShape(sf::RectangleShape& rectangle, UIPosition2D position)
	{
		rectangle.setPosition({ position.x, position.y });
	}

	void UpdateTextScreen(sf::Text& textScreen, std::string text)
	{
		textScreen.setString(text);
	}

	void UpdateTextScreen(sf::Text& textScreen, UIPosition2D gameTextPosition)
	{
		textScreen.setPosition({ gameTextPosition.x, gameTextPosition.y });
	}
}