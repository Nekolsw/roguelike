#pragma once
#include "BaseBonus.h"
#include "FireBallBonus.h"
#include "GlassBrickBonus.h"
#include "IncreasingPlatformBonus.h"

namespace Arkanoid 
{
	class WorkshopBonus
	{
	public:

		virtual std::shared_ptr <BaseBonus> Create() = 0;
	};

	class WorkshopFireBallBonus : public WorkshopBonus
	{
	public:
		std::shared_ptr <BaseBonus> Create() override;
	};

	class WorkshopGlassBrickBonus : public WorkshopBonus
	{
	public:
		std::shared_ptr <BaseBonus> Create() override;
	};

	class WorkshopIncreasingPlatform : public WorkshopBonus
	{
	public:
		std::shared_ptr <BaseBonus> Create() override;
	};
	
	class ConstructionBonus
	{
	private:
		std::vector<std::shared_ptr <BaseBonus>> bonuses;
		std::shared_ptr <BaseBonus> CreateRandomBonus(sf::Vector2f spawnPositio, GameResources& resources);

	public:
		void CreateBonus(sf::Vector2f spawnPositio, GameResources& resources);
		std::vector<std::shared_ptr <BaseBonus>>& GetBonuses();
		void Draw(sf::RenderWindow& window);
	};


}

