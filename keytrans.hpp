#ifndef _KEYTRANS_HPP_
#define _KEYTRANS_HPP_

#include "utils.hpp"

class keytrans {
	public:
		keytrans();
		~keytrans();
		double operator () (char, double);
		void set(double);
	private:
		int voicec[256];
		double delta;
} ;
#endif
