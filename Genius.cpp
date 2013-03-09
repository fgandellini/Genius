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

	bestParamsForward =
		this->EvaluateBestInsertTypeIIParamsWithOrientedTour(tour, v, neighborhoodSize);

	tour->Reverse();

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

	bestParamsForward =
		this->EvaluateBestRemoveTypeIIParamsWithOrientedTour(tour, vi, neighborhoodSize);

	tour->Reverse();

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
		DBG  << "SI  <"
			 << "vi=" << Utils::ToString(bestParamsForTypeI.vi->Id, true) << " "
			 << "vj=" << Utils::ToString(bestParamsForTypeI.vj->Id, true) << " "
			 << "vk=" << Utils::ToString(bestParamsForTypeI.vk->Id, true) << " "
			 << "      "
			 << (bestParamsForTypeI.tourMustBeReversed ? "R" : "F")
			 << ">";
		tour->InsertTypeI(node,
			bestParamsForTypeI.vi,
			bestParamsForTypeI.vj,
			bestParamsForTypeI.vk);

	} else {
		if (bestParamsForTypeII.tourMustBeReversed) {
			tour->Reverse();
		}
		DBG  << "SII <"
			 << "vi=" << Utils::ToString(bestParamsForTypeII.vi->Id, true) << " "
			 << "vj=" << Utils::ToString(bestParamsForTypeII.vj->Id, true) << " "
			 << "vk=" << Utils::ToString(bestParamsForTypeII.vk->Id, true) << " "
			 << "vl=" << Utils::ToString(bestParamsForTypeII.vl->Id, true) << " "
			 << (bestParamsForTypeII.tourMustBeReversed ? "R" : "F")
			 << ">";
		tour->InsertTypeII(node,
			bestParamsForTypeII.vi,
			bestParamsForTypeII.vj,
			bestParamsForTypeII.vk,
			bestParamsForTypeII.vl);
	}
}

bool Genius::UnstringNodeFromTour(pNode node, pTour tour, int neighborhoodSize) {

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

//	if (bestParamsForTypeI.distance == bestParamsForTypeII.distance) {
//		ERR << endl << "bestParamsForTypeI.distance="
//			<< bestParamsForTypeI.distance
//			<< " bestParamsForTypeII.distance="
//			<< bestParamsForTypeII.distance
//			<< flush;
//	}

	if (bestParamsForTypeI.distance == INF_DISTANCE &&
		bestParamsForTypeII.distance == INF_DISTANCE) {
		ERR << endl << "Unstringing node " << node->Id << " from tour"
			<< endl << "(" << tour->TotalDistance() << ") " << tour->ToString()
			<< endl << "No suitable param-set found! Skipping to next node!"
			<< flush << endl;
		return false;
	}

	if (bestParamsForTypeI.distance <= bestParamsForTypeII.distance) {
		if (bestParamsForTypeI.tourMustBeReversed) {
			tour->Reverse();
		}
		DBG  << "UI  <"
			 << "vj=" << Utils::ToString(bestParamsForTypeI.vj->Id, true) << " "
			 << "vk=" << Utils::ToString(bestParamsForTypeI.vk->Id, true) << " "
			 << "            "
			 << (bestParamsForTypeI.tourMustBeReversed ? "R" : "F")
			 << ">" << flush;
		tour->RemoveTypeI(node,
			bestParamsForTypeI.vj,
			bestParamsForTypeI.vk);

	} else {
		if (bestParamsForTypeII.tourMustBeReversed) {
			tour->Reverse();
		}
		DBG  << "UII <"
			 << "vj=" << Utils::ToString(bestParamsForTypeII.vj->Id, true) << " "
			 << "vk=" << Utils::ToString(bestParamsForTypeII.vk->Id, true) << " "
			 << "vl=" << Utils::ToString(bestParamsForTypeII.vl->Id, true) << " "
			 << "      "
			 << (bestParamsForTypeII.tourMustBeReversed ? "R" : "F")
			 << ">" << flush;
		tour->RemoveTypeII(node,
			bestParamsForTypeII.vj,
			bestParamsForTypeII.vk,
			bestParamsForTypeII.vl);
	}
	return true;
}

