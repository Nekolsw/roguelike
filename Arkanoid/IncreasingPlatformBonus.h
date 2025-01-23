#pragma once
#include "BaseBonus.h"
#include "GameMath.h"
namespace Roguelike 
{
	class IncreasingPlatformBonus : public BaseBonus
	{
		void Initialization(GameResources& resources) override;
	};
}


