#include "DeveloperLevel.h"
#include "MazeGenerator.h"


using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		int width = 17;
		int height = 17;
		int x_Offset = 0.f;
		int y_Offset = 0.f;

		for (int y = 0; y < height + 1; y++)
		{
			for (int x = 0; x < width + 1; x++)
			{
				//if not wall place
				if (x != 0 && x != width && y != 0 && y != height)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(0)));
				}

				//Left-bottom angle screen
				if (x == 0 && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(25)));
				}

				//Right-bottom angle screen
				if (x == width && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(27)));
				}

				//Left-top angle screen
				if (x == 0 && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(1)));
				}

				//Right-top angle screen
				if (x == width && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(3)));
				}

				//Left screen
				if (x == 0 && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(18)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(12)));
				}

				//Right screen
				if (x == width && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(19)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(12)));
				}

				//Bottom screen
				if (y == 0 && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(38)));
				}

				//Top screen
				if (y == height && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(38)));
				}
			}
		}
		int generatWidth = width + x_Offset;
		int generatHeight = height + x_Offset;
		MazeGenerator mazeGenerator(generatWidth, generatHeight, this);
		mazeGenerator.Generate();

		player = std::make_shared<Player>(std::forward<XYZEngine::Vector2Df>({ (x_Offset + width) / 2 * 64.f, (y_Offset + height) / 2 * 64.f }));
		swordMan = std::make_shared<Enemy>(XYZEngine::Vector2Df({ 350.f, 350.f }));

		backgroundMusic = std::make_unique<SoundPlayer>("BackgroundMusic");
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop() 
	{
		GameWorld::Instance()->Clear();
	}
}