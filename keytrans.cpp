#include "keytrans.hpp"

const int voice[] = {
	262, 294, 330, 349, 392, 440, 494,
	523, 578, 659, 698, 784, 880, 988,
	1046, 1175, 1318, 1397, 1568, 1760, 1976,
	2093, 2349, 2637, 2793, 3135, 3520, 3951
};
const double vol = 1.059463;
const char ch[] = "ZXCVBNMASDFGHJQWERTYU1234567";

keytrans::keytrans() {
	memset(voicec, 0, sizeof voicec);
	const int sz = strlen(ch);
	for (int i = 0; i < sz; ++i) voicec[(int)ch[i]] = voice[i];
}

keytrans::~keytrans() {
}

double keytrans::operator ()(char ch, double pw) {
	return voicec[(int)ch] * pow(vol, pw) * delta;
}

void keytrans::set(double pw) {
	delta = pow(vol, pw);
}
