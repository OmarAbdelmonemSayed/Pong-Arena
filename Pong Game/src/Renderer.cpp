#include "../include/Renderer.h"

void Renderer::drawBackground(RenderWin32Platform render, unsigned int color)
{
	unsigned int* pixel = (unsigned int*)render.memory;
	for (int i = 0; i < render.recHeight; i++)
	{
		for (int j = 0; j < render.recWidth; j++)
		{
			*pixel++ = color;
		}
	}
}


void Renderer::rect(RenderWin32Platform render, int x1, int x2, int y1, int y2, unsigned int color)
{

	// to prevent a crash due to the coordinates exceeding the height or the weight of the render
	x1 = min(max(0, x1), render.recWidth);
	x2 = min(max(0, x2), render.recWidth);
	y1 = min(max(0, y1), render.recHeight);
	y2 = min(max(0, y2), render.recHeight);

	for (int i = y1; i < y2; i++)
	{
		unsigned int* pixel = (unsigned int*)render.memory + x1 + i * render.recWidth;
		for (int j = x1; j < x2; j++)
		{
			*pixel++ = color;
		}
	}
}

void Renderer::drawRectangle(RenderWin32Platform render, float x1, float x2, float y1, float y2, unsigned int color)
{
	int newX1 = x1 * render.recWidth / 100.0;
	int newX2 = x2 * render.recWidth / 100.0;
	int newY1 = y1 * render.recHeight / 100.0;
	int newY2 = y2 * render.recHeight / 100.0;

	rect(render, newX1, newX2, newY1, newY2, color);
}

void Renderer::circle(RenderWin32Platform render, int centerX, int centerY, int radius, unsigned int color)
{
	int minX = max(0, centerX - radius);
	int maxX = min(centerX + radius, render.recWidth - 1);
	int minY = max(0, centerY - radius);
	int maxY = min(centerY + radius, render.recHeight - 1);

	for (int i = minY; i <= maxY; i++)
	{
		for (int j = minX; j <= maxX; j++)
		{
			int distance = sqrt(pow(j - centerX, 2) + pow(i - centerY, 2));
			if (distance <= radius)
			{
				if (j >= 0 && j < render.recWidth && i >= 0 && i < render.recHeight)
				{
					unsigned int* pixel = (unsigned int*)((char*)render.memory + j * sizeof(unsigned int) + i * render.recWidth * sizeof(unsigned int));
					*pixel = color;
				}
			}
		}
	}
}


void Renderer::drawCircle(RenderWin32Platform render, float centerX, float centerY, float radius, unsigned int color)
{
	int newCenterX = centerX * render.recWidth / 100.0;
	int newCenterY = centerY * render.recHeight / 100.0;
	int newRadius = radius * min(render.recHeight, render.recWidth) / 100.0;

	circle(render, newCenterX, newCenterY, newRadius, color);
}

void Renderer::drawNumber(RenderWin32Platform render, int number, float x1, float x2, float y1, float y2, unsigned int color)
{
	switch (number)
	{
		case 0:
		{
			drawRectangle(render, x1, x2, y1 - 1.4, y1 - 0.4, color);
			drawRectangle(render, x1, x2, y2 + 0.4, y2 + 1.4, color);
			drawRectangle(render, x1 - 1.2, x1, y1 - 1.4, y2 + 1.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y2 + 1.4, color);
		}
		break;

		case 1:
		{
			drawRectangle(render, x1 - 0.1, x2 + 0.1, y1 - 1.7, y2 + 1.7, color);
		}
		break;

		case 2:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.4, color);
			drawRectangle(render, x1 - 1.2, x1, y1 - 1.4, y1 + (y2 - y1) / 2, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.5, y1 + (y2 - y1) / 2 + 0.5, color);
			drawRectangle(render, x2, x2 + 1.2, y1 + (y2 - y1) / 2, y2 + 1.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.4, y2 + 1.4, color);
		}
		break;

		case 3:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.5, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 + 0.4, y1 - 1.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.4, y1 + (y2 - y1) / 2 + 0.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.5, y2 + 1.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y2 + 1, color);
		}
		break;

		case 4:
		{
			drawRectangle(render, x1 + 0.1, x2 + 0.1, y1 - 1.7, y2 + 1.7, color);
			drawRectangle(render, x1 - 1, x1 + 0.1, (y1 - 1.7 + y2 + 1.7) / 2 - 0.8, (y1 - 1.7 + y2 + 1.7) / 2 + 0.8, color);
			drawRectangle(render, x1 - 1.8, x1 - 1, (y1 - 1.7 + y2 + 1.7) / 2 - 0.8, y2 + 1.7, color);
		}
		break;

		case 5:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y1 + (y2 - y1) / 2, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.5, y1 + (y2 - y1) / 2 + 0.5, color);
			drawRectangle(render, x1 - 1.2, x1, y1 + (y2 - y1) / 2, y2 + 1.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.4, y2 + 1.4, color);
		}
		break;

		case 6:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.5, y1 + (y2 - y1) / 2 + 0.5, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.4, y2 + 1.4, color);
			drawRectangle(render, x1 - 1.2, x1, y1 - 1.4, y2 + 1.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y1 + (y2 - y1) / 2, color);
		}
		break;

		case 7:
		{
			drawRectangle(render, x1 + 0.1, x2 + 0.1, y1 - 1.7, y2 + 1.7, color);
			drawRectangle(render, x1 - 1.3, x1 + 0.1, y2 + 0.5, y2 + 1.7, color);
		}
		break;

		case 8:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.5, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.4, y1 + (y2 - y1) / 2 + 0.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.5, y2 + 1.4, color);
			drawRectangle(render, x1 - 1.2, x1, y1 - 1.4, y2 + 1.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y2 + 1.4, color);
		}
		break;

		case 9:
		{
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 - 1.4, y1 - 0.5, color);
			drawRectangle(render, x1 - 1.2, x1, y1 + (y2 - y1) / 2 + 0.4, y2 + 0.5, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y1 + (y2 - y1) / 2 - 0.4, y1 + (y2 - y1) / 2 + 0.4, color);
			drawRectangle(render, x1 - 1.2, x2 + 1.2, y2 + 0.5, y2 + 1.4, color);
			drawRectangle(render, x2, x2 + 1.2, y1 - 1.4, y2 + 1, color);
		}
		break;

	}
}

