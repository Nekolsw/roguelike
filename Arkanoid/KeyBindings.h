#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid 
{
	class KeyBindings 
	{
		KeyBindings();

		~KeyBindings();

		const struct KeyBinds
		{
			sf::Keyboard::Key keyRight = sf::Keyboard::D;
			sf::Keyboard::Key keyLeft = sf::Keyboard::A;
			sf::Keyboard::Key keyUp = sf::Keyboard::W;
			sf::Keyboard::Key keyDown = sf::Keyboard::S;
			sf::Keyboard::Key keyEnter = sf::Keyboard::Enter;
			sf::Keyboard::Key keyEscape = sf::Keyboard::Escape;
			sf::Keyboard::Key none = sf::Keyboard::Unknown;
		};

		KeyBinds keyBinds;
		sf::Keyboard::Key pressedKey, holdingKey;

	public:
		KeyBindings(const KeyBindings& keyBindings) = delete;
		KeyBindings& operator= (const KeyBindings&) = delete;

		static KeyBindings& Instance();

		void PressedKey(sf::Event& event);
		KeyBinds GetKey();
		sf::Keyboard::Key GetKeyPressed();
		sf::Keyboard::Key GetKeyHolding();

	};
}