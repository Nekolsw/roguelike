#pragma once
#include "AIMovementComponent.h"
#include "Weapon.h"
namespace XYZRoguelike
{
	class AISwordMan : public XYZEngine::AIMovementComponent
	{
	public:
		AISwordMan(XYZEngine::GameObject* gameObject);
		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		void SetTarget(XYZEngine::GameObject* gameObject);
		void AddWeapon(XYZEngine::Weapon* weapon);
		void ClearTarget();
		float GetSpeed() const;
		float GetAccelerationSquared() const;

	private:
		XYZEngine::TransformComponent* transformSelf;
		XYZEngine::TransformComponent* transformTarget = nullptr;
		XYZEngine::Weapon* sword = nullptr;
		float speed = 20.f;
		float viewingRadius = 300.f;
		float meleeAttackRadius = 70.f;
		XYZEngine::Vector2Df previousPosition = { 0, 0 };
		XYZEngine::Vector2Df acceleration = { 0, 0 };
		float offsetSword = 40.f;
	};

}