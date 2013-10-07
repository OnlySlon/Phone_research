/* SCEMA KSG for Voice and Message Content "scemaKSG.c" */

#include "scema.h" /* see Exhibit  2 -53 */

void SCEMA_KSG(unsigned char *keystreamBuf,
				const unsigned int requestedStreamLen,
				const unsigned char *inputBuf,
				const unsigned int inputLen,
				const unsigned char contentType,
				keySched *schedPtr,
				const unsigned int direction)
{
	unsigned int i;
	unsigned char csync[4];
	unsigned char id;
	unsigned int outputStreamLen;

	/* Generates a minimum of 6 octets of keystream */
	outputStreamLen = MAX(SixOctets,requestedStreamLen);
	
	/* Combine ID segments */
	id = (unsigned char)(direction << 7) | contentType;
	
	/* Repeat input across SCEMA's PT field */
	for (i = 0; i < outputStreamLen; i++)
		keystreamBuf[i] =  inputBuf[i % inputLen];
	
	/*
	Copy 4 least significant octets of PT to CS input.
	ID is XORed in to yield KSGs that are unique with
	respect to content and direction.
	*/
	for (i = 0; i < 4; i++)
		csync[i] =  keystreamBuf[i] ^ id;

	SCEMA(keystreamBuf,outputStreamLen,csync,KSGArchitecture,KSGIdMask,
			ENCRYPTING,schedPtr);
}

