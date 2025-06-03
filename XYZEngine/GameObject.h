#pragma once

#include "TransformComponent.h"
#include <iostream>
#include <vector>

namespace XYZEngine
{
	class TransformComponent;

	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		GameObject(std::string newName);

		~GameObject();
		static std::shared_ptr<GameObject> Create(std::string name = "") 
		{
			try {
				// Важно: не используем make_shared с enable_shared_from_this
				auto obj = std::shared_ptr<GameObject>(new GameObject(name));

				// Проверка целостности
				if (obj.use_count() != 1) {
					throw std::runtime_error("Invalid shared_ptr state");
				}

				obj->Initialize();
				return obj;
			}
			catch (...) {
				throw std::runtime_error("GameObject construction failed");
			}
		}

		std::string GetName() const;
		void Print(int depth = 0) const;

		void Update(float deltaTime);
		void Render();

		template <typename T>
		std::shared_ptr<T> AddComponent()
		{

			static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

			if constexpr (std::is_same_v<T, TransformComponent>)
			{
				if (GetComponent<TransformComponent>())
				{
					std::cout << "Can't add Transform, because it will break the engine loop.\n";
					return nullptr;
				}
			}

			try {
				shared_from_this(); // Проверка доступности
			}
			catch (const std::bad_weak_ptr&) {
				throw std::runtime_error("GameObject must be managed by shared_ptr");
			}

			auto newComponent = std::make_shared<T>(shared_from_this());
			components.push_back(newComponent);

			return newComponent;
		}

		void RemoveComponent(const std::shared_ptr<Component>& component)
		{
			components.erase(std::remove_if(components.begin(), components.end(), [&component](const auto& obj) { return obj == component; }), components.end());
			std::cout << "Deleted component";
		}

		template <typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (const auto& component : components)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(component))
				{
					return casted;
				}
			}
			return nullptr;
		}

		template <typename T>
		std::shared_ptr<T> GetComponentInChildren() const
		{
			std::shared_ptr<T> component = GetComponent<T>();
			if (component != nullptr || children.size() == 0)
			{
				return component;
			}

			for (const auto& child : children)
			{
				T* childComponent = child->GetComponentInChildren<T>();
				if (childComponent != nullptr)
				{
					return childComponent;
				}
			}

			return nullptr;
		}

		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponents() const
		{
			std::vector<std::shared_ptr<T>> result;
			for (const auto& component : components)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(component))
				{
					result.push_back(casted);
				}
			}
			return result;
		}

		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponentsInChildren() const
		{
			auto result = GetComponents<T>();

			for (const auto& childWeak : children)
			{
				if (auto child = childWeak.lock())
				{
					auto childComponents = child->GetComponentsInChildren<T>();
					result.insert(result.end(), childComponents.begin(), childComponents.end());
				}
			}

			return result;
		}

		void AddChild(std::shared_ptr<GameObject> child);
		void RemoveChild(std::shared_ptr<GameObject> child);

		friend class GameWorld;
		friend class TransformComponent;

	private:
		std::string name;

		std::vector<std::weak_ptr<GameObject>> children = {};
		std::vector<std::shared_ptr<Component>> components = {};
		void Initialize() 
		{
			AddComponent<TransformComponent>();
		}
	};
}