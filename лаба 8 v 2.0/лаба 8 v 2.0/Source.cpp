#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<Windows.h>
#include<io.h>

using namespace std;

bool menu();
bool except(bool, char[], const char[]);
bool fileMenu(char[]);
void sync(FILE*, struct info*&, int&);
bool sortMenu(struct info[], char* [], const char[], int, int);
bool editMenu(struct info*&, const char[], int&);
void showFile(struct info[], int, const char[]);
void add(struct info[], const char[], int);
void addOne(info &);
void saveNew(struct info[], struct info, const char[], int);
bool del(struct info[], const char[], int, const int);
void saveDel(struct info[], const char[], int, int);
bool corr(struct info[], const char[], int,const int);
void saveCorr(struct info[], const char[], int);
void outputChanges(struct info[], char[], int);
void sortGroup(info[], int);
void sortAvg(info[], char[], int, bool);
int switcherCheck(char, char, const char[]);
int switcherCheck(char, char, const char[], const char[]);
bool goAgain(const char[]);
bool create(char*);
bool fileSelection(char*);
void inputWord(char*, const int&, const char[], const char[], int);
char notTrashAssignment(char&);
void readWord(FILE*, char[]);
double getDouble(const char[],int, int);

const char OUTPUT_FILE[] = "output.txt";
const int SIZE_OF_FILENAME = 20; //max length of the file name(5 sumbols reserved for the .txt extension and \0)
const int GROUP_LENGTH = 7; // length of groups (1 symbol reserved for '\0')
const int LENGTH_OF_STUDENT_NAME = 15;
const int LENGTH_OF_BIRTHDAY = 5;
const int MIN_BIRTHDAY = 1900;
const int MAX_BIRTHDAY = 2021;
//all messages used (for translation)
const char UNCORRECT_INPUT[] = " Возможно, вы ввели что-то не правильно. Попробуйте ещё раз. \n"; //switcherCheck
const char ONE_MORE[] = " Хотите добавить ещё одного студента?\n 1) Да.\n 2) Нет.\n";
const char WELCOME[] = "     Добро пожаловать!\n  Что вы хотите сделать? \n 1) Создать новый файл. \n 2) Выбрать уже существующий файл. \n 0) Выйти. \n"; //menu
const char FILE_ERROR[] = "\n Что-то пошло  не так: ";
const char CREATE_ERROR[] = " Файл не создан!\n";
const char NOT_FOUND[] = " Такого файла не существует!\n";
const char GO_AGAIN[] = " Хотите попробовать снова?\n 1) Да.\n 2) Нет.";
const char FILE_MENU[] = "-текущий файл\n  Меню:\n 1) Посмотреть содержимое файла.\n 2) Сортировать.\n 3) Редактировать файл.\n 0) Назад.\n"; //fileMenu
const char EMPTY[] = " Файл пуст.";
const char SORT_MENU[] = "-текущий файл\n  Меню сортировки:\n 1)Вывести имена студентов, чей средний балл выше введённого с клавиатуры.\n 0) Назад.\n"; //sortMenu
const char GROUP_SELECT[] = "Выберите интересующую вас группу:\n";
const char EDIT_MENU[] = "-текущий файл\n  Меню редактирования:\n 1) Добавить нового студента.\n 2) Редактировать информацию о студенте.\n 3) Удалить данные о студенте.\n 0) Назад.\n "; //editMenu
const char ADD_OK[] = " Успешно добавлено!";
const char DEL_MENU[] = " Введите порядковый номер студента,чьи данные вы хотите удалить. Для отмены введите 0";
const char DEL_CONF[] = " Вы уверены, что хотите удалить данные этого студента?\n 1) Да.\n 2) Нет. ";
const char DEL_OK[] = " Успешно удалено!";
const char CORR_MENU[] = " Введите порядковый номер студента,чьи данные вы хотите изменить. Для отмены введите 0";
const char CORR_CONF[] = " Сохранить изменения?\n 1) Да.\n 2) Нет. ";
const char CORR_OK[] = " Успешно изменено!";
const char SORT_AVG[] = "Введите минимальный средний балл.\n"; //sortAvg
const char SURNAME[] = "Фамилия"; //info
const char NAME[] = "Имя";
const char PATRONYMIC[] = "Отчество";
const char GROUP[] = "№ группы";
const char BIRTHDAY[] = "Г. рожд.";
const char RATING[] = "Оценки за семестр:";
const char PHYSICS[] = "Физ.";
const char MATH[] = "Мат.";
const char INFORMATICS[] = "Информ.";
const char CHEMISTRY[] = "Хим.";
const char AVG_RATING[] = "Ср. балл";
const char UNCRR_AVG[] = "Студенты оцениваются по 10-ти бальной системе."; //getDouble
const char UNCRR_BIRTHDAY[] = "Неверно введённый год рождения. Попробуйте снова.";
const char OK[] = "Ладно.";
const char TOO_LONG_NUM[] = "Ваше число слишком большое.";
const char NO_ONE[] = " Cтудентов со средним баллом выше или равным введённому НЕ НАЙДЕНО."; //sortAvg
const char FILE_NAME_ERR[] = " Название вашего файла достигло максимальной длины."; //inputWord
const char NAME_OF_FILE[] = " Имя файла";
const char TOO_LONG[] = "Достигнуто максимальное количество символов.";
const char ALL[] = "Все."; //global
const char BACK[] = "Назад.";

