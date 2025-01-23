#pragma once
#include "UIConstructor.h"
namespace Arkanoid
{
	class UIPopUpEnterName
	{
		sf::Text textHeader, textYes, textNo;
		sf::RectangleShape background, backgroundMainMenu, backgroundStartGame;
		bool willNameEntered = false;
	public:
		bool answerIsSelected = false;
		bool PopUpWillNameEntered(sf::Event event);
		void InitializedMainMenu(sf::Font& font);
		void DrawPopUp(sf::RenderWindow& window);
	};
}