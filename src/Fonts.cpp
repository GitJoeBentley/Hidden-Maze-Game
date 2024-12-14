#include "Fonts.h"
#include "Constants.h"
#include <iostream>
using namespace std;

Fonts::Fonts()
{
    string temp;
    for (size_t i = 0; i < FontNames.size(); i++)
    {
        fonts[FontNames[i]] = new sf::Font;
        temp = ResourcePath + FontNames[i] + ".ttf";
        fonts[FontNames[i]]->loadFromFile(temp);
    }
}

Fonts::~Fonts()
{
    for (size_t i = 0; i < FontNames.size(); i++)
    {
        delete fonts[FontNames[i]];
        fonts[FontNames[i]] = nullptr;
    }
}