struct info
{
	char surname[LENGTH_OF_STUDENT_NAME] = { '\0' };
	char name[LENGTH_OF_STUDENT_NAME]{ '\0' };
	char patronymic[LENGTH_OF_STUDENT_NAME] = { '\0' };
	int birthday = NULL;
	char group_num[GROUP_LENGTH] = { NULL };
	float phys = NULL;
	float math = NULL;
	float inform = NULL;
	float  chemist = NULL;
	float avg_rating = NULL;
};

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	SetConsoleCP(1251);
	/*while(true) printf("%i",_getch());*/
	bool menu_flag = true;
	while (menu_flag == true) menu_flag = menu();
	return 0;
}

bool menu()
{
	
	while (true)
	{
		bool except_flag = true;
		printf("%s", WELCOME);
		char switcher = switcherCheck('0', '2', WELCOME);
		system("cls");
		switch (switcher)
		{
		case '1':
		{
			while (except_flag == true)
			{
				char name_of_file[SIZE_OF_FILENAME] = { '\0' };
				except_flag = except(create(&name_of_file[0]), name_of_file, CREATE_ERROR);
			}
			break;
		}
		case '2':
		{
			while (except_flag == true)
			{
				char name_of_file[SIZE_OF_FILENAME] = { '\0' };
				except_flag = except(fileSelection(&name_of_file[0]), name_of_file, NOT_FOUND);
			}
			break;
		}
		case '0':
		{
			printf(" Завершение работы...\n");
			return false;
		}
		default:
			break;
		}
	}
}

bool except(bool func, char name_of_file[], const char message[])
{
	if (func == false)
	{
		printf("%s%s", FILE_ERROR, message);
		if (goAgain(GO_AGAIN) == true)
		{
			system("cls");
			return true;
		}
		system("cls");
		return false;
	}
	system("cls");
	bool file_flag = true;
	while (file_flag == true) file_flag = fileMenu(name_of_file);
	return false;
}

