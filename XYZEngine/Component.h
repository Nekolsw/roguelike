#pragma once
#include <iostream>

namespace XYZEngine
{
	class GameObject;

	class Component
	{
	public:
		Component(std::shared_ptr<GameObject> gameObject);
		virtual ~Component();

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		std::shared_ptr<GameObject> GetGameObject();
	protected:
		std::shared_ptr<GameObject> gameObject;
	};
}