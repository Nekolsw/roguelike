#include "CharacterStats.h"

namespace XYZEngine
{

	CharacterStats::CharacterStats(GameObject* gameObject) : Component(gameObject)
	{
		health = 100.f;
		maxHealth = 100.f;
		armor = 0.f;
		transform = gameObject->GetComponent<TransformComponent>();
	}

	void CharacterStats::SetMaxHealth(float maxHealthSet)
	{
		maxHealth = maxHealthSet;
	}

	void CharacterStats::SetHealth(float healthSet)
	{
		health = healthSet;
	}

	float CharacterStats::GetHealth()
	{
		return health;
	}

	void CharacterStats::Setarmor(float armorSet)
	{
		armor = armorSet;
	}

	void CharacterStats::DealDamage(float amountDamage)
	{
		if (amountDamage < 0.f)
		{
			amountDamage * -1.f;
		}

		if (health >= amountDamage - armor)
		{
			health -= amountDamage - armor;
		}
		else 
		{
			health = 0.f;
			stateLifeCharacter = false;
			OnDeath();
		}
	}

	bool CharacterStats::CheckStateLifeCharacter()
	{
		return stateLifeCharacter;
	}

	void CharacterStats::RestoreHealth(float amountHealth)
	{
		health += amountHealth;
	}

	void CharacterStats::Update(float deltaTime)
	{

	}

	void CharacterStats::Render()
	{
	}

	void CharacterStats::OnDeath()
	{
		transform->SetWorldPosition(0.f, 0.f);
		health = maxHealth;
		stateLifeCharacter = true;
	}

}