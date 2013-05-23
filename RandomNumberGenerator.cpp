#include "RandomNumberGenerator.h"

namespace Genius {

int RandomNumberGenerator::Seed = -123;

RandomNumberGenerator::RandomNumberGenerator() {
}

RandomNumberGenerator::~RandomNumberGenerator() {
}

/* Random number generator ran1 from Computers in Physics */
/* Volume 6 No. 5, 1992, 522-524, Press and Teukolsky */
/* To generate real random numbers 0.0-1.0 */
/* Should be seeded with a negative integer */
double RandomNumberGenerator::GetNumber() {
	int *idum = &RandomNumberGenerator::Seed;
	int j,k;
	static int iv[NTAB],iy=0;
	void nrerror();
	static double NDIV = 1.0/(1.0+(IM-1.0)/NTAB);
	static double RNMX = (1.0-EPS);
	static double AM = (1.0/IM);

	if ((*idum <= 0) || (iy == 0)) {
		*idum = MAX(-*idum,*idum);
                for(j=NTAB+7;j>=0;j--) {
			k = *idum/IQ;
			*idum = IA*(*idum-k*IQ)-IR*k;
			if(*idum < 0) *idum += IM;
			if(j < NTAB) iv[j] = *idum;
		}
		iy = iv[0];
	}
	k = *idum/IQ;
	*idum = IA*(*idum-k*IQ)-IR*k;
	if(*idum<0) *idum += IM;
	j = iy*NDIV;
	iy = iv[j];
	iv[j] = *idum;
	return MIN(AM*iy,RNMX);
}

} /* namespace Genius */
