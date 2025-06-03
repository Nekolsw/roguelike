#pragma once

#include "GameObject.h"
#include "PhysicsSystem.h"
#include <iostream>
#include <vector>
#include <mutex>

namespace XYZEngine
{
	class GameWorld
	{
	public:
		static std::shared_ptr<GameWorld> Instance();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
		void LateUpdate();

		std::shared_ptr<GameObject> CreateGameObject();
		std::shared_ptr<GameObject> CreateGameObject(std::string name);
		std::shared_ptr<GameObject> GetGameObjectByName(std::string name);
		void DestroyGameObject(std::shared_ptr<GameObject> gameObject);
		void Clear();

		void Print() const;
	private:

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<GameObject>> markedToDestroyGameObjects = {};
		GameWorld() {}
		~GameWorld() {}

		GameWorld(GameWorld const&) = delete;
		GameWorld& operator= (GameWorld const&) = delete;

		float fixedCounter = 0.f;

		void DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject);
	};
}