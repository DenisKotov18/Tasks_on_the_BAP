#include "MyString.h"

int getLineSize(const char line[]) 
{
	int i = 0;
	while (line[i] != '\0') i++;
	return i;
}

char* lineResize(char*& line, int additional_cells)
{
	int old_size = getLineSize(line),
		new_size = old_size + additional_cells;
	char* re_line = NULL;
	if (new_size >= 0) re_line = new char[new_size + 1]{ '\0' };
	else
	{
		printf("ERROR LineResize: Line size < 1.");
		return NULL;
	}

	if (new_size > old_size)
		for (int i = 0; i < old_size; i++) re_line[i] = line[i];
	else
		for (int i = 0; i <= new_size-1; i++) re_line[i] = line[i];
	delete[]line;
	line = re_line;
	return line;
}

char*& addToLine(char*& original_line  , const char additional_line[])
{
	int old_size = getLineSize(original_line),
		additional_size = getLineSize(additional_line),
		new_size = old_size + additional_size;
	lineResize(original_line, additional_size);
	for (int i = old_size, j = 0; i < new_size; i++, j++)
		original_line[i] = additional_line[j];
	return original_line;
}

void copyLine(const char old_line[], char new_line[])
{
	int i = 0;
	while (old_line[i] != '\0')
	{
		new_line[i] = old_line[i];
		i++;
	}
	new_line[i] = '\0';
}