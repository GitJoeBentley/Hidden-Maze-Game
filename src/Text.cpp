#include "Text.h"

Text::Text(const std::string& txt, sf::Font& font, unsigned size, sf::RenderWindow& win, const sf::Color color, const sf::Vector2f position)
    :  sf::Text(txt, font, size), window(win)
{
    setFillColor(color);
    sf::FloatRect textRect = getLocalBounds();
    setOrigin(textRect.left +
                   textRect.width / 2.0f,
                   textRect.top +
                   textRect.height / 2.0f);
    setPosition(position);
}

Text::~Text()
{
    //dtor
}
