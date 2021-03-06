#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"
#include "TourFactory.h"
#include "Drawer.h"
#include "InstanceLoader.h"

namespace Genius {

class Genius {
private:
	pTourFactory tourFactory;

	pDrawer drawer;

	void PrintDbgVars(pNode vi, pNode vj, pNode vk, pNode vl);

	InsertTypeIParams EvaluateBestInsertTypeIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize);
	InsertTypeIIParams EvaluateBestInsertTypeIIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize);

	RemoveTypeIParams EvaluateBestRemoveTypeIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize);
	RemoveTypeIIParams EvaluateBestRemoveTypeIIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize);

	void AssertIsFeasibleSolution(pInstance instance, pTour solution, pTour optimalTour);

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
	bool UnstringNodeFromTour(pNode node, pTour tour, int neighborhoodSize);

	void ExecuteGenius(string instanceFile, string optTourFile, int p);
	void ExecuteGeniusWithTimeTrace(string instanceFile, string optTourFile, int p);

};
typedef Genius* pGenius;

} /* namespace Genius */
#endif /* GENIUS_H_ */
