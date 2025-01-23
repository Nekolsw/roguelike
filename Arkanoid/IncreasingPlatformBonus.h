#pragma once
#include "BaseBonus.h"
#include "GameMath.h"
namespace Arkanoid 
{
	class IncreasingPlatformBonus : public BaseBonus
	{
		void Initialization(GameResources& resources) override;
	};
}


