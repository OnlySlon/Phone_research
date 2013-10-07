#include <stdio.h>
#include "cave.h"  /* see Exhibit  2 -2 */
#include "wre.h"   /* see Exhibit  2 -31 */

/* NAM stored data */

unsigned char ESN[4] = { 0xd7, 0x5a, 0x96, 0xec };
unsigned char MIN1[3] = { 0x79, 0x29, 0x71 };
unsigned char A_key[8];
unsigned char SSD_A_NEW[8], SSD_A[8];
unsigned char SSD_B_NEW[8], SSD_B[8];


/* Test vector inputs */

unsigned char manufact[16] = { 0x85, 0x03, 0xA7, 0xDC, 
                               0x14, 0x35, 0xFA, 0x90, 
                               0xB6, 0x72, 0x40, 0x32, 
                               0x45, 0x05, 0x33, 0xC0 };

unsigned char baseid[4] = { 0x00, 0x00, 0x01, 0x00 };

unsigned char random_challenge[4] = { 0x7E, 0x49, 0xAE, 0x4F };

unsigned char acre_phone[3] = { 0x49, 0x85, 0xA6 };

unsigned char random_wre[3] = { 0x62, 0xEA, 0x40 };

unsigned char hs_esn[4] = { 0xED, 0x07, 0x13, 0x95 };

unsigned char rand_wikey[7] = { 0xB7, 0xFC, 0x75, 0x5A, 
                                0xF0, 0xA4, 0x90 };

/* CAVE outputs */

extern unsigned char		WIKEY[8];
extern unsigned char		WIKEY_NEW[8];
extern unsigned char		WRE_KEY[8];

void main(void)
{
    int i;
    unsigned long auth_sig;

    WIKEY_Generation(manufact,baseid);
    printf("WIKEY = ");
    for(i=0;i<8;i++)
      printf("%02x",(unsigned int)WIKEY[i]);
    printf("\n");

    auth_sig = WI_Auth_Signature(random_challenge,baseid,acre_phone);
    printf("AUTH_SIGNATURE = %05lx\n",auth_sig);

    WRE_KEY[0] = 0xCB;
    WRE_KEY[1] = 0x60;
    WRE_KEY[2] = 0xF9;
    WRE_KEY[3] = 0x9F;
    WRE_KEY[4] = 0x5B;
    WRE_KEY[5] = 0x15;
    WRE_KEY[6] = 0x6F;
    WRE_KEY[7] = 0xAE;

    auth_sig = WRE_Auth_Signature(random_wre,baseid,hs_esn);
    printf("AUTH_SIGNATURE = %05lx\n",auth_sig);

    WIKEY_Update(rand_wikey,baseid);
    printf("WIKEY_NEW = ");
    for(i=0;i<8;i++)
      printf("%02x",(unsigned int)WIKEY_NEW[i]);
    printf("\n");

	printf("Enter to exit\n");
	getchar();
}

