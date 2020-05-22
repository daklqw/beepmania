#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include "utils.hpp"
#include <chrono>

class timer {
	public:
		timer();
		~timer();
		int current();
		double interval(int);
		void set();
	private:
		std::chrono::_V2::steady_clock::time_point tim;
} ;

#endif