bool fileMenu(char file_name[])
{
	info* student = 0;
	//delete[]student;
	char** no_rep_group = 0;
	int amt_no_repl = 0; //is the numper of non-repeating groups 
	FILE* list;
	fopen_s(&list, file_name, "r");
	int num_of_lines = 0;
	int fd = _fileno(list);
	bool empty_flag = false;
	if (_filelength(fd) == 0)
	{
		empty_flag = true;
		fclose(list);
	}
	else
	{
		sync(list, student, num_of_lines);
		fclose(list);
		if (num_of_lines > 0)
		{
			char** arr_of_groups = new char* [num_of_lines];
			for (int i = 0; i < num_of_lines; i++)
			{
				arr_of_groups[i] = new char[GROUP_LENGTH];
				arr_of_groups[i][GROUP_LENGTH - 1] = '\0';
			}
			sortGroup(student, num_of_lines);
			for (int i = 0; i < (GROUP_LENGTH - 1); i++) arr_of_groups[0][i] = student[0].group_num[i];
			amt_no_repl++;
			for (int i = 1; i < num_of_lines; i++)
			{
				bool repeat_flag = true;
				for (int j = 0; j < amt_no_repl; j++)
				{
					repeat_flag = true;
					for (int k = 0; k < (GROUP_LENGTH - 1); k++)
					{
						if (student[i].group_num[k] != arr_of_groups[j][k])
						{
							repeat_flag = false;
							break;
						}
						if (repeat_flag == false) break;
					}
					if (repeat_flag == true) break;
				}
				if (repeat_flag == true) continue;
				for (int k = 0; k < (GROUP_LENGTH - 1); k++) arr_of_groups[amt_no_repl][k] = student[i].group_num[k];
				amt_no_repl++;
			}
			no_rep_group = new char* [amt_no_repl];
			for (int i = 0; i < amt_no_repl; i++)
			{
				no_rep_group[i] = new char[GROUP_LENGTH];
				no_rep_group[i][GROUP_LENGTH - 1] = '\0';
			}
			for (int i = 0; i < amt_no_repl; i++)
			{
				for (int j = 0; j < (GROUP_LENGTH - 1); j++) no_rep_group[i][j] = arr_of_groups[i][j];
			}
			for (int i = 0; i < num_of_lines; i++) delete[]arr_of_groups[i];
			delete[]arr_of_groups;
		}
		else empty_flag = true;
	}
	while (true)
	{
		system("cls");
		printf("\"%s\"%s ", file_name, FILE_MENU);
		int switcher = switcherCheck('0', '3', file_name, FILE_MENU);
		switch (switcher)
		{
		case '1':
		{
			/*for(int i = 0;i<2;i++)*/
			showFile(student, num_of_lines, EMPTY);
			system("pause");
			break;
		}
		case '2':
		{
			if (num_of_lines > 0)
			{
				bool sort_flag = true;
				while (sort_flag == true) sort_flag = sortMenu(student, no_rep_group, file_name, num_of_lines, amt_no_repl);
			}
			else
			{
				system("cls");
				printf("%s\n", EMPTY);
				system("pause");
			}
			break;
		}
		case '3':
		{
			bool edit_flag = true;
			while (edit_flag == true) edit_flag = editMenu(student, file_name, num_of_lines);
			if (empty_flag == false)
			{
				for (int i = 0; i < amt_no_repl; i++) delete[]no_rep_group[i];
				delete[]no_rep_group;
			}
			if (num_of_lines > 0) delete[]student;
			return true;
		}
		case '0':
		{
			system("cls");
			printf("");
			outputChanges(student, file_name, num_of_lines);
			if (num_of_lines > 0)
			{
				for (int i = 0; i < amt_no_repl; i++) delete[]no_rep_group[i];
				delete[]no_rep_group;
				delete[]student;
			}
			return false;
		}
		default: break;
		}
	}
}

void sync(FILE* list, info*& student, int& num_of_lines)
{
	fscanf_s(list, "%i \n", &num_of_lines);
	if (num_of_lines > 0)
	{
		info* re_student = new info[num_of_lines];
		for (int i = 0; i < num_of_lines; i++)
		{
			fscanf_s(list, " \n");
			readWord(list, re_student[i].surname);
			fscanf_s(list, " ");
			readWord(list, re_student[i].name);
			fscanf_s(list, " ");
			readWord(list, re_student[i].patronymic);
			fscanf_s(list, " ");
			fscanf_s(list, " %d", &re_student[i].birthday);
			fscanf_s(list, " ");
			readWord(list, re_student[i].group_num);
			fscanf_s(list, " %f", &re_student[i].phys);
			fscanf_s(list, " %f", &re_student[i].math);
			fscanf_s(list, " %f", &re_student[i].inform);
			fscanf_s(list, " %f", &re_student[i].chemist);
			re_student[i].avg_rating = (re_student[i].phys + re_student[i].math + re_student[i].inform + re_student[i].chemist) / 4;
		}
		student = re_student;
	}
}

