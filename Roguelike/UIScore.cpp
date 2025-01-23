#include "UIScore.h"

namespace Roguelike
{
	void UIScore::InitializingScore(sf::Font& font)
	{

		SetTextScreen(scoreUI, "TO BE DONE... Press Esc to exit to menu", TEXT_SCORE_SIZE, sf::Color::Cyan, font, { 500.f, 500.f }, { 0, 0 });
	}
	void UIScore::UpdateScore(int& numberScore)
	{
		UpdateTextScreen(scoreUI, "Score: "  + std::to_string(numberScore));
	}
	void UIScore::DrawScore(sf::RenderWindow& window)
	{
		window.draw(scoreUI);
	}
}
