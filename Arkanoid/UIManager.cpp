#include "UIManager.h"

namespace Arkanoid 
{
	void UIManager::InitializationUIManager()
	{
		InitializingResources(resources);
		interfaces.uiScore.InitializingScore(resources.fontText);
		interfaces.uiTableRecord.InitializedTable(resources.fontText);
		interfaces.uiMainMenu.InitializedMainMenu(resources.fontText);
		interfaces.uiEnterName.InitializedMainMenu(resources.fontText);
		interfaces.uiPopUpEnterName.InitializedMainMenu(resources.fontText);
		interfaceState = InterfaceState::MainMenu;
	}


	void UIManager::UpdateScore()
	{

		interfaces.uiScore.UpdateScore(numberScore);
	}

	void UIManager::AddScore(GameSettings::TypeBrick typeBrick)
	{
		int addNumberScore = 0;

		switch (typeBrick)
		{
		case GameSettings::TypeBrick::Standart:
			addNumberScore = 2;
			break;
		case GameSettings::TypeBrick::Glass:
			addNumberScore = 1;
			break;
		case GameSettings::TypeBrick::Protected:
			addNumberScore = 3;
			break;
		default:
			break;
		}

		numberScore += addNumberScore;
		UpdateScore();
	}
	int UIManager::GetScore()
	{
		return numberScore;
	}
	void UIManager::ResetScore()
	{
		numberScore = 0;
	}

	void UIManager::IsGameWon(bool isWinning)
	{
		if(isWinning) 
		{
			interfaceState = UIManager::InterfaceState::EnterName;
			gameState = UIManager::GameState::Pause;
		}
		else 
		{
			interfaceState = UIManager::InterfaceState::PopUpTableRecord;
			gameState = UIManager::GameState::Pause;
		}
	}

	void UIManager::AddPlayerInTable(std::string namePlayerTable, int numberScore)
	{
		interfaces.uiTableRecord.UpdateNumberScorePlayer(namePlayerTable, numberScore);
	}

	void UIManager::ManagementMainMenu(sf::Window& window)
	{

		gameState = GameState::Pause; 
		bool isMenuClosed = interfaces.uiMainMenu.ChoiceItemMenu(window, gameSettings, resources);
		if (isMenuClosed) 
		{
			gameState = GameState::Restart;
			interfaceState = InterfaceState::Game;
		}
		
	}

	void UIManager::PopUpEnteredName(sf::Event& event)
	{
		if (interfaceState == InterfaceState::IsEnterName) 
		{
			bool willNameEntered = interfaces.uiPopUpEnterName.PopUpWillNameEntered(event);

			if (willNameEntered && interfaces.uiPopUpEnterName.answerIsSelected)
			{
				interfaceState = InterfaceState::EnterName;
				
			}
			else if (!willNameEntered && interfaces.uiPopUpEnterName.answerIsSelected)
			{
				ResetScore();
				UpdateScore();
				interfaceState = InterfaceState::MainMenu;
			}
		}
	}

	void UIManager::PopUpTableRecord(sf::Event& event)
	{
		bool isSelectedMainMenu = interfaces.uiTableRecord.SelectedEventButton(event);

		if (interfaceState == InterfaceState::PopUpTableRecord)
		{

			if (interfaces.uiTableRecord.isSelected && isSelectedMainMenu)
			{
				interfaceState = InterfaceState::MainMenu;
			}
			else if (interfaces.uiTableRecord.isSelected && !isSelectedMainMenu) 
			{
				interfaceState = InterfaceState::Game;
				gameState = GameState::Restart;
			}
		}
	}

	void UIManager::EnterNamePlayer(sf::Event& event) 
	{
		if (interfaceState == InterfaceState::EnterName)
		{
			interfaces.uiEnterName.EnterPlayerName(event, resources);

			if (interfaces.uiEnterName.isPlayerNameEnter)
			{
				interfaceState = InterfaceState::PopUpTableRecord;
				AddPlayerInTable(interfaces.uiEnterName.playerName, numberScore);
				ResetScore();
				UpdateScore();
			}
		}
	}

	void UIManager::DrawUI(sf::RenderWindow& window)
	{
		switch (interfaceState)
		{
		case Arkanoid::UIManager::InterfaceState::MainMenu:
			interfaces.uiMainMenu.DrawMainMenu(window, resources.fontText, interfaces.uiTableRecord);
			break;
		case Arkanoid::UIManager::InterfaceState::Game:
			interfaces.uiScore.DrawScore(window);
			break;
		case Arkanoid::UIManager::InterfaceState::IsEnterName:
			interfaces.uiPopUpEnterName.DrawPopUp(window);
			break;
		case Arkanoid::UIManager::InterfaceState::EnterName:
			interfaces.uiEnterName.DrawEnterText(window);
			break;
		case Arkanoid::UIManager::InterfaceState::PopUpTableRecord:
			interfaces.uiTableRecord.DrawTableGameOver(window, resources, numberPlayerNameGameOverTable);
			break;

		default:
			break;
		}
	}

	void UIManager::UpdateEvent(sf::Event& event, sf::Window& window)
	{
		switch (interfaceState)
		{
		case UIManager::InterfaceState::EnterName:
			EnterNamePlayer(event);
			break;
		case UIManager::InterfaceState::Game:
			break;
		case UIManager::InterfaceState::PopUpTableRecord:
			PopUpTableRecord(event);
			break;
		case UIManager::InterfaceState::IsEnterName:
			PopUpEnteredName(event);
			break;
		case UIManager::InterfaceState::MainMenu:
			ManagementMainMenu(window);
		}
	}

}