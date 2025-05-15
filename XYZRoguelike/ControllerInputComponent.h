#pragma once
#include "InputComponent.h"
#include "AttackComponent.h"
namespace XYZRoguelike
{
	class ControllerInputComponent : public XYZEngine::Component
	{
	public:
		ControllerInputComponent(XYZEngine::GameObject* gameObject);
	private:
		void Update(float deltaTime) override;
		void Render() override;
		XYZEngine::InputComponent* input;
		AttackComponent* attackComponent;
	};

}