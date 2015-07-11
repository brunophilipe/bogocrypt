#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bogocrypt.h"

long readBuffer(char **pBuffer)
{
	const int lStep = 256;
	int lBytesRead = 0;
	
	char lBasket = '\0';
	char *lBuffer = calloc(1, sizeof(char) * lStep);
	while (scanf("%c", &lBasket) != EOF)
	{
		if (lBasket == '\n') break;
		lBuffer[lBytesRead] = lBasket;
		lBytesRead++;
		if (lBytesRead % (lStep-1) == 0)
		{
			lBuffer = realloc(lBuffer, lBytesRead + lStep);
		}
	}
	
	*pBuffer = lBuffer;
	return lBytesRead;
}

void runInputEncryptMode(const char *pInput, long pInputLength, const char *pKey, int pKeyLength)
{
	long lCypherSize = bogocryptsize(pInputLength, (int)pKeyLength);
	char *lCypher = calloc(1, sizeof(char) * lCypherSize);
	
	bogocrypt(pInput, pInputLength, pKey, (int)pKeyLength, &lCypher);
	
	for (int i = 0; i < lCypherSize; i++)
	{
		printf("%02X", (0x000000FF & lCypher[i]));
	}
	
	printf("\n");
}

void runInputDecryptMode(const char *pInput, long pInputLength, const char *pKey, int pKeyLength)
{
	long lPlainTextSize = bogodecryptsize(pInputLength, (int)pKeyLength);
	char *lPlainText = calloc(1, sizeof(char) * lPlainTextSize);
	char *lBinaryInput = calloc(1, sizeof(char) * (pInputLength / 2));
	char lBasket[3] = {0x00, 0x00, 0x00};
	
	for (int i=0; i<(pInputLength/2); i++)
	{
		strncpy(lBasket, pInput + (i * 2), 2);
		lBinaryInput[i] = strtol(lBasket, NULL, 16);
	}
	
	bogodecrypt(lBinaryInput, pInputLength/2, pKey, (int)pKeyLength, &lPlainText);

	printf("%s\n", lPlainText);
}

void runInteractiveMode()
{
	char mode = '\0';
	char *lKey = NULL;
	char *lInputText = NULL;
	
	long lKeyLength = 0;
	long lInputTextLength = 0;
	
	printf("bogocrypt - The stupid encryption+obfuscation algorithm.\n");
	printf("Interactive mode: [e:encrypt|d:decrypt]: ");
	
	while (mode == '\0')
	{
		scanf("%c", &mode);
		getchar();
		if (mode != 'e' && mode != 'd')
		{
			printf("Interactive mode: [e:encrypt|d:decrypt]: ");
			mode = '\0';
		}
	}
	
	switch (mode)
	{
		case 'e':
			printf("Insert input (new line marks end - prefered format is base64): ");
			break;
			
		case 'd':
			printf("Insert input (new line marks end - format is HEX): ");
			break;
	}
	
	lInputTextLength = readBuffer(&lInputText);
	
	printf("Insert key (new line marks end - prefered format is byte string): ");
	lKeyLength		 = readBuffer(&lKey);
	
	if (lKeyLength > INT16_MAX)
	{
		printf("Error! Key should not be longer than %d bytes.", INT16_MAX);
	}
	else
	{
		switch (mode)
		{
			case 'e':
				runInputEncryptMode(lInputText, lInputTextLength, lKey, (int)lKeyLength);
				break;
				
			case 'd':
				runInputDecryptMode(lInputText, lInputTextLength, lKey, (int)lKeyLength);
				break;
				
			default:
				break;
		}
	}
	
	free(lKey);
	free(lInputText);
}

int main(int argc, char **argv)
{
	int success = 0;
	
	if (argc == 2)
	{
		if (strcmp(argv[1], "-i") == 0)
		{
			runInteractiveMode();
			success = 1;
		}
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-e") == 0 && strcmp(argv[3], "-k") == 0)
		{
			runInputEncryptMode(argv[2], strlen(argv[2]), argv[4], (int)strlen(argv[4]));
			success = 1;
		}
		else if (strcmp(argv[1], "-d") == 0 && strcmp(argv[3], "-k") == 0)
		{
			runInputDecryptMode(argv[2], strlen(argv[2]), argv[4], (int)strlen(argv[4]));
			success = 1;
		}
	}
	
	if (success == 0)
	{
		printf("bogocrypt - The stupid encryption+obfuscation algorithm.\n");
		printf("	Usage:		bogocrypt [command]\n");
		printf("\n");
		printf("	Commands:	-e <string> -k <key>\n");
		printf("			Encrypts string with key. Output is HEX string.\n");
		printf("			<string> is any byte string.\n");
		printf("			<key> is any byte string with length < INT16_MAX.\n");
		printf("\n");
		printf("			-d <blob> -k <key>\n");
		printf("			Decrypts string with key.\n");
		printf("			<string> is HEX string exactly as output by above command.\n");
		printf("			<key> is any byte string with length < INT16_MAX.\n");
		printf("\n");
		printf("			-i\n");
		printf("			Interactive mode.\n");
		printf("\n");
		printf("	Example:	$ bogocrypt -e \"test\" -k 1234\n");
		printf("			> 4546542307665F516B7D407B0C28475B\n");
		printf("\n");
		printf("			$ bogocrypt -d 4546542307665F516B7D407B0C28475B -k 1234\n");
		printf("			> test\n");
	}

	return 0;
}