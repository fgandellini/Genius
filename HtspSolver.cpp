/*
 * HtspSolver.cpp
 *
 *  Created on: 15/mar/2013
 *      Author: fede
 */

#include "HtspSolver.h"

namespace Genius {

HtspSolver::HtspSolver(pInstance instance) {
	this->instance = instance;
	this->tourFactory = new TourFactory(this->instance);

	this->geniSolution = NULL;
	this->geniusSolution = NULL;
	this->genius = new Genius();

	this->maxSubtoursCount = (int)ceil( (double)this->instance->P / ((double)this->instance->k + 1) );

	this->subtours = this->InitSubtours();

	this->partialMergedSubtours = new SubtourVector();

	this->subinstances = new InstanceVector();



//	this->NodesByPriorityLevel = new vector<pNodeVector>();
//
//	this->genius = new Genius();

//	for (int l=0; l<this->instance->P; l++) {
//		int priority = l+1;
//		this->NodesByPriorityLevel->push_back(
//			this->GetAllNodesByPriorityLevel(this->instance, priority));
//	}
//
//	this->DumpNodesByPriorityLevel();
}

HtspSolver::~HtspSolver() {
//	for (int l=0; l<this->instance->P; l++) {
//		SAFE_DELETE_VECTOR(this->NodesByPriorityLevel->at(l));
//	}
//	SAFE_DELETE_VECTOR(this->NodesByPriorityLevel);
//
	SAFE_DELETE(this->geniSolution);
	SAFE_DELETE(this->geniusSolution);
	SAFE_DELETE(this->genius);
	SAFE_DELETE(this->tourFactory);

	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);

	for(int s=1; s<(int)partialMergedSubtours->size(); s++) {
		SAFE_DELETE(partialMergedSubtours->at(s));
	}
	SAFE_DELETE(partialMergedSubtours);
	SAFE_DELETE(subinstances);
}



pTour HtspSolver::BuildSolution(pTour startingTour) {

	pTour currentTour = startingTour;

	for (int l=0; l<this->instance->P; l++) {
		pNodeVector nodeSet = this->NodesByPriorityLevel->at(l);

		while (nodeSet->size() > 0) {
			pNode nodeToAdd = *nodeSet->begin();

			//if ( (nodeToAdd->Priority + this->instance->k) <= this->instance->P ) {
				pTour subTour = GetSubtour(
						startingTour,
						nodeToAdd->Priority,
						(nodeToAdd->Priority + this->instance->k) );

				cout << endl;
				cout << "Adding node " << nodeToAdd->Id << " to tour: " << subTour->ToString() << endl;

				// Aggiunge il nodo al subtour
				//genius->StringNodeInTour(nodeToAdd, subTour, 4);
				subTour->Append(nodeToAdd);

				cout << "Resulting tour: " << subTour->ToString() << endl;

				// riaggiungere il subTour al currentTour
				//int addedNodeIndex = subTour->GetIndex(nodeToAdd);



				nodeSet->erase(nodeSet->begin());
			//}
		}
	}
}

pTour HtspSolver::GetSubtour(pTour currentTour, int startLevel, int endLevel) {
	pTour subTour = new Tour(this->instance);

	bool addNodeToSubtour = false;
	for (int n=0; n<currentTour->Length(); n++) {
		pNode node = currentTour->Get(n);

		if (node->Priority == startLevel) {
			addNodeToSubtour = true;
		}

		if (addNodeToSubtour) {
			subTour->Append(node);
		}

		if (node->Priority == endLevel) {
			addNodeToSubtour = false;
			break;
		}
	}

	return subTour;
}

pTour HtspSolver::BuildStartingTour() {
	pTour startingTour = new Tour(this->instance);

	for (int l=0; l<this->instance->P; l++) {
		pNodeVector nodeSet = this->NodesByPriorityLevel->at(l);

		if (nodeSet->size() > 0) {
			pNode node = *nodeSet->begin();

			startingTour->Append(node);

			nodeSet->erase(nodeSet->begin());
		}
	}

	cout << endl << startingTour->ToString();
	this->DumpNodesByPriorityLevel();

	return startingTour;
}

