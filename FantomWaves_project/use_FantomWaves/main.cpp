#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <FantomWaves.h>
//#include "../../FantomWaves/FantomWaves.h"

int main()
{
	fw::Bindata data;
	data.add(std::string("test"));
	data.add(long(2525));
	data.add(float(3.1415));

	fw::Bindata data_container;
	data_container.add(std::string("data_container"));
	data_container.add(data);
	data_container.add(std::string("end"));

	std::string str_con;
	std::string str_test;
	long integer;
	float decimal;
	std::string str_end;
	data_container >> str_con >> str_test >> integer >> decimal >> str_end;

	std::cout << str_con << std::endl;
	std::cout << str_test << std::endl;
	std::cout << integer << std::endl;
	std::cout << decimal << std::endl;
	std::cout << str_end << std::endl;

	return 0;
}