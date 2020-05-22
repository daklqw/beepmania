#ifndef _SOUND_HPP_
#define _SOUND_HPP_

#include "utils.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>

class sound {
	public:
		sound();
		~sound();
		void push(int, double, double);
		int front();
		bool empty();
		void playnext();
		int registerbeep(const char *);
		void beep(double, double);
		void sleep(double);
		void setenable(bool);
	private:
		bool enablesound;
		struct note {
			int ti; double hi, lst;
		} ;
		std::queue<note> que;
		int dev;
} ;

#endif
