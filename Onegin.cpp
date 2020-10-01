// ToDo: Закрывать все открываемые файлы руками
// ToDo: Пробелов должно быть ровно столько, сколько нужно
// ToDo: Обработка ошибок пользователей c printf-ом
// ToDo: Обработка ошибок программиста с assert-ом
// ToDo: Обработка ошибок "окружения" тоже с printf-ом

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#include <search.h>

#pragma warning(disable : 6387)
//"file_out" может быть равен "0":  это не соответствует спецификации функции "fclose".Самое раннее расположение, где это могло произойти, см.в строке 92
#pragma warning(disable : 4996)
//'fopen': This function or variable may be unsafe.Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.

struct Line
{
	char* point = nullptr;
	size_t lenght = 0;
};

void ReadTxt (char** text, const char* file_name);

int CountSymbols (char* text, const char str);

void DoLines (char* text, Line *lines, int num_lines);

void QuickSort (Line * mass, size_t num_elements,
	int (*comp)(const void* element1, const void* element2));

void Swap (Line* var1, Line* var2);

int CompareFront (const void* element1, const void* element2);
int CompareBack  (const void* element1, const void* element2);

void PrintTxt (Line* lines, int num_lines, const char* file_name);

void TestCountSymbols();

void TestDoLines();

void TestQuickSort();

void TestSwap();

void TestCompareFront();

void TestCompareBack();

int main()
{
	TestCountSymbols();

	char* text = NULL;
	ReadTxt (&text, "in.txt");
	size_t num_lines = CountSymbols (text, '\n') + 1;

	Line* lines = (Line*) calloc (num_lines, sizeof (lines[0]));
	DoLines (text, lines, num_lines);
	
	/*
	QuickSort (lines, num_lines, &CompareFront);
	PrintTxt  (lines, num_lines, "out_front.txt");
	*/

	qsort (lines, num_lines, sizeof(lines[0]), CompareFront);
	PrintTxt (lines, num_lines, "out_front.txt");

	qsort (lines, num_lines, sizeof(lines[0]), CompareBack);
	PrintTxt (lines, num_lines, "out_back.txt");

	free (text);
	free (lines);
	
	return 0;
}

void ReadTxt (char** text, const char* file_name)
{
	assert (text);
	assert (file_name);

	FILE* file = fopen (file_name, "r");
	if (file == NULL)
	{
		printf("[Input error] Unable to open file \"%s\"\n", file_name);
		exit(EXIT_FAILURE);
	}

	fseek (file, 0, SEEK_END);
	size_t num_symbols = ftell (file);
	fseek (file, 0, SEEK_SET);

	*text = (char*) calloc (num_symbols + 2, sizeof (**text));
	if (*text == NULL)
	{
		printf("[Error] Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	fread (*text, sizeof (**text), num_symbols, file);
	
	fclose (file);

	return;
}

int CountSymbols(char* text, const char str)
{
	assert (text);
	int counter = 0;
	if (*text == str) counter++;
	while (text = strchr(text + 1, str)) counter++;
	return counter;
}

void DoLines (char* text, Line *lines, int num_lines)
{
	assert (text);
	assert (lines);
	assert (lines > 0);
	
	if (*text != '\n')
		lines[0].point = text;

	int i_line = 1;
	//i_line
	for (i_line; i_line < num_lines; i_line++)
	{
		lines[i_line].point = strchr (lines[i_line - 1].point, '\n') + 1;
		*(lines[i_line].point - 1) = '\0';
		lines[i_line - 1].lenght = lines[i_line].point - lines[i_line - 1].point;
	}
	
	i_line--;
	lines[i_line].lenght = strchr (lines[i_line].point, '\0') - 
		lines[i_line].point + 1;

	return;
}

void PrintTxt (Line *lines, int num_lines, const char* file_name)
{
	assert (lines);
	assert (num_lines > 0);

	FILE* file_out = NULL;
	fopen_s (&file_out, file_name, "w");
	for (int i = 0; i < num_lines; i++)
		fprintf (file_out, "%s\n", lines[i].point);

	fclose (file_out);
	return;
}

void QuickSort(Line* mass, size_t num_elements, 
		int (*comp)(const void* element1, const void* element2))
{
	assert (num_elements >= 0);
	assert (mass);
	assert (comp);

	int left  = 0;
	int	right = num_elements - 1;
	int mid   = (left + right) / 2;

	while (left < right)
	{
		//printf ("%d %d\n", left, right);
		while ((*comp)(mass +  left, mass + mid) <  0) left++;
		//printf("kk\n");
		while ((*comp)(mass + right, mass + mid) >= 0) right--;
		//printf("gg\n");

		if (left >= right) break;
		Swap (mass + left++, mass + right--);
	}

	printf("%d %d\n", left, right);
	if (right > 1)
		QuickSort (mass,                        right, comp);
	if (right + 1 < num_elements && right > 0) 
		QuickSort (mass + right, num_elements - right, comp);
	return;
}

void Swap (Line* var1, Line* var2)
{
	assert (var1);
	assert (var2);
	
	Line temp = *var1;
	*var1 = *var2;
	*var2 = temp;
	return;
}

int CompareFront (const void* element1, const void* element2)
{
	assert (element1);
	assert (element2);

	char* el1 = (*((Line*)element1)).point;
	char* el2 = (*((Line*)element2)).point;

	while (1)
	{
		if (*el1 == '\0' && *el2 == '\0')
			return 0;
		if (*el1 == '\0')
			return -1;
		if (*el2 == '\0')
			return 1;

		//printf ("%s $$$ %s\n", el1, el2);

		if (isalpha(*el1) == 0)
		{
			el1++;
			continue;
		}
		if (isalpha(*el2) == 0)
		{
			el2++;
			continue;
		}

		if (*el1 == *el2)
		{
			el1++;
			el2++;
			continue;
		}

		return *el1 - *el2;
	}
}

int CompareBack (const void* element1, const void* element2)
{
	assert (element1);
	assert (element2);

	if (*(*((Line*)element1)).point == '\0') return -1;
	if (*(*((Line*)element2)).point == '\0') return +1;

	char* el1 = (*((Line*)element1)).point + (*((Line*)element1)).lenght - 2;
	char* el2 = (*((Line*)element2)).point + (*((Line*)element2)).lenght - 2;

	while (1)
	{
		if (*el1 == '\0' && *el2 == '\0')
			return 0;
		if (*el1 == '\0')
			return -1;
		if (*el2 == '\0')
			return 1;

		//printf("%s $$$ %s\n", el1, el2);

		if (isalpha(*el1) == 0)
		{
			el1--;
			continue;
		}
		if (isalpha(*el2) == 0)
		{
			el2--;
			continue;
		}

		if (*el1 == *el2)
		{
			el1--;
			el2--;
			continue;
		}

		return *el1 - *el2;
	}
}

void TestCountSymbols()
{
	FILE* text = fopen ("TestCountSymbols.txt", "r");
	assert (text);

	int n = 0;
	fscanf (text, "%d\n", &n);

	char test[50] = {};
	int ans = 0;
	char ch = '\0';

	for (int i = 0; i < n; i++)
	{
		fscanf (text, "%d %c %s\n", &ans, &ch, test);
		if (CountSymbols(test, ch) == ans)
			printf ("Test #%d OK\n", i);
		else
			printf ("Test #%d failed, input: answer = %d string = %s, symbol = %c\n",
				i, ans, test, ch);
	}
	fclose (text);
	return;
}

void TestDoLines();

void TestQuickSort();

void TestSwap();

void TestCompareFront();

void TestCompareBack();
