#include "dep.h"
#include <conio.h>
#include <fstream>


enum DIR { UP_ARROW = 296, DOWN_ARROW = 304, ENTER_KEY = 13, ARROW_KEY = 224 };


namespace setting
{
	void add_service(std::string& master_password)
	{
		std::string service, password;
		std::cout << "\n\n\nEnter the name of the Service to be added >> ";
		std::cin >> service;
		std::cout << "Enter the Password for the sevice >> ";
		std::cin >> password;

		std::ofstream fServices;
		fServices.open("services.txt", std::ios_base::app);
		fServices << service + '\n';
		std::ofstream fPassword;
		fPassword.open("pass.txt", std::ios_base::app);
		fPassword << password + '\n';
		
		if (!fServices || !fPassword)
		{
			std::cout << "Unable open Services.txt or Pass.txt\n";
			std::cout << "Press any key to continue...";
			_getch();
		}
		else
		{
			fServices.close();
			fPassword.close();
			std::cout << "\n\n\n\nNew Service added successfully!!\n\n\nPress any key to return..."; // here is where you left and add a cosnt char* print message into the search function
			_getch();
		}
		pass::Interface(master_password);
	}


	void del_service(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords, std::string& master_password)
	{
		std::string Service_name;
		int Sel_point = 0; 
		int pos = 0;
		char got;
		do
		{
			std::cout << "\n\n\nSearch for the Service to be deleted >> ";
			got = strf::getstr(Service_name, Sel_point, pos, true);
		} while (got != 13);
		if (Service_name.size())
		{
			const std::string deleted_service = services[pos];

			for (int i = pos; isalpha(services[i][0]); i++)
			{
				services[i] = services[i + 1];
				passwords[i] = passwords[i + 1];
			}

			std::ofstream fServices("services.txt", std::ios::trunc);
			std::ofstream fPasswords("pass.txt", std::ios::trunc);
			for (int i = 0; isalpha(services[i][0]); i++)
			{
				fServices << services[i] << '\n';
				fPasswords << passwords[i] << '\n';
			}
			fServices.close();
			fPasswords.close();
			std::cout << "\n\n\n\n" << deleted_service << " is successfully deleted";
			std::cout << "\n\n\n\nPress any key to continue...";
			_getch();
		}
		else
		{
			std::cout << "\n\nPress any key to go back...";
			_getch();
			pass::Interface(master_password);
		}
	}

	void change_master_password(std::string& master_password, std::array<std::string, 50>& service_passwords, int size)
	{
		std::string confirmation;
		do
		{
			system("cls");
			std::cout << "Enter the new master password >> ";
			std::cin >> master_password;

			std::cout << "Re-enter the password >> ";
			std::cin >> confirmation;

			if (master_password != confirmation)
			{
				std::cout << "Passwords did not match...\n\n\nPress any key to re-enter Password.";
				_getch();
			}

		} while (master_password != confirmation);

		std::ofstream fPassword("pass.txt", std::ios::trunc);

		fPassword << master_password << '\n';
		
		for (int i = 0; i < size; i++)
		{
			fPassword << service_passwords[i] << '\n';
		}

		fPassword.close();

		std::cout << "master_password changed successfully!\n\n\nPress any key to coninue...";

		_getch();
		system("cls");
		pass::Master_Password(master_password);
		pass::Interface(master_password);
	}

	void change_service_password(std::string& master_password)
	{
		system("cls");
		std::cout << R"(Selected Change Service Password
This feature is not yet available!!)" << '\n';
		system("pause");
	}
}

int setting::Interface()
{
	int sel_item = 0;
	int input;
	std::array<const char*, 5> items = { "1. Add New Service", "2. Del a Service",
										 "3. Change Master Password", "4. Change Service Password", "5. Go back" };
	do
	{
		system("cls");
		std::cout << "Use Up and Down arrow to Navigate\n";
		for (int i = 0; i < items.size(); i++)
		{
			char chr = isSelected(sel_item, i, items.size());
			std::cout << chr << items[i] << ' ' << chr << '\n';
		}
		input = _getch();
		if (input == ARROW_KEY) // ARROW_KEY = 224 means an arrow key is pressed
		{
			input += _getch(); // I think this picks up arrow key release. Without this all the arrow Keys return 224.
		}
		if (input == UP_ARROW) { sel_item--; }
		else if (input == DOWN_ARROW) { sel_item++; }

	} while (input != ENTER_KEY);

	return sel_item + 1;
}