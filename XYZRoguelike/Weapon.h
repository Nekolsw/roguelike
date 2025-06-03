#pragma once
#include "GameWorld.h"
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include <SpriteColliderComponent.h>
namespace XYZEngine
{
	class Weapon : public Component
	{
	public:
		Weapon(GameObject* gameObject);
		~Weapon();
		GameObject* GetGameObject();
		void Update(float deltaTime) override;
		void Render() override;
		void SetActive(bool OnActive);
		void DamageCollision(XYZEngine::Collision collision);
	private:
		XYZEngine::SpriteRendererComponent* weaponRenderer;
		XYZEngine::TransformComponent* transform;
		XYZEngine::TransformComponent* ownerTransform;
		XYZEngine::SpriteColliderComponent* collider;
		float placementDistance = 40.f;
		float weaponDamage = 55.f;
		float tickDamage = 0.f;
	};
}