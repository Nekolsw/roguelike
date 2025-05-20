#include "AISwordMan.h"
#include "Logger.h"
namespace XYZRoguelike
{
	AISwordMan::AISwordMan(XYZEngine::GameObject* gameObject) : XYZEngine::AIMovementComponent(gameObject)
	{
		transformSelf = gameObject->GetComponent<XYZEngine::TransformComponent>();
		attackComponent = gameObject->GetComponent<AttackComponent>();
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
			transformSelf->RotateTo(transformSelf->GetWorldPosition(), transformTarget->GetWorldPosition());
			attackComponent->Attack();
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
		assert(gameObject != nullptr && "A pointer to a gameObject for a target must not have a null value");
		transformTarget = gameObject->GetComponent<XYZEngine::TransformComponent>();
		LOG_INFO("Target AISwordMan: " + gameObject->GetName() + "\n");
	}
	void AISwordMan::ClearTarget()
	{
		transformTarget = nullptr;
		LOG_INFO("Target AISwordMan clear \n");
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