bool sortMenu(info student[], char* group[], const char file_name[], int amount, int num)
{
	while (true)
	{
		system("cls");
		printf("\"%s\"%s", file_name, SORT_MENU);
		char switcher = switcherCheck('0', '1', file_name, SORT_MENU);
		switch (switcher)
		{
		case '1':
		{
			int counter = 0;
			bool all_flag = false;
			system("cls");
			printf("  %s", GROUP_SELECT);
			for (; counter < num; counter++) printf(" %1d) %s\n", (counter + 1), group[counter]);
			printf(" %1d) %s\n 0) %s\n", ++counter, ALL, BACK);
			int len_num = 0, re_amt = num;
			while (re_amt > 9)
			{
				re_amt /= 10;
				len_num++;
			}
			len_num++;
			int choise = getDouble(GROUP_SELECT, len_num,1);
			while ((choise < 0) || (choise > counter))
			{
				printf("\n%s\n", UNCORRECT_INPUT);
				choise = getDouble(GROUP_SELECT, len_num, 1);
			}
			char curr_group[GROUP_LENGTH] = { '\0' };
			switch (choise)
			{
			case 0: return true;
			default:
			{
				if (choise != counter)
				{
					for (int i = 0; i < (GROUP_LENGTH - 1); i++) curr_group[i] = group[choise - 1][i];
				}
				else all_flag = true;
				break;
			}
			}
			sortAvg(student, curr_group, amount, all_flag);
			break;
		}
		case '0': return false;
		}
	}
}

bool editMenu(info *&student, const char file_name[], int &amount)
{
	while (true)
	{
		bool corr_flag = true, del_flag = true;
		if (amount > 0) delete[]student;
			FILE* list;
			fopen_s(&list, file_name, "r");
			sync(list, student, amount);
			fclose(list);
			sortGroup(student, amount);
			int len_num = 0, re_amt = amount;
			while (re_amt > 9)
			{
				re_amt /= 10;
				len_num++;
			}
			len_num++;
		system("cls");
		printf("\"%s\"%s", file_name, EDIT_MENU);
		char switcher = switcherCheck('0', '3', file_name, EDIT_MENU);
		switch (switcher)
		{
		case '1':
		{
			add(student, file_name, amount);
			break;
		}
		case '2':
		{
			if (amount > 0)
			{
				while (corr_flag == true) corr_flag = corr(student, file_name, amount, len_num);
			}
			else
			{
				system("cls");
				printf("%s\n", EMPTY);
				system("pause");
			}
			break;
		}
		case '3':
		{
			if (amount > 0)
			{
				while (del_flag == true) del_flag = del(student, file_name, amount, len_num);
			}
			else
			{
				system("cls");
				printf("%s\n", EMPTY);
				system("pause");
			}
			break;
		}
		case '0': return false;
		default: break;
		}
	}
}

void showFile(info student[], int amount, const char message[])
{
	system("cls");
	if (amount > 0)
	{
		printf("==");
		for (int i = 1; i < 38; i++) printf("___");
		printf("==");
		printf("\n|| № | %-15s | %-15s | %-15s |%s|%-9s| %s| %s|%s| %s|%s||\n||", SURNAME, NAME, PATRONYMIC, BIRTHDAY, GROUP, PHYSICS, MATH, INFORMATICS, CHEMISTRY, AVG_RATING);
		for (int i = 1; i < 38; i++) printf("===");
		printf("||");
		for (int i = 0; i < amount; i++)
		{
			printf(" \n|| %1d | %-15s | %-15s | %-15s |  %4d  | %-6s  |%-5.2f|%-5.2f| %-5.2f |%-5.2f|  %-5.2f ||\n||", (i+1), student[i].surname, student[i].name, student[i].patronymic, student[i].birthday, student[i].group_num, student[i].phys, student[i].math, student[i].inform, student[i].chemist, student[i].avg_rating);
			if (i != (amount - 1))
			{
				for (int j = 1; j < 38; j++) printf("---");
			}
			else
			{
				for (int j = 1; j < 38; j++) printf("___");
			}
			printf("||");
		}
	}
	else printf("%s", message);
	printf("\n ");
}

