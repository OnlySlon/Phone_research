/* SCEMA DTC Key Generation "dtcKeyGen.c" */

#include "scema.h" /* see Exhibit  2 -53 */

/*
dtcScheds[0] accesses DTC CaveKey1 schedule.
*/

unsigned char	dtcScemaKeyCK1[ScemaKeyLengthCK1];
unsigned int	dtcOboxCK1[16];
unsigned int	dtcOffKeyAuxCK1[2];

keySched dtcScheds[] = {
	{dtcScemaKeyCK1, dtcOboxCK1, dtcOffKeyAuxCK1, NeededLengthCK1},
};


void DTC_Key_Generation(void)
{
	SCEMA_Secret_Generation(dtcScheds);
}

/*
Note: If a key schedule of a different strength is required in the future,
the following can serve as an example:

/.
dtcScheds[0] will access DTC CaveKey1 schedule.
dtcScheds[1] will access DTC TBD Key2 schedule.
./

unsigned char	dtcScemaKeyCK1[ScemaKeyLengthCK1];
unsigned int	dtcOboxCK1[16];
unsigned int	dtcOffKeyAuxCK1[2];

unsigned char	dtcScemaKeyTbdK2[ScemaKeyLengthTbdK2];
unsigned int	dtcOboxTbdK2[16];
unsigned int	dtcOffKeyAuxTbdK2[2];

keySched dtcScheds[] = {
	{dtcScemaKeyCK1, dtcOboxCK1, dtcOffKeyAuxCK1, NeededLengthCK1},
	{dtcScemaKeyTbdK2, dtcOboxTbdK2, dtcOffKeyAuxTbdK2, NeededLengthTbdK2}
};
*/

