#include "Genius.h"

namespace Genius {

Genius::Genius() {
	this->tourFactory = new TourFactory();
	this->drawer = new Drawer();
}

Genius::~Genius() {
	SAFE_DELETE(this->tourFactory);
	SAFE_DELETE(this->drawer);
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

RemoveTypeIParams Genius::EvaluateBestRemoveTypeIParams(pTour tour, pNode vi, int neighborhoodSize) {
	RemoveTypeIParams bestParamsForward;
	bestParamsForward.vj = NULL;
	bestParamsForward.vk = NULL;
	bestParamsForward.distance = INF_DISTANCE;
	bestParamsForward.tourMustBeReversed = false;

	RemoveTypeIParams bestParamsBackward;
	bestParamsBackward.vj = NULL;
	bestParamsBackward.vk = NULL;
	bestParamsBackward.distance = INF_DISTANCE;
	bestParamsBackward.tourMustBeReversed = true;

	bestParamsForward =
		this->EvaluateBestRemoveTypeIParamsWithOrientedTour(tour, vi, neighborhoodSize);

	tour->Reverse();

	bestParamsBackward =
		this->EvaluateBestRemoveTypeIParamsWithOrientedTour(tour, vi, neighborhoodSize);

	tour->Reverse();

	if (bestParamsForward.distance < bestParamsBackward.distance) {
		bestParamsForward.tourMustBeReversed = false;
		return bestParamsForward;
	} else {
		bestParamsBackward.tourMustBeReversed = true;
		return bestParamsBackward;
	}
}

RemoveTypeIIParams Genius::EvaluateBestRemoveTypeIIParams(pTour tour, pNode vi, int neighborhoodSize) {
	RemoveTypeIIParams bestParamsForward;
	bestParamsForward.vj = NULL;
	bestParamsForward.vk = NULL;
	bestParamsForward.vl = NULL;
	bestParamsForward.distance = INF_DISTANCE;
	bestParamsForward.tourMustBeReversed = false;

	RemoveTypeIIParams bestParamsBackward;
	bestParamsBackward.vj = NULL;
	bestParamsBackward.vk = NULL;
	bestParamsBackward.vl = NULL;
	bestParamsBackward.distance = INF_DISTANCE;
	bestParamsBackward.tourMustBeReversed = true;

	//	cout << "FORWARD" << endl;
	bestParamsForward =
		this->EvaluateBestRemoveTypeIIParamsWithOrientedTour(tour, vi, neighborhoodSize);

	tour->Reverse();

	//	cout << "BACKWARD" << endl;
	bestParamsBackward =
		this->EvaluateBestRemoveTypeIIParamsWithOrientedTour(tour, vi, neighborhoodSize);

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

				if ( tour->CheckInsertTypeIConditions(v, vi, vj, vk, false) ) {

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

//				if ( (vk->Id != vj->Id) && (vk->Id != vjplus1->Id) && tour->IsBetween(vk, vj, vi) ) {

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

						//if ( (vl->Id != vi->Id) && (vl->Id != viplus1->Id) && tour->IsBetween(vl, vi, vj) ) {

					if ( tour->CheckInsertTypeIIConditions(v, vi, vj, vk, vl, false) ) {

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
//				}
			}
		}
	}

	return bestParams;
}

RemoveTypeIParams Genius::EvaluateBestRemoveTypeIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize) {
	double currentTourDistance = 0;

	RemoveTypeIParams bestParams;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

	pNode viplus1 = tour->Next(vi);
	pNode viminus1 = tour->Previous(vi);

    pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
    int nodesToEvaluate = min(neighborhoodSize, (int)viplus1Neighborhood->size());

	for (int j=0; j<nodesToEvaluate; j++) {
		pNode vj = viplus1Neighborhood->at(j);

		pNodeVector viminus1Neighborhood = tour->GetNeighborhood(viminus1);
		int nodesToEvaluate2 = min(neighborhoodSize, (int)viminus1Neighborhood->size());

		for (int k=0; k<nodesToEvaluate2; k++) {
			pNode vk = viminus1Neighborhood->at(k);

			if ( tour->CheckRemoveTypeIConditions(vi, vj, vk, false) ) {

				currentTourDistance = tour->EvaluateRemoveTypeI(vi, vj, vk);

				if (currentTourDistance <= bestParams.distance) {
					bestParams.distance = currentTourDistance;
					bestParams.vj = vj;
					bestParams.vk = vk;
				}
			}
		}
	}
	return bestParams;
}

