/*
** EPITECH PROJECT, 2020
** for_norme
** File description:
** Game.cpp
*/

#include <cmath>
#include "Game.hpp"

Game::Game()
    : displayThread(&Game::displayPressOrder, this)
{
    const VideoMode desktopMode = VideoMode::getDesktopMode();
    const Vector2u desktopSize(desktopMode.width, desktopMode.height);
    ContextSettings settings;

    srand(time(nullptr));
    settings.antialiasingLevel = 8; // ?
    window.create(VideoMode(900, 900), "Simon", Style::Close, settings);
    window.setPosition(Vector2i(desktopSize - window.getSize()) / 2);
    window.setFramerateLimit(30);
    createButtons();
    while (pressOrder.size() < 3)
        levelUp();
    canPlay = false;
}

void Game::run()
{
    displayThread.launch();
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed && canPlay)
                pressButton(Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
        window.clear();
        for (Button &button : buttons) {
            button.update();
            button.aff(window);
        }
        window.display();
    }
}

void Game::createButtons()
{
    const vector<Color> colors = {
        Color::Red,
        Color(255, 255, 0),
        Color::Green,
        Color(0, 255, 255),
        Color::Blue,
        Color(255, 0, 255),
    };

    for (size_t i = 0; i < colors.size(); i++)
        buttons.push_back(Button(colors[i], 2 * i * M_PI / (float)colors.size(), 50, Vector2f(window.getSize()) / (float)2));
}

void Game::pressButton(const Vector2f &mousePosition)
{
    for (Button &button : buttons)
        if (button.contains(mousePosition)) {
            button.press();
            if (&button != pressOrder[index]) {
                canPlay = false;
                for (Button &button2 : buttons)
                    button2.null();
            }
            else {
                index++;
                if (index >= pressOrder.size()) {
                    canPlay = false;
                    levelUp();
                    displayThread.launch();
                }
            }
        }
}

void Game::levelUp()
{
    pressOrder.push_back(&buttons[rand() % buttons.size()]);
    index = 0;
}

void Game::displayPressOrder()
{
    sleep(seconds(1));
    for (Button *button : pressOrder) {
        button->press();
        sleep(seconds(0.7));
    }
    canPlay = true;
}
