/* Vector Set 7 - Enhanced Voice Privacy "vs7enhVoicePriv.h"

Note 1: The current coder standards' bit allocations as listed in TIA/EIA-136-510 are: The Number of {Class 1A bits, remaining bits, CRC bits} for 136 speech coders are: 136-410 ACELP {48, 100, 7}, 136-420 VSELP {12, 147, 7}, and 136-430 US1 {81, 163, 8}.

Note 2: The last octets of the decrypted buffers may not match the original input buffers' last octets. This is legitimate and comprises a test to ensure that the output clean up code is working to zero out non-content bearing bits.
*/

	printf("\n\nVector Set 7 - Enhanced Voice Privacy\n");
	
	/* 48 Class 1A bits, 100 remaining bits */

	printf("\n48 Class 1A bits, 100 remaining bits\n\n");
	
	printf("1A/Rem. bits input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");

	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		testBufTwo[i] = ~buf[i % EightOctets];
	
	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	
	/* Encrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,48,testBufTwo,100,
							ENCRYPTING,CAVEKey1,ForwardChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	
	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	/* Decrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,48,testBufTwo,100,
							DECRYPTING,CAVEKey1,ForwardChannel);
	
	printf("  Decryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	
	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	pause();	

	/* 81 Class 1A bits, 163 remaining bits */

	printf("\n81 Class 1A bits, 163 remaining bits\n\n");

	printf("1A/Rem. bits input =");
	
	for (i = 0; i < ((81 - 1) / 8) + 1; i++)
		testBuf[i] = buf[i % EightOctets];
	
	for (i = 0; i < ((81 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");

	for (i = 0; i < ((163 - 1) / 8) + 1; i++)
		testBufTwo[i] = ~buf[i % EightOctets];
	
	for (i = 0; i < ((163 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	/* Encrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,81,testBufTwo,163,
							ENCRYPTING,CAVEKey1,ForwardChannel);

	printf("  Encryptor output =");

	for (i = 0; i < ((81 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	
	for (i = 0; i < ((163 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	/* Decrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,81,testBufTwo,163,
							DECRYPTING,CAVEKey1,ForwardChannel);
	
	printf("  Decryptor output =");

	for (i = 0; i < ((81 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	
	for (i = 0; i < ((163 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");

	pause();	

	/* 12 Class 1A bits, 147 remaining bits */

	printf("\n12 Class 1A bits, 147 remaining bits\n\n");

	printf("1A/Rem. bits input =");

	for (i = 0; i < ((12 - 1) / 8) + 1; i++)
		testBuf[i] = buf[i % EightOctets];

	for (i = 0; i < ((12 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");

	for (i = 0; i < ((147 - 1) / 8) + 1; i++)
		testBufTwo[i] = ~buf[i % EightOctets];

	for (i = 0; i < ((147 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");

	/* Encrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,12,testBufTwo,147,
							ENCRYPTING,CAVEKey1,ForwardChannel);

	printf("  Encryptor output =");

	for (i = 0; i < ((12 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");

	for (i = 0; i < ((147 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");

	/* Decrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,12,testBufTwo,147,
							DECRYPTING,CAVEKey1,ForwardChannel);

	printf("  Decryptor output =");

	for (i = 0; i < ((12 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	for (i = 0; i < ((147 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	pause();	

	/* Reverse Channel, 48 Class 1A bits, 100 remaining bits */

	printf("\nReverse Channel, 48 Class 1A bits, 100 remaining bits\n\n");
	
	printf("1A/Rem. bits input =");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];
	
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");

	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		testBufTwo[i] = ~buf[i % EightOctets];
	
	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
	
	/* Encrypting */
	Enhanced_Voice_Privacy(CoderVersionZero,testBuf,48,testBufTwo,100,
							ENCRYPTING,CAVEKey1,ReverseChannel);
	
	printf("  Encryptor output =");

	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf(" /");
	
	for (i = 0; i < ((100 - 1) / 8) + 1; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n");
