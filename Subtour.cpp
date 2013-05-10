#include "Subtour.h"

namespace Genius {

Subtour::Subtour() {
	this->priorityRangeBegin = 0;
	this->priorityRangeEnd = 0;

	this->candidateArcs = new ArcVector();
	this->candidateArcs->push_back(new Arc());

	this->tour = NULL;
}

Subtour::~Subtour() {
	SAFE_DELETE(this->tour);
	for(int a=0; a<(int)this->candidateArcs->size(); a++) {
		SAFE_DELETE(this->candidateArcs->at(a));
	}
	SAFE_DELETE(this->candidateArcs);
}

void Subtour::Print() {
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

void Subtour::PrintTour() {
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

} /* namespace Genius */
