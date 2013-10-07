//#define CAVE_SOURCE_FILE // From cave.c
#include "cavei.h" // From cave.c
/* A_Key_Verify has the same header as CAVE (see Exhibit  2 -4) */

/* A_KEY_DIGITS contains the ASCII digits in the order entered */

int A_Key_Verify(const char A_KEY_DIGITS[26])
{
	int i;
	unsigned char temp_A_key[8];
	unsigned long entered_checksum;

	/* convert first 20 digits to 64-bit representation in temp_A_key */
	
	for (i = 0; i < 8; i++)
		temp_A_key[i] = 0;
	
	for (i = 0; i < 20; i++)
	{
		mul10(temp_A_key,(unsigned int)(A_KEY_DIGITS[i] - '0'));
	}
	
	/* convert last 6 digits to entered checksum */
	
	entered_checksum = 0;
	for (i = 20; i < 26; i++)
	{
		entered_checksum = (entered_checksum * 10) 
			+ (A_KEY_DIGITS[i] - '0');
	}
	
	if(Calc_Checksum(temp_A_key) == entered_checksum)
	{
		for (i = 0; i < 8; i++)
		{
			A_key[i] = temp_A_key[i];
			SSD_A[i] = SSD_B[i] = 0;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
