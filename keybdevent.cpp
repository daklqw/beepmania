#include "keybdevent.hpp"

keybd::keybd() { }
keybd::~keybd() { }
int keybd::getNextKey(){
	const size_t siz = sizeof ie;
	while (true) {
		int res = read(dev, &ie, siz);
		if (res == -1) return 0;
		if (ie.type == 1) {
			if (ie.value <= 1) {
				return ie.value ? (int) ie.code : -((int) ie.code);
			}
		}
	}
	return -1;
}

int keybd::registerKeybdDevice(const char * device) {
	dev = open(device, O_RDONLY | O_NONBLOCK);
	if (dev <= 0) return RGDERR_FILE;
	return 0;
}
