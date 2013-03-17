/*
 * HtspSolver.cpp
 *
 *  Created on: 15/mar/2013
 *      Author: fede
 */

#include "HtspSolver.h"

namespace Genius {

HtspSolver::HtspSolver() {

	// Procedura per solver HTSP
	// 1. Pesco un vertice per ogni valore di priorità
	// 2. li metto in un tour in ordine di priorità (lungo P nodi)
	// 3. ottengo il prossimo nodo di priorità L da inserire (con L = 1..P)
	// 4. ottengo un subtour dove inserirlo:
	//		- il subtour parte dal primo nodo a priorità L già nel tour
	//		- e termina con il primo nodo a priorità l+k già nel tour
	// 5. riaggancio il subtour al tour completo
	// 6. se ha altri nodi da inserire, continuo dal passo 3
	//	  altrimenti esco




}

HtspSolver::~HtspSolver() {
}

void HtspSolver::AssertIsFeasibleHtspSolution(pInstance instance, pTour solution)
{
	for(int n=0; n<solution->Length(); n++) {
		pNode node = solution->Get(n);

		int levelToCheck = node->Priority - instance->k;
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
