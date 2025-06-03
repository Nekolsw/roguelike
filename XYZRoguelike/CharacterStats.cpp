#include "CharacterStats.h"
#include "Logger.h"

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
		if (std::abs(amountDamage) <= armor) 
		{
			LOG_INFO("The armor absorbed all the damage\n");
			return; 
		}
		if (health >= std::abs(amountDamage) - armor)
		{
			LOG_INFO(this->gameObject->GetName() + " received damage: " + std::to_string(std::abs(amountDamage) - armor) + "\n");
			health -= std::abs(amountDamage) - armor;
		}
		else
		{
			health = 0.f;
			LOG_INFO("Dead");
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
		if(!stateLifeCharacter) 
		{
			this->gameObject->~GameObject();
		}
	}

	void CharacterStats::Render()
	{
	}

	void CharacterStats::OnDeath()
	{
		//transform->SetWorldPosition(0.f, 0.f);
		//health = maxHealth;
		//stateLifeCharacter = true;
	}

}