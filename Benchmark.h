#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include "CommonIncludes.h"

namespace Genius {

class Benchmark {
private:
	map<string, clock_t> timers;
	map<string, bool> timerRunning;

public:
	Benchmark();
	virtual ~Benchmark();

	void StartTimer(string name);
	double StopTimer(string name);
	double TimerElapsed(string name);

	string TimerElapsedToString(string name);
};
typedef Benchmark* pBenchmark;

} /* namespace Genius */
#endif /* BENCHMARK_H_ */
