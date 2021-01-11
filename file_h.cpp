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
		decrypt_str[i] -= (std::stoi(std::string(code[i], 1)) - 2);
	}
}

std::string file_h::encrypt(std::string encrypt_str, size_t pos)
{
	srand(time(NULL));

	std::array<std::string, 50> code = pass::get_code_arr();

	for (char& i : encrypt_str)
	{
		int randNum = rand() % 10;
		i += randNum;
		code[pos] += std::to_string(randNum + 2);
	}

	return encrypt_str;
}

void file_h::Make_File(std::fstream& service, std::fstream& pass, std::fstream& code)
{
	service.close();
	pass.close();
	code.close();

	std::cout << "Some files are missing!\n\n";
	std::cout << "Press any key to contine and Wipe and data in existing files...\n\n";
	std::cout << "The master password Will be Reset TO THE DEFAULT 'p'.\n\n\n";

	service.open("service.txt", std::ios_base::out);
	pass.open("pass.txt", std::ios_base::out);
	code.open("cd.txt", std::ios_base::out);
	
	code << file_h::encrypt("p") << '\n';
	
	service.close();
	pass.close();
	code.close();
}


void file_h::Services_Password(std::array<std::string, 50>& services, std::array<std::string, 50>& password)
{
	std::fstream fServices("services.txt", std::ios::in);

	std::fstream fpassword("pass.txt", std::ios_base::in);

	std::fstream fcode("cd.txt", std::ios_base::in);

	std::array<std::string, 50>& code = pass::get_code_arr();

	if (!fServices || !fpassword || !fcode)
	{
		file_h::Make_File(fServices, fpassword, fcode);
		return;
	}

	int i = 0;
	fpassword.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	fcode.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (std::getline(fpassword, password[i]))
	{ 
		std::getline(fcode, code[i]);
		decrypt(password[i], code[i]);
		i++; 
	}

	fpassword.close();
	fcode.close();

	i = 0;
	while (std::getline(fServices, services[i]))
	{ 
		decrypt(services[i], code[i]);
		i++;
	}
	fServices.close();
}


void file_h::get_password(std::string& master_password)
{
	std::ifstream fPassword("pass.txt");
	fPassword >> master_password;
}