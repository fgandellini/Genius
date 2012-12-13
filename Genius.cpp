#include "Genius.h"

namespace Genius {

Genius::Genius() {
	this->tourFactory = new TourFactory();
}

Genius::~Genius() {
	SAFE_DELETE(this->tourFactory);
}

InsertTypeIParams Genius::EvaluateBestInsertTypeIParams(pTour tour, pNode v, int neighborhoodSize) {
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
		this->EvaluateBestInsertTypeIParamsWithOrientedTour(tour, v, neighborhoodSize);

	tour->Reverse();

	bestParamsBackward =
		this->EvaluateBestInsertTypeIParamsWithOrientedTour(tour, v, neighborhoodSize);

	tour->Reverse();

	if (bestParamsForward.distance < bestParamsBackward.distance) {
		bestParamsForward.tourMustBeReversed = false;
		return bestParamsForward;
	} else {
		bestParamsBackward.tourMustBeReversed = true;
		return bestParamsBackward;
	}
}

InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParams(pTour tour, pNode v, int neighborhoodSize) {
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
		this->EvaluateBestInsertTypeIIParamsWithOrientedTour(tour, v, neighborhoodSize);

	tour->Reverse();

	//	cout << "BACKWARD" << endl;
	bestParamsBackward =
		this->EvaluateBestInsertTypeIIParamsWithOrientedTour(tour, v, neighborhoodSize);

	tour->Reverse();

	if (bestParamsForward.distance < bestParamsBackward.distance) {
		bestParamsForward.tourMustBeReversed = false;
		return bestParamsForward;
	} else {
		bestParamsBackward.tourMustBeReversed = true;
		return bestParamsBackward;
	}
}

InsertTypeIParams Genius::EvaluateBestInsertTypeIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize) {
	double currentTourDistance = 0;

	InsertTypeIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

    pNodeVector vNeighborhood = tour->GetNeighborhood(v);
    int nodesToEvaluate = min(neighborhoodSize, (int)vNeighborhood->size());

	for (int i=0; i<nodesToEvaluate; i++) {
		pNode vi = vNeighborhood->at(i);
		pNode viplus1 = tour->Next(vi);

		for (int j=0; j<nodesToEvaluate; j++) {
			pNode vj = vNeighborhood->at(j);

			pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
			int nodesToEvaluate2 = min(neighborhoodSize, (int)viplus1Neighborhood->size());

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

InsertTypeIIParams Genius::EvaluateBestInsertTypeIIParamsWithOrientedTour(pTour tour, pNode v, int neighborhoodSize) {
	double currentTourDistance = 0;

	InsertTypeIIParams bestParams;
	bestParams.vi = NULL;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.vl = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

    pNodeVector vNeighborhood = tour->GetNeighborhood(v);
    int nodesToEvaluate = min(neighborhoodSize, (int)vNeighborhood->size());

	for (int i=0; i<nodesToEvaluate; i++) {
		pNode vi = vNeighborhood->at(i);
		pNode viplus1 = tour->Next(vi);

		for (int j=0; j<nodesToEvaluate; j++) {
			pNode vj = vNeighborhood->at(j);
			pNode vjplus1 = tour->Next(vj);

			pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
			int nodesToEvaluate2 = min(neighborhoodSize, (int)viplus1Neighborhood->size());

			for (int k=0; k<nodesToEvaluate2; k++) {
				pNode vk = viplus1Neighborhood->at(k);

				if ( (vk->Id != vj->Id) && (vk->Id != vjplus1->Id) && tour->IsBetween(vk, vj, vi) ) {

					pNodeVector vjplus1Neighborhood = tour->GetNeighborhood(vjplus1);
					int nodesToEvaluate3 = min(neighborhoodSize, (int)vjplus1Neighborhood->size());

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

void Genius::StringNodeInTour(pNode node, pTour tour, int neighborhoodSize) {

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
	bestParamsForTypeII.tourMustBeReversed = false;

	bestParamsForTypeI =
		this->EvaluateBestInsertTypeIParams(tour, node, neighborhoodSize);

	bestParamsForTypeII =
		this->EvaluateBestInsertTypeIIParams(tour, node, neighborhoodSize);

	if (bestParamsForTypeI.distance < bestParamsForTypeII.distance) {
		if (bestParamsForTypeI.tourMustBeReversed) {
			tour->Reverse();
		}
		tour->InsertTypeI(node,
			bestParamsForTypeI.vi,
			bestParamsForTypeI.vj,
			bestParamsForTypeI.vk);
	} else {
		if (bestParamsForTypeII.tourMustBeReversed) {
			tour->Reverse();
		}
		tour->InsertTypeII(node,
			bestParamsForTypeII.vi,
			bestParamsForTypeII.vj,
			bestParamsForTypeII.vk,
			bestParamsForTypeII.vl);
	}
}

pTour Genius::ExecuteGeni(pInstance nodesToVisit, int neighborhoodSize) {
	pTour tour = tourFactory->SetInstance(nodesToVisit)->GetTour();

	this->InitializeTourWithThreeNodes(tour, nodesToVisit);

	for (int n=0; n<(int)nodesToVisit->Size(); n++) {
		pNode nodeToInsert = nodesToVisit->GetNode(n);

		if (!tour->Contains(nodeToInsert)) {
			this->StringNodeInTour(nodeToInsert, tour, neighborhoodSize);
		}
	}

	return tour;
}

void Genius::InitializeTourWithThreeNodes(pTour tour, pInstance nodesToVisit) {
	assert(nodesToVisit->Size() >= 4);
	tour->Append(nodesToVisit->GetNode(0));
	tour->Append(nodesToVisit->GetNode(1));
	tour->Append(nodesToVisit->GetNode(2));
}

void Genius::ExecuteUs(pTour tour) {
	pTour bestTour = NULL;
	double bestTourDistance = INF_DISTANCE;
	int currentNodeOfTour = 0;

	// per sempre for(;;)
	{
		// ottiene il nodo corrente del tour currentNodeOfTour (=vt)
		// esegui unstringing di vt

		// valuta stringing di vt (=z)

		// se z < bestTourDistance
			// currentNodeOfTour = 0
			// bestTourDistance = z
			// bestTour = tour ottenuto con l'insert

		// altrimenti
			// se ho nodi nel tour
				// currentNodeOfTour++
			// altrimenti
				// fine
	}

}

} /* namespace Genius */
