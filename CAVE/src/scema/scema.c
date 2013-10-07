/* SCEMA source including transforms and stbox "scema.c" */

#include "cave.h" /* see Exhibit 2-2 */
#include "scema.h" /* see Exhibit 2-53 */

/* Stbox function
Note: The SCEMA Key Length must be an even number of octets.
The "-1" in the first "while" statement prevents overflow if
ScemaKeyLength is accidentally odd. 
*/

unsigned char stbox(const unsigned char z, 
					const unsigned char *scema_key,
					const unsigned char len)
{
	unsigned char t = z;
	int i = 0;

	while(i < len - 1)
	{
		t = ibox[(t + scema_key[i++]) & 0xff];
		t = ibox[t ^ scema_key[i++]];
	}

	--i;
		
	while(i > 1)
	{
		t = ibox[(t - scema_key[--i]) & 0xff];
		t = ibox[t ^ scema_key[--i]];
	}

	t = (t - scema_key[--i]) & 0xff;
	return t;
}


/* Transformation */

void SCEMA_transform(unsigned char *msg_buf, const int octet_count,
					 unsigned int *offInt, const unsigned char *key,
					 const unsigned int *obox, const unsigned char len)
{
	unsigned char k, z;
	int msg_index;
		
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
	/* offset generator cycle and involutary lookup of present octet */
		
		offsetInt[0] += offsetInt[1] + obox[offsetInt[1] & 0x0F];
		offsetInt[1] ^= 
			((offsetInt[0] & 0xFFFF)>>4) + (offsetInt[0]<<4);
	
		msg_buf[msg_index] = OFFSETB ^ 
			stbox((unsigned char)(msg_buf[msg_index] ^ OFFSETA), 
				key, len);
		
		/* bit-trade between present octet and the one below */
		
		if (msg_index > 0)
		{
			k = msg_buf[msg_index - 1] ^ msg_buf[msg_index];
			k &= stbox((unsigned char)(k ^ OFFSETA), key, len);
			msg_buf[msg_index - 1] ^= k;
			msg_buf[msg_index] ^= k;
		}
		
		/* random octet permutation */
		/* exchange previous octet with a random one below it */
		
		if (msg_index > 1)
		{
			k = stbox((unsigned char)(msg_buf[msg_index] ^ OFFSETA), 
				key, len);
			k = ((msg_index) * k) >> 8;
			z = msg_buf[k];
			msg_buf[k] = msg_buf[msg_index - 1];
			msg_buf[msg_index - 1] = z;
		}
	}
	
	/* final octet permutation */
	/* exchange last octet with a random one below it */
	
	k = stbox((unsigned char)(0x37 ^ OFFSETA), key, len);
	k = ((msg_index) * k) >> 8;
	z = msg_buf[k];
	msg_buf[k] = msg_buf[msg_index - 1];
	msg_buf[msg_index - 1] = z;

 	/* final involution and XORing */

	k = stbox(msg_buf[0], key, len);
	for (msg_index = 1; msg_index < octet_count; msg_index++)
	{
		msg_buf[msg_index] = stbox(msg_buf[msg_index], key, len);
		k ^= msg_buf[msg_index];
	}

	msg_buf[0] = k;
	for (msg_index = 1; msg_index < octet_count; msg_index++)
		msg_buf[msg_index] ^= k ;

}

/* Inverse Transformation */

