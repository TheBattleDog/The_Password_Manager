#include "dep.h"

#include <conio.h>
enum DIR { UP_ARROW = 296, DOWN_ARROW = 304, ENTER_KEY = 13, ARROW_KEY = 224 };
std::array<std::string, 50> services, service_passwords, code;

std::array<std::string, 50>& pass::get_code_arr()
{
	return code;
}

char isSelected(int& sel_point, const int& curr_pos, const int& size)
{
	if (sel_point >= size) { sel_point = 0; }
	if (sel_point < 0) { sel_point = size - 1; }
	if (sel_point == curr_pos) { return '|'; }
	return '\r';
}

int pass::get_service_count(std::array<std::string, 50>& services)
{
	int i;
	for (i = 0; isalpha(services[i][0]); i++);
	return i;
}

void pass::getpass(std::string& str)
{
	char got;
	str.clear();
	while (true)
	{
		got = _getch();
		if (got == '\b')
		{
			system("cls");
			std::cout << "Enter the Master Password >> ";
			str.clear();
		}
		else if (got == 13) // 13 is the value of Enter Key
			break;
		else
			_putch('*');

		str += got;
	}
}

void pass::Master_Password(std::string& master_password)
{
	std::string user_input;
	std::cout << "Enter the Master Password >> ";
	pass::getpass(user_input);

	while (user_input != master_password)
	{
		std::cout << "\nYou Sus! The password entered was wrong -_-\n";
		std::cout << "Try Re-Entering the password >> ";
		pass::getpass(user_input);
		system("cls");
	}
}

bool NotPrinted(const int& curr_pos, const std::array<int, 50> const Printed, const int& count);
bool precision_search(const char* str, const char* look_for)
{
	for (int i = 0; i < strlen(look_for); i++)
		if (str[i] != look_for[i])
			return false;
	return true;
}

template<size_t size>
int get_count(std::array<std::string, size> arr)
{
	int i;
	for (i = 0; isalpha(arr[i][0]); i++);

	return i;
}

int pass::search(const std::string& search_for, int& sel_point, int& total, const char* display_text)
{
	system("cls");
	std::cout << display_text << search_for;


	size_t search_range = search_for.size();
	int count = 0;
	int selected = -1;
	std::string sub_search_for;
	for (int i = 0; services[i].size() > 0; i++) // This algorithm is more precise search. Character must in order for this algo to display it.
	{
		std::string temp = services[i];
		strf::str_tolower(temp);
		int pos = temp.find(sub_search_for);
		if (pos != -1 && precision_search(temp.c_str(), search_for.c_str()))
		{
			char sel = isSelected(sel_point, count, total);
			count++;
			std::cout << '\n' << sel << count << ". " << services[i] << sel;
			if (sel == '|')
				selected = i;
		}
	}
	total = count == 0 ? total : count;
	if(count == 0) // But if no result is found from previous algo then this one displays an array element if a letter is found at any order.
		while (search_range)
		{
			sub_search_for = search_for.substr(0, search_range);
			for (int i = 0; services[i].size() > 0; i++)
			{
				std::string temp = services[i];
				strf::str_tolower(temp);
				int pos = temp.find(sub_search_for);
				if (pos != -1)
				{
					char sel = isSelected(sel_point, count, total);
					count++;
					std::cout << '\n' << sel << count << ". " << services[i] << sel;
					if (sel == '|')
						selected = i; 
				}
			}
			total = count;
			search_range--;
		}
	return selected;
}


void pass::search_nav(const int& got, int& sel_point)
{
	if (got == UP_ARROW)
		sel_point--;
	else if (got == DOWN_ARROW)
		sel_point++;
}

void pass::print_pass(const int& pos)
{
	system("cls");
	char yn;
	do
	{
		std::cout << "Are you sure that no one is watching you? (Y/N)";
		std::cin >> yn;
	} while (yn == 'n' || yn == 'N');

	std::cout << "\n\n\n\nPassword for " << services[pos] << " = "<< service_passwords[pos];
	std::cout << "\n\n\n\n\n\nPress any key to exit...";
	_getch();
}
void pass::Interface(std::string& master_password)
{
	std::string Service_name;
	int Sel_item = 0;
	int Selected = 0;
	bool settings = false;
	file_h::Services_Password(services, service_passwords);

	while(true)
	{
		system("cls");
		std::cout << "Enter the name of service inorder to retrive its password!\t\t  Press Ctrl+s to go to settings.\n";
		std::cout << "\nSearch Bar >> ";
		int got = strf::getstr(Service_name, Sel_item, Selected);
		if (got == '\b')
			continue;
		else if (got == 13) // Enter Key = 13
			break;
		else if (got == 19) // Ctrl + s = 19
		{
			Sel_item = setting::Interface();
			if (Sel_item == 5) { continue; }
			settings = true;
			break;
		}
	}
	
	if (settings)
	{
		if (Sel_item == 1) { setting::add_service(master_password); }
		if (Sel_item == 2) { setting::del_service(services, service_passwords, master_password); }
		if (Sel_item == 3) { setting::change_master_password(master_password, service_passwords, pass::get_service_count(services)); }
		if (Sel_item == 4) { setting::change_service_password(master_password); }
	}
	else
	{
		pass::print_pass(Selected);
	}

}

bool NotPrinted(const int& curr_pos, const std::array<int, 50> const Printed, const int& count)
{
	for (int i = 0; i <= count; i++)
	{
		if (Printed[i] == curr_pos)
			return false;
	}
	return true;
}