//#define ECMEA_SOURCE_FILE // From ecmea.c
#include "cavei.h"        // From ecmea.c
#include "ecmea.h"        // From ecmea.c
/* enhanced tbox has the same header as ECMEA (see Exhibit  2 -30) */

unsigned char etbox(const unsigned char z, 
const unsigned char *ecmea_key)
{
	
	unsigned char t;
	
	t = ibox[(z + ecmea_key[0]) & 0xff];
	t = ibox[t ^ ecmea_key[1]];
	t = ibox[(t + ecmea_key[2]) & 0xff];
	t = ibox[t ^ ecmea_key[3]];
	t = ibox[(t + ecmea_key[4]) & 0xff];
	t = ibox[t ^ ecmea_key[5]];
	t = ibox[(t + ecmea_key[6]) & 0xff];
	t = ibox[t ^ ecmea_key[7]];
	t = ibox[(t - ecmea_key[6]) & 0xff];
	t = ibox[t ^ ecmea_key[5]];
	t = ibox[(t - ecmea_key[4]) & 0xff];
	t = ibox[t ^ ecmea_key[3]];
	t = ibox[(t - ecmea_key[2]) & 0xff];
	t = ibox[t ^ ecmea_key[1]];
	t = (t - ecmea_key[0]) & 0xff;
	
	return t;
}
