#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caesar.h"

/*
 * main()
 */
int main(int argc, char **argv)
{
	char str[80];
	char cryptstr[80];
	char decryptstr[80];
	char numstr[80];
	int num;

	char keystr[80];
	int key = 5;

	while (1)
	{
		printf("Test for Caesar cipher\n");
		printf("1) Encrypt message\n");
		printf("2) Decrypt message\n");
		printf("3) Encrypt and decrypt message\n");
		printf("4) Set the key (currently %d)\n", key);
		printf("9) Exit\n");
		printf(">");

		fgets(numstr, 80, stdin);
		num = atoi(numstr);
		switch (num)
		{
			case 1:
				printf("Insert the message to encrypt: ");
				fgets(str, 80, stdin);
				encryption(key, str, cryptstr, 80);
				printf("                    Encrypted: %s", cryptstr);
				break;
			case 2:
				printf("Insert the message to decrypt: ");
				fgets(str, 80, stdin);
				decryption(key, str, decryptstr, 80);
				printf("                    Decrypted: %s", decryptstr);
				break;
			case 3:
				printf("Insert the message to encrypt: ");
				fgets(str, 80, stdin);
				encryption(key, str, cryptstr, 80);
				printf("                    Encrypted: %s", cryptstr);
				decryption(key, cryptstr, decryptstr, 80);
				printf("                    Decrypted: %s", decryptstr);
				break;
			case 4:
				printf("Insert the key: ");
				fgets(keystr, 80, stdin);
				key = atoi(keystr);
				break;
		}

		if (num == 9)
			break;
	}

	return 0;
}