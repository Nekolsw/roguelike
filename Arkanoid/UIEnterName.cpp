#include "UIEnterName.h"
#include "UIManager.h"
namespace Arkanoid
{
	void UIEnterName::EnterPlayerName(sf::Event& event, GameResources& resources)
	{
		isPlayerNameEnter = false;
		if (sf::Keyboard::isKeyPressed && event.key.code == sf::Keyboard::Enter)
		{
			isPlayerNameEnter = true;
		}

		if (sf::Keyboard::isKeyPressed && event.key.code == sf::Keyboard::BackSpace)
		{
			playerName = playerName.substring(0, playerName.getSize() - 1);
		}

		if (event.type == sf::Event::TextEntered && playerName.getSize() < 10)
		{
			playerName += static_cast<char>(event.text.unicode);
		}
		SetTextScreen(enterNameText, "Player's name: " + playerName, 56, sf::Color::Cyan, resources.fontText, { 350.f - playerName.getSize() * 8, 300.f }, { 0.0f, 0.0f });
	}
	void UIEnterName::InitializedMainMenu(sf::Font& font)
	{
		SetRectangleShape(enterNameBackground, { 890.f, 110.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 260.f, 285.f }, sf::Color::Cyan, 1.f);
		SetTextScreen(headerText, "Congratulations on your victory!!!!", 56, sf::Color::Cyan, font, { 710.f, 200.f }, { 0.5f, 0.5f });
		SetTextScreen(enterNameText, "Player's name: " + playerName, 56, sf::Color::Cyan, font, { 350.f - playerName.getSize() * 8, 300.f }, { 0.0f, 0.0f });
	}
	void UIEnterName::DrawEnterText(sf::RenderWindow& window)
	{
		window.draw(enterNameBackground);
		window.draw(enterNameText);
		window.draw(headerText);
	}
}