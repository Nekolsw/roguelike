#include <SFML/Graphics.hpp>
#include "GameMath.h"
#include "SpriteObject.h"
#include "Ball.h"

namespace Arkanoid
{
	void Ball::Initialization(sf::Vector2f newPosition, GameResources& resources, sf::Color color)
	{
		ballTexture = resources.ballTexture;
		ballTextureDamage_1 = resources.ballTextureDamage_1;
		ballTextureDamage_2 = resources.ballTextureDamage_2;
		ballTextureDamage_3 = resources.ballTextureDamage_3;
		ballTextureDestroy = resources.ballTextureDestroy;
		repeatAttemps = REPEATED_ATTEMPS;
		SpriteObject::Initialization(newPosition, { radius, radius }, resources.ballTexture, color);
		SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
		direction = BALL_STANDART_SPEED;
	}

	void Ball::Update(float& deltaTime)
	{
		if (durationFireBallBonus > 0) 
		{
			durationFireBallBonus = durationFireBallBonus - (1.f * deltaTime);
		}
		else 
		{
			durationFireBallBonus = 0;
			objectSprite.setColor(sf::Color::Red);
			if (direction.x > BALL_STANDART_SPEED.x && direction.x > 0)
			{
				direction.x -= LOSS_BALL_SPEED.x;
			}
			if (direction.x < -BALL_STANDART_SPEED.x && direction.x < 0)
			{
				direction.x += LOSS_BALL_SPEED.x;
			}
			if (direction.y > BALL_STANDART_SPEED.y && direction.y > 0)
			{
				direction.y -= LOSS_BALL_SPEED.y;
			}
			if (direction.y < -BALL_STANDART_SPEED.y && direction.y < 0)
			{
				direction.y += LOSS_BALL_SPEED.y;
			}
		}
		objectSprite.setPosition(objectSprite.getPosition() + direction * deltaTime);
	}

	void Ball::IncreaseSpeed()
	{
		durationFireBallBonus = DURATION_BONUSES;
		objectSprite.setColor(sf::Color::Yellow);
		direction = direction * BALL_COEFFICIENT_INCREASING_SPEED;
	}

	void Ball::MirroringDirectionX()
	{
		direction.x = -direction.x;
	}
	void Ball::MirroringDirectionY()
	{
		direction.y = -direction.y;
	}

	bool Ball::Collision(SpriteObject& walls)
	{

		if (objectSprite.getPosition().x - collisionBall <= 0 && direction.x < 0)
		{
			MirroringDirectionX();
			return true;
		}

		if (objectSprite.getPosition().x + collisionBall >= walls.GetPosition().x && direction.x > 0)
		{
			MirroringDirectionX();
			return true;
		}

		if (objectSprite.getPosition().y - collisionBall <= 0 && direction.y < 0)
		{
			MirroringDirectionY();
			return true;
		}
		return false;
	}

	bool Ball::IsBallLosing(SpriteObject& walls)
	{
		float sizeDownTexture = 20.f;
		if (objectSprite.getPosition().y + collisionBall >= walls.GetPosition().y - sizeDownTexture && direction.y > 0 && repeatAttemps > 1)
		{
			MirroringDirectionY();
			--repeatAttemps;
			switch (repeatAttemps)
			{
			case 1:
				objectSprite.setTexture(ballTextureDamage_3);
				break;
			case 2:
				objectSprite.setTexture(ballTextureDamage_2);
				break;
			case 3:
				objectSprite.setTexture(ballTextureDamage_1);
				break;
			case 4:
				objectSprite.setTexture(ballTexture);
				break;
			default:
				break;
			}
		}
		if (objectSprite.getPosition().y + collisionBall > walls.GetPosition().y - sizeDownTexture && direction.y > 0)
		{
			objectSprite.setTexture(ballTextureDestroy);
			return true;
		}
		return false;
	}

	bool Ball::Collision(Platform& platform, SpriteObject& ball)
	{
		float dx = (float)fabs(platform.GetPosition().x - objectSprite.getPosition().x);
		float dy = (float)fabs(platform.GetPosition().y - objectSprite.getPosition().y);

		if (dx <= (platform.GetScale().x + ball.GetScale().x) / 2.f &&
			dy <= (platform.GetScale().y + ball.GetScale().y) / 2.f) 
		{
			if ((platform.GetPosition().x - platform.GetScale().x / 2.f) >= ball.GetPosition().x)  // left
			{
				if (platform.GetDirectionSpeed() != 0)
				{
					direction.x = platform.GetDirectionSpeed();
				}
				if (ball.GetPosition().x && direction.x > 0) //Ñhanges in direction only if the ball is flying in the opposite direction
				{
					MirroringDirectionX();
				}
			}
			if ((platform.GetPosition().x + platform.GetScale().x / 2.f) <= ball.GetPosition().x) // right
			{
				if (platform.GetDirectionSpeed() != 0)
				{
					direction.x = platform.GetDirectionSpeed();
				}
				if (ball.GetPosition().x && direction.x < 0) //Ñhanges in direction only if the ball is flying in the opposite direction
				{
					MirroringDirectionX();
				}
			}
			if (platform.GetPosition().y - platform.GetScale().y / 2.f >= ball.GetPosition().y && direction.y > 0) // up
			{
				if (direction.y + ACCELETATION_PLATFORM_CONTACT < MAX_BALL_SPEED)
				{
					direction.y += ACCELETATION_PLATFORM_CONTACT;
				}
				else 
				{
					direction.y = MAX_BALL_SPEED;
				}
				MirroringDirectionY();
			}
			if ((platform.GetScale().y / 2.f + platform.GetPosition().y) <= ball.GetPosition().y && direction.y < 0) // down
			{
				if (direction.y + ACCELETATION_PLATFORM_CONTACT > -MAX_BALL_SPEED)
				{
					direction.y -= ACCELETATION_PLATFORM_CONTACT;
				}
				else
				{
					direction.y = -MAX_BALL_SPEED;
				}
				MirroringDirectionY();
			}
			return true;
		}
		return false;
	}

	bool Ball::Collision(BaseBrick& brick, SpriteObject& ball)
	{

		float dx = (float)fabs(brick.GetPosition().x - objectSprite.getPosition().x);
		float dy = (float)fabs(brick.GetPosition().y - objectSprite.getPosition().y);

		if (dx <= (brick.GetScale().x + ball.GetScale().x) / 2.f &&
			dy <= (brick.GetScale().y + ball.GetScale().y) / 2.f)
		{
			if ((brick.GetPosition().x - brick.GetScale().x / 2.f) >= ball.GetPosition().x)  // left side
			{
				if (ball.GetPosition().x && direction.x > 0) //Ñhanges in direction only if the ball is flying in the opposite direction
				{
					MirroringDirectionX();
				}
			}
			if ((brick.GetPosition().x + brick.GetScale().x / 2.f) <= ball.GetPosition().x) // right side
			{
				if (ball.GetPosition().x && direction.x < 0) //Ñhanges in direction only if the ball is flying in the opposite direction
				{
					MirroringDirectionX();
				}
			}
			if (brick.GetPosition().y - brick.GetScale().y / 2.f >= ball.GetPosition().y && direction.y > 0) // up side
			{
				MirroringDirectionY();
			}
			if ((brick.GetScale().y / 2.f + brick.GetPosition().y) <= ball.GetPosition().y && direction.y < 0) // down side
			{
				MirroringDirectionY();
			}


			return true;

		}



		return false;
	}

	
	
}