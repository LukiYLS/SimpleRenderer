#pragma once
typedef struct window_rectangle
{
	int xpos;
	int ypos;
	int _width;
	int _height;
}window_rect, viewport;

//mouse=================================================
typedef struct mouse_event
{
	unsigned int time;
	int mouse_status;
	int xpos;
	int ypos;
	int wheelvalue;
}*mouse_event_ptr;

typedef struct mouse_event_vector
{
	mouse_event_ptr  _mouse_events;
	unsigned int		_event_num;
}mouse_event_vector;
//keyboard
typedef struct {
	bool keyDown[256];
} Keys;
#define MOUSE_NONE 0x0
#define LB_DOWN  0x01
#define RB_DOWN  0x02
#define LB_CLICK 0x04
#define LB_UP    0x08
#define RB_CLICK  0x10
#define RB_UP    0x20
#define MB_DOWN  0x40
#define MB_UP    0x80
#define M_MOVE   0x100
#define M_WHEEL  0x200

//Key=================================================================
