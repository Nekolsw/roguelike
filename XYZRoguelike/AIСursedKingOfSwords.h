#pragma once
#include "AIMovementComponent.h"
#include "AttackComponent.h"
namespace XYZRoguelike
{
	class AI�ursedKingOfSwords : public XYZEngine::AIMovementComponent 
	{
   public:
		AI�ursedKingOfSwords(XYZEngine::GameObject* gameObject);
		void Update(float deltaTime) override;
   private:
    float meleeAttackRadius = 90.f;
    float preAttackDelay = 1.0f;
    float offsetSword = 60.f;
	};
}  // namespace XYZRoguelike