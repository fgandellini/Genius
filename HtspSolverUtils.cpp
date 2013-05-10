#include "HtspSolverUtils.h"

namespace Genius {

HtspSolverUtils::HtspSolverUtils() {
	this->genius = new Genius();
	this->tourFactory = new TourFactory();
}

HtspSolverUtils::~HtspSolverUtils() {
	SAFE_DELETE(this->genius);
	SAFE_DELETE(this->tourFactory);
}

pTour HtspSolverUtils::ExecuteGenius(pInstance instance) {
	pTour geniTour = this->genius->ExecuteGeni(instance, 4);
	pTour geniusTour = this->genius->ExecuteUs(geniTour, 4);

	SAFE_DELETE(geniTour);
	return geniusTour;
}

pSubtourVector HtspSolverUtils::InitSubtours(pInstance instance, bool initInternalTour) {
	this->tourFactory->SetInstance(instance);
	pSubtourVector subtours = new SubtourVector();

	int P = instance->P;
	int k = instance->k;

	int subtoursCount = this->GetSubtoursCount(instance);
	int multiplier = this->GetNumberOfPrioritiesPerSubtour(instance);

	for (int s=0; s<subtoursCount; s++) {
		pSubtour subtour = new Subtour();

		subtour->priorityRangeBegin = (s * multiplier) + 1;
		subtour->priorityRangeEnd =
			((subtour->priorityRangeBegin + k) < P) ? (subtour->priorityRangeBegin + k) : P;

		if (initInternalTour) {
			subtour->tour = this->tourFactory->GetTour();
		}

		subtours->push_back(subtour);
	}

	return subtours;
}

pInstanceVector HtspSolverUtils::InitSubinstances(pInstance instance) {
	int subtoursCount = this->GetSubtoursCount(instance);

	pInstanceVector subinstances = new InstanceVector();
	for (int s=0; s<subtoursCount; s++) {
		subinstances->push_back(new Instance());
	}

	return subinstances;
}

int HtspSolverUtils::GetSubtoursCount(pInstance instance) {
	return (int)ceil( (double)(instance->P) / ((double)(instance->k) + 1) );
}

pSubtourVector HtspSolverUtils::ExtractSubtours(pInstance instance, pTour tour) {
	pNode lastNode = NULL;
	pSubtour lastSubtour = NULL;
	pSubtourVector subtours = this->InitSubtours(instance, true);

	for (int n=0; n<tour->Length(); n++) {
		pNode node = tour->Get(n);
		pSubtour subtour = this->GetSubtourByPriority(instance, subtours, node->Priority);

		if (lastSubtour == NULL) {
			lastSubtour = subtour;
			lastNode = node;
		}

		if (lastSubtour != subtour) {

			pArc lastSubtourArc = this->GetFreeArc(lastSubtour);
			if (lastSubtourArc->From == NULL) {
				lastSubtourArc->From = lastNode;
			}

			pArc currentSubtourArc = this->GetFreeArc(subtour);
			if (currentSubtourArc->From != NULL && currentSubtourArc->To == NULL) {
				currentSubtourArc->To = node;
			}

			lastSubtour = subtour;
		}

		subtour->tour->Append(node);

		lastNode = node;
	}

	// Corregge le chiusure degli ultimi archi di tutti i subtour
	for (int s=0; s<(int)subtours->size(); s++) {
		pSubtour subtour = subtours->at(s);
		pArc lastArc = subtour->candidateArcs->at(subtour->candidateArcs->size()-1);
		if (lastArc->To == NULL) {
			lastArc->To = subtour->tour->Get(0);
		}
	}

	return subtours;
}

pInstanceVector HtspSolverUtils::ExtractSubinstances(pInstance instance) {
	pInstanceVector subinstances = this->InitSubinstances(instance);

	for (int n=0; n<instance->Size(); n++) {
		pNode node = instance->GetNode(n);
		int subtourIndex = this->GetSubtourIndexByPriority(instance, node->Priority);

		subinstances->at(subtourIndex)->Add(node->Clone());
	}

	return subinstances;
}

pSubtour HtspSolverUtils::GetSubtourByPriority(pInstance instance, pSubtourVector subtours, int p) {
	int index = this->GetSubtourIndexByPriority(instance, p);
	if (index > -1) {
		return subtours->at(index);
	}
	return NULL;
}

int HtspSolverUtils::GetSubtourIndexByPriority(pInstance instance, int p) {
	int prioritiesPerSubtour = this->GetNumberOfPrioritiesPerSubtour(instance);
	int subtourIndex = (int)floor( (double)p / (double)(prioritiesPerSubtour + 1) );

	if (0 <= subtourIndex && subtourIndex < this->GetSubtoursCount(instance)) {
		return subtourIndex;
	}
	return -1;
}

int HtspSolverUtils::GetNumberOfPrioritiesPerSubtour(pInstance instance) {
	return (int)ceil( (double)(instance->P) / (double)(instance->k) );
}

pArc HtspSolverUtils::GetFreeArc(pSubtour subtour) {
	int arcs = (int)subtour->candidateArcs->size();
	pArc lastArc = subtour->candidateArcs->at(arcs-1);

	if (lastArc->To != NULL) {
		subtour->candidateArcs->push_back(new Arc());
		lastArc = subtour->candidateArcs->at(arcs);
	}

	return lastArc;
}

pSubtour HtspSolverUtils::MergeSubtours(pInstance instance, pSubtour first, pSubtour second) {
	this->tourFactory->SetInstance(instance);
	double R, I, currentJoinRatio, maxJoinRatio = 0;
	pArc bestFirstCandidate, bestSecondCandidate;

	pSubtour merged = new Subtour();
	merged->tour = this->tourFactory->GetTour();

	// Ottiene gli archi candidati da tagliare per eseguire il merge dei due subtour
	for(int a1=0; a1<(int)first->candidateArcs->size(); a1++) {
		pArc firstArc = first->candidateArcs->at(a1);

		for(int a2=0; a2<(int)second->candidateArcs->size(); a2++) {
			pArc secondArc = second->candidateArcs->at(a2);

			R = firstArc->From->DistanceFrom(firstArc->To) + secondArc->From->DistanceFrom(secondArc->To);
			I = firstArc->From->DistanceFrom(secondArc->To) + secondArc->From->DistanceFrom(firstArc->To);
			currentJoinRatio = R / I;

			if (currentJoinRatio > maxJoinRatio) {
				maxJoinRatio = currentJoinRatio;
				bestFirstCandidate = firstArc;
				bestSecondCandidate = secondArc;
			}
		}
	}

	// Accoda i due tour a partire dai nodi candidati
	this->AppendTour(first->tour, bestFirstCandidate->To, merged->tour);
	this->AppendTour(second->tour, bestSecondCandidate->To, merged->tour);

	// Imposta l'arco candidato per il tour risultante
	merged->candidateArcs->at(0)->From = bestSecondCandidate->From;
	merged->candidateArcs->at(0)->To = bestFirstCandidate->To;

	// Imposta i range nel tour risultante
	merged->priorityRangeBegin = first->priorityRangeBegin;
	merged->priorityRangeEnd = second->priorityRangeEnd;

	return merged;
}

void HtspSolverUtils::AppendTour(pTour source, pNode startingNodeInSource, pTour destination) {
	source->GoTo(startingNodeInSource);
	pNode n = source->Next();
	destination->Append(n);
	while (n != source->Current()) {
		pNode current = source->Current();
		destination->Append(current);
		source->Next();
	}
}

void HtspSolverUtils::PrintSubtours(string title, pSubtourVector subtours) {
	cout << endl << title << endl;
	for (int s=0; s<(int)subtours->size(); s++) {
		subtours->at(s)->Print();
	}
}

} /* namespace Genius */
