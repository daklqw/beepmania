#include "track.hpp"

track::track() {
}

track::~track() {
}

void track::bindscore(score * x) { sb = x; }
void track::setarea(rect rt) { area = rt; }

rect track::getpos(note * nt, clock_t now) {
	double mid = (nt->tick - now) / 1000000.;
	rect ar;
	ar.p2.x = area.p1.x + (int) (area.p2.x - area.p1.x + 1) * (1 - mid / spn) - 1;
	ar.p1.x = ar.p2.x - nt->size + 1;
	ar.p1.y = area.p1.y;
	ar.p2.y = area.p2.y;
	return rect::areaand(area, ar);
}

std::vector<rect> track::gettrack(clock_t now) {
	int _c = cur;
	std::vector<rect> res;
	while (_c < notes.size()) {
		if (notes[_c].tick - now > spn * CLOCKS_PER_SEC) break;
		rect tmp = getpos(&notes[_c++], now);
		if (tmp.none()) continue;
		res.push_back(tmp);
	}
	return res;
}

char track::getdisplaych() { return drawch; }
void track::setdisplaych(char x) { drawch = x; }

void track::setspn(double x) { spn = x; }
void track::setrange(int a, int b, int c, int d) {
	perfect = a, great = b, good = c, bad = d;
}
void track::push(note x) {
	notes.push_back(x);
}

void track::reset() {
	cur = 0;
}

bool track::checkhit(clock_t now) {
	if (cur == notes.size()) return false;
	int delta = notes[cur].tick - (now - checkdelta);
	int res = match(delta);
	if (res == -1) return false;
	++cur;
	sb->push(res);
	if (res != TAG_BAD) sb->pushdelta(delta);
	return true;
}
bool track::checkmiss(clock_t now) {
	if (cur == notes.size()) return false;
	int res = (now - checkdelta) - notes[cur].tick;
	if (res > bad) {
		++cur;
		sb->push(TAG_BAD);
		return true;
	}
	return false;
}
int track::match(int dta) {
	if (std::abs(dta) <= perfect) return TAG_PERFECT;
	if (std::abs(dta) <= great) return TAG_GREAT;
	if (std::abs(dta) <= good) return TAG_GOOD;
	if (std::abs(dta) <= bad) return TAG_BAD;
	return TAG_MISS;
}
coord track::getstatus() {
	return coord(area.p2.x + 2, area.p1.y + 1);
}
rect track::getdown() {
	coord p1(area.p2.x + 1, area.p1.y);
	coord p2(area.p2.x + 1, area.p2.y);
	return rect(p1, p2);
}
void track::setdelta(int x) { checkdelta = x; }
