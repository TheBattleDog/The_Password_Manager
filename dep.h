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
	void getpass(std::string& str, const char* Prompt_Message);
	void search_nav(const int& got, int& sel_point);
	void print_pass(const int& pos);
	int get_service_count();
	std::array<std::string, 50>& get_pass_code_arr();
	std::array<std::string, 50>& get_service_code_arr();
	std::array<std::string, 50>& get_service_arr();
}

namespace setting
{
	void add_service(std::string& master_password);
	void change_master_password(std::string& master_password, std::array<std::string, 50>& service_passwords, int size);
	void del_service(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords, std::string& master_password);
	void change_service_password(std::string& master_password, std::array<std::string, 50>& Passwords, std::array<std::string, 50>& Pass_code);
	int Interface();
}

namespace strf
{
	void str_tolower(std::string& str);
	int getstr(std::string& str, int& sel_point, int& pos, bool settings = false, const char* Prompt_Message = "Search Bar >> ");
	int finder(const char* str, const char* search_for, int start_from = 0);
	bool RUN();
}

namespace file_h
{
	void Services_Password(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords);
	std::string get_master_password(std::string& master_password);
	void Make_File(std::fstream& service, std::fstream& pass, std::fstream& code);
	std::string encrypt(std::string encrypt_str, std::string& encrypted_code);
	void decrypt(std::string& decrypt_str, std::string& code);
	void app_service_code(std::string& code);
}