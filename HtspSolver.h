#ifndef HTSPSOLVER_H_
#define HTSPSOLVER_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"

namespace Genius {

class HtspSolver {
private:
	int GetCountOfNodesByLevel(pInstance instance, int level);
	int GetCountOfNodesByLevelInSubtour(pTour tour, int startingNodeIdx, int endingNodeIdx, int level);
	void AssertIsFeasibleHtspSolution(pInstance instance, pTour solution, int k);

public:
	HtspSolver();
	virtual ~HtspSolver();

};
typedef HtspSolver* pHtspSolver;

} /* namespace Genius */
#endif /* HTSPSOLVER_H_ */
