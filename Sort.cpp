#include "Sort.h"
#include "main.h"

int DoLines (char* text, Line* lines, int num_lines)
{
	assert (text);
	assert (lines);
	assert (num_lines > 0);

	char* first = nullptr,
		* second = text;

	for (int i_line = 0; i_line < num_lines; i_line++)
	{
		size_t count_empty = 0;

		do
		{
			count_empty++;
			first = second + 1;
			second = strchr (first, '\n');
		} while (second - first < 2 && second);

		num_lines -= --count_empty;

		if (second)
		{
			lines[i_line].point = first;
			lines[i_line].lenght = second - first + 1;
			*second = '\0';
		}
		else
		{
			second = strchr (first + 1, '\0');
			if (second && second - first)
			{
				lines[i_line].point = first;
				lines[i_line].lenght = second - first - 1;
				*second = '\0';
			}
		}
	}

	assert (num_lines > 0);
	return num_lines;
}

void QuickSort (Line* mass, size_t num_elements,
	int (*comp) (const void* element1, const void* element2))
{
	assert (num_elements >= 0);
	assert (mass);
	assert (comp);

	int left = 0;
	int	right = num_elements - 1;
	Line mid = mass[num_elements / 2];

	while (left < right)
	{
		while ( (*comp) (mass + left, &mid) < 0 && left < right) left++;
		while ( (*comp) (mass + right, &mid) > 0 && left < right) right--;

		if (left < right)
			Swap (mass + left++, mass + right--);
	}

	const int c = ( (*comp) (mass + left, &mid) < 0) ? 1 : 0;

	if (left > 1 && left < num_elements)
		QuickSort (mass, left + c, comp);
	if (right + 1 < num_elements && right > 0)
		QuickSort (mass + right + c, num_elements - right - c, comp);

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

	char* el1 = (* ( (Line*)element1)).point;
	char* el2 = (* ( (Line*)element2)).point;

	assert (el1);
	assert (el2);

	if (el1 == el2)
		return 0;

	while (true)
	{
		if (*el1 == '\0' && *el2 == '\0')
			return 0;
		if (*el1 == '\0')
			return -1;
		if (*el2 == '\0')
			return 1;

		//printf ("%s $$$ %s\n", el1, el2);

		if (IsAlphaRus (*el1) == 0)
		{
			el1++;
			continue;
		}
		if (IsAlphaRus (*el2) == 0)
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

	if (* (* ( (Line*)element1)).point == '\0') 
		return -1;
	if (* (* ( (Line*)element2)).point == '\0') 
		return +1;

	char* el1 = (* ( (Line*)element1)).point + (* ( (Line*)element1)).lenght - 2;
	char* el2 = (* ( (Line*)element2)).point + (* ( (Line*)element2)).lenght - 2;

	if (el1 == el2)
		return 0;

	while (true)
	{
		if (*el1 == '\0' && *el2 == '\0')
			return 0;
		if (*el1 == '\0')
			return -1;
		if (*el2 == '\0')
			return 1;

		//printf ("%s $$$ %s\n", el1, el2);

		if (IsAlphaRus (*el1) == 0)
		{
			el1--;
			continue;
		}
		if (IsAlphaRus (*el2) == 0)
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

int IsAlphaRus (const char c)
{
	return (c >= 'A' && c <= 'Z' ||
			c >= 'a' && c <= 'z' ||
			c >= '�' && c <= '�' ||
			c >= '�' && c <= '�' ||
			c == '�' || c == '�');
}