void outputChanges(info student[], char file_name[], int amount)
{
	FILE* list;
	fopen_s(&list, OUTPUT_FILE, "w");
	system("cls");
	fprintf(list, "==");
	for (int i = 1; i < 38; i++) fprintf(list, "___");
	fprintf(list, "==");
	fprintf(list,"\n|| № | %-15s | %-15s | %-15s |%s|%-9s| %s| %s|%s| %s|%s||\n||", SURNAME, NAME, PATRONYMIC, BIRTHDAY, GROUP, PHYSICS, MATH, INFORMATICS, CHEMISTRY, AVG_RATING);
	for (int i = 1; i < 38; i++) fprintf(list, "===");
	fprintf(list, "||");
	for (int i = 0; i < amount; i++)
	{
		fprintf(list," \n|| %1d | %-15s | %-15s | %-15s |  %4d  | %-6s  |%-5.2f|%-5.2f| %-5.2f |%-5.2f|  %-5.2f ||\n||", (i + 1), student[i].surname, student[i].name, student[i].patronymic, student[i].birthday, student[i].group_num, student[i].phys, student[i].math, student[i].inform, student[i].chemist, student[i].avg_rating);
		if (i != (amount - 1))
		{
			for (int j = 1; j < 38; j++) fprintf(list, "---");
		}
		else
		{
			for (int j = 1; j < 38; j++) fprintf(list, "___");
		}
		fprintf(list, "||");
	}
	fprintf(list, "\n %s", file_name);
	fclose(list);
}

void add(info student[], const char file_name[], int amount)
{
	info new_stud;
	system("cls");
	addOne(new_stud);
	saveNew(student, new_stud, file_name, amount);
	printf("\n.\n.\n.\n %s\n", ADD_OK);
	system("pause");
}

void addOne(info &new_stud)
{
	printf("\n %s-", SURNAME);
	inputWord(&new_stud.surname[0], LENGTH_OF_STUDENT_NAME, SURNAME, TOO_LONG, 2);
	printf("\n %s-", NAME);
	inputWord(&new_stud.name[0], LENGTH_OF_STUDENT_NAME, NAME, TOO_LONG, 2);
	printf("\n %s-", PATRONYMIC);
	inputWord(&new_stud.patronymic[0], LENGTH_OF_STUDENT_NAME, PATRONYMIC, TOO_LONG, 2);
	printf("\n %s-", BIRTHDAY);
	new_stud.birthday = getDouble(BIRTHDAY,5, 1);
	while ((new_stud.birthday < MIN_BIRTHDAY) || (new_stud.birthday > MAX_BIRTHDAY))
	{
		printf(" %s\n 1)%s", UNCRR_BIRTHDAY, OK);
		while (_getch() != '1');
		printf(" %s-", BIRTHDAY);
	}
	printf("\n %s-", GROUP);
	inputWord(&new_stud.group_num[0], GROUP_LENGTH, GROUP, TOO_LONG, 3);
	printf("\n\n %s", RATING);
	printf("\n %s-", PHYSICS);
	new_stud.phys = getDouble(PHYSICS,5, 2);
	printf("\n %s-", MATH);
	new_stud.math = getDouble(MATH,5,2);
	printf("\n %s-", INFORMATICS);
	new_stud.inform = getDouble(INFORMATICS,5, 2);
	printf("\n %s-", CHEMISTRY);
	new_stud.chemist = getDouble(CHEMISTRY,5, 2);
	new_stud.avg_rating = (new_stud.phys + new_stud.math + new_stud.inform + new_stud.chemist) / 4;
}

void saveNew(info stud[], info new_stud, const char file_name[], int amount)
{
	FILE* list;
	fopen_s(&list, file_name, "w");
	fprintf(list, " %d", (amount + 1));
	for (int i = 0; i < amount; i++) fprintf(list, "\n%s %s %s %d %s %5.2f %5.2f %5.2f %5.2f", stud[i].surname, stud[i].name, stud[i].patronymic, stud[i].birthday, stud[i].group_num, stud[i].phys, stud[i].math, stud[i].inform, stud[i].chemist);
	fprintf(list, "\n%s %s %s %d %s %5.2f %5.2f %5.2f %5.2f", new_stud.surname, new_stud.name, new_stud.patronymic, new_stud.birthday, new_stud.group_num, new_stud.phys, new_stud.math, new_stud.inform, new_stud.chemist);
	fclose(list);
}

