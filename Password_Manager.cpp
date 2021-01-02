#include "dep.h"

int main()
{
	std::string master_password;
	file_h::get_password(master_password);
	pass::Master_Password(master_password);
	system("cls");
	pass::Interface(master_password);

	return 0;
}