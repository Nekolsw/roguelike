#include "Game.h"
#include "GameSettings.h"


namespace Roguelike
{ /*
	void Game::RunApplication(GameStruct& gameStruct)
	{

		InitializingResources(gameStruct.resources);
		GetUIManager().InitializationUIManager();
		gameStruct.walls.Initialization({ 1280.f, 720.f }, WINDOW_SIZE, gameStruct.resources.wallTexture, sf::Color::Cyan);
	}

	UIManager& Game::GetUIManager()
	{
		static UIManager uiManager = UIManager();
		return uiManager;
	}

	void Game::RestartGame(GameStruct& gameStruct)
	{
		GetUIManager().gameState = GetUIManager().Pause;
		GetUIManager().gameState = GetUIManager().Playing;
	}
	

	void Game::UpdateGame(GameStruct& gameStruct, float deltaTime, sf::RenderWindow& window)
	{
		if (GetUIManager().gameState == GetUIManager().Playing)
		{
			if (gameStruct.timeSinceGameStart <= PAUSE_LENGHT_START)
			{
				gameStruct.timeSinceGameStart += deltaTime;
			}
			else
			{
				

			}
		}
		if (GetUIManager().gameState == GetUIManager().Restart)
		{
			RestartGame(gameStruct);
		}
	}

	void Game::UpdateEvent(GameStruct& gameStruct, sf::Event& event, sf::Window& window, float deltaTime)
	{
		KeyBindings::Instance().PressedKey(event);
		GetUIManager().UpdateEvent(event, window);
	}

	void Game::DrawGame(GameStruct& gameStruct, sf::RenderWindow& window)
	{
		gameStruct.walls.Draw(window);
		GetUIManager().DrawUI(window);
	}
		*/
}