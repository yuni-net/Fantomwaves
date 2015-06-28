#include <stdio.h>
#include <stdlib.h>
#include <FantomWaves.h>
//#include "../../FantomWaves/FantomWaves.h"

int main()
{
	fw::uint size = fw::filesize("test.txt");
	int integer = 2525;
	std::string stdstring = "テストだよー!";
	fw::vector<std::string> fwvector;
	fwvector.add(std::string("No.01")).add(std::string("No.02")).add(std::string("日本語もおｋ？"));
	fw::Binfile("test.dat").clear() << integer << stdstring << fwvector;

	int gotint = 0;
	std::string gotstr;
	fw::vector<std::string> gotvec;
	fw::Binfile bf("test.dat");
	bf >> gotint;
	bf >> gotstr;
	bf >> gotvec;

	printf("gotint:%d\n", gotint);
	printf("gotstr:%s\n", gotstr.c_str());
	for (unsigned int cnt = 0; cnt < gotvec.size(); ++cnt)
	{
		const std::string & str = gotvec[cnt];
		printf("gotvec[%d]:%s\n", cnt, str.c_str());
	}

	printf("\n\nfinished\n\n");

	return 0;
}