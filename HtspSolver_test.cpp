/*
 * HtspSolver_test.cpp
 *
 *  Created on: 15/mar/2013
 *      Author: fede
 */

#include "HtspSolver.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

TEST_GROUP(HtspSolver) {
	void setup() {}
	void teardown() {}
};

IGNORE_TEST(HtspSolver, BuildStartingTour) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	pTour startingTour = htspSolver->BuildStartingTour();

	STRCMP_EQUAL(
		"1p1 => 5p2 => 8p3 => 11p4 => 13p5 => 1p1",
		startingTour->ToString().c_str());

	htspSolver->BuildSolution(startingTour);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(startingTour);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, SolveTspTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	htspSolver->SolveAsTsp(ulysses16Htsp);

	CHECK(htspSolver->geniusSolution->Length() == ulysses16Htsp->Size());
	STRCMP_EQUAL(
		"6p2 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 15p5 => 5p2 => 11p4 => 9p3 => 10p3 => 7p2 => 6p2",
		htspSolver->geniusSolution->ToString().c_str());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, InitSubtoursTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);

	CHECK(htspSolver->subtours->size() == 2);
	for(int s=0; s<(int)htspSolver->subtours->size(); s++) {
		CHECK(htspSolver->subtours->at(s)->tour->Length() == 0);
		CHECK(htspSolver->subtours->at(s)->candidateArcs->size() == 1);
	}
	CHECK(htspSolver->subtours->at(0)->priorityRangeBegin == 1);
	CHECK(htspSolver->subtours->at(0)->priorityRangeEnd   == 3);
	CHECK(htspSolver->subtours->at(1)->priorityRangeBegin == 4);
	CHECK(htspSolver->subtours->at(1)->priorityRangeEnd   == 5);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, GetSubtourByPriorityTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);

	pSubtour subtour1 = htspSolver->GetSubtourByPriority(1);
	pSubtour subtour2 = htspSolver->GetSubtourByPriority(2);
	pSubtour subtour3 = htspSolver->GetSubtourByPriority(3);
	pSubtour subtour4 = htspSolver->GetSubtourByPriority(4);
	pSubtour subtour5 = htspSolver->GetSubtourByPriority(5);

	CHECK(subtour1 == subtour2);
	CHECK(subtour1 == subtour3);
	CHECK(subtour1 != subtour4);
	CHECK(subtour4 == subtour5);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, ExtractSubtoursTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	htspSolver->SolveAsTsp(ulysses16Htsp);
	htspSolver->ExtractSubtours();

	CHECK(htspSolver->subtours->size() == 2);

	pSubtour firstSubtour = htspSolver->subtours->at(0);
	CHECK(firstSubtour->tour->Length() == 10);
	CHECK(firstSubtour->candidateArcs->size() == 3);
	CHECK(firstSubtour->candidateArcs->at(0)->From->Id == 6);
	CHECK(firstSubtour->candidateArcs->at(0)->To->Id == 1);
	CHECK(firstSubtour->candidateArcs->at(1)->From->Id == 8);
	CHECK(firstSubtour->candidateArcs->at(1)->To->Id == 5);
	CHECK(firstSubtour->candidateArcs->at(2)->From->Id == 5);
	CHECK(firstSubtour->candidateArcs->at(2)->To->Id == 9);

	pSubtour secondSubtour = htspSolver->subtours->at(1);
	CHECK(secondSubtour->tour->Length() == 6);
	CHECK(secondSubtour->candidateArcs->size() == 3);
	CHECK(secondSubtour->candidateArcs->at(0)->From->Id == 16);
	CHECK(secondSubtour->candidateArcs->at(0)->To->Id == 15);
	CHECK(secondSubtour->candidateArcs->at(1)->From->Id == 15);
	CHECK(secondSubtour->candidateArcs->at(1)->To->Id == 11);
	CHECK(secondSubtour->candidateArcs->at(2)->From->Id == 11);
	CHECK(secondSubtour->candidateArcs->at(2)->To->Id == 14);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, MergeSubtoursTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);
	pTourFactory tourFactory = new TourFactory(ulysses16Htsp);

	pSubtour first = new Subtour();
	first->tour = tourFactory->GetTour();
	first->tour->Append(ulysses16Htsp->GetNodeById(6));
	first->tour->Append(ulysses16Htsp->GetNodeById(1));
	first->tour->Append(ulysses16Htsp->GetNodeById(3));
	first->tour->Append(ulysses16Htsp->GetNodeById(2));
	first->tour->Append(ulysses16Htsp->GetNodeById(4));
	first->tour->Append(ulysses16Htsp->GetNodeById(8));
	first->tour->Append(ulysses16Htsp->GetNodeById(5));
	first->tour->Append(ulysses16Htsp->GetNodeById(9));
	first->tour->Append(ulysses16Htsp->GetNodeById(10));
	first->tour->Append(ulysses16Htsp->GetNodeById(7));
	first->candidateArcs->push_back(new Arc());
	first->candidateArcs->push_back(new Arc());
	first->candidateArcs->at(0)->From = ulysses16Htsp->GetNodeById(6);
	first->candidateArcs->at(0)->To = ulysses16Htsp->GetNodeById(1);
	first->candidateArcs->at(1)->From = ulysses16Htsp->GetNodeById(8);
	first->candidateArcs->at(1)->To = ulysses16Htsp->GetNodeById(5);
	first->candidateArcs->at(2)->From = ulysses16Htsp->GetNodeById(5);
	first->candidateArcs->at(2)->To = ulysses16Htsp->GetNodeById(9);
	first->priorityRangeBegin = 1;
	first->priorityRangeEnd = 3;

	pSubtour second = new Subtour();
	second->tour = tourFactory->GetTour();
	second->tour->Append(ulysses16Htsp->GetNodeById(14));
	second->tour->Append(ulysses16Htsp->GetNodeById(13));
	second->tour->Append(ulysses16Htsp->GetNodeById(12));
	second->tour->Append(ulysses16Htsp->GetNodeById(16));
	second->tour->Append(ulysses16Htsp->GetNodeById(15));
	second->tour->Append(ulysses16Htsp->GetNodeById(11));
	second->candidateArcs->push_back(new Arc());
	second->candidateArcs->push_back(new Arc());
	second->candidateArcs->at(0)->From = ulysses16Htsp->GetNodeById(16);
	second->candidateArcs->at(0)->To = ulysses16Htsp->GetNodeById(15);
	second->candidateArcs->at(1)->From = ulysses16Htsp->GetNodeById(15);
	second->candidateArcs->at(1)->To = ulysses16Htsp->GetNodeById(11);
	second->candidateArcs->at(2)->From = ulysses16Htsp->GetNodeById(11);
	second->candidateArcs->at(2)->To = ulysses16Htsp->GetNodeById(14);
	second->priorityRangeBegin = 4;
	second->priorityRangeEnd = 5;

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	pSubtour merged = htspSolver->MergeSubtours(first, second);

	CHECK(merged->tour->Length() == first->tour->Length() + second->tour->Length());
	STRCMP_EQUAL(
		"1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 5p2 => 9p3 => 10p3 => 7p2 => 6p2 => 15p5 => 11p4 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1",
		merged->tour->ToString().c_str());

	CHECK(merged->candidateArcs->size() == 1);
	CHECK(merged->candidateArcs->at(0)->From->Id == 16);
	CHECK(merged->candidateArcs->at(0)->To->Id == 1);

	CHECK(merged->priorityRangeBegin == 1);
	CHECK(merged->priorityRangeEnd == 5);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	SAFE_DELETE(tourFactory);
	SAFE_DELETE(merged);
	SAFE_DELETE(first);
	SAFE_DELETE(second);
}

TEST(HtspSolver, SolveTypeITest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	pTour htspSolution = htspSolver->SolveTypeI();

	CHECK(htspSolution->Length() == ulysses16Htsp->Size());
	STRCMP_EQUAL(
		"1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 5p2 => 9p3 => 10p3 => 7p2 => 6p2 => 15p5 => 11p4 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1",
		htspSolution->ToString().c_str());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

TEST(HtspSolver, SolveTypeIITest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	pTour htspSolution = htspSolver->SolveTypeII();

	CHECK(htspSolver->subtours->size() == 2);

	pSubtour firstSubtour = htspSolver->subtours->at(0);
	CHECK(firstSubtour->tour->Length() == 10);
	CHECK(firstSubtour->candidateArcs->size() == 10);

	pSubtour secondSubtour = htspSolver->subtours->at(1);
	CHECK(secondSubtour->tour->Length() == 6);
	CHECK(secondSubtour->candidateArcs->size() == 6);

	CHECK(htspSolution->Length() == ulysses16Htsp->Size());

//	STRCMP_EQUAL(
//		"1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 5p2 => 9p3 => 10p3 => 7p2 => 6p2 => 15p5 => 11p4 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1",
//		htspSolution->ToString().c_str());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
}

} /* namespace Genius */
