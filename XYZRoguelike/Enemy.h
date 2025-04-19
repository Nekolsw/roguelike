#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"

namespace XYZRoguelike
{
	class Enemy
	{
	public:
		Enemy();
		Enemy(const XYZEngine::Vector2Df position);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
		void HandleCollision() {
			
		}
	};
}

