#include "timer.hpp"
#include <ctime>

timer::timer() {
}
timer::~timer() {
}

// std::chrono ?
void timer::set() {
	tim = std::chrono::steady_clock::now();
}
int timer::current() {
	return (std::chrono::steady_clock::now() - tim).count() / 1000;
}
double timer::interval(int x) {
	return (current() - x) / (double) CLOCKS_PER_SEC;
}
