#pragma once
#include "UIConstructor.h"
#include "GameSettings.h"
namespace Arkanoid
{
	class UISettings
	{
		sf::Text textHeader, textMusic, textSound;
		sf::RectangleShape settingsBackground, checkSound, checkMusic;
		sf::Sound soundGame;
	public:
		enum class SettingsItems
		{
			Sound = 0,
			Music
		};

		void InitializedSettings(sf::Font& font);
		void Playback(sf::SoundBuffer& buffer, GameSettings& gameSettings);
		bool ChoiceSettings(GameSettings& gameSettings, GameResources& gameResources);
		void DrawSettings(sf::RenderWindow& window);
	private:
		SettingsItems settingsItems = SettingsItems::Sound;
	};
}
