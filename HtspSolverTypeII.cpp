#include "HtspSolverTypeII.h"

namespace Genius {

HtspSolverTypeII::HtspSolverTypeII(pInstance instance) {
	this->instance = instance;
	this->solverUtils = new HtspSolverUtils();
	this->partialMergedSubtours = new SubtourVector();

	this->subtours =
		this->solverUtils->InitSubtours(instance, false);

	this->subinstances =
		this->solverUtils->ExtractSubinstances(this->instance);
}

HtspSolverTypeII::~HtspSolverTypeII() {
	SAFE_DELETE(this->solverUtils);

	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);

	for(int s=1; s<(int)partialMergedSubtours->size(); s++) {
		SAFE_DELETE(partialMergedSubtours->at(s));
	}
	SAFE_DELETE(partialMergedSubtours);

	for(int s=0; s<(int)subinstances->size(); s++) {
		SAFE_DELETE(subinstances->at(s));
	}
	SAFE_DELETE(subinstances);
}

pTour HtspSolverTypeII::Solve() {
	cout << endl << endl
		 << "HTSP SOLVER Type II "
		 << "[" << this->instance->Name << "]"
		 << endl << endl;

	this->PrintSubinstances();

	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subtours->at(s)->tour =
			this->solverUtils->ExecuteGenius(this->subinstances->at(s));
		pTour tour = this->subtours->at(s)->tour;

		pArc currentArc, nextArc;
		pNode n = tour->Current();
		do {
			pNode current = tour->Current();
			currentArc = this->solverUtils->GetFreeArc(this->subtours->at(s));
			if (currentArc->From == NULL) {
				currentArc->From = current;
			} else {
				currentArc->To = current;
				nextArc = this->solverUtils->GetFreeArc(this->subtours->at(s));
				nextArc->From = current;
			}
			tour->Next();
		} while (n != tour->Current());
		nextArc->To = n;
	}

	this->solverUtils->PrintSubtours("TSP solutions for Subtours:", this->subtours);

	this->partialMergedSubtours->push_back(this->subtours->at(0));
	for(int s=0; s<(int)this->subtours->size()-1; s++) {
		pSubtour first = this->partialMergedSubtours->at(s);
		pSubtour second = this->subtours->at(s+1);

		this->partialMergedSubtours->push_back(this->solverUtils->MergeSubtours(this->instance, first, second));
	}

	this->solverUtils->PrintSubtours("Partial Merged Subtours:", this->partialMergedSubtours);

	this->PrintSolution("HTSP Solver Type II Solution:");

	return this->partialMergedSubtours->at(this->partialMergedSubtours->size()-1)->tour->Clone();
}

void HtspSolverTypeII::PrintSubinstances() {
	cout << endl << "Subinstances:" << endl;
	for (int i=0; i<(int)this->subinstances->size(); i++) {
		cout << "SI_" << i << ": (";
		for (int s=0; s<(int)this->subinstances->at(i)->Size(); s++) {
			cout << this->subinstances->at(i)->GetNode(s)->ToString() << ", ";
		}
		cout << ")" << endl;
	}
}

void HtspSolverTypeII::PrintSolution(string title) {
	int lastPartialSubtour = this->partialMergedSubtours->size()-1;
	cout << endl << title << endl
		 << this->partialMergedSubtours->at(lastPartialSubtour)->tour->ToString()
		 << " (" << this->partialMergedSubtours->at(lastPartialSubtour)->tour->TotalDistance() << ")"
		 << endl << endl;
}

} /* namespace Genius */
