#ifndef DOOM_GENERIC
#define DOOM_GENERIC

#include <stdint.h>

#define DOOMGENERIC_RESX 0x400 //640
#define DOOMGENERIC_RESY 0x300 //400

#ifdef __cplusplus
extern "C"
{
#endif
extern uint32_t* DG_ScreenBuffer;
extern size_t DG_BufferSize;

void DG_Init();
void DG_DrawFrame();
void DG_SleepMs(uint32_t ms);
uint32_t DG_GetTicksMs();
int DG_GetKey(int* pressed, unsigned char* key);
void DG_SetWindowTitle(const char * title);

#ifdef __cplusplus
}
#endif

#endif //DOOM_GENERIC
