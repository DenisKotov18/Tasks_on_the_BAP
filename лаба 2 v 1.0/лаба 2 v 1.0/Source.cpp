#include <math.h>
#include <iostream>
#include <clocale>
#include <conio.h>
using namespace std;
double check()
{
	while (true)
	{
		double z;
		cin >> z;
		if (std::cin.fail() == 1)
		{
			cin.clear();
			cin.ignore(32767, '\n');
			std::cout << " Вы ввели некорректное число, попробуйте ещё раз."<< endl;
		}
		else
		{
			cin.ignore(32767, '\n');
			return z;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		std::cout << " Выберите используемую функцию" << std::endl << " 1) 2x" << std::endl << " 2) x^2" << std::endl << " 3) x/3" << std::endl;
		double unkn;
		unkn = 0;
		double x;
		x = 0;
		while (true)
		{
			bool retry;
			retry = false;
			int choice;
			choice = check ();
			switch (choice)
			{
			case 1:
			{
				std::cout << " Внимание! В зависимости от значения z формула нахождения переменной х будет меняться" << std::endl;
				system("pause");
				std::cout << " При z > 0, x = z^(1/2)" << std::endl << " При значениях z = 0 или z < 0, x = z^2" << std::endl << " Введите z - " << endl;
				double z;
				z = check();
				if (z > 0) x = pow(z, 1. / 2.);
				else x = pow(z, 2);
				unkn = (2 * x);
				break;
			}
			case 2:
			{
				std::cout << " Внимание! В зависимости от значения z формула нахождения переменной х будет меняться" << std::endl;
				system("pause");
				std::cout << " При z > 0, x = z^(1/2)" << std::endl << " При значениях z = 0 или z < 0, x = z^2" << std::endl << " Введите z - " << endl;
				double z;
				z = check();
				if (z > 0) x = pow(z, 1. / 2.);
				else x = pow(z, 2);
				unkn = pow(x, 2);
				break;
			}
			case 3:
			{
				std::cout << " Внимание! В зависимости от значения z формула нахождения переменной х будет меняться" << std::endl;
				system("pause");
				std::cout << " При z > 0, x = z^(1/2)" << std::endl << " При значениях z = 0 или z < 0, x = z^2" << std::endl << " Введите z - " << endl;
				double z;
				z = check();
				if (z > 0) x = pow(z, 1. / 2.);
				else x = pow(z, 2);
				unkn = (x / 3.);
				break;
			}
			default:
			{
				std::cout << " Пожалуйста, введите значение от 1 до 3 " << std::endl;
				retry = true;
				break;
			}
			}
			if (retry == true) continue;
			break;
		}
		std::cout << " Пожалуйста, введите значение a " << std::endl;
		double a;
		a = check();
		std::cout << " Пожалуйста, введите значение d " << std::endl;
		double d;
		d = check();
		double y;
		y = 2 * unkn * (a * sin(x) + d * exp(-(x+3)));
		if ( isfinite (y) == 0)
		{
			cout << " Значение не может быть вычислено. Проверьте правильность ввода и повторите попытку..." << endl;
			system("pause");
			continue;
		}
		std::cout << " Ответ = " << y << endl;
		break;
	}
	system("pause");
}