pNode HtspSolver::GetFirstNodeInTourByPriorityLevel(pTour tour, int priorityLevel) {
	for (int n=0; n<tour->Length(); n++) {
		pNode node = tour->Get(n);
		if (node->Priority == priorityLevel) {
			return node;
		}
	}
	return NULL;
}

void HtspSolver::DumpNodesByPriorityLevel() {
	cout << endl;
	for (int l=0; l<this->instance->P; l++) {
		cout << l+1 << "] ";
		pNodeVector nodeSet = this->NodesByPriorityLevel->at(l);
		for (int n=0; n<((int)nodeSet->size()-1); n++) {
			cout << nodeSet->at(n)->Id << ", ";
		}
		cout << nodeSet->at(nodeSet->size()-1)->Id << endl;
	}
}









pSubtourVector HtspSolver::InitSubtours() {
	pSubtourVector subtours = new SubtourVector();
	int P = this->instance->P;
	int k = this->instance->k;

	int multiplier = this->GetNumberOfPrioritiesPerSubtour();

	for (int s=0; s<this->maxSubtoursCount; s++) {
		pSubtour subtour = new Subtour();

		subtour->priorityRangeBegin = (s * multiplier) + 1;
		subtour->priorityRangeEnd =
			((subtour->priorityRangeBegin + k) < P) ? (subtour->priorityRangeBegin + k) : P;

		subtour->tour = this->tourFactory->GetTour();

		subtours->push_back(subtour);
	}

	return subtours;
}

int HtspSolver::GetNumberOfPrioritiesPerSubtour() {
	int P = this->instance->P;
	int k = this->instance->k;
	return (int)ceil( (double)P / (double)k );
}



pTour HtspSolver::SolveTypeII() {
	this->ExtractSubinstances();
	cout << endl << "Subinstances:" << endl;
	for (int i=0; i<(int)this->subinstances->size(); i++) {
		cout << "SI_" << i << ": (";
		for (int s=0; s<(int)this->subinstances->at(i)->Size(); s++) {
			cout << this->subinstances->at(i)->GetNode(s)->ToString() << ", ";
		}
		cout << ")" << endl;
	}

	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subtours->at(s)->tour = this->ExecuteGenius(this->subinstances->at(s));
		pTour tour = this->subtours->at(s)->tour;

		pArc currentArc, nextArc;
		pNode n = tour->Current();
		do {
			pNode current = tour->Current();
			currentArc = this->GetFreeArc(this->subtours->at(s));
			if (currentArc->From == NULL) {
				currentArc->From = current;
			} else {
				currentArc->To = current;
				nextArc = this->GetFreeArc(this->subtours->at(s));
				nextArc->From = current;
			}
			tour->Next();
		} while (n != tour->Current());
		nextArc->To = n;
	}

	cout << endl << "TSP solutions for Subtours:" << endl;
	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subtours->at(s)->Print();
	}

	this->partialMergedSubtours->push_back(this->subtours->at(0));
	for(int s=0; s<(int)this->subtours->size()-1; s++) {
		pSubtour first = this->partialMergedSubtours->at(s);
		pSubtour second = this->subtours->at(s+1);

		this->partialMergedSubtours->push_back(this->MergeSubtours(first, second));
	}

	cout << endl << "Partial Merged Subtours:" << endl;
	for (int s=0; s<(int)this->partialMergedSubtours->size(); s++) {
		this->partialMergedSubtours->at(s)->Print();
	}

	int lastPartialSubtour = this->partialMergedSubtours->size()-1;

	cout << endl << "HTSP Solution:" << endl
		 << this->partialMergedSubtours->at(lastPartialSubtour)->tour->ToString()
		 << " (" << this->partialMergedSubtours->at(lastPartialSubtour)->tour->TotalDistance() << ")"
		 << endl << endl;

	return this->partialMergedSubtours->at(lastPartialSubtour)->tour;
}

void HtspSolver::ExtractSubinstances() {
	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subinstances->push_back(new Instance());
	}
	for (int n=0; n<this->instance->Size(); n++) {
		pNode node = this->instance->GetNode(n);
		int subtourIndex = this->GetSubtourIndexByPriority(node->Priority);

		this->subinstances->at(subtourIndex)->Add(node);
	}
}





