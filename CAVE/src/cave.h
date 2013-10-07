#ifndef CAVE_H
#define CAVE_H

/* external header for CAVE and related procedures */

/* function declarations */

void CAVE(const int number_of_rounds,
          int *offset_1,
          int *offset_2);
          
void A_Key_Checksum(const char A_KEY_DIGITS[20], 
                    char A_KEY_CHECKSUM[6]);

int A_Key_Verify(const char A_KEY_DIGITS[26]);

void SSD_Generation(const unsigned char RANDSSD[7]);

void SSD_Update(void);

unsigned long Auth_Signature(const unsigned char RAND_CHALLENGE[4],
                             const unsigned char AUTH_DATA[3],
                             const unsigned char *SSD_AUTH,
                             const int SAVE_REGISTERS);

void Key_VPM_Generation(void);

void CMEA(unsigned char *msg_buf, const int octet_count);

/* global variable definitions */

#ifdef CAVE_SOURCE_FILE
#define CAVE_GLOBAL
#else
#define CAVE_GLOBAL extern
#endif

/* externally available results */

CAVE_GLOBAL
unsigned char		cmeakey[8];

CAVE_GLOBAL
unsigned char		VPM[65];

CAVE_GLOBAL
unsigned char		SAVED_LFSR[4];
CAVE_GLOBAL
int					SAVED_OFFSET_1;
CAVE_GLOBAL
int					SAVED_OFFSET_2;
CAVE_GLOBAL
unsigned char		SAVED_RAND[4];
CAVE_GLOBAL
unsigned char		SAVED_DATA[3];



/* global constant definitions */

#ifndef CAVE_SOURCE_FILE

CAVE_GLOBAL
unsigned char		CaveTable[256];

CAVE_GLOBAL
unsigned char		ibox[256];

#endif // ifndef CAVE_SOURCE_FILE

#endif // ifndef CAVE_H

/* end of CAVE external header */
/********************************************************************/
