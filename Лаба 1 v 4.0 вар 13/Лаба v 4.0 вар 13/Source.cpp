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
			    cout << endl << " ������� �������� � -" << endl;
			    cin >> x;
			    if (std::cin.fail())
			    {
				    cin.clear();
				    cin.ignore(32767, '\n');
				    cout << " �� ����� ������������ �����, ���������� ��� ���.";
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
				cout << endl << " ������� �������� y -" << endl;
				cin >> y;
				if (std::cin.fail())
				{
					cin.clear();
					cin.ignore(32767, '\n');
					cout << " �� ����� ������������ �����, ���������� ��� ���.";
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
			cout << endl << " ������� �������� z -" << endl;
			cin >> z;
			if (std::cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << " �� ����� ������������ �����, ���������� ��� ���.";
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
		if (y + cbrt(x - 1.) < 0 || fabs(x - y) == 0 )    // �������� �� ���������� �� �������������� � �� ����
		{
			cout << " ����, ������, ���-�� ����� �� ���, ��������� ����, ����������" << endl;
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
		if (z == 0) // �������� �� ������� �� ����
		{
			cout << " ��, ��� ����� �� ��������, ���������� ������";
			z = checking(trigger_y, trigger_z);
			continue;
		}
		break;
	}
	double f;
	f = pow ( ( y + cbrt (x - 1. ) ), 1. / 4 ) / ( fabs ( x - y ) * ( pow ( sin ( z ) , 2. ) + tan ( z )  ) );
	cout << endl << " ������� f = " << f << endl;
	system("pause");
 }