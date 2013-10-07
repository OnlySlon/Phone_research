//#define WRE_SOURCE_FILE // From wre.c
#include "cavei.h"      // From wre.c
#include "wre.h"        // From wre.c
/* WRE_Auth_Signature has the same header as WIKEY_Generation (see Exhibit  2 -34) */

/* Note that RAND_WRE is left justified and PBID is right justified.
   This means that the 5 LSBs of RAND_WRE and the 2 MSBs of PBID 
   must be set to 0 by the calling routine. */

unsigned long WRE_Auth_Signature(const unsigned char RAND_WRE[3],
                                 const unsigned char PBID[4],
                                 const unsigned char ESN[4])
{
   int i,offset_1,offset_2;
   unsigned long AUTH_SIGNATURE;

   for (i = 0; i < 3; i++)
      LFSR[i] = RAND_WRE[i];
   LFSR[2] = LFSR[2] | (PBID[2] & 0x1F);
   LFSR[3] = PBID[3];
   for (i = 0; i < 4; i++)
      LFSR[i] = LFSR[i] ^ WRE_KEY[i] ^ WRE_KEY[i+4];
   if ((LFSR[0] | LFSR[1] | LFSR[2] | LFSR[3]) == 0)
   {
     for (i = 0; i < 3; i++)
        LFSR[i] = RAND_WRE[i];
     LFSR[2] = LFSR[2] | (PBID[2] & 0x1F);
     LFSR[3] = PBID[3];
   }
   for (i = 0; i < 8; i++)
      Register[i] = WRE_KEY[i];
   Register[8] = AAV;
   for (i = 0; i < 3; i++)
      Register[i+9] = PBID[i];
   for (i = 0; i < 4; i++)
      Register[i+12] = ESN[i];
   offset_1 = offset_2 = 128;
   CAVE(8, &offset_1, &offset_2);
   AUTH_SIGNATURE =
      (  ((unsigned long)(Register[0] ^ Register[13]) << 16) +
         ((unsigned long)(Register[1] ^ Register[14]) << 8)  +
         ((unsigned long)(Register[2] ^ Register[15]) )        )
      & 0x3ffff;
   return(AUTH_SIGNATURE);
}

