#pragma once
#include "GameObject.h"
#include "MovementComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"

namespace XYZEngine
{
	class SpriteMovementAnimationComponent : public Component
	{
	public:
		SpriteMovementAnimationComponent(std::shared_ptr<GameObject> gameObject);

		void Initialize(const std::string& textureMapName, float newFramerate);

		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<MovementComponent> movement;
		std::shared_ptr<SpriteRendererComponent> renderer;

		std::vector<const sf::Texture*> textureMap;
		float secondsForFrame = 0.f;

		float counter = 0.f;
		int frame = 0;
	};
}
