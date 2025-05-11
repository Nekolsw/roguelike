#pragma once
#include "GameWorld.h"
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
namespace XYZEngine
{
	class Weapon : public Component
	{
	public:
		//enum WeaponType {Sword, Bow};
		Weapon(GameObject* gameObject);
		GameObject* GetGameObject();
		void Update(float deltaTime) override;
		void Render() override;
		void Attack(const Vector2Df characterPosition, float placementDistance, float angelAttack);
		void StopAttack();
		//void SetWeaponType(WeaponType type);
		//WeaponType GetWeaponType();
	private:
		//WeaponType weaponType = Sword;
		SpriteRendererComponent* weaponRenderer;
		TransformComponent* transform;
		float delayAttack = 0.f;
		float attackSpeed = 0.f;
	};
}