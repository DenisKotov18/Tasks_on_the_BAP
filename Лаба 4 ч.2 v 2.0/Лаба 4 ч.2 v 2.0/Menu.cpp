#include "Menu.h"

int getSize(const char* const []);

int menu(const char head[], const char* const menu_point[])
{
	char exit_catcher = NULL;
	int choise = 0;
	const int points_amt = getSize(menu_point);

	while (true)
	{
		system("cls");
		cout << head << endl << endl;
		for (int i = 0; i < points_amt; i++)
		{
			if (i == choise)
			{
				cout << '>' << "\033[32m" << menu_point[i] << "\033[0m" << '<' << endl;
				continue;
			}
			cout << " " << menu_point[i] << endl;
		}
		exit_catcher = NULL;
		while (exit_catcher != -32)
		{
			exit_catcher = _getch();
			if (exit_catcher == '\r') return choise;
		}
		pointerCatcher(choise, 0, points_amt, 0, 1);
	}
}

int pointerCatcher(int& column, const int& first_point, const int& last_point, int line, const int& line_size)
{
	char switcher = NULL;

	switcher = _getch();

	switch (switcher)
	{
	case UP:
	{
		(column == first_point) ? column = last_point - 1 : column--;
		return line;
	}
	case DOWN:
	{
		column = ++column % last_point;
		return line;
	}
	case LEFT: return (line == 0) ? line_size - 1 : --line;
	case RIGHT: return ((line + 1) % line_size);
	default: break;
	}
	return line;
}

int getSize(const char* const my_vector[])
{
	int i = 0;
	while ( my_vector[i] != NULL) i++;
	return i;
}
