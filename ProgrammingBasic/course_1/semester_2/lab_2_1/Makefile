# Компилятор
CC = gcc

# Флаги компиляции: предупреждения, отладочная информация, стандарт C11 и режим DEBUG
CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

# Каталоги с заголовочными файлами
INCLUDES = -I src/bitset -I src/output

# Исходные файлы для основной программы
MAIN_SRC = src/main.c src/bitset/bitset.c src/output/output.c

# Исходные файлы для тестов
TEST_SRC = tests/tests.c src/bitset/bitset.c src/output/output.c

# Целевые файлы
MAIN_TARGET = bitset_main.o
TEST_TARGET = run_tests

# Правила сборки
.PHONY: all test clean rebuild

# Сборка основной программы
all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN_SRC) -o $(MAIN_TARGET)

# Сборка и запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) -o $(TEST_TARGET)

# Очистка скомпилированных файлов
clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) *.o src/bitset/*.o src/output/*.o tests/*.o

# Полная пересборка: очистка, сборка основной программы и тестов, запуск тестов
rebuild: clean all test
