#include "IncreasingPlatformBonus.h"
#include "Constants.h"
namespace Roguelike
{
	void IncreasingPlatformBonus::Initialization(GameResources& resources)
	{
		BaseBonus::typeBonus = BaseBonus::TypeBonus::IncreasingPlatform;
		SpriteObject::Initialization({ 0, 0 }, BONUS_RADIUS, resources.IncreasingPlatformBonusTexture, sf::Color().White);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	}
}