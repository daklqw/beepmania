#ifndef _TRACK_HPP_
#define _TRACK_HPP_
#include "note.hpp"
#include "utils.hpp"
#include "score.hpp"

class track {
	public:
		track();
		~track();
		// render
		void setarea(rect);
		rect getarea();
		void bindscore(score * x);
		std::vector<rect> gettrack(clock_t);
		rect getdown();
		char getdisplaych();
		void setdisplaych(char);

		// difficulty and track
		void setspn(double);
		void setrange(int, int, int, int);
		void push(note);

		void reset();

		// hit
		bool checkhit(clock_t);
		bool checkmiss(clock_t);
		int match(int);
		void setdelta(int);
		int getwidth();
		bool islight();
		void setlight(bool);
		int getlightheight();
		void setlightheight(int);
	private:
		bool light;
		int lightheight;
		rect getpos(note*, clock_t);
		double spn; // seconds per note
		int perfect, great, good, bad;
		int checkdelta;
		int range;
		char drawch;
		rect area;
		std::vector<note> notes;
		int cur;
		score * sb; // update score board
} ;

#endif
