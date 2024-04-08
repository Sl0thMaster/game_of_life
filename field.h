#include <iostream>
#include <fstream>

/**
 * \brief Класс, реализующий функционал поля для игры Жизнь.
 */
class Field {
public:
    Field(int field_width, int field_height);

    Field(const Field& other);

    Field(Field&& other) noexcept;

    Field& operator=(Field copy);

    ~Field();

    //! Доступ к элементу поля по индексу.
    bool& operator[](int index);

    //! Переход поля к следующему поколению.
    void advance();

    //! Переключение состояния клетки.
    void toggle(int x, int y);

    //! Получение значения клетки по её координатам.
    bool get(int x, int y);

    //! Массив живых клеток.
    int* living_cells();

    //! Загрузка состояния поля из файла.
    void load(const std::string& file_path);

    //! Сохранение состояния поля в файл.
    void save(const std::string& file_path);

private:
    //! Поле игры.
    bool* field;

    //! Ширина поля.
    int width;

    //! Высота поля.
    int height;

    //! Обмен полями.
    void swap(Field& other);

    //! Очистка поля.
    void clear();
};
