#ifndef _CUI_HPP_
#define _CUI_HPP_

#include "track.hpp"
#include "timer.hpp"
#include "utils.hpp"
#include "score.hpp"

class UI {
	public:
		UI() ;
		~UI() ;
		void bindtimer(timer *);
		void bindscore(score *);
		void setFPS(coord);
		void update(clock_t);
		double getFPS();
		void showFPS();
		void setscore(coord);
		void showscore();
		void flush();
		void pushtrack(track *);
		void reset();
	private:
		std::vector<track*> trs;
		timer * ti;
		std::queue<int> flevent;
		coord fpsat, sbat;
		bool FPSset;
		score * sb;
} ;

#endif
