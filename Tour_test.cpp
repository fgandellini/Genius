#include "Tour.h"
#include<CppUTest/TestHarness.h>

namespace Genius {

pTour paper_tourz;
pTour ten_nodes_tour;
pTour long_tour;
pNode reference;
pNode from;
pNode to;
pNode x;

TEST_GROUP(Tour) {
	void setup() {
		paper_tourz = new Tour();
		paper_tourz->Append(new Node(1, 21.8, 72.8));
		paper_tourz->Append(new Node(2, 31.5, 10.8));
		paper_tourz->Append(new Node(3, 16.3, 13.7));
		paper_tourz->Append(new Node(4,  3.7, 54.8));
		paper_tourz->Append(new Node(5, 21.0, 21.7));
		paper_tourz->Append(new Node(6, 69.3,  1.3));
		paper_tourz->Append(new Node(7, 40.8, 60.1));
		paper_tourz->Append(new Node(8, 27.8, 26.2));

		ten_nodes_tour = new Tour();
		ten_nodes_tour->Append(new Node(1,  0, 0));
		ten_nodes_tour->Append(new Node(2,  0, 0));
		ten_nodes_tour->Append(new Node(3,  0, 0));
		ten_nodes_tour->Append(new Node(4,  0, 0));
		ten_nodes_tour->Append(new Node(5,  0, 0));
		ten_nodes_tour->Append(new Node(6,  0, 0));
		ten_nodes_tour->Append(new Node(7,  0, 0));
		ten_nodes_tour->Append(new Node(8,  0, 0));
		ten_nodes_tour->Append(new Node(9,  0, 0));
		ten_nodes_tour->Append(new Node(10, 0, 0));

		long_tour = new Tour();
		long_tour->Append(new Node(1,  0, 0));
		long_tour->Append(new Node(2,  0, 0));
		long_tour->Append(new Node(3,  0, 0));
		long_tour->Append(new Node(4,  0, 0));
		long_tour->Append(new Node(5,  0, 0));
		long_tour->Append(new Node(6,  0, 0));
		long_tour->Append(new Node(7,  0, 0));
		long_tour->Append(new Node(8,  0, 0));
		long_tour->Append(new Node(9,  0, 0));
		long_tour->Append(new Node(10, 0, 0));
		long_tour->Append(new Node(11, 0, 0));
		long_tour->Append(new Node(12, 0, 0));
		long_tour->Append(new Node(13, 0, 0));
		long_tour->Append(new Node(14, 0, 0));
		long_tour->Append(new Node(15, 0, 0));
		long_tour->Append(new Node(16, 0, 0));

		reference = new Node(0, 0, 0);
		from = new Node(0, 0, 0);
		to = new Node(0, 0, 0);
		x = new Node(0, 0, 0);
	}

	void teardown() {
		for (int i=0; i<paper_tourz->Length(); i++) {
			paper_tourz->DeleteAt(i);
		}
		SAFE_DELETE(paper_tourz);

		for (int i=0; i<ten_nodes_tour->Length(); i++) {
			ten_nodes_tour->DeleteAt(i);
		}
		SAFE_DELETE(ten_nodes_tour);

		for (int i=0; i<long_tour->Length(); i++) {
			long_tour->DeleteAt(i);
		}
		SAFE_DELETE(long_tour);

		SAFE_DELETE(reference);
		SAFE_DELETE(from);
		SAFE_DELETE(to);
		SAFE_DELETE(x);
	}
};

TEST(Tour, GoToNodeTest) {
	reference->Id = 7;
	paper_tourz->GoTo(reference);
	CHECK(paper_tourz->nodes.current_element()->Id == 7);
	CHECK(paper_tourz->nodes.next_element()->Id == 7);
	CHECK(paper_tourz->nodes.previous_element()->Id == 7);
	CHECK(paper_tourz->nodes.next_element()->Id == 7);
	CHECK(paper_tourz->nodes.previous_element()->Id == 7);
	CHECK(paper_tourz->nodes.previous_element()->Id == 6);

	reference->Id = 4;
	paper_tourz->GoTo(reference);
	CHECK(paper_tourz->nodes.previous_element()->Id == 3);
	CHECK(paper_tourz->nodes.next_element()->Id == 3);
	CHECK(paper_tourz->nodes.next_element()->Id == 4);

	reference->Id = 8;
	paper_tourz->GoTo(reference);
	CHECK(paper_tourz->nodes.next_element()->Id == 8);
	CHECK(paper_tourz->nodes.previous_element()->Id == 8);
	CHECK(paper_tourz->nodes.previous_element()->Id == 7);
}

TEST(Tour, GetNextTest) {
	reference->Id = 1;
	CHECK(ten_nodes_tour->Next(reference)->Id == 2);

	reference->Id = 2;
	CHECK(ten_nodes_tour->Next(reference)->Id == 3);

	reference->Id = 10;
	CHECK(ten_nodes_tour->Next(reference)->Id == 1);

	reference->Id = 6;
	CHECK(ten_nodes_tour->Next(reference)->Id == 7);
}

TEST(Tour, GetPrevTest) {
	reference->Id = 1;
	CHECK(ten_nodes_tour->Previous(reference)->Id == 10);

	reference->Id = 2;
	CHECK(ten_nodes_tour->Previous(reference)->Id == 1);

	reference->Id = 10;
	CHECK(ten_nodes_tour->Previous(reference)->Id == 9);

	reference->Id = 6;
	CHECK(ten_nodes_tour->Previous(reference)->Id == 5);
}

TEST(Tour, GetSubtourTest) {
	data::clist<pNode> subtour;

	from->Id = 3; to->Id = 8;
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
	reference->Id = 1;
	CHECK(ten_nodes_tour->GetIndex(reference) ==  0);

	reference->Id = 2;
	CHECK(ten_nodes_tour->GetIndex(reference) ==  1);

	reference->Id = 3;
	CHECK(ten_nodes_tour->GetIndex(reference) ==  2);

	reference->Id = 12;
	CHECK(ten_nodes_tour->GetIndex(reference) == -1);

	reference->Id = 1;
	CHECK(ten_nodes_tour->GetIndex(reference) ==  0);

	reference->Id = 3;
	CHECK(ten_nodes_tour->GetIndex(reference) ==  2);

	reference->Id = 2;
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

TEST(Tour, InsertTypeITest_LongTour) {

	pNode v  = new Node(0, 0, 0);
	pNode vi = new Node(0, 0, 0);
	pNode vj = new Node(0, 0, 0);
	pNode vk = new Node(0, 0, 0);

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 1",
		long_tour->ToString().c_str());

	v->Id = 100;
	vi->Id = 1;
	vj->Id = 6;
	vk->Id = 11;
	long_tour->InsertTypeI(v, vi, vj, vk);

	STRCMP_EQUAL(
		"100 => 6 => 5 => 4 => 3 => 2 => 11 => 10 => 9 => 8 => 7 => 12 => 13 => 14 => 15 => 16 => 1 => 100",
		long_tour->ToString().c_str());

	SAFE_DELETE(vi);
	SAFE_DELETE(vj);
	SAFE_DELETE(vk);
}

TEST(Tour, TotalDistanceTest) {
	pTour smal_ltour = new Tour();
	smal_ltour->Append(new Node(1, 21.8, 72.8));
	smal_ltour->Append(new Node(2, 31.5, 10.8));
	smal_ltour->Append(new Node(3, 16.3, 13.7));

	CHECK_EQUAL_C_REAL(137.6, smal_ltour->TotalDistance(), 0.1);

	for (int i=0; i<smal_ltour->Length(); i++) {
		smal_ltour->DeleteAt(i);
	}
	SAFE_DELETE(smal_ltour);
}

TEST(Tour, BuildNeighborhoodsTest) {

}

} /* namespace Genius */
