#include "Tour.h"
#include<CppUTest/TestHarness.h>

namespace Genius {

pInstance geniusPaperInstance;
pInstance tenNodesInstance;
pInstance twentyNodesInstance;
pInstance fourNodesInstance;

pTour paper_tour;
pTour ten_nodes_tour;
pTour long_tour;
pTour long_long_tour;

TEST_GROUP(Tour) {
	void setup() {
		geniusPaperInstance = new Instance();
		geniusPaperInstance->Add(new Node(1, 21.8, 72.8));
		geniusPaperInstance->Add(new Node(2, 31.5, 10.8));
		geniusPaperInstance->Add(new Node(3, 16.3, 13.7));
		geniusPaperInstance->Add(new Node(4,  3.7, 54.8));
		geniusPaperInstance->Add(new Node(5, 21.0, 21.7));
		geniusPaperInstance->Add(new Node(6, 69.3,  1.3));
		geniusPaperInstance->Add(new Node(7, 40.8, 60.1));
		geniusPaperInstance->Add(new Node(8, 27.8, 26.2));

		paper_tour = new Tour(geniusPaperInstance);
		paper_tour->Append(geniusPaperInstance->GetNode(0));
		paper_tour->Append(geniusPaperInstance->GetNode(1));
		paper_tour->Append(geniusPaperInstance->GetNode(2));
		paper_tour->Append(geniusPaperInstance->GetNode(3));
		paper_tour->Append(geniusPaperInstance->GetNode(4));
		paper_tour->Append(geniusPaperInstance->GetNode(5));
		paper_tour->Append(geniusPaperInstance->GetNode(6));
		paper_tour->Append(geniusPaperInstance->GetNode(7));

		tenNodesInstance = new Instance();
		tenNodesInstance->Add(new Node(1,  0, 0));
		tenNodesInstance->Add(new Node(2,  1, 0));
		tenNodesInstance->Add(new Node(3,  2, 0));
		tenNodesInstance->Add(new Node(4,  3, 0));
		tenNodesInstance->Add(new Node(5,  3, 1));
		tenNodesInstance->Add(new Node(6,  3, 2));
		tenNodesInstance->Add(new Node(7,  2, 2));
		tenNodesInstance->Add(new Node(8,  1, 2));
		tenNodesInstance->Add(new Node(9,  0, 2));
		tenNodesInstance->Add(new Node(10, 0, 1));

		ten_nodes_tour = new Tour(tenNodesInstance);
		ten_nodes_tour->Append(tenNodesInstance->GetNode(0));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(1));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(2));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(3));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(4));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(5));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(6));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(7));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(8));
		ten_nodes_tour->Append(tenNodesInstance->GetNode(9));

		twentyNodesInstance = new Instance();
		twentyNodesInstance->Add(new Node(1,  0, 0));
		twentyNodesInstance->Add(new Node(2,  0, 0));
		twentyNodesInstance->Add(new Node(3,  0, 0));
		twentyNodesInstance->Add(new Node(4,  0, 0));
		twentyNodesInstance->Add(new Node(5,  0, 0));
		twentyNodesInstance->Add(new Node(6,  0, 0));
		twentyNodesInstance->Add(new Node(7,  0, 0));
		twentyNodesInstance->Add(new Node(8,  0, 0));
		twentyNodesInstance->Add(new Node(9,  0, 0));
		twentyNodesInstance->Add(new Node(10, 0, 0));
		twentyNodesInstance->Add(new Node(11, 0, 0));
		twentyNodesInstance->Add(new Node(12, 0, 0));
		twentyNodesInstance->Add(new Node(13, 0, 0));
		twentyNodesInstance->Add(new Node(14, 0, 0));
		twentyNodesInstance->Add(new Node(15, 0, 0));
		twentyNodesInstance->Add(new Node(16, 0, 0));
		twentyNodesInstance->Add(new Node(17, 0, 0));
		twentyNodesInstance->Add(new Node(18, 0, 0));
		twentyNodesInstance->Add(new Node(19, 0, 0));
		twentyNodesInstance->Add(new Node(20, 0, 0));
		twentyNodesInstance->Add(new Node(100, 0, 0));

		long_tour = new Tour(twentyNodesInstance);
		long_tour->Append(twentyNodesInstance->GetNode(0));
		long_tour->Append(twentyNodesInstance->GetNode(1));
		long_tour->Append(twentyNodesInstance->GetNode(2));
		long_tour->Append(twentyNodesInstance->GetNode(3));
		long_tour->Append(twentyNodesInstance->GetNode(4));
		long_tour->Append(twentyNodesInstance->GetNode(5));
		long_tour->Append(twentyNodesInstance->GetNode(6));
		long_tour->Append(twentyNodesInstance->GetNode(7));
		long_tour->Append(twentyNodesInstance->GetNode(8));
		long_tour->Append(twentyNodesInstance->GetNode(9));
		long_tour->Append(twentyNodesInstance->GetNode(10));
		long_tour->Append(twentyNodesInstance->GetNode(11));
		long_tour->Append(twentyNodesInstance->GetNode(12));
		long_tour->Append(twentyNodesInstance->GetNode(13));
		long_tour->Append(twentyNodesInstance->GetNode(14));
		long_tour->Append(twentyNodesInstance->GetNode(15));

		long_long_tour = new Tour(twentyNodesInstance);
		long_long_tour->Append(twentyNodesInstance->GetNode(0));
		long_long_tour->Append(twentyNodesInstance->GetNode(1));
		long_long_tour->Append(twentyNodesInstance->GetNode(2));
		long_long_tour->Append(twentyNodesInstance->GetNode(3));
		long_long_tour->Append(twentyNodesInstance->GetNode(4));
		long_long_tour->Append(twentyNodesInstance->GetNode(5));
		long_long_tour->Append(twentyNodesInstance->GetNode(6));
		long_long_tour->Append(twentyNodesInstance->GetNode(7));
		long_long_tour->Append(twentyNodesInstance->GetNode(8));
		long_long_tour->Append(twentyNodesInstance->GetNode(9));
		long_long_tour->Append(twentyNodesInstance->GetNode(10));
		long_long_tour->Append(twentyNodesInstance->GetNode(11));
		long_long_tour->Append(twentyNodesInstance->GetNode(12));
		long_long_tour->Append(twentyNodesInstance->GetNode(13));
		long_long_tour->Append(twentyNodesInstance->GetNode(14));
		long_long_tour->Append(twentyNodesInstance->GetNode(15));
		long_long_tour->Append(twentyNodesInstance->GetNode(16));
		long_long_tour->Append(twentyNodesInstance->GetNode(17));
		long_long_tour->Append(twentyNodesInstance->GetNode(18));
		long_long_tour->Append(twentyNodesInstance->GetNode(19));
	}

	void teardown() {
		SAFE_DELETE(geniusPaperInstance);
		SAFE_DELETE(tenNodesInstance);
		SAFE_DELETE(twentyNodesInstance);
		SAFE_DELETE(fourNodesInstance);

		SAFE_DELETE(paper_tour);
		SAFE_DELETE(ten_nodes_tour);
		SAFE_DELETE(long_tour);
		SAFE_DELETE(long_long_tour);
	}
};

