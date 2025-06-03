#include "pch.h"
#include "AIMovementComponent.h"

XYZEngine::AIMovementComponent::AIMovementComponent(std::shared_ptr<GameObject> gameObject)
	: Component(gameObject)
{
	transformSelf = gameObject->GetComponent<TransformComponent>();
}

void XYZEngine::AIMovementComponent::Update(float deltaTime)
{
	Vector2Df positionAI = transformSelf->GetWorldPosition();
	float distanceFromTarget = positionAI.CalculateDistance(transformTarget->GetWorldPosition());
	bool isTargetInRadius = distanceFromTarget <= viewingRadius;
	if (transformTarget != nullptr && isTargetInRadius)
	{
		Vector2Df direction = transformTarget->GetWorldPosition() - transformSelf->GetWorldPosition();
		direction = direction.Normalize();

		transformSelf->MoveBy(speed * deltaTime * Vector2Df{ direction.x, direction.y });
		acceleration = transformSelf->GetWorldPosition() - previousPosition;
		previousPosition = transformSelf->GetWorldPosition();

	}

}

void XYZEngine::AIMovementComponent::Render()
{

}

void XYZEngine::AIMovementComponent::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

void XYZEngine::AIMovementComponent::SetTarget(std::shared_ptr<GameObject> gameObject)
{
	transformTarget = gameObject->GetComponent<XYZEngine::TransformComponent>();
}

void XYZEngine::AIMovementComponent::ClearTarget()
{
	transformTarget = nullptr;
}

float XYZEngine::AIMovementComponent::GetSpeed() const
{
	return speed;
}

float XYZEngine::AIMovementComponent::GetAccelerationSquared() const
{
	return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}