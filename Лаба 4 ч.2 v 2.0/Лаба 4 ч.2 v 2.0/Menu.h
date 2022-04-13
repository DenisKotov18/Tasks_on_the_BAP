#pragma once

#include<iostream>
#include<conio.h>
#include"MyString.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

int menu(const char[], const char* const []); // универсальная функция вывода меню
int pointerCatcher(int&, const int&, const int&, int, const int&); // функция считывания нажатия стрелочек
