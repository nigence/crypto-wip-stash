#ifndef SHA3UTILITY_H
#define SHA3UTILITY_H

#include <string>
extern "C"
{
	bool getFileSha3(const char* filepathname, char* digest, int digestMaxLen);

}
#endif