#include "Enemy.h"
#include <ResourceSystem.h>
#include <AIMovementComponent.h>
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
		auto movement = gameObject->AddComponent<XYZEngine::AIMovementComponent>();
		movement->SetSpeed(50.f);
		movement->SetTarget(XYZEngine::GameWorld::Instance()->GetGameObjectByName("Player"));

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		
	}
	Enemy::Enemy(const XYZEngine::Vector2Df position)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(24, 24);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);
		auto movement = gameObject->AddComponent<XYZEngine::AIMovementComponent>();
		movement->SetSpeed(50.f);
		movement->SetTarget(XYZEngine::GameWorld::Instance()->GetGameObjectByName("Player"));

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}