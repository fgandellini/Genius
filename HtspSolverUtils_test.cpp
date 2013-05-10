#include "HtspSolverUtils.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

TEST_GROUP(HtspSolverUtils) {
	void setup() {}
	void teardown() {}
};

TEST(HtspSolverUtils, InitSubtoursTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverUtils htspSolver = new HtspSolverUtils();
	pSubtourVector subtours = htspSolver->InitSubtours(ulysses16Htsp, true);

	CHECK(subtours->size() == 2);
	for(int s=0; s<(int)subtours->size(); s++) {
		CHECK(subtours->at(s)->tour->Length() == 0);
		CHECK(subtours->at(s)->candidateArcs->size() == 1);
	}
	CHECK(subtours->at(0)->priorityRangeBegin == 1);
	CHECK(subtours->at(0)->priorityRangeEnd   == 3);
	CHECK(subtours->at(1)->priorityRangeBegin == 4);
	CHECK(subtours->at(1)->priorityRangeEnd   == 5);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);
}

TEST(HtspSolverUtils, ExecuteGeniusTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverUtils htspSolver = new HtspSolverUtils();
	pTour geniusTour = htspSolver->ExecuteGenius(ulysses16Htsp);

	CHECK(geniusTour->Length() == ulysses16Htsp->Size());
	STRCMP_EQUAL(
		"6p2 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 15p5 => 5p2 => 11p4 => 9p3 => 10p3 => 7p2 => 6p2",
		geniusTour->ToString().c_str());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	SAFE_DELETE(geniusTour);
}

TEST(HtspSolverUtils, ExtractSubtoursTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverUtils htspSolver = new HtspSolverUtils();
	pTour geniusTour = htspSolver->ExecuteGenius(ulysses16Htsp);
	pSubtourVector subtours = htspSolver->ExtractSubtours(ulysses16Htsp, geniusTour);

	CHECK(subtours->size() == 2);

	pSubtour firstSubtour = subtours->at(0);
	CHECK(firstSubtour->tour->Length() == 10);
	CHECK(firstSubtour->candidateArcs->size() == 3);
	CHECK(firstSubtour->candidateArcs->at(0)->From->Id == 6);
	CHECK(firstSubtour->candidateArcs->at(0)->To->Id == 1);
	CHECK(firstSubtour->candidateArcs->at(1)->From->Id == 8);
	CHECK(firstSubtour->candidateArcs->at(1)->To->Id == 5);
	CHECK(firstSubtour->candidateArcs->at(2)->From->Id == 5);
	CHECK(firstSubtour->candidateArcs->at(2)->To->Id == 9);

	pSubtour secondSubtour = subtours->at(1);
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
	SAFE_DELETE(geniusTour);
	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);
}

TEST(HtspSolverUtils, GetSubtourByPriorityTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverUtils htspSolver = new HtspSolverUtils();
	pTour geniusTour = htspSolver->ExecuteGenius(ulysses16Htsp);
	pSubtourVector subtours = htspSolver->ExtractSubtours(ulysses16Htsp, geniusTour);

	pSubtour subtour1 = htspSolver->GetSubtourByPriority(ulysses16Htsp, subtours, 1);
	pSubtour subtour2 = htspSolver->GetSubtourByPriority(ulysses16Htsp, subtours, 2);
	pSubtour subtour3 = htspSolver->GetSubtourByPriority(ulysses16Htsp, subtours, 3);
	pSubtour subtour4 = htspSolver->GetSubtourByPriority(ulysses16Htsp, subtours, 4);
	pSubtour subtour5 = htspSolver->GetSubtourByPriority(ulysses16Htsp, subtours, 5);

	CHECK(subtour1 == subtour2);
	CHECK(subtour1 == subtour3);
	CHECK(subtour1 != subtour4);
	CHECK(subtour4 == subtour5);

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	SAFE_DELETE(geniusTour);
	for(int s=0; s<(int)subtours->size(); s++) {
		SAFE_DELETE(subtours->at(s)->tour);
		SAFE_DELETE(subtours->at(s));
	}
	SAFE_DELETE(subtours);
}

TEST(HtspSolverUtils, MergeSubtoursTest) {
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

	pHtspSolverUtils htspSolver = new HtspSolverUtils();
	pSubtour merged = htspSolver->MergeSubtours(ulysses16Htsp, first, second);

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

} /* namespace Genius */
