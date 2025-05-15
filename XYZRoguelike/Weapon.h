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
		XYZEngine::InputComponent* input;
		XYZEngine::SpriteRendererComponent* weaponRenderer;
		XYZEngine::TransformComponent* transform;
		XYZEngine::TransformComponent* ownerTransform;
		float placementDistance = 40.f;
		float damageTime = 1.f;
	};
}