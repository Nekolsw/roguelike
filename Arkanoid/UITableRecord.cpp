#include "UITableRecord.h"
#include "Constants.h"
namespace Arkanoid
{

    void UITableRecord::SortedRecordTable()
    {
        sortedRecordsTable.clear();
        for (const auto& item : recordsTable)
        {
            sortedRecordsTable.insert(std::make_pair(item.second, item.first));
        }

    }

    void UITableRecord::SerializeRecordTable()
    {
        std::ofstream file(RECORDS_TABLE_NAME);
        if (file.is_open())
        {
            for (const auto& record : recordsTable)
            {
                file << record.first << " " << record.second << std::endl;
            }
            file.close();
        }
    }

    void UITableRecord::DeserializeRecordTable()
    {
        std::ifstream file(RECORDS_TABLE_NAME);
        if (file.is_open())
        {
            std::string name;
            int score;
            while (file >> name >> score)
            {
               recordsTable.insert(std::make_pair(name, score));
            }
            file.close();
        }
    }

    bool UITableRecord::SelectedEventButton(sf::Event& event)
    {
        isSelected = false;
        if (sf::Mouse::getPosition().x >= 850.f && sf::Mouse::getPosition().x <= 1110.f && sf::Mouse::getPosition().y >= 735.f && sf::Mouse::getPosition().y <= 785.f)
        {
            textStartGame.setFillColor(sf::Color::Green);
            if (event.type == event.MouseButtonPressed)
            {
                    isSelected = true;
                    return false;
            }
        }
        else
        {
            textStartGame.setFillColor(sf::Color::Cyan);
        }

        if (sf::Mouse::getPosition().x >= 850.f && sf::Mouse::getPosition().x <= 1110.f && sf::Mouse::getPosition().y >= 790.f && sf::Mouse::getPosition().y <= 840.f)
        {
            textMainMenu.setFillColor(sf::Color::Green);
            if (event.type == event.MouseButtonPressed)
            {
                isSelected = true;
                return true;
            }
        }
        else
        {
            textMainMenu.setFillColor(sf::Color::Cyan);
        }
    }

    void UITableRecord::InitializedTable(sf::Font& font)
    {
        SetTextScreen(textHeader, "Table Record", 46, sf::Color::Cyan, font, { 650.f, 190.f }, {0.5f, 0.5f});
        SetTextScreen(textStartGame, "Start game", 28, sf::Color::Cyan, font, { 650.f, 550.f }, { 0.5f, 0.5f });
        SetTextScreen(textMainMenu, "Main menu", 28, sf::Color::Cyan, font, { 650.f, 600.f }, { 0.5f, 0.5f });
        SetRectangleShape(gameOverBackground, { 400.f, 500.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 443.f, 160.f }, sf::Color::Cyan, 1.f);
        SetRectangleShape(tableRecordBackground, { 400.f, 500.f }, sf::Color(25, 25, 25, 235), { 0.5f, 0.5f }, { 443.f, 160.f }, sf::Color::Cyan, 1.f);
        SetRectangleShape(startGameBackground, { 260.f, 50.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 525.f, 525.f }, sf::Color::Cyan, 1.f);
        SetRectangleShape(mainMenuBackground, { 260.f, 50.f }, sf::Color(25, 25, 25, 255), { 0.5f, 0.5f }, { 525.f, 580.f }, sf::Color::Cyan, 1.f);
        DeserializeRecordTable(); 
        SortedRecordTable();

    }

    void UITableRecord::UpdateNumberScorePlayer(std::string namePlayerTable, int numberScore)
    {
        recordsTable[namePlayerTable] = std::max(recordsTable[namePlayerTable],
            numberScore);

        SortedRecordTable();
        SerializeRecordTable();
    }

    void UITableRecord::DrawTableGameOver(sf::RenderWindow& window, GameResources& recources, int numberDisplayedNames)
    {
        window.draw(gameOverBackground);
        window.draw(startGameBackground);
        window.draw(mainMenuBackground);
        window.draw(textHeader);
        window.draw(textStartGame);
        window.draw(textMainMenu);
        int i = 0;

        for (const auto& item : sortedRecordsTable)
        {
            if (i < numberDisplayedNames)
            {
                sf::Text textRecord;
                SetTextScreen(textRecord, (std::to_string(i + 1) + ". " + std::to_string(item.first) + " " + item.second), 32, sf::Color::Cyan, recources.fontText, { 500.f - 20.f, 400.f - 140.f + 42 * i }, { 0.f, 0.5f });
                window.draw(textRecord);
                ++i;
            }

        }

    }

    void UITableRecord::DrawTableRecord(sf::RenderWindow& window, sf::Font& font, int numberDisplayedNames)
    {
        window.draw(tableRecordBackground);
        window.draw(textHeader);

        int i = 0;
        for (const auto& item : sortedRecordsTable)
        {
            if (i < numberDisplayedNames)
            {
                sf::Text textRecord;
                SetTextScreen(textRecord, (std::to_string(item.first) + " " + item.second), 38, sf::Color::Cyan, font, { 500.f - 20.f, 400.f - 140.f + 42 * i }, { 0.f, 0.5f });
                window.draw(textRecord);
                ++i;
            }

        }
    }

    std::unordered_map<std::string, int> &UITableRecord::GetRecordTable()
    {
        return recordsTable;
    }


}