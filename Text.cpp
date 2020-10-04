#include "Text.h"
#include "main.h"

int CountSize (FILE* file)
{
	fseek(file, 0, SEEK_END);
	size_t num_symbols = ftell(file);
	fseek(file, 0, SEEK_SET);

	return num_symbols;
}

void PrintOriginal(char* text, size_t num_lines)
{
	FILE* file = fopen ("original.txt", "w");

	for (int i_line = 0; i_line < num_lines; i_line++)
	{
		size_t num_skip = CountSymbols (text, '\n');
		fprintf (file, "%s\n", text);
		text = strchr (text, '\0') + 1;
	}

	fclose (file);

	return;
}

void ReadTxt (char** text, const char* file_name)
{
	assert (text);
	assert (file_name);

	FILE* file = fopen (file_name, "r");
	if (file == NULL)
	{
		printf ("[Input error] Unable to open file \"%s\"\n", file_name);
		exit (EXIT_FAILURE);
	}

	size_t num_symbols = CountSize (file);

	*text = (char*)calloc (num_symbols + 2, sizeof (**text));
	if (*text == NULL)
	{
		printf ("[Error] Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	**text = '\0';
	fread (*text + 1, sizeof (**text), num_symbols, file);

	fclose (file);

	return;
}

int CountSymbols (char* text, const char str)
{
	assert (text);
	int counter = 0;
	if (*text == str) 
		counter++;
	while (text = strchr (text + 1, str))
		counter++;
	return counter;
}

void PrintTxt (Line *lines, int num_lines, const char* file_name)
{
	assert (lines);
	assert (num_lines > 0);

	FILE* file_out = fopen (file_name, "w");

	for (int i = 0; i < num_lines; i++)
		fprintf (file_out, "%s\n", lines[i].point);

	fclose (file_out);
	return;
}

