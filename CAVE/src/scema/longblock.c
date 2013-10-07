/*
Long Block Encryptor (6 octets) for Voice and Message Content "longBlock.c" 
Note: The Long Block Encryptor/Decryptor's LHS and RHS are each 3 octets in length. 
*/
#include "scema.h" /* see Exhibit  2 -53 */

void Long_Block_Encryptor(unsigned char *contentBuf,
					const unsigned char contentType,
					const unsigned int decrypt,
					keySched *schedPtr,
					const unsigned int direction)
{
	unsigned char csync[4] = { 0x00, 0x00, 0x00, 0x00 };
	unsigned char id;
	unsigned char instanceId;
	
/*
Combine ID segments
Note: In particular, the LongBlockArchitecture ID segment forces bit 2 
of SCEMA's cryptosync top octet to 1 to differentiate it from all 
other uses (i.e.KSG uses) where bit 2 is forced to 0.
*/
	id = (unsigned char)(direction << 7) | contentType | 
		LongBlockArchitecture;
	
/*
SCEMA instance 0: PT <- LHS of contentBuf, CS <- RHS, instance = 0
for encrypt, and 2 for decrypt.

Note: The temporary variable csync is used to prevent buffer overflow 
during reading since SCEMA reads in a 4-octet csync buffer. This is 
not needed in the second instance since no overflow occurs and since 
the highest cync input octet is zeroed by LongBlkIdMask.
*/
	
	csync[0] = contentBuf[3];
	csync[1] = contentBuf[4];
	csync[2] = contentBuf[5];
	
	if (decrypt)
		instanceId = id | Instance2;
	else
		instanceId = id;
	
	SCEMA(contentBuf,ThreeOctets,csync,instanceId,LongBlkIdMask,
			decrypt,schedPtr);

/* SCEMA instance 1: PT <- RHS of contentBuf, CS <- LHS, instance = 1 */
	
	instanceId = id | Instance1;

	SCEMA(contentBuf + 3,ThreeOctets, contentBuf, instanceId, 
		LongBlkIdMask, decrypt, schedPtr);

/* SCEMA instance 2: PT <- LHS of contentBuf, CS <- RHS, instance = 2 */
	
	csync[0] = contentBuf[3];
	csync[1] = contentBuf[4];
	csync[2] = contentBuf[5];
	
	if (decrypt)
		instanceId = id;
	else
		instanceId = id | Instance2;
		
	SCEMA(contentBuf,ThreeOctets,csync,instanceId,LongBlkIdMask,
			decrypt,schedPtr);

}
