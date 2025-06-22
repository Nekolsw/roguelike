#pragma once
#include "GameObject.h"

#include <GameWorld.h>
#include <ResourceSystem.h>

class Wall {
   public:
    Wall(const XYZEngine::Vector2Df position, int indexTexture);

   private:
    XYZEngine::GameObject* gameObject;
};
