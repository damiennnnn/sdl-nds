/*---------------------------------------------------------------------------------
	$Id: template.c,v 1.2 2005/09/07 20:06:06 wntrmute Exp $

	Simple ARM7 stub (sends RTC, TSC, and X/Y data to the ARM 9)

	$Log: template.c,v $
	Revision 1.2  2005/09/07 20:06:06  wntrmute
	updated for latest libnds changes
	
	Revision 1.8  2005/08/03 05:13:16  wntrmute
	corrected sound code


---------------------------------------------------------------------------------*/
#include <nds.h>

#include <nds/bios.h>
#include <nds/arm7/touch.h>
#include <nds/arm7/clock.h> 

#include "../../spcme.h"
#include <nds/ipc.h>
// Play buffer, left buffer is first MIXBUFSIZE * 2 u16's, right buffer is next
s8 playBuffer[0x5000 * 2];
int MIXBUFSIZE;
int MIXRATE;
int soundCursor;
bool paused = false;

void SetupSound() {
	MIXBUFSIZE=SPC_IPC->MIXBUFSIZE;
	MIXRATE=SPC_IPC->MIXRATE;
    soundCursor = 0;//MIXBUFSIZE;
    powerON(POWER_SOUND);
    SOUND_CR = SOUND_ENABLE | SOUND_VOL(0x7F);

        int channel =  0 ;//? 0 : 1;
        SCHANNEL_TIMER(channel) = SOUND_FREQ(MIXRATE);
        SCHANNEL_SOURCE(channel) = (uint32)&(playBuffer[0]);
        SCHANNEL_LENGTH(channel) =  (MIXBUFSIZE * 2) >> 2;
        SCHANNEL_REPEAT_POINT(channel) = 0;
        SCHANNEL_CR(channel) = SCHANNEL_ENABLE | SOUND_REPEAT | SOUND_VOL(0x7F) | SOUND_PAN(64) | SOUND_8BIT;

    TIMER0_DATA = SOUND_FREQ(MIXRATE) * 2;
    TIMER0_CR = TIMER_DIV_1 | TIMER_ENABLE;

    TIMER1_DATA = 0x10000 - MIXBUFSIZE;
    TIMER1_CR = TIMER_CASCADE | TIMER_IRQ_REQ | TIMER_ENABLE;
}

void StopSound() {
    powerOFF(POWER_SOUND);
    SOUND_CR = 0;
    TIMER0_CR = 0;
    TIMER1_CR = 0;
	
}

inline void SendArm9Command(u32 command) {
    REG_IPC_FIFO_TX = command;
}


void TIMER1Handler(void) {

		soundCursor = MIXBUFSIZE - soundCursor;

        SPC_IPC->curCommand = REG_IPC_FIFO_CR;
        for (int i = 0; i < MIXBUFSIZE; i++) {
            playBuffer[soundCursor + i] = SPC_IPC->playBuffer[i];
        }

		if (REG_IPC_FIFO_CR & IPC_FIFO_ERROR) REG_IPC_FIFO_CR |= IPC_FIFO_SEND_CLEAR;
			SendArm9Command(ARM9COMMAND_UPDATE_APU);

}


void FIFO_Receive() {

            u32 command = REG_IPC_FIFO_RX;

            // Command received from the ARM9, let's check what it is
            switch (command) {
            case ARM7COMMAND_START_SOUND:
                SetupSound();
                break;
            case ARM7COMMAND_STOP_SOUND:
                StopSound();
                SPC_IPC->arm7State = ARM7STATE_WAITING;
                break;
            }
        //REG_IF = IRQ_FIFO_NOT_EMPTY;


}

//---------------------------------------------------------------------------------
void VblankHandler(void) {
//---------------------------------------------------------------------------------
	static int heartbeat = 0;

	uint16 but=0, x=0, y=0, xpx=0, ypx=0, z1=0, z2=0, batt=0, aux=0;
	int t1=0, t2=0;
	uint32 temp=0;
	uint8 ct[sizeof(IPC->curtime)];
	u32 i;

	// Update the heartbeat
	heartbeat++;

	// Read the touch screen

	but = REG_KEYXY;

	if (!(but & (1<<6))) {

		touchPosition tempPos = touchReadXY();

		x = tempPos.x;
		y = tempPos.y;
		xpx = tempPos.px;
		ypx = tempPos.py;
	}

	z1 = touchRead(TSC_MEASURE_Z1);
	z2 = touchRead(TSC_MEASURE_Z2);

	
	batt = touchRead(TSC_MEASURE_BATTERY);
	aux  = touchRead(TSC_MEASURE_AUX);

	// Read the time
	rtcGetTime((uint8 *)ct);
	BCDToInteger((uint8 *)&(ct[1]), 7);

	// Read the temperature
	temp = touchReadTemperature(&t1, &t2);

	// Update the IPC struct
	IPC->heartbeat	= heartbeat;
	IPC->buttons		= but;
	IPC->touchX			= x;
	IPC->touchY			= y;
	IPC->touchXpx		= xpx;
	IPC->touchYpx		= ypx;
	IPC->touchZ1		= z1;
	IPC->touchZ2		= z2;
	IPC->battery		= batt;
	IPC->aux			= aux;

	for(i=0; i<sizeof(ct); i++) {
		IPC->curtime[i] = ct[i];
	}

	IPC->temperature = temp;
	IPC->tdiode1 = t1;
	IPC->tdiode2 = t2;


	/*sound code  :)
	TransferSound *snd = IPC->soundData;
	IPC->soundData = 0;

	if (0 != snd) {

		for (i=0; i<snd->count; i++) {
			s32 chan = getFreeSoundChannel();

			if (chan >= 0) {
				startSound(snd->data[i].rate, snd->data[i].data, snd->data[i].len, chan, snd->data[i].vol, snd->data[i].pan, snd->data[i].format);
			}
		}
	}
	*/
}

//---------------------------------------------------------------------------------
int main(int argc, char ** argv) {
//---------------------------------------------------------------------------------

	// Reset the clock if needed
	rtcReset();

    //for (int i = 0; i < MIXBUFSIZE * 2; i++) {
    //    playBuffer[i] = 0;
    //}

	// Initialise the interrupt system
	irqInit();
	// install our simple vblank handler
	irqSet(IRQ_FIFO_NOT_EMPTY, FIFO_Receive);
	// enable the interrupt
	irqEnable(IRQ_FIFO_NOT_EMPTY);
	REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_SEND_CLEAR | IPC_FIFO_RECV_IRQ;

	irqSet(IRQ_TIMER1, TIMER1Handler);
	// enable the interrupt
	irqEnable(IRQ_TIMER1);
	irqSet(IRQ_VBLANK, VblankHandler);
	// enable the interrupt
	irqEnable(IRQ_VBLANK);

    SPC_IPC->arm7State = ARM7STATE_WAITING;

	// Keep the ARM7 out of main RAM
	while (1) swiWaitForVBlank();
}