TEST(Tour, GoToNodeTest) {
	pNode reference = tenNodesInstance->GetNode(6);
	paper_tour->GoTo(reference);
	CHECK(paper_tour->nodes.current_element()->Id == 7);
	CHECK(paper_tour->nodes.next_element()->Id == 7);
	CHECK(paper_tour->nodes.previous_element()->Id == 7);
	CHECK(paper_tour->nodes.next_element()->Id == 7);
	CHECK(paper_tour->nodes.previous_element()->Id == 7);
	CHECK(paper_tour->nodes.previous_element()->Id == 6);

	reference = tenNodesInstance->GetNode(3);
	paper_tour->GoTo(reference);
	CHECK(paper_tour->nodes.previous_element()->Id == 3);
	CHECK(paper_tour->nodes.next_element()->Id == 3);
	CHECK(paper_tour->nodes.next_element()->Id == 4);

	reference = tenNodesInstance->GetNode(7);
	paper_tour->GoTo(reference);
	CHECK(paper_tour->nodes.next_element()->Id == 8);
	CHECK(paper_tour->nodes.previous_element()->Id == 8);
	CHECK(paper_tour->nodes.previous_element()->Id == 7);
}

TEST(Tour, GetNextTest) {
	pNode reference = tenNodesInstance->GetNode(0);
	CHECK(ten_nodes_tour->Next(reference)->Id == 2);

	reference = tenNodesInstance->GetNode(1);
	CHECK(ten_nodes_tour->Next(reference)->Id == 3);

	reference = tenNodesInstance->GetNode(9);
	CHECK(ten_nodes_tour->Next(reference)->Id == 1);

	reference = tenNodesInstance->GetNode(5);
	CHECK(ten_nodes_tour->Next(reference)->Id == 7);
}

