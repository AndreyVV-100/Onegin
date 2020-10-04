#include "Unit.h"
#include "Sort.h"
#include "Text.h"
#include "main.h"

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
		if (CountSymbols (test, ch) == ans)
			printf ("Test #%d OK\n", i);
		else
			printf ("Test #%d failed, input: answer = %d string = %s, symbol = %c\n",
				i, ans, test, ch);
	}
	fclose (text);
	return;
}