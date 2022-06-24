#include<iostream>
#include<cmath>
#include<conio.h>
#include <Windows.h>
#include"MyString.h";
#include"Constants.h"
#include"Menu.h"
#include"Checks.h"


using namespace std;

struct Stack
{
	char symbol;
	double number;
	Stack* next;
};

void mainMenu();
char* convert(const char[]);
int getPrior(const char&);
void calculation(const char[], const char[]);
double action(double, double, const char&);
Stack* addChar(Stack*&, const char&);
Stack* addNum(Stack*&, const double&);
char getChar(Stack*&);
double getNum(Stack*&);
Stack* delOne(Stack*&);
int Repeat(const char[], const char[], const int&, const int&);

void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	bool exit_flag = false;
	while (exit_flag == false)
	{
		switch (menu("	Добро пожаловать!", MAIN_POINTS))
		{
		case 0: mainMenu(); break;
		case 1: exit_flag = true; break;
		default: break;
		}
	}
}

void mainMenu()
{
	system("cls");
	printf("%s\n", ENTERING_RPN);
	char* head = new char[1]{ '\0' },
		*line = getExpression(),
		* converted_line = convert(line);
	addToLine(addToLine(addToLine(addToLine(head, MAIN_MENU_HEAD_1), line), MAIN_MENU_HEAD_2), converted_line);
	while (true)
	{
		switch (menu(head, MAIN_MENU_POINTS))
		{
		case 0:
		{
			calculation(converted_line, head);
			system("pause");
			system("cls");
			break;
		}
		case 1: 
		{
			delete[]head;
			delete[]line;
			delete[]converted_line;
			system("pause");
			return;
		}
		default: break;
		}
	}
}

char* convert(const char original_line[])
{
	Stack* begin = NULL;
	char* converted_line = new char[getLineSize(original_line) + 1]{ '\0' };
	int counter_original = 0,
		counter_converted = 0;
	while (original_line[counter_original] != '\0')
	{
		switch (original_line[counter_original])
		{
		case '(': addChar(begin, original_line[counter_original]); break;
		case ')': 
		{
			while (begin->symbol != '(')
			{
				converted_line[counter_converted] = getChar(begin);
				counter_converted++;
			}
			begin = delOne(begin);
			break;
		}
		case'+':case'-':case'*':case'/':case'^':
		{
			if (begin != NULL)
			{
				int symbol_prior = getPrior(original_line[counter_original]);
				if (symbol_prior <= getPrior(begin->symbol))
				{
					while (begin != NULL && symbol_prior <= getPrior(begin->symbol))
					{
						converted_line[counter_converted] = getChar(begin);
						counter_converted++;
					}
				}
				addChar(begin, original_line[counter_original]);
			}
			else begin = addChar(begin, original_line[counter_original]);
			break;
		}
		default:
		{
			converted_line[counter_converted] = original_line[counter_original];
			counter_converted++;
			break;
		}
		}
		counter_original++;
	}
	while (begin != NULL) converted_line[counter_converted] = getChar(begin);
	return converted_line;
}

int getPrior(const char& a)
{
	switch (a)
	{
	case '^': return 4;
	case '*': case '/': return 3;
	case '-': case '+': return 2;
	case '(': return 1;
	default: return 0;
	}
	
}

Stack* addChar(Stack*& begin, const char& symbol)
{
	Stack* n_elem = new Stack;
	n_elem->symbol = symbol;
	n_elem->next = begin;
	begin = n_elem;
	return begin;
}

Stack* addNum(Stack*& begin, const double& number)
{
	Stack* n_elem = new Stack;
	n_elem->number = number;
	n_elem->next = begin;
	begin = n_elem;
	return begin;
}

char getChar(Stack*& begin)
{
	char elem = begin->symbol;
	begin = delOne(begin);
	return elem;
}

double getNum(Stack*& begin)
{
	double elem = begin->number;
	begin = delOne(begin);
	return elem;
}

Stack* delOne(Stack*&  begin)
{
	Stack* del_elem = begin;
	begin = begin->next;
	delete del_elem;
	return begin;
}

double action(double first,double second, const char& operation)
{
	switch (operation)
	{
	case'+': return  first + second;
	case'-': return  first - second;
	case'*': return  first * second;
	case'/': return  first / second;
	case '^': return pow(first, second);
	default:
		return 0;
	}
}

void calculation(const char line[], const char* head)
{
	Stack* begin = NULL;
	int counter = 0,
		repeat_counter = 0;
	char* symbols = new char[2]{ '\0' };
	int* numbers = new int[getLineSize(line) / 2 + 1];
	while (line[counter] != '\0')
	{
		switch (line[counter])
		{
		case'/':
		{
			double first = getNum(begin),
			second = getNum(begin);
			if (first != 0)begin = addNum(begin, action(second, first, line[counter]));
			else
			{
				printf("\n%s\n", ERROR_NULL);
				delete[]symbols;
				delete[]numbers;
				return;
			}
			break;
		}
		case'+':case'-':case'*':case'^':
			{
				begin = addNum(begin, action(getNum(begin), getNum(begin), line[counter]));
				break;
			}
			default:
			{
				int repeat_pos = Repeat(symbols, line, counter, repeat_counter);
				if (repeat_pos != -1) begin = addNum(begin, numbers[repeat_pos]);
				else
				{
					printf("\n%s%c: ", ENTERING_NUM, line[counter]);
					begin = addNum(begin, getDouble(ENTERING_NUM));
					lineResize(symbols, 1);
					symbols[repeat_counter] = line[counter];
					numbers[repeat_counter] = begin->number;
					repeat_counter++;
				}
				break;
			}
		}
		counter++;
	}
	double result = getNum(begin);
	(isfinite(result)) ? printf("%s%g\n",RESULT, result) : printf("%s\n", ERROR_INF);
	delete[]symbols;
	delete[]numbers;
}

int Repeat(const char symbols[], const char line[], const int& counter, const int& repeat_size)
{
	for (int i = 0; i < repeat_size; i++)
	{
		if (line[counter] == symbols[i]) return i;
	}
	return -1;
}