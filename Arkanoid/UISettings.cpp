#include "UISettings.h"
#include "KeyBindings.h"

namespace Roguelike
{
	void UISettings::InitializedSettings(sf::Font& font)
	{

		SetTextScreen(textHeader, "Settings", 48, sf::Color::Cyan, font, { 650.f, 190.f }, { 0.5f, 0.5f });
		SetTextScreen(textSound, "Sounds", 36, sf::Color::Green, font, { 550.f, 230.f }, { 0.f, 0.f });
		SetTextScreen(textMusic, "Music", 36, sf::Color::Cyan, font, { 550.f, 280.f }, { 0.f, 0.f });
		SetRectangleShape(settingsBackground, { 400.f, 200.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 443.f, 160.f }, sf::Color::Cyan, 1.f);
		SetRectangleShape(checkSound, { 40.f, 40.f }, sf::Color::Cyan, { 0.5f, 0.5f }, { 740.f, 235.f }, sf::Color(25, 25, 25, 255), 2.f);
		SetRectangleShape(checkMusic, { 40.f, 40.f }, sf::Color::Cyan, { 0.5f, 0.5f }, { 740.f, 285.f }, sf::Color(25, 25, 25, 255), 2.f);
	}
	void UISettings::Playback(sf::SoundBuffer& buffer, GameSettings& gameSettings)
	{
		if (gameSettings.isPlaySound)
		{
			soundGame.setBuffer(buffer);
			soundGame.play();
		}
	}

	bool UISettings::ChoiceSettings(GameSettings& gameSettings, GameResources& gameResources)
	{
		switch (KeyBindings::Instance().GetKeyPressed())
		{
		case sf::Keyboard::W:
			Playback(gameResources.menuHover, gameSettings);
			settingsItems = SettingsItems::Sound;
			textSound.setFillColor(sf::Color::Green);
			textMusic.setFillColor(sf::Color::Cyan);
			break;

		case sf::Keyboard::S:
			Playback(gameResources.menuHover, gameSettings);
			settingsItems = SettingsItems::Music;
			textSound.setFillColor(sf::Color::Cyan);
			textMusic.setFillColor(sf::Color::Green);
			break;
		case sf::Keyboard::Enter:
			Playback(gameResources.menuEnter, gameSettings);
			if (settingsItems == SettingsItems::Sound) 
			{
				gameSettings.isPlaySound = !gameSettings.isPlaySound;
				if (gameSettings.isPlaySound)
				{
					SetRectangleShape(checkSound, { 40.f, 40.f }, sf::Color::Cyan, { 0.5f, 0.5f }, { 740.f, 235.f }, sf::Color(25, 25, 25, 255), 2.f);
				}
				else 
				{
					SetRectangleShape(checkSound, { 40.f, 40.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 740.f, 235.f }, sf::Color::Cyan, 2.f);
				}
				break;
			}
			else 
			{
				gameSettings.isPlayMusic = !gameSettings.isPlayMusic;
				if (gameSettings.isPlayMusic)
				{
					SetRectangleShape(checkMusic, { 40.f, 40.f }, sf::Color::Cyan, { 0.5f, 0.5f }, { 740.f, 285.f }, sf::Color(25, 25, 25, 255), 2.f);
				}
				else
				{
					SetRectangleShape(checkMusic, { 40.f, 40.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 740.f, 285.f }, sf::Color::Cyan, 2.f);
				}
				break;
			}
		case sf::Keyboard::Escape:
			return true;
		default:
			break;
	}
	return false;
}
	void UISettings::DrawSettings(sf::RenderWindow& window)
	{
		window.draw(settingsBackground);
		window.draw(textHeader);
		window.draw(textSound);
		window.draw(textMusic);
		window.draw(checkSound);
		window.draw(checkMusic);

	}
}
