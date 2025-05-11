#pragma once
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Weapon.h"
namespace XYZRoguelike
{
	class AttackComponent : public XYZEngine::Component
	{
	public:
		AttackComponent(XYZEngine::GameObject* gameObject);

	private:
		void Update(float deltaTime) override;
		void Render() override;
		XYZEngine::InputComponent* input;
		XYZEngine::TransformComponent* transform;
		XYZEngine::Weapon* weapon;

		XYZEngine::Vector2Df previousPosition = { 0, 0 };
		float lastHorizontalAxis = 0.f, lastVerticalAxis = 0.f;
	};

}