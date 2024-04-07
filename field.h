class Field {
public:
    Field(int field_width, int field_height);

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
};
