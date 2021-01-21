#include "dep.h"
#include <conio.h>
#include <fstream>


enum DIR { UP_ARROW = 296, DOWN_ARROW = 304, ENTER_KEY = 13, ARROW_KEY = 224 };


namespace setting
{
	void add_service(std::string& master_password)
	{
		std::string service, password, pass_confimation,code, pass_code;

		const char* Pass_Prompt_Message = "\nEnter the Password for the service >> ";
		const char* ReEnter_Prompt_Message = "\nRe-enter the password >> ";

		std::cout << "\n\n\nEnter the name of the Service to be added >> ";
		std::cin >> service;

		while(true)
		{
			std::cout << Pass_Prompt_Message;
			pass::getpass(password, Pass_Prompt_Message);
			std::cout << ReEnter_Prompt_Message;
			pass::getpass(pass_confimation, Pass_Prompt_Message);
			if (password != pass_confimation) 
			{
				std::cout << "\nPasswords did match try re-entering...\n";
				system("pause");
				system("cls");
				std::cout << "\n\n\nEnter the name of the Service to be added >> " << service;
			}
			else { break; }
		}

		// Add encryption to all options in settings... SURE MAN
		std::ofstream fServices("services.txt", std::ios_base::app);

		std::ofstream fPassword("pass.txt", std::ios_base::app);

		std::ofstream fCode("cd.txt", std::ios_base::app);
		
		if (!fServices || !fPassword || !fCode)
		{
			std::cout << "Unable open dependencies...\n";
			std::cout << "Press any key to continue...";
			_getch();
		}
		else
		{
			service = file_h::encrypt(service, code); // Encrypts the Service name
			file_h::app_service_code(code); // Adds the service code to file
			fServices << service << '\n'; // Appends service name to file
			
			password = file_h::encrypt(password, pass_code); // Encrypts the password
			fPassword << password << '\n'; // Appends password to the file
			fCode << pass_code << '\n'; // Appends the password code to the file

			fServices.close();
			fPassword.close();
			fCode.close();
			std::cout << "\n\n\n\nNew Service added successfully!!\n\n\nPress any key to return...";
			_getch();
		}
		pass::Interface(master_password);
	}


	void del_service(std::array<std::string, 50>& services, std::array<std::string, 50>& passwords, std::string& master_password)
	{
		std::array<std::string, 50>& service_code = pass::get_service_code_arr();
		std::array<std::string, 50>& pass_code = pass::get_pass_code_arr();

		std::string Service_name;
		int Sel_point = 0;
		int pos = 0;
		char got;
		const char* Prompt_Message = "\n\n\nSearch for the Service to be deleted >> ";

		do
		{
			std::cout << Prompt_Message;
			got = strf::getstr(Service_name, Sel_point, pos, true, Prompt_Message);
		} while (got != 13);
		if (Service_name.size())
		{
			const char* deleted_service = services[pos].c_str();

			for (int i = pos; isalpha(services[i][0]); i++)
			{
				services[i] = services[i + 1];
				passwords[i] = passwords[i + 1];
				service_code[i] = service_code[i + 1];
				pass_code[i] = pass_code[i + 1];
			}
			
			std::string Master_Code;

			std::ofstream fServices("services.txt", std::ios::trunc);
			std::ofstream fPasswords("pass.txt", std::ios::trunc);
			std::ofstream fCode("cd.txt", std::ios::trunc);

			int service_count = pass::get_service_count();

			fPasswords << file_h::encrypt(master_password, Master_Code) << '\n';
			fCode << Master_Code << '\n';

			for (int i = 0; i < service_count; i++)
			{
				fServices << file_h::encrypt(services[i], service_code[i]) << '\n';
				fPasswords << file_h::encrypt(passwords[i], pass_code[i]) << '\n';
				fCode << service_code[i] << '\n';
			}
			for (int i = 0; i < service_count; i++)
			{
				fCode << pass_code[i] << '\n';
			}
			fServices.close();
			fPasswords.close();
			fCode.close();
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
		std::array<std::string, 50>& Services_code = pass::get_service_code_arr();
		std::array<std::string, 50>& pass_code = pass::get_pass_code_arr();
		std::string confirmation, master_code;
		const char* Prompt_Message = "\nEnter the new master password >> ";
		const char* ReEnter_Prompt_Message = "\nRe-enter the password >> ";

		while(true)
		{
			system("cls");
			
			std::cout << Prompt_Message;
			pass::getpass(master_password, Prompt_Message);

			std::cout << ReEnter_Prompt_Message;
			pass::getpass(confirmation, ReEnter_Prompt_Message);

			if (master_password != confirmation)
			{
				std::cout << "\nPasswords did not match...\n\n\nPress any key to re-enter Password.";
				_getch();
			}
			else { break; }
		}

		std::ofstream fPassword("pass.txt", std::ios::trunc);
		std::ofstream fCode("cd.txt", std::ios::trunc);

		fPassword << file_h::encrypt(master_password, master_code) << '\n';
		
		for (int i = 0; i < size; i++)
		{
			fPassword << file_h::encrypt(service_passwords[i], pass_code[i]) << '\n';
		}

		fCode << master_code << '\n';

		for (int i = 0; i < size; i++)
		{
			fCode << Services_code[i] << '\n';
		}

		for (int i = 0; i < size; i++)
		{
			fCode << pass_code[i] << '\n';
		}

		fPassword.close();

		std::cout << "\nMaster Password changed successfully!\n\n\nPress any key to coninue...";

		_getch();
		system("cls");
		pass::Master_Password(master_password);
		pass::Interface(master_password);
	}

	void change_service_password(std::string& master_password, std::array<std::string, 50>& Passwords, std::array<std::string, 50>& Pass_code)
	{

		std::string service_name;
		std::string password;
		std::string confirmation;
		const char* Prompt_Meassage = "\nEnter the Name of service to chage its Password >> ";
		int Sel_Point = 0, pos = 0;
		char got;
		std::array<std::string, 50>& service_code = pass::get_service_code_arr();
		std::array<std::string, 50>& service = pass::get_service_arr();

		do
		{
			std::cout << Prompt_Meassage;
			got = strf::getstr(service_name, Sel_Point, pos, true, Prompt_Meassage);
		} while (got != 13);

		while (true)
		{
			std::cout << "\n\nEnter the new Password >> ";
			pass::getpass(password, "\n\nEnter the new password >> ");
			std::cout << "\n\nRe-enter the Password >> ";
			pass::getpass(confirmation, "\n\nRe-enter the Password >> ");

			if (password != confirmation)
			{
				std::cout << "\n\n\nPasswords did not match...\n\n\n\n";
				std::cout << "Pess any key to try again...";
				_getch();
			}
			else
			{
				Passwords[pos] = password;
				break;
			}
		}

		std::string sCode;
		file_h::get_master_password(master_password);

		std::ofstream fPasswords("pass.txt", std::ios_base::trunc);
		std::ofstream fCode("cd.txt", std::ios_base::trunc);

		fPasswords << file_h::encrypt(master_password, sCode) << '\n';
		fCode << sCode << '\n';

		int service_count = pass::get_service_count();


		for (int i = 0; i < service_count; i++)
		{
			fCode << service_code[i] << '\n';
		}

		for (int i = 0; i < service_count; i++)
		{
			fPasswords << file_h::encrypt(Passwords[i], sCode) << '\n';
			fCode << sCode << '\n';
		}

		fPasswords.close();
		fCode.close();

		std::cout << '\n' << service[pos] << " password changed successfully.\n\n\n";
		std::cout << "Press any key to continue...";
		_getch();

		pass::Interface(master_password);
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
