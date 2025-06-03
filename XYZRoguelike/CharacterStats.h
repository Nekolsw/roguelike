#pragma once
#include "TransformComponent.h"
#include "GameObject.h"
#include "Component.h"
namespace XYZEngine
{
	class CharacterStats : public Component
	{
	public:
		CharacterStats(std::shared_ptr<GameObject> gameObject);
		void SetMaxHealth(float maxHealthSet);
		void SetHealth(float healthSet);
		float GetHealth();
		void Setarmor(float armorSet);
		void DealDamage(float amountDamage);
		bool CheckStateLifeCharacter();
		void RestoreHealth(float amountHealth);

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

	private:
		void OnDeath();
		std::shared_ptr<TransformComponent> transform;
		float health, maxHealth, armor;
		bool stateLifeCharacter = true;
	};
}