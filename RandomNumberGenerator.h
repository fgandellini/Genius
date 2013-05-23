#ifndef RANDOMNUMBERGENERATOR_H_
#define RANDOMNUMBERGENERATOR_H_

#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NTAB 32
#define EPS (1.2E-07)
#define MAX(a,b) (a>b)?a:b
#define MIN(a,b) (a<b)?a:b

namespace Genius {

class RandomNumberGenerator {
public:
	static int Seed;
	RandomNumberGenerator();
	virtual ~RandomNumberGenerator();

	static double GetNumber();
};

} /* namespace Genius */
#endif /* RANDOMNUMBERGENERATOR_H_ */
