/*
Short Block Encryptor (less than 6 octets) for Voice and Message Content "shortBlock.c" 

Note: The Short Block Encryptor/Decryptor's LHS and RHS are each less then or equal 3 octets in length. The number of content-bearing bits of its LHS (left hand side) always equals or is one greater than the number of content-bearing bits in its RHS. 
*/

#include "scema.h" /* see Exhibit  2 -53 */

void feistelPiece(const unsigned char *inputBuf,
				  unsigned char *outputBuf,
				  const unsigned char *ksgTemplate,
				  const unsigned char instanceId,
				  const unsigned char *entropy,
				  keySched *schedPtr)
{
	unsigned int i;
	unsigned char csync[4];
	unsigned char keystreamBuf[3];

	/*
	SCEMA's PT input is tied to CS input with ID differentiator..
	ID is XORed in to yield KSGs that are unique with respect
	to content, direction, and instance.
	*/

	for (i = 0; i < 3; i++)
	{
		csync[i] =  inputBuf[i] ^ entropy[i];
		keystreamBuf[i] = csync[i] ^ instanceId;
	}

	csync[3] = entropy[3] ^ instanceId;
	
	SCEMA(keystreamBuf,ThreeOctets,csync,KSGArchitecture,KSGIdMask,
		ENCRYPTING,schedPtr);

	/* KSG output is XORed with right buffer. The template passes
	only those bits that correspond to the right buffer's content
	bits.
	*/
	
	for (i = 0; i < 3; i++)
		outputBuf[i] ^= keystreamBuf[i] & ksgTemplate[i];
		
}


void Short_Block_Encryptor(unsigned char *contentBuf,
					const unsigned int numBits,
					const unsigned char contentType,
					const unsigned char *entropy,
					const unsigned int decrypt,
					keySched *schedPtr,
					const unsigned int direction)
{
	unsigned int i;
	unsigned char id;
	unsigned int numBitsLocal;
	unsigned int octetSize;
	unsigned int numTopBits;

	unsigned char leftBuf[3] = {0x00,0x00,0x00};
	unsigned char rightBuf[3] = {0x00,0x00,0x00};
	unsigned int leftBufNumBits;
	unsigned int rightBufNumBits;
	
	unsigned char leftKsgTemplate[3] = {0x00,0x00,0x00};
	unsigned char rightKsgTemplate[3] = {0x00,0x00,0x00};

	unsigned char *pContent;
	unsigned char *pLeft;
	unsigned char *pRight;
	
	/* Prevents accidental buffer overflow */

	numBitsLocal = MIN(numBits,48);
	numBitsLocal = MAX(numBitsLocal,1);

	/*
	Number of octets needed to contain contentBuf bits
	Note: The index of the top octet (the highest one containing
	content) is thus octetSize - 1.
	*/

	octetSize = ((numBitsLocal - 1) / 8) + 1;

	/*
	Number of content bits in top octet which occupy the top
	bits of the octet
	*/

	numTopBits = numBitsLocal - (8 * (octetSize - 1));

	/* Number of content bits in left buffer */

	leftBufNumBits = (numBitsLocal + 1)/2;

	/* Number of content bits in right buffer */

	rightBufNumBits = numBitsLocal/2;

	/* Ensure that unused contentBuf octets are zeroed and that
	unused bits	in the top octet are zeroed.
	*/

	for (i = octetSize; i < 6; i++)
		contentBuf[i] = 0;

	contentBuf[octetSize - 1] >>= (8 - numTopBits);
	contentBuf[octetSize - 1] <<= (8 - numTopBits);

	/*
	Divide contentBuf input bits between left and right buffers
	to begin building a Feistel network. If numBitsLocal is even,
	both buffers receive an equal number of bits. If numBitsLocal
	is odd, the left buffer receives one more bit than the right
	buffer.
	*/

	pContent = contentBuf;
	pLeft = &leftBuf[0];
	pRight = &rightBuf[0];
	
	for (i = 0; i < 3; i++)
	{
		*pLeft |= *pContent & 0xAA;
		*pRight |= (*pContent++ & 0x55) << 1;
		*pLeft++ |= (*pContent & 0xAA) >> 1;
		*pRight++ |= *pContent++ & 0x55;
	}

	/* Now that the content has been extracted from the contentBuf,
	the buffer is re-used temporarily to generate KSG templates.
	These templates will be	used to pass only those KSG bits
	corresponding to the content-bearing left and right buffer bits.
	*/

	for (i = 0; i < octetSize; i++)
		contentBuf[i] = 0xFF;
	
	for (i = octetSize; i < 6; i++)
		contentBuf[i] = 0;

	contentBuf[octetSize - 1] >>= (8 - numTopBits);
	contentBuf[octetSize - 1] <<= (8 - numTopBits);

	pContent = contentBuf;
	pLeft = &leftKsgTemplate[0];
	pRight = &rightKsgTemplate[0];
	
	for (i = 0; i < 3; i++)
	{
		*pLeft |= *pContent & 0xAA;
		*pRight |= (*pContent++ & 0x55) << 1;
		*pLeft++ |= (*pContent & 0xAA) >> 1;
		*pRight++ |= *pContent++ & 0x55;
	}

	/*
	Combine ID segments. A DCCH/DTC id segment is not needed for
	differentiation	because the two channels use different keys.
	*/

	id = (unsigned char)(direction << 7) | contentType;	

	
	/*
	Encryption/Decryption
	
	*/

	if(!decrypt) /* encrypting */
	{		
		/*
		Four Feistel-SCEMA instances. The zeroth instance does not
		contain an explicit instance number because the number
		is zero.
		*/

		feistelPiece(leftBuf,rightBuf,rightKsgTemplate,
						id,entropy,schedPtr);
		
		feistelPiece(rightBuf,leftBuf,leftKsgTemplate,
						(unsigned char)(id | Instance1),
						entropy,schedPtr);

		feistelPiece(leftBuf,rightBuf,rightKsgTemplate,
						(unsigned char)(id | Instance2),
						entropy,schedPtr);

		feistelPiece(rightBuf,leftBuf,leftKsgTemplate,
						(unsigned char)(id | Instance3),
						entropy,schedPtr);

	}


	/*
	Almost everything above is done in reverse order.
	*/
	
	else  /* decrypting */
	{		
		feistelPiece(rightBuf,leftBuf,leftKsgTemplate,
						(unsigned char)(id | Instance3),
						entropy,schedPtr);
		
		feistelPiece(leftBuf,rightBuf,rightKsgTemplate,
						(unsigned char)(id | Instance2),
						entropy,schedPtr);
		
		feistelPiece(rightBuf,leftBuf,leftKsgTemplate,
						(unsigned char)(id | Instance1),
						entropy,schedPtr);

		feistelPiece(leftBuf,rightBuf,rightKsgTemplate,
						id,entropy,schedPtr);
	
	}

	/*
	Output processing: Load left and right buffers back into content
	buffer.
	*/

	for (i = 0; i < 6; i++)
		contentBuf[i] = 0;

	pContent = contentBuf;
	pLeft = &leftBuf[0];
	pRight = &rightBuf[0];
	
	for (i = 0; i < 3; i++)
	{
		*pContent |= *pLeft & 0xAA;
		*pContent++ |= (*pRight >> 1) & 0x55;
		*pContent |= (*pLeft++ << 1) & 0xAA;
		*pContent++ |= *pRight++ & 0x55;
	}

}
