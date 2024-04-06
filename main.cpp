#include <SFML/Graphics.hpp>
#include <iostream>
#include "field.h"

const int SIDE_OF_SQUARE = 40;
const int FPS = 60;
int set_0[5] = {28, 55, 79, 80, 81};
int step = 0;
int game_speed = 3;
bool paused = true;
bool button1_available = true;
bool button2_available = true;

int main()
{
    Field field;
    field.clear();
//    field.set(set_0, std::size(set_0));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game of life");
    window.setFramerateLimit(FPS);

    sf::Event event;

    sf::RectangleShape rectangle(sf::Vector2f(SIDE_OF_SQUARE, SIDE_OF_SQUARE));
    rectangle.setFillColor(sf::Color::White);

    sf::RectangleShape pixel(sf::Vector2f(1, 1));
    pixel.setFillColor(sf::Color::Black);

    sf::RectangleShape transparent(sf::Vector2f(2 * SIDE_OF_SQUARE, 2 * SIDE_OF_SQUARE));
    transparent.setFillColor(sf::Color(0, 0, 0, 128));

    sf::Font font;
    font.loadFromFile("slkscr.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(120);
    text.setFillColor(sf::Color::White);

    sf::Sprite play;
    sf::Sprite pause;
    sf::Sprite speed1;
    sf::Sprite speed2;
    sf::Sprite frame;

    sf::Texture texture1;
    texture1.loadFromFile("textures/play.png");
    play.setTexture(texture1);
    sf::Texture texture2;
    texture2.loadFromFile("textures/pause.png");
    pause.setTexture(texture2);
    sf::Texture texture3;
    texture3.loadFromFile("textures/speed.png");

    speed1.setTexture(texture3);
    speed2.setTexture(texture3);
    speed1.rotate(180);
    play.setPosition(27 * SIDE_OF_SQUARE,15 * SIDE_OF_SQUARE);
    pause.setPosition(27 * SIDE_OF_SQUARE,15 * SIDE_OF_SQUARE);
    speed2.setPosition(29 * SIDE_OF_SQUARE,4 * SIDE_OF_SQUARE);
    speed1.setPosition(29 * SIDE_OF_SQUARE,6 * SIDE_OF_SQUARE);
    text.setPosition(28 * SIDE_OF_SQUARE,0);

    sf::Texture texture4;
    texture4.loadFromFile("textures/frame.png");
    frame.setTexture(texture4);
    frame.setPosition(26 * SIDE_OF_SQUARE,0);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i m_position = sf::Mouse::getPosition(window);
                    int mouse_x = m_position.x / SIDE_OF_SQUARE;
                    int mouse_y = m_position.y / SIDE_OF_SQUARE;
                    if (mouse_x < WIDTH)
                        field.toggle(mouse_x, mouse_y);
                    else if (27 <= mouse_x && mouse_x < 31 && 15 <= mouse_y && mouse_y < 17)
                        paused = !paused;
                    else if (29 <= mouse_x && mouse_x < 31 && 4 <= mouse_y && mouse_y < 6 && button2_available) {
                        game_speed++;
                        if (game_speed == 5)
                            button2_available = false;
                        button1_available = true;
                    } else if (27 <= mouse_x && mouse_x < 29 && 4 <= mouse_y && mouse_y < 6 && button1_available) {
                        game_speed--;
                        if (game_speed == 1)
                            button1_available = false;
                        button2_available = true;
                    }
                }
            }
        }

        window.clear();
        window.draw(frame);
//        Обновление поля
        step++;
        if (step % (FPS/(game_speed * game_speed) - 1) == 0 && !paused) {
            field.update();
            step = 0;
        }
//        Наполнение поля живыми клетками
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                if (field[i * WIDTH + j]) {
                    rectangle.setPosition(j * SIDE_OF_SQUARE,i * SIDE_OF_SQUARE);
                    window.draw(rectangle);
                }
//        Сетка поля
        for (int i = 0; i < 26 * SIDE_OF_SQUARE; i++)
            for (int j = 0; j < 18 * SIDE_OF_SQUARE; j++)
                if ((i + 1) % SIDE_OF_SQUARE <= 1 || (j + 1) % SIDE_OF_SQUARE <= 1) {
                    pixel.setPosition(i, j);
                    window.draw(pixel);
                }
//        Кнопка паузы
        if (paused)
            window.draw(play);
        else
            window.draw(pause);
//        Настройки скорости игры
        text.setString(std::to_string(game_speed));
        window.draw(text);
        window.draw(speed1);
        window.draw(speed2);
        if (!button1_available) {
            transparent.setPosition(27 * SIDE_OF_SQUARE, 4 * SIDE_OF_SQUARE);
            window.draw(transparent);
        }
        if (!button2_available) {
            transparent.setPosition(29 * SIDE_OF_SQUARE, 4 * SIDE_OF_SQUARE);
            window.draw(transparent);
        }

        window.display();
    }

    return 0;
}
