#include <iostream>
#include <cmath>
#include <clocale>
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
			std::cout << " Вы ввели некорректное число, попробуйте ещё раз." << endl;
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
	double k = 0;
	 long double Yx = 0;
	 long double Sx = 0;
	while (true) //
	{
		cout << "Введите значение a = " << endl;
		const double a = check();
		cout << "Введите значение b = " << endl;
		const double b = check();
		if (a >= b)
		{
			cout << " Значение а дожно быть меньше значения b. Повторите попытку." << endl;
			continue;
		}
		while (true) //
		{
			cout << "Введите значение h = " << endl;
			const double h = check();
			if (fabs(b - a) / h > 1000)
			{
				cout << " Вы уверены что нигде не ошиблись?" << endl << "1) Да" << endl << "2) Нет" << endl;
				const int yesnt = check();
				switch (yesnt)
				{
				case 1: break;
				case 2: continue;
				default: continue;
					break;
				}
			}
				if (h <=0)
				{
					cout << " Ваше число не подходит к системе, попробуйте снова." << endl;
					continue;
				}
				int n = 0;
				while (true)
				{
					cout << " Введите n = " << endl;
				    n = check();
					if (n < 1)
					{
						cout << "" << endl; 
						continue;
					}
					break;
				}
				double x;
				for (x = a; x <= b; x += h)
				{
					Yx = 0;
					Sx = 0;
					int sign;
					sign = -1;
					long double reccurent;
					reccurent = x*x;
					long double reccurent_s;
					reccurent_s = 0;
					for (k = 1; k <= n;)
					{
						reccurent_s += (2 * k * (2 * k - 1));
						reccurent_s -= (2 * (k - 1) * (2 * (k - 1) - 1));
						sign *= -1;
						Sx +=sign * reccurent / reccurent_s;
						reccurent *= x * x;
						k++;
					}
					Yx = -(log(sqrt(1 + pow(x, 2)))) + x * atan(x);
					if ((isfinite(Yx) == 0) || (isfinite(Sx) == 0))
					{
						cout << " Значение не может быть вычислено." << endl;
						continue;
					}
					cout << " Y(x) = " << Yx << "  S(x) = " << Sx << "  |Y(x) - S(x)| = " << fabs(Yx - Sx) << endl;
				}	
			break;
		}
		break;
	}
	system("pause");
}