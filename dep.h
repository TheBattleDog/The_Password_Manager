#pragma once
#include <iostream>
#include <array>
#include <string>

char isSelected(int& sel_point, const int& curr_pos, const int& size);

namespace pass
{
	void Master_Password(std::string& master_password);
	int search(const std::string& str, int& sel_point, int& total, const char* display_text);
	void Interface(std::string& master_password);
	void getpass(std::string& str);
	void search_nav(const int& got, int& sel_point);
	void print_pass(const int& pos);
	int get_service_count(std::array<std::string, 50>& services);
}

namespace setting
{
	void add_service(std::string& master_password);
	void change_master_password(std::string& master_password, std::array<std::string, 50>& service_passwords, int size);
	void del_service(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords, std::string& master_password);
	void change_service_password(std::string& master_password);
	int Interface();
}

namespace strf
{
	void str_tolower(std::string& str);
	int getstr(std::string& str, int& sel_point, int& selected, bool settings = false);
	int finder(const char* str, const char* search_for, int start_from = 0);
}

namespace file_h
{
	void Services_Password(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords);
	void get_password(std::string& master_password);
}