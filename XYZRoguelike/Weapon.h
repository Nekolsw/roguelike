#pragma once
#include "GameWorld.h"
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
namespace XYZEngine
{
	class Weapon : public Component
	{
	public:
		Weapon(GameObject* gameObject);
		GameObject* GetGameObject();
		void Update(float deltaTime) override;
		void Render() override;
		void SetActive(bool OnActive);
	private:
		XYZEngine::SpriteRendererComponent* weaponRenderer;
		XYZEngine::TransformComponent* transform;
		XYZEngine::TransformComponent* ownerTransform;
		float placementDistance = 40.f;
		const std::unique_ptr<float> linkDamageTime = std::make_unique<float>(1.f);
	};
}