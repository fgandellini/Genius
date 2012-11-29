#include "Genius.h"

namespace Genius {

Genius::Genius() {
	this->p = INF;
}

Genius::~Genius() {
}

InsertTypeIParams Genius::EvaluateBestInsertTypeIParams(pTour tour, pNode v) {

	double currentTourDistance = 0;
	bool tourHasBeenReversed = false;

	InsertTypeIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

	tour->Reverse();

//	cout << endl << "evaluating insert (typeI) of " << v->Id
//		 << " in tour " << tour->ToString()
//		 << " (distance: " << tour->TotalDistance() << ")" << endl
//		 << "v  vi vj vk distance" << endl
//		 << "-- -- -- -- --------" << endl;

	this->p = 4;
    pNodeVector vNeighborhood = tour->GetNeighborhood(v);
    int nodesToEvaluate = min(this->p, (int)vNeighborhood->size());

	for (int i=0; i<nodesToEvaluate; i++) {
		pNode vi = vNeighborhood->at(i);
		pNode viplus1 = tour->Next(vi);

		for (int j=0; j<nodesToEvaluate; j++) {
			pNode vj = vNeighborhood->at(j);

			pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
			int nodesToEvaluate2 = min(this->p, (int)viplus1Neighborhood->size());

			for (int k=0; k<nodesToEvaluate2; k++) {
				pNode vk = viplus1Neighborhood->at(k);

//				cout << v->Id << "  " << vi->Id << "  " << vj->Id << "  " << vk->Id << "  " << flush;

				if ( (vi->Id != vj->Id) && (vk->Id != vi->Id) && (vk->Id != vj->Id) ) {

					// Inverte il tour se necessario
					if ( tour->IsBetween(vk, vj, vi) ) {
						tourHasBeenReversed = false;
					} else {
						tour->Reverse();
						tourHasBeenReversed = true;
					}

					currentTourDistance = tour->EvaluateInsertTypeI(v, vi, vj, vk);
//					cout << currentTourDistance;

					if (tourHasBeenReversed) {
//						cout << " (rev)";
						tour->Reverse();
					}

					if (currentTourDistance <= bestParams.distance) {
						bestParams.distance = currentTourDistance;
						bestParams.vi = vi;
						bestParams.vj = vj;
						bestParams.vk = vk;
						bestParams.tourMustBeReversed = tourHasBeenReversed;
					}
				}
//				} else {
//					cout << "[not feasible]";
//				}
//				cout << endl;
			}
		}
	}

//	cout << ">  "
//		 << bestParams.vi->Id << "  "
//		 << bestParams.vj->Id << "  "
//		 << bestParams.vk->Id << "  "
//		 << bestParams.distance
//		 << bestParams.tourMustBeReversed ? "(rev)" : "";

	return bestParams;
}

InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParams(pTour tour, pNode v) {

	double currentTourDistance = 0;
	bool tourHasBeenReversed = false;

	InsertTypeIIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.vl = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

	tour->Reverse();

	cout << endl << "evaluating insert (typeII) of " << v->Id
		 << " in tour " << tour->ToString()
		 << " (distance: " << tour->TotalDistance() << ")" << endl
		 << "v  vi vj vk vl distance" << endl
		 << "-- -- -- -- -- --------" << endl;

	this->p = 4;
    pNodeVector vNeighborhood = tour->GetNeighborhood(v);
    int nodesToEvaluate = min(this->p, (int)vNeighborhood->size());

	for (int i=0; i<nodesToEvaluate; i++) {
		pNode vi = vNeighborhood->at(i);
		pNode viplus1 = tour->Next(vi);

		for (int j=0; j<nodesToEvaluate; j++) {
			pNode vj = vNeighborhood->at(j);
			pNode vjplus1 = tour->Next(vj);

			pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
			int nodesToEvaluate2 = min(this->p, (int)viplus1Neighborhood->size());

			for (int k=0; k<nodesToEvaluate2; k++) {
				pNode vk = viplus1Neighborhood->at(k);

				pNodeVector vjplus1Neighborhood = tour->GetNeighborhood(vjplus1);
				int nodesToEvaluate3 = min(this->p, (int)vjplus1Neighborhood->size());

				for (int l=0; l<nodesToEvaluate3; l++) {
					pNode vl = vjplus1Neighborhood->at(l);

					cout << v->Id << "  " << vi->Id << "  " << vj->Id << "  " << vk->Id << "  " << vl->Id << "  " << flush;

					if ( (vk->Id != vj->Id) &&
						 (vk->Id != vjplus1->Id) &&
						 (vl->Id != vi->Id) &&
						 (vl->Id != viplus1->Id) ) {

						// Inverte il tour se necessario
						if ( tour->IsBetween(vk, vj, vi) && tour->IsBetween(vl, vi, vj) ) {
							tourHasBeenReversed = false;
						} else {
							tour->Reverse();
							tourHasBeenReversed = true;
						}

						currentTourDistance = tour->EvaluateInsertTypeII(v, vi, vj, vk, vl);
						cout << currentTourDistance;

						if (tourHasBeenReversed) {
							cout << " (rev)";
							tour->Reverse();
						}

						if (currentTourDistance <= bestParams.distance) {
							bestParams.distance = currentTourDistance;
							bestParams.vi = vi;
							bestParams.vj = vj;
							bestParams.vk = vk;
							bestParams.vl = vl;
							bestParams.tourMustBeReversed = tourHasBeenReversed;
						}
					} else {
						cout << "[not feasible]";
					}
					cout << endl;
				}
			}
		}
	}

//	cout << ">  "
//		 << bestParams.vi->Id << "  "
//		 << bestParams.vj->Id << "  "
//		 << bestParams.vk->Id << "  "
//		 << bestParams.distance
//		 << bestParams.tourMustBeReversed ? "(rev)" : "";

	return bestParams;
}

//InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParams(pTour tour, pNode v) {
//
//	double currentTourDistance = 0;
//	bool tourHasBeenReversed = false;
//
//	InsertTypeIIParams bestParams;
//	bestParams.vi = NULL;
//	bestParams.vj = NULL;
//	bestParams.vk = NULL;
//	bestParams.vl = NULL;
//	bestParams.distance = INF_DISTANCE;
//	bestParams.tourMustBeReversed = false;
//
////	cout << endl << "evaluating insert (typeI) of " << v->Id
////		 << " in tour " << tour->ToString()
////		 << " (distance: " << tour->TotalDistance() << ")" << endl
////		 << "v  vi vj vk distance" << endl
////		 << "-- -- -- -- -------------" << endl;
//
//	int tourLen = tour->Length();
//	for (int i=0; i<tourLen; i++) {
//		pNode vi = tour->Get(i);
//
//		for (int j=0; j<tourLen; j++) {
//			pNode vj = tour->Get(j);
//
//			for (int k=0; k<tourLen; k++) {
//				pNode vk = tour->Get(k);
//
//				for (int l=0; l<tourLen; l++) {
//					pNode vl = tour->Get(l);
//
//					if (tour->CheckInsertTypeIIConditions(vi, vj, vk, vl)) {
//	//					cout << v->Id << "  " << vi->Id << "  " << vj->Id << "  " << vk->Id << "  ";
//
//						tourHasBeenReversed = false;
//						currentTourDistance = tour->EvaluateInsertTypeII(v, vi, vj, vk, vl);
//	//					cout << currentTourDistance;
//
//						if ( currentTourDistance >= (INF_DISTANCE-1) ) {
//							tour->Reverse();
//							tourHasBeenReversed = true;
//							currentTourDistance = tour->EvaluateInsertTypeII(v, vi, vj, vk, vl);
//	//						cout << " (rev = " << currentTourDistance << ")";
//							tour->Reverse();
//						}
//
//						if (currentTourDistance <= bestParams.distance) {
//							bestParams.distance = currentTourDistance;
//							bestParams.vi = vi;
//							bestParams.vj = vj;
//							bestParams.vk = vk;
//							bestParams.vl = vl;
//							bestParams.tourMustBeReversed = tourHasBeenReversed;
//						}
//
//	//					cout << endl;
//					}
//				}
//			}
//		}
//	}
//
////	cout << ">  "
////		 << bestParams.vi->Id << "  "
////		 << bestParams.vj->Id << "  "
////		 << bestParams.vk->Id << "  "
////		 << bestParams.distance
////		 << bestParams.tourMustBeReversed ? "(rev)" : "";
//
//	return bestParams;
//}


InsertTypeIParams Genius::EvaluateBestInsertionPoint(pTour tour, pNode v) {
	return this->EvaluateBestInsertTypeIParams(tour, v);
}


void Genius::Geni(pTour initialTour, pInstance nodesToVisit) {



/*

	pTour tour = initialTour;
	for (int n=0; n<(int)nodesToVisit->size(); n++) {
		minDistance = INF_DISTANCE;
		pNode v = nodesToVisit->at(n);


		tour->InsertTypeI(v, minVi, minVj, minVk);

		if (v->Id == 6) return;
	}
	*/
}



} /* namespace Genius */
