#pragma warning(disable : 6387)
//"file_out" может быть равен "0":  это не соответствует спецификации функции "fclose".
#pragma warning(disable : 4996)
//'fopen': This function or variable may be unsafe.Consider using fopen_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.

struct Line;

void ReadTxt (char** text, const char* file_name);

int CountSymbols (char* text, const char str);

void PrintTxt (Line* lines, int num_lines, const char* file_name);