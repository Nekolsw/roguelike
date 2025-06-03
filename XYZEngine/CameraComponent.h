#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "TransformComponent.h"

namespace XYZEngine
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent(std::shared_ptr<GameObject> gameObject);
		~CameraComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetWindow(sf::RenderWindow* newWindow);
		void ZoomBy(float newZoom);
		void SetTurnTracking(bool isTracking);
		void SetBaseResolution(int width, int height);
	private:
		bool isTurnTracking = true;
		std::shared_ptr<TransformComponent> transform;
		sf::RenderWindow* window;
		sf::View* view;
	};
}