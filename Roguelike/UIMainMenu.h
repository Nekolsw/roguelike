#pragma once
#include <list>
#include <iterator>
#include "UIConstructor.h"
#include "UISettings.h"
#include "Resources.h"
namespace Roguelike
{
	class UIMainMenu
	{
		struct UIMenuItem 
		{
			UISettings uiSettings;
		};
		UIMenuItem uiMenuItem; 
		sf::Sound soundGame;
		sf::Text textHeader, text;
		sf::RectangleShape menuBackground;
		int accountMenuItems = 0;
	public: 
		bool isMenuItemSelected = false;
		enum MenuItems 
		{
			StartPLaying = 0, 
			Settings,
			Exit,
		};
		void InitializedMainMenu(sf::Font& font);
		void Playback(sf::SoundBuffer& buffer, GameSettings& gameSettings);
		bool ChoiceItemMenu(sf::Window& window, GameSettings& gameSettings, GameResources& gameResources);
		void DrawMainMenu(sf::RenderWindow& window, sf::Font& font);
	private:
		MenuItems beginMenuItem;
		std::list <sf::Text> listTextMenuItems;
		std::list <sf::Text>::iterator textMenuIter;
	};
}