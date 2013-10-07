/* internal header for CAVE, used by all cryptographic source files */

#include "cave.h" /* see Exhibit  2 -2 */

/* authentication algorithm version (fixed) */

#define AAV 0xC7

#define LOMASK       0x0F
#define HIMASK       0xF0
#define TRUE         1
#define FALSE        0

/* NAM stored data */

extern
unsigned char		ESN[4];

extern
unsigned char 		A_key[8];

extern
unsigned char		SSD_A_NEW[8], SSD_A[8];

extern
unsigned char		SSD_B_NEW[8], SSD_B[8];

/* saved outputs */

CAVE_GLOBAL
unsigned char 		LFSR[4];

#define LFSR_A LFSR[0]
#define LFSR_B LFSR[1]
#define LFSR_C LFSR[2]
#define LFSR_D LFSR[3]

CAVE_GLOBAL
unsigned char		Register[16];




