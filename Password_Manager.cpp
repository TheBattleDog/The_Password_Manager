#include "dep.h"

int main()
{
	std::string master_password;
	file_h::get_password(master_password);
	if(master_password.size())
		pass::Master_Password(master_password);
	system("cls");
	while (strf::RUN())
	{
		pass::Interface(master_password);
		system("cls");
	}

	return 0;
}