/*
** EPITECH PROJECT, 2020
** for_norme
** File description:
** Game.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

using namespace std;
using namespace sf;

class Game
{
public:
    Game();
    void run();

private:
    void createButtons();
    void pressButton(const Vector2f &mousePosition);
    void levelUp(); // rename ??
    void displayPressOrder();

private:
    RenderWindow window;
    vector<Button> buttons;
    vector<Button*> pressOrder;
    size_t index;
    bool canPlay;
    Thread displayThread;
};
