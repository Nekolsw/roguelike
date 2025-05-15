#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class Player
	{
	public:
		Player();
	private:
		XYZEngine::GameObject* gameObject;
	};
}