#pragma once

using namespace std;

const char* const MAIN_POINTS[] = { "Начать работу", "Завершить программу", NULL };

const char ENTERING_RPN[] = "Введите выражение";

const char ENTERING_NUM[] = "Введите число ";

const char ERROR_NULL[] = "\033[31mОшибка!\033[0m Деление на 0";

const char ERROR_INF[] = "\033[31mОшибка!\033[0m Результат выходит за диапазон допустимых значений! Попробуйте снова";

const char RESULT[] = "Результат вычислений = ";

const char MAIN_MENU_HEAD_1[] = "Текущее выражение: ";

const char MAIN_MENU_HEAD_2[] = "\nОбратная польская запись данного выражения: ";

const char* const MAIN_MENU_POINTS[] = { "Произвести расчёты по формуле", "Выход", NULL };