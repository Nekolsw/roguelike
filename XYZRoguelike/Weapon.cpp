#include "Weapon.h"
#include "Logger.h"
#include "CharacterStats.h"
#include "IDelayedAction.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
namespace XYZEngine
{
	Weapon::Weapon(GameObject* gameObject) : Component(gameObject)
	{
		ownerTransform = gameObject->GetComponent<TransformComponent>();
		gameObject = GameWorld::Instance()->CreateGameObject("Sword");
	
		weaponRenderer = gameObject->AddComponent<SpriteRendererComponent>();
		weaponRenderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("ball"));
		weaponRenderer->SetPixelSize(0, 0);
		auto body = gameObject->AddComponent<RigidbodyComponent>();
		body->SetKinematic(true);
		auto collider = gameObject->AddComponent<SpriteColliderComponent>();
		transform = gameObject->GetComponent<TransformComponent>();
		transform->SetWorldPosition({ 0.f, 0.f });
		float weaponDamage = 15.f;
		collider->SubscribeCollision([weaponDamage, &tickDamage = std::move(linkDamageTime)](XYZEngine::Collision x)
		{
			CharacterStats* characterStats = x.first->GetGameObject()->GetComponent<CharacterStats>();
			try 
			{
				if (!characterStats) 
				{
					throw std::invalid_argument("Component: CharacterStats not found\n");
				}
			}
			catch (const std::invalid_argument& e)
			{
				LOG_WARN(e.what());
			}
			if (characterStats && tickDamage && *tickDamage <= 0.f)
			{
				characterStats->DealDamage(weaponDamage);
				*tickDamage = 1.f;
				std::cout << characterStats->GetHealth() << std::endl;
			}
		});
	}
	GameObject* Weapon::GetGameObject()
	{
		return gameObject;
	}

	void Weapon::Update(float deltaTime)
	{
		if (*linkDamageTime > 0.f)
		{
			*linkDamageTime -= 1.f * deltaTime;
		}
		auto characterPosition = ownerTransform->GetWorldPosition();
		auto characterRotation = ownerTransform->GetWorldRotation();
		// Обновляем позицию меча
		float dirX = cos(transform->GetWorldRotation() * 3.14159265f / 180.f); //Переводим в радианы 
		float dirY = sin(transform->GetWorldRotation() * 3.14159265f / 180.f);

		Vector2Df offset;
		offset.x = characterPosition.x + dirX * placementDistance;
		offset.y = characterPosition.y + dirY * placementDistance;

		transform->SetWorldRotation(characterRotation);
		transform->SetWorldPosition(offset);
	}

	void Weapon::Render()
	{
	}

	void Weapon::SetActive(bool OnActive)
	{
		if (OnActive)
		{
			weaponRenderer->SetPixelSize(35, 8);
		}
		else 
		{
			weaponRenderer->SetPixelSize(0, 0);
		}
		
		
	}


}