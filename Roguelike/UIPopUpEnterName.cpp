#include "UIPopUpEnterName.h"
#include "KeyBindings.h"
namespace Roguelike 
{

	bool UIPopUpEnterName::PopUpWillNameEntered(sf::Event event)
	{
		answerIsSelected = false;
			switch (KeyBindings::Instance().GetKeyPressed())
			{
			case sf::Keyboard::A:
				willNameEntered = true;
				textYes.setFillColor(sf::Color::Green);
				textNo.setFillColor(sf::Color::Cyan);
				break;

			case sf::Keyboard::D:
				textYes.setFillColor(sf::Color::Cyan);
				textNo.setFillColor(sf::Color::Green);
				willNameEntered = false;
				break;
			case sf::Keyboard::Space:
				answerIsSelected = true;
				return willNameEntered;
			default:
				break;
			}
	}

	void UIPopUpEnterName::InitializedMainMenu(sf::Font& font)
	{
		SetTextScreen(textHeader, "Entered name?", 36, sf::Color::Cyan, font, { 650.f, 300.f }, { 0.5f, 0.5f });
		SetTextScreen(textYes, "Yes", 36, sf::Color::Cyan, font, { 600.f, 360.f }, { 0.5f, 0.5f });
		SetTextScreen(textNo, "No", 36, sf::Color::Green, font, { 700.f, 360.f }, { 0.5f, 0.5f });
		SetRectangleShape(background, { 300.f, 150.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 500.f, 260.f }, sf::Color::Cyan, 1.f);
	}

	void UIPopUpEnterName::DrawPopUp(sf::RenderWindow& window)
	{
		window.draw(background);
		window.draw(textHeader);
		window.draw(textYes);
		window.draw(textNo);
	}
}