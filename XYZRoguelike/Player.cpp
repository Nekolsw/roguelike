#include "Player.h"
#include "CharacterStats.h"
#include "Weapon.h"
#include "AttackComponent.h"
#include "ControllerInputComponent.h"
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
		playerCamera->SetTurnTracking(false);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();

		auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		auto weapon = gameObject->AddComponent<XYZEngine::Weapon>();


		auto attackSystem = gameObject->AddComponent<AttackComponent>();
		auto controllerInput = gameObject->AddComponent<ControllerInputComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		auto playerStats = gameObject->AddComponent<XYZEngine::CharacterStats>();
		playerStats->Setarmor(4.f);

	}

}