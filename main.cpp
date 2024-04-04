#include <iostream>

const int WIDTH = 16;
const int HEIGHT = 9;
int set_0[4] = {18, 22, 23, 24};

class Field {
public:
    Field(): field(new bool[WIDTH * HEIGHT]) {}
//    void update() {
//
//    }
    void clear() {
        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                field[i * HEIGHT + j] = false;
    }
    void set(int[] x) {
        for (auto k: x)
            for (int i = 0; i < HEIGHT; i++)
                for (int j = 0; j < WIDTH; j++)
                    if (x[k] == i * HEIGHT + j)
                        field[i * HEIGHT + j] = true;
    }
    void show() {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++)
                std::cout << field[i * HEIGHT + j] << ' ';
            std::cout << std::endl;
        }
    }

private:
    bool* field;
};


int main() {
    Field field;
    field.clear();
    field.set(set_0);
    field.show();
    return 0;
}


