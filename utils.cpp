#include "utils.hpp"

coord::coord() { x = y = 0; }
coord::coord(int a, int b) { x = a, y = b; }
coord::coord(const coord & a) { x = a.x, y = a.y; }
coord coord::min(const coord & a, const coord & b) {
	return coord(std::min(a.x, b.x), std::min(a.y, b.y));
}
coord coord::max(const coord & a, const coord & b) {
	return coord(std::max(a.x, b.x), std::max(a.y, b.y));
}

rect::rect() { }
rect::rect(const coord & a, const coord & b) { p1 = a, p2 = b; }
rect::rect(const rect & a) { p1 = a.p1, p2 = a.p2; }
rect rect::areaand(const rect & a, const rect & b) {
	rect res(coord::max(a.p1, b.p1), coord::min(a.p2, b.p2));
	return res;
}
bool rect::none() {
	return p1.x > p2.x || p1.y > p2.y;
}
