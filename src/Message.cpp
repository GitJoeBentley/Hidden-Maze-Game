#include "Message.h"
#include "Constants.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
using namespace sf;

Message::Message(const string& msg, const Vector2f& popupSize, const Vector2f& popupPos, const Vector2f& textPos, Font& font, unsigned charSize)
    : popUp(popupSize), message(msg, font)
{
    popUp.setPosition(popupPos);
    popUp.setOutlineColor(sf::Color::Yellow);
    popUp.setOutlineThickness(10.0f);
    popUp.setFillColor(sf::Color(sf::Color::Black));
    message.setCharacterSize(charSize);
    message.setPosition(textPos);
    message.setFillColor(sf::Color::White);
    message.setString(msg);
}

void Message::draw(sf::RenderWindow& wnd)
{
    wnd.draw(popUp);
    wnd.draw(message);
}
