// SHA3utility.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "sha3.h"

using namespace std;

//dirty-ish? The extern C was messing up the filestream stuff? So I did it this way
static ifstream* ifstreamPtr = 0;
static int bytesReainingToRead = 0;

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

void getDigestAsHexStr(const char* digestAsBin, std::string& digestAsString)
{
	char byteAsHexString[3] = { 0, 0, 0 };
	digestAsString = "";
	for (int j = 0; j < 48; j++)
	{
		char thisbyte = digestAsBin[j];
		toHexStr(thisbyte, byteAsHexString);
		digestAsString.append(byteAsHexString);
	}
}


void readfile(std::string filepathname, int bufsize, char* buf, int& bytesCountRead, int&bytesCountToRead, bool& okay)
{
	okay = false;
	if (!ifstreamPtr)
	{
		streampos begin, end;
		ifstreamPtr = new ifstream(filepathname, ios::binary);
		if (ifstreamPtr->is_open())
		{
			begin = ifstreamPtr->tellg();
			ifstreamPtr->seekg(0, ios::end);
			end = ifstreamPtr->tellg();
			bytesReainingToRead = (int)(end - begin);
			ifstreamPtr->seekg(0, ios::beg);
		}
		else
			return;
	}

	if (bytesReainingToRead <= 0)
		return;

	int thisReadByteCount = (bufsize > bytesReainingToRead ? bytesReainingToRead : bufsize);

	ifstreamPtr->read(buf, thisReadByteCount);

	bytesReainingToRead -= thisReadByteCount;
	bytesCountRead = thisReadByteCount;
	bytesCountToRead = bytesReainingToRead;
	okay = true;

	if (bytesReainingToRead == 0)
	{
		ifstreamPtr->close();
		delete ifstreamPtr;
		ifstreamPtr = 0;
	}
}



extern "C"
{
	//Note digest is for SHA3 384  i.e. 48*2 ASCII characters and a null terminator
	__declspec(dllexport) bool getFileSha3(const char* filepathname, char* digest, int digestMaxLen)
	{
		bool okayStatus = false;
		std::string fpn = filepathname;
		const int bufsize = 1024;
		char* buf = new char[bufsize];
		sha3_context context;
		sha3_Init384(&context);
		std::string debugString;
		int bytesCountRead;
		int bytesCountToRead;
		bool finished = false;
		do
		{
			readfile(fpn, bufsize, buf, bytesCountRead, bytesCountToRead, okayStatus);

			if (!okayStatus || bytesCountRead == 0)
				return okayStatus;

			sha3_Update(&context, buf, bytesCountRead);

			if (bytesCountToRead==0)
				finished = true;
		} while (!finished);
		const char* digestPtr = (const char*)sha3_Finalize(&context);
		std::string digestDebugStr;
		getDigestAsHexStr(digestPtr, digestDebugStr);
		memcpy(digest, digestDebugStr.c_str(), digestMaxLen);
		delete[] buf;
		okayStatus = true;
		return okayStatus;
	}
}