#include "KeyBindings.h"

namespace Arkanoid 
{
	KeyBindings::KeyBindings()
	{
		pressedKey = sf::Keyboard::Key::Unknown;
	}

	KeyBindings::~KeyBindings()
	{

	}
	KeyBindings& KeyBindings::Instance()
	{
		static KeyBindings instance;
		return instance;
	}
	void KeyBindings::PressedKey(sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == keyBinds.keyRight)
			{
				pressedKey = keyBinds.keyRight;
				holdingKey = keyBinds.keyRight;
			}
			if (event.key.code == keyBinds.keyLeft)
			{
				pressedKey = keyBinds.keyLeft;
				holdingKey = keyBinds.keyLeft;
			}
			if (event.key.code == keyBinds.keyUp)
			{
				pressedKey = keyBinds.keyUp;
				holdingKey = keyBinds.keyUp;
			}
			if (event.key.code == keyBinds.keyDown)
			{
				pressedKey = keyBinds.keyDown;
				holdingKey = keyBinds.keyDown;
			}
			if (event.key.code == keyBinds.keyEnter)
			{
				pressedKey = keyBinds.keyEnter;
				holdingKey = keyBinds.keyEnter;
			}
			if (event.key.code == keyBinds.keyEscape)
			{
				pressedKey = keyBinds.keyEscape;
				holdingKey = keyBinds.keyEscape;
			}
		}
		else 
		{
			pressedKey = keyBinds.none;
		}
		if (event.type == sf::Event::KeyReleased)
		{
			pressedKey = keyBinds.none;
			holdingKey = keyBinds.none;
		}
	}
	KeyBindings::KeyBinds KeyBindings::GetKey()
	{
		return keyBinds;
	}
	sf::Keyboard::Key KeyBindings::GetKeyPressed()
	{
			return pressedKey;
	}
	sf::Keyboard::Key KeyBindings::GetKeyHolding()
	{
		return holdingKey;
	}
};