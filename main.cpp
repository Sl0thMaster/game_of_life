#include <iostream>

const int WIDTH = 16;
const int HEIGHT = 9;
int set_0[5] = {18, 35, 49, 50, 51};

class Field {
public:
    Field(): field(new bool[WIDTH * HEIGHT]) {}

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


int main() {
    Field field;
    field.clear();
    field.set(set_0, std::size(set_0));
    field.show();
    for (int i = 0; i < 5; i++) {
        field.update();
        field.show();
    }
    return 0;
}


