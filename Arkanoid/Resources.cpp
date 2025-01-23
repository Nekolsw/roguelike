#include "Resources.h"
namespace Roguelike
{
	void InitializingResources(GameResources& resources)
	{
		//Load image
		assert(resources.ballTexture.loadFromFile(RESOURCES_PATH + "Ball.png"));
		assert(resources.ballTextureDamage_1.loadFromFile(RESOURCES_PATH + "BallDamageLow.png"));
		assert(resources.ballTextureDamage_2.loadFromFile(RESOURCES_PATH + "BallDamageMedium.png"));
		assert(resources.ballTextureDamage_3.loadFromFile(RESOURCES_PATH + "BallDamageHight.png"));
		assert(resources.ballTextureDestroy.loadFromFile(RESOURCES_PATH + "BallDestroyed.png"));

		assert(resources.wallTexture.loadFromFile(RESOURCES_PATH + "Wall_2.png"));
		assert(resources.platformTexture.loadFromFile(RESOURCES_PATH + "Platform.png"));
		assert(resources.brickClassicTexture.loadFromFile(RESOURCES_PATH + "BrickClassic.png"));
		assert(resources.brickProtectedTexture.loadFromFile(RESOURCES_PATH + "BrickProtected.png"));

		assert(resources.fireBallBonusTexture.loadFromFile(RESOURCES_PATH + "BonusFireBall.png"));
		assert(resources.glassBrickBonusTexture.loadFromFile(RESOURCES_PATH + "BonusGlassBrick.png"));
		assert(resources.IncreasingPlatformBonusTexture.loadFromFile(RESOURCES_PATH + "BonusSizePlatform.png"));


		//Load font
		assert(resources.fontText.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf"));

		//Load sound
		//assert(resources.snakeHit.loadFromFile(RESOURCES_PATH + "ClapApple.wav"));
		//assert(resources.playerDeath.loadFromFile(RESOURCES_PATH + "GameOverSound.wav"));
		//assert(resources.menuHover.loadFromFile(RESOURCES_PATH + "Theevilsocks__menu-hover.wav"));
		//assert(resources.menuEnter.loadFromFile(RESOURCES_PATH + "Timgormly__Enter.wav"));
	}




}