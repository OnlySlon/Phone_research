/* Enhanced Message Encryption "enhMsgEnc.c" */

#include "scema.h" /* see Exhibit  2 -53 */

void Enhanced_Message_Encryption(unsigned char *msgBuf,
							const unsigned int numBits,
							const unsigned int dcchDTC,
							const unsigned char *rand,
							const unsigned char msgType,
							const unsigned int decrypt,
							const unsigned int keyGenerator,
							const unsigned int direction)
{
	unsigned int i;
	unsigned char keystreamBuf[MaxMessageOctetSize];
	unsigned int msgBufOctetSize;
	unsigned int numTopBits;
	unsigned int excessOctetSize;
	unsigned int ksgInputOctetSize;
	unsigned char entropy[4] = { 0x00, 0x00, 0x00, 0x00 };

	/* Pointers to be set and used later */

	unsigned char *pKeyStream;
	unsigned char *pMessage;
	keySched *pDcchDtc;

	/* Entropy gathering and key schedule selection*/
	
	if(dcchDTC) /* DTC channel */
	{
		entropy[0] = msgType;
		pDcchDtc = dtcScheds;
	}

	else /* DCCH channel */
	{
		for (i = 0; i < 4; i++)
			entropy[i] = rand[i];
		entropy[0] ^= msgType;
		pDcchDtc = dcchScheds;
	}
		
	/*
	Number of octets that contain the message bits, and
	number of bits in their top octet.
	*/

	msgBufOctetSize = ((numBits - 1) / 8) + 1;
	numTopBits = numBits - (8 * (msgBufOctetSize - 1));

	/*
	Number of octets that contain any excess message bits
	beyond the first 6 octets (48 bits).
	*/

	excessOctetSize = MAX(msgBufOctetSize ,6) - 6;	

	/*
	If the number of message bits is greater than or equal
	to 48 bits, the 6-octet Long Block Encryptor is used, and
	its output feeds the KSG. The KSG is run only if excess
	bits are present. However, if the number of message bits
	is less than 48 bits, only the Short Block Encryptor is
	used.
	*/

	ksgInputOctetSize = MIN(msgBufOctetSize, 6);

	/* Input clean up */
	
	/*
	Ensure that bits other than the content-containing
	top bits are zeroed.
	*/

	msgBuf[msgBufOctetSize - 1] >>= (8 - numTopBits);
	msgBuf[msgBufOctetSize - 1] <<= (8 - numTopBits);

	if(!decrypt) /* encrypting */
	{
		/*
		If there are more than 48 message bits, XOR the excess
		into initial 48 bits to inject added entropy.
		*/

		for (i = 0; i < excessOctetSize; i++)
			msgBuf[i % 6] ^=  msgBuf[i + 6];

		/*
		Use different block encryptors depending on the number
		of message bits.
		*/

		if(numBits >= 48)
		{
			/*
			Block encrypt the first 6 octets of msgBuf and
			first inject entropy.
			Note: keyGenerator = 1 for CaveKey1.The first
			6 octets of msgBuf are replaced by ciphertext.
			*/

			for (i = 0; i < 4; i++)
				msgBuf[i] ^=  entropy[i];

			Long_Block_Encryptor(msgBuf,MessageContent,decrypt,
									pDcchDtc + keyGenerator - 1,
									direction);

			if(numBits > 48)
			{
				/*
				Form the appropriate amount of keystream with
				msgBuf as input.
				*/

				SCEMA_KSG(keystreamBuf, excessOctetSize, msgBuf, 
					ksgInputOctetSize, MessageContent, 
					pDcchDtc + keyGenerator - 1, direction);

				/*
				XOR keystream into buffers to yield ciphertext
				Start at zeroth keystream octet
				*/

				pKeyStream = &keystreamBuf[0];

				/* First encrypt excess message bits if extant */

				pMessage = msgBuf + 6;
				for (i = 0; i < excessOctetSize; i++)
					*pMessage++ ^=  *pKeyStream++;
			}
		}

		else /* numBits < 48 */
		{
			/*
			Block encrypt numBits of msgBuf to yield the
			same amount of ciphertext.			
			*/

			Short_Block_Encryptor(msgBuf, numBits, MessageContent, 
				entropy, decrypt, pDcchDtc + keyGenerator - 1,direction);
		}

		/*
		Ensure that bits other than the content-containing
		(encrypted) (excess) message top bits are zeroed.
		*/
		
		msgBuf[msgBufOctetSize - 1] >>= (8 - numTopBits);
		msgBuf[msgBufOctetSize - 1] <<= (8 - numTopBits);
	
	}
	
	else  /* decrypting */
	{
		/*
		Almost everything above is done in reverse order.
		The KSG is now first, and the block encryptor second.
		*/

		if(numBits > 48)
		{
		
				SCEMA_KSG(keystreamBuf,excessOctetSize,msgBuf,ksgInputOctetSize,
				MessageContent, pDcchDtc + keyGenerator - 1,direction);	

				pKeyStream = &keystreamBuf[0];
				pMessage = msgBuf + 6;

				for (i = 0; i < excessOctetSize; i++)
					*pMessage++ ^=  *pKeyStream++;

		}

		/* Block encryptor choice */

		if(numBits >= 48)
		{
			Long_Block_Encryptor(msgBuf,MessageContent,decrypt,
									pDcchDtc + keyGenerator - 1,
									direction);

			for (i = 0; i < 4; i++)
				msgBuf[i] ^=  entropy[i];
		}

		else /* numBits < 48 */
		{
			Short_Block_Encryptor(msgBuf,numBits,MessageContent,entropy,
							decrypt, pDcchDtc + keyGenerator - 1,direction);
		}

		/*
		Ensure that bits other than the content-containing
		(decrypted) message top bits are zeroed, and then do
		post-XORing.
		*/

		msgBuf[msgBufOctetSize - 1] >>= (8 - numTopBits);
		msgBuf[msgBufOctetSize - 1] <<= (8 - numTopBits);

		if(numBits > 48)
			for (i = 0; i < excessOctetSize; i++)
				msgBuf[i % 6] ^=  msgBuf[i + 6];
			
	}
	
}

