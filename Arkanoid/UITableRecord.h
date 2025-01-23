#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include "UIConstructor.h"
#include "Resources.h"
namespace Roguelike
{
	class UITableRecord
	{
		sf::Text textHeader, textStartGame, textMainMenu;
		sf::RectangleShape gameOverBackground, tableRecordBackground, startGameBackground, mainMenuBackground;
		std::unordered_map<std::string, int> recordsTable;
		std::multimap<int, std::string, std::greater<int>> sortedRecordsTable;
		void SortedRecordTable();
		void SerializeRecordTable();
		void DeserializeRecordTable();
	public:
		bool isSelected = false;
		bool SelectedEventButton(sf::Event& event);
		void InitializedTable(sf::Font& font);
		void UpdateNumberScorePlayer(std::string namePlayerTable, int numberScore); 
		void DrawTableGameOver(sf::RenderWindow& window, GameResources& recources, int numberDisplayedNames);
		void DrawTableRecord(sf::RenderWindow& window, sf::Font& font, int numberDisplayedNames);
		std::unordered_map<std::string, int> &GetRecordTable();

	};
}
