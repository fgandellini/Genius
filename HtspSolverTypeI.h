#ifndef HTSPSOLVERTYPEI_H_
#define HTSPSOLVERTYPEI_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"
#include "Subtour.h"
#include "HtspSolverUtils.h"

namespace Genius {

class HtspSolverTypeI {
private:
	pHtspSolverUtils solverUtils;

	pInstance instance;
	pTourFactory tourFactory;
	pTour tspSolution;
	pSubtourVector partialMergedSubtours;

public:
	pSubtourVector subtours;

	HtspSolverTypeI(pInstance instance);
	virtual ~HtspSolverTypeI();

	pTour Solve();
};
typedef HtspSolverTypeI* pHtspSolverTypeI;

} /* namespace Genius */
#endif /* HTSPSOLVERTYPEI_H_ */
