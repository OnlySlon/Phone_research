void WIKEY_Generation(const unsigned char MANUFACT_KEY[16],
                      const unsigned char PBID[4]);

void WIKEY_Update(const unsigned char RANDWIKEY[7],
                  const unsigned char PBID[4]);

unsigned long WI_Auth_Signature(const unsigned char RAND_CHALLENGE[4],
                                const unsigned char PBID[4],
                                const unsigned char ACRE_PHONE_NUMBER[3]);

unsigned long WRE_Auth_Signature(const unsigned char RAND_WRE[3],
                                 const unsigned char PBID[4],
                                 const unsigned char ESN[4]);

#ifndef WRE_SOURCE_FILE
extern
unsigned char		WIKEY[8];
extern
unsigned char		WIKEY_NEW[8];
extern
unsigned char		WRE_KEY[8];
#endif
