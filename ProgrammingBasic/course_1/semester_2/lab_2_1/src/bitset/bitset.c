#include "bitset.h"
#include <string.h>
#include <assert.h>

BitSet bitset_create(size_t capacity) {
    BitSet set;
    // Определяем количество блоков по 64 бита
    set.size = (capacity + 63) / 64;
    set.capacity = capacity;
    set.bits = (uint64_t*)calloc(set.size, sizeof(uint64_t));
    if (set.bits == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для битового множества\n");
        exit(EXIT_FAILURE);
    }
    return set;
}

void bitset_destroy(BitSet *set) {
    if (set && set->bits) {
        free(set->bits);
        set->bits = NULL;
        set->size = 0;
        set->capacity = 0;
    }
}

void bitset_add(BitSet *set, int element) {
    assert(set != NULL);
    if (element < 0 || (size_t)element >= set->capacity) {
        fprintf(stderr, "Ошибка: элемент %d выходит за пределы множества\n", element);
        return;
    }
    size_t index = element / 64;
    size_t bit = element % 64;
    set->bits[index] |= (1ULL << bit);
}

bool bitset_contains(const BitSet *set, int element) {
    assert(set != NULL);
    if (element < 0 || (size_t)element >= set->capacity) {
        return false;
    }
    size_t index = element / 64;
    size_t bit = element % 64;
    return (set->bits[index] & (1ULL << bit)) != 0;
}

void bitset_print(const BitSet *set, OutputFunc func_output) {
    assert(set != NULL);
    if (func_output == NULL) {
        return;
    }
    char buffer[1024] = {0};
    size_t pos = 0;
    pos += snprintf(buffer + pos, sizeof(buffer) - pos, "{ ");
    for (size_t i = 0; i < set->capacity; i++) {
        if (bitset_contains(set, i)) {
            pos += snprintf(buffer + pos, sizeof(buffer) - pos, "%zu ", i);
        }
    }
    snprintf(buffer + pos, sizeof(buffer) - pos, "}");
    func_output(buffer);
}

BitSet bitset_union(const BitSet *A, const BitSet *B) {
    assert(A != NULL && B != NULL);
    assert(A->capacity == B->capacity);
    BitSet result = bitset_create(A->capacity);
    for (size_t i = 0; i < A->size; i++) {
        result.bits[i] = A->bits[i] | B->bits[i];
    }
    return result;
}

BitSet bitset_intersection(const BitSet *A, const BitSet *B) {
    assert(A != NULL && B != NULL);
    assert(A->capacity == B->capacity);
    BitSet result = bitset_create(A->capacity);
    for (size_t i = 0; i < A->size; i++) {
        result.bits[i] = A->bits[i] & B->bits[i];
    }
    return result;
}

BitSet bitset_difference(const BitSet *A, const BitSet *B) {
    assert(A != NULL && B != NULL);
    assert(A->capacity == B->capacity);
    BitSet result = bitset_create(A->capacity);
    for (size_t i = 0; i < A->size; i++) {
        result.bits[i] = A->bits[i] & ~(B->bits[i]);
    }
    return result;
}

BitSet bitset_sym_diff(const BitSet *A, const BitSet *B) {
    assert(A != NULL && B != NULL);
    assert(A->capacity == B->capacity);
    BitSet result = bitset_create(A->capacity);
    for (size_t i = 0; i < A->size; i++) {
        result.bits[i] = A->bits[i] ^ B->bits[i];
    }
    return result;
}

BitSet bitset_complement(const BitSet *A) {
    assert(A != NULL);
    BitSet result = bitset_create(A->capacity);
    for (size_t i = 0; i < A->size; i++) {
        result.bits[i] = ~(A->bits[i]);
        // Маскируем лишние биты в последнем блоке, если емкость не кратна 64
        if (i == A->size - 1) {
            int extra = A->size * 64 - A->capacity;
            if (extra > 0) {
                uint64_t mask = ~0ULL >> extra;
                result.bits[i] &= mask;
            }
        }
    }
    return result;
}

bool bitset_is_subset(const BitSet *A, const BitSet *B) {
    assert(A != NULL && B != NULL);
    assert(A->capacity == B->capacity);
    for (size_t i = 0; i < A->size; i++) {
        if ((A->bits[i] & B->bits[i]) != A->bits[i]) {
            return false;
        }
    }
    return true;
}

bool bitset_is_strict_subset(const BitSet *A, const BitSet *B) {
    if (!bitset_is_subset(A, B)) {
        return false;
    }
    // Проверка, что множества не равны
    for (size_t i = 0; i < A->size; i++) {
        if (A->bits[i] != B->bits[i]) {
            return true;
        }
    }
    return false;
}
