#include<iostream>
#include<conio.h>

using namespace std;

void menu();
double getDouble(int);
struct Queue* &order(Queue*&, Queue*&);
Queue*& linkUpdate(Queue*&, Queue*&);
Queue*& reverseLinkUpdate(Queue*&, Queue*&);
void linkPart(Queue* const &, Queue*&, Queue*&, Queue*&);
void createNew( Queue*&, Queue*&, int);
void showStack(Queue*);
void displayOrder(Queue*&, Queue*&);
void delEvery2(Queue*, Queue*&, Queue*&);
void garbageCollector(Queue*&);
//void test(int*&);

const char CONF_EXIT[] = " Вы уверены, что хотите выйти?";
const char MENU_INFO[] = "	 Добро пожаловать!\n	Что вы хотите сделать?\n 1) Вывести список \n 2) Добавить новые элементы\n 3) Удалить каждый 2 элемент\n ESC-назад";
const char EMPTY[] = " Список пуст.";
const char SHOW_TO[] = "С какого элемента показать список?\n 1) С первого\n 2) С последнего";
const char INPUT_AMT[] = " Сколько элементов будем добавлять?";
const char INPUT_INFO[] = " Введите значение элемента - ";
const char INPUT_TO[] = "  В какую часть списка добавить?\n 1) В начало\n 2) В конец";
const char DEL_TO[] = "  Откуда начинать удаление?\n 1) С начала списка\n 2) С конца списка";
const char CONFIRM[] = " Вы уверены, что хотите совершить это необратимое действие? \n 1) Да. \n 2) НЕТ.";
const char DONE[] = " Готово!";
const char ERR_DEL[] = " Нечего удалять!";

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

//void test(int *&link)
//{
//	int a = 9;
//	link = &a;
//}

void menu()
{
	Queue* begin = NULL, *end = NULL;
	bool exit_flag = false;
	char switcher = NULL;
	//test(order(begin, end));
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
			if (begin)
			{
				cout << SHOW_TO << endl;
				showStack(order(begin, end));
			}
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
			createNew(begin, end, num);
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
					cout << DEL_TO << endl;
					delEvery2(order(begin, end), begin, end);
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

Queue*& order(Queue*& begin, Queue*& end)
{
	char choise = _getch();
	while (choise <'1' || choise > '2') choise = _getch();
	return (choise == '1') ? begin: end;
}

void linkPart(Queue* const & elem, Queue*& use_elem, Queue*& choise, Queue*& choise_link)
{
	use_elem = choise;
	choise_link = elem;
	choise = elem;
}

void showStack(Queue* begin)
{
	system("cls");
	Queue* elem = begin; 
	int i = 1;
	while (elem)
	{
		cout << ' ' << i << ") " << elem->info << endl;
		elem = linkUpdate(begin, elem);
		i++;
	}
}

void createNew(Queue*& begin, Queue*& end, int num)
{
	Queue* n_elem = NULL, * choise = NULL;
	for (int i = 0; i < num; i++)
	{
		n_elem = new Queue;
		cout << endl << INPUT_INFO;
		n_elem->info = getDouble(1);
		n_elem->prev = n_elem->next = NULL;
		if (!begin) begin = end = n_elem;
		else
		{
			cout << endl << INPUT_TO << endl;
			choise = order(begin, end);
			(!choise->prev) ? linkPart(n_elem, n_elem->next, choise, choise->prev) : linkPart(n_elem, n_elem->prev, choise, choise->next);
		}
	}
}

void delEvery2(Queue* start, Queue*& begin, Queue*& end)
{
	Queue* elem = start, * d_elem = NULL, *next_elem = NULL,* next_next_elem = NULL;
	int i = 1;
	
		while (elem)
		{
			next_elem = linkUpdate(start, elem);
			next_next_elem = linkUpdate(start, next_elem);
			if (((i % 2) != 0) && (next_elem))
			{
				reverseLinkUpdate(start, next_next_elem) = elem;
				linkUpdate(start, elem) = next_next_elem;
				d_elem = next_elem;
				next_elem= next_next_elem;
				delete d_elem;
				i++;
			}
			elem = next_elem;
			i++;
			if (!next_elem) (!start->prev) ? end = elem : begin = elem;
		}
}

Queue*& linkUpdate(Queue*& first, Queue*& elem)
{
	return (!first->prev) ? elem->next : elem->prev;
}

Queue*& reverseLinkUpdate(Queue*& first, Queue*& elem)
{
	return (first->prev) ? elem->next : elem->prev;
}

void garbageCollector(Queue* &d_elem)
{
	Queue* link = NULL;
	while (d_elem)
	{
		link = d_elem->next;
		delete d_elem;
		d_elem = link;
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
		cout << endl << " Число выходит за границы инициализации, please try again." << endl;
	}
}
