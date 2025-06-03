#pragma once
#include "GameObject.h"
namespace XYZEngine
{
	class AIMovementComponent : public Component
	{
	public:
		AIMovementComponent(std::shared_ptr<GameObject> gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		void SetTarget(std::shared_ptr<GameObject> gameObject);
		void ClearTarget();
		float GetSpeed() const;
		float GetAccelerationSquared() const;
	private:
		std::shared_ptr<TransformComponent> transformSelf;
		std::shared_ptr<TransformComponent> transformTarget = nullptr;

		float speed = 20.f;
		float viewingRadius = 300.f;
		Vector2Df previousPosition = { 0, 0 };
		Vector2Df acceleration = { 0, 0 };
	};

}