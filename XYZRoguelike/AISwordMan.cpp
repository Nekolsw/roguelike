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
		if(objectTarget)
		{
			float distanceFromTarget = positionAI.CalculateDistance(objectTarget->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition());
			bool isTargetInRadius = distanceFromTarget <= viewingRadius && distanceFromTarget >= meleeAttackRadius;
			if (isTargetInRadius)
			{
				XYZEngine::Vector2Df direction = objectTarget->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition() - transformSelf->GetWorldPosition();
				direction = direction.Normalize();

				transformSelf->MoveBy(speed * deltaTime * XYZEngine::Vector2Df{ direction.x, direction.y });
				transformSelf->RotateTo(transformSelf->GetWorldPosition(), objectTarget->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition());

				acceleration = transformSelf->GetWorldPosition() - previousPosition;
				previousPosition = transformSelf->GetWorldPosition();

			}

			else if (distanceFromTarget <= meleeAttackRadius && objectTarget != nullptr)
			{
				transformSelf->RotateTo(transformSelf->GetWorldPosition(), objectTarget->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition());
				attackComponent->Attack();
			}
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
		objectTarget = gameObject;
		LOG_INFO("Target AISwordMan: " + gameObject->GetName() + "\n");
	}
	void AISwordMan::ClearTarget()
	{
		objectTarget = nullptr;
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