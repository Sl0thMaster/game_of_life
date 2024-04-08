#include <cassert>

#include "field.h"

int main() {

//    Переключение клетки с мёртвой на живую
    Field field_0 = Field(3, 3);
    field_0.toggle(2, 0);
    assert(field_0.get(2, 0) == true);

//    Загрузка поля при помощи файла
    Field field_1 = Field(3, 3);
    field_1.load("tests/test_0.txt");
    assert(field_1.get(1, 2) == true);

//    Массив живых клеток
    Field field_3 = Field(3, 3);
    field_3.load("tests/test_0.txt");
    int expected_cells_0[6] = {1, 0, 1, 1, 1, 2};
    for (int i = 0; i < 6; i++) {
        std::cout << field_3.living_cells()[i];
        assert(field_3.living_cells()[i] == expected_cells_0[i]);
    }

//    Переход к следующим поколениям зацикленной структуры
    Field field_4 = Field(3, 3);
    field_4.load("tests/test_0.txt");
    field_4.advance();
    int expected_cells_1[6] = {0, 1, 1, 1, 2, 1};
    for (int i = 0; i < 6; i++) {
        std::cout << field_4.living_cells()[i];
        assert(field_4.living_cells()[i] == expected_cells_1[i]);
    }

//    Переход к следующим поколениям умирающей структуры
    Field field_5 = Field(3, 3);
    field_5.toggle(1, 1);
    field_5.advance();
    field_5.advance();
    assert(field_5.get(1, 1) == false);

//    Переход к следующим поколениям глайдера
    Field field_6 = Field(5, 5);
    field_6.load("tests/test_1.txt");
    for (int i = 0; i < 4; i++)
        field_6.advance();
    int expected_cells_2[10] = {2, 1, 3, 2, 1, 3, 2, 3, 3, 3};
    for (int i = 0; i < 10; i++) {
        std::cout << field_6.living_cells()[i];
        assert(field_6.living_cells()[i] == expected_cells_2[i]);
    }
}
