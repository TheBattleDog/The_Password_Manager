#include "dep.h"
#include <conio.h>
#include <cctype>
#include <cstring>

bool run = true;

bool strf::RUN()
{
	return run;
}

void strf::str_tolower(std::string& str)
{
	for (char& i : str)
		i = tolower(i);
}

int strf::getstr(std::string& str, int& Sel_point, int& selected, bool settings, const char* Prompt_Message)
{
	int got;
	str.clear();
	bool nav = false;
	int total = 0;
	while (true)
	{
		got = _getch();
		if (got == '\b')
		{
			system("cls");
			str.clear();
			return got;
		}
		else if (got == 13) // 13 is Enter Key
		{
			return char(13);
		}
		else if (got == 19) // Ctrl + s = 19
		{
			return got;
		}
		else if (got == 224)
		{
			got += _getch();
			pass::search_nav(got, Sel_point);
			nav = true;
		}
		else if (got == 17) // Ctlr + q = 17
		{
			run = false;
			return 0;
		}
		else
		{
			nav = false;
			_putch(got);
		}

		if (!nav)
			str += tolower(got);
		if (settings)
		{
			selected = pass::search(str, Sel_point, total, Prompt_Message);
		}
		else
		{
			selected = pass::search(str, Sel_point, total, "Search Bar >> ");
		}
	}
} 


int strf::finder(const char* str, const char* search_for, int start_from)
{
	int pos;
	if (strlen(search_for) == 1)
		for (int i = start_from; i < strlen(str); i++)
		{
			if (str[i] == search_for[0])
				return i;
		}
	else
		for (int i = start_from; i < strlen(str); i++)
		{
			bool found = true;
			int temp = i;
			for (int j = 0; j < strlen(search_for); j++)
			{

				if (str[i] != search_for[j])
				{
					found = false;
					break;
				}
				else
				{
					i++;
				}

			}
			if (found)
			{
				return temp;
			}
			i = temp;
		}

	return -1;
}