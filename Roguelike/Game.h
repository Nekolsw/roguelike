#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "SpriteObject.h"
#include "KeyBindings.h"
#include "Resources.h"
#include "UIManager.h"

namespace Roguelike
{
	class Game
	{
	private:
		struct GameStruct
		{
			GameResources resources;
			float timeSinceGameStart = 0;
			SpriteObject walls = {};
		};
	public:
		GameStruct mainGameStruct;
		UIManager& GetUIManager();
		void RunApplication(GameStruct& gameStruct);
		void RestartGame(GameStruct& gameStruct);
		void UpdateGame(GameStruct& gameStruct, float deltaTime, sf::RenderWindow& window); 
		void UpdateEvent(GameStruct& gameStruct, sf::Event& event, sf::Window& window, float deltaTime);
		void DrawGame(GameStruct& gameStruct, sf::RenderWindow& window);
	};
}
