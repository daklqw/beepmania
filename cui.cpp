// console user interface
#include <curses.h>
#include "cui.hpp"
#include "utils.hpp"

UI::UI() {
	initscr();
	start_color();
	FPSset = false;
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
}
UI::~UI() { endwin(); }
void UI::bindtimer(timer * _t) { ti = _t; }
void UI::bindscore(score * _t) { sb = _t; }
void UI::setFPS(coord _t) { fpsat = _t; FPSset = true; }
void UI::setStatusPos(coord _t) { statat = _t; }
void UI::setWordPos(coord _t) { wordat = _t, wordDisplay = true;  }
void UI::setWordDisplay(bool is_display = true) { wordDisplay = is_display; }
void matrix(rect box, char ch) {
	for (int x = box.p1.x; x <= box.p2.x; ++x)
		for (int y = box.p1.y; y <= box.p2.y; ++y)
			mvaddch(x, y, ch);
}
void UI::update(clock_t now) {
	clear();
	for (auto tr : trs) {
		for (auto box : tr->gettrack(now)) {
			int v = tr->getdisplaych();
			attron(COLOR_PAIR(v));
			matrix(box, ' ');
			attroff(COLOR_PAIR(v));
		}
		matrix(tr->getdown(), '=');
	}
}
double UI::getFPS() { return flevent.size(); }
void UI::showFPS() {
	move(fpsat.x, fpsat.y);
	printw("FPS: %.1lf", getFPS());
}
void UI::showWord() {
	move(wordat.x, wordat.y);
	// printw("%s\n", word.c_str());
}
void UI::setscore(coord t) { sbat = t; }
void UI::showscore() {
	move(fpsat.x + 1, fpsat.y);
	printw("perfect: %d", sb->perfect);
	move(fpsat.x + 2, fpsat.y);
	printw("great  : %d", sb->great);
	move(fpsat.x + 3, fpsat.y);
	printw("good   : %d", sb->good);
	move(fpsat.x + 4, fpsat.y);
	printw("bad    : %d", sb->bad);
	move(fpsat.x + 5, fpsat.y);
	printw("combo  : %d", sb->combo);
	move(fpsat.x + 6, fpsat.y);
	printw("maxcb. : %d", sb->maxcombo);
	move(fpsat.x + 7, fpsat.y);
	printw("score  : %d", sb->totscore);
	move(fpsat.x + 8, fpsat.y);
	printw("acc    : %.2lf%%", sb->getacc() * 100);
	move(fpsat.x + 9, fpsat.y);
	double tmp = sb->getavgdelta();
	printw("hitavg : %.0lf(%c)", tmp, (tmp >= 0 ? 'e' : 'l'));
	move(fpsat.x + 10, fpsat.y);
	printw("lstdta : %d", sb->lstdelta);
	move(statat.x, statat.y);
	printw("%5d %s", sb->combo, statusName.at(sb->lststatus));
}
void UI::flush() {
	while (!flevent.empty() && ti->interval(flevent.front()) > 1.0)
		flevent.pop();
	flevent.push(ti->current());
	if (FPSset) showFPS();
	showscore();
	refresh();
}
void UI::pushtrack(track * x) {
	trs.push_back(x);
}
void UI::reset() {
}
