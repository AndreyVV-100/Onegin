#pragma once
#pragma warning(disable : 6387)
//"file_out" может быть равен "0":  это не соответствует спецификации функции "fclose".
#pragma warning(disable : 4996)
//'fopen': This function or variable may be unsafe.Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.

#include <stdio.h>

struct Line;

/*!
	This function are reading txt file.
	@param [out] text Place, when point to text will be saved.
	@param [in] file_name Name of file, when text will be reading.
*/

void ReadTxt (char** text, const char* file_name);

/*!
	This function count size of file.
	@param [in] file Checking file.
*/

int CountSize(FILE* file);

/*!
	Count, how many symbols are in this text
	@param [in] text Text, when symbols need to be countable.
	@param [in] str Symbols, what was countable.
	@return Return number of symbols.
*/

int CountSymbols (char* text, const char str);

/*!
	Print the text to file to the txt.
	@param [in] lines The text.
	@param [in] num_lines Number of lines.
	@param [in] file_name Name of file, when the text will be printed.
*/

void PrintTxt (Line* lines, int num_lines, const char* file_name);

/*!
	This function print original great text!
	@param [in] text Great text!
	@param [in] num_lines Number of lines.
*/

void PrintOriginal (char* text, size_t num_lines);