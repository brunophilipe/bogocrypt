//
// Created by Bruno Philipe on 7/1/15.
//

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bogocrypt.h"

#define RANDFUNC arc4random

long bogocryptsize(long pInputLength, int pKeyLength)
{
	return pKeyLength * pInputLength;
}

long bogodecryptsize(long pInputLength, int pKeyLength)
{
	return (long)(fmaxf(pKeyLength, pInputLength) / fminf(pKeyLength, pInputLength));
}

int bogocrypt(const char *pInput, long pInputLength, const char *pKey, int pKeyLength, char **pOutput)
{
	int lPosition = 0;

	for (int lInputIndex = 0; lInputIndex < pInputLength; ++lInputIndex)
	{
		lPosition = (unsigned int)(pKey[(lInputIndex + lPosition) % pKeyLength] + (lInputIndex >= pKeyLength ? pInput[lInputIndex-pKeyLength] : 0)) % pKeyLength;
		for (int lKeyIndex = 0; lKeyIndex < pKeyLength; ++lKeyIndex)
		{
			if (lKeyIndex == lPosition)
			{
				char lCypher = pKey[lKeyIndex] ^ pInput[lInputIndex];
				(*pOutput)[lKeyIndex + lInputIndex * pKeyLength] = lCypher;
			}
			else
			{
				(*pOutput)[lKeyIndex + lInputIndex * pKeyLength] = (char)(RANDFUNC() % INT8_MAX);
			}
		}
	}

	memset(&lPosition, '0', sizeof(lPosition));

	return 1;
}

int bogodecrypt(const char *pInput, long pInputLength, const char *pKey, int pKeyLength, char **pOutput)
{
	long lOutputLength = bogodecryptsize(pInputLength, pKeyLength);
	int lPosition = 0;

	for (int lOutputIndex = 0; lOutputIndex < lOutputLength; ++lOutputIndex)
	{
		lPosition = (unsigned int)(pKey[(lOutputIndex + lPosition) % pKeyLength] + (lOutputIndex >= pKeyLength ? (*pOutput)[lOutputIndex-pKeyLength] : 0)) % pKeyLength;
		char lCypher = pInput[lOutputIndex * pKeyLength + lPosition];
		(*pOutput)[lOutputIndex] = pKey[lPosition] ^ lCypher;
	}

	memset(&lPosition, '0', sizeof(lPosition));
	memset(&lOutputLength, '0', sizeof(lOutputLength));

	return 1;
}