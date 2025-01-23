#include "ConstructionBonus.h"
#include "Constants.h"
namespace Arkanoid
{
	std::shared_ptr <BaseBonus> WorkshopFireBallBonus::Create()
	{
		return std::make_unique <FireBallBonus>();
	}

	std::shared_ptr <BaseBonus> WorkshopGlassBrickBonus::Create()
	{
		return std::make_unique <GlassBrickBonus>();
	}

	std::shared_ptr <BaseBonus> WorkshopIncreasingPlatform::Create()
	{
		return std::make_unique <IncreasingPlatformBonus>();
	}

	std::shared_ptr <BaseBonus> ConstructionBonus::CreateRandomBonus(sf::Vector2f spawnPosition, GameResources& resources)
	{
		std::shared_ptr <WorkshopBonus> creator;
		std::shared_ptr <BaseBonus> tempBonus = {};
		switch (rand() % 3)
		{
		case 0:
			creator = std::make_unique<WorkshopFireBallBonus>();
			break;
		case 1:
			creator = std::make_unique<WorkshopGlassBrickBonus>();
			break;
		case 2:
			creator = std::make_unique<WorkshopIncreasingPlatform>();
			break;
		default:
			creator = nullptr;
			break;
		}
		if (creator != nullptr) 
		{
			tempBonus = creator->Create();
			if (tempBonus != nullptr)
			{
				tempBonus->Initialization(resources);
				tempBonus->SetPosition(spawnPosition);
				return tempBonus;
			}
		}

		else 
		{
			return nullptr;
		}
	}
	void ConstructionBonus::CreateBonus(sf::Vector2f spawnPosition, GameResources& resources)
	{
		if ((rand() % 100) >= (100 - PROBABILITY_SPAWNING_BONUS))
		{
			std::shared_ptr <BaseBonus> tempBonus = CreateRandomBonus(spawnPosition, resources);
			if (tempBonus != nullptr) 
			{
				bonuses.push_back(tempBonus);
			}
		}
	}
	std::vector<std::shared_ptr<BaseBonus>>& ConstructionBonus::GetBonuses()
	{
		return bonuses;
	}
	void ConstructionBonus::Draw(sf::RenderWindow& window)
	{
		for (auto& row : bonuses)
		{
			row->Draw(window);
		}
	}
}