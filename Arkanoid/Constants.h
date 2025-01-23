#pragma once
#include <SFML/Graphics.hpp>
namespace Arkanoid 
{
	const std::string RESOURCES_PATH = "Resources/\\";

	//Ball constants
	const float BALL_RADIUS = 30.f;
	const sf::Vector2f BALL_STANDART_SPEED = { 150.f, 150.f };
	const float BALL_COEFFICIENT_INCREASING_SPEED = 1.5f;
	const sf::Vector2f  LOSS_BALL_SPEED = { 0.05f, 0.05f }; // Returning the speed of the ball to its original speed
	const float MAX_BALL_SPEED = 500.f;
	const float ACCELETATION_PLATFORM_CONTACT = 300.f;

	//Brick constants
	const sf::Vector2f STARTING_POSITION_BRICK = { 48.f, 100.f };
	const sf::Vector2f BRICK_SIZE = { 70.f, 30.f };
	const int PROTECTED_BRICK_HOLDS_PUNCHES = 2;
	const int BRICK_FOR_WIDTH = 16;
	const int BRICK_FOR_HEIGHT = 3;

	//Platform constants
	const sf::Vector2f PLATFORM_STANDART_SIZE = { 200.f, 40.f };
	const sf::Vector2f PLATFORM_INCREASING_SIZE = { 300.f, 40.f };
	const float PLATFORM_SPEED = 300.f;

	//Bonus constants
	const sf::Vector2f SPEED_FALL_BONUS = { 0.f, 190.f };
	const float DURATION_BONUSES = 10.f;
	const  sf::Vector2f BONUS_RADIUS = { 60.f, 60.f };
	const int PROBABILITY_SPAWNING_BONUS = 100;

	//Game constants
	const int REPEATED_ATTEMPS = 4;
	const sf::Vector2f WINDOW_SIZE = { 1280.f, 720.f };
	const  sf::Vector2f DISTANCE_BETWEEN_BRICKS = { 79.f, 35.f };
	const float PAUSE_LENGHT_START = 2.f;

	//Record table constants
	const std::string RECORDS_TABLE_NAME = "Table Record";
	const int TEXT_SCORE_SIZE = 46;
}
