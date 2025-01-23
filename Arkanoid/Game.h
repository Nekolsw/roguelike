#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "SpriteObject.h"
#include "Ball.h"
#include "Platform.h"
#include "ConstructionBricks.h"
#include "ConstructionBonus.h"
#include "KeyBindings.h"
#include "Resources.h"
#include "UIManager.h"

namespace Arkanoid
{
	class Game
	{
	private:
		struct GameStruct
		{
			GameResources resources;
			Ball ball; 
			ConstructionBonus constructionBonuses;
			ConstructionBricks constructionBricks;
			float timeSinceGameStart = 0;
			float durationGlassBlockBonus = 0;
			Platform platform;
			SpriteObject walls = {};
			int brickDestroyed = 0;
		};
	public:
		GameStruct mainGameStruct;
		void UpdateGameBonus(GameStruct& gameStruct, float& deltaTime);
		UIManager& GetUIManager();
		void RunApplication(GameStruct& gameStruct);
		void UpdateBrick(GameStruct& gameStruct);
		void RestartGame(GameStruct& gameStruct);
		void UpdateGame(GameStruct& gameStruct, float deltaTime, sf::RenderWindow& window); 
		void UpdateEvent(GameStruct& gameStruct, sf::Event& event, sf::Window& window, float deltaTime);
		void DrawGame(GameStruct& gameStruct, sf::RenderWindow& window);
	};
}
