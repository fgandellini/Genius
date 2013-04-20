#ifndef HTSPSOLVER_H_
#define HTSPSOLVER_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"

namespace Genius {

class HtspSolver {
private:
	vector<pNodeVector>* NodesByPriorityLevel;
	pInstance instance;
	pGenius genius;

	int GetCountOfNodesByLevel(pInstance instance, int level);
	int GetCountOfNodesByLevelInSubtour(pTour tour, int startingNodeIdx, int endingNodeIdx, int level);
	void AssertIsFeasibleHtspSolution(pInstance instance, pTour solution);

public:
	HtspSolver(pInstance instance);
	virtual ~HtspSolver();

	pTour BuildStartingTour();
//	pNode GetFirstNodeByPriorityLevel(pInstance instance, int priorityLevel);
	pNodeVector GetAllNodesByPriorityLevel(pInstance instance, int priorityLevel);

	void DumpNodesByPriorityLevel();
	pTour GetSubtour(pTour currentTour, int starLevel, int endLevel);
	pNode GetFirstNodeInTourByPriorityLevel(pTour tour, int priorityLevel);

	pTour BuildSolution(pTour startingTour);


	vector<pNodeVector>* candidateNodes;
	pTour Solve();
};
typedef HtspSolver* pHtspSolver;

} /* namespace Genius */
#endif /* HTSPSOLVER_H_ */