bool del(struct info stud[], const char file_name[], int amount, const int len)
{
	system("cls");
	showFile(stud, amount, "");
	printf("%s\n", DEL_MENU);
	int switcher = getDouble(DEL_MENU,len,1);
	while ((switcher < 0) || (switcher > amount))
	{
		printf("\n%s\n", UNCORRECT_INPUT);
		switcher = getDouble(DEL_MENU, len, 1);
	}
	if (switcher == 0) return false;
	switcher--;
	printf("\n %s %s %s  %s- %d  %s- %s  %s- %5.2f  %s- %5.2f  %s- %5.2f  %s- %5.2f  %s- %5.2f\n", stud[switcher].surname, stud[switcher].name, stud[switcher].patronymic, BIRTHDAY, stud[switcher].birthday, GROUP, stud[switcher].group_num, PHYSICS, stud[switcher].phys, MATH, stud[switcher].math, INFORMATICS, stud[switcher].inform, CHEMISTRY, stud[switcher].chemist, AVG_RATING, stud[switcher].avg_rating);
	if (goAgain(DEL_CONF) == false) return true;
	saveDel(stud, file_name, amount, switcher);
	printf("\n.\n.\n.\n %s\n", DEL_OK);
	system("pause");
	return false;
}

void saveDel(info stud[], const char file_name[], int amount, int pos)
{
	FILE* list;
	fopen_s(&list, file_name, "w");
	fprintf(list, " %d", (amount - 1));
	for (int i = 0; i < amount; i++) if (i != pos) fprintf(list, "\n%s %s %s %d %s %5.2f %5.2f %5.2f %5.2f", stud[i].surname, stud[i].name, stud[i].patronymic, stud[i].birthday, stud[i].group_num, stud[i].phys, stud[i].math, stud[i].inform, stud[i].chemist);
	fclose(list);
}

bool corr(info stud[], const char file_name[], int amount, const int len)
{
	system("cls");
	showFile(stud, amount, "");
	printf("\n%s\n", CORR_MENU);
	int switcher = getDouble(CORR_MENU, len, 1);
	while ((switcher < 0) || (switcher > amount))
	{
		printf("%s\n", UNCORRECT_INPUT);
		switcher = getDouble(CORR_MENU, len, 1);
	}
	if (switcher == 0) return false;
	switcher--;
	printf("\n %s %s %s  %s- %d  %s- %s  %s- %5.2f  %s- %5.2f  %s- %5.2f  %s- %5.2f  %s- %5.2f\n", stud[switcher].surname, stud[switcher].name, stud[switcher].patronymic, BIRTHDAY, stud[switcher].birthday, GROUP, stud[switcher].group_num, PHYSICS, stud[switcher].phys, MATH, stud[switcher].math, INFORMATICS, stud[switcher].inform, CHEMISTRY, stud[switcher].chemist, AVG_RATING, stud[switcher].avg_rating);
	info intermediate = stud[switcher];
	addOne(stud[switcher]);
	printf("\n");
	if (goAgain(CORR_CONF) == false)
	{
		stud[switcher] = intermediate;
		return true;
	}
	sortGroup(stud, amount);
	saveCorr(stud, file_name, amount);
	printf("\n.\n.\n.\n %s\n", CORR_OK);
	system("pause");
	return false;
}

void saveCorr(info stud[], const char file_name[], int amount)
{
	FILE* list;
	fopen_s(&list, file_name, "w");
	fprintf(list, " %d", amount);
	for (int i = 0; i < amount; i++) fprintf(list, "\n%s %s %s %d %s %5.2f %5.2f %5.2f %5.2f", stud[i].surname, stud[i].name, stud[i].patronymic, stud[i].birthday, stud[i].group_num, stud[i].phys, stud[i].math, stud[i].inform, stud[i].chemist);
	fclose(list);
}

