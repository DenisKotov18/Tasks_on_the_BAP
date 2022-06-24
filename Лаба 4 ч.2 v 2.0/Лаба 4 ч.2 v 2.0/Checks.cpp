#include "Checks.h"

const char ERROR[] = "Error, please try again.";
const char INT_ERROR[] = "Пожалуйста, введите целочисленное значение";
const char ERROR_EXPRESSION[] = "   \033[31mНеверное выражение!\033[0m";

void outputSymbol(char*& line, char symbol, int& counter, int i, int& line_size)
{
	if (counter == line_size)
	{
		lineResize(line, 1);
		line_size++;
	}
	line[counter] = symbol;
	printf("%c", symbol);
	counter += i;
}

char* getNumString(char*& num, int& sign)
{
	int counter = 0,
		num_size = 1;
	bool break_flag = false,
		point_flag = false;

	while (break_flag == false)
	{
		char symbol = _getch();
		if ((num[0] == '0' && point_flag == false) && (symbol != '.') && (symbol != ',') && (symbol != '\r') && (symbol != '\b')) continue;
		switch (symbol)
		{
		case '-':
		{
			if ((sign>0) && (counter == 0))
			{
				sign = -1;
				printf("-");
			}
			break;
		}
		case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '0':
			outputSymbol(num, symbol, counter, 1, num_size); break;
		case '.':case',':
		{
			if (point_flag == false && counter > 0)
				{
				point_flag = true;
				outputSymbol(num, '.', counter, 1,num_size);
				}
			break;
		}
		case '\b':
		{
			if (counter > 0)
			{
				if (point_flag == true && num[counter - 1] == '.')
					point_flag = false;
				outputSymbol(num, '\0', --counter, 0, num_size);
				printf("\b \b");
			}
			else
			{
				if (sign < 0)
				{
					sign = 1;
					printf("\b \b");
				}
			}
			break;
		}
		case'\r': 
			if (counter > 0 && num[counter - 1] != '.') break_flag = true; break;
		default:
			break;
		}
	}
	return num;
}

double getDouble(const char message[])
{
	while (true)
	{
		int counter = 0, point_pos = 0, sign = 1;
		char* num = new char[2]{ '\0' };
		double fin_num = 0;
		num = getNumString(num, sign);
		while (num[counter] != '\0')
		{
			if (num[counter] == '.')
				point_pos = counter;
			else
				fin_num = fin_num * 10 + ((int)num[counter] - (int)'0');
			counter++;
		}
		if (point_pos != 0)
		{
			for (int i = point_pos + 1; i < counter; i++)
				fin_num /= 10.;
		}
		delete[]num;
		if (isfinite(fin_num) != 0)
		{
			printf("\n");
			return fin_num * sign;
		}
		printf("\n%s\n%s", ERROR, message);
	}
}

int getInt(const char message[])
{
	while (true)
	{
		int counter = 0, point_pos = 0, sign = 1;
		char* num = new char[2]{ '\0' };
		double fin_num = 0;
		num = getNumString(num, sign);
		while (num[counter] != '\0')
		{
			if (num[counter] == '.')
			{
				point_pos = counter;
				break;
			}
			else
				fin_num = (int)(fin_num * 10 + ((int)num[counter] - (int)'0'));
			counter++;
		}
		delete[]num;
		if (point_pos > 0)
		{
			printf("\n%s\n", INT_ERROR);
			system("pause");
			system("cls");
			printf("%s", message);
			continue;
		}
		if (isfinite(fin_num) != 0)
		{
			printf("\n");
			return fin_num * sign;
		}
		printf("\n%s\n", ERROR);
	}
}

//use delete[] when calling this function
char*& getExpression()
{
	int open_counter = 0,
		close_counter = 0,
		counter = 0,
		expression_size = 1;
	char symbol = 0;
	bool operation_flag = true,
		break_flag = false,
		error_flag = false;
	char* expression = new char[2]{ '\0' };
	while (break_flag == false)
	{
		symbol = _getch();
		if (error_flag) for (int i = 0; i < 22; i++)
		{
			printf("\b \b");
			error_flag = false;
		}
		switch (symbol)
		{
		case'\r':
		{
			if (counter > 0 && open_counter == close_counter && operation_flag == false) break_flag = true;
			else
			{
				printf("%s", ERROR_EXPRESSION);
				error_flag = true;
			}
			break;
		}
		case'/':case'+':case'-':case'*':case'^':
		{
			if (operation_flag == false)
			{
				operation_flag = true;
				outputSymbol(expression, symbol, counter, 1, expression_size);
			}
			break;
		}
		case '(':
		{
			if (operation_flag == true)
			{
				open_counter++;
				outputSymbol(expression, symbol, counter, 1, expression_size);
			}
			break;
		}
		case ')':
		{
			if (operation_flag == false && close_counter < open_counter)
			{ 
			close_counter++;
			outputSymbol(expression, symbol, counter, 1, expression_size);
			}
			break;
		}
		case '\b':
		{
			if (counter > 0)
			{
				switch (expression[counter - 1])
				{

				case'(': open_counter--; break;

				case')':close_counter--; break;

				case'/':case'+':case'-':case'*':case'^': operation_flag = false; break;

				default:
					break;
				}
				if (operation_flag == false && (expression[counter - 1] >= 'a' && expression[counter - 1] <= 'z'))
					operation_flag = true;
				outputSymbol(expression, '\0', --counter, 0, expression_size);
				printf("\b \b");
			}
			break;
		}
		default:
		{
			if (operation_flag == true && (symbol >= 'a' && symbol <= 'z'))
			{
				operation_flag = false;
				outputSymbol(expression, symbol, counter, 1, expression_size);
			}
			break;
		}
		}
	}
	return expression;
}