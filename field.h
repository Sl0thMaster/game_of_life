const int WIDTH = 26;
const int HEIGHT = 18;

class Field {
public:
    Field();

    bool& operator[](int index);

    void update();

    void toggle(int x, int y);

    void clear();

    void set(int* x, int size);

private:
    bool* field;
};
