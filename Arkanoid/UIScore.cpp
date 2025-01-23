#include "UIScore.h"

namespace Arkanoid
{
	void UIScore::InitializingScore(sf::Font& font)
	{

		SetTextScreen(scoreUI, "Score: 0", TEXT_SCORE_SIZE, sf::Color::Cyan, font, { 1000.f, 10.f }, { 0, 0 });
	}
	void UIScore::UpdateScore(int& numberScore)
	{
		UpdateTextScreen(scoreUI, "Score: " + std::to_string(numberScore));
	}
	void UIScore::DrawScore(sf::RenderWindow& window)
	{
		window.draw(scoreUI);
	}
}
