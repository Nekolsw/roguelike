#include "Game.h"
#include "GameSettings.h"
#include "BaseBonus.h"
namespace Roguelike
{
	void Game::RunApplication(GameStruct& gameStruct)
	{

		InitializingResources(gameStruct.resources);
		GetUIManager().InitializationUIManager();
		gameStruct.ball.Initialization({400.f, 400.f}, gameStruct.resources, sf::Color::Red);
		gameStruct.walls.Initialization({ 1280.f, 720.f }, WINDOW_SIZE, gameStruct.resources.wallTexture, sf::Color::Cyan);
		gameStruct.constructionBricks.Construction(gameStruct.resources);
		gameStruct.platform.Initialization({ 640.f, 620.f }, gameStruct.resources, sf::Color::Cyan);
	}

	UIManager& Game::GetUIManager()
	{
		static UIManager uiManager = UIManager();
		return uiManager;
	}

	void Game::RestartGame(GameStruct& gameStruct)
	{
		GetUIManager().gameState = GetUIManager().Pause;
		gameStruct.constructionBricks.Restructuring(gameStruct.resources);
		gameStruct.ball.Initialization({ 400.f, 400.f }, gameStruct.resources, sf::Color::Red);
		gameStruct.brickDestroyed = 0;
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
				gameStruct.ball.Update(deltaTime);
				gameStruct.ball.Collision(gameStruct.walls);
				if (gameStruct.ball.IsBallLosing(gameStruct.walls)) 
				{
					GetUIManager().IsGameWon(false);
				}
				gameStruct.ball.Collision(gameStruct.platform, gameStruct.ball);
				gameStruct.platform.Update(deltaTime);

				UpdateBrick(gameStruct);
				UpdateGameBonus(gameStruct, deltaTime);
				

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
		gameStruct.ball.Draw(window);
		gameStruct.walls.Draw(window);
		gameStruct.platform.Draw(window);
		gameStruct.constructionBricks.Draw(window);
		gameStruct.constructionBonuses.Draw(window);
		GetUIManager().DrawUI(window);
	}

	void Game::UpdateBrick(GameStruct& gameStruct)
	{
		for (auto& row : gameStruct.constructionBricks.GetBricks())
		{
			if (gameStruct.ball.Collision(*row, gameStruct.ball))
			{
				row->Punch(gameStruct.durationGlassBlockBonus > 0.f);
				if (row->isDestroyed())
				{
					++gameStruct.brickDestroyed;
					GetUIManager().AddScore(row->GetTypeBrick());
					gameStruct.constructionBonuses.CreateBonus(row->GetPosition(), gameStruct.resources);
				}
				if (gameStruct.brickDestroyed == (BRICK_FOR_WIDTH * BRICK_FOR_HEIGHT))
				{
					GetUIManager().IsGameWon(true);
				}
			}

		}
		for (auto it = gameStruct.constructionBricks.GetBricks().begin(); it != gameStruct.constructionBricks.GetBricks().end();)
		{
			if (it->get()->isDestroyed())
			{
				it = gameStruct.constructionBricks.GetBricks().erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void Game::UpdateGameBonus(GameStruct& gameStruct, float& deltaTime)
	{

		if (gameStruct.durationGlassBlockBonus > 0.f)
		{
			gameStruct.durationGlassBlockBonus = gameStruct.durationGlassBlockBonus - (1.0f * deltaTime);
		}

		else 
		{
			gameStruct.durationGlassBlockBonus = 0;
		}

		for (auto& row : gameStruct.constructionBonuses.GetBonuses())
		{
			row->Update(deltaTime);
			if (gameStruct.platform.Collision(*row, gameStruct.platform))
			{
				row->DestroyBonus();
				switch (row->GetTypeBonus())
				{
				case BaseBonus::TypeBonus::FireBall:
					gameStruct.ball.IncreaseSpeed();
					break;
				case BaseBonus::TypeBonus::GlassBrick:
					gameStruct.durationGlassBlockBonus = DURATION_BONUSES;
					break;
				case BaseBonus::TypeBonus::IncreasingPlatform:
					gameStruct.platform.TookSizeIncreaseBonus();
					break;
				default:
					break;
				}
			}
			
		}

		for (auto it = gameStruct.constructionBonuses.GetBonuses().begin(); it != gameStruct.constructionBonuses.GetBonuses().end();)
		{
			if (it->get()->isDestroyed())
			{
				it = gameStruct.constructionBonuses.GetBonuses().erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}