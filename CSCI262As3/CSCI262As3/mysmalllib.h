/* * * * * * * * * * * * * * * * * * * *
*	Name		: Pang Jin Xiong Joel  *
*	Student ID	: 4643409              *
* * * * * * * * * * * * * * * * * * * */
#ifndef _MYSMALLLIB_H
#define _MYSMALLLIB_H
#include "stdafx.h"

namespace mylib
{
	const std::string validCharacters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789_@.-";
	bool writeFile(std::string filename, std::string text, std::ios_base::openmode type);
	bool writeFile(std::string filename, std::string text);
	std::string readFileLine(std::string filename);
	void readFile(std::string filename, std::vector<std::string> &text);
	int Hash(std::string text);
	void delimString(std::string text, char delim, std::vector<std::string> &ret);
	std::string getpass(const char *prompt, bool show_asterisk);
	std::string tolower(std::string);
}
#endif