TEST(Tour, GetPrevTest) {
	pNode reference = tenNodesInstance->GetNode(0);
	CHECK(ten_nodes_tour->Previous(reference)->Id == 10);

	reference = tenNodesInstance->GetNode(1);
	CHECK(ten_nodes_tour->Previous(reference)->Id == 1);

	reference = tenNodesInstance->GetNode(9);
	CHECK(ten_nodes_tour->Previous(reference)->Id == 9);

	reference = tenNodesInstance->GetNode(5);
	CHECK(ten_nodes_tour->Previous(reference)->Id == 5);
}

TEST(Tour, GetSubtourTest) {
	data::clist<pNode> subtour;

	pNode from = tenNodesInstance->GetNode(2);
	pNode to = tenNodesInstance->GetNode(7);
	subtour = ten_nodes_tour->GetSubtour(from, to);

	STRCMP_EQUAL("3 => 4 => 5 => 6 => 7 => 8 => 3",
		ten_nodes_tour->TourToString(subtour).c_str());

	from->Id = 3; to->Id = 3;
	subtour = ten_nodes_tour->GetSubtour(from, to);

	STRCMP_EQUAL("3 => 3",
		ten_nodes_tour->TourToString(subtour).c_str());

	from->Id = 3; to->Id = 8;
	subtour = ten_nodes_tour->GetReversedSubtour(from, to);

	STRCMP_EQUAL("8 => 7 => 6 => 5 => 4 => 3 => 8",
		ten_nodes_tour->TourToString(subtour).c_str());

	from->Id = 3; to->Id = 3;
	subtour = ten_nodes_tour->GetReversedSubtour(from, to);

	STRCMP_EQUAL("3 => 3",
		ten_nodes_tour->TourToString(subtour).c_str());
}

TEST(Tour, GetIndexTest) {
	pNode reference = tenNodesInstance->GetNode(0);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  0);

	reference = tenNodesInstance->GetNode(1);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  1);

	reference = tenNodesInstance->GetNode(3);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  2);

	reference = tenNodesInstance->GetNode(11); // probabile NULL!!!
	CHECK(ten_nodes_tour->GetIndex(reference) == -1);

	reference = tenNodesInstance->GetNode(0);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  0);

	reference = tenNodesInstance->GetNode(2);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  2);

	reference = tenNodesInstance->GetNode(3);
	CHECK(ten_nodes_tour->GetIndex(reference) ==  1);
}

TEST(Tour, IsBetweenTest) {

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 1",
		ten_nodes_tour->ToString().c_str());

	from->Id = 2; x->Id = 3; to->Id = 4; // caso normale, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 10; x->Id = 1; to->Id = 2; // check testa, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 9; x->Id = 10; to->Id = 1; // check coda, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 2; x->Id = 4; to->Id = 7; // caso normale, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 5; x->Id = 1; to->Id = 3; // check testa, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 6; x->Id = 10; to->Id = 4; // check coda, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);

	from->Id = 4; x->Id = 3; to->Id = 2; // caso normale, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);
	from->Id = 2; x->Id = 1; to->Id = 10; // check testa, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);
	from->Id = 1; x->Id = 10; to->Id = 9; // check coda, nodi adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);
	from->Id = 10; x->Id = 4; to->Id = 2; // caso normale, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);
	from->Id = 3; x->Id = 1; to->Id = 5; // check testa, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);
	from->Id = 4; x->Id = 10; to->Id = 6; // check coda, nodi non adiacenti
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == false);

	from->Id = 3; x->Id = 3; to->Id = 6; // x e from collassati
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 3; x->Id = 6; to->Id = 6; // x e to collassati
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
	from->Id = 3; x->Id = 3; to->Id = 3; // x, from e to collassati
	CHECK(ten_nodes_tour->IsBetween(x, from, to) == true);
}

