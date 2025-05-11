#include "CharacterStats.h"

namespace XYZEngine
{

	CharacterStats::CharacterStats(GameObject* gameObject) : Component(gameObject)
	{
		health = 100.f;
		maxHealth = 100.f;
		armor = 0.f;
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
		if (health >= amountDamage - armor)
		{
			health -= amountDamage - armor;
		}
		else 
		{
			health = 0.f;
			stateLifeCharacter = false;
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

}