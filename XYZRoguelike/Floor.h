#pragma once

#include <GameWorld.h>
#include <ResourceSystem.h>
#include <SpriteRendererComponent.h>

#include "GameObject.h"

namespace XYZRoguelike {
class Floor {
   public:
    Floor(const XYZEngine::Vector2Df position, int textureMapIndex);

   private:
       std::shared_ptr<XYZEngine::GameObject> gameObject;
};
}  // namespace XYZRoguelike
