#pragma once
#include "UIScore.h"
#include "UIMainMenu.h"
#include "UIEnterName.h"
#include "UIPopUpEnterName.h"
#include "Resources.h"
#include "GameSettings.h"

namespace Roguelike 
{
	class UIManager
	{
		struct Interface 
		{
			UIScore uiScore;
			UITableRecord uiTableRecord;
			UIMainMenu uiMainMenu;
			UIEnterName uiEnterName;
			UIPopUpEnterName uiPopUpEnterName;
		};

		int numberScore = 0, numberPlayerNameGameOverTable = 5;
		GameResources resources;
		Interface interfaces;
		void PopUpEnteredName(sf::Event& event);
		void PopUpTableRecord(sf::Event& event);
		void EnterNamePlayer(sf::Event& event);
		void AddPlayerInTable(std::string namePlayerTable, int numberScore);
		void ManagementMainMenu(sf::Window& window);
	public:
		GameSettings gameSettings;
		enum class InterfaceState
		{
			MainMenu = 0,
			Game,
			EnterName,
			IsEnterName,
			PopUpTableRecord,
			MenuItem
		};
		InterfaceState interfaceState;

		enum GameState
		{
			Playing = 0,
			Restart,
			Pause
		};

		GameState gameState;

		void InitializationUIManager();
		void UpdateScore();
		void AddScore(GameSettings::TypeBrick typeBrick);
		int GetScore();
		void ResetScore();
		void IsGameWon(bool isWinning);
		void DrawUI(sf::RenderWindow& window);
		void UpdateEvent(sf::Event& event, sf::Window& window);

	};

}
