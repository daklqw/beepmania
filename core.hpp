#ifndef _CORE_HPP_
#define _CORE_HPP_
#include "utils.hpp"
#include "score.hpp"
#include "timer.hpp"
#include "track.hpp"
#include "cui.hpp"
#include "keytrans.hpp"
#include "sound.hpp"
#include "keybdevent.hpp"

class gamecore {
	public:
		gamecore();
		~gamecore();

		int registerkeybd(const char *);
		int configsound(const char *);
		void setsound(bool);
		void configscore();
		void configtimer();
		void configtrack(FILE *);
		void configui();
		void readbeatmap(FILE *);
		void bindkey(int, int);
		void warn();

		void start();
	private:
		void getclick(int);
		score sb;
		timer ti;
		sound sd;
		keytrans kt;
		keybd kb;
		std::vector<track> tv;
		std::map<int, int> binder;
		// 不考虑哪个毒瘤一个键映射四个轨道
		UI ui;
		int fpslimit = 60;
} ;

#endif
