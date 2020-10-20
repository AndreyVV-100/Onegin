#include "Text.h"
#include "Unit.h"
#include "Sort.h"
#include "main.h"

int main()
{
	//TestCountSymbols();

	setlocale(LC_ALL, "Russian");

	const char* file_in = "in.txt";

	Text text = {};

	ConstructorText (&text, file_in);
	
	QuickSort (text.lines, text.n_empty_lines, &CompareFront);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareFront);
	
	PrintTxt  (&text, "out_front.txt");

	QuickSort (text.lines, text.n_empty_lines, &CompareBack);
	//qsort (lines, num_lines, sizeof(lines[0]), CompareBack);

	PrintTxt (&text, "out_back.txt");

	PrintOriginal (&text);

	DestructorText (&text);
	
	return 0;
}
