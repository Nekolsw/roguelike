#pragma once
#include "Component.h"
#include "GameObject.h"

#include <SpriteColliderComponent.h>
namespace XYZRoguelike {
class Weapon : public XYZEngine::Component {
   public:
    Weapon(XYZEngine::GameObject* gameObject)
        : XYZEngine::Component(gameObject) {};
    virtual XYZEngine::GameObject* GetGameObject() = 0;
    virtual void SetActive(bool OnActive) = 0;
    virtual void DamageCollision(XYZEngine::Collision collision) = 0;

   protected:
};
}  // namespace XYZRoguelike