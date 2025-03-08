#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * @brief Определение типа функции вывода.
 * Функция принимает строку и выводит её в нужное место (консоль, файл и т.д.).
 */
typedef void (*OutputFunc)(const char *);

/**
 * @brief Вывод строки в стандартный поток вывода.
 * @param message Строка для вывода.
 */
void output_to_stdout(const char *message);

/**
 * @brief Вывод строки в стандартный поток ошибок.
 * @param message Строка для вывода.
 */
void output_to_stderr(const char *message);

#endif // OUTPUT_H
