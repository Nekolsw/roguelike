// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"
#include "Logger.h"

using namespace XYZRoguelike;

int main()
{
	//Configuring the logger
	auto logger = std::make_shared <Logger>();
	logger->addSink(std::make_shared <ConsoleSink>());
	logger->addSink(std::make_shared <FileSink>("log.txt"));
	LoggerRegistry::getInstance().registerLogger("global", logger);
	LoggerRegistry::getInstance().setDefaultLogger(logger);

	
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike"));

	XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ballw.png");
	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("Walls", "Resources/MapsTexture/Wallsw.png", { 16, 16 }, 48, false);

	ResourceSystem::Instance()->LoadSound("BackgroundMusic", "Resources/Music/BackgroundMusic.wav");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}
