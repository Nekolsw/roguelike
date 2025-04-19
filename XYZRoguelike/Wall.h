#pragma once
#include <GameWorld.h>
#include <ResourceSystem.h>
#include "GameObject.h"

class Wall
{
	public:
		Wall(const XYZEngine::Vector2Df position, int indexTexture);
	private:
		XYZEngine::GameObject* gameObject;

};

