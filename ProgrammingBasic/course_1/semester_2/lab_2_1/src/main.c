#include <stdio.h>
#include "bitset.h"
#include "output.h"

/**
 * @brief Индивидуальное задание для варианта 23:
 * Вычисление выражения:
 *   ((A ∪ B) - (C ∩ D)) Δ ((C - B) ∪ (A ∩ D))
 *
 * Для демонстрации множества A, B, C, D заполняются тестовыми значениями.
 */
int main(void) {
    // Задаём универсальную мощность множеств (например, 100 элементов)
    size_t capacity = 100;

    // Создаем множества A, B, C, D
    BitSet A = bitset_create(capacity);
    BitSet B = bitset_create(capacity);
    BitSet C = bitset_create(capacity);
    BitSet D = bitset_create(capacity);

    // Инициализация множеств тестовыми значениями
    // Пример: A = {1, 2, 3, 10}, B = {2, 3, 4, 10}, C = {3, 4, 5, 20}, D = {4, 5, 6, 20}
    bitset_add(&A, 1);
    bitset_add(&A, 2);
    bitset_add(&A, 3);
    bitset_add(&A, 10);

    bitset_add(&B, 2);
    bitset_add(&B, 3);
    bitset_add(&B, 4);
    bitset_add(&B, 10);

    bitset_add(&C, 3);
    bitset_add(&C, 4);
    bitset_add(&C, 5);
    bitset_add(&C, 20);

    bitset_add(&D, 4);
    bitset_add(&D, 5);
    bitset_add(&D, 6);
    bitset_add(&D, 20);

    // Вычисляем (A ∪ B)
    BitSet unionAB = bitset_union(&A, &B);
    // Вычисляем (C ∩ D)
    BitSet interCD = bitset_intersection(&C, &D);
    // Вычисляем разность: ((A ∪ B) - (C ∩ D))
    BitSet diff1 = bitset_difference(&unionAB, &interCD);

    // Вычисляем (C - B)
    BitSet diff2 = bitset_difference(&C, &B);
    // Вычисляем (A ∩ D)
    BitSet interAD = bitset_intersection(&A, &D);
    // Вычисляем объединение: ((C - B) ∪ (A ∩ D))
    BitSet union2 = bitset_union(&diff2, &interAD);

    // Вычисляем симметрическую разность между полученными частями
    BitSet result = bitset_sym_diff(&diff1, &union2);

    // Вывод исходных множеств
    output_to_stdout("Множество A:");
    bitset_print(&A, output_to_stdout);
    output_to_stdout("Множество B:");
    bitset_print(&B, output_to_stdout);
    output_to_stdout("Множество C:");
    bitset_print(&C, output_to_stdout);
    output_to_stdout("Множество D:");
    bitset_print(&D, output_to_stdout);

    // Вывод результата вычисления выражения
    output_to_stdout("Результат выражения ((A ∪ B) - (C ∩ D)) Δ ((C - B) ∪ (A ∩ D)):");
    bitset_print(&result, output_to_stdout);

    // Освобождаем память для всех множеств
    bitset_destroy(&A);
    bitset_destroy(&B);
    bitset_destroy(&C);
    bitset_destroy(&D);
    bitset_destroy(&unionAB);
    bitset_destroy(&interCD);
    bitset_destroy(&diff1);
    bitset_destroy(&diff2);
    bitset_destroy(&interAD);
    bitset_destroy(&union2);
    bitset_destroy(&result);

    return 0;
}
