#pragma once
#include <memory>

#include "SFML/Graphics.hpp"

namespace XYZRoguelike {
class Colladiable {
   protected:
    virtual void OnHit() = 0;

   public:
    virtual bool CheckCollision(std::shared_ptr<Colladiable> collidable) {
        if (GetCollision(collidable)) {
            OnHit();
            collidable->OnHit();
            return true;
        }
        return false;
    }

    virtual bool GetCollision(
        std::shared_ptr<Colladiable> collidable) const = 0;
};
}  // namespace XYZRoguelike