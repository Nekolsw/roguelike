#include "UIManager.h"

namespace Roguelike 
{
	void UIManager::InitializationUIManager()
	{
		InitializingResources(resources);
		interfaces.uiScore.InitializingScore(resources.fontText);
		interfaces.uiMainMenu.InitializedMainMenu(resources.fontText);
		interfaces.uiEnterName.InitializedMainMenu(resources.fontText);
		interfaces.uiPopUpEnterName.InitializedMainMenu(resources.fontText);
		interfaceState = InterfaceState::MainMenu;
	}


	void UIManager::UpdateScore()
	{

		interfaces.uiScore.UpdateScore(numberScore);
	}

	void UIManager::AddScore()
	{

		numberScore++;
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
			gameState = UIManager::GameState::Pause;
		}
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

	void UIManager::EnterNamePlayer(sf::Event& event) 
	{
		if (interfaceState == InterfaceState::EnterName)
		{
			interfaces.uiEnterName.EnterPlayerName(event, resources);

			if (interfaces.uiEnterName.isPlayerNameEnter)
			{
				ResetScore();
				UpdateScore();
			}
		}
	}

	void UIManager::DrawUI(sf::RenderWindow& window)
	{
		switch (interfaceState)
		{
		case Roguelike::UIManager::InterfaceState::MainMenu:
			interfaces.uiMainMenu.DrawMainMenu(window, resources.fontText);
			break;
		case Roguelike::UIManager::InterfaceState::Game:
			interfaces.uiScore.DrawScore(window);
			break;
		case Roguelike::UIManager::InterfaceState::IsEnterName:
			interfaces.uiPopUpEnterName.DrawPopUp(window);
			break;
		case Roguelike::UIManager::InterfaceState::EnterName:
			interfaces.uiEnterName.DrawEnterText(window);
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
		case Roguelike::UIManager::InterfaceState::Game:
			break;
		case UIManager::InterfaceState::IsEnterName:
			PopUpEnteredName(event);
			break;
		case UIManager::InterfaceState::MainMenu:
			ManagementMainMenu(window);
		}
	}

}