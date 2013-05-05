#ifndef HTSPSOLVER_H_
#define HTSPSOLVER_H_

#include "CommonIncludes.h"
#include "Genius.h"
#include "InstanceLoader.h"

namespace Genius {

class Subtour {
public:
	int priorityRangeBegin;
	int priorityRangeEnd;
	pTour tour;
	pArcVector candidateArcs;

	Subtour() {
		this->priorityRangeBegin = 0;
		this->priorityRangeEnd = 0;

		this->candidateArcs = new ArcVector();
		this->candidateArcs->push_back(new Arc());

		this->tour = NULL;
	}

	~Subtour() {
		SAFE_DELETE(this->tour);
		for(int a=0; a<(int)this->candidateArcs->size(); a++) {
			SAFE_DELETE(this->candidateArcs->at(a));
		}
		SAFE_DELETE(this->candidateArcs);
	}

	void Print() {
		cout << "[" << this->priorityRangeBegin << ", " << this->priorityRangeEnd << "] ";
		this->PrintTour();
		cout << " (" << tour->TotalDistance() << ") | ";
		for (int a=0; a<(int)candidateArcs->size(); a++) {
			cout << "(";
			if (candidateArcs->at(a)->From != NULL) {
				cout << candidateArcs->at(a)->From->Id;
			} else {
				cout << " ";
			}
			cout << "->";
			if (candidateArcs->at(a)->To != NULL) {
				cout << candidateArcs->at(a)->To->Id;
			} else {
				cout << " ";
			}
			cout << ") ";
		}
		cout << endl;
	}

	void PrintTour() {
		if (this->tour->Length() > 0) {
			for (int n=0; n<this->tour->Length(); n++) {
				pNode node = this->tour->Get(n);
				cout << node->Id << "p" << node->Priority;

				bool newArc = false;
				for (int a=0; a<(int)candidateArcs->size(); a++) {
					if (candidateArcs->at(a)->From->Id == node->Id) {
						cout << " -> ";
						newArc = true;
						break;
					}
				}

				if (!newArc) {
					cout << " => ";
				}
			}
			pNode node = this->tour->Get(0);
			cout << node->Id << "p" << node->Priority;
		}
	}
};
typedef Subtour* pSubtour;
typedef vector<pSubtour> SubtourVector;
typedef SubtourVector* pSubtourVector;

class HtspSolver {
private:
	vector<pNodeVector>* NodesByPriorityLevel;
	int GetCountOfNodesByLevel(pInstance instance, int level);
	int GetCountOfNodesByLevelInSubtour(pTour tour, int startingNodeIdx, int endingNodeIdx, int level);
	void AssertIsFeasibleHtspSolution(pInstance instance, pTour solution);



	pInstance instance;
	pTourFactory tourFactory;
	pInstanceVector subinstances;
	pSubtourVector partialMergedSubtours;

	pTour geniSolution;
	pGenius genius;
	int maxSubtoursCount;
	pSubtourVector InitSubtours();
	int GetNumberOfPrioritiesPerSubtour();
	pArc GetFreeArc(pSubtour subtour);
	void AppendTour(pTour source, pNode startingNodeInSource, pTour destination);

	pTour ExecuteGenius(pInstance instance);
	int GetSubtourIndexByPriority(int p);
	void ExtractSubinstances();

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
	pTour SolveOld();



	pSubtourVector subtours;
	pTour geniusSolution;

	pTour SolveTypeI();
	pTour SolveTypeII();
	void SolveAsTsp(pInstance instance);
	void ExtractSubtours();
	pSubtour GetSubtourByPriority(int p);
	pSubtour MergeSubtours(pSubtour first, pSubtour second);
};
typedef HtspSolver* pHtspSolver;

} /* namespace Genius */
#endif /* HTSPSOLVER_H_ */