pTour HtspSolver::SolveTypeI() {
	this->SolveAsTsp(this->instance);
	cout << endl << "TSP Solution:" << endl;
	cout << this->geniusSolution->ToString() << " (" << this->geniusSolution->TotalDistance() << ")" << endl;

	this->ExtractSubtours();
	cout << endl << "Extracted Subtours:" << endl;
	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subtours->at(s)->Print();
	}

	this->partialMergedSubtours->push_back(this->subtours->at(0));
	for(int s=0; s<(int)this->subtours->size()-1; s++) {
		pSubtour first = this->partialMergedSubtours->at(s);
		pSubtour second = this->subtours->at(s+1);

		this->partialMergedSubtours->push_back(this->MergeSubtours(first, second));
	}

	cout << endl << "Partial Merged Subtours:" << endl;
	for (int s=0; s<(int)this->partialMergedSubtours->size(); s++) {
		this->partialMergedSubtours->at(s)->Print();
	}

	int lastPartialSubtour = this->partialMergedSubtours->size()-1;

	cout << endl << "HTSP Solution:" << endl
		 << this->partialMergedSubtours->at(lastPartialSubtour)->tour->ToString()
		 << " (" << this->partialMergedSubtours->at(lastPartialSubtour)->tour->TotalDistance() << ")"
		 << endl << endl;

	return this->partialMergedSubtours->at(lastPartialSubtour)->tour;
}

void HtspSolver::SolveAsTsp(pInstance instance) {
	this->geniusSolution = this->ExecuteGenius(instance);
}

pTour HtspSolver::ExecuteGenius(pInstance instance) {
	this->geniSolution = this->genius->ExecuteGeni(instance, 4);
	pTour geniusTour = this->genius->ExecuteUs(this->geniSolution, 4);

	return geniusTour;
}

