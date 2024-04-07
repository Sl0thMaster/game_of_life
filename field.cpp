#include "field.h"

Field::Field(int field_width, int field_height) {
    width = field_width;
    height = field_height;
    field = new bool[width * height];
}

Field::Field(const Field &other) {
    width = other.width;
    height = other.height;
    field = new bool[width * height];
    for (int i = 0; i < width * height; i++)
        *(field + i) = *(other.field + i);
}

Field::Field(Field &&other) : width(other.width), height(other.height), field(other.field) {
    other.field = new bool[width * height];
}

Field &Field::operator=(Field copy) {
    swap(copy);
    return *this;
}

Field::~Field() {
    delete[] field;
}

bool &Field::operator[](int index) {
    return *(field + index);
}

void Field::advance() {
    int alive_neighbors;
    bool* new_field = new bool[width * height];
    for (int i = 0; i < width * height; i++)
        *(new_field + i) = *(field + i);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            alive_neighbors = 0;
            for (int n_i = -1; n_i < 2; n_i++)
                for (int n_j = -1; n_j < 2; n_j++)
                    if (0 <= i + n_i && i + n_i < height && 0 <= j + n_j && j + n_j < width)
                        alive_neighbors += field[(i + n_i) * width + j + n_j];
            alive_neighbors -= field[i * width + j];
            if (!field[i * width + j] && alive_neighbors == 3)
                new_field[i * width + j] = true;
            else if (field[i * width + j] && (2 > alive_neighbors || alive_neighbors > 3))
                new_field[i * width + j] = false;
        }
    delete[] field;
    field = new_field;
}

void Field::toggle(int x, int y) {
    field[y * width + x] = !field[y * width + x];
}

void Field::clear() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            field[i * width + j] = false;
}

int *Field::living_cells() {
    int number_of_living_cells = 0;
    for (int i = 0; i < width * height; i++)
        if (field[i])
            number_of_living_cells++;
    int* result = new int[number_of_living_cells];
    int index = 0;
    for (int i = 0; i < width * height; i++)
        if (field[i])
            result[index++] = i;
    return result;
}

void Field::set(int *x, int size) {
    for (int k = 0; k < size; k++)
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (x[k] == i * width + j)
                    field[i * width + j] = true;
}

void Field::swap(Field &other) {
    std::swap(width, other.width);
    std::swap(height, other.height);
    std::swap(field, other.field);
}
