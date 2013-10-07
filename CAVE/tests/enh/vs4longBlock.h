/* Vector Set 4 - Long Block Encryptor "vs4longBlock.h" */

	printf("\nVector Set 4 - Long Block Encryptor\n\n");

	/* Encryption/Decryption (Voice content, Reverse Channel) */
	printf("\nEncryption/Decryption (Voice content, Reverse Channel)\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("                      Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

		
	Long_Block_Encryptor(testBuf,VoiceContent,ENCRYPTING,
							dtcScheds,ReverseChannel);

	
	printf("Long Block Encryptor Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	
	Long_Block_Encryptor(testBuf,VoiceContent,DECRYPTING,
							dtcScheds,ReverseChannel);
	
	printf("Long Block Decryptor Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n\n");


	/* Encryption (Message Content,Reverse Channel) */
	printf("\nEncryption (Message Content,Reverse Channel)\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("                      Input =");	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

		
	Long_Block_Encryptor(testBuf,MessageContent,ENCRYPTING,
							dtcScheds,ReverseChannel);

	
	printf("Long Block Encryptor Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n\n");
		
	
	/* Encryption (Voice Content,Forward Channel) */
	printf("\nEncryption (Voice Content,Forward Channel)\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("                      Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

		
	Long_Block_Encryptor(testBuf,VoiceContent,ENCRYPTING,
							dtcScheds,ForwardChannel);

	
	printf("Long Block Encryptor Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n\n");
		
	pause();	
	
