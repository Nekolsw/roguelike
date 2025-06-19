#pragma once
#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "TransformComponent.h"

namespace XYZEngine {
class MovementComponent : public Component {
   public:
    MovementComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetSpeed(float newSpeed);
    float GetSpeed() const;
    float GetAccelerationSquared() const;

   private:
    InputComponent* input;
    TransformComponent* transform;

    float speed = 0;
    Vector2Df previousPosition = {0, 0};
    Vector2Df acceleration = {0, 0};
};
}  // namespace XYZEngine
