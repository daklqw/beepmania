// root and pthread required.
#ifndef _KEYBDEVENT_H_
#define _KEYBDEVENT_H_
#define MAXKEYBD_L 256
#define RGDERR_FILE -1
#define VK_MENU 56
#define VK_SHIFT 42
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.hpp"

struct keybd {
	public:
		keybd();
		~keybd();
		int registerKeybdDevice(const char *);
		int getNextKey();
	private:
		input_event ie;
		int dev;
};
#endif
