/* SCEMA Header File "scema.h" */

/* Key schedule architecture */

typedef struct _key_sched {
	unsigned char *scemaKey;
	unsigned int *obox;
	unsigned int *offKey;
	unsigned char neededLength;
} keySched;

keySched dtcScheds[];

keySched dcchScheds[];


/* SCEMA procedure/function declarations */

void DTC_Key_Generation(void);

void DCCH_Key_Generation(void);

void SCEMA_Secret_Generation(keySched *schedPtr);

void SCEMA(unsigned char *msg_buf,
           const int octet_count,
           const unsigned char *csync,
		   const unsigned char id,
		   const unsigned char idMask,
           const unsigned int decrypt,
           keySched *schedPtr);

void SCEMA_KSG(unsigned char *keystreamBuf,
				const unsigned int requestedStreamLen,
				const unsigned char *inputBuf,
				const unsigned int inputLen,
				const unsigned char contentType,
				keySched *schedPtr,
				const unsigned int direction);

void Long_Block_Encryptor(unsigned char *contentBuf,
							const unsigned char contentType,
							const unsigned int decrypt,
							keySched *schedPtr,
							const unsigned int direction);

void Short_Block_Encryptor(unsigned char *contentBuf,
					const unsigned int numBits,
					const unsigned char contentType,
					const unsigned char *entropy,
							const unsigned int decrypt,
							keySched *schedPtr,
							const unsigned int direction);

void Enhanced_Message_Encryption(unsigned char *msgBuf,
							const unsigned int numBits,
							const unsigned int dcchDTC,
							const unsigned char *rand,
							const unsigned char msgType,
							const unsigned int decrypt,
							const unsigned int keyGenerator,
							const unsigned int direction);

void Enhanced_Voice_Privacy(const unsigned int coderVer,
							unsigned char *speechBuf1,
							const unsigned int num1aBits,
							unsigned char *speechBufRem,
							const unsigned int numRemBits,
							const unsigned int decrypt,
							const unsigned int keyGenerator,
							const unsigned int direction);

void Enhanced_Data_Mask(unsigned char *mask,
						const unsigned long HOOK,
						const unsigned int len,
						const unsigned int keyGenerator);

/* Encryption mode of SCEMA */

#define ENCRYPTING	0
#define DECRYPTING	1

/* Blocksize of plaintext (or ciphertext) */
#define ThreeOctets	3
#define SixOctets	6
#define EightOctets	8

/* Long Block Definitions
Note: The LongBlockArchitecture identity segment forces a one into bit 2
of SCEMA's cryptosync top octet to differentiate the Long Block Encryptor from all other KSG-type encryptors.
*/

#define LongBlkIdMask			0xFF
#define LongBlockArchitecture	0x04

/* KSG, RLP, and Short Block Definitions
Note: The LongBlockArchitecture identity segment forces a zero into bit 2 of SCEMA's cryptosync top octet.
*/
#define KSGIdMask		0x04
#define KSGArchitecture	0x00

/* Content Types */
#define VoiceContent	0x00
#define MessageContent	0x10
#define RlpContent		0x20

/* Direction */
#define ForwardChannel 1
#define ReverseChannel 0

/* Instances */
#define Instance1 0x01
#define Instance2 0x02
#define Instance3 0x03

/* DCCH/DTC */
#define DCCH 0
#define DTC 1

/* Message Types */
#define TestMsgType 0x1A
#define TestMsgType2 0x09

/* Used in SCEMA transforms */
#define OFFSETA ((unsigned char)(*offInt & 0xFF))
#define OFFSETB ((unsigned char)((*offInt >> 8) & 0xFF))

/* Miscellaneous */
#define MaxFrameOctetSize	35 /* 278 bits */
#define MaxMessageOctetSize	256 /* 2048 bits */
#define CAVEKey1			1
#define CoderVersionZero	0

#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define MIN(A,B) ((A) < (B) ? (A) : (B))

unsigned int offsetInt[2];

/* Key length determination and individual key schedule architectures
Note: NeededLength must be <= length of scemaKey to prevent
stbox() overflow, and should be >= the key schedule entropy.
Also, it must be even.

If a key schedule of a different strength is required in the future,
replicate the below with "CK1" replaced by the appropriate designator.
*/
/*  CaveKey1 */
#define ScemaKeyLengthCK1 8
#define	NeededLengthCK1 8

#if NeededLengthCK1 > ScemaKeyLengthCK1
	#error NeededLengthCK1 too large
#endif

#if NeededLengthCK1 % 2
	#error NeededLengthCK1 must be an even number
#endif
