#define WRE_SOURCE_FILE
#include "cavei.h"  /* see Exhibit  2 -3 */
#include "wre.h"    /* see Exhibit  2 -31 */

unsigned char		WIKEY[8];
unsigned char		WIKEY_NEW[8];
unsigned char		WRE_KEY[8];

/* Note that MANUFACT_KEY is left justified and PBID is right justified.
   This means that the 6 LSBs of MANUFACT_KEY and the 2 MSBs of PBID
   must be set to 0 by the calling routine. */

void WIKEY_Generation(const unsigned char MANUFACT_KEY[16],
                      const unsigned char PBID[4])
{
   int i,offset_1,offset_2;

   for (i = 0; i < 4; i++)
      LFSR[i] = MANUFACT_KEY[i];
   for (i = 0; i < 8; i++)
      Register[i] = MANUFACT_KEY[i+4];
   Register[8] = AAV;
   for (i = 0; i < 4; i++)
      Register[i+9] = MANUFACT_KEY[i+12];
   Register[12] = Register[12] | PBID[0];
   for (i = 0; i < 3; i++)
      Register[i+13] = PBID[i+1];
   offset_1 = offset_2 = 128;
   CAVE(8, &offset_1, &offset_2);
   for (i = 0; i < 8; i++)
      WIKEY[i] = Register[i] ^ Register[i+8];
}

