#include <cmath>
#include <iostream>
#include <clocale>
#include <conio.h> 
using namespace std;
double checking(bool trigger_y, bool trigger_z)
{
	while (true)
	{
		
		while (true)
		{
			if (trigger_y == true)
			{
				break;
			}
			else
			{
			    double x;
			    cout << endl << " Введите значение х -" << endl;
			    cin >> x;
			    if (std::cin.fail())
			    {
				    cin.clear();
				    cin.ignore(32767, '\n');
				    cout << " Вы ввели некорректное число, попробуйте ещё раз.";
			    }
			    else
			    {
				    cin.ignore(32767, '\n');
				    return x;
			    }
			}
		}    
		
		while (true)
		{
			if (trigger_z == true)
			{
				break;
			}
			else
			{
				double y;
				cout << endl << " Введите значение y -" << endl;
				cin >> y;
				if (std::cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
					cout << " Вы ввели некорректное число, попробуйте ещё раз.";
				}
				else
				{
					cin.ignore(32767, '\n');
					return y;
				}
			}
		}
		while (true)
		{
			double z;
			cout << endl << " Введите значение z -" << endl;
			cin >> z;
			if (std::cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << " Вы ввели некорректное число, попробуйте ещё раз.";
			}
			else
			{
				cin.ignore(32767, '\n');
				return z;
			}
		}
		break;
	}
}
int main()
{
	setlocale(LC_ALL, "Russian"); 
	bool t;
	t = false;
	bool trigger_y = 0;
	bool trigger_z = 0;
	double x = checking (trigger_y, trigger_z);
	trigger_y = true;
	double y = checking(trigger_y, trigger_z);
	while (true)
	{
		if (y + cbrt(x - 1.) < 0 || fabs(x - y) == 0 )    // Проверка на извлечение из отрицательного и на ноль
		{
			cout << " Уупс, похоже, что-то пошло не так, повторите ввод, пожалуйста" << endl;
			trigger_y = false;
			x = checking(trigger_y, trigger_z);
			trigger_y = true;
			y = checking(trigger_y, trigger_z);
			continue;
		}
			break;
	}
	trigger_z = true;
	double z = checking(trigger_y, trigger_z);
	while (true)
	{
		if (z == 0) // проверка на деление на ноль
		{
			cout << " Ой, эта цифра не подходит, попробуйте другую";
			z = checking(trigger_y, trigger_z);
			continue;
		}
		break;
	}
	double f;
	f = pow ( ( y + cbrt (x - 1. ) ), 1. / 4 ) / ( fabs ( x - y ) * ( pow ( sin ( z ) , 2. ) + tan ( z )  ) );
	cout << endl << " Значени f = " << f << endl;
	system("pause");
 }