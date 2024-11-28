#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE_PLATE	128

/*
 * This is an implementation of the Caesar cipher using two concentric plates.
 * Encryption and decryption is done by positioning the inner plate (see 
 * rotateplate() function) and rotating it; the two plates allow encrypting 
 * or decrypting of each character (see changechar() function).
 */

const char outerplate[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz0123456789!\"$%&/()=?^'*+[]@";

/*
 * changechar() 
 * determines the position of the character c within platein and returns 
 * the character present at the same position in plateout.
 */
static char changechar(char c, const char* platein, const char* plateout)
{
	const char *pplatein  = platein;
	const char* pplateout = plateout;
	
	while (*pplatein)						// search the char
	{
		if (c == *pplatein)
			return *pplateout;				// if found, return from the other plate
		pplatein++;
		pplateout++;
	}
	
	return c;								// unencrypted character
}

/*
 * rotateplate()
 * load innerplate rotating it for 'key' positions
 */
static int rotateplate(int key, const char* outerplate, char *innerplate)
{
	int nchars;
	int i;
	int j;

	nchars = (int)strlen(outerplate);

	if (nchars >= MAXSIZE_PLATE)
		return 0;

	i = 0;
	j = key % nchars;	// in case that key>nchars
	while (i < nchars)
	{
		if (j >= nchars)
			j = 0;

		innerplate[j] = outerplate[i];

		i++;
		j++;
	}
	innerplate[nchars] = '\0';

#ifdef _DEBUG
	printf("outer plate: %s\n", outerplate);
	printf("inner plate: %s\n", innerplate);
#endif

	return 1;
}

/*
 * encryption()
 * encrypts the string 'str' using the key 'key' and loads the encrypted 
 * string in 'cryptstr'.
 * Returns 1 on success, 0 on error
 */
int encryption(int key, char *str, char *cryptstr, int maxstr)
{
	char innerplate[MAXSIZE_PLATE];
	int i;

	strcpy(cryptstr, "");

	if (strlen(str) >= maxstr)
		return 0;

	strcpy(cryptstr, str);
	
	if (!rotateplate(key, outerplate, innerplate))
		return 0;

	for (i = 0; i < (int)strlen(str); i++)
		cryptstr[i] = changechar(cryptstr[i], outerplate, innerplate);

	return 1;
}

/*
 * decryption()
 * decrypts the string 'str' using the key 'key' and loads the decrypted
 * string in 'decryptstr'.
 * Returns 1 on success, 0 on error
 */
int decryption(int key, char* str, char* decryptstr, int maxstr)
{
	char innerplate[MAXSIZE_PLATE];
	int i;

	strcpy(decryptstr, "");

	if (strlen(str) >= maxstr)
		return 0;

	strcpy(decryptstr, str);

	if( !rotateplate(key, outerplate, innerplate) )
		return 0;

	for (i = 0; i < (int)strlen(str); i++)
		decryptstr[i] = changechar(decryptstr[i], innerplate, outerplate);

	return 1;
}
