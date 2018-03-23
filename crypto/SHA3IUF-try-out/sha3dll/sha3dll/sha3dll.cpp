// sha3dll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

extern "C"
{
#include "sha3.h"

	__declspec(dllexport) void jivsov_sha3_impl_Init384(void *priv)
	{
		sha3_Init384(priv);
	}

	__declspec(dllexport) void jivsov_sha3_impl_Update(void *priv, void const *bufIn, size_t len)
	{
		sha3_Update(priv, bufIn, len);
	}

	__declspec(dllexport) void const * jivsov_sha3_impl_Finalize(void *priv)
	{
		return sha3_Finalize(priv);
	}

}//End 'extern "C"' to prevent name mangling
