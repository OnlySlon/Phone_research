//#define ECMEA_SOURCE_FILE // From ecmea.c
#include "cavei.h"        // From ecmea.c
#include "ecmea.h"        // From ecmea.c
/* Non_Financial_Seed_Key_Generation has the same header as ECMEA (see Exhibit  2 -30) */

void Non_Financial_Seed_Key_Generation(void)
{
	int i,offset_1,offset_2;
	
	/* iteration 1, first pass through CAVE */
	
	for (i = 0; i < 4; i++)
		LFSR[i] = cmeakey[i];
	
	if ((LFSR_A | LFSR_B | LFSR_C | LFSR_D) == 0)
	{
		LFSR_A = 0x31;
		LFSR_B = 0x41;
		LFSR_C = 0x59;
		LFSR_D = 0x26;
	}
	for (i = 0; i < 8; i++)
		Register[i] = ~cmeakey[i];
			
	for (i = 8; i < 16; i++)
		Register[i] = cmeakey[i-8];
	
	offset_1 = 0x0;
	offset_2 = 0x0;
	
	CAVE(8, &offset_1, &offset_2);
	
	/* iteration 2, generation of seed_nf_key */
	
	roll_LFSR_2();  /* defined in Exhibit  2 -19 */
	CAVE(4, &offset_1, &offset_2);
	for (i = 0; i < 5; i++)
		seed_nf_key[i] = Register[i+2] ^ Register[i+8];
}
