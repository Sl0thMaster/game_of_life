#include "field.h"

Field::Field() : field(new bool[WIDTH * HEIGHT]) {}

bool &Field::operator[](int index) {
    return *(field + index);
}

void Field::update() {
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

void Field::toggle(int x, int y) {
    field[y * WIDTH + x] = !field[y * WIDTH + x];
}

void Field::clear() {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            field[i * WIDTH + j] = false;
}

void Field::set(int *x, int size) {
    for (int k = 0; k < size; k++)
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                if (x[k] == i * WIDTH + j)
                    field[i * WIDTH + j] = true;
}
