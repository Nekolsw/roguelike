#include "Application.h"
namespace Roguelike
{
	Application::Application()
	{
		StartGame();
	}
	Application::~Application()
	{

	}
	Application& Application::Instance()
	{

		static Application instance;
		return instance;
	}
	void Application::StartGame()
	{
		sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Roguelike");
		srand(seed);
		game.RunApplication(game.mainGameStruct);
		float lastTime = gameClock.getElapsedTime().asSeconds();
		while (window.isOpen())
		{
			// Calculate time delta
			float currentTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				game.UpdateEvent(game.mainGameStruct, event, window, deltaTime);
			}
			game.UpdateGame(game.mainGameStruct, deltaTime, window);
			window.clear();
			game.DrawGame(game.mainGameStruct, window);
			window.display();
		}
	}
}