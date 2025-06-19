#pragma once
#include "AIMovementComponent.h"
#include "AttackComponent.h"
#include "Weapon.h"

#include <cassert>
namespace XYZRoguelike {
class AICreeper : public XYZEngine::AIMovementComponent {
   public:
    AICreeper(XYZEngine::GameObject* gameObject);
    void Update(float deltaTime) override;

   private:
    AttackComponent* attackComponent = nullptr;
    float meleeAttackRadius = 35.f;
    float preAttackDelay = 1.5f;
    float gapBetweenMoving = 1.f;
    float timeMoving = 1.f;
    float delayAttack = 1.f;
    bool isExplosionStarted = false;

    const float GAP_BETWEEN_MOVING = 1.5f;
    const float TIME_MOVING = 1.f;
};
}  // namespace XYZRoguelike