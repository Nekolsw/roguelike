#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class SwordMan
	{
	public:
		SwordMan();
		SwordMan(const XYZEngine::Vector2Df position);
		std::shared_ptr<XYZEngine::GameObject> GetGameObject();
	private:
		std::shared_ptr<XYZEngine::GameObject> gameObject;
	};
}

