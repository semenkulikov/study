#include <stdio.h>
#include "bitset.h"
#include "output.h"

int main(void) {
    // Создаем множество с емкостью 520 элементов
    BitSet work_set = bitset_create(520);

    // Добавляем несколько элементов в множество
    bitset_add(&work_set, 10);
    bitset_add(&work_set, 50);
    bitset_add(&work_set, 100);

    // Выводим множество на стандартный поток вывода
    output_to_stdout("Вывод множества:");
    bitset_print(&work_set, output_to_stdout);

    // Освобождаем память, выделенную для множества
    bitset_destroy(&work_set);

    return 0;
}
