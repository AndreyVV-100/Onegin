struct Line;

/*!
	This function sort massive of Lines
	@param [out] mass A massive, what need to be sorted.
	@param [in] num_elements Number of elements in massive.
	@param [in] comp A pointer to function, what compare.
*/

void QuickSort (Line* mass, size_t num_elements,
	int (*comp) (const void* element1, const void* element2));

/*!
	This function swap to lines.
	@param [in] var1 First line.
	@param [in] var2 Second line.
*/

void Swap (Line* var1, Line* var2);

/*!
	This function compare to lines from head to back.
	@param [in] var1 First line.
	@param [in] var2 Second line.
*/

int CompareFront (const void* element1, const void* element2);

/*!
	This function compare to lines from back to head.
	@param [in] var1 First line.
	@param [in] var2 Second line.
*/

int CompareBack (const void* element1, const void* element2);

/*!
	This function says, is the symbol alpha.
	@param [in] c Symbol, what will be verified.
*/

int IsAlphaRus (char c);