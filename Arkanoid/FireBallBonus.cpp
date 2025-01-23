#include "FireBallBonus.h"
#include "GameMath.h"
namespace Arkanoid
{
	void FireBallBonus::Initialization(GameResources& resources)
	{
		BaseBonus::typeBonus = BaseBonus::TypeBonus::FireBall;
		SpriteObject::Initialization({0, 0}, BONUS_RADIUS, resources.fireBallBonusTexture, sf::Color().White);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	}
}