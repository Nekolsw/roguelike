#pragma once
#include "GameWorld.h"
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include <SpriteColliderComponent.h>
namespace XYZEngine
{
	class Weapon : public Component
	{
	public:
		Weapon(std::shared_ptr<GameObject> gameObject);
		~Weapon();
		std::shared_ptr<GameObject> GetGameObject();
		void Update(float deltaTime) override;
		void Render() override;
		void SetActive(bool OnActive);
		void DamageCollision(XYZEngine::Collision collision);
	private:
		std::shared_ptr<XYZEngine::SpriteRendererComponent> weaponRenderer;
		std::shared_ptr<XYZEngine::TransformComponent> transform;
		std::shared_ptr<XYZEngine::TransformComponent> ownerTransform;
		std::shared_ptr<XYZEngine::SpriteColliderComponent> collider;
		float placementDistance = 40.f;
		float weaponDamage = 55.f;
		float tickDamage = 0.f;
	};
}