#pragma once
#include "GameObject.h"
#include "InputComponent.h"

namespace XYZEngine
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(std::shared_ptr<GameObject> gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetSpeed(float newSpeed);
		void SetDirectionalRotation(bool newDirectionalRotation);
		float GetSpeed() const;
		float GetAccelerationSquared() const;
	private:
		std::shared_ptr<InputComponent> input;
		std::shared_ptr<TransformComponent> transform;

		float lastHorizontalAxis = 0.f, lastVerticalAxis = 0.f;
		float speed = 0.f;
		float angle = 0.f;
		bool directionalRotation;
		Vector2Df previousPosition = { 0.f, 0.f };
		Vector2Df acceleration = { 0.f, 0.f };
	};
}

