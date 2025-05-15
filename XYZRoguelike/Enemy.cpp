#include "Enemy.h"
#include "CharacterStats.h"
#include "AISwordMan.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
namespace XYZRoguelike
{
	Enemy::Enemy()
	{

		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		
		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(24, 24);
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		auto weapon = gameObject->AddComponent<XYZEngine::Weapon>();
		auto attackSystem = gameObject->AddComponent<AttackComponent>();
		auto movement = gameObject->AddComponent<AISwordMan>();
		movement->SetSpeed(50.f);
		movement->SetTarget(XYZEngine::GameWorld::Instance()->GetGameObjectByName("Player"));

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		movement->GetGameObject()->AddChild(collider->GetGameObject());
		auto enemyStats = gameObject->AddComponent<XYZEngine::CharacterStats>();
		
	}
	Enemy::Enemy(const XYZEngine::Vector2Df position)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(24, 24);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);
		auto weapon = gameObject->AddComponent<XYZEngine::Weapon>();
		auto attackSystem = gameObject->AddComponent<AttackComponent>();
		auto movement = gameObject->AddComponent<AISwordMan>();
		movement->SetSpeed(50.f);
		movement->SetTarget(XYZEngine::GameWorld::Instance()->GetGameObjectByName("Player"));

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		auto enemyStats = gameObject->AddComponent<XYZEngine::CharacterStats>();
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}