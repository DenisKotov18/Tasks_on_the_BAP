#include<iostream>
#include<conio.h>

using namespace std;

void menu();
double getDouble(int);
struct Queue* order(Queue*&, Queue*&);
void createNew(Queue*&, Queue*&, int);
void showStack(Queue*);
void garbageCollector(Queue*);


const char CONF_EXIT[] = " �� �������, ��� ������ �����?";
const char MENU_INFO[] = "	 ����� ����������!\n	��� �� ������ �������?\n 1) ������� ������ \n 2) �������� ����� ��������\n 3) ������� ������ 2 �������\n ESC-�����";
const char EMPTY[] = " ������ ����.";
const char INPUT_AMT[] = " ������� ��������� ����� ���������?";
const char INPUT_INFO[] = " ������� �������� �������� - ";
const char CONFIRM[] = " �� �������, ��� ������ ��������� ��� ����������� ��������? \n 1) ��. \n 2) ���.";
const char DONE[] = " ������!";
const char ERR_DEL[] = " ������ �������!";

struct Queue
{
	int info;
	Queue* next,* prev;
};


void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	menu();
	system("pause");
}

void menu()
{
	Queue* begin = NULL, *end = NULL;
	bool exit_flag = false;
	char switcher = NULL;
	while (exit_flag == false)
	{
		system("cls");
		cout << MENU_INFO << endl;
		switcher = _getch();
		switch (switcher)
		{
		case '1':
		{
			system("cls");
			if (begin) showStack(begin);
			else cout << EMPTY << endl;
			system("pause");
			system("cls");
			break;
		}
		case '2':
		{
			system("cls");
			cout << INPUT_AMT << endl;
			int num = getDouble(1);
			begin = createNew(begin, num);
			break;
		}
		case '3':
		{
			cout << CONFIRM << endl;
			char choise = _getch();
			while ((choise < '1') || (choise > '2')) choise = _getch();
			if (choise == '1')
			{
				if ((begin) && (begin->next))
				{
					delEvery2(begin);
					cout << DONE << endl;
				}
				else cout << ERR_DEL << endl;
				system("pause");
			}
			break;
		}
		case 27:
		{
			exit_flag = true;
			break;
		}
		}
	}
	garbageCollector(begin);
}

Queue* order(Queue*& begin, Queue*& end)
{
	char choise = _getch();
	while (choise <'1' || choise > '2') choise = _getch();
	return (choise == '1') ? begin : end;
}

void createNew(Queue*& begin, Queue*& end, int num)
{
	Queue* n_elem = NULL;
	for (int i = 0; i < num; i++)
	{
		n_elem = new Queue;
		n_elem->info = getDouble(1);

		n_elem->next = NULL;
		if (!begin) begin = end = n_elem;
		else end->next = n_elem;
		end = n_elem;
	}
}

double getDouble(int mode) //1-int, 2-double
{
	while (true)
	{
		int counter = 0, point_pos = 0, sign = 1;
		char num[100] = { '\0' };
		double fin_num = 0;
		int l_num = 0;
		bool break_flag = false, point_flag = false, first_0 = false, sign_flag = false;
		while (break_flag == false)
		{
			char symbol = _getch();
			if ((counter == 99) && (symbol != '\b') && (symbol != '\r')) continue;
			if ((first_0 == true) && (symbol != '.') && (symbol != ',') && (symbol != '\r') && (symbol != '\b')) continue;
			switch (symbol)
			{
			case '-':
			{
				if ((sign_flag == false) && (counter == 0))
				{
					sign_flag = true;
					sign = -1;
					cout << '-';
				}
				break;
			}
			case '0':
			{
				num[counter] = symbol;
				counter++;
				cout << symbol;
				if (counter == 1) first_0 = true;
				break;
			}
			case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			{
				num[counter] = symbol;
				counter++;
				cout << symbol;
				break;
			}
			case '.':case',':
			{
				if ((point_flag == false) && (counter > 0) && (mode == 2))
				{
					point_flag = true;
					first_0 = false;
					point_pos = counter;
					num[counter] = '.';
					cout << '.';
					counter++;
				}
				break;
			}
			case '\b':
			{
				if ((point_flag == true) && (counter == (point_pos + 1)))
				{
					num[point_pos] = '\0';
					point_flag = false;
					counter--;
					cout << '\b' << " " << '\b';
					break;
				}
				if (counter > 0)
				{
					if (counter == 1) first_0 = false;
					counter--;
					num[counter] = '\0';
					cout << '\b' << " " << '\b';
				}
				else
				{
					sign_flag = false;
					sign = 1;
					cout << '\b' << " " << '\b';
				}
				break;
			}
			case'\r': break_flag = true;
			default:
				break;
			}

		}
		if (point_flag == true)
		{
			for (int i = 0; i < point_pos; i++) l_num = l_num * 10 + ((int)num[i] - (int)'0');
			for (int i = (point_pos + 1); i < counter; i++) l_num = (l_num * 10 + ((int)num[i] - (int)'0'));
			fin_num = l_num;
			for (int i = (counter - 1); i > point_pos; i--) fin_num *= 0.1;
		}
		else
		{
			for (int i = 0; i < counter; i++) fin_num = fin_num * 10 + ((int)num[i] - (int)'0');
			fin_num = (int)fin_num;
		}
		if (isfinite(fin_num) != 0)
		{
			cout << endl;
			return fin_num * sign;
		}
		cout << endl << " ����� ������� �� ������� �������������, please try again." << endl;
	}
}
