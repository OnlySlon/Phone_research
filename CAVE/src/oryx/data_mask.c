//#define ORYX_SOURCE_FILE // From oryx.c
#include "cavei.h"       // From oryx.c
#include "oryx.h"        // From oryx.c
/* Data_Mask has the same header as DataKey_Generation 
   (see Exhibit  2 -46) */

void Data_Mask(const unsigned long DataKey, 
               const unsigned long HOOK, 
               const int len, 
               unsigned char mask[] )
{
	int i;
	
	K = (unsigned long)L[HOOK&0xff];
	K += ((unsigned long)L[((HOOK>>8)+HOOK)&0xff])<<8;
	K += ((unsigned long)L[((HOOK>>16)+HOOK)&0xff])<<16;
	K += ((unsigned long)L[((HOOK>>24)+HOOK)&0xff])<<24;
	kstep(); A = DataKey ^ K; /* kstep() is defined in Exhibit  2 -45 */
	kstep(); B = DataKey ^ K;
	kstep(); K = DataKey ^ K;
	
	for(i=0; i<len; i++)
		mask[i] = keygen(); /* keygen() is defined in Exhibit  2 -45 */
}
