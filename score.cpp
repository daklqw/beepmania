#include "score.hpp"

score::score() {
	reset();
}
score::~score() { }
void score::reset() {
	perfect = great = good = bad = 0;
	maxcombo = click = combo = totscore = 0;
	deltas = 0;
	lstdelta = 0;
}
double score::getacc() {
	if (click == 0) return 0;
	return (perfect * 300 + great * 100 + good * 50) / (click * 300.);
}
void score::push(int x) {
	switch (x) {
		case TAG_PERFECT:
			++perfect, ++combo, totscore += combo * 12 + 300;
			break;
		case TAG_GREAT:
			++great, ++combo, totscore += combo * 4 + 100;
			break;
		case TAG_GOOD:
			++good, totscore += combo * 2 + 50;
			break;
		case TAG_BAD:
			++bad, combo = 0;
			break;
		default: break;
	}
	++click;
	maxcombo = std::max(maxcombo, combo);
}
void score::pushdelta(int x) {
	deltas += x / 1000.;
	lstdelta = x / 1000;
}
double score::getavgdelta() {
	int hav = click - bad;
	if (!hav) return 0;
	return deltas / hav;
}
