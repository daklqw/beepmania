#include "core.hpp"
#include <iostream>

int main(int argc, char ** argv) {
	if (argc <= 1) return 0;
	gamecore gm;
	FILE * fin = fopen(argc < 3 ? "track.ini" : argv[2], "r");
	if (fin == NULL) {
		std::cerr << "Cannot open config file" << std::endl;
		return -1;
	}
	char keybd[1024], beep[1024];
	fgets(keybd, 1024, fin);
	keybd[strlen(keybd) - 1] = 0;
	fgets(beep, 1024, fin);
	beep[strlen(beep) - 1] = 0;
	if (gm.registerkeybd(keybd) < 0) {
		std::cerr << "Open keyboard event error" << std::endl;
		return -1;
	}
	std::cerr << "Open beep device " << beep << std::endl;
	if (gm.configsound(beep) < 0) {
		std::cerr << "Open beep device error" << std::endl;
		return -1;
	}
	gm.configscore();
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
