#include <iostream>
#include <fstream>

class Field {
public:
    Field(int field_width, int field_height);

    Field(const Field& other);

    Field(Field&& other) noexcept ;

    Field& operator=(Field copy);

    ~Field();

    bool& operator[](int index);

    void advance();

    void toggle(int x, int y);

    int* living_cells();

    void set(const int* x, int size);

    void load(const std::string& file_path);

    void save(const std::string& file_path);

private:
    bool* field;
    int width;
    int height;

    void swap(Field& other);

    void clear();
};
