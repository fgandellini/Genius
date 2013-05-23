#ifndef HTSPSOLVERUTILS_H_
#define HTSPSOLVERUTILS_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"
#include "Subtour.h"

namespace Genius {

class HtspSolverUtils {
private:
	pGenius genius;
	pTourFactory tourFactory;

	int GetSubtourIndexByPriority(pInstance instance, int p);
	int GetMaximumNumberOfPrioritiesPerSubtour(pInstance instance);

	void AppendTour(pTour source, pNode startingNodeInSource, pTour destination);

public:
	HtspSolverUtils();
	virtual ~HtspSolverUtils();

	pSubtourVector InitSubtours(pInstance instance, bool initInternalTour);
	pInstanceVector InitSubinstances(pInstance instance);

	pTour ExecuteGenius(pInstance instance);

	pSubtourVector ExtractSubtours(pInstance instance, pTour tour);
	pInstanceVector ExtractSubinstances(pInstance instance);

	int GetSubtoursCount(pInstance instance);
	pSubtour GetSubtourByPriority(pInstance instance, pSubtourVector subtours, int p);

	pSubtour MergeSubtours(pInstance instance, pSubtour first, pSubtour second);
	pArc GetFreeArc(pSubtour subtour);

	void PrintSubtours(string title, pSubtourVector subtours);
};
typedef HtspSolverUtils* pHtspSolverUtils;

} /* namespace Genius */
#endif /* HTSPSOLVERUTILS_H_ */