pTour Genius::ExecuteGeni(pInstance nodesToVisit, int neighborhoodSize) {

	WARN << endl
		 << "Instance " << nodesToVisit->Name << endl
		 << "----------------------------------------" << endl
		 << "Execution of Geni" << endl;

	pTour tour = tourFactory->SetInstance(nodesToVisit)->GetTour();

	this->InitializeTourWithThreeNodes(tour, nodesToVisit);
	if (ENABLE_DRAWER) {
		this->drawer->Draw(tour, "geni_0");
	}

	INFO << "00]                                 ("
		 << tour->TotalDistance() << ") "
		 << tour->ToString() << flush << endl;

	int step = 1;
	for (int n=0; n<(int)nodesToVisit->Size(); n++) {
		pNode nodeToInsert = nodesToVisit->GetNode(n);

		if (!tour->Contains(nodeToInsert)) {

			INFO << Utils::ToString(step, true) << "] ";

			this->StringNodeInTour(nodeToInsert, tour, neighborhoodSize);
			if (ENABLE_DRAWER) {
				this->drawer->Draw(tour, "geni_" + Utils::ToString(step, true));
			}

			INFO << " (" << tour->TotalDistance() << ") "
			     << tour->ToString() << flush << endl;

			step++;
		}
	}

	WARN << "GENI] Heuristic solution            ("
		 << tour->TotalDistance() << ") "
		 << tour->ToString() << flush << endl;

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
	int currentNodeIdx = 0;

	pTour currentTour = tour->Clone();

	WARN << "Execution of Us" << endl;

	int it = 0;
	for(;;)
	{
		pNode currentNode = currentTour->Get(currentNodeIdx);

		INFO << Utils::ToString(it, true) << "] Unstring of "
			 << Utils::ToString(currentNode->Id, true) << " from             ("
			 << currentTour->TotalDistance() << ") "
			 << currentTour->ToString() << endl;
		DBG << Utils::ToString(it, true) << "] ";

		double newDistance = currentTour->TotalDistance();

		if (this->UnstringNodeFromTour(currentNode, currentTour, neighborhoodSize)) {
			DBG << " (" << currentTour->TotalDistance() << ") "
				 << currentTour->ToString() << endl;

			INFO << Utils::ToString(it, true) << "] String of "
				 << Utils::ToString(currentNode->Id, true) << " in                 ("
				 << currentTour->TotalDistance() << ") "
				 << currentTour->ToString() << endl;
			DBG << Utils::ToString(it, true) << "] ";

			this->StringNodeInTour(currentNode, currentTour, neighborhoodSize);
			newDistance = currentTour->TotalDistance();

			DBG << " (" << currentTour->TotalDistance() << ") "
				 << currentTour->ToString() << flush << endl;

			if (newDistance < bestTourDistance) {
				currentNodeIdx = 0;
				bestTourDistance = newDistance;
				SAFE_DELETE(bestTour);
				bestTour = currentTour->Clone();
				INFO << Utils::ToString(it, true) << "] Best tour updated               ("
					 << bestTour->TotalDistance() << ") "
					 << bestTour->ToString() << flush << endl;
			} else {
				if ( currentNodeIdx < (tour->Length()-1) ) {
					currentNodeIdx++;
				} else {
					break;
				}
			}

		} else { // no param-set found;
			if ( currentNodeIdx < (tour->Length()-1) ) {
				ERR << "skipping node " << currentTour->Get(currentNodeIdx)->Id << endl;
				currentNodeIdx++;
				ERR << "continuing with " << currentTour->Get(currentNodeIdx)->Id << endl;
			} else {
				break;
			}
		}

		if (ENABLE_DRAWER) {
			this->drawer->Draw(currentTour, "us_" + Utils::ToString(it, true), currentNode);
		}

		// Security check!
		if (currentTour->Length() != tour->Length()) {
			ERR << endl << "TOUR LENGHT CHECK FAILED!" << endl << endl;
			break;
		}

		it++;
	}
	SAFE_DELETE(currentTour);

	WARN << "US] Best tour found by US            ("
		 << bestTour->TotalDistance() << ") "
		 << bestTour->ToString() << flush << endl;

	return bestTour;
}

void Genius::ExecuteGenius(string instanceFile, string optTourFile, int p) {
	pInstance instance = InstanceLoader::LoadFromFile(instanceFile);
	assert(instance->Size() > 0);
	if (ENABLE_DRAWER) {
		drawer->Draw(instance, "instance");
	}

	pTour optTour = InstanceLoader::LoadOptTourFromFile(instance, optTourFile);
	assert(optTour->Length() == instance->Size());
	if (ENABLE_DRAWER) {
		drawer->Draw(optTour, "optTour");
	}

	pTour geniSol = this->ExecuteGeni(instance, p);
	if (ENABLE_DRAWER) {
		drawer->Draw(geniSol, "geniSol");
	}

	pTour solution = this->ExecuteUs(geniSol, p);
	if (ENABLE_DRAWER) {
		drawer->Draw(solution, "solution");
	}

	WARN << "!!] Optimal tour                     ("
		 << optTour->TotalDistance() << ") "
		 << optTour->ToString() << flush << endl;

	assert(solution->Length() == instance->Size());
	assert(solution->TotalDistance() >= optTour->TotalDistance());

	SAFE_DELETE(optTour);
	SAFE_DELETE(solution);
	SAFE_DELETE(geniSol);
	SAFE_DELETE(instance);
}

void Genius::ExecuteGeniusWithTimeTrace(string instanceFile, string optTourFile, int p)
{
	//timeval stop, start;
	//gettimeofday(&start, NULL);

    clock_t start, stop;
    int i;
    start = clock();

	this->ExecuteGenius(instanceFile, optTourFile, p);

	stop = clock();
	double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

	//gettimeofday(&stop, NULL);
	//long elapsed = stop.tv_usec - start.tv_usec;

	cout << endl << instanceFile << " solution time: " << elapsed << " s" << endl;
}

} /* namespace Genius */
