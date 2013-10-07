#define ECMEA_SOURCE_FILE
#include "cavei.h"  /* see Exhibit  2 -3 */
#include "ecmea.h"  /* see Exhibit  2 -29 */

#define MOBILE 1 /* set to 0 for base station algorithm */

void ECMEA(unsigned char *msg_buf, const int octet_count,
           const unsigned char sync[2],
           const unsigned int decrypt,
           const unsigned int data_type)
{
	unsigned char k, z, offset1, offset2, offsetc;
	unsigned long x1, x2, s;
	int msg_index;
	unsigned char *key, *offset;

	/* select key and offset key */
	if (data_type)
	{
		key = ecmea_nf_key;
		offset = offset_nf_key;
	}
	else
	{
		key = ecmea_key;
		offset = offset_key;
	}
	
	/* calculate offsets */
	/* offset12 = 
		((offset[1,0]+1)*(CS+1) mod 65537)^offset[3,2] mod 65536 */
	x1 = ((unsigned long)offset[1] << 8) + (unsigned long)offset[0];
	x2 = ((unsigned long)offset[3] << 8) + (unsigned long)offset[2];
	s = ((unsigned long)sync[1] << 8) + (unsigned long)sync[0];
	/* x1 = (((x1 + 1) * (s + 1)) % 65537) ^ x2; in two steps to 
		prevent overflow */
	x1 = (x1 * (s + 1)) % 65537;
	x1 = ((x1 + s + 1) % 65537) ^ x2;
	offset1 = (unsigned char) (x1 >> 8);
	offset2 = (unsigned char) (offset1 ^ x1);
	if (offset2 == offset1)
		offset2 ^= 1;

#if MOBILE

	if (decrypt)
		offsetc = offset2;
	else
		offsetc = offset1;

#else

	if (decrypt)
		offsetc = offset1;
	else
		offsetc = offset2;

#endif
	
	/* initial transformation */
#if MOBILE
	transform(msg_buf, octet_count, offset1, offset2, key);
#else
	transform(msg_buf, octet_count, offset2, offset1, key);
#endif
	
	/* CMEA */
	/* first manipulation (inverse of third) */
	z = 0;
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		k = etbox((unsigned char)(z ^ offsetc), key);
		msg_buf[msg_index] += k;
		z = msg_buf[msg_index];
	}
	
	/* second manipulation (self-inverse) */
	for (msg_index = 0; msg_index < octet_count - 1; msg_index += 2)
		msg_buf[msg_index] ^= msg_buf[msg_index + 1];
	
	/* third manipulation (inverse of first) */
	z = 0;
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		k = etbox((unsigned char)(z ^ offsetc), key);
		z = msg_buf[msg_index];
		msg_buf[msg_index] -= k;
	}
	
	/* final inverse transformation */
#if MOBILE
	inv_transform(msg_buf, octet_count, offset2, offset1, key);
#else
	inv_transform(msg_buf, octet_count, offset1, offset2, key);
#endif
}
