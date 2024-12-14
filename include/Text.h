#ifndef TEXT_H
#define TEXT_H
#include "Constants.h"
#include "Fonts.h"

#include <string>

class Text : public sf::Text
{
    public:
        Text(const std::string& txt, sf::Font& font, unsigned size, sf::RenderWindow& win, const sf::Color color, const sf::Vector2f position = MidWindow);
        virtual ~Text();
        sf::RenderWindow& getWindow() const { return window; }
        void draw() { window.draw(*this); }

    private:
        sf::RenderWindow& window;
};

#endif // TEXT_H