void HtspSolver::ExtractSubtours() {
	pNode lastNode = NULL;
	pSubtour lastSubtour = NULL;

	for (int n=0; n<this->geniusSolution->Length(); n++) {
		pNode node = this->geniusSolution->Get(n);
		pSubtour subtour = this->GetSubtourByPriority(node->Priority);

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
	for (int s=0; s<(int)this->subtours->size(); s++) {
		pSubtour subtour = this->subtours->at(s);
		pArc lastArc = subtour->candidateArcs->at(subtour->candidateArcs->size()-1);
		if (lastArc->To == NULL) {
			lastArc->To = subtour->tour->Get(0);
		}
	}
}

int HtspSolver::GetSubtourIndexByPriority(int p) {
	int prioritiesPerSubtour = this->GetNumberOfPrioritiesPerSubtour();
	int subtourIndex = (int)floor( (double)p / (double)(prioritiesPerSubtour + 1) );

	if (0 <= subtourIndex && subtourIndex < (int)this->subtours->size()) {
		return subtourIndex;
	}
	return -1;
}

pSubtour HtspSolver::GetSubtourByPriority(int p) {
	int index = this->GetSubtourIndexByPriority(p);
	if (index > -1) {
		return this->subtours->at(index);
	}
	return NULL;
}

pArc HtspSolver::GetFreeArc(pSubtour subtour) {
	int arcs = (int)subtour->candidateArcs->size();
	pArc lastArc = subtour->candidateArcs->at(arcs-1);

	if (lastArc->To != NULL) {
		subtour->candidateArcs->push_back(new Arc());
		lastArc = subtour->candidateArcs->at(arcs);
	}

	return lastArc;
}

pSubtour HtspSolver::MergeSubtours(pSubtour first, pSubtour second) {
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

void HtspSolver::AppendTour(pTour source, pNode startingNodeInSource, pTour destination) {
	source->GoTo(startingNodeInSource);
	pNode n = source->Next();
	destination->Append(n);
	while (n != source->Current()) {
		pNode current = source->Current();
		destination->Append(current);
		source->Next();
	}
}
















/*
pSubtourVector HtspSolver::ExtractSubtours(pTour fullTour, int P, int k) {
	pSubtourVector subtours = this->InitSubtours(P);



	// per ogni nodo del fulltour
		//


}
*/





















// Vecchio solver HTSP --------------------------------------------------
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
// ----------------------------------------------------------------------


//pTour HtspSolver::Solve1() {

	// Calcola la soluzione del problema TSP associato

	// Separa il tour ottenuto in P/(d+1) subtour (uno per ogni cluster di nodi con priorità ammissibili)

	// Per ogni subtour, ottiene l'elenco dei nuovi archi inseriti per rendere il tour connesso

	// Ottiene le connessioni più economiche tra due tour

	// Connette i subtour utilizzando le connessioni ottenute e produce il tour finale
//}

//pTour HtspSolver::Solve2() {

	// Ottiene P/(d+1) istanze dall'istanza HTSP

	// Risolve ogni istanza come TSP con geni ottenendo P/(d+1) subtour (uno per ogni cluster di nodi con priorità ammissibili)

	// Ottiene le connessioni più economiche tra due tour

	// Connette i subtour utilizzando le connessioni ottenute e produce il tour finale
//}

pTour HtspSolver::SolveOld() {
	pTourFactory tf = new TourFactory(this->instance);

	pTour htspTour = tf->GetTour();

	pGenius genius = new Genius();
	pTour geniSol = genius->ExecuteGeni(this->instance, 4);
	cout << endl << "geniSol: " << geniSol->ToString() << " (" << geniSol->TotalDistance() << ")" << endl;
	pTour geniusSol = genius->ExecuteUs(geniSol, 4);
	cout << "geniusSol: " << geniusSol->ToString() << " (" << geniusSol->TotalDistance() << ")" << endl << endl;

	int P = this->instance->P;
	int k = this->instance->k;

	int subset = (int)ceil( (double)P / ((double)k + 1) );

	pTourVector subtours = new TourVector();

	for (int s=0; s<subset; s++) {
		pTour subtour = tf->GetTour();

		double c = ceil((double)P/(double)k);
		int mul = (int)c;
		int startingPriorityLevel = (s*mul) + 1;
		int endingPriorityLevel = startingPriorityLevel + k;

		cout << "subset " << s << " priorities between " << startingPriorityLevel << " and " << endingPriorityLevel << endl;

		for (int n=0; n<geniusSol->Length(); n++) {
			pNode node = geniusSol->Get(n);

			if (node->Priority >= startingPriorityLevel &&
				node->Priority <= endingPriorityLevel) {
				subtour->Append(node);
			}
		}

		subtours->push_back(subtour);
	}

	candidateNodes = new vector<pNodeVector>();

	for (int s=0; s<(int)subtours->size(); s++) {
		pTour t = subtours->at(s);
		cout << endl << "subtour " << s << ": " << t->ToString() << " (" << t->TotalDistance() << ")" << endl;

		pNodeVector candidates = new NodeVector();

		// Cerca i nuovi archi inseriti per connettere il subtour ------------------
		if (t->Length() > 0) {
			for (int n=0; n<t->Length()-1; n++) {
				pNode from = t->Get(n);
				pNode to = t->Get(n+1);
				if (!geniusSol->ContainsArc(from, to))
				{
					cout << "arc added " << from->ToString() << " => " << to->ToString() << " (" << from->DistanceFrom(to) << ")" << endl;
					candidates->push_back(from);
					candidates->push_back(to);
				}
			}

			pNode from = t->Get(t->Length()-1);
			pNode to = t->Get(0);
			if (!geniusSol->ContainsArc(from, to))
			{
				cout << "arc added " << from->ToString() << " => " << to->ToString() << " (" << from->DistanceFrom(to) << ")" << endl;
				candidates->push_back(from);
				candidates->push_back(to);
			}
		}

		candidateNodes->push_back(candidates);
	}

	double total = 0;
	for (int s=0; s<(int)subtours->size(); s++) {
		total += subtours->at(s)->TotalDistance();
	}
	cout << endl << "subtours total distance =" << total << endl << endl;

	for (int s=0; s<(int)subtours->size()-1; s+=2) {
		pNodeVector candidatesForFirstSubtour = candidateNodes->at(s);
		pNodeVector candidatesForSecondSubtour = candidateNodes->at(s+1);

		double maxJoinRatio = 0;
		pNode bestFirstArcStart = NULL;
		pNode bestFirstArcEnd = NULL;
		pNode bestSecondArcStart = NULL;
		pNode bestSecondArcEnd = NULL;

		for (int i=0; i<(int)candidatesForFirstSubtour->size()-1; i+=2) {
			pNode firstArcStart = candidatesForFirstSubtour->at(i);
			pNode firstArcEnd = candidatesForFirstSubtour->at(i+1);

			for (int j=0; j<(int)candidatesForSecondSubtour->size()-1; j+=2) {
				pNode secondArcStart = candidatesForSecondSubtour->at(j);
				pNode secondArcEnd = candidatesForSecondSubtour->at(j+1);

				double firstArcToRemoveDistance = firstArcStart->DistanceFrom(firstArcEnd);
				double secondArcToRemoveDistance = secondArcStart->DistanceFrom(secondArcEnd);
				double R = firstArcToRemoveDistance + secondArcToRemoveDistance;

				double firstArcToInsertDistance = firstArcStart->DistanceFrom(secondArcEnd);
				double secondArcToInsertDistance = secondArcStart->DistanceFrom(firstArcEnd);
				double I = firstArcToInsertDistance + secondArcToInsertDistance;

				cout << "REM "
					 << firstArcStart->ToString() << " => " << firstArcEnd->ToString() << ", "
					 << secondArcStart->ToString() << " => " << secondArcEnd->ToString()
					 << " R=" << R << endl;

				cout << "INS "
					 << firstArcStart->ToString() << " => " << secondArcEnd->ToString() << ", "
					 << secondArcStart->ToString() << " => " << firstArcEnd->ToString()
					 << " I=" << I << " R/I=" << R/I << " DISTANCE=" << total - R + I << endl;

				double currentJoinRatio = R / I;

				if (currentJoinRatio > maxJoinRatio) {
					maxJoinRatio = currentJoinRatio;
					bestFirstArcStart = firstArcStart;
					bestFirstArcEnd = firstArcEnd;
					bestSecondArcStart = secondArcStart;
					bestSecondArcEnd = secondArcEnd;
				}
			}
		}

		cout << endl << "maxJoinRatio=" << maxJoinRatio << " "
			 << bestFirstArcStart->Id << " => " << bestFirstArcEnd->Id << ", "
			 << bestSecondArcStart->Id << " => " << bestSecondArcEnd->Id << endl;

		pTour firstSubtour = subtours->at(s);
		pTour secondSubtour = subtours->at(s+1);

		firstSubtour->GoTo(bestFirstArcEnd);
		pNode n = firstSubtour->Next();
		htspTour->Append(n);
		while (n != firstSubtour->Current()) {
			pNode current = firstSubtour->Current();
			htspTour->Append(current);
			firstSubtour->Next();
		}

		secondSubtour->GoTo(bestSecondArcEnd);
		n = secondSubtour->Next();
		htspTour->Append(n);
		while (n != secondSubtour->Current()) {
			pNode current = secondSubtour->Current();
			htspTour->Append(current);
			secondSubtour->Next();
		}
	}

	cout << "HTSP TOUR: " << htspTour->ToString() << " (" << htspTour->TotalDistance() << ")" << endl;

	// TODO: Aggiungere DEPOT!!!!!

	// -----------------------------------------------

	// Procedura join subtours
	// -----------------------

	// 1 - per ogni subtour ottenere l'elenco (As) degli archi inseriti quando lo si è creato
	// 2 - prendere gli (As) a coppie A1 con A2, A2 con A3, A3 con A4, ...
	// 2.1 - fare un doppio ciclo tra archi del primo e del secondo e ottenere la somma R
	// 2.2 - ottenere il costo I dato dalla somma dei 2 archi che si dovrebbero inserire se si rimuovesse gli R
	// 2.3 - calcolare R/I e salvarsi via gli archi se R/I aumenta
	// 3 - applicare la modifica che ha dato R/I massimo

	return htspTour;
}

//pNode HtspSolver::GetFirstNodeByPriorityLevel(pInstance instance, int priorityLevel) {
//	for (int n=0; n<instance->Size(); n++) {
//		pNode node = instance->GetNode(n);
//		if (node->Priority == priorityLevel) {
//			return node;
//		}
//	}
//	return NULL;
//}

pNodeVector HtspSolver::GetAllNodesByPriorityLevel(pInstance instance, int priorityLevel) {
	pNodeVector nodesFound = new NodeVector();
	for (int n=0; n<instance->Size(); n++) {
		pNode node = instance->GetNode(n);
		if (node->Priority == priorityLevel) {
			nodesFound->push_back(node);
		}
	}
	return nodesFound;
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
