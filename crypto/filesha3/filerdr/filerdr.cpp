// filerdr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include "jivsovsha3.h"

using namespace std;


int getFileSize( std::string filepathname )
{
	streampos begin, end;
	ifstream myfile(filepathname, ios::binary);
	begin = myfile.tellg();
	myfile.seekg(0, ios::end);
	end = myfile.tellg();
	myfile.close();
	return (int)(end - begin);
}

char toHexChar(int n)
{
	char retval = '?';
	switch (n)
	{
	case 0: retval = '0'; break;
	case 1: retval = '1'; break;
	case 2: retval = '2'; break;
	case 3: retval = '3'; break;
	case 4: retval = '4'; break;
	case 5: retval = '5'; break;
	case 6: retval = '6'; break;
	case 7: retval = '7'; break;
	case 8: retval = '8'; break;
	case 9: retval = '9'; break;
	case 10: retval = 'A'; break;
	case 11: retval = 'B'; break;
	case 12: retval = 'C'; break;
	case 13: retval = 'D'; break;
	case 14: retval = 'E'; break;
	case 15: retval = 'F'; break;
	}
	return retval;
}

void toHexStr(uint8_t in, char* putStrHere)
{
	int msn = in / 16;
	int lsn = in % 16;
	putStrHere[0] = toHexChar(msn);
	putStrHere[1] = toHexChar(lsn);
	putStrHere[2] = 0;
}

void getDigestAsHexStr( const char* digestAsBin, std::string& digestAsString )
{
	char byteAsHexString[3] = { 0, 0, 0 };
	digestAsString = "";
	//const char* i = digestAsBin;
	for (int j = 0; j < 48; j++)
	{
		char thisbyte = digestAsBin[j];
		toHexStr(thisbyte, byteAsHexString);
		digestAsString.append(byteAsHexString);
	}
}

void getFileSha3(std::string filepathname, std::string& digest, bool& okay)
{
	okay = false;
	int byteCountToProcess = getFileSize( filepathname );
	if (byteCountToProcess <= 0)
		return;

	ifstream file( filepathname, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		const int bufsize = 1024;
		char* buf = new char[bufsize];
		sha3_context context;
		jivsov_sha3_impl_Init384(&context);
		while (byteCountToProcess > 0)
		{
			int bytesToProcessThisLoop = byteCountToProcess >= bufsize ? bufsize : byteCountToProcess;
			file.read(buf, bytesToProcessThisLoop);
			jivsov_sha3_impl_Update( &context, buf, bytesToProcessThisLoop );
			byteCountToProcess -= bytesToProcessThisLoop;
		}
		file.close();
		const char* digestPtr = (const char*)jivsov_sha3_impl_Finalize( &context );
		getDigestAsHexStr(digestPtr, digest);
		delete[] buf;
		okay = true;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string filename = "Sample002.jpg";
	std::string digest = "";
	bool okay = false;
	getFileSha3(filename, digest, okay);
	if (!okay)
		std::cout << "ERROR! Problems getting hash..." << std::endl ;
	else
		std::cout << "SHA3 hash is ..." << digest.c_str() << std::endl;
	std::cin.get();


	return 0;
}
