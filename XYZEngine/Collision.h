#pragma once

#include <SFML/Graphics.hpp>

namespace XYZEngine {
class ColliderComponent;
struct Collision {
   public:
    Collision(ColliderComponent* newFirst, ColliderComponent* newSecond,
              sf::FloatRect newCollisionRect)
        : first(newFirst),
          second(newSecond),
          collisionRect(newCollisionRect) {};

    ColliderComponent* first;
    ColliderComponent* second;

   private:
    sf::FloatRect collisionRect;
};
}  // namespace XYZEngine