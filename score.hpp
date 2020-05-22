#ifndef _SCORE_HPP_
#define _SCORE_HPP_
#define TAG_PERFECT 1
#define TAG_GREAT 2
#define TAG_GOOD 3
#define TAG_BAD 4
#define TAG_MISS -1

#include "utils.hpp"

const std::map<int, const char *> statusName = {
	{-1, "MISS"},
	{0, ""},
	{1, "PERFECT"},
	{2, "GREAT"},
	{3, "GOOD"},
	{4, "BAD"},
};


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
		int lstdelta, lststatus;
	private:
		int click;
		double deltas;
} ;

#endif
