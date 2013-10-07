//#define ORYX_SOURCE_FILE // From oryx.c
#include "cavei.h"       // From oryx.c
#include "oryx.h"        // From oryx.c
/* The header for LTable_Generation is the same as for 
   DataKey_Generation (see Exhibit  2 -46).*/

void LTable_Generation(const unsigned char RAND[4])
{
	int i,j;
	unsigned char tempc;
	
	K = 0;
	for(i=0; i<4; i++)
		K = (K<<8) + (unsigned long)RAND[i];
	for (i=0; i<256; i++)
		L[i] = (unsigned  char)i;
	
	/* use high octet of K to permute 0 through 255 */
	for (i=0; i< 256; i++)
	{
		kstep();
		j =  high(K);
		tempc = L[i];
		L[i] = L[j];
		L[j] = tempc;
	}
}
