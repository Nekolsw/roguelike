#include "BaseBonus.h"

namespace Roguelike {

	void BaseBonus::Update(float& deltaTime)
	{
		objectSprite.setPosition(objectSprite.getPosition() + SPEED_FALL_BONUS * deltaTime);
	};

	BaseBonus::TypeBonus BaseBonus::GetTypeBonus()
	{
		return typeBonus;
	}
	void BaseBonus::DestroyBonus()
	{
		isDestroy = true;
	}
	
	bool BaseBonus::isDestroyed()
	{
		return isDestroy;
	}
}