TEST(Tour, CalcSubtourDistanceTest) {
	double dist = 0;

	//  A
	//  | . . . . .
	//  9 8 7 6 . .
	//  10. . 5 . .
	// -1-2-3-4----->
//
//	from->Id = 1; to->Id = 4;
//	dist = ten_nodes_tour->CalcSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(3, dist, 0.1);
//
//	from->Id = 4; to->Id = 6;
//	dist = ten_nodes_tour->CalcSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(2, dist, 0.1);
//
//	from->Id = 10; to->Id = 3;
//	dist = ten_nodes_tour->CalcSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(3, dist, 0.1);
//
//	from->Id = 2; to->Id = 9;
//	dist = ten_nodes_tour->CalcSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(7, dist, 0.1);
//
//	from->Id = 8; to->Id = 8;
//	dist = ten_nodes_tour->CalcSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(0, dist, 0.1);
//
//
//	from->Id = 1; to->Id = 4;
//	dist = ten_nodes_tour->CalcReversedSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(7, dist, 0.1);
//
//	from->Id = 4; to->Id = 6;
//	dist = ten_nodes_tour->CalcReversedSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(8, dist, 0.1);
//
//	from->Id = 10; to->Id = 3;
//	dist = ten_nodes_tour->CalcReversedSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(7, dist, 0.1);
//
//	from->Id = 2; to->Id = 9;
//	dist = ten_nodes_tour->CalcReversedSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(3, dist, 0.1);
//
//	from->Id = 8; to->Id = 8;
//	dist = ten_nodes_tour->CalcReversedSubtourDistance(from, to);
//	CHECK_EQUAL_C_REAL(0, dist, 0.1);
}

