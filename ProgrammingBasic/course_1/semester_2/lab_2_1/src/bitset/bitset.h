#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "output.h"

/**
 * @brief Структура для представления битового множества.
 */
typedef struct {
    uint64_t *bits;    // Динамический массив битов
    size_t size;       // Количество 64-битных блоков
    size_t capacity;   // Общее число элементов (размер универсального множества)
} BitSet;

/**
 * @brief Создает битовое множество заданной емкости.
 * @param capacity Максимальное число элементов в множестве.
 * @return Инициализированное множество.
 */
BitSet bitset_create(size_t capacity);

/**
 * @brief Освобождает память, выделенную для множества.
 * @param set Указатель на множество.
 */
void bitset_destroy(BitSet *set);

/**
 * @brief Добавляет элемент в множество.
 * @param set Указатель на множество.
 * @param element Элемент для добавления.
 */
void bitset_add(BitSet *set, int element);

/**
 * @brief Проверяет, содержится ли элемент в множестве.
 * @param set Константный указатель на множество.
 * @param element Элемент для проверки.
 * @return true, если элемент присутствует, иначе false.
 */
bool bitset_contains(const BitSet *set, int element);

/**
 * @brief Выводит множество, используя заданную функцию вывода.
 * @param set Константный указатель на множество.
 * @param func_output Указатель на функцию вывода.
 */
void bitset_print(const BitSet *set, OutputFunc func_output);

/**
 * @brief Функция объединения: result = A ∪ B.
 */
BitSet bitset_union(const BitSet *A, const BitSet *B);

/**
 * @brief Функция пересечения: result = A ∩ B.
 */
BitSet bitset_intersection(const BitSet *A, const BitSet *B);

/**
 * @brief Функция разности: result = A - B.
 */
BitSet bitset_difference(const BitSet *A, const BitSet *B);

/**
 * @brief Функция симметрической разности: result = A △ B.
 */
BitSet bitset_sym_diff(const BitSet *A, const BitSet *B);

/**
 * @brief Функция дополнения множества с учетом его размера.
 */
BitSet bitset_complement(const BitSet *A);

/**
 * @brief Проверка включения A ⊆ B.
 */
bool bitset_is_subset(const BitSet *A, const BitSet *B);

/**
 * @brief Проверка строгого включения A ⊂ B.
 */
bool bitset_is_strict_subset(const BitSet *A, const BitSet *B);

#endif // BITSET_H
