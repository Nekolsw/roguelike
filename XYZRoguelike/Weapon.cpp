#include "Weapon.h"
#include "IDelayedAction.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
namespace XYZEngine
{
	Weapon::Weapon(GameObject* gameObject) : Component(gameObject)
	{
		gameObject = GameWorld::Instance()->CreateGameObject("Sword");

		weaponRenderer = gameObject->AddComponent<SpriteRendererComponent>();
		weaponRenderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("ball"));
		weaponRenderer->SetPixelSize(0, 0);
		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(true);
		auto collider = gameObject->AddComponent<SpriteColliderComponent>();
		transform = gameObject->GetComponent<TransformComponent>();
		transform->SetWorldPosition({0.f, 0.f});
		
	}
	GameObject* Weapon::GetGameObject()
	{
		return gameObject;
	}

	void Weapon::Update(float deltaTime)
	{

		delayAttack -= 1.f * deltaTime;
		if (delayAttack <= 0.f)
		{
			StopAttack();
			attackSpeed -= 1.f * deltaTime;
		}
	}

	void Weapon::Render()
	{
	}

	void Weapon::Attack(const Vector2Df characterPosition, float placementDistance, float angelAttack)
	{
		if (delayAttack <= 0.f && attackSpeed <= 0.f) 
		{
			delayAttack = 0.1f;
			attackSpeed = 2.f;
			weaponRenderer->SetPixelSize(35, 8);
			transform->SetWorldRotation(angelAttack);

			// Обновляем позицию меча
			float dirX = cos(transform->GetWorldRotation() * 3.14159265f / 180.f); //Переводим в радианы 
			float dirY = sin(transform->GetWorldRotation() * 3.14159265f / 180.f);

			Vector2Df offset;
			offset.x = characterPosition.x + dirX * placementDistance;
			offset.y = characterPosition.y + dirY * placementDistance;

			transform->SetWorldPosition(offset);

		}
		
	}

	void Weapon::StopAttack()
	{
		weaponRenderer->SetPixelSize(0, 0);
	}

	//void Weapon::SetWeaponType(WeaponType type)
	//{
	//	weaponType = type;
	//}

	//Weapon::WeaponType Weapon::GetWeaponType()
	//{
	//	return weaponType;
	//}

}