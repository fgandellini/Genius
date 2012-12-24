#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"
#include "TourFactory.h"

namespace Genius {

class Genius {
private:
	pTourFactory tourFactory;

	InsertTypeIParams EvaluateBestInsertTypeIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize);
	InsertTypeIIParams EvaluateBestInsertTypeIIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize);

	RemoveTypeIParams EvaluateBestRemoveTypeIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize);
	RemoveTypeIIParams EvaluateBestRemoveTypeIIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize);
public:
	Genius();
	virtual ~Genius();

	InsertTypeIParams EvaluateBestInsertTypeIParams(pTour tour, pNode v, int neighborhoodSize);
	InsertTypeIIParams EvaluateBestInsertTypeIIParams(pTour tour, pNode v, int neighborhoodSize);

	RemoveTypeIParams EvaluateBestRemoveTypeIParams(pTour tour, pNode vi, int neighborhoodSize);
	RemoveTypeIIParams EvaluateBestRemoveTypeIIParams(pTour tour, pNode vi, int neighborhoodSize);

	void Geni();

	pTour ExecuteGeni(pInstance nodesToVisit, int neighborhoodSize);
	void InitializeTourWithThreeNodes(pTour tour, pInstance nodesToVisit);
	void StringNodeInTour(pNode node, pTour tour, int neighborhoodSize);

	pTour ExecuteUs(pTour tour,int neighborhoodSize);
	void UnstringNodeFromTour(pNode node, pTour tour, int neighborhoodSize);
};
typedef Genius* pGenius;

} /* namespace Genius */
#endif /* GENIUS_H_ */
