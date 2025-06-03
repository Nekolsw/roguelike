#include "pch.h"
#include "GameObject.h"

namespace XYZEngine
{
	GameObject::GameObject()
	{
		name = "GameObject";
		//AddComponent<TransformComponent>();
	}
	GameObject::GameObject(std::string newName)
	{
		name = newName;
		//AddComponent<TransformComponent>();
	}

	GameObject::~GameObject()
	{
		// Убедимся, что деструктор не вызывается дважды
		static std::atomic<bool> destructing = false;
		if (destructing.exchange(true)) {
			std::terminate(); // Аварийное завершение при двойном удалении
		}

		// Очистка компонентов
		components.clear(); // Автоматическое удаление через shared_ptr
		//children.clear();
	}

	std::string GameObject::GetName() const
	{
		return name;
	}

	void GameObject::Print(int depth) const
	{
		std::cout << std::string(depth * 2, ' ') << GetName() << std::endl;

		for (const auto& component : components)
		{
			std::cout << std::string(depth * 2, ' ') << "::" << component.get() << std::endl;
		}

		for (const auto& childWeak : children)
        {
            if (auto child = childWeak.lock())
            {
                child->Print(depth + 1);
            }
        }
	}

	void GameObject::Update(float deltaTime)
	{
		for (auto& component : components)
		{
			if (!components.empty())
			{
				component->Update(deltaTime);
			}
		}
	}
	void GameObject::Render()
	{
		for (auto& component : components)
		{
			component->Render();
		}
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> child)
	{
		children.push_back(child);
	}
	void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
	{
		children.erase(std::remove_if(children.begin(), children.end(), [&child](const std::weak_ptr<GameObject>& obj) { return obj.expired() || obj.lock() == child; }), children.end());
	}
}