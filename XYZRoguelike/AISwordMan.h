#pragma once
#include "AIMovementComponent.h"
#include "AttackComponent.h"
#include "Weapon.h"
#include <cassert>
namespace XYZRoguelike
{
	class AISwordMan : public XYZEngine::AIMovementComponent
	{
	public:
		AISwordMan(std::shared_ptr<XYZEngine::GameObject> gameObject);
		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		void SetTarget(std::shared_ptr<XYZEngine::GameObject> gameObject);
		void ClearTarget();
		float GetSpeed() const;
		float GetAccelerationSquared() const;

	private:
		std::shared_ptr<XYZEngine::TransformComponent> transformSelf;
		std::shared_ptr<XYZEngine::TransformComponent> transformTarget = nullptr;
		std::shared_ptr<XYZRoguelike::AttackComponent> attackComponent = nullptr;
		float speed = 20.f;
		float viewingRadius = 300.f;
		float meleeAttackRadius = 70.f;
		XYZEngine::Vector2Df previousPosition = { 0, 0 };
		XYZEngine::Vector2Df acceleration = { 0, 0 };
		float offsetSword = 40.f;
	};

}