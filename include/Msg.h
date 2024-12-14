#ifndef MSG_H
#define MSG_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Text.h"


class Msg
{
public:
    Msg(Text txt);
    //Msg(sf::RenderWindow& wnd, const std::string& txt, sf::Font& font, unsigned size, const sf::Color& color);
    void draw();
private:
    sf::RenderWindow& window;
    Text text;
    sf::RectangleShape rectangle;

};

#endif // MSG_H
