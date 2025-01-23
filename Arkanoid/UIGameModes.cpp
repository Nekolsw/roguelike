#include "UIGameModes.h"
#include "KeyBindings.h"
namespace Roguelike
{
	void UIGameModes::InitializedMainMenu(sf::Font& font)
	{
		SetTextScreen(textHeader, "Game mode", 48, sf::Color::Cyan, font, { 650.f, 190.f }, { 0.5f, 0.5f });
		SetTextScreen(text, "Adding moving obstacles", 24, sf::Color::Green, font, { 495.f, 265.f }, { 0.f, 0.f });
		listTextGameModeItems.push_back(text);
		SetTextScreen(text, "Adding portals", 24, sf::Color::Cyan, font, { 495.f, 295.f }, { 0.f, 0.f });
		listTextGameModeItems.push_back(text);
		SetRectangleShape(checkMoveObstacle, { 20.f, 20.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 465.f, 270.f }, sf::Color::Cyan, 2.f);
		SetRectangleShape(checkPortal, { 20.f, 20.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 465.f, 300.f }, sf::Color::Cyan, 2.f);
	
		beginGameModeItem = GameModeItems::isMoveObstacle;
		textGameModeIter = listTextGameModeItems.begin();
		SetRectangleShape(gameModeBackground, { 400.f, 500.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 443.f, 160.f }, sf::Color::Cyan, 1.f);
	}
	void UIGameModes::Playback(sf::SoundBuffer& buffer, GameSettings& gameSettings)
	{
		if (gameSettings.isPlaySound)
		{
			soundGame.setBuffer(buffer);
			soundGame.play();
		}
	}
	bool UIGameModes::ChoiceMenu(GameSettings& gameSettings, GameResources& gameResouces)
	{
			switch (KeyBindings::Instance().GetKeyPressed())
			{
			case sf::Keyboard::W:
				if (beginGameModeItem > GameModeItems::isMoveObstacle)
				{
					Playback(gameResouces.menuHover, gameSettings);
					--accountGameModeItems;
					beginGameModeItem = static_cast<GameModeItems>(accountGameModeItems);
					textGameModeIter->setFillColor(sf::Color::Cyan);
					--textGameModeIter;
					textGameModeIter->setFillColor(sf::Color::Green);
				}
				break;

			case sf::Keyboard::S:
				if (beginGameModeItem < GameModeItems::isPortalEnable)
				{
					Playback(gameResouces.menuHover, gameSettings);
					++accountGameModeItems;
					beginGameModeItem = static_cast<GameModeItems>(accountGameModeItems);
					textGameModeIter->setFillColor(sf::Color::Cyan);
					++textGameModeIter;
					textGameModeIter->setFillColor(sf::Color::Green);
				}
				break;
			case sf::Keyboard::Enter:
				Playback(gameResouces.menuEnter, gameSettings);
				switch (beginGameModeItem)
				{
				case Roguelike::UIGameModes::isMoveObstacle:
					gameSettings.gameMode.isMoveObstacle = !gameSettings.gameMode.isMoveObstacle;
					break;
				case Roguelike::UIGameModes::isPortalEnable :
					gameSettings.gameMode.isPortalEnable = !gameSettings.gameMode.isPortalEnable;
					break;
				default:
					break;
				}
				SetRectangleShape(checkMoveObstacle, { 20.f, 20.f }, (bool)gameSettings.gameMode.isMoveObstacle ? sf::Color::Cyan : sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 465.f, 270.f },
					(bool)gameSettings.gameMode.isMoveObstacle ? sf::Color(25, 25, 25, 255) : sf::Color::Cyan, 2.f);
				SetRectangleShape(checkPortal, { 20.f, 20.f }, (bool)gameSettings.gameMode.isPortalEnable ? sf::Color::Cyan : sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 465.f, 300.f },
					(bool)gameSettings.gameMode.isPortalEnable ? sf::Color(25, 25, 25, 255) : sf::Color::Cyan, 2.f);

			case sf::Keyboard::Escape:
				return true;
			default:
				break;
			}
		return false;
	}

	void UIGameModes::Draw(sf::RenderWindow& window)
	{
			window.draw(gameModeBackground);
			window.draw(textHeader); 
			window.draw(checkMoveObstacle);
			window.draw(checkPortal);
			for (std::list <sf::Text>::iterator drawTextMenuIter = listTextGameModeItems.begin(); drawTextMenuIter != listTextGameModeItems.end(); ++drawTextMenuIter)
			{
				window.draw(*drawTextMenuIter);
			}
	}
}