#pragma once
#include "VectorMain.h"
#include "Constants.h"
#include "SpriteObject.h"
#include "Platform.h"
#include "BaseBrick.h"
#include "ProtectedBrick.h"
#include "Resources.h"
namespace Roguelike
{
	class Ball : public SpriteObject
	{
	private:
		sf::Vector2f direction;
		GameResources resources;
		sf::Texture ballTexture, ballTextureDamage_1, ballTextureDamage_2, ballTextureDamage_3, ballTextureDestroy;
		float radius = BALL_RADIUS;
		float durationFireBallBonus = 0.f;
		int repeatAttemps = REPEATED_ATTEMPS;
		float collisionBall = radius / 2;
		void MirroringDirectionX();
		void MirroringDirectionY();
		sf::Text textBall, textPlatform;
	public:
		bool Collision(SpriteObject& walls);
		bool IsBallLosing(SpriteObject& walls);
		bool Collision(Platform& platform, SpriteObject& ball);
		bool Collision(BaseBrick& brick, SpriteObject& ball);
		void Update(float& deltaTime);
		void IncreaseSpeed();
		void Initialization(sf::Vector2f newPosition, GameResources& resources, sf::Color color);
	};
}

