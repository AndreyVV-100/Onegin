struct Line;

int DoLines (char* text, Line* lines, int num_lines);

void QuickSort (Line* mass, size_t num_elements,
	int (*comp) (const void* element1, const void* element2));

void Swap (Line* var1, Line* var2);

int CompareFront (const void* element1, const void* element2);

int CompareBack (const void* element1, const void* element2);

int IsAlphaRus (char c);