#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "../src/bitset/bitset.h"
#include "../src/output/output.h"

/**
 * @brief Тестирование базовых операций: создание, добавление и проверка
 * принадлежности.
 */
void test_basic_operations() {
  BitSet set = bitset_create(100);

  // Проверяем, что все элементы изначально отсутствуют
  for (int i = 0; i < 100; i++) {
    assert(!bitset_contains(&set, i));
  }

  // Добавляем несколько элементов
  bitset_add(&set, 0);
  bitset_add(&set, 50);
  bitset_add(&set, 99);

  // Проверяем наличие добавленных элементов
  assert(bitset_contains(&set, 0));
  assert(bitset_contains(&set, 50));
  assert(bitset_contains(&set, 99));
  assert(!bitset_contains(&set, 1));

  bitset_destroy(&set);
}

/**
 * @brief Тестирование граничных условий (элементы с индексами 0 и capacity-1).
 */
void test_boundary_conditions() {
  BitSet set = bitset_create(65);
  bitset_add(&set, 0);
  bitset_add(&set, 64);

  assert(bitset_contains(&set, 0));
  assert(bitset_contains(&set, 64));

  bitset_destroy(&set);
}

/**
 * @brief Тестирование операций объединения и пересечения.
 */
void test_union_intersection() {
  BitSet setA = bitset_create(100);
  BitSet setB = bitset_create(100);

  // setA = {10, 20, 30}
  bitset_add(&setA, 10);
  bitset_add(&setA, 20);
  bitset_add(&setA, 30);

  // setB = {20, 40, 50}
  bitset_add(&setB, 20);
  bitset_add(&setB, 40);
  bitset_add(&setB, 50);

  BitSet unionSet = bitset_union(&setA, &setB);
  assert(bitset_contains(&unionSet, 10));
  assert(bitset_contains(&unionSet, 20));
  assert(bitset_contains(&unionSet, 30));
  assert(bitset_contains(&unionSet, 40));
  assert(bitset_contains(&unionSet, 50));

  BitSet interSet = bitset_intersection(&setA, &setB);
  assert(!bitset_contains(&interSet, 10));
  assert(bitset_contains(&interSet, 20));
  assert(!bitset_contains(&interSet, 30));

  bitset_destroy(&setA);
  bitset_destroy(&setB);
  bitset_destroy(&unionSet);
  bitset_destroy(&interSet);
}

/**
 * @brief Тестирование операций разности и симметрической разности.
 */
void test_difference_sym_diff() {
  BitSet setA = bitset_create(100);
  BitSet setB = bitset_create(100);

  // setA = {1, 2, 3, 4, 5}
  // setB = {4, 5, 6, 7}
  for (int i = 1; i <= 5; i++) {
    bitset_add(&setA, i);
  }
  for (int i = 4; i <= 7; i++) {
    bitset_add(&setB, i);
  }

  BitSet diffSet = bitset_difference(&setA, &setB);
  // Ожидаем, что diffSet = {1, 2, 3}
  assert(bitset_contains(&diffSet, 1));
  assert(bitset_contains(&diffSet, 2));
  assert(bitset_contains(&diffSet, 3));
  assert(!bitset_contains(&diffSet, 4));

  BitSet symDiffSet = bitset_sym_diff(&setA, &setB);
  // Ожидаем, что symDiffSet = {1, 2, 3, 6, 7}
  assert(bitset_contains(&symDiffSet, 1));
  assert(bitset_contains(&symDiffSet, 2));
  assert(bitset_contains(&symDiffSet, 3));
  assert(bitset_contains(&symDiffSet, 6));
  assert(bitset_contains(&symDiffSet, 7));
  assert(!bitset_contains(&symDiffSet, 4));
  assert(!bitset_contains(&symDiffSet, 5));

  bitset_destroy(&setA);
  bitset_destroy(&setB);
  bitset_destroy(&diffSet);
  bitset_destroy(&symDiffSet);
}

/**
 * @brief Тестирование операции дополнения множества.
 */
void test_complement() {
  BitSet set = bitset_create(100);
  // Добавляем несколько элементов
  bitset_add(&set, 10);
  bitset_add(&set, 20);

  BitSet comp = bitset_complement(&set);
  // Дополнение: элементы 10 и 20 не должны присутствовать в дополнении
  assert(!bitset_contains(&comp, 10));
  assert(!bitset_contains(&comp, 20));
  // Если 0 не был добавлен в исходное множество, то он должен присутствовать в
  // дополнении
  if (!bitset_contains(&set, 0)) {
    assert(bitset_contains(&comp, 0));
  }

  bitset_destroy(&set);
  bitset_destroy(&comp);
}

/**
 * @brief Тестирование функций проверки включения.
 */
void test_subset_functions() {
  BitSet setA = bitset_create(100);
  BitSet setB = bitset_create(100);

  // setA = {10, 20}; setB = {10, 20, 30}
  bitset_add(&setA, 10);
  bitset_add(&setA, 20);

  bitset_add(&setB, 10);
  bitset_add(&setB, 20);
  bitset_add(&setB, 30);

  assert(bitset_is_subset(&setA, &setB));
  assert(bitset_is_strict_subset(&setA, &setB));

  // Проверяем случай равенства
  BitSet setC = bitset_union(&setA, &setB);
  assert(bitset_is_subset(&setC, &setB));
  assert(!bitset_is_strict_subset(&setC, &setB));

  bitset_destroy(&setA);
  bitset_destroy(&setB);
  bitset_destroy(&setC);
}

/**
 * @brief Тестирование производительности добавления элементов.
 */
void test_performance() {
  const size_t N = 1000000;
  BitSet set = bitset_create(N);

  clock_t start = clock();
  for (size_t i = 0; i < N; i++) {
    bitset_add(&set, i);
  }
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Добавление %zu элементов заняло %.3f секунд.\n", N, seconds);

  bitset_destroy(&set);
}

int main(void) {
  printf("Запуск тестов...\n");
  test_basic_operations();
  test_boundary_conditions();
  test_union_intersection();
  test_difference_sym_diff();
  test_complement();
  test_subset_functions();
  test_performance();
  printf("Все тесты успешно пройдены.\n");
  return 0;
}
