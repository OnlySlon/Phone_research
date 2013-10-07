/* SCEMA DCCH Key Generation "dcchKeyGen.c" */

#include "scema.h" /* see Exhibit  2 -53 */

/*
dcchScheds[0] accesses DCCH CaveKey1 schedule.
*/

unsigned char	dcchScemaKeyCK1[ScemaKeyLengthCK1];
unsigned int	dcchOboxCK1[16];
unsigned int	dcchOffKeyAuxCK1[2];

keySched dcchScheds[] = {
	{dcchScemaKeyCK1, dcchOboxCK1, dcchOffKeyAuxCK1, NeededLengthCK1},
};


void DCCH_Key_Generation(void)
{
	SCEMA_Secret_Generation(dcchScheds);
}


/*
Note: If a key schedule of a different strength is required in the future,
see the example in dtcKeyGen.c.
*/