void sortGroup(info student[], int amount)
{
	for (int counter = (GROUP_LENGTH - 2); counter >= 0; counter--)
	{
		int i = 1;
		while (i < amount)
		{
			if (student[i].group_num[counter] < student[i - 1].group_num[counter])
			{
				info intermediate;
				intermediate = student[i - 1];
				student[i - 1] = student[i];
				student[i] = intermediate;
				if (i > 1) i -= 2;
			}
			i++;
		}
	}
}

void sortAvg(info student[], char group[], int amount, bool flag)
{
	int counter = 0;
	int sort_amount = 0;
	system("cls");
	printf("%s", SORT_AVG);
	double min_avg = getDouble(SORT_AVG,5, 2);
	for (int i = 0; i < amount; i++)
	{
		if ((student[i].avg_rating >= min_avg)) counter++;
	}
	info* sort_student = new info[counter];
	for (int i = 0; i < amount; i++)
	{
		bool continue_flag = false;
		if (student[i].avg_rating >= min_avg)
		{
			if (flag == false)
			{
				for (int j = 0; j < (GROUP_LENGTH - 1); j++)
				{
					if (student[i].group_num[j] != group[j])
					{
						continue_flag = true;
						break;
					}
				}
				if (continue_flag == true) continue;
			}
			sort_student[sort_amount] = student[i];
			sort_amount++;
		}
	}
	showFile(sort_student, sort_amount, NO_ONE);
	system("pause");
	delete[]sort_student;
}

int switcherCheck(char left, char right, const char message[])
{
	char switcher = _getch();
	while ((switcher < left) || (switcher > right))
	{
		printf("\n%s ", UNCORRECT_INPUT);
		system("pause");
		system("cls");
		printf("%s ", message);
		switcher = _getch();
	}
	return switcher;
}

int switcherCheck(char left, char right, const char pre_message[], const char message[])
{
	char switcher = _getch();
	while ((switcher < left) || (switcher > right))
	{
		printf("\n%s ", UNCORRECT_INPUT);
		system("pause");
		system("cls");
		printf("\"%s\"%s ", pre_message, message);
		switcher = _getch();
	}
	return switcher;
}

bool goAgain(const char message[])
{
	printf("\n%s", message);
	int switcher = switcherCheck('1', '2', message);
	return (switcher == '1') ? true : false;
}

bool create(char* name)
{
	printf(" Введите имя файла. (Не более %i символов)\n ", (SIZE_OF_FILENAME - 5));
	inputWord(name, SIZE_OF_FILENAME, NAME_OF_FILE, FILE_NAME_ERR, 1);
	FILE* list;
	fopen_s(&list, name, "w");
	if (list == NULL) return false;
	fclose(list);
	return true;
}

