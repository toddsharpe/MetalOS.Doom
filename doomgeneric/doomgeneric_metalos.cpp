#include "doomkeys.h"

#include "doomgeneric.h"

#include <stdio.h>

#include <user/MetalOS.h>
#include <user/MetalOS.UI.h>
#include "Assert.h"
#include <ctype.h>
#include <string.h>

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

using namespace Graphics;

static unsigned char convertToDoomKey(unsigned char key)
{
	switch (key)
	{
	case VK_RETURN:
		key = KEY_ENTER;
		break;
	case VK_ESCAPE:
		key = KEY_ESCAPE;
		break;
	case VK_LEFT:
		key = KEY_LEFTARROW;
		break;
	case VK_RIGHT:
		key = KEY_RIGHTARROW;
		break;
	case VK_UP:
		key = KEY_UPARROW;
		break;
	case VK_DOWN:
		key = KEY_DOWNARROW;
		break;
	case VK_CONTROL:
		key = KEY_FIRE;
		break;
	case VK_SPACE:
		key = KEY_USE;
		break;
	case VK_SHIFT:
		key = KEY_RSHIFT;
		break;
	default:
		key = tolower(key);
		break;
	}

	return key;
}

static void addKeyToQueue(int pressed, unsigned char keyCode)
{
	unsigned char key = convertToDoomKey(keyCode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

Handle window;

static void ProcessMessage(const struct Message& message)
{
	switch (message.Header.MessageType)
	{
		//case WM_CLOSE:
		//	DestroyWindow(hwnd);
		//	break;
		//case WM_DESTROY:
		//	PostQuitMessage(0);
		//	ExitProcess(0);
		//	break;
	case MessageType::PaintEvent:
		ReadOnlyBuffer buffer;
		buffer.Length = DG_BufferSize;
		buffer.Data = DG_ScreenBuffer;
		PaintWindow(window, buffer);
		break;

	case MessageType::KeyEvent:
		addKeyToQueue(message.KeyEvent.Flags.Pressed, message.KeyEvent.Key);
		break;
		//default:
			//return DefWindowProcA(hwnd, msg, wParam, lParam);
	}
}

extern "C" void DG_Init()
{
	printf("DG_Init\n");
	
	Rectangle bounds;
	GetScreenRect(bounds);
	
	AllocWindow(window, bounds);
	DebugPrintf("Bounds: (0x%x,0x%x)\n", bounds.X, bounds.Y);

	memset(s_KeyQueue, 0, KEYQUEUE_SIZE * sizeof(unsigned short));
}

extern "C" void DG_DrawFrame()
{
	struct Message message;
	memset(&message, 0, sizeof(struct Message));
	while (PeekMessage(message) == SystemCallResult::Success)
	{
		ProcessMessage(message);
	}
}

extern "C" void DG_SleepMs(uint32_t ms)
{
	Sleep(ms);
}

extern "C" uint32_t DG_GetTicksMs()
{
	return GetTickCount();
}

extern "C" int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (s_KeyQueueReadIndex == s_KeyQueueWriteIndex)
	{
		//key queue is empty
		return 0;
	}
	else
	{
		unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
		s_KeyQueueReadIndex++;
		s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

		*pressed = keyData >> 8;
		*doomKey = keyData & 0xFF;

		return 1;
	}
}

extern "C" void DG_SetWindowTitle(const char * title)
{
	//if (s_Hwnd)
	//{
		//SetWindowTextA(s_Hwnd, title);
	//}
}
