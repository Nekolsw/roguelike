#pragma once

#include "ColliderComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"

#include <SFML/Graphics/Sprite.hpp>

namespace XYZEngine {
class SpriteColliderComponent : public ColliderComponent {
   public:
    SpriteColliderComponent(GameObject* gameObject);
    ~SpriteColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace XYZEngine
