#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"


class Player
{
    public:
        Player();
        virtual ~Player();

    protected:

    private:
        sf::Sprite player;
};

#endif // PLAYER_H
