//#define WRE_SOURCE_FILE // From wre.c
#include "cavei.h"      // From wre.c
#include "wre.h"        // From wre.c
/* WI_Auth_Signature has the same header as WIKEY_Generation (see Exhibit  2 -34) */

/* Note that PBID is right justified.  This means that the 2 MSBs of PBID 
   must be set to 0 by the calling routine. */

unsigned long WI_Auth_Signature(const unsigned char RAND_CHALLENGE[4],
                                const unsigned char PBID[4],
                                const unsigned char ACRE_PHONE_NUMBER[3])
{
   int i,offset_1,offset_2;
   unsigned long AUTH_SIGNATURE;

   for (i = 0; i < 4; i++)
      LFSR[i] = RAND_CHALLENGE[i] ^ WIKEY[i] ^ WIKEY[i+4];
   if ((LFSR[0] | LFSR[1] | LFSR[2] | LFSR[3]) == 0)
      for (i = 0; i < 4; i++)
         LFSR[i] = RAND_CHALLENGE[i];
   for (i = 0; i < 8; i++)
      Register[i] = WIKEY[i];
   Register[8] = AAV;
   for (i = 0; i < 3; i++)
      Register[i+9] = ACRE_PHONE_NUMBER[i];
   for (i = 0; i < 4; i++)
      Register[i+12] = PBID[i];
   offset_1 = offset_2 = 128;
   CAVE(8, &offset_1, &offset_2);
   AUTH_SIGNATURE =
      (  ((unsigned long)(Register[0] ^ Register[13]) << 16) +
         ((unsigned long)(Register[1] ^ Register[14]) << 8)  +
         ((unsigned long)(Register[2] ^ Register[15]) )        )
      & 0x3ffff;
   return(AUTH_SIGNATURE);
}
