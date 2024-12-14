#ifndef FONTS_H
#define FONTS_H
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>


class Fonts
{
public:
    Fonts();
    ~Fonts();
    sf::Font& font(const std::string& name) { return *(fonts[name]); }

private:
    std::map<std::string, sf::Font*> fonts;
};

#endif // FONTS_H
