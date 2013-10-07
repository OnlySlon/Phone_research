//#define CAVE_SOURCE_FILE // From cave.c
#include "cavei.h" // From cave.c
/* tbox has the same header as CAVE (see Exhibit  2 -4) */

static unsigned char tbox(const unsigned char z)
{
	int k_index,i;
	unsigned char result;
	
	k_index = 0;
	result = z;
	
	for (i = 0; i < 4; i++)
	{
		result ^= cmeakey[k_index];
		result += cmeakey[k_index+1];
		result = z + CaveTable[result];
		k_index += 2;
	}
	
	return(result);
}

