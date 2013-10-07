/* Vector Set 6 - Enhanced Message Encryption "vs6enhMsgEnc.h" 

Note: The last octets of the decrypted buffers may not match the original input buffers' last octets. This is legitimate and comprises a test to ensure that the output clean up code is working to zero out non-content bearing bits.
*/

	printf("\n\nVector Set 6 - Enhanced Message Encryption\n");
	
	/* 48 bits */

	printf("\n48 bits\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];
	
		
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,48,DCCH,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	
	/* Decrypting */
	Enhanced_Message_Encryption(testBuf,48,DCCH,testBufTwo,TestMsgType,
							DECRYPTING,CAVEKey1,ForwardChannel);
	
	
	printf("  Decryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	

	pause();	

		
	/* 256 Octets (2047 bits) */

	printf("\n256 Octets (2047 bits)\n\n");

	printf("   Last P/O Message input =");
	
	for (i = 0; i < 256; i++)
		testBuf[i] = buf[i % EightOctets];

	for (i = 0; i < EightOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i + 248]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];	
	
	
	/* Encrypting */

	Enhanced_Message_Encryption(testBuf,2047,DCCH,testBufTwo,
		TestMsgType,ENCRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("Last P/O Encryptor output =");

	for (i = 0; i < EightOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i + 248]);
	printf("\n");
	
		
	/* Decrypting */

	Enhanced_Message_Encryption(testBuf,2047,DCCH,testBufTwo,
		TestMsgType,DECRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("Last P/O Decryptor output =");

	for (i = 0; i < EightOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i + 248]);
	printf("\n");
	

	pause();	

	
	/* 44 bits */

	printf("\n44 bits\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];
	
		
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,44,DCCH,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	/* Decrypting */
	Enhanced_Message_Encryption(testBuf,44,DCCH,testBufTwo,TestMsgType,
							DECRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("  Decryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	

	pause();

	/* 48 bits, Forward Channel -> Reverse Channel */

	printf("\n48 bits, Forward Channel -> Reverse Channel\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];
	
		
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,48,DCCH,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ReverseChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	/* 48 bits, DCCH -> DTC */

	printf("\n48 bits, DCCH -> DTC\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];
	
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,48,DTC,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	 	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	/* 48 bits, different RAND */

	printf("\n48 bits, different RAND\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = buf[i];
	
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,48,DCCH,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	/* 44 bits, different RAND */

	printf("\n44 bits, different RAND\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = buf[i];
	
	/* Encrypting */
	Enhanced_Message_Encryption(testBuf,44,DCCH,testBufTwo,TestMsgType,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	/* 48 bits, different Message Type */

	printf("\n48 bits, different Message Type\n\n");
	
	printf("     Message input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	for (i = 0; i < 4; i++)
		testBufTwo[i] = ~buf[i];
	
/* Encrypting */
	Enhanced_Message_Encryption(testBuf,48,DCCH,testBufTwo,
										TestMsgType2, ENCRYPTING, CAVEKey1, 
										ForwardChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	pause();	
