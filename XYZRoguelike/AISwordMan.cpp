#include "AISwordMan.h"
namespace XYZRoguelike
{
	AISwordMan::AISwordMan(XYZEngine::GameObject* gameObject) : XYZEngine::AIMovementComponent(gameObject)
	{
		transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
	}
	void AISwordMan::Update(float deltaTime)
	{
		XYZEngine::Vector2Df positionAI = transformSelf->GetWorldPosition();
		float distanceFromTarget = positionAI.CalculateDistance(transformTarget->GetWorldPosition());
		bool isTargetInRadius = distanceFromTarget <= viewingRadius && distanceFromTarget >= meleeAttackRadius;
		if (transformTarget != nullptr && isTargetInRadius)
		{
			XYZEngine::Vector2Df direction = transformTarget->GetWorldPosition() - transformSelf->GetWorldPosition();
			direction = direction.Normalize();

			transformSelf->MoveBy(speed * deltaTime * XYZEngine::Vector2Df{ direction.x, direction.y });
			transformSelf->RotateTo(transformSelf->GetWorldPosition(), transformTarget->GetWorldPosition());

			acceleration = transformSelf->GetWorldPosition() - previousPosition;
			previousPosition = transformSelf->GetWorldPosition();
			
		}

		else if (distanceFromTarget <= meleeAttackRadius && transformTarget != nullptr)
		{
			float angle = transformSelf->RotateTo(transformSelf->GetWorldPosition(), transformTarget->GetWorldPosition());
			sword->Attack(previousPosition, offsetSword, angle);
				
		}
	}
	void AISwordMan::Render()
	{
		AIMovementComponent::Render();
	}
	void AISwordMan::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}
	void AISwordMan::SetTarget(XYZEngine::GameObject* gameObject)
	{
		transformTarget = gameObject->GetComponent<XYZEngine::TransformComponent>();
	}
	void AISwordMan::AddWeapon(XYZEngine::Weapon* weapon)
	{
		sword = weapon;
	}
	void AISwordMan::ClearTarget()
	{
		transformTarget = nullptr;
	}
	float AISwordMan::GetSpeed() const
	{
		return speed;
	}
	float AISwordMan::GetAccelerationSquared() const
	{
		return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
	}
}