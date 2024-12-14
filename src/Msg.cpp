#include "Msg.h"
#include "Constants.h"

Msg::Msg(Text txt)
    : window(txt.getWindow()), text(txt)
{
    sf::FloatRect textRect = txt.getLocalBounds();
    rectangle.setSize(sf::Vector2f(textRect.width * 1.2f, textRect.height * 1.5f));
    rectangle.setOutlineColor(sf::Color::Blue);
    rectangle.setOutlineThickness(10.0f);
    rectangle.setFillColor(sf::Color(sf::Color(80, 0, 10)));
    sf::FloatRect rect = rectangle.getLocalBounds();
    rectangle.setOrigin(rect.left +
                        rect.width / 2.0f,
                        rect.top +
                        rect.height / 2.0f);
    rectangle.setPosition(MidWindow);
}


void Msg::draw()
{
    window.draw(rectangle);
    window.draw(text);
}