TEST(Tour, EvaluateInsertTypeITest1) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1"
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2"
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3"

	STRCMP_EQUAL("1 => 2 => 3 => 1",
		paperTour->ToString().c_str());

	CHECK_EQUAL_C_REAL(137.6, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(3); // nodo "4"
	vi = paperTour->Get(0); // nodo "1"
	vj = paperTour->Get(2); // nodo "3"
	vk = paperTour->Get(1); // nodo "2"
	double newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(INF_DISTANCE, newTourDistance, 0.1);

	STRCMP_EQUAL("1 => 2 => 3 => 1",
		paperTour->ToString().c_str());

	paperTour->Reverse();
	newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(146.7, newTourDistance, 0.1);

	STRCMP_EQUAL("3 => 2 => 1 => 3",
		paperTour->ToString().c_str());

//	paperTour->Append(paper_tour->Get(4)); // nodo "4"
//
//	STRCMP_EQUAL("4 => 3 => 2 => 1 => 4",
//		paperTour->ToString().c_str());
//
//	v  = paper_tour->Get(4); // nodo "5"
//	vi = paperTour->Get(3); // nodo "1"
//	vj = paperTour->Get(2); // nodo "2"
//	vk = paperTour->Get(1); // nodo "3"
//	paperTour->InsertTypeI(v, vi, vj, vk);
//	STRCMP_EQUAL("5 => 2 => 3 => 4 => 1 => 5",
//		paperTour->ToString().c_str());
//
//	v  = paper_tour->Get(5); // nodo "6"
//	vi = paperTour->Get(1); // nodo "2"
//	vj = paperTour->Get(3); // nodo "4"
//	vk = paperTour->Get(2); // nodo "3"
//	paperTour->InsertTypeI(v, vi, vj, vk);
//	STRCMP_EQUAL("6 => 4 => 1 => 5 => 3 => 2 => 6",
//		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, EvaluateInsertTypeITest2) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(3)); // nodo "4"
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3"
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2"
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1"

	STRCMP_EQUAL("4 => 3 => 2 => 1 => 4",
		paperTour->ToString().c_str());

	CHECK_EQUAL_C_REAL(146.7, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(4); // nodo "5"
	vi = paperTour->Get(3); // nodo "1"
	vj = paperTour->Get(2); // nodo "2"
	vk = paperTour->Get(1); // nodo "3"
	double newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(INF_DISTANCE, newTourDistance, 0.1);

	STRCMP_EQUAL("4 => 3 => 2 => 1 => 4",
		paperTour->ToString().c_str());

	paperTour->Reverse();
	newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(150.2, newTourDistance, 0.1);

	STRCMP_EQUAL("1 => 2 => 3 => 4 => 1",
		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, EvaluateInsertTypeITest3) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(4)); // nodo "5"
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2"
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3"
	paperTour->Append(geniusPaperInstance->GetNode(3)); // nodo "4"
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1"

	STRCMP_EQUAL("5 => 2 => 3 => 4 => 1 => 5",
		paperTour->ToString().c_str());

	CHECK_EQUAL_C_REAL(150.2, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(5); // nodo "6"
	vi = paperTour->Get(1); // nodo "2"
	vj = paperTour->Get(3); // nodo "4"
	vk = paperTour->Get(2); // nodo "3"
	double newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(INF_DISTANCE, newTourDistance, 0.1);

	STRCMP_EQUAL("5 => 2 => 3 => 4 => 1 => 5",
		paperTour->ToString().c_str());

	paperTour->Reverse();
	newTourDistance = paperTour->EvaluateInsertTypeI(v, vi, vj, vk);

	CHECK_EQUAL_C_REAL(225.0, newTourDistance, 0.1);

	STRCMP_EQUAL("1 => 4 => 3 => 2 => 5 => 1",
		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, EvaluateInsertTypeIITest1) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(5)); // nodo "6"
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2"
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3"
	paperTour->Append(geniusPaperInstance->GetNode(4)); // nodo "5"
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1"
	paperTour->Append(geniusPaperInstance->GetNode(3)); // nodo "4"


	STRCMP_EQUAL("6 => 2 => 3 => 5 => 1 => 4 => 6",
		paperTour->ToString().c_str());

	CHECK_EQUAL_C_REAL(225.0, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(6); // nodo "7"
	vi = paperTour->Get(4); // nodo "1"
	vj = paperTour->Get(1); // nodo "2"
	vk = paperTour->Get(5); // nodo "4"
	vl = paperTour->Get(1); // nodo "2"
	double newTourDistance = paperTour->EvaluateInsertTypeII(v, vi, vj, vk, vl);

	CHECK_EQUAL_C_REAL(INF_DISTANCE, newTourDistance, 0.1);

	STRCMP_EQUAL("6 => 2 => 3 => 5 => 1 => 4 => 6",
		paperTour->ToString().c_str());

	paperTour->Reverse();
	newTourDistance = paperTour->EvaluateInsertTypeII(v, vi, vj, vk, vl);

	CHECK_EQUAL_C_REAL(238.6, newTourDistance, 0.1);

	STRCMP_EQUAL("4 => 1 => 5 => 3 => 2 => 6 => 4",
		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, EvaluateInsertTypeIITest2) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(6)); // nodo "7"
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2"
	paperTour->Append(geniusPaperInstance->GetNode(5)); // nodo "6"
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3"
	paperTour->Append(geniusPaperInstance->GetNode(4)); // nodo "5"
	paperTour->Append(geniusPaperInstance->GetNode(3)); // nodo "4"
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1"

	STRCMP_EQUAL("7 => 2 => 6 => 3 => 5 => 4 => 1 => 7",
		paperTour->ToString().c_str());

	CHECK_EQUAL_C_REAL(238.6, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(7); // nodo "8"
	vi = paperTour->Get(1); // nodo "2"
	vj = paperTour->Get(4); // nodo "5"
	vk = paperTour->Get(1); // nodo "2"
	vl = paperTour->Get(3); // nodo "3"
	double newTourDistance = paperTour->EvaluateInsertTypeII(v, vi, vj, vk, vl);

	CHECK_EQUAL_C_REAL(229.0, newTourDistance, 0.1);

	STRCMP_EQUAL("7 => 2 => 6 => 3 => 5 => 4 => 1 => 7",
		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, InsertTypeITest_LongTour) {
	pNode v, vi, vj, vk;

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 1",
		long_tour->ToString().c_str());

	v = twentyNodesInstance->GetNode(20);
	vi = twentyNodesInstance->GetNode(0);
	vj = twentyNodesInstance->GetNode(5);
	vk = twentyNodesInstance->GetNode(10);
	long_tour->InsertTypeI(v, vi, vj, vk);

	STRCMP_EQUAL(
		"100 => 6 => 5 => 4 => 3 => 2 => 11 => 10 => 9 => 8 => 7 => 12 => 13 => 14 => 15 => 16 => 1 => 100",
		long_tour->ToString().c_str());
}

TEST(Tour, InsertTypeIITest_LongTour) {
	pNode v, vi, vj, vk, vl;

	STRCMP_EQUAL("1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 17 => 18 => 19 => 20 => 1",
		long_long_tour->ToString().c_str());

	v = twentyNodesInstance->GetNode(20);
	vi = twentyNodesInstance->GetNode(0);
	vj = twentyNodesInstance->GetNode(9);
	vk = twentyNodesInstance->GetNode(16);
	vl = twentyNodesInstance->GetNode(5);
	long_long_tour->InsertTypeII(v, vi, vj, vk, vl);

	STRCMP_EQUAL("100 => 10 => 9 => 8 => 7 => 6 => 11 => 12 => 13 => 14 => 15 => 16 => 5 => 4 => 3 => 2 => 17 => 18 => 19 => 20 => 1 => 100",
		long_long_tour->ToString().c_str());
}

TEST(Tour, SolvePaperTourTest) {
	pNode v, vi, vj, vk, vl;

	pTour paperTour = new Tour(geniusPaperInstance);
	paperTour->Append(geniusPaperInstance->GetNode(0)); // nodo "1" (i)
	paperTour->Append(geniusPaperInstance->GetNode(1)); // nodo "2" (j)
	paperTour->Append(geniusPaperInstance->GetNode(2)); // nodo "3" (k)

	STRCMP_EQUAL("1 => 2 => 3 => 1",
		paperTour->ToString().c_str());

	v  = paper_tour->Get(3); // nodo "4"
	vi = paperTour->Get(0); // nodo "1"
	vj = paperTour->Get(2); // nodo "3"
	vk = paperTour->Get(1); // nodo "2"
	paperTour->InsertTypeI(v, vi, vj, vk);
	STRCMP_EQUAL("4 => 3 => 2 => 1 => 4",
		paperTour->ToString().c_str());

	v  = paper_tour->Get(4); // nodo "5"
	vi = paperTour->Get(3); // nodo "1"
	vj = paperTour->Get(2); // nodo "2"
	vk = paperTour->Get(1); // nodo "3"
	paperTour->InsertTypeI(v, vi, vj, vk);
	STRCMP_EQUAL("5 => 2 => 3 => 4 => 1 => 5",
		paperTour->ToString().c_str());

//	v  = paper_tour->Get(5); // nodo "6"
//	vi = paperTour->Get(4); // nodo "1"
//	vj = paperTour->Get(1); // nodo "2"
//	vk = paperTour->Get(2); // nodo "3"
//	paperTour->Reverse();
//	paperTour->InsertTypeI(v, vi, vj, vk);
//	cout << paperTour->ToString();
//	CHECK_EQUAL_C_REAL(225.0, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(5); // nodo "6"
	vi = paperTour->Get(1); // nodo "2"
	vj = paperTour->Get(3); // nodo "4"
	vk = paperTour->Get(2); // nodo "3"
	paperTour->InsertTypeI(v, vi, vj, vk);
	STRCMP_EQUAL("6 => 4 => 1 => 5 => 3 => 2 => 6",
		paperTour->ToString().c_str());
	CHECK_EQUAL_C_REAL(225.0, paperTour->TotalDistance(), 0.1);

	v  = paper_tour->Get(6); // nodo "7"
	vi = paperTour->Get(2); // nodo "1"
	vj = paperTour->Get(5); // nodo "2"
	vk = paperTour->Get(1); // nodo "4"
	vl = paperTour->Get(5); // nodo "2"
	paperTour->InsertTypeII(v, vi, vj, vk, vl);
	STRCMP_EQUAL("7 => 2 => 6 => 3 => 5 => 4 => 1 => 7",
		paperTour->ToString().c_str());

	v  = paper_tour->Get(7); // nodo "8"
	vi = paperTour->Get(1); // nodo "2"
	vj = paperTour->Get(4); // nodo "5"
	vk = paperTour->Get(1); // nodo "2"
	vl = paperTour->Get(3); // nodo "3"
	paperTour->InsertTypeII(v, vi, vj, vk, vl);
	STRCMP_EQUAL("8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		paperTour->ToString().c_str());

	SAFE_DELETE(paperTour);
}

TEST(Tour, TotalDistanceTest) {
	pTour small_tour = new Tour(geniusPaperInstance);
	small_tour->Append(geniusPaperInstance->GetNode(0));
	small_tour->Append(geniusPaperInstance->GetNode(1));
	small_tour->Append(geniusPaperInstance->GetNode(2));

	CHECK_EQUAL_C_REAL(137.6, small_tour->TotalDistance(), 0.1);

	SAFE_DELETE(small_tour);
}

IGNORE_TEST(Tour, SortingByDistanceFromReferenceNode) {
	fourNodesInstance = new Instance();
	fourNodesInstance->Add(new Node(1,  0, 0));
	fourNodesInstance->Add(new Node(2,  0, 1));
	fourNodesInstance->Add(new Node(3,  0, 2));
	fourNodesInstance->Add(new Node(4,  1, 2));

	pTour small_tour = new Tour(fourNodesInstance);
	small_tour->Append(fourNodesInstance->GetNode(0));
	small_tour->Append(fourNodesInstance->GetNode(1));
	small_tour->Append(fourNodesInstance->GetNode(2));

	pNode referenceNode = fourNodesInstance->GetNode(3);

	pNodeVector nodes = small_tour->GetNeighborhood(referenceNode);

	CHECK(nodes->at(0)->Id == 3);
	CHECK(nodes->at(1)->Id == 2);
	CHECK(nodes->at(2)->Id == 1);

	SAFE_DELETE(fourNodesInstance);
	SAFE_DELETE(small_tour);
}

IGNORE_TEST(Tour, GetNeighborhoodTest) {
	pInstance neigborhoodInstance = new Instance();
	neigborhoodInstance->Add(new Node(0,  0, 0));
	neigborhoodInstance->Add(new Node(1,  0, 1));
	neigborhoodInstance->Add(new Node(2,  0, 2));
	neigborhoodInstance->Add(new Node(3,  0, 3));
	neigborhoodInstance->Add(new Node(4,  0, 4));
	neigborhoodInstance->Add(new Node(5,  0, 5));
	neigborhoodInstance->Add(new Node(6,  0, 6));
	neigborhoodInstance->Add(new Node(7,  0, 7));
	neigborhoodInstance->Add(new Node(8,  0, 8));
	neigborhoodInstance->Add(new Node(9,  0, 9));
	neigborhoodInstance->Add(new Node(10, 1, 6));

	pTour neighborhood_test_tour = new Tour(neigborhoodInstance);
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(0));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(1));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(2));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(3));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(4));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(5));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(6));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(7));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(8));
	neighborhood_test_tour->Append(neigborhoodInstance->GetNode(9));

	pNode referenceNode = neigborhoodInstance->GetNode(10);

	//neighborhood_test_tour->BuildNeighborhoods(p);
	pNodeVector nodes = neighborhood_test_tour->GetNeighborhood(referenceNode);

	CHECK(nodes->size() == 4);
	CHECK(nodes->at(0)->Id == 6);
	CHECK(nodes->at(1)->Id == 5);
	CHECK(nodes->at(2)->Id == 7);
	CHECK(nodes->at(3)->Id == 4);

	SAFE_DELETE(neigborhoodInstance);
	SAFE_DELETE(neighborhood_test_tour);
}

TEST(Tour, PrintNeighborhoodsTest) {

}

} /* namespace Genius */
