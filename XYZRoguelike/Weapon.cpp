#include "Weapon.h"
#include "Logger.h"
#include "CharacterStats.h"
#include "IDelayedAction.h"
#include <ResourceSystem.h>
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
		collider = gameObject->AddComponent<SpriteColliderComponent>();
		transform = gameObject->GetComponent<TransformComponent>();
		transform->SetWorldPosition({ 0.f, 0.f });
		collider->SubscribeCollision(std::bind(&Weapon::DamageCollision, this, std::placeholders::_1));
	}
	Weapon::~Weapon()
	{
		collider->UnsubscribeCollision(std::bind(&Weapon::DamageCollision, this, std::placeholders::_1));
	}
	GameObject* Weapon::GetGameObject()
	{
		return gameObject;
	}

	void Weapon::Update(float deltaTime)
	{
		if (tickDamage > 0.f)
		{
			tickDamage -= 1.f * deltaTime;
		}
		if (ownerTransform)
		{
			
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

	void Weapon::DamageCollision(XYZEngine::Collision collision)
	{
		auto characterStats = collision.first->GetGameObject()->GetComponent<CharacterStats>();
		try {
			if (!characterStats) {
				throw std::invalid_argument(
					"Component: CharacterStats not found\n");
			}
		}
		catch (const std::invalid_argument& e) {
			LOG_WARN(e.what());
		}
		if (characterStats && (tickDamage <= 0.f && tickDamage <= 0.f)) {
			characterStats->DealDamage(weaponDamage);
			tickDamage = 1.f;
			std::cout << characterStats->GetHealth() << std::endl;
		}
	}


}