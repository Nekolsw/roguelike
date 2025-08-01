#pragma once
#define NOMINMAX

#include "Logger.h"

#include "SFML/Graphics.hpp"

namespace XYZEngine {
class Engine {
   public:
    Engine(const Engine& app) = delete;
    Engine& operator=(const Engine&) = delete;

    static Engine* Instance();

    void Run();

   private:
    Engine();
    ~Engine() = default;
};
}  // namespace XYZEngine