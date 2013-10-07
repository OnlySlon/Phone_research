//#define ECMEA_SOURCE_FILE // From ecmea.c
#include "cavei.h"        // From ecmea.c
#include "ecmea.h"        // From ecmea.c
/* Non_Financial_Secret_Generation has the same header as ECMEA (see Exhibit  2 -30) */

void Non_Financial_Secret_Generation(void)
{
	int i,j,offset_1,offset_2;
	
	/* iteration 1, first pass through CAVE */
	
	for (i = 0; i < 4; i++)
		LFSR[i] = seed_nf_key[i+1];
	
	if ((LFSR_A | LFSR_B | LFSR_C | LFSR_D) == 0)
	{
		LFSR_A = 0x31;
		LFSR_B = 0x41;
		LFSR_C = 0x59;
		LFSR_D = 0x26;
	}
	for (i = 0; i < 5; i++)
		Register[i] = seed_nf_key[i];

	for (i = 5; i < 8; i++)
		Register[i] = 0;
			
	for (i = 8; i < 13; i++)
		Register[i] = ~seed_nf_key[i-8];
	
	for (i = 13; i < 16; i++)
		Register[i] = 0;

	offset_1 = 0x0;
	offset_2 = 0x0;
	
	CAVE(8, &offset_1, &offset_2);
	
	/* Iterations 2 and 3, generation of ECMEA_NF_KEY */
	
	i = 0; j = 4;
	while (i < 8)
	{
		/* see if new key material needs to be generated */
		if( j == 4 )
		{
			j = 0;
			roll_LFSR_2();
			CAVE(4, &offset_1, &offset_2);
		}

		ecmea_nf_key[i] = Register[j+4] ^ Register[j+8];
		j++;

		/* advance to next octet of ECMEA_NF_KEY if not zero; otherwise 
		   generate another value */

		if (ecmea_nf_key[i] != 0)
			i++;
	}

	/* iteration 4, generation of ECMEA offset_nf_key */
	
	roll_LFSR_2();  /* defined in Exhibit  2 -19 */
	CAVE(4, &offset_1, &offset_2);
	for (i = 0; i < 4; i++)
		offset_nf_key[i] = Register[i+4] ^ Register[i+8];
}


