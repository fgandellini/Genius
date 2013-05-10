#ifndef HTSPSOLVERTYPEII_H_
#define HTSPSOLVERTYPEII_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"
#include "Subtour.h"
#include "HtspSolverUtils.h"

namespace Genius {

class HtspSolverTypeII {
private:
	pHtspSolverUtils solverUtils;

	pInstance instance;
	pInstanceVector subinstances;
	pSubtourVector partialMergedSubtours;

	void PrintSubinstances();

public:
	pSubtourVector subtours;

	HtspSolverTypeII(pInstance instance);
	virtual ~HtspSolverTypeII();

	pTour Solve();

	void PrintSolution(string title);
};
typedef HtspSolverTypeII* pHtspSolverTypeII;

} /* namespace Genius */
#endif /* HTSPSOLVERTYPEII_H_ */
