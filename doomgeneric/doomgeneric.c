#include <stdio.h>

#include "m_argv.h"

#include "doomgeneric.h"

pixel_t* DG_ScreenBuffer = NULL;

void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create(int argc, char **argv)
{
	// save arguments
    myargc = argc;
    myargv = argv;

	M_FindResponseFile();

	DG_ScreenBuffer = (pixel_t*)malloc(DG_BufferSize);
	DebugPrintf("DG_ScreenBuffer: 0x%016x Size: 0x%x\n", DG_ScreenBuffer, DG_BufferSize);

	DG_Init();

	D_DoomMain ();
}

