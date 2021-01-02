#include "dep.h"
#include <fstream>
#include <conio.h>
#include <limits>
void file_h::Services_Password(std::array<std::string, 50>& services, std::array<std::string, 50>& password)
{
	std::fstream fServices;

	fServices.open("services.txt", std::ios::in);
	std::ifstream fpassword("pass.txt");

	if (!fServices)
	{
		fServices.open("services.txt", std::ios::out);
		fServices.close();
		fpassword.close();
		std::cout << "No services stored please add services.\nUse the settings menu to add services.\n\n\n\
Press any key to continue and it will also wipe data stored in pass.txt...";
		_getch();
		fpassword.open("pass.txt", std::ios::out);
		fpassword.clear();
		fpassword.close();
		return;
	}
	
	int i = 0;
	while (std::getline(fServices, services[i])) { i++; }

	fServices.close();
	i = 0;

	if (!fpassword)
	{
		fpassword.open("pass.txt", std::ios::out);
		fpassword.close();
		std::cout << "pass.txt not found. So add passwords using settings menu.\n\n\nPress any key to continue and it will also wipe all data stored in services.txt...";
		_getch();
		fServices.open("services.txt");
		fServices.clear();
		fServices.close();
		return;
	}
	
	fpassword.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (std::getline(fpassword, password[i])) { i++; }

	fpassword.close();
}


void file_h::get_password(std::string& master_password)
{
	std::ifstream fPassword("pass.txt");
	fPassword >> master_password;
}