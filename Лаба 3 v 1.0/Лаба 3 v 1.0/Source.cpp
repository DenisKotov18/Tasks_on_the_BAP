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
			std::cout << " �� ����� ������������ �����, ���������� ��� ���." << endl;
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
		cout << "������� �������� a = " << endl;
		const double a = check();
		cout << "������� �������� b = " << endl;
		const double b = check();
		if (a >= b)
		{
			cout << " �������� � ����� ���� ������ �������� b. ��������� �������." << endl;
			continue;
		}
		while (true) //
		{
			cout << "������� �������� h = " << endl;
			const double h = check();
			if (fabs(b - a) / h > 1000)
			{
				cout << " �� ������� ��� ����� �� ��������?" << endl << "1) ��" << endl << "2) ���" << endl;
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
					cout << " ���� ����� �� �������� � �������, ���������� �����." << endl;
					continue;
				}
				int n = 0;
				while (true)
				{
					cout << " ������� n = " << endl;
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
						cout << " �������� �� ����� ���� ���������." << endl;
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