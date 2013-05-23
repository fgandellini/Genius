#include "Benchmark.h"

namespace Genius {

Benchmark::Benchmark() {
}

Benchmark::~Benchmark() {
}

void Benchmark::StartTimer(string name) {
	this->timers[name] = clock();
	this->timerRunning[name] = true;
}

double Benchmark::StopTimer(string name) {
	if (this->timerRunning[name]) {
		this->timers[name] = clock() - this->timers[name];
		this->timerRunning[name] = false;
	}
	return (double)(this->timers[name])/CLOCKS_PER_SEC;
}

double Benchmark::TimerElapsed(string name) {
	clock_t elapsed = (this->timerRunning[name]) ? clock() - this->timers[name] : this->timers[name];
	return ((double)elapsed)/CLOCKS_PER_SEC;
}

string Benchmark::TimerElapsedToString(string name) {
	return Utils::ToString(this->TimerElapsed(name));
}

} /* namespace Genius */