void Renderer::drawText(RenderWin32Platform render, const char* text, float x, float y, unsigned int color)
{
	while (*text)
	{
		char c = *text++;
		drawCharacter(render, c, x, y, color);
		x += c < 'A' ? 1.5 : 3.0;
	}
}

const unsigned char font[27][7] = {
	// A
   {0b01110,
	0b10001,
	0b10001,
	0b11111,
	0b10001,
	0b10001,
	0b10001},
	// B
   {0b11110,
	0b10001,
	0b10001,
	0b11110,
	0b10001,
	0b10001,
	0b11110},
	// C
   {0b01110,
	0b10001,
	0b10000,
	0b10000,
	0b10000,
	0b10001,
	0b01110},
	// D
   {0b11110,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b11110},
	// E
   {0b11111,
	0b10000,
	0b10000,
	0b11110,
	0b10000,
	0b10000,
	0b11111},
	// F
   {0b11111,
	0b10000,
	0b10000,
	0b11110,
	0b10000,
	0b10000,
	0b10000},
	// G
   {0b01110,
	0b10001,
	0b10000,
	0b10111,
	0b10001,
	0b10001,
	0b01110},
	// H
   {0b10001,
	0b10001,
	0b10001,
	0b11111,
	0b10001,
	0b10001,
	0b10001},
	// I
   {0b01110,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b01110},
	// J
   {0b00111,
	0b00010,
	0b00010,
	0b00010,
	0b10010,
	0b10010,
	0b01100},
	// K
   {0b10001,
	0b10010,
	0b10100,
	0b11000,
	0b10100,
	0b10010,
	0b10001},
	// L
   {0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b10000,
	0b11111},
	// M
   {0b10001,
	0b11011,
	0b10101,
	0b10001,
	0b10001,
	0b10001,
	0b10001},
	// N
   {0b10001,
	0b11001,
	0b10101,
	0b10011,
	0b10001,
	0b10001,
	0b10001},
	// O
   {0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b01110},
	// P
   {0b11110,
	0b10001,
	0b10001,
	0b11110,
	0b10000,
	0b10000,
	0b10000},
	// Q
   {0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b10101,
	0b10010,
	0b01101},
	// R
   {0b11110,
	0b10001,
	0b10001,
	0b11110,
	0b10100,
	0b10010,
	0b10001},
	// S
   {0b01111,
	0b10000,
	0b10000,
	0b01110,
	0b00001,
	0b00001,
	0b11110},
	// T
   {0b11111,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b00100},
	// U
   {0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b01110},
	// V
   {0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b01010,
	0b00100},
	// W
   {0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10101,
	0b11011,
	0b10001},
	// X
   {0b10001,
	0b01010,
	0b00100,
	0b00100,
	0b01010,
	0b10001,
	0b10001},
	// Y
   {0b10001,
	0b10001,
	0b10001,
	0b01010,
	0b00100,
	0b00100,
	0b00100},
	// Z
   {0b11111,
	0b00001,
	0b00010,
	0b00100,
	0b01000,
	0b10000,
	0b11111},
	// :
	{0b00000,
	 0b00100,
	 0b00000,
	 0b00000,
	 0b00100,
	 0b00000,
	 0b00000}
};

void Renderer::drawCharacter(RenderWin32Platform render, char c, float x, float y, unsigned int color)
{
	if (c >= 'A' && c <= 'Z' || c == ':')
	{
		int index = c == ':' ? 26 : c - 'A';
		for (int row = 6; row >= 0; row--)
		{
			for (int col = 4; col >= 0; col--)
			{
				if (font[index][row] & (1 << col))
				{
					float pixelX1 = x + ((4 - col) * 0.5);
					float pixelX2 = pixelX1 + 0.5;
					float pixelY1 = y + ((6 - row) * 0.5);
					float pixelY2 = pixelY1 + 0.5;
					drawRectangle(render, pixelX1, pixelX2, pixelY1, pixelY2, color);
				}
			}
		}
	}
}