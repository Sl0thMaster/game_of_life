#include <SFML/Graphics.hpp>
#include <iostream>
#include "field.h"

const int WIDTH = 26;
const int HEIGHT = 18;
const int SIDE_OF_SQUARE = 40;
const int FPS = 60;
int set_0[5] = {28, 55, 79, 80, 81};
int set_1[36] = {77, 127, 129, 169, 170, 177, 178, 191, 192, 220, 224,
                 229, 230, 243, 244, 261, 262, 271, 277,281, 282,
                 313, 314, 323, 327, 329, 330, 335, 337, 375, 381,
                 389, 428, 432, 481, 482};
int step = 0;
int game_speed = 3;
bool paused = true;
bool button1_available = true;
bool button2_available = true;
int field_scale = 2;

int main()
{
    Field field = Field(field_scale * WIDTH, field_scale * HEIGHT);
    field.clear();
    field.set(set_1, std::size(set_1));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game of life", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(FPS);

    sf::Event event;

    sf::RectangleShape cell(sf::Vector2f(SIDE_OF_SQUARE / field_scale, SIDE_OF_SQUARE / field_scale));
    cell.setFillColor(sf::Color::White);

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
                        field.toggle(m_position.x / (SIDE_OF_SQUARE / field_scale), m_position.y / (SIDE_OF_SQUARE / field_scale));
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
        if (step % (32 >> game_speed) == 0 && !paused) {
            field.advance();
            step = 0;
        }
//        Наполнение поля живыми клетками
        for (int i = 0; i < field_scale * HEIGHT; i++)
            for (int j = 0; j < field_scale * WIDTH; j++)
                if (field[i * field_scale * WIDTH + j]) {
                    cell.setPosition(j * SIDE_OF_SQUARE / field_scale,i * SIDE_OF_SQUARE / field_scale);
                    window.draw(cell);
                }
//        Сетка поля
        for (int i = 0; i < WIDTH * SIDE_OF_SQUARE; i++)
            for (int j = 0; j < HEIGHT * SIDE_OF_SQUARE; j++)
                if ((i + 1) % (SIDE_OF_SQUARE / field_scale) <= 1 || (j + 1) % (SIDE_OF_SQUARE / field_scale) <= 1) {
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
