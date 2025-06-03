#include "pch.h"
#include "GameWorld.h"

namespace XYZEngine
{
	std::shared_ptr<GameWorld> GameWorld::Instance()
	{
		static std::shared_ptr<GameWorld> world;
		return world;
	}

	void GameWorld::Update(float deltaTime)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(deltaTime);
		}
	}
	void GameWorld::FixedUpdate(float deltaTime)
	{
		fixedCounter += deltaTime;
		if (fixedCounter > PhysicsSystem::Instance()->GetFixedDeltaTime())
		{
			fixedCounter -= PhysicsSystem::Instance()->GetFixedDeltaTime();
			PhysicsSystem::Instance()->Update();
		}
	}
	void GameWorld::Render()
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Render();
		}
	}
	void GameWorld::LateUpdate()
	{
		for (int i = markedToDestroyGameObjects.size() - 1; i >= 0; i--)
		{
			DestroyGameObjectImmediate(markedToDestroyGameObjects[i]);
		}
	}

	std::shared_ptr<GameObject> GameWorld::CreateGameObject()
	{
		auto newGameObject = GameObject::Create();
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}
	std::shared_ptr<GameObject> GameWorld::CreateGameObject(std::string name)
	{
		static_assert(sizeof(gameObjects) == sizeof(std::vector<std::shared_ptr<GameObject>>),
			"ABI mismatch detected");
		// 1. Проверка целостности вектора
		auto CheckVector = [this]() {
			if (gameObjects.size() > gameObjects.capacity()) {
				throw std::runtime_error("Vector size/capacity mismatch");
			}
			if (gameObjects.capacity() > 0 && !gameObjects.data()) {
				throw std::runtime_error("Vector data pointer invalid");
			}
			};

		CheckVector();

		// 2. Создание объекта
		auto newGameObject = GameObject::Create(name);

		// 3. Проверка перед добавлением
		if (!newGameObject || newGameObject.use_count() != 1) {
			throw std::runtime_error("Invalid GameObject state");
		}

		// 4. Безопасное расширение capacity
		try {
			if (gameObjects.size() == gameObjects.capacity()) {
				size_t new_capacity = gameObjects.capacity() * 2 + 10;
				std::vector<std::shared_ptr<GameObject>> temp;
				temp.reserve(new_capacity);
				temp = gameObjects; // Копируем через оператор присваивания
				gameObjects.swap(temp); // Безопасный обмен
			}
		}
		catch (...) {
			throw std::runtime_error("Memory allocation failed");
		}

		// 5. Проверка перед добавлением
		CheckVector();

		// 6. Безопасное добавление
		try {
			gameObjects.push_back(newGameObject);
			return newGameObject;
		}
		catch (...) {
			throw std::runtime_error("Failed to add to vector");
		}
	}
	std::shared_ptr<GameObject> GameWorld::GetGameObjectByName(std::string name)
	{
		std::shared_ptr<GameObject> searchGameObject = nullptr;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (gameObjects[i]->GetName() == name)
			{
				searchGameObject = gameObjects[i];
				return searchGameObject;
			}
		}
		return nullptr;
	}
	void GameWorld::DestroyGameObject(std::shared_ptr<GameObject> gameObject)
	{
		markedToDestroyGameObjects.push_back(gameObject);
	}
	void GameWorld::Clear()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			if (gameObjects[i] == nullptr)
			{
				continue;
			}

			if (gameObjects[i]->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				DestroyGameObjectImmediate(gameObjects[i]);
			}
		}

		fixedCounter = 0.f;
	}

	void GameWorld::Print() const
	{
		for (auto& obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				obj->Print();
			}
		}
	}

	void GameWorld::DestroyGameObjectImmediate(std::shared_ptr<GameObject> gameObject)
	{
		auto parent = gameObject->GetComponent<TransformComponent>()->GetParent();
		if (parent != nullptr)
		{
			parent->GetGameObject()->RemoveChild(gameObject);
		}

		for (auto transform : gameObject->GetComponentsInChildren<TransformComponent>())
		{
			std::shared_ptr<GameObject> gameObjectToDelete = transform->GetGameObject();

			gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [gameObjectToDelete](std::shared_ptr<GameObject> obj) { return obj == gameObjectToDelete; }), gameObjects.end());
			markedToDestroyGameObjects.erase(std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(), [gameObjectToDelete](std::shared_ptr<GameObject> obj) { return obj == gameObjectToDelete; }), markedToDestroyGameObjects.end());

		}
	}
}