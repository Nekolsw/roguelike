#pragma once
#include "TransformComponent.h"
#include "Weapon.h"
namespace XYZRoguelike
{
	class AttackComponent : public XYZEngine::Component
	{
	public:
		AttackComponent(std::shared_ptr<XYZEngine::GameObject> gameObject);
		void Attack();

	private:
		void Update(float deltaTime) override;
		void Render() override;
		std::shared_ptr<XYZEngine::Weapon> weapon;
		float delayAttack = 0.f;
		float attackSpeed = 0.f;
	};

}