#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"
#include "Tour.h"

namespace Genius {

class Genius {
public:
	Genius();
	virtual ~Genius();

	void Geni(pInstance nodesToVisit);

	void Add(pNode node, pTour tour);
};
typedef Genius* pGenius;


} /* namespace Genius */
#endif /* GENIUS_H_ */
