#include "pch.h"
#include "Component.h"
#include <iostream>

namespace XYZEngine
{
	Component::Component(std::shared_ptr<GameObject> gameObject) : gameObject(gameObject) {}
	Component::~Component()
	{
		std::cout << "Deleted component: " << this << std::endl;
	}
	std::shared_ptr<GameObject> Component::GetGameObject()
	{
		return gameObject;
	}
}