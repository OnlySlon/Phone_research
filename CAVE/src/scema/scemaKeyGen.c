/* SCEMA Financial_Secret_Generation has the same header as SCEMA (see Exhibit  2 -53) */
/* SCEMA_Secret_Generation "scemaKeyGen.c */

#include "cavei.h" /* see Exhibit  2 -3 */
#include "scema.h" /* see Exhibit  2 -53 */


/* CAVE-related code */

void roll_LFSR_SCEMA(void)
{
	LFSR_A = Register[0];
	LFSR_B = Register[1];
	LFSR_C = Register[14];
	LFSR_D = Register[15];
	
	if ((LFSR_A | LFSR_B | LFSR_C | LFSR_D) == 0)
	{
		LFSR_A = 0x31;
		LFSR_B = 0x41;
		LFSR_C = 0x59;
		LFSR_D = 0x26;
	}
}


void SCEMA_Secret_Generation(keySched *schedPtr)
{
	int i,j,offset_1,offset_2;
	
	/* iteration 1, first pass through CAVE */
	
	for (i = 0; i < 4; i++)
		LFSR[i] = cmeakey[i+4];
	
	if ((LFSR_A | LFSR_B | LFSR_C | LFSR_D) == 0)
	{
		LFSR_A = 0x31;
		LFSR_B = 0x41;
		LFSR_C = 0x59;
		LFSR_D = 0x26;
	}
	for (i = 0; i < 8; i++)
		Register[i] = cmeakey[i];
			
	for (i = 8; i < 16; i++)
		Register[i] = ~cmeakey[i-8];
	
	offset_1 = 0x0;
	offset_2 = 0x0;
	
	CAVE(8, &offset_1, &offset_2);

/* Generation of SCEMA_KEY */
	
	i = 0; j = 4;
	while (i < ScemaKeyLengthCK1)
	{
		/* see if new key material needs to be generated */
		if( j == 4 )
		{
			j = 0;
			roll_LFSR_SCEMA();
			CAVE(4, &offset_1, &offset_2);
		}

		schedPtr->scemaKey[i] = Register[j+4] ^ Register[j+8];
		j++;

		/* advance to next octet of SCEMA_KEY if not zero; otherwise 
		   generate another value */

		if (schedPtr->scemaKey[i] != 0)
			i++;
	}

	/* Generation of SCEMA Obox Table */
	
	i = 0; j = 4;
	while (i < 16)
	{
		/* see if new key material needs to be generated */
		if( j == 4 )
		{
			j = 0;
			roll_LFSR_SCEMA();
			CAVE(4, &offset_1, &offset_2);
		}

		schedPtr->obox[i] = 
			(int)(((Register[j+4] ^ Register[j+8]) & 0xFF) |
					((Register[j+5] ^ Register[j+9]) << 8));
		j += 2;
		
		/* advance to next octet of Obox Table if not zero; otherwise 
		   generate another value */

		if (((schedPtr->obox[i] + i) & 0x0F) != 0)
			i++;
	}

	/* Generation of SCEMA auxiliary offset keys */
	
	roll_LFSR_SCEMA();
	CAVE(4, &offset_1, &offset_2);
	
	schedPtr->offKey[0] = (int)(((Register[4] ^ Register[8]) & 0xFF) |
					((Register[5] ^ Register[9]) << 8));

	schedPtr->offKey[1] = (int)(((Register[6] ^ Register[10]) & 0xFF) |
					((Register[7] ^ Register[11]) << 8));

}
