/* Enhanced Voice Privacy "enhVoicePriv.c" */

#include "scema.h" /* see Exhibit  2 -53 */

void Enhanced_Voice_Privacy(const unsigned int coderVer,
							unsigned char *speechBuf1,
							const unsigned int num1aBits,
							unsigned char *speechBufRem,
							const unsigned int numRemBits,
							const unsigned int decrypt,
							const unsigned int keyGenerator,
							const unsigned int direction)
{
	unsigned int i;
	unsigned char keystreamBuf[MaxFrameOctetSize];
	unsigned int net1aOctetSize;
	unsigned int num1aTopBits;
	unsigned int excess1aOctetSize;
	unsigned int remBitsOctetSize;
	unsigned int numRemTopBits;
	unsigned int ksgInputOctetSize;
	unsigned char nullEntropy[4] = { 0x00, 0x00, 0x00, 0x00 };

	/* Pointers to be set and used later */

	unsigned char *pKeyStream;
	unsigned char *pSpeech;	

	/*
	Number of octets that contain the Class 1A bits, and
	number of bits in the 1A bits top octet.
	*/

	net1aOctetSize = ((num1aBits - 1) / 8) + 1;
	num1aTopBits = num1aBits - (8 * (net1aOctetSize - 1));

	/*
	Number of octets that contain any excess Class 1A bits
	beyond the first 6 octets (48 bits). For ACELP and VSELP,
	this equals zero.
	*/

	excess1aOctetSize = MAX(net1aOctetSize ,6) - 6;	

	/*
	Number of octets that contain the remaining bits, namely
	those bits not protected by a CRC, usually called Class 1B
	and Class 2 bits. Also calculated is the number of bits
	in the remaining bits top octet.
	*/

	remBitsOctetSize = ((numRemBits - 1) / 8) + 1;
	numRemTopBits = numRemBits - (8 * (remBitsOctetSize - 1));

	/*
	If the number of Class 1A bits is greater than or equal
	to 48 bits, the 6-octet Long Block Encryptor is used, and
	its output feeds the KSG. However, if the number of 1A bits
	is less than 48 bits, the Short Block Encryptor is used and
	only its output is fed to the KSG. In this latter case, the
	KSG input will be repeated as necessary (in SCEMA_KSG()) to
	fill SCEMA's plaintext input field.
	*/

	ksgInputOctetSize = MIN(net1aOctetSize, 6);

	/* Input clean up */
	
	/*
	Ensure that bits other than the content-containing
	1A top bits are zeroed.
	*/

	speechBuf1[net1aOctetSize - 1] >>= (8 - num1aTopBits);
	speechBuf1[net1aOctetSize - 1] <<= (8 - num1aTopBits);

	/*Do the same for the remaining bits, i.e the Class 1B and
	Class 2 bits.
	*/

	speechBufRem[remBitsOctetSize - 1] >>= (8 - numRemTopBits);
	speechBufRem[remBitsOctetSize - 1] <<= (8 - numRemTopBits);

	
	if(!decrypt) /* encrypting */
	{
		/*
		If there are more than 48 1A bits, XOR the excess
		into initial 48 bits to inject added entropy.
		*/

		for (i = 0; i < excess1aOctetSize; i++)
			speechBuf1[i % 6] ^=  speechBuf1[i + 6];

		/*
		Use different block encryptors depending on the number
		of 1A bits.
		*/
		if(num1aBits >= 48)
		{
			/*
			Block encrypt the first 6 octets of speechBuf1.
			Note: keyGenerator = 1 for CaveKey1.The first
			6 octets of speechBuf1 are replaced by ciphertext.
			*/

			Long_Block_Encryptor(speechBuf1,VoiceContent,decrypt,
									dtcScheds + keyGenerator - 1,
									direction);
		}

		else /* num1aBits < 48 */
		{
			/*
			Block encrypt num1aBits of speechBuf1 to yield the
			same amount of ciphertext.			
			*/

			Short_Block_Encryptor (speechBuf1,num1aBits,VoiceContent,
											nullEntropy,decrypt,
											dtcScheds + keyGenerator - 1, 
											direction);
		}

		/*
		Form the appropriate amount of keystream with
		speechBuf1 as input. Either the first 6 octets
		of speechBuf1 are used which comprise the output of the
		Long Block Encryptor, or less are used if
		ksgInputOctetSize is set less than 6 octets, namely the
		output of the Short Block Encryptor.
		*/

		SCEMA_KSG(keystreamBuf,
					excess1aOctetSize + remBitsOctetSize,
					speechBuf1,ksgInputOctetSize,VoiceContent,
					dtcScheds + keyGenerator - 1,direction);
	
		/*
		XOR keystream into buffers to yield ciphertext
		Start at zeroth keystream octet
		*/

		pKeyStream = &keystreamBuf[0];

		/* First encrypt excess 1A bits if extant */

		pSpeech = speechBuf1 + 6;

		for (i = 0; i < excess1aOctetSize; i++)
			*pSpeech++ ^=  *pKeyStream++;

		/*
		Ensure that bits other than the content-containing
		(encrypted) (excess) 1A top bits are zeroed.
		*/
		
		speechBuf1[net1aOctetSize - 1] >>= (8 - num1aTopBits);
		speechBuf1[net1aOctetSize - 1] <<= (8 - num1aTopBits);
	
		
		/* Then encrypt remaining bits */

		pSpeech = speechBufRem;

		for (i = 0; i < remBitsOctetSize; i++)
			*pSpeech++ ^= *pKeyStream++;

	}
	
	
	else  /* decrypting */
	{
		/*
		Almost everything above is done in reverse order.
		The KSG is now first, and the block encryptor second.
		*/
		
		SCEMA_KSG(keystreamBuf,
					excess1aOctetSize + remBitsOctetSize,
					speechBuf1,ksgInputOctetSize,VoiceContent,
					dtcScheds + keyGenerator - 1,direction);

		pKeyStream = &keystreamBuf[0];
		pSpeech = speechBuf1 + 6;
		
		for (i = 0; i < excess1aOctetSize; i++)
			*pSpeech++ ^=  *pKeyStream++;

		pSpeech = speechBufRem;

		/* Decrypt remaining bits */
		
		for (i = 0; i < remBitsOctetSize; i++)
			*pSpeech++ ^= *pKeyStream++;

		/* Block encryptor choice */

		if(num1aBits >= 48)
		{
			Long_Block_Encryptor(speechBuf1,VoiceContent,decrypt,
									dtcScheds + keyGenerator - 1,
									direction);
		}

		else /* num1aBits < 48 */
		{
			Short_Block_Encryptor(speechBuf1,num1aBits,VoiceContent,
										nullEntropy,decrypt,
										dtcScheds + keyGenerator - 1,direction);
		}

		/*
		Ensure that bits other than the content-containing
		(decrypted) 1A top bits are zeroed, and then do
		post-XORing.
		*/

		speechBuf1[net1aOctetSize - 1] >>= (8 - num1aTopBits);
		speechBuf1[net1aOctetSize - 1] <<= (8 - num1aTopBits);

		if(num1aBits > 48)
			for (i = 0; i < excess1aOctetSize; i++)
				speechBuf1[i % 6] ^=  speechBuf1[i + 6];
			
	}	

	/*
	Remaining output clean up: Ensure that bits other than the
	content-containing remaining bits (Class 1B and Class 2
	bits) are zeroed.
	*/
	
	speechBufRem[remBitsOctetSize - 1] >>= (8 - numRemTopBits);
	speechBufRem[remBitsOctetSize - 1] <<= (8 - numRemTopBits);

}
