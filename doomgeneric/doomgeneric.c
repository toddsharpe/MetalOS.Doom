#include "doomgeneric.h"
#include <stdlib.h>

uint32_t* DG_ScreenBuffer = NULL;
size_t DG_BufferSize = 0;


void dg_Create()
{
	DG_BufferSize = DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4;
	DG_ScreenBuffer = (uint32_t*)malloc(DG_BufferSize);
	DebugPrintf("DG_ScreenBuffer: 0x%016x Size: 0x%x\n", DG_ScreenBuffer, DG_BufferSize);

	DG_Init();
}

