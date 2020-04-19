/*
** EPITECH PROJECT, 2020
** for_norme
** File description:
** Button.cpp
*/

#include <iostream> // tmp // TODO add Error class
#include <cmath>
#include "Button.hpp"

Button::Button(const float &_semitones, const Color &color, const float &angle, const float &distance, const Vector2f &position)
{
    semitones = _semitones;
    colors[false] = color * Color(50, 50, 50);
    colors[true] = color;
    polygon.setPointCount(4);
    polygon.setPoint(0, sf::Vector2f(0, 0));
    polygon.setPoint(1, sf::Vector2f(300, 120));
    polygon.setPoint(2, sf::Vector2f(380, 0));
    polygon.setPoint(3, sf::Vector2f(300, -120));
    polygon.setFillColor(colors[false]);
    polygon.setOutlineColor(colors[true]);
    polygon.setOutlineThickness(5); // ?
    polygon.rotate(angle * 180.0 / M_PI + 50);
    polygon.setPosition(cos(angle) * distance + position.x, sin(angle) * distance + position.y);
    pressTime = seconds(0.5);
    if (!sound.openFromFile("Resources/Sound/Note.ogg"))
        cerr << "sound can't be load" << endl; // TODO add Error class
}

Button::~Button()
{
    sound.stop();
}

bool Button::contains(const Vector2f &point)
{
    bool var;

    for (size_t i = 0; i < polygon.getPointCount(); i++) {
        const Transform transform = polygon.getTransform();
        Vector2f p1 = polygon.getPoint(i);
        Vector2f p2 = polygon.getPoint((i + 1) % polygon.getPointCount());

        p1 = transform.transformPoint(p1);
        p2 = transform.transformPoint(p2);
        bool b = (point.x - p1.x) * (p1.y - p2.y) - (point.y - p1.y) * (p1.x - p2.x) > 0;

        if (i == 0)
            var = b;
        else if (var ^ b)
            return false;
    }
    return true;
}

void Button::press()
{
    polygon.setFillColor(colors[true]);
    playSound();
    clock.restart();
}

void Button::update()
{
    if (clock.getElapsedTime() >= pressTime)
        polygon.setFillColor(colors[false]);
}

void Button::aff(RenderTarget &target) const
{
    target.draw(polygon);
}

void Button::null()
{
    Color color(120, 120, 120);

    colors[false] = color * Color(50, 50, 50);
    colors[true] = color;

    polygon.setFillColor(colors[false]);
    polygon.setOutlineColor(colors[true]);
}

void Button::playSound()
{
    sound.stop();
    sound.setPitch(pow(2, semitones / 12.0));
    sound.play();
}
