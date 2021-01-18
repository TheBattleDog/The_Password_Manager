#include "dep.h"
#include <fstream>
#include <conio.h>
#include <string>
#include <limits>
#include <random>
#include <ctime>

void file_h::decrypt(std::string& decrypt_str, std::string& code)
{
	for (int i = 0; i < decrypt_str.size(); i++)
	{
		decrypt_str[i] -= (code[i] - '0') - 2;
	}
}

std::string file_h::encrypt(std::string encrypt_str, std::string& encrypted_code)
{
	srand(time(NULL));
	encrypted_code.clear();
	for (char& i : encrypt_str)
	{
		int randNum = rand() % 8;
		i += randNum;
		encrypted_code += std::to_string(randNum + 2);
	}

	return encrypt_str;
}

void file_h::Make_File(std::fstream& service, std::fstream& pass, std::fstream& code)
{
	service.close();
	pass.close();
	code.close();

	std::cout << "Some files are missing!\n\n";
	std::cout << "Press any key to continue and by continuing all the data in existing files will be Wiped...\n\n";
	std::cout << "The master password Will be Reset TO THE DEFAULT 'p'.\n\n\n";

	_getch();
	system("cls");

	service.open("services.txt", std::ios_base::out);
	pass.open("pass.txt", std::ios_base::out);
	code.open("cd.txt", std::ios_base::out);
	
	pass << file_h::encrypt("p", pass::get_pass_code_arr()[0]) << '\n';
	code << pass::get_pass_code_arr()[0] << '\n';
	
	service.close();
	pass.close();
	code.close();
}


void file_h::Services_Password(std::array<std::string, 50>& services, std::array<std::string, 50>& password)
{
	std::fstream fServices("services.txt", std::ios::in);

	std::fstream fpassword("pass.txt", std::ios_base::in);

	std::fstream fcode("cd.txt", std::ios_base::in);

	std::array<std::string, 50>& service_code = pass::get_service_code_arr();
	std::array<std::string, 50>& pass_code = pass::get_pass_code_arr();

	if (!fServices || !fpassword || !fcode)
	{
		file_h::Make_File(fServices, fpassword, fcode);
		file_h::get_password(password[0]);
		pass::Master_Password(password[0]);
		return;
	}

	int i = 0;
	
	fcode.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (std::getline(fServices, services[i]))
	{
		std::getline(fcode, service_code[i]);
		decrypt(services[i], service_code[i]);
		i++;
	}
	
	fServices.close();
	
	i = 0;

	fpassword.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (std::getline(fpassword, password[i]))
	{ 
		std::getline(fcode, pass_code[i]);
		decrypt(password[i], pass_code[i]);
		i++; 
	}
	fpassword.close();
	fcode.close();
}


void file_h::get_password(std::string& master_password)
{
	std::fstream fpassword("pass.txt", std::ios_base::in);
	std::fstream fcode("cd.txt", std::ios_base::in);

	if (!fpassword || !fcode)
	{
		return;
	}

	std::string sCode;

	fcode >> sCode;
	fpassword >> master_password;

	decrypt(master_password, sCode);

	fcode.close();
	fpassword.close();
}

void file_h::app_service_code(std::string& new_code)
{
	std::fstream fCode("cd.txt", std::ios_base::in);
	std::array<std::string, 50>& service_code = pass::get_service_code_arr();
	std::array<std::string, 50>& pass_code = pass::get_pass_code_arr();
	
	std::string master_code;

	fCode >> master_code;

	fCode.close();

	fCode.open("cd.txt", std::ios_base::out | std::ios_base::trunc);
	fCode << master_code << '\n';
	
	int size = pass::get_service_count();

	for (int i = 0; i < size; i++)
	{
		fCode << service_code[i] <<'\n';
	}

	fCode << new_code << '\n';

	for (int i = 0; i < size; i++)
	{
		fCode << pass_code[i] << '\n';
	}
}