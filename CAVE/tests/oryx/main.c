#include <stdio.h>
#include "cave.h"  /* see Exhibit  2 -2 */
#include "oryx.h"  /* see Exhibit  2 -45 */

/* NAM stored data */

unsigned char ESN[4] = { 0xd7, 0x5a, 0x96, 0xec };
unsigned char MIN1[3] = { 0x79, 0x29, 0x71 };
unsigned char A_key[8];
unsigned char SSD_A_NEW[8], SSD_A[8];
unsigned char SSD_B_NEW[8], SSD_B[8];

void pause(void)
{
	printf("Enter to continue\n");
	getchar();
}

void main(void)
{
	int i, j;
	unsigned long hook;
	unsigned char buf[24], rand[4];

	rand[0] = 0x12;
	rand[1] = 0x34;
	rand[2] = 0xab;
	rand[3] = 0xcd;

	hook = 0xcdef5678;

	SSD_B[0] = 0x14;
	SSD_B[1] = 0x92;
	SSD_B[2] = 0x52;
	SSD_B[3] = 0x80;
	SSD_B[4] = 0x17;
	SSD_B[5] = 0x76;
	SSD_B[6] = 0x18;
	SSD_B[7] = 0x67;

	printf("\nSSD_B =");
	for (i = 0; i < 4; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
		{
			printf("%02x", (unsigned int)SSD_B[2*i+j]);
		}
	}

	printf("\nRAND =");
	for (i = 0; i < 2; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
		{
			printf("%02x", (unsigned int)rand[2*i+j]);
		}
	}

	printf("\nHOOK = %04lx %04lx\n", hook >> 16, hook & 0x0000ffff);

	pause();

	printf("24 octets of mask to be returned");

	DataKey = DataKey_Generation();

	printf("\n\nOutput:\n\n");

	printf("\nDataKey = %04lx %04lx\n", DataKey >> 16, 
		DataKey & 0x0000ffff);

	LTable_Generation(rand);

	printf("\n\nL:\n\n");

	for(i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			printf("%02x ", (unsigned int)L[16*i+j]);
		}
		printf("\n");
	}

	pause();

	Data_Mask(DataKey, hook, 24, buf);

	printf("\n\nmask:\n\n");

	for(i = 0; i < 2; i++)
	{
		for (j = 0; j < 12; j++)
		{
			printf("%02x ", (unsigned int)buf[12*i+j]);
		}
		printf("\n");
	}
	pause();
}
