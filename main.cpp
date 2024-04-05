#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 26;
const int HEIGHT = 18;
const int SIDE_OF_SQUARE = 40;
//int set_0[5] = {18, 35, 49, 50, 51};
int step = 0;
bool paused = true;

class Field {
public:
    Field(): field(new bool[WIDTH * HEIGHT]) {}
    bool& operator[](int index) {
        return *(field + index);
    }
    void update() {
        int alive_neighbors;
        bool* new_field = new bool[WIDTH * HEIGHT];
        for (int i = 0; i < WIDTH * HEIGHT; i++)
            *(new_field + i) = *(field + i);
        for (int i = 1; i < HEIGHT - 1; i++)
            for (int j = 1; j < WIDTH - 1; j++) {
                alive_neighbors = 0;
                for (int n_i = -1; n_i < 2; n_i++)
                    for (int n_j = -1; n_j < 2; n_j++)
                        alive_neighbors += field[(i + n_i) * WIDTH + j + n_j];
                alive_neighbors -= field[i * WIDTH + j];
                if (!field[i * WIDTH + j] && alive_neighbors == 3)
                    new_field[i * WIDTH + j] = true;
                else if (field[i * WIDTH + j] && (2 > alive_neighbors || alive_neighbors > 3))
                    new_field[i * WIDTH + j] = false;
            }
        delete[] field;
        field = new_field;
    }
    void toggle(int x, int y) {
        field[y * WIDTH + x] = !field[y * WIDTH + x];
    }
    void clear() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                field[i * WIDTH + j] = false;
    }
    void set(int* x, int size) {
        for (int k = 0; k < size; k++)
            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++)
                    if (x[k] == i * WIDTH + j)
                        field[i * WIDTH + j] = true;
    }
    void show() {
        std::cout << std::endl;
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                std::cout << field[i * WIDTH + j] << ' ';
            std::cout << std::endl;
        }
    }

private:
    bool* field;
};

int main()
{
    Field field;
    field.clear();
//    field.set(set_0, std::size(set_0));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game of life");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::RectangleShape rectangle(sf::Vector2f(SIDE_OF_SQUARE, SIDE_OF_SQUARE));
    rectangle.setFillColor(sf::Color::White);

    sf::RectangleShape rectangle2(sf::Vector2f(6 * SIDE_OF_SQUARE, 18 * SIDE_OF_SQUARE));
    rectangle2.setFillColor(sf::Color::White);
    rectangle2.setPosition(26 * SIDE_OF_SQUARE, 0);

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
                }
            }
        }

        window.clear();
        step++;
        if (step % 11 == 0 && !paused) {
            field.update();
            step = 0;
        }
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                if (field[i * WIDTH + j]) {
                    rectangle.setPosition(j * SIDE_OF_SQUARE,i * SIDE_OF_SQUARE);
                    window.draw(rectangle);
                }
        window.draw(rectangle2);
        window.display();
    }

    return 0;
}

