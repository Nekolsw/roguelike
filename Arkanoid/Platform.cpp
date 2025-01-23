#include "Platform.h"
#include "GameMath.h"
#include "KeyBindings.h"
void Roguelike::Platform::Initialization(sf::Vector2f newPosition, GameResources& resources, sf::Color color)
{
	positionPlaform = newPosition;
	SpriteObject::Initialization(newPosition, PLATFORM_STANDART_SIZE, resources.platformTexture, color);
	SetSpriteRelativeOrigin(objectSprite, { 0.5f, 0.5f });
	directionSpeed = PLATFORM_SPEED;
}

void Roguelike::Platform::Update(float& deltaTime)
{
		if (KeyBindings::Instance().GetKeyHolding() == KeyBindings::Instance().GetKey().keyRight && objectSprite.getPosition().x <= (WINDOW_SIZE.x - objectSprite.getOrigin().x - 30.f))
		{
			objectSprite.setPosition({ positionPlaform.x += directionSpeed * deltaTime, positionPlaform.y });
		}

		if (KeyBindings::Instance().GetKeyHolding() == KeyBindings::Instance().GetKey().keyLeft && objectSprite.getPosition().x >= (30.f + objectSprite.getOrigin().x))
		{
			objectSprite.setPosition({ positionPlaform.x -= directionSpeed * deltaTime, positionPlaform.y });
		}

		if (KeyBindings::Instance().GetKeyHolding() == KeyBindings::Instance().GetKey().none)
		{

		}

		if (durationInIncreasedSize > 0.f) 
		{
			durationInIncreasedSize = durationInIncreasedSize - (1.f * deltaTime);
			SetSpriteSize(objectSprite, PLATFORM_INCREASING_SIZE);
			SetScaleObject(PLATFORM_INCREASING_SIZE);
		}

		else 
		{
			durationInIncreasedSize = 0.f;
			SetSpriteSize(objectSprite, PLATFORM_STANDART_SIZE);
			SetScaleObject(PLATFORM_STANDART_SIZE);
		}
}

void Roguelike::Platform::TookSizeIncreaseBonus()
{
	durationInIncreasedSize = DURATION_BONUSES;
}

bool Roguelike::Platform::Collision(BaseBonus& bonus, SpriteObject& platform)
{
	float dx = (float)fabs(bonus.GetPosition().x - objectSprite.getPosition().x);
	float dy = (float)fabs(bonus.GetPosition().y - objectSprite.getPosition().y);

	if (dx <= (platform.GetScale().x + bonus.GetScale().x) / 2.f &&
		dy <= (platform.GetScale().y + bonus.GetScale().y) / 2.f)
	{
		if (platform.GetPosition().y - platform.GetScale().y / 2.f >= bonus.GetPosition().y) // up
		{
			return true;
		}
	}
	return false;
}

float Roguelike::Platform::GetDirectionSpeed()
{
	return directionSpeed;
}
