//#define WRE_SOURCE_FILE // From wre.c
#include "cavei.h"      // From wre.c
#include "wre.h"        // From wre.c
/* WIKEY_Update has the same header as WIKEY_Generation (see Exhibit  2 -34) */

/* Note that PBID is right justified.  This means that the 2 MSBs of PBID 
   must be set to 0 by the calling routine. */

void WIKEY_Update(const unsigned char RANDWIKEY[7],
                  const unsigned char PBID[4])
{
   int i,offset_1,offset_2;

   for (i = 0; i < 4; i++)
      LFSR[i] = RANDWIKEY[i+3] ^ WIKEY[i] ^ WIKEY[i+4];
   if ((LFSR[0] | LFSR[1] | LFSR[2] | LFSR[3]) == 0)
      for (i = 0; i < 4; i++)
         LFSR[i] = RANDWIKEY[i+3];
   for (i = 0; i < 8; i++)
      Register[i] = WIKEY[i];
   Register[8] = AAV;
   for (i = 0; i < 3; i++)
      Register[i+9] = RANDWIKEY[i];
   for (i = 0; i < 4; i++)
      Register[i+12] = PBID[i];
   offset_1 = offset_2 = 128;
   CAVE(8, &offset_1, &offset_2);
   for (i = 0; i < 8; i++)
      WIKEY_NEW[i] = Register[i] ^ Register[i+8];
}
