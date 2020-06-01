#include "core.hpp"

gamecore::gamecore() {
}
gamecore::~gamecore() {
}
int gamecore::registerkeybd(const char * buf) {
	return kb.registerKeybdDevice(buf);
}
int gamecore::configsound(const char * buf) {
	return sd.registerbeep(buf);
}
void gamecore::configscore() {
	sb.reset();
}
void gamecore::configtimer() {
	ti.set();
}
void gamecore::readbeatmap(FILE * fin) {
	double tick, hi;
	fscanf(fin, "%lf%lf", &tick, &hi);
	tick /= 1000;
	kt.set(hi);
	static char buf[1024], opt[1024];
	double pre = 1;
	while (fscanf(fin, "%s", opt) == 1) {
		std::transform(opt, opt + strlen(opt), opt, ::toupper);
		if (strcmp(opt, "END") == 0) break;
		if (strcmp(opt, "SLEEP") == 0) {
			double tim;
			fscanf(fin, "%lf", &tim);
			pre += tim / 1000.;
			fgets(buf, 1024, fin);
			continue;
		}
		if (*opt == ';') { fgets(buf, 1024, fin); continue; }
		double tim, dta;
		fscanf(fin, "%lf%lf", &tim, &dta);
		tim *= tick;
		double hi = kt(*opt, dta);
		fgets(buf, 1024, fin);
		std::vector<std::vector<int> > vec;
		for (char * cur = buf; *cur; ++cur)
			if (*cur == '#') vec.push_back({});
			else if (isdigit(*cur))
				vec.back().push_back(*cur & 15);
		sd.push(pre * CLOCKS_PER_SEC, hi, tim);
		if (vec.empty()) {
			pre += tim;
		} else {
			double sm = tim / vec.size();
			for (auto t : vec) {
				for (auto c : t)
					tv[c - 1].push(note(pre * CLOCKS_PER_SEC));
				pre += sm;
			}
		}
	}
}
void gamecore::configtrack(FILE * fin) {
	int tc;
	fscanf(fin, "%d %d", &fpslimit, &tc);
	double spn;
	int C, L, R, dta;
	fscanf(fin, "%lf%d%d%d%d", &spn, &C, &L, &R, &dta);
	tv.clear();
	for (int i = 0; i < tc; ++i) {
		int A, B;
		fscanf(fin, "%d%d", &A, &B);
		binder[A] = i;
		tv.push_back(track());
		tv[i].reset();
		tv[i].setdisplaych(B);
		tv[i].bindscore(&sb);
		tv[i].setspn(spn);
		tv[i].setrange(35000, 80000, 150000, 200000);
		tv[i].setarea(rect(coord(1, R * i + 1), coord(C, R * i + R)));
		tv[i].setdelta(dta);
		tv[i].setlightheight(L);
	}
}
void gamecore::configui() {
	ui.bindtimer(&ti);
	ui.bindscore(&sb);
	ui.setFPS(coord(1, tv.size() * tv[0].getwidth() + 1));
	ui.setStatusPos(coord(tv[0].getdown().p2.x + 1, 3));
	for (int i = 0; i != (int)tv.size(); ++i)
		ui.pushtrack(&tv[i]);
}

void gamecore::getclick(int ch) {
	bool light = true;
	if (ch < 0) light = false, ch = -ch;
	if (binder.count(ch)) {
		track & tar = tv[binder[ch]];
		if (light) {
			int cur = ti.current();
			tar.checkhit(cur);
		}
		tar.setlight(light);
	}
}

void gamecore::start() {
	configtimer();
	int lst = ti.current();
	while (true) {
		while (int t = kb.getNextKey()) getclick(t);
		for (auto & i : tv) i.checkmiss(ti.current());
		if (ti.interval(lst) * fpslimit >= 1) {
			lst = ti.current();
			ui.update(lst);
			ui.flush();
		}
		if (!sd.empty() && ti.current() > sd.front())
			sd.playnext();
		usleep(10);
	}
}

void gamecore::warn() {
	sd.beep(400, 0.5);
}

void gamecore::setsound(bool x) {
	sd.setenable(x);
}
