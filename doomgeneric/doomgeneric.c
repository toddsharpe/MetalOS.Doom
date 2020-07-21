#include "doomgeneric.h"
#include <stdlib.h>

uint32_t* DG_ScreenBuffer = NULL;


void dg_Create()
{
	DG_ScreenBuffer = (uint32_t*)malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);
	DebugPrintf("DG_ScreenBuffer: 0x%016x\n", DG_ScreenBuffer);

	DG_Init();
}

