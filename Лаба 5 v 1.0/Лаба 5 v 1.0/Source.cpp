#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
int check()
{
	while (true)
	{
		int z;
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
	setlocale(LC_ALL, "RUSSIAN");
	srand(time(NULL));
	cout << " Введите размер массива." << endl;
	int n = check();
	while (n < 1)
	{
		cout << " Размер массива должен быть больше 0." << endl;
		n = check();
	}
	int* arr = new int[n];
	cout << " Хотите заполнить массив случайными числами?" << endl;
	while (true)
	{
		cout << "1)ДА " << " 2)НЕТ" << endl;
		bool trigger = false;
		int yesnt = check();
		switch (yesnt)
		{
		case 1:
		{
			cout << "Введите минимальное число" << endl;
			int a = check();
			cout << "Введите максимальное число" << endl;
			int b = check();
			
			for (int i = 0; i <= (n - 1); i++)	arr[i] = rand() % (b - a + 1) + a;
			break;
		}
		case 2:
		{
			for (int i = 0; i <= (n - 1); i++)
			{
				cout << " Введите " << (i + 1) << "-й член массива";
				arr[i] = check();
			}
			break;
		}
		default:
		{
			cout << "Капкан на дурака сработал, ладно..." << endl;
			trigger = true;
			break;
		}
		}
		if (trigger == false) break;
	}
	int max = arr[0];
	int max_num = 0;
	for (int i = 1; i <= (n - 1); i++)
	{
		cout << arr[i]<<endl;
		if (arr[i] > max)
		{
			max = arr[i];
			max_num = i;
		}
	}
	int sum = 0;
	for (int i = 0; i < max_num; i++)
	{
		if (arr[i]>0) sum += arr[i];
	}
	delete[]arr;
	cout << endl <<" Сумма положительных элементов массива до наибольшего равно -"<< sum;
	return 0;
}
