/*
** EPITECH PROJECT, 2020
** for_norme
** File description:
** Button.hpp
*/

#pragma once

#include <list>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button
{
public:
    Button(const Color &color, const float &angle, const float &distance, const Vector2f &position = Vector2f(0, 0));
    bool contains(const Vector2f &point);
    void press();
    void update();
    void aff(RenderTarget &target) const;
    void null(); // TODO rename

private:
    ConvexShape polygon;
    array<Color, 2> colors;
    Time pressTime;
    Clock clock;
};
