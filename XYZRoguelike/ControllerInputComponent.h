#pragma once
#include "InputComponent.h"
#include "AttackComponent.h"
namespace XYZRoguelike
{
	class ControllerInputComponent : public XYZEngine::Component
	{
	public:
		ControllerInputComponent(std::shared_ptr<XYZEngine::GameObject> gameObject);
	private:
		void Update(float deltaTime) override;
		void Render() override;
		std::shared_ptr<XYZEngine::InputComponent> input;
		std::shared_ptr<XYZRoguelike::AttackComponent> attackComponent;
	};

}