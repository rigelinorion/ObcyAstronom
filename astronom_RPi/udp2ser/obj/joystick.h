#ifndef joystick_H
#define joystick_H

#include "includes.inc"

#define JOY_DEV "/dev/input/js0"

#define KEY_NONE			0
#define KEY_AX_LEFT 		24 //13
#define KEY_AX_RIGHT		13 //24
#define KEY_AX_UP			35
#define KEY_AX_DOWN			46
#define KEY_AX_LEFT_UP		KEY_AX_LEFT + KEY_AX_UP
#define KEY_AX_LEFT_DOWN	KEY_AX_LEFT + KEY_AX_DOWN
#define KEY_AX_RIGHT_UP		KEY_AX_RIGHT + KEY_AX_UP
#define KEY_AX_RIGHT_DOWN	KEY_AX_RIGHT + KEY_AX_DOWN

#define KEY_BTN_1			1
#define KEY_BTN_2			2
#define KEY_BTN_3			3
#define KEY_BTN_4			4
#define KEY_BTN_5			5
#define KEY_BTN_6			6
#define KEY_BTN_7			7
#define KEY_BTN_8			8
#define KEY_BTN_9			9
#define KEY_BTN_10			10
#define KEY_BTN_11			11
#define KEY_BTN_12			12

void joystick_init();
void joystick_destroy();
int  joystick_getJStateEx(int *faxis, char *fbuttons);
void joystick_sendCommand(char cmd[16]);
void joystick_slew(int key);
void joystick_stop();
void joystick_keyEvent();
#endif