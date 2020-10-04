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
	size_t original = num_lines;

	Line* lines = (Line*) calloc (num_lines, sizeof (lines[0]));
	num_lines = DoLines (text, lines, num_lines);
	
	QuickSort (lines, num_lines, &CompareFront);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareFront);
	
	PrintTxt  (lines, num_lines, "out_front.txt");

	QuickSort (lines, num_lines, &CompareBack);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareBack);

	PrintTxt (lines, num_lines, "out_back.txt");

	PrintOriginal (text + 1, original);

	free (text);
	free (lines);
	
	return 0;
}
