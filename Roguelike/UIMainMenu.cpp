#include "UIMainMenu.h"
#include "KeyBindings.h"
#pragma warning(disable : 4996)

namespace Roguelike
{
	void UIMainMenu::InitializedMainMenu(sf::Font& font)
	{
		SetTextScreen(textHeader, "Menu", 48, sf::Color::Cyan, font, { 650.f, 190.f }, { 0.5f, 0.5f });
		SetTextScreen(text, "Start", 36, sf::Color::Green, font, { 650.f, 280.f }, { 0.5f, 0.5f });
		listTextMenuItems.push_back(text);
		SetTextScreen(text, "Settings", 36, sf::Color::Cyan, font, { 650.f, 330.f }, { 0.5f, 0.5f });
		listTextMenuItems.push_back(text);
		SetTextScreen(text, "Exit", 36, sf::Color::Cyan, font, { 650.f, 380.f }, { 0.5f, 0.5f });
		listTextMenuItems.push_back(text);
		beginMenuItem = MenuItems::StartPLaying;
		textMenuIter = listTextMenuItems.begin();
		SetRectangleShape(menuBackground, { 400.f, 500.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 443.f, 160.f }, sf::Color::Cyan, 1.f);
		uiMenuItem.uiSettings.InitializedSettings(font);
	}
	void UIMainMenu::Playback(sf::SoundBuffer& buffer, GameSettings& gameSettings)
	{
		if (gameSettings.isPlaySound)
		{
			soundGame.setBuffer(buffer);
			soundGame.play();
		}
	}
	bool UIMainMenu::ChoiceItemMenu(sf::Window& window, GameSettings& gameSettings, GameResources& gameResources)
	{
		if (!isMenuItemSelected)
		{
			switch (KeyBindings::Instance().GetKeyPressed())
			{
			case sf::Keyboard::W:
				if (beginMenuItem > MenuItems::StartPLaying)
				{
					Playback(gameResources.menuHover, gameSettings);
					--accountMenuItems;
					beginMenuItem = static_cast<MenuItems>(accountMenuItems);
					textMenuIter->setColor(sf::Color::Cyan);
					--textMenuIter;
					textMenuIter->setColor(sf::Color::Green);
				}
				break;

			case sf::Keyboard::S:
				if (beginMenuItem < MenuItems::Exit)
				{
					Playback(gameResources.menuHover, gameSettings);
					++accountMenuItems;
					beginMenuItem = static_cast<MenuItems>(accountMenuItems);
					textMenuIter->setColor(sf::Color::Cyan);
					++textMenuIter;
					textMenuIter->setColor(sf::Color::Green);
				}
				break;
			case sf::Keyboard::Enter:
				Playback(gameResources.menuEnter, gameSettings);
				isMenuItemSelected = true;
			default:
				break;
			}
		}
		else if (isMenuItemSelected) 
		{
			switch (beginMenuItem)
			{
			case Roguelike::UIMainMenu::StartPLaying:
				isMenuItemSelected = false;
				return true;
				break;
			case Roguelike::UIMainMenu::Settings:
				uiMenuItem.uiSettings.ChoiceSettings(gameSettings, gameResources);
				break;
			case Roguelike::UIMainMenu::Exit:
				window.close();
				break;
			default:
				break;
			}
		}

		if (KeyBindings::Instance().GetKeyPressed() == KeyBindings::Instance().GetKey().keyEscape)
		{
			isMenuItemSelected = false;
		}
		
		return false;
	}

	void UIMainMenu::DrawMainMenu(sf::RenderWindow& window, sf::Font& font)
	{
		if (!isMenuItemSelected)
		{
			window.draw(menuBackground);
			window.draw(textHeader);
			for (std::list <sf::Text>::iterator drawTextMenuIter = listTextMenuItems.begin(); drawTextMenuIter != listTextMenuItems.end(); ++drawTextMenuIter)
			{
				window.draw(*drawTextMenuIter);
			}
		}
		else 
		{
			switch (beginMenuItem)
			{
			case Roguelike::UIMainMenu::Settings:
				uiMenuItem.uiSettings.DrawSettings(window);
				break;
			default:
				break;
			}
		}
	}
	


}
