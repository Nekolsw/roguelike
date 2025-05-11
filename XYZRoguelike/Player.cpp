#include "Player.h"
#include "CharacterStats.h"
#include "Weapon.h"
#include "AttackComponent.h"
#include <ResourceSystem.h>
#include <MovementComponent.h>
#include <SpriteColliderComponent.h>

namespace XYZRoguelike
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		auto weapon = gameObject->AddComponent<XYZEngine::Weapon>();
		//weapon->SetWeaponType(XYZEngine::Weapon::Sword);


		auto attackSystem = gameObject->AddComponent<AttackComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		auto playerStats = gameObject->AddComponent<XYZEngine::CharacterStats>();
		collider->SubscribeCollision([playerStats](XYZEngine::Collision x)
		{ 
			if (x.second->GetGameObject()->GetName() == "Sword") 
			{
				playerStats->DealDamage(15.f);
				std::cout << playerStats->GetHealth() << std::endl;
			}
		});

	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}