RemoveTypeIIParams Genius::EvaluateBestRemoveTypeIIParamsWithOrientedTour(pTour tour, pNode vi, int neighborhoodSize) {
	double currentTourDistance = 0;

	RemoveTypeIIParams bestParams;
	bestParams.vj = NULL;
	bestParams.vk = NULL;
	bestParams.vl = NULL;
	bestParams.distance = INF_DISTANCE;
	bestParams.tourMustBeReversed = false;

	pNode viplus1 = tour->Next(vi);
	pNode viminus1 = tour->Previous(vi);
	//pNode viminus2 = tour->Previous(viminus1);

    pNodeVector viplus1Neighborhood = tour->GetNeighborhood(viplus1);
    int nodesToEvaluate = min(neighborhoodSize, (int)viplus1Neighborhood->size());

	for (int j=0; j<nodesToEvaluate; j++) {
		pNode vj = viplus1Neighborhood->at(j);
		//pNode vjplus1 = tour->Next(vj);

		pNodeVector viminus1Neighborhood = tour->GetNeighborhood(viminus1);
		int nodesToEvaluate2 = min(neighborhoodSize, (int)viminus1Neighborhood->size());

		for (int k=0; k<nodesToEvaluate2; k++) {
			pNode vk = viminus1Neighborhood->at(k);
			pNode vkplus1 = tour->Next(vk);
			//pNode vkminus1 = tour->Previous(vk);

			pNodeVector vkplus1Neighborhood = tour->GetNeighborhood(vkplus1);
			int nodesToEvaluate3 = min(neighborhoodSize, (int)vkplus1Neighborhood->size());

			for (int l=0; l<nodesToEvaluate3; l++) {
				pNode vl = vkplus1Neighborhood->at(l);

				if ( tour->CheckRemoveTypeIIConditions(vi, vj, vk, vl, false) ) {

					currentTourDistance = tour->EvaluateRemoveTypeII(vi, vj, vk, vl);

					if (currentTourDistance <= bestParams.distance) {
						bestParams.distance = currentTourDistance;
						bestParams.vj = vj;
						bestParams.vk = vk;
						bestParams.vl = vl;
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

void Genius::UnstringNodeFromTour(pNode node, pTour tour, int neighborhoodSize) {

	RemoveTypeIParams bestParamsForTypeI;
	bestParamsForTypeI.vj = NULL;
	bestParamsForTypeI.vk = NULL;
	bestParamsForTypeI.distance = INF_DISTANCE;
	bestParamsForTypeI.tourMustBeReversed = false;

	RemoveTypeIIParams bestParamsForTypeII;
	bestParamsForTypeII.vj = NULL;
	bestParamsForTypeII.vk = NULL;
	bestParamsForTypeII.vl = NULL;
	bestParamsForTypeII.distance = INF_DISTANCE;
	bestParamsForTypeII.tourMustBeReversed = false;

	bestParamsForTypeI =
		this->EvaluateBestRemoveTypeIParams(tour, node, neighborhoodSize);

	bestParamsForTypeII =
		this->EvaluateBestRemoveTypeIIParams(tour, node, neighborhoodSize);

	cout << "> bestParamsForTypeI.distance="
		 << bestParamsForTypeI.distance
		 << " bestParamsForTypeII.distance="
		 << bestParamsForTypeII.distance
		 << endl;

	if (bestParamsForTypeI.distance <= bestParamsForTypeII.distance) {
		if (bestParamsForTypeI.tourMustBeReversed) {
			tour->Reverse();
		}
		cout << "> Performing Remove TypeI of " << node->Id
			 << " (vj="
			 << bestParamsForTypeI.vj->Id << ", "
			 << " vk="
			 << bestParamsForTypeI.vk->Id << ") "
			 << "tour is " << (bestParamsForTypeI.tourMustBeReversed ? "reversed" : "forward")
			 << endl;
		tour->RemoveTypeI(node,
			bestParamsForTypeI.vj,
			bestParamsForTypeI.vk);
	} else {
		if (bestParamsForTypeII.tourMustBeReversed) {
			tour->Reverse();
		}
		cout << "> Performing Remove TypeII of " << node->Id
			 << " (vj="
			 << bestParamsForTypeII.vj->Id << ", "
			 << " vk="
			 << bestParamsForTypeII.vk->Id << ", "
			 << " vl="
			 << bestParamsForTypeII.vl->Id << ") "
			 << "tour is " << (bestParamsForTypeII.tourMustBeReversed ? "reversed" : "forward")
			 << endl;
		tour->RemoveTypeII(node,
			bestParamsForTypeII.vj,
			bestParamsForTypeII.vk,
			bestParamsForTypeII.vl);
	}
}

pTour Genius::ExecuteGeni(pInstance nodesToVisit, int neighborhoodSize) {
	pTour tour = tourFactory->SetInstance(nodesToVisit)->GetTour();

	this->InitializeTourWithThreeNodes(tour, nodesToVisit);
	this->drawer->Draw(tour, "geni_0");

	int step = 1;
	for (int n=0; n<(int)nodesToVisit->Size(); n++) {
		pNode nodeToInsert = nodesToVisit->GetNode(n);

		if (!tour->Contains(nodeToInsert)) {
			this->StringNodeInTour(nodeToInsert, tour, neighborhoodSize);
			this->drawer->Draw(tour, "geni_" + Utils::ToString(step, true));
			step++;
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

pTour Genius::ExecuteUs(pTour tour, int neighborhoodSize) {
	pTour bestTour = NULL;
	double bestTourDistance = INF_DISTANCE;
	int currentNodeOfTour = 0;

	pTour currentTour = tour->Clone();

	cout << endl;

	int it = 0;
	for(;;)
	{
		cout << "---- it " << it << " -----------------" << endl;

		pNode currentNode = currentTour->Get(currentNodeOfTour);
		cout << "currentNode " << currentNode->Id << endl;

		cout << "currentTour before unstring: " << currentTour->ToString() << endl;
		cout << "currentTour distance before unstring: " << currentTour->TotalDistance() << endl;

		this->UnstringNodeFromTour(currentNode, currentTour, neighborhoodSize);

		cout << "currentTour after unstring: " << currentTour->ToString() << endl;
		cout << "currentTour distance after unstring: " << currentTour->TotalDistance() << endl;

		this->StringNodeInTour(currentNode, currentTour, neighborhoodSize);
		double newDistance = currentTour->TotalDistance();

		cout << "currentTour after string: " << currentTour->ToString() << endl;
		cout << "currentTour distance after string: " << currentTour->TotalDistance() << endl;

		this->drawer->Draw(currentTour, "us_" + Utils::ToString(it, true), currentNode);

		if (newDistance < bestTourDistance) {
			currentNodeOfTour = 0;
			bestTourDistance = newDistance;
			SAFE_DELETE(bestTour);
			bestTour = currentTour->Clone();
		} else {
			if ( currentNodeOfTour < (currentTour->Length()-1) ) {
				currentNodeOfTour++;
			} else {
				break;
			}
		}
		it++;
	}
	SAFE_DELETE(currentTour);
	return bestTour;
}

} /* namespace Genius */
