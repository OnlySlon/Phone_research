#include <stdio.h>
#include "cave.h"   /* see Exhibit  2 -2  */
#include "ecmea.h"  /* see Exhibit  2 -29 */

/* NAM stored data */

unsigned char ESN[4] = { 0xd7, 0x5a, 0x96, 0xec };
unsigned char MIN1[3] = { 0x79, 0x29, 0x71 };
unsigned char A_key[8];
unsigned char SSD_A_NEW[8], SSD_A[8];
unsigned char SSD_B_NEW[8], SSD_B[8];

/* data received from the network */

unsigned char RANDSSD[7] =	{ 0x4d, 0x18, 0xee, 0xaa,
                              0x05, 0x89, 0x5c };
unsigned char RAND1[4]    = { 0x34, 0xa2, 0xb0, 0x5f };
unsigned char RAND2[4]    = { 0x53, 0x75, 0xdf, 0x99 };
unsigned char RAND3[4]    = { 0x6c, 0x00, 0x02, 0x58 };

/* cryptosync (meaning is air interface specific) */

unsigned char sync1[2] = { 0x3d, 0xa2 };
unsigned char sync2[2] = { 0xff, 0xff };

/* test plaintext */

unsigned char buf[6] = { 0xb6, 0x2d, 0xa2, 0x44, 0xfe, 0x9b };

/* entered A_key and checksum */

char digits[26] = 
	{ '1', '4', '1', '4', '2', '1', '3', '5', '6', '2',
	  '3', '7', '3', '0', '9', '5', '0', '4', '8', '8',
	  '0', '8', '6', '5', '0', '0' };

void pause(void)
{
	printf("Enter to continue\n");
	getchar();
}

