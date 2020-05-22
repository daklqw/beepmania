#ifndef _SCORE_HPP_
#define _SCORE_HPP_
#define TAG_PERFECT 1
#define TAG_GREAT 2
#define TAG_GOOD 3
#define TAG_BAD 4
#define TAG_MISS -1

#include "utils.hpp"

class score {
	public:
		score();
		~score();
		void reset();
		void push(int);
		void pushdelta(int);
		double getacc();
		double getavgdelta();
		int perfect, great, good, bad;
		int combo;
		long long totscore;
		int maxcombo;
		int lstdelta;
	private:
		int click;
		double deltas;
} ;

#endif
