/* Vector Set 5 - Short Block Encryptor "vs5shortBlock.h" 

Note: The last octets of the decrypted buffers may not match the original input buffers' last octets. This is legitimate and comprises a test to ensure that the output clean up code is working to zero out non-content bearing bits.
*/

	printf("\n\nVector Set 5 - Short Block Encryptor\n");

	
	/* Encryption/Decryption (47 bits,Voice content,Reverse Channel) */

	printf("\nEncryption/Decryption (47 bits, Voice content,Reverse Channel)\n\n");
	
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,47,VoiceContent,testBufTwo,
							ENCRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,47,VoiceContent,testBufTwo,
							DECRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");


	/* Encryption/Decryption (17 bits,Voice content,Reverse Channel) */

	printf("\nEncryption/Decryption (17 bits, Voice content,Reverse Channel\n\n");
		
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,17,VoiceContent,testBufTwo,
							ENCRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,17,VoiceContent,testBufTwo,
							DECRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	
	pause();	


	/* Encryption/Decryption (16 bits,Voice content,Reverse Channel) */

	printf("\nEncryption/Decryption (16 bits, Voice content,Reverse Channel\n\n");
		
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,16,VoiceContent,testBufTwo,
							ENCRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,16,VoiceContent,testBufTwo,
							DECRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	
	/* Encryption/Decryption (2 bits,Voice content,Reverse Channel) */

	printf("\nEncryption/Decryption (2 bits, Voice content,Reverse Channel\n\n");
	
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,2,VoiceContent,testBufTwo,
							ENCRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,2,VoiceContent,testBufTwo,
							DECRYPTING,dtcScheds,ReverseChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	pause();


	/* Encryption,47 bits,Voice content,Forward Channel */

	printf("\nEncryption,47 bits,Voice content,Forward Channel\n\n");
	
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,47,VoiceContent,testBufTwo,
							ENCRYPTING,dtcScheds,ForwardChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

		
	/* Encryption,47 bits,Message content,Forward Channel */

	printf("\nEncryption,47 bits,Message content,Forward Channel\n\n");
	
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,47,MessageContent,testBufTwo,
							ENCRYPTING,dtcScheds,ForwardChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	
	/*
	Encryption,47 bits,Message content,Forward Channel,different entropy */

	printf("\nEncryption,47 bits,Message content,Forward Channel,different entropy\n\n");
	
	for (i = 0; i < SixOctets; i++)
	{
		testBuf[i] = buf[i];
		testBufTwo[i] = ~buf[i + 1];
	}

	printf(" SB Data Mask Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	Short_Block_Encryptor(testBuf,47,MessageContent,testBufTwo,
							ENCRYPTING,dtcScheds,ForwardChannel);
	
	printf("SB Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	pause();
