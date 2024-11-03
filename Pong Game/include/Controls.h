#pragma once

struct Button
{
	bool isDown;
	bool changeState;
};


enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_RIGHT,
	BUTTON_LEFT,
	BUTTON_W,
	BUTTON_S,
	BUTTON_D,
	BUTTON_A,
	BUTTON_ENTER,
	NUMBEROFBUTTONS,
};

struct Input
{
	Button buttons[NUMBEROFBUTTONS];
};