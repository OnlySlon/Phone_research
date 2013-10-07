//#define ECMEA_SOURCE_FILE // From ecmea.c
#include "cavei.h"        // From ecmea.c
#include "ecmea.h"        // From ecmea.c
/* transform and inv_transform have the same header as ECMEA (see Exhibit  2 -30) */

void transform(unsigned char *msg_buf, const int octet_count,
               unsigned char offseta, const unsigned char offsetb,
               const unsigned char *key)
{
	unsigned char k, z;
	int msg_index;
	
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		/* offseta rotation and involutary lookup of present octet */
		
		if (msg_index > 0)
			offseta = (offseta >> 1) | (offseta << 7);
		msg_buf[msg_index] = offsetb ^ 
			etbox((unsigned char)(msg_buf[msg_index] ^ offseta), key);
		
		/* bit-trade between present octet and the one below */
		
		if (msg_index > 0)
		{
			k = msg_buf[msg_index - 1] ^ msg_buf[msg_index];
			k &= etbox((unsigned char)(k ^ offseta), key);
			msg_buf[msg_index - 1] ^= k;
			msg_buf[msg_index] ^= k;
		}
		
		/* random octet permutation */
		/* exchange previous octet with a random one below it */
		
		if (msg_index > 1)
		{
			k = etbox((unsigned char)(msg_buf[msg_index] ^ offseta), 
				key);
			k = ((msg_index) * k) >> 8;
			z = msg_buf[k];
			msg_buf[k] = msg_buf[msg_index - 1];
			msg_buf[msg_index - 1] = z;
		}
	}
	
	/* final octet permutation */
	/* exchange last octet with a random one below it */
	
	k = etbox((unsigned char)(0x37 ^ offseta), key);
	k = ((msg_index) * k) >> 8;
	z = msg_buf[k];
	msg_buf[k] = msg_buf[msg_index - 1];
	msg_buf[msg_index - 1] = z;

	/* final involution and XORing */

	k = etbox(msg_buf[0], key);
	for (msg_index = 1; msg_index < octet_count; msg_index++)
	{
		msg_buf[msg_index] = etbox(msg_buf[msg_index], key);
		k ^= msg_buf[msg_index];
	}

	msg_buf[0] = k;
	for (msg_index = 1; msg_index < octet_count; msg_index++)
		msg_buf[msg_index] ^= k ;

}

/* Inverse Transformation */

void inv_transform(unsigned char *msg_buf, const int octet_count,
                   unsigned char offseta, const unsigned char offsetb,
                   const unsigned char *key)
{
	unsigned char k, z;
	int msg_index;
	
	/* initial offseta rotation */
	
	k = (octet_count - 1) & 0x07;
	offseta = (offseta >> k) | (offseta << (8 - k));

	/* inverse of final involution and XORing */

	for (msg_index = 1; msg_index < octet_count; msg_index++)
		msg_buf[msg_index] ^= msg_buf[0];

	for (msg_index = 1; msg_index < octet_count; msg_index++)
	{
		msg_buf[0] ^= msg_buf[msg_index];
		msg_buf[msg_index] = etbox(msg_buf[msg_index], key);
	}
	msg_buf[0] = etbox(msg_buf[0], key);
	
	/* initial octet permutation */
	/* exchange last octet with a random one below it */
	
	k = etbox((unsigned char)(0x37 ^ offseta), key);
	k = ((octet_count) * k) >> 8;
	z = msg_buf[k];
	msg_buf[k] = msg_buf[octet_count - 1];
	msg_buf[octet_count - 1] = z;
	
	for (msg_index = octet_count - 1; msg_index >= 0; msg_index--)
	{
		/* random octet permutation */
		/* exchange previous octet with a random one below it */
		
		if (msg_index > 1)
		{
			k = etbox((unsigned char)(msg_buf[msg_index] ^ offseta), 
				key);
			k = ((msg_index) * k) >> 8;
			z = msg_buf[k];
			msg_buf[k] = msg_buf[msg_index - 1];
			msg_buf[msg_index - 1] = z;
		}
		
		/* bit-trade between present octet and the one below */
		
		if (msg_index > 0)
		{
			k = msg_buf[msg_index - 1] ^ msg_buf[msg_index];
			k &= etbox((unsigned char)(k ^ offseta), key);
			msg_buf[msg_index - 1] ^= k;
			msg_buf[msg_index] ^= k;
		}
		
		/* involutary lookup of present octet and offset rotation */
		
		msg_buf[msg_index] = offseta ^ 
			etbox((unsigned char)(msg_buf[msg_index] ^ offsetb), key);
		offseta = (offseta << 1) | (offseta >> 7);
	}
}

