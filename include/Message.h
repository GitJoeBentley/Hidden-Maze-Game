#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "SFML/Graphics.hpp"


class Message
{
    public:
        Message(const std::string& text, const sf::Vector2f& popupsize, const sf::Vector2f& popuppop, const sf::Vector2f& textPos, sf::Font& font, unsigned charSize);
        void draw(sf::RenderWindow& wnd);

    protected:

    private:
        sf::RectangleShape popUp;
        sf::Text message;
};

#endif // MESSAGE_H
