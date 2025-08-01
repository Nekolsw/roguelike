#pragma once

#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

#include <iostream>
#include <map>

namespace XYZEngine {
class PhysicsSystem {
   public:
    static PhysicsSystem* Instance();

    void Update();

    float GetFixedDeltaTime() const;
    void Subscribe(ColliderComponent* collider);
    void Unsubscribe(ColliderComponent* collider);

   private:
    PhysicsSystem() {}
    ~PhysicsSystem() {}

    PhysicsSystem(PhysicsSystem const&) = delete;
    PhysicsSystem& operator=(PhysicsSystem const&) = delete;

    std::vector<ColliderComponent*> colliders;
    std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

    float fixedDeltaTime = 0.02f;
};
}  // namespace XYZEngine