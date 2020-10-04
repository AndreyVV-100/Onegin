#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//#include <search.h>

/*!
	The struct contains a pointer to string and buffer and length
of this string ('including '\0').
*/

struct Line
{
	char* point = nullptr;
	size_t lenght = 0;
};

/*!
@mainpage
\authors <a href = "https://vk.com/andreyid1"> Andrey Vyazovtsev </a>
\version Version 1.2, release
\date 18 September 2020
\warning Bad translate!
\todo More unit tests!!!
\copyright Absolutly free, 2020
*/