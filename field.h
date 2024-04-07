#include <iostream>

class Field {
public:
    Field(int field_width, int field_height);;

    Field(const Field& other);;

    Field(Field&& other);;

    Field& operator=(Field copy);;

    ~Field();

    bool& operator[](int index);

    void advance();

    void toggle(int x, int y);

    void clear();

    int* living_cells();

    void set(int* x, int size);

private:
    bool* field;
    int width;
    int height;

    void swap(Field& other);
};