void SCEMA_inv_transform(unsigned char *msg_buf, 
								 const int octet_count,
						 		 unsigned int *offInt, 
								 const unsigned char *key,
						 		 const unsigned int *obox, 
								 const unsigned char len)
{
	unsigned char k, z;
	int msg_index;
	
	/* inverse of final involution and XORing */

	for (msg_index = 1; msg_index < octet_count; msg_index++)
		msg_buf[msg_index] ^= msg_buf[0];

	for (msg_index = 1; msg_index < octet_count; msg_index++)
	{
		msg_buf[0] ^= msg_buf[msg_index];
		msg_buf[msg_index] = stbox(msg_buf[msg_index], key, len);
	}
	msg_buf[0] = stbox(msg_buf[0], key, len);
	
	/* initial octet permutation */
	/* exchange last octet with a random one below it */
	
	k = stbox((unsigned char)(0x37 ^ OFFSETA), key, len);
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
			k = stbox((unsigned char)(msg_buf[msg_index] ^ OFFSETA), 
				key, len);
			k = ((msg_index) * k) >> 8;
			z = msg_buf[k];
			msg_buf[k] = msg_buf[msg_index - 1];
			msg_buf[msg_index - 1] = z;
		}
		
		/* bit-trade between present octet and the one below */
		
		if (msg_index > 0)
		{
			k = msg_buf[msg_index - 1] ^ msg_buf[msg_index];
			k &= stbox((unsigned char)(k ^ OFFSETA), key, len);
			msg_buf[msg_index - 1] ^= k;
			msg_buf[msg_index] ^= k;
		}
		
	/* involutary lookup of present octet and offset generator cycle */
		
		msg_buf[msg_index] = OFFSETA ^ 
			stbox((unsigned char)(msg_buf[msg_index] ^ OFFSETB), 
				key, len);
		
		offsetInt[1] ^= 
			((offsetInt[0] & 0xFFFF)>>4) + (offsetInt[0]<<4);
		offsetInt[0] -= offsetInt[1] + obox[offsetInt[1] & 0x0F];
	}
}

/* SCEMA Algorithm */

void SCEMA(unsigned char *msg_buf,
				const int octet_count,
				const unsigned char *csync,
				const unsigned char id,
				const unsigned char idMask,
				const unsigned int decrypt,
				keySched *schedPtr)
{
	unsigned char k, z, offsetc;
	int msg_index;
	unsigned char *key;
	unsigned int *obox, *offKeyAux;
	unsigned char len;
	unsigned char csync3id;
	unsigned int csyncInt[2];

	/* load key schedule element pointers */
	
	key = schedPtr->scemaKey;
	obox = schedPtr->obox;
	offKeyAux = schedPtr->offKey;
	len = schedPtr->neededLength;
	
	 	
	/* Offset Generator Initialization */

	csync3id = (csync[3] & ~idMask) | (id & idMask);

	csyncInt[0] = (unsigned int)((csync[1] << 8) | (csync[0] & 0xFF));
	csyncInt[1] = (unsigned int)((csync3id << 8) | (csync[2] & 0xFF));

	offsetInt[0] = csyncInt[1] + offKeyAux[0];
	offsetInt[1] = csyncInt[0] + offKeyAux[1];

	offsetInt[0] += obox[offsetInt[1] & 0x0F] 
					+ obox[(offsetInt[1] >> 4) & 0x0F]
					+ obox[(offsetInt[1] >> 8) & 0x0F]
					+ obox[(offsetInt[1] >> 12) & 0x0F] ;

	offsetInt[1] += obox[offsetInt[0] & 0x0F] 
					+ obox[(offsetInt[0] >> 4) & 0x0F]
					+ obox[(offsetInt[0] >> 8) & 0x0F]
					+ obox[(offsetInt[0] >> 12) & 0x0F] ;

	/* initial transformation */
	if (decrypt)
		SCEMA_transform(msg_buf, octet_count, offsetInt + 1, key, 
			obox, len);
	else
		SCEMA_transform(msg_buf, octet_count, offsetInt, key, obox, len);

	
	/* CMEA */
	offsetc = (unsigned char)((offsetInt[0] + offsetInt[1]) & 0xFF);
	/* first manipulation (inverse of third) */
	z = 0;
	for (msg_index = 0; msg_index < octet_count; msg_index++)
	{
		k = stbox((unsigned char)(z ^ offsetc), key, len);
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
		k = stbox((unsigned char)(z ^ offsetc), key, len);
		z = msg_buf[msg_index];
		msg_buf[msg_index] -= k;
	}
	
	/* final inverse transformation */
	if (decrypt)
		SCEMA_inv_transform(msg_buf, octet_count, offsetInt, key, 
			obox, len);
	else
		SCEMA_inv_transform(msg_buf, octet_count, offsetInt + 1, key, 
			obox, len);
}
