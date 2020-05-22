#include "sound.hpp"

int sound::registerbeep(const char * buf) {
	return dev = open(buf, O_WRONLY);
}
sound::sound() {
}
sound::~sound() {
}
void sound::push(int x, double y, double z) {
	que.push((sound::note) {x, y, z});
}
int sound::front() {
	return que.front().ti;
}
bool sound::empty() {
	return que.empty();
}
void sound::playnext() {
	auto t = que.front(); que.pop();
	beep(t.hi, t.lst);
}
void sound::sleep(double x) {
	usleep((int) (x * 1000));
}
void sound::beep(double hi, double ti) {
	if (enablesound) {
		// DEBUG MODE
		int tt = std::max((int) ceil(ti * 960), 1);
		ioctl(dev, KDMKTONE, (tt << 16)+(int) (1193180 / hi));
	}
}
void sound::setenable(bool x) {
	enablesound = x;
}
