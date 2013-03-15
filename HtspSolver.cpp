/*
 * HtspSolver.cpp
 *
 *  Created on: 15/mar/2013
 *      Author: fede
 */

#include "HtspSolver.h"

namespace Genius {

HtspSolver::HtspSolver() {
}

HtspSolver::~HtspSolver() {
}

void HtspSolver::AssertIsFeasibleHtspSolution(pInstance instance, pTour solution, int k)
{
	for(int n=0; n<solution->Length(); n++) {
		pNode node = solution->Get(n);

		int levelToCheck = node->Priority - k;
		if (levelToCheck > 0) {
			int nodesToFound = this->GetCountOfNodesByLevel(instance, levelToCheck);
			int nodesFound = this->GetCountOfNodesByLevelInSubtour(solution, 0, n, levelToCheck);
			assert(nodesFound == nodesToFound);
		}
	}
}

int HtspSolver::GetCountOfNodesByLevelInSubtour(pTour tour, int startingNodeIdx, int endingNodeIdx, int level)
{
	int count = 0;
	for(int n=startingNodeIdx; n<endingNodeIdx; n++) {
		count += (tour->Get(n)->Priority == level) ? 1 : 0;
	}
	return count;
}

int HtspSolver::GetCountOfNodesByLevel(pInstance instance, int level)
{
	int count = 0;
	for(int n=0; n<instance->Size(); n++) {
		count += (instance->GetNode(n)->Priority == level) ? 1 : 0;
	}
	return count;
}

} /* namespace Genius */
