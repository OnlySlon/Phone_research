//#define CAVE_SOURCE_FILE // From cave.c
#include "cavei.h" // From cave.c
/* CMEA has the same header as CAVE (see Exhibit  2 -4) */

void CMEA(unsigned char *msg_buf, const int octet_count)
{
	int msg_index,half;
	unsigned char k,z;
	
	/* first manipulation (inverse of third) */
	
	z = 0;
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		k = tbox((unsigned char)(z ^ (msg_index & 0xff)));
		msg_buf[msg_index] += k;
		z += msg_buf[msg_index];
	}
	
	/* second manipulation (self-inverse) */
	
	half = octet_count/2;
	for (msg_index = 0; msg_index < half; msg_index++)
	{
		msg_buf[msg_index] ^= 
			msg_buf[octet_count - 1 - msg_index] | 0x01;
	}
	
	/* third manipulation (inverse of first) */
	
	z = 0;
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		k = tbox((unsigned char)(z ^ (msg_index & 0xff)));
		z += msg_buf[msg_index];
		msg_buf[msg_index] -= k;
	}
}

