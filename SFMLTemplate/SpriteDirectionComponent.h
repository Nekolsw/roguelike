#pragma once
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"

namespace XYZEngine
{
	class SpriteDirectionComponent : public Component
	{
	public:
		SpriteDirectionComponent(std::shared_ptr<GameObject> gameObject);

		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<InputComponent> input;
		std::shared_ptr<SpriteRendererComponent> spriteRenderer;
	};
}
