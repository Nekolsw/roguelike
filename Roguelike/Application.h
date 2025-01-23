#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
namespace Roguelike
{
	class Application
	{
	private:
		Application();

		~Application();
		int seed = (int)time(nullptr);
		//Game initialized
		Game game;
		sf::Clock gameClock;
		void StartGame();
	public:
		Application(const Application& application) = delete;
		Application& operator= (const Application&) = delete;

		static Application& Instance();


	};
}

