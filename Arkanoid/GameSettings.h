#pragma once
#include "Constants.h"
namespace Arkanoid
{
	struct GameSettings
	{
		bool isPlayMusic = true, isPlaySound = true;
		enum class TypeBrick
		{
			Standart = 1,
			Protected,
			Glass
		};

		struct GameMode 
		{
			bool isMoveObstacle = false;
			bool isPortalEnable = false;
		};

		GameMode gameMode;
	};
}