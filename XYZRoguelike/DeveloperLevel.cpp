#include "DeveloperLevel.h"

using namespace XYZEngine;

namespace XYZRoguelike
{
	void DeveloperLevel::Start()
	{
		int width = 17;
		int height = 17;
		int x_Offset = -300.f;
		int y_Offset = -350.f;

		for (int y = 0; y < height + 1; y++)
		{
			for (int x = 0; x < width + 1; x++)
			{

				//Left-bottom angle screen
				if (x == 0 && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(25)));
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
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x_Offset + x * 64.f, y_Offset + y * 64.f }), std::forward<int>(12)));
				}

				//Right screen
				if (x == width && y != height && y != 0)
				{
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
		player = std::make_shared<Player>();
		enemy = std::make_shared<Enemy>(XYZEngine::Vector2Df ({ 350.f, 350.f }));

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