#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#include <map>

class coord {
	public:
		int x, y;
		coord();
		coord(int, int);
		coord(const coord &);
		static coord min(const coord &, const coord &);
		static coord max(const coord &, const coord &);
} ;
class rect {
	public:
		coord p1, p2;
		rect();
		rect(const coord &, const coord &);
		rect(const rect &);
		static rect areaand(const rect & a, const rect & b);
		bool none();
} ;
#endif
