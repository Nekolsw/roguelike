#include <SFML/Graphics.hpp>
#include "UIMath.h"

namespace Arkanoid
{

	void SetTextRelativeOrigin(sf::Text& text, const UIPosition2D& relativePosition)
	{
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin((textRect.left + textRect.width) * relativePosition.x, (textRect.top + textRect.height) * relativePosition.y);
	}


}
