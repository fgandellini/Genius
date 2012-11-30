#include "Genius.h"

namespace Genius {

Genius::Genius() {
	this->p = INF;
}

Genius::~Genius() {
}

InsertTypeIParams Genius::EvaluateBestInsertTypeIParams(pTour tour, pNode v) {
	InsertTypeIParams bestParamsForward;
	bestParamsForward.vi = NULL;
	bestParamsForward.vj = NULL;
	bestParamsForward.vk = NULL;
	bestParamsForward.distance = INF_DISTANCE;
	bestParamsForward.tourMustBeReversed = false;

	InsertTypeIParams bestParamsBackward;
	bestParamsBackward.vi = NULL;
	bestParamsBackward.vj = NULL;
	bestParamsBackward.vk = NULL;
	bestParamsBackward.distance = INF_DISTANCE;
	bestParamsBackward.tourMustBeReversed = true;

	bestParamsForward =
		this->EvaluateBestInsertTypeIParamsWithOrientedTour(tour, v);

	tour->Reverse();

	bestParamsBackward =
		this->EvaluateBestInsertTypeIParamsWithOrientedTour(tour, v);

	tour->Reverse();

	if (bestParamsForward.distance < bestParamsBackward.distance) {
		bestParamsForward.tourMustBeReversed = false;
		return bestParamsForward;
	} else {
		bestParamsBackward.tourMustBeReversed = true;
		return bestParamsBackward;
	}
}

InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParams(pTour tour, pNode v) {
	InsertTypeIIParams bestParamsForward;
	bestParamsForward.vi = NULL;
	bestParamsForward.vj = NULL;
	bestParamsForward.vk = NULL;
	bestParamsForward.vl = NULL;
	bestParamsForward.distance = INF_DISTANCE;
	bestParamsForward.tourMustBeReversed = false;

	InsertTypeIIParams bestParamsBackward;
	bestParamsBackward.vi = NULL;
	bestParamsBackward.vj = NULL;
	bestParamsBackward.vk = NULL;
	bestParamsBackward.vl = NULL;
	bestParamsBackward.distance = INF_DISTANCE;
	bestParamsBackward.tourMustBeReversed = true;

//	cout << "FORWARD" << endl;
	bestParamsForward =
		this->EvaluateBestInsertTypeIIParamsWithOrientedTour(tour, v);

	tour->Reverse();

//	cout << "BACKWARD" << endl;
	bestParamsBackward =
		this->EvaluateBestInsertTypeIIParamsWithOrientedTour(tour, v);

	tour->Reverse();

	if (bestParamsForward.distance < bestParamsBackward.distance) {
		bestParamsForward.tourMustBeReversed = false;
		return bestParamsForward;
	} else {
		bestParamsBackward.tourMustBeReversed = true;
		return bestParamsBackward;
	}
}

InsertTypeIParams Genius::EvaluateBestInsertTypeIParamsWithOrientedTour(pTour tour, pNode v) {
	double currentTourDistance = 0;

	InsertTypeIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

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

				if ( (vi->Id != vj->Id) &&
					  (vk->Id != vi->Id) &&
					  (vk->Id != vj->Id) &&
					  tour->IsBetween(vk, vj, vi)) {

					currentTourDistance = tour->EvaluateInsertTypeI(v, vi, vj, vk);

					if (currentTourDistance <= bestParams.distance) {
						bestParams.distance = currentTourDistance;
						bestParams.vi = vi;
						bestParams.vj = vj;
						bestParams.vk = vk;
					}
				}
			}
		}
	}
	return bestParams;
}

