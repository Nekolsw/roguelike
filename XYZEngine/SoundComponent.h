#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Component.h"


namespace XYZEngine
{
	class SoundComponent : public Component
	{
	public:
		SoundComponent(std::shared_ptr<GameObject> gameObject);
		~SoundComponent();

		void Play();
		void Stop();
		void Pause();
		void Update(float deltaTime) override;
		void Render() override;
		void SetSound(const sf::SoundBuffer& sound);
		void SetLoop(bool loop);
		void SetVolume(float volume);
		
	private:
		sf::Sound* playSound;
	};
}

