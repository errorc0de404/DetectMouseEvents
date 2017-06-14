/*
Author: Lyan

I saw many threads where people have asked whether those "AHK-Cheats" or generally pixel "aimbots" in Overwatch, can be detected.

This is an easy example, on how to detect if a mouse event was triggered by hardware or was injected by another process.
This program will trigger a messagebox as soon as mouse input was received not by hardware.

Try it yourself and see how easy it is to detect your cheat!
*/

#include <Windows.h>

HHOOK hook;

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644970(v=vs.85).aspx
MSLLHOOKSTRUCT mouseStruct;

int idx = 0;
char* mouseMessage[] = { "default", "left mousebutton down", "left mousebutton up", "mouse was moved", "mousewheel moved",
"horizontal mousewheel moved", "right mousebutton down", "right mousebutton up" };

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644986(v=vs.85).aspx
LRESULT CALLBACK LLMP(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0)
	{
		mouseStruct = *((MSLLHOOKSTRUCT*)lParam);

		// LLMHF_INJECTED FLAG
		if (mouseStruct.flags & 0x01)
		{
			switch (wParam)
			{
			case WM_LBUTTONDOWN: idx = 1; break;
			case WM_LBUTTONUP: idx = 2; break;
			case WM_MOUSEMOVE: idx = 3; break;
			case WM_MOUSEWHEEL: idx = 4; break;
			case WM_MOUSEHWHEEL: idx = 5; break;
			case WM_RBUTTONDOWN: idx = 6; break;
			case WM_RBUTTONUP: idx = 7;
			}

			MessageBox(NULL, mouseMessage[idx], "Detected!", MB_ICONINFORMATION);
		}
	}

	return CallNextHookEx(hook, nCode, wParam, lParam);
}

void InstallHook()
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644990(v=vs.85).aspx
	if (!(hook = SetWindowsHookEx(WH_MOUSE_LL, LLMP, NULL, 0)))
	{
		MessageBox(NULL, "failed to install hook", "fail", MB_ICONERROR);
	}
}

void main()
{
	InstallHook();

	// Message loop to keep console alive/get messages.
	MSG gmsg;
	while (GetMessage(&gmsg, NULL, 0, 0))
	{

	}
}
