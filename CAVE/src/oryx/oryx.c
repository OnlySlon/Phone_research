#define ORYX_SOURCE_FILE
#include "cavei.h"  /* see Exhibit  2 -3 */
#include "oryx.h"   /* see Exhibit  2 -45 */

#define high(x) (unsigned char)(0xffU&(x>>24))    /* leftmost octet */
#define FA1 000460216667        /* Peterson & Weldon prim 32 */
#define FA2 001760427607        /* Peterson & Weldon prim 32 */
#define FB 020014300113         /* P&W prim 31 020004100071 times z+1 */
#define FK 030634530010         /* reverse of P&W prim 32 042003247143 */

static
unsigned long K;                /* 32-bit K  register */
static
unsigned long A, B;             /* 32-bit LFSRs */

unsigned char L[256];           /* look up table */
unsigned long DataKey;          /* data encryption key */

static
void kstep(void);
static
unsigned char keygen(void);

unsigned long DataKey_Generation(void)
{
	int i;
	unsigned long temp;
	
	A = 0;
	for(i=0; i<4; i++)
		A = (A<<8) + (unsigned long)SSD_B[i];
	B = 0;
	for(i=4; i<8; i++)
		B = (B<<8) + (unsigned long)SSD_B[i];
	
	K = A ^ B;
	for(i=0; i<256; i++)
	{
		kstep();
		L[i] = high(K);
	}
	for(i=0; i<32; i++)
	{
		temp = (unsigned long)keygen();
		A = (A<<9) + temp;
		temp = (unsigned long)keygen();
		B = (B<<9) + temp;
		temp = (unsigned long)keygen();
		K = (0xff00ffffU & K) + (temp << 16);
		K &= 0xffff00ffU + (temp<<8);
	}
	return ( (A ^ B ^ K) & 0xffffffff );
}

static
unsigned char keygen(void)
{
	unsigned char x;
	int  i, trips;
	
	kstep();
	/*
	 * if high bit of K set, use A1 feedback
	 * otherwise use A2 feedback
	 */
	if((1UL<<31) & A)
	{
		A += A;
		if((1UL<<31) & K)
			A = A ^ FA1;
		else
			A = A ^ FA2;
	}
	else
		A += A;
	/*
	 * if next-high bit of  K set, step B twice
	 * otherwise once
	 */
	if((1UL<<30) & K)
		trips = 2;
	else
		trips = 1;
	for(i=0; i<trips; i++)
	{
		if((1UL<<31) & B)
		{
			B += B;
			B = B ^ FB;
		}
		else
			B += B;
	}
	x = high(K) + L[high(A)] + L[high(B)];
	x &= 0xffU;										/* use only 8 bits */
	return x;
}

/*
 * step the K register
 */
static
void kstep(void)
{
	if(K==0) K = 0x31415926;
	if(K&1)
	{
		K = (K>>1) ^ FK;
	} 
	else
	{
		K = (K>>1);
	}
	K &= 0xffffffff;
}

