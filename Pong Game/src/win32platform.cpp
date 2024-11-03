#include <windows.h>
#include "../include/RenderWIn32Platform.h"
#include "../include/Renderer.h"
#include "../include/Controls.h"
#include "../include/Game.h"
#include <algorithm>

RenderWin32Platform render;
Renderer graphicsRenderer;
Game game;
Input input;
bool running = true;

LRESULT CALLBACK windowCallBack(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result {};

	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		running = false;
		break;

	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);

		// height of the new window
		render.recHeight = rect.bottom - rect.top;

		// width of the new window
		render.recWidth = rect.right - rect.left;

		// buffer size of the new rectangle (area of rectangle * size of a pixel)
		int bufferSize = render.recHeight * render.recWidth * sizeof(unsigned int);

		if (render.memory)
			// free the memory allocated from the heap
			VirtualFree(render.memory, 0, MEM_RELEASE);

		// allocate memory from the heap
		render.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render.bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		render.bmi.bmiHeader.biWidth = render.recWidth;
		render.bmi.bmiHeader.biHeight = render.recHeight;
		render.bmi.bmiHeader.biPlanes = 1;
		render.bmi.bmiHeader.biBitCount = 32;
		render.bmi.bmiHeader.biCompression = BI_RGB;
		render.bmi.bmiHeader.biSizeImage = 0;
		render.bmi.bmiHeader.biXPelsPerMeter = 0;
		render.bmi.bmiHeader.biYPelsPerMeter = 0;
		render.bmi.bmiHeader.biClrUsed = 0;
		render.bmi.bmiHeader.biClrImportant = 0;

	}
		break;

	// release key
	case WM_KEYUP:
	{
		switch (wParam)
		{
			case VK_UP:
			{
				input.buttons[BUTTON_UP].changeState = (input.buttons[BUTTON_UP].isDown == true);
				input.buttons[BUTTON_UP].isDown = false;
			}
			break;

			case VK_DOWN:
			{
				input.buttons[BUTTON_DOWN].changeState = (input.buttons[BUTTON_DOWN].isDown == true);
				input.buttons[BUTTON_DOWN].isDown = false;
			}
			break;

			case VK_RIGHT:
			{
				input.buttons[BUTTON_RIGHT].changeState = (input.buttons[BUTTON_RIGHT].isDown == true);
				input.buttons[BUTTON_RIGHT].isDown = false;
			}
			break;

			case VK_LEFT:
			{
				input.buttons[BUTTON_LEFT].changeState = (input.buttons[BUTTON_LEFT].isDown == true);
				input.buttons[BUTTON_LEFT].isDown = false;
			}
			break;

			case 'W':
			{
				input.buttons[BUTTON_W].changeState = (input.buttons[BUTTON_W].isDown == true);
				input.buttons[BUTTON_W].isDown = false;
			}
			break;

			case 'S':
			{
				input.buttons[BUTTON_S].changeState = (input.buttons[BUTTON_S].isDown == true);
				input.buttons[BUTTON_S].isDown = false;
			}
			break;

			case 'D':
			{
				input.buttons[BUTTON_D].changeState = (input.buttons[BUTTON_D].isDown == true);
				input.buttons[BUTTON_D].isDown = false;
			}
			break;

			case 'A':
			{
				input.buttons[BUTTON_A].changeState = (input.buttons[BUTTON_A].isDown == true);
				input.buttons[BUTTON_A].isDown = false;
			}
			break;

			case VK_RETURN:
			{
				input.buttons[BUTTON_ENTER].changeState = (input.buttons[BUTTON_ENTER].isDown == true);
				input.buttons[BUTTON_ENTER].isDown = false;
			}
			break;
		}
	}
	break;

	// press key
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			case VK_UP:
			{
				input.buttons[BUTTON_UP].changeState = (input.buttons[BUTTON_UP].isDown == false);
				input.buttons[BUTTON_UP].isDown = true;
			}
			break;

			case VK_DOWN:
			{
				input.buttons[BUTTON_DOWN].changeState = (input.buttons[BUTTON_DOWN].isDown == false);
				input.buttons[BUTTON_DOWN].isDown = true;
			}
			break;
		
			case VK_RIGHT:
			{
				input.buttons[BUTTON_RIGHT].changeState = (input.buttons[BUTTON_RIGHT].isDown == false);
				input.buttons[BUTTON_RIGHT].isDown = true;
			}
			break;

			case VK_LEFT:
			{
				input.buttons[BUTTON_LEFT].changeState = (input.buttons[BUTTON_LEFT].isDown == false);
				input.buttons[BUTTON_LEFT].isDown = true;
			}
			break;

			case 'W':
			{
				input.buttons[BUTTON_W].changeState = (input.buttons[BUTTON_W].isDown == false);
				input.buttons[BUTTON_W].isDown = true;
			}
			break;

			case 'S':
			{
				input.buttons[BUTTON_S].changeState = (input.buttons[BUTTON_S].isDown == false);
				input.buttons[BUTTON_S].isDown = true;
			}
			break;

			case 'D':
			{
				input.buttons[BUTTON_D].changeState = (input.buttons[BUTTON_D].isDown == false);
				input.buttons[BUTTON_D].isDown = true;
			}
			break;

			case 'A':
			{
				input.buttons[BUTTON_A].changeState = (input.buttons[BUTTON_A].isDown == false);
				input.buttons[BUTTON_A].isDown = true;
			}
			break;

			case VK_RETURN:
			{
				input.buttons[BUTTON_ENTER].changeState = (input.buttons[BUTTON_ENTER].isDown == false);
				input.buttons[BUTTON_ENTER].isDown = true;
			}
			break;
		}
	}
	break;

	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return result;
}

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// create an instance of WNDCLASS structure
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window Class";
	windowClass.lpfnWndProc = windowCallBack;
	
	// hide cursor
	ShowCursor(FALSE);
	
	// RegisterClass registers the windowClass in the operating system
	RegisterClass(&windowClass);

	// create window
	HWND window = CreateWindow(windowClass.lpszClassName, L"Pong Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	// to center the window in the middle of the screen
	SetWindowPos(window, NULL, (GetSystemMetrics(SM_CXSCREEN) - 1280) / 2, (GetSystemMetrics(SM_CYSCREEN) - 720) / 2, 1280, 720, SWP_SHOWWINDOW);

	// to make the window full screen when it starts
	SetWindowLong(window, GWL_STYLE, GetWindowLong(window, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
	MONITORINFO mi = { sizeof(mi) };
	GetMonitorInfo(MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY), &mi);
	SetWindowPos(window, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

	HDC hdc = GetDC(window);

	double time = 0.01666666, performance;
	LARGE_INTEGER frameBeginTime, frameEndTime, temp;

	// QueryPerformanceCounter -> measures the elapsed time between two points
	// QuadPart -> calculates the number of cycles per second
	
	QueryPerformanceCounter(&temp);
	performance = (float)temp.QuadPart;

	QueryPerformanceCounter(&frameBeginTime);

	while (running)
	{
		// reset the changeState for every frame
		for (int i = 0; i < NUMBEROFBUTTONS; i++)
		{
			input.buttons[i].changeState = false;
		}

		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		game.simulateGame(&input, graphicsRenderer, render, time);

		// strech a bitmap from bufferMemory and draw it onto device context (DC) 
		StretchDIBits(hdc, 0, 0, render.recWidth, render.recHeight, 0, 0, render.recWidth, render.recHeight, render.memory, &render.bmi, DIB_RGB_COLORS, SRCCOPY);

		QueryPerformanceCounter(&frameEndTime);

		// calculate seconds per frame
		time = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / performance;
		
		// update frameBeginTime for the next frame
		frameBeginTime = frameEndTime;
	}
}