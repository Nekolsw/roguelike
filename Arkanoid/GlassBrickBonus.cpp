#include "GlassBrickBonus.h"
#include "GameMath.h"
namespace Arkanoid
{
	void GlassBrickBonus::Initialization(GameResources& resources)
	{
		BaseBonus::typeBonus = BaseBonus::TypeBonus::GlassBrick;
		SpriteObject::Initialization({ 0, 0 }, BONUS_RADIUS, resources.glassBrickBonusTexture, sf::Color().White);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	}
}