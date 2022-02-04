#include <nds.h>
//#include "debug.h"

typedef struct  {
    int arm7State;
    int arm9State;

    int curCommand;
	s8 MIXBUFSIZE;
	s8 MIXRATE;
    s8 playBuffer[0x5000];
} SpcTransferRegion;

#define SPC_IPC ((SpcTransferRegion volatile *)(0x027FF000))

#define ARM9COMMAND_UPDATE_APU 1
#define ARM9COMMAND_STEP_APU_DONE 2

#define ARM7COMMAND_START_SOUND 1
#define ARM7COMMAND_STOP_SOUND 2
#define ARM7COMMAND_LOAD_SPC 3
#define ARM7COMMAND_STEP_APU 4
#define ARM7COMMAND_FASTSTEP_APU 5
#define ARM7COMMAND_DONE_APU_UPDATE 6

#define ARM9STATE_INITIALIZING 1
#define ARM9STATE_READY 0x100

#define ARM7STATE_WAITING 1 
#define ARM7STATE_READY 0x101

#define DTCM_IRQ_HANDLER	(*(VoidFunctionPointer *)0x02803FFC)
#define BIOS_INTR_ACK       (*(vu32*)0x02803FF8)

#define ALIGNED __attribute__ ((aligned(4)))
#define CODE_IN_ITCM __attribute__ ((section (".itcm")))
//#define VAR_IN_ITCM __attribute__ ((section (".itcm")))
#define VAR_IN_DTCM __attribute__ ((section (".dtcm")))
#define ALIGNED_VAR_IN_DTCM __attribute__ ((aligned(4),section (".dtcm")))
