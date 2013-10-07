/* Vector Set 3 - SCEMA KSG "vs3scemaKSG.h" */

	printf("\nVector Set 3 - SCEMA KSG\n\n");

	/* Voice content, Reverse Channel, 3-octet input, 8-octet output */
	printf("\nVoice content, Reverse Channel, 3-octet input, 8-octet output\n\n");

	for (i = 0; i < ThreeOctets; i++)
		testBuf[i] = buf[i];

	printf("           Input =");
	for (i = 0; i < ThreeOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

		
	SCEMA_KSG(testBufTwo,EightOctets,testBuf,ThreeOctets,
				VoiceContent,dtcScheds,ReverseChannel);

	
	printf("SCEMA KSG Output =");
	for (i = 0; i < EightOctets; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n\n");

	
	/* Voice content, Reverse Channel, 6-octet input, 6-octet output */
	printf("\nVoice content, Reverse Channel, 6-octet input, 6-octet output\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("           Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

			
	SCEMA_KSG(testBufTwo,SixOctets,testBuf,SixOctets,
				VoiceContent,dtcScheds,ReverseChannel);

	
	printf("SCEMA KSG Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n\n");

	
	/*
	Voice content, Reverse Channel, 6-octet input,
	3-octet requested output, 6 octets delivered
	*/
	printf("\nVoice content, Reverse Channel, 6-octet input,\n");
	printf(" 3-octet requested output, 6-octets delivered\n\n");
	
	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("           Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

			
	SCEMA_KSG(testBufTwo,ThreeOctets,testBuf,SixOctets,
				VoiceContent,dtcScheds,ReverseChannel);

	
	printf("SCEMA KSG Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n\n");

	pause();

	
	printf("\nVector Set 3 - SCEMA KSG cont'd\n\n");
	
	/* Message content, Reverse Channel, 6-octet input, 6-octet output */
	printf("\nMessage content, Reverse Channel, 6-octet input, 6-octet output\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("           Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	SCEMA_KSG(testBufTwo,SixOctets,testBuf,SixOctets,
				MessageContent,dtcScheds,ReverseChannel);

	printf("SCEMA KSG Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n\n");

	/* Message content, Forward Channel, 6-octet input, 6-octet output */

	printf("\nMessage content, Forward Channel, 6-octet input, 6-octet output\n\n");

	for (i = 0; i < SixOctets; i++)
		testBuf[i] = buf[i];

	printf("           Input =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");

	SCEMA_KSG(testBufTwo,SixOctets,testBuf,SixOctets,
				MessageContent,dtcScheds,ForwardChannel);

	printf("SCEMA KSG Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBufTwo[i]);
	printf("\n\n");

	
	pause();

