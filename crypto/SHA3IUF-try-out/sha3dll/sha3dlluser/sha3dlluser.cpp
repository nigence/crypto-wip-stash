// sha3dlluser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern "C" {
#include "jivsovsha3.h"
}
#include <iostream>
#include <iomanip>
#include <assert.h>

void FIPS202ExampleTest()
{
	sha3_context c;
	uint8_t *hash;
	uint8_t inputTextBuffer[200];
	for (int i = 0; i < 200; i++)
	{
		inputTextBuffer[i] = 0xA3;
	}

	jivsov_sha3_impl_Init384(&c);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 100);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 50);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 25);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 12);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 7);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 3);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 2);
	jivsov_sha3_impl_Update(&c, inputTextBuffer, 1);
	hash = (uint8_t*)jivsov_sha3_impl_Finalize(&c);

	const static uint8_t expected_sha3_384_of_0xa3_200_times[384 / 8] = {
		0x18, 0x81, 0xde, 0x2c, 0xa7, 0xe4, 0x1e, 0xf9,
		0x5d, 0xc4, 0x73, 0x2b, 0x8f, 0x5f, 0x00, 0x2b,
		0x18, 0x9c, 0xc1, 0xe4, 0x2b, 0x74, 0x16, 0x8e,
		0xd1, 0x73, 0x26, 0x49, 0xce, 0x1d, 0xbc, 0xdd,
		0x76, 0x19, 0x7a, 0x31, 0xfd, 0x55, 0xee, 0x98,
		0x9f, 0x2d, 0x70, 0x50, 0xdd, 0x47, 0x3e, 0x8f
	};

	if (memcmp(expected_sha3_384_of_0xa3_200_times, hash,
		sizeof(expected_sha3_384_of_0xa3_200_times)) == 0)
		printf(" FIPS 202 example test passed\n");
	else
		printf(" ERROR - FIPS 202 example test problem\n");
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

void SpeedTest(int megabytes)
{
	sha3_context c;
	uint8_t *hash;
	const int maxBufSize = 256 * 1024;
	const int bufSize = megabytes * 1024;
	assert(megabytes <= 256);
	uint8_t inputTextBuffer[maxBufSize];
	for (int i = 0; i < sizeof(inputTextBuffer); i++)
	{
		inputTextBuffer[i] = 0x55;
	}

	jivsov_sha3_impl_Init384(&c);
	printf(" Speed test - hashing BIG buffer... \n");
	for (int j = 0; j < 1024; j++)
	{
		//if (j == 371) inputTextBuffer[6793] = 0x57; // changes 
		//if (j == 372) inputTextBuffer[6793] = 0x55; // just one bit

		jivsov_sha3_impl_Update(&c, inputTextBuffer, sizeof(inputTextBuffer));
	}

	hash = (uint8_t*)jivsov_sha3_impl_Finalize(&c);

	char hex[3];
	for (int k = 0; k < 48; ++k)
	{
		//std::cout << std::hex << std::setfill('0') << std::setw(2) << hash[k] << " ";
		//if ( k % 16 == 15 )
		//	std::cout << std::endl;
		toHexStr(hash[k], hex);
		printf(hex); printf(" ");
		if (k % 16 == 15)
			printf("\n");
	}
	std::cout << std::endl;
	printf(" done. \n");
};



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Try out of Andrey Jivsov implementation of SHA3-384...\n";

	// Try the reference test given in the NIST documentation
	// (there is only 1 given where the number of bits is divisible by 8).
	FIPS202ExampleTest();

	// Speed test - how long does it take to hash a typical image file?
	SpeedTest(256); //256 megabytes

	getchar();
	return 0;
}