/* Vector Set 8 - Enhanced Data Mask Generation "vs8enhDataMask.h" */

	printf("\nVector Set 8 - Enhanced Data Mask Generation\n\n");
		
	Enhanced_Data_Mask(testBuf, 0x87654321, SixOctets, CAVEKey1); 
	
	printf("Enhanced Data Mask Output =");
	for (i = 0; i < SixOctets; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n");
	
	Enhanced_Data_Mask(testBuf, 0x87654321, 3, CAVEKey1); 
	
	printf("   Output,with short Mask =");
	for (i = 0; i < 3; i++)
		printf(" %02x",(unsigned int)testBuf[i]);
	printf("\n\n");
	
	pause();	
