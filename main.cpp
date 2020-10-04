// ToDo: Закрывать все открываемые файлы руками
// ToDo: Пробелов должно быть ровно столько, сколько нужно
// ToDo: Обработка ошибок пользователей c printf-ом
// ToDo: Обработка ошибок программиста с assert-ом
// ToDo: Обработка ошибок "окружения" тоже с printf-ом

#include "Text.h"
#include "Unit.h"
#include "Sort.h"
#include "main.h"

int main()
{
	//TestCountSymbols();
	setlocale(LC_ALL, "Russian");

	char* text = NULL;
	ReadTxt (&text, "in.txt");
	size_t num_lines = CountSymbols (text + 1, '\n') + 1;

	Line* lines = (Line*) calloc (num_lines, sizeof (lines[0]));
	num_lines = DoLines (text, lines, num_lines);
	
	QuickSort (lines, num_lines, &CompareFront);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareFront);
	
	PrintTxt  (lines, num_lines, "out_front.txt");

	QuickSort (lines, num_lines, &CompareBack);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareBack);

	PrintTxt (lines, num_lines, "out_back.txt");

	free (text);
	free (lines);
	
	return 0;
}