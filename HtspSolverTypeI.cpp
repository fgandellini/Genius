#include "HtspSolverTypeI.h"

namespace Genius {

HtspSolverTypeI::HtspSolverTypeI(pInstance instance) {
	this->instance = instance;
	this->solverUtils = new HtspSolverUtils();

	this->tspSolution = NULL;
	this->subtours = NULL;
	this->partialMergedSubtours = new SubtourVector();
}

HtspSolverTypeI::~HtspSolverTypeI() {
	SAFE_DELETE(this->solverUtils);
	SAFE_DELETE(this->tspSolution);

	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);

	for(int s=1; s<(int)partialMergedSubtours->size(); s++) {
		SAFE_DELETE(partialMergedSubtours->at(s));
	}
	SAFE_DELETE(partialMergedSubtours);
}





pTour HtspSolverTypeI::Solve() {
	cout << endl << endl
		 << "HTSP SOLVER Type I "
		 << "[" << this->instance->Name << "]"
		 << endl << endl;

	this->tspSolution = this->solverUtils->ExecuteGenius(this->instance);
	cout << endl << "TSP Solution:" << endl;
	cout << this->tspSolution->ToString() << " (" << this->tspSolution->TotalDistance() << ")" << endl;

	this->subtours = this->solverUtils->ExtractSubtours(this->instance, this->tspSolution);
	cout << endl << "Extracted Subtours:" << endl;
	for (int s=0; s<(int)this->subtours->size(); s++) {
		this->subtours->at(s)->Print();
	}

	this->partialMergedSubtours->push_back(this->subtours->at(0));
	for(int s=0; s<(int)this->subtours->size()-1; s++) {
		pSubtour first = this->partialMergedSubtours->at(s);
		pSubtour second = this->subtours->at(s+1);

		this->partialMergedSubtours->push_back(this->solverUtils->MergeSubtours(this->instance, first, second));
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

	return this->partialMergedSubtours->at(lastPartialSubtour)->tour->Clone();
}





















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

//	// Procedura join subtours
//	// -----------------------
//
//	// 1 - per ogni subtour ottenere l'elenco (As) degli archi inseriti quando lo si è creato
//	// 2 - prendere gli (As) a coppie A1 con A2, A2 con A3, A3 con A4, ...
//	// 2.1 - fare un doppio ciclo tra archi del primo e del secondo e ottenere la somma R
//	// 2.2 - ottenere il costo I dato dalla somma dei 2 archi che si dovrebbero inserire se si rimuovesse gli R
//	// 2.3 - calcolare R/I e salvarsi via gli archi se R/I aumenta
//	// 3 - applicare la modifica che ha dato R/I massimo
//
//	return htspTour;
//}



} /* namespace Genius */
