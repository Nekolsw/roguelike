#pragma once

#include "Component.h"
#include "Vector.h"

#include <SFML/Window.hpp>

namespace XYZEngine {
class InputComponent : public Component {
   public:
    InputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;
    bool GetSpaceBarPressed() const;

   private:
    float horizontalAxis = 0.f;
    float verticalAxis = 0.f;
    bool isSpaceBarPressed = false;
};
}  // namespace XYZEngine