// SHA3utilityUserCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "SHA3utility.h"


int _tmain(int argc, _TCHAR* argv[])
{
	const int digestLengthInChars = 48*2; //2 ASCII chars to rep' each byte of SHA3-384 digest
	char digest[digestLengthInChars+1];
	digest[digestLengthInChars] = 0;
	bool okay = false;
	std::string filename = "C:\\Xray\\Data\\TestSet\\Sample002.jpg";
	char* digestPtr = digest;
	okay = getFileSha3(filename.c_str(), digestPtr, digestLengthInChars);
	if (!okay)
		std::cout << "ERROR! Problems getting hash..." << std::endl;
	else
		std::cout << "Sample002.jpg SHA3 hash is ...\n" << digest << std::endl;


	filename = "C:\\Xray\\Data\\TestSet\\Sample002-Thumbxray.jpg";
	okay = getFileSha3(filename.c_str(), digestPtr, digestLengthInChars);
	if (!okay)
		std::cout << "ERROR! Problems getting hash..." << std::endl;
	else
		std::cout << "Sample002-Thumbxray.jpg SHA3 hash is ...\n" << digest << std::endl;


	filename = "C:\\Xray\\Data\\TestSet\\Sample002.jpg";
	okay = getFileSha3(filename.c_str(), digestPtr, digestLengthInChars);
	if (!okay)
		std::cout << "ERROR! Problems getting hash..." << std::endl;
	else
		std::cout << "Sample002.jpg SHA3 hash is ...\n" << digest << std::endl;

	std::cin.get();

	return 0;
}

