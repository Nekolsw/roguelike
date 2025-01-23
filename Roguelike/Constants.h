#pragma once
#include <SFML/Graphics.hpp>
namespace Roguelike 
{
	const std::string RESOURCES_PATH = "Resources/\\";

	//Game constants
	const sf::Vector2f WINDOW_SIZE = { 1280.f, 720.f };
	const  sf::Vector2f DISTANCE_BETWEEN_BRICKS = { 79.f, 35.f };
	const float PAUSE_LENGHT_START = 2.f;
	const int TEXT_SCORE_SIZE = 40.f;
}
