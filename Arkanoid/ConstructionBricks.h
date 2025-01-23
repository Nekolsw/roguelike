#pragma once
#include <memory>
#include "Resources.h"
#include "BaseBrick.h"
#include "Brick.h"
#include "ProtectedBrick.h"
#include <SFML/Graphics.hpp>
namespace Arkanoid
{
	class WorkshopBrick
	{
	public:
		virtual std::shared_ptr <BaseBrick> Create() = 0;
	};

	class WorkshopClassicBrick : public WorkshopBrick 
	{
	public:
		std::shared_ptr <BaseBrick> Create() override;
	};

	class WorkshopProtectedBrick : public WorkshopBrick
	{
	public:
		std::shared_ptr <BaseBrick> Create() override;
	};

	class ConstructionBricks
	{
	private:
		std::vector<std::shared_ptr <BaseBrick>> bricks;
	public:
		void Construction(GameResources& resources);
		void Restructuring(GameResources& resources);
		std::vector<std::shared_ptr <BaseBrick>>& GetBricks();
		void Draw(sf::RenderWindow& window);
	};

}