bool fileSelection(char* name)
{
	printf(" Введите имя файла. (Не более %i символов)\n ", (SIZE_OF_FILENAME - 5));
	inputWord(name, SIZE_OF_FILENAME, NAME_OF_FILE, FILE_NAME_ERR, 1);
	FILE* list;
	fopen_s(&list, name, "r");
	if (list == NULL) return false;
	fclose(list);
	return true;
}
// function modes 1-creating a file name 2-entering a word 3-entering a number
void inputWord(char* line, const int& size, const char message[], const char border[], int mode)
{
	int mode_size = size;
	switch (mode)
	{
	case 2: case 3: mode_size += 4;
	default: break;
	}
	char intermediate = NULL, not_trash = NULL;
	int counter = 0;
	while (line[counter] != '\0') counter++;
	printf("%s", line);
	bool break_flag = false;
	while (break_flag == false)
	{
		intermediate = notTrashAssignment(not_trash);
		if (intermediate == -32)
		{
			printf("%c", intermediate);
			char trash = _getch();
			if (!((trash == 75) || (trash == 80) || (trash == 72) || (trash == 77) || (trash == -123)))
			{
				line[counter] = intermediate;
				not_trash = trash;
				counter++;
				continue;
			}
			printf("\b \b");
			continue;
		}
		if ((counter == (mode_size - 5)) && (intermediate != '\b') && (intermediate != '\r'))
		{
			printf("\n%s\n", border);
			system("pause");
			printf("\n\n%s- %s", message, line);
			continue;
		}
		switch (intermediate)
		{
		case 27: case'\\': case'/': case':': case'*': case'?': case'"': case'<': case '>': case'|':
		{
			break;
		}
		case'\0':
		{
			char trash = _getch();
			break;
		}
		case '\r':
		{
			if (counter > 0) break_flag = true;
			break;
		}
		case '\b':
		{
			if (counter > 0)
			{
				printf("\b \b");
				counter--;
				line[counter] = '\0';
			}
			break;
		}
		case '0': case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
		{
			if (mode != 2)
			{
				line[counter] = intermediate;
				printf("%1c", intermediate);
				counter++;
			}
			break;
		}
		case ' ':
		{
			if (mode == 1)
			{
				line[counter] = intermediate;
				printf("%1c", intermediate);
				counter++;
			}
			break;
		}
		default:
		{
			if (mode != 3)
			{
				line[counter] = intermediate;
				printf("%1c", intermediate);
				counter++;
			}
			break;
		}
		}
	}
	while (line[0] == ' ')
	{
		for (int i = 0; i < counter; i++) line[i] = line[i + 1];
		counter--;
	}
	while (line[counter - 1] == ' ')
	{
		line[counter - 1] = '\0';
		counter--;
	}
	if (mode == 1)
	{
		line[counter] = '.';
		line[counter + 1] = 't';
		line[counter + 2] = 'x';
		line[counter + 3] = 't';
	}
}

char notTrashAssignment(char& not_trash)
{
	char symbol = NULL;
	if (not_trash == NULL)
	{
		symbol = _getch();
	}
	else
	{
		symbol = not_trash;
		not_trash = NULL;
	}
	return symbol;
}

void readWord(FILE* list, char argument[])
{
	int i = 0;
	do
	{
		fscanf_s(list, "%1c", &argument[i], 1);
		i++;
	} while ((argument[i - 1] != NULL) && (argument[i - 1] != ' ') && (argument[i - 1] != '\n'));
	argument[i - 1] = '\0';
}
// function modes 1-integer 2-double 
double getDouble(const char message[],int len, int mode)
{
	while (true)
	{
		int counter = 0, point_pos = NULL;
		char *num = new char[len+1];
		num[len] = '\0';
		double fin_num = 0;
		int l_num = NULL;
		bool break_flag = false, point_flag = false, first_null = false;
		while (break_flag == false)
		{
			char symbol = _getch();
			if ((counter == len) && (symbol != '\b') && (symbol != '\r'))
			{
				printf("\n%s\n", TOO_LONG_NUM);
				system("pause");
				printf("\n\n%s- %s", message, num);
				continue;
			}
			if ((first_null == true) && (symbol != '\b') && (symbol != '\r') && (symbol != ',') && (symbol != '.')) continue;
			switch (symbol)
			{
			case '0':
			{
					num[counter] = symbol;
					counter++;
					printf("%1c", symbol);
					if (counter == 1) first_null = true;
					break;
			}
			case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
			{
				num[counter] = symbol;
				counter++;
				printf("%1c", symbol);
				break;
			}
			case '.':case',':
			{
				if ((point_flag == false) && (counter > 0) && (mode == 2))
				{
					point_flag = true;
					point_pos = counter;
					num[counter] = '.';
					printf(".");
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
					printf("\b \b");
					break;
				}
				if (counter == 1)
				{
					counter--;
					num[counter] = '\0';
					printf("\b \b");
					first_null = false;
					break;
				}
				if (counter > 0)
				{
					counter--;
					num[counter] = '\0';
					printf("\b \b");
				}
				break;
			}
			case'\r': 
			{
				if (counter > 0)
				break_flag = true;
			}
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
		delete[]num;
		switch (mode)
		{
		case 1: return fin_num;
		case 2:
			{
				if ((fin_num > 0) && (fin_num <= 10)) return fin_num;
				system("cls");
				printf(" %s\n 1)%s", UNCRR_AVG, OK);
				break;
			}
		}
		while (_getch() != '1');
		system("cls");
		printf(" %s-", message);
	}
}