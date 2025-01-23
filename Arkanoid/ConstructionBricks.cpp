#include "ConstructionBricks.h"
namespace Roguelike 
{
	std::shared_ptr <BaseBrick> WorkshopClassicBrick::Create()
	{
		return std::make_unique <Brick>();
	}
	std::shared_ptr <BaseBrick> WorkshopProtectedBrick::Create()
	{
		return std::make_unique <ProtectedBrick>();
	}

	void ConstructionBricks::Construction(GameResources& resources)
	{
		for (int i = 0; i < BRICK_FOR_WIDTH; ++i)
		{
			std::shared_ptr  <WorkshopBrick> creator;
			std::shared_ptr  <BaseBrick> tempBrick = {};
			for (int j = 0; j < BRICK_FOR_HEIGHT; ++j)
			{
				if (rand() % 2)
				{
					creator = std::make_unique < WorkshopClassicBrick>();
				}
				else
				{
					creator = std::make_unique < WorkshopProtectedBrick>();
				}

				tempBrick = creator->Create();
				tempBrick->Initialization({ STARTING_POSITION_BRICK.x + DISTANCE_BETWEEN_BRICKS.x * i, STARTING_POSITION_BRICK.y + DISTANCE_BETWEEN_BRICKS.y * j },
					BRICK_SIZE, resources, sf::Color::Cyan);
				tempBrick->RandomColoring();
				bricks.push_back(tempBrick);

			}
		}
	}

	void ConstructionBricks::Restructuring(GameResources& resources) 
	{
		bricks.clear();
		Construction(resources);
	}

	std::vector<std::shared_ptr<BaseBrick>>& ConstructionBricks::GetBricks()
	{
		return bricks;
	}

	void ConstructionBricks::Draw(sf::RenderWindow& window)
	{
		for (auto& row : bricks)
		{
				row->Draw(window);

		}
	}
	
}