void main(void)
{
	int i, j;
	unsigned char auth_data[3], test_buf[6];
	unsigned long AUTHR;	
	
	/* check A_key and SSD */
	
	if(A_Key_Verify(digits))
	{
		printf("A key verified ok\n");
	}
	else
	{
		printf("A key verification failed\n");
		return;
	}
	
	/* check SSD generation process */
		
	SSD_Generation(RANDSSD);
	SSD_Update();
	
	printf("SSD_A =");
	for (i = 0; i < 4; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
			printf("%02x",(unsigned int)SSD_A[2*i+j]);
	}
	printf("\n");
	
	printf("SSD_B =");
	for (i = 0; i < 4; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
			printf("%02x",(unsigned int)SSD_B[2*i+j]);
	}
	printf("\n");
	
	/* Inputs for test vectors */
	
	/* put MIN1 into auth_data (no dialed digits for this test) */
	
	for (i = 0; i < 3; i++)
		auth_data[i] = MIN1[i];
		
	/* vector 1 */
	
	printf("\nVector 1\n\n");
	
	AUTHR = Auth_Signature(RAND1,auth_data,SSD_A,1);
	
	printf("RAND_CHALLENGE =");
	for (i = 0; i < 2; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
			printf("%02x",(unsigned int)RAND1[2*i+j]);
	}
	printf("\n");
	
	printf("AUTH_SIGNATURE = %01lx %04lx\n", AUTHR >> 16, 
		AUTHR & 0x0000ffff);
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	
	Key_VPM_Generation();
	ECMEA_Secret_Generation();
	Non_Financial_Seed_Key_Generation();
	Non_Financial_Secret_Generation();
	
	printf("      CMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)cmeakey[i]);
	printf("\n");
	
	printf("     ECMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_key[i]);
	printf("\n");
	
	printf("    offset_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_key[i]);
	printf("\n");
	
	printf("   SEED_NF key =");
	for (i = 0; i < 5; i++)
		printf(" %02x",(unsigned int)seed_nf_key[i]);
	printf("\n");
	
	printf("  ECMEA_NF key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_nf_key[i]);
	printf("\n");
	
	printf(" offset_nf_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_nf_key[i]);
	printf("\n");
	
	printf("    sync =");
	printf(" %02x %02x\n",(unsigned int)sync1[0],
		(unsigned int)sync1[1]);

	pause();	

	printf("          Input =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	CMEA(test_buf,6);
	
	printf("    CMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync1,0,0);
	
	printf("   ECMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync1,0,1);
	
	printf("ECMEA_NF Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	printf("VPM =");
	for (i = 0; i < 65; i++)
	{
		printf(" %02x",(unsigned int)VPM[i]);
		if (((i+1)%8) == 0)
			printf("\n     ");
	}
	printf("\n");

	pause();	

	/* vector 2 */
	
	printf("\nVector 2\n\n");
	
	AUTHR = Auth_Signature(RAND2,auth_data,SSD_A,1);
	
	printf("RAND_CHALLENGE =");
	for (i = 0; i < 2; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
			printf("%02x",(unsigned int)RAND2[2*i+j]);
	}
	printf("\n");
	
	printf("AUTH_SIGNATURE = %01lx %04lx\n", AUTHR >> 16, 
		AUTHR & 0x0000ffff);
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	
	Key_VPM_Generation();
	ECMEA_Secret_Generation();
	Non_Financial_Seed_Key_Generation();
	Non_Financial_Secret_Generation();
	
	printf("      CMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)cmeakey[i]);
	printf("\n");
	
	printf("     ECMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_key[i]);
	printf("\n");
	
	printf("    offset_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_key[i]);
	printf("\n");
	
	printf("   SEED_NF key =");
	for (i = 0; i < 5; i++)
		printf(" %02x",(unsigned int)seed_nf_key[i]);
	printf("\n");
	
	printf("  ECMEA_NF key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_nf_key[i]);
	printf("\n");
	
	printf(" offset_nf_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_nf_key[i]);
	printf("\n");
	
	printf("    sync =");
	printf(" %02x %02x\n",(unsigned int)sync2[0],
		(unsigned int)sync2[1]);

	pause();	

	printf("          Input =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	CMEA(test_buf,6);
	
	printf("    CMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync2,0,0);
	
	printf("   ECMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync2,0,1);
	
	printf("ECMEA_NF Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	printf("VPM =");
	for (i = 0; i < 65; i++)
	{
		printf(" %02x",(unsigned int)VPM[i]);
		if (((i+1)%8) == 0)
			printf("\n     ");
	}
	printf("\n");

	pause();	

	/* vector 3 */
	
	printf("\nVector 3\n\n");
	
	AUTHR = Auth_Signature(RAND3,auth_data,SSD_A,1);
	
	printf("RAND_CHALLENGE =");
	for (i = 0; i < 2; i++)
	{
		printf(" ");
		for (j = 0; j < 2; j++)
			printf("%02x",(unsigned int)RAND3[2*i+j]);
	}
	printf("\n");
	
	printf("AUTH_SIGNATURE = %01lx %04lx\n", AUTHR >> 16, 
		AUTHR & 0x0000ffff);
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	
	Key_VPM_Generation();
	ECMEA_Secret_Generation();
	Non_Financial_Seed_Key_Generation();
	Non_Financial_Secret_Generation();
	
	printf("      CMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)cmeakey[i]);
	printf("\n");
	
	printf("     ECMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_key[i]);
	printf("\n");
	
	printf("    offset_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_key[i]);
	printf("\n");
	
	printf("   SEED_NF key =");
	for (i = 0; i < 5; i++)
		printf(" %02x",(unsigned int)seed_nf_key[i]);
	printf("\n");
	
	printf("  ECMEA_NF key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)ecmea_nf_key[i]);
	printf("\n");
	
	printf(" offset_nf_key =");
	for (i = 0; i < 4; i++)
		printf(" %02x",(unsigned int)offset_nf_key[i]);
	printf("\n");
	
	printf("    sync =");
	printf(" %02x %02x\n",(unsigned int)sync2[0],
		(unsigned int)sync2[1]);

	pause();

	printf("          Input =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	CMEA(test_buf,6);
	
	printf("    CMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync2,0,0);
	
	printf("   ECMEA Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	for (i = 0; i < 6; i++)
		test_buf[i] = buf[i];
	ECMEA(test_buf,6,sync2,0,1);
	
	printf("ECMEA_NF Output =");
	for (i = 0; i < 6; i++)
		printf(" %02x",(unsigned int)test_buf[i]);
	printf("\n");
	
	printf("VPM =");
	for (i = 0; i < 65; i++)
	{
		printf(" %02x",(unsigned int)VPM[i]);
		if (((i+1)%8) == 0)
			printf("\n     ");
	}
	printf("\n");

	pause();
}

