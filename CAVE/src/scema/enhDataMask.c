/* Enhanced Data Mask Generation "enhDataMask.c" */

#include "scema.h" /* see Exhibit  2 -53 */

void Enhanced_Data_Mask(unsigned char *mask,
						const unsigned long HOOK,
						const unsigned int len,
						const unsigned int keyGenerator)
{
	unsigned int i;
	unsigned char csync[4];
	unsigned char maskSix[6];
	
	csync[0] = (unsigned char)(HOOK & 0xFF);
	csync[1] = (unsigned char)((HOOK >> 8) & 0xFF);
	csync[2] = (unsigned char)((HOOK >> 16) & 0xFF);
	csync[3] = (unsigned char)((HOOK >> 24) & 0xFF);

	if(len >= 6)
	{
	
		/* Repeat HOOK across SCEMA's PT field */
		for (i = 0; i < len; i++)
			mask[i] =  csync[i % 4];

		/* Prevents cross-replay effects with other content types */
		for (i = 0; i < 4; i++)
			csync[i] ^=  RlpContent;
	
		/*
		Note: keyGenerator = 1 for CaveKey1.
		Since RLP encryption uses SCEMA in a KSG mode, the values
		KSGArchitecture and KSGIdMask are passed. This serves to force
		bit 2		in the cryptosync's top octet to zero to differentiate the cryptosync from that used in the Long Block Encryptor.
		*/
		SCEMA(mask,len,csync,KSGArchitecture,KSGIdMask,ENCRYPTING,
				dtcScheds + keyGenerator - 1);

	}

	
/*
If requested length is less then 6, create 6 octets of keystream
and output only what is needed
*/
	
	else
	{
		for (i = 0; i < 6; i++)
			maskSix[i] =  csync[i % 4];

		/* Prevents cross-replay effects with other content types */
		for (i = 0; i < 4; i++)
			csync[i] ^=  RlpContent;
	
	SCEMA(maskSix,SixOctets,csync,KSGArchitecture,KSGIdMask,ENCRYPTING,
				dtcScheds + keyGenerator - 1);
		
		for (i = 0; i < len; i++)
		{
			mask[i] = maskSix[i];
		}

	}
}


