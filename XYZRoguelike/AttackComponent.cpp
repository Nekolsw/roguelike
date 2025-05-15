#include "AttackComponent.h"
#include "Vector.h"
namespace XYZRoguelike
{
	AttackComponent::AttackComponent(XYZEngine::GameObject* gameObject) : Component(gameObject) 
	{
		weapon = gameObject->GetComponent<XYZEngine::Weapon>();
	}

	void AttackComponent::Update(float deltaTime)
	{
		delayAttack -= 1.f * deltaTime;
		if (delayAttack <= 0.f)
		{
			weapon->SetActive(false);
			attackSpeed -= 1.f * deltaTime;
		}
	}

	void AttackComponent::Render()
	{
	}

	void AttackComponent::Attack()
	{
		if (delayAttack <= 0.f && attackSpeed <= 0.f)
		{
			delayAttack = 0.1f;
			attackSpeed = 2.f;
			weapon->SetActive(true);
		}
	}

	
}