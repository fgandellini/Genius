#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"
#include "Tour.h"

namespace Genius {

class Genius {
public:
	int p;

	Genius();
	virtual ~Genius();


	//pNodeVector vNeighborhood;
	//pNodeVector viplus1Neighborhood;
	//pNodeVector vjplus1Neighborhood;

	InsertTypeIParams EvaluateBestInsertionPoint(pTour tour, pNode v);
	InsertTypeIParams EvaluateBestInsertTypeIParams(pTour tour, pNode v);
	InsertTypeIIParams EvaluateBestInsertTypeIIParams(pTour tour, pNode v);

	void Geni(pTour initialTour, pInstance nodesToVisit);

};
typedef Genius* pGenius;


} /* namespace Genius */
#endif /* GENIUS_H_ */
