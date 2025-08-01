#include "pch.h"

#include "Engine.h"

#include "GameWorld.h"
#include "RenderSystem.h"

#include <iostream>

namespace XYZEngine {
Engine* Engine::Instance() {
    static Engine instance;
    return &instance;
}

Engine::Engine() {
    unsigned int seed = (unsigned int)time(nullptr);
    srand(seed);
}

void Engine::Run() {
    // Configuring the logger
    auto logger = std::make_shared<Logger>();
    logger->addSink(std::make_shared<ConsoleSink>());
    logger->addSink(std::make_shared<FileSink>("log.txt"));
    LoggerRegistry::getInstance().registerLogger("global", logger);
    LoggerRegistry::getInstance().setDefaultLogger(logger);

    sf::Clock gameClock;
    sf::Event event;

    while (RenderSystem::Instance()->GetMainWindow().isOpen()) {
        sf::Time dt = gameClock.restart();
        float deltaTime = dt.asSeconds();

        while (RenderSystem::Instance()->GetMainWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                RenderSystem::Instance()->GetMainWindow().close();
            }
        }

        if (!RenderSystem::Instance()->GetMainWindow().isOpen()) {
            break;
        }

        RenderSystem::Instance()->GetMainWindow().clear();

        GameWorld::Instance()->Update(deltaTime);
        GameWorld::Instance()->FixedUpdate(deltaTime);
        GameWorld::Instance()->Render();
        GameWorld::Instance()->LateUpdate();

        RenderSystem::Instance()->GetMainWindow().display();
    }
}
}  // namespace XYZEngine