/*
InsertTypeIParams Genius::EvaluateBestInsertTypeIParamsWithOrientedTour(pTour tour, pNode v) {

	double currentTourDistance = 0;
	//bool tourHasBeenReversed = false;

	InsertTypeIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

	//tour->Reverse();

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

				if ( (vi->Id != vj->Id) &&
					  (vk->Id != vi->Id) &&
					  (vk->Id != vj->Id) &&
					  tour->IsBetween(vk, vj, vi)) {

					// Inverte il tour se necessario
//					if ( tour->IsBetween(vk, vj, vi) ) {
//						tourHasBeenReversed = false;
//					} else {
//						tour->Reverse();
//						tourHasBeenReversed = true;
//					}

					currentTourDistance = tour->EvaluateInsertTypeI(v, vi, vj, vk);
//					cout << currentTourDistance;

//					if (tourHasBeenReversed) {
////						cout << " (rev)";
//						tour->Reverse();
//					}

					if (currentTourDistance <= bestParams.distance) {
						bestParams.distance = currentTourDistance;
						bestParams.vi = vi;
						bestParams.vj = vj;
						bestParams.vk = vk;
						//bestParams.tourMustBeReversed = tourHasBeenReversed;
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
*/

InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParamsWithOrientedTour(pTour tour, pNode v) {
	double currentTourDistance = 0;

	InsertTypeIIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.vl = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

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

				if ( (vk->Id != vj->Id) && (vk->Id != vjplus1->Id) && tour->IsBetween(vk, vj, vi) ) {

					pNodeVector vjplus1Neighborhood = tour->GetNeighborhood(vjplus1);
					int nodesToEvaluate3 = min(this->p, (int)vjplus1Neighborhood->size());

//					cout << vj->Id << " ] vjplus1 (" << vjplus1->Id
//						 << ") Neighborhood :";
//					for (int n=0; n<(int)vjplus1Neighborhood->size(); n++) {
//						cout << vjplus1Neighborhood->at(n)->Id << " ("
//							 << vjplus1->DistanceFrom(vjplus1Neighborhood->at(n))
//							 << ") >> ";
//					}
//					cout << endl;

					for (int l=0; l<nodesToEvaluate3; l++) {
						pNode vl = vjplus1Neighborhood->at(l);

						if ( (vl->Id != vi->Id) && (vl->Id != viplus1->Id) && tour->IsBetween(vl, vi, vj) ) {

							currentTourDistance = tour->EvaluateInsertTypeII(v, vi, vj, vk, vl);
//							cout << v->Id << "  " << vi->Id << "  " << vj->Id << "  " << vk->Id << "  " << vl->Id << "  " << flush;
//							cout << currentTourDistance;
//							cout << endl;


							if (currentTourDistance <= bestParams.distance) {
								bestParams.distance = currentTourDistance;
								bestParams.vi = vi;
								bestParams.vj = vj;
								bestParams.vk = vk;
								bestParams.vl = vl;
							}
						}
					}
				}
			}
		}
	}

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

void Genius::StringNodeInTour(pNode node, pTour tour) {

	InsertTypeIParams bestParamsForTypeI;
	bestParamsForTypeI.vi = NULL;
	bestParamsForTypeI.vj = NULL;
	bestParamsForTypeI.vk = NULL;
	bestParamsForTypeI.distance = INF_DISTANCE;
	bestParamsForTypeI.tourMustBeReversed = false;

	InsertTypeIIParams bestParamsForTypeII;
	bestParamsForTypeII.vi = NULL;
	bestParamsForTypeII.vj = NULL;
	bestParamsForTypeII.vk = NULL;
	bestParamsForTypeII.vl = NULL;
	bestParamsForTypeII.distance = INF_DISTANCE;
	bestParamsForTypeII.tourMustBeReversed = true;

	bestParamsForTypeI =
		this->EvaluateBestInsertTypeIParams(tour, node);

	bestParamsForTypeII =
		this->EvaluateBestInsertTypeIIParams(tour, node);

	if (bestParamsForTypeI.distance < bestParamsForTypeII.distance) {
		tour->InsertTypeI(node,
			bestParamsForTypeI.vi,
			bestParamsForTypeI.vj,
			bestParamsForTypeI.vk);
	} else {
		tour->InsertTypeII(node,
			bestParamsForTypeII.vi,
			bestParamsForTypeII.vj,
			bestParamsForTypeII.vk,
			bestParamsForTypeII.vl);
	}
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
