#pragma once
#include "RenderWin32Platform.h"
#include <math.h>

class Renderer
{
private:
	void rect(RenderWin32Platform render, int x1, int x2, int y1, int y2, unsigned int color);
	void circle(RenderWin32Platform render, int centerX, int centerY, int radius, unsigned int color);

public:
	void drawBackground(RenderWin32Platform render, unsigned int color);
	void drawRectangle(RenderWin32Platform render, float x1, float x2, float y1, float y2, unsigned int color);
	void drawCircle(RenderWin32Platform render, float centerX, float centerY, float radius, unsigned int color);
	void drawNumber(RenderWin32Platform render, int number, float x1, float x2, float y1, float y2, unsigned int color);
	void drawText(RenderWin32Platform render, const char* text, float x, float y, unsigned int color);
	void drawCharacter(RenderWin32Platform render, char c, float x, float y, unsigned int color);
};