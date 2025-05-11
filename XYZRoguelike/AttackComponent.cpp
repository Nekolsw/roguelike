#include "AttackComponent.h"
#include "Vector.h"
namespace XYZRoguelike
{
	AttackComponent::AttackComponent(XYZEngine::GameObject* gameObject) : Component(gameObject) 
	{
		input = gameObject->GetComponent<XYZEngine::InputComponent>();
		transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		weapon = gameObject->GetComponent<XYZEngine::Weapon>();

		if (input == nullptr)
		{
			std::cout << "Need input component for movement" << std::endl;
			gameObject->RemoveComponent(this);
		}
	}

	void AttackComponent::Update(float deltaTime)
	{
		if (input->GetVerticalAxis() != 0.f)
		{
			lastVerticalAxis = input->GetVerticalAxis();
			lastHorizontalAxis = 0.f;
		}
		if (input->GetHorizontalAxis() != 0.f)
		{
			lastHorizontalAxis = input->GetHorizontalAxis();

			lastVerticalAxis = 0.f;
		}
		if (input->GetSpaceBarPressed()) 
		{
			previousPosition = transform->GetWorldPosition();
			float angle = 0.f;
			if (lastHorizontalAxis < 0.f) 
			{
				angle = 180.f;
			}
			else if (lastHorizontalAxis > 0.f)
			{
				angle = 0.f;
			}
			else if (lastVerticalAxis != 0.f) 
			{
				angle = 90.f * lastVerticalAxis;
			}
			weapon->Attack(previousPosition, 40.f, angle);
		}
	}

	void AttackComponent::Render()
	{
	}
	
}