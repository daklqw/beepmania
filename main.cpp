#include "core.hpp"
#include <iostream>

int main(int argc, char ** argv) {
	if (argc <= 1) return 0;
	gamecore gm;
	if (gm.registerkeybd("/dev/input/event4") < 0) {
		std::cerr << "Open keyboard event error" << std::endl;
		return -1;
	}
	if (gm.configsound("/dev/console") < 0) {
		std::cerr << "Open beep device error" << std::endl;
		return -1;
	}
	gm.configscore();
	FILE * fin = fopen(argc < 3 ? "track.ini" : argv[2], "r");
	if (fin == NULL) {
		std::cerr << "Cannot open config file" << std::endl;
		return -1;
	}
	gm.configtrack(fin);
	gm.configui();
	fin = fopen(argv[1], "r");
	if (fin == NULL) {
		std::cerr << "Cannot open " << argv[1] << std::endl;
		return -1;
	}
	gm.readbeatmap(fin);
	fclose(fin);
	gm.setsound(true);
	gm.warn();
	gm.start();
	return 0;
}
