void ECMEA_Secret_Generation(void);

void Non_Financial_Seed_Key_Generation(void);

void Non_Financial_Secret_Generation(void);

void ECMEA(unsigned char *msg_buf,
           const int octet_count,
           const unsigned char sync[2],
           const unsigned int decrypt,
           const unsigned int data_type);

#ifdef ECMEA_SOURCE_FILE
#define ECMEA_GLOBAL
#else
#define ECMEA_GLOBAL extern
#endif

ECMEA_GLOBAL
unsigned char		ecmea_key[8];
ECMEA_GLOBAL
unsigned char		ecmea_nf_key[8];
ECMEA_GLOBAL
unsigned char		offset_key[4];
ECMEA_GLOBAL
unsigned char		offset_nf_key[4];
ECMEA_GLOBAL
unsigned char		seed_nf_key[5];
