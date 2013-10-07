unsigned long DataKey_Generation(void);

void LTable_Generation(const unsigned char [] );

void Data_Mask(const unsigned long , 
               const unsigned long , 
               const int , 
               unsigned char []);

#ifdef ORYX_SOURCE_FILE
#define ORYX_GLOBAL
#else
#define ORYX_GLOBAL extern
#endif
