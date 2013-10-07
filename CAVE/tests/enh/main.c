/*
EPE test file "main.c"

Explicitly contains code for generating vector sets 1 (DTC key 
schedule) and 2 (DCCH key schedule). These first two sets also test 
SCEMA. The key schedules are needed for generating the remaining 
vector sets. However,none of the remaining sets depend upon other sets 
being generated.
*/

#include <stdio.h>

#include "cave.h"

#include "scema.h"

void pause(void)
{
	printf("Enter to continue\n");
	getchar();
}

void main(void)
{
	unsigned int i;
	
/* test plaintext */

	const unsigned char buf[8] = {0xb6,0x2d,0xa2,0x44,
                                 0xfe,0x9b,0x23, 0xab};
	unsigned char testBuf[MaxMessageOctetSize];
	unsigned char testBufTwo[MaxFrameOctetSize];
	
	/* cryptosync (meaning is air interface specific) */

	unsigned char sync1[4] = { 0x3d,0x00,0xa2,0x00 };
	unsigned char sync2[4] = { 0xff,0x00,0xff,0x00 };

	/* vector set 1 */

	cmeakey[0] = 0xA0;
	cmeakey[1] = 0x7B;
	cmeakey[2] = 0x1C;
	cmeakey[3] = 0xD1;
	cmeakey[4] = 0x02;
	cmeakey[5] = 0x75;
	cmeakey[6] = 0x69;
	cmeakey[7] = 0x14;

	printf("\nVector Set 1 - DTC Key Generation and SCEMA\n\n");

	DTC_Key_Generation();

	printf("                DTC CMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)cmeakey[i]);
	printf("\n");
	
	printf("     DTC scemaKey (CaveKey1) =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)(dtcScheds)->scemaKey[i]);
	printf("\n");
	
	printf("                        sync =");
	printf(" %02x %02x %02x %02x\n",(unsigned int)sync1[0],
		(unsigned int)sync1[1],(unsigned int)sync1[2],
		(unsigned int)sync1[3]);

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	printf("                       Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	SCEMA(testBuf,SixOctets,sync1,0,0,ENCRYPTING,dtcScheds);
	
	printf("            DTC SCEMA Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	pause();
	
	/* vector set 2 */

	cmeakey[0] = 0xf0;
	cmeakey[1] = 0x06;
	cmeakey[2] = 0xa8;
	cmeakey[3] = 0x5a;
	cmeakey[4] = 0x05;
	cmeakey[5] = 0xcd;
	cmeakey[6] = 0xb3;
	cmeakey[7] = 0x2a;
	
	printf("\nVector Set 2 - DCCH Key Generation and SCEMA\n\n");
	
	DCCH_Key_Generation();

	printf("                DCCH CMEA key =");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)cmeakey[i]);
	printf("\n");
	
	printf("      DCCH scemaKey (CaveKey1)=");
	for (i = 0; i < 8; i++)
		printf(" %02x",(unsigned int)(dcchScheds)->scemaKey[i]);
	printf("\n");
	
	printf("                         sync =");
	printf(" %02x %02x %02x %02x\n",(unsigned int)sync2[0],
		(unsigned int)sync2[1],(unsigned int)sync2[2],
		(unsigned int)sync2[3]);

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	printf("                        Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	SCEMA(testBuf,SixOctets,sync2,0,0,ENCRYPTING,dcchScheds);
	
	printf("            DCCH SCEMA Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	pause();	
/*
Note: None of these remaining tests are mutually dependent, and can
thus be selectively disabled.
*/
/* Vector Set 3 - SCEMA KSG */
#include "vs3scemaKSG.h" 

/* Vector Set 4 - Long Block Encryptor */
#include "vs4longBlock.h" 

/* Vector Set 5 - Short Block Encryptor */
#include "vs5shortBlock.h" 

/* Vector Set 6 - Enhanced Message Encryption */
#include "vs6enhMsgEnc.h" 

/* Vector Set 7 - Enhanced Voice Privacy */
#include "vs7enhVoicePriv.h" 
	
/* Vector Set 8 - Enhanced Data Mask Generation */
#include "vs8enhDataMask.h" 

}
