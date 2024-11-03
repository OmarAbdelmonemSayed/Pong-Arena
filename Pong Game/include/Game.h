#pragma once
#include "Controls.h"
#include "Renderer.h"
#include "RenderWin32Platform.h"

class Game
{
public:
	void simulateGame(Input* inputm, Renderer graphicsRenderer, RenderWin32Platform render, double time);
	friend bool isDown(Input* input, int button);
	friend bool pressed(Input* input, int button);
	friend bool released(Input* input, int button);
};