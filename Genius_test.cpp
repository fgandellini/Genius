/*
 * Genius_test.cpp
 *
 *  Created on: 19/ott/2012
 *      Author: fede
 */

#include "Genius.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

Genius* paper_tour;
Genius* my_tour;

TEST_GROUP(Genius) {
	void setup() {
		paper_tour = new Genius();
		my_tour = new Genius();
	}

	void teardown() {
		SAFE_DELETE(paper_tour);
		SAFE_DELETE(my_tour);
	}
};

TEST(Genius, GetNextTest) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6");
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");

	STRCMP_EQUAL("2", my_tour->GetNext("1").c_str());
	STRCMP_EQUAL("3", my_tour->GetNext("2").c_str());
	STRCMP_EQUAL("1", my_tour->GetNext("10").c_str());
	STRCMP_EQUAL("7", my_tour->GetNext("6").c_str());
}

TEST(Genius, GetPrevTest) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6");
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");

	STRCMP_EQUAL("10", my_tour->GetPrev("1").c_str());
	STRCMP_EQUAL("1", my_tour->GetPrev("2").c_str());
	STRCMP_EQUAL("9", my_tour->GetPrev("10").c_str());
	STRCMP_EQUAL("5", my_tour->GetPrev("6").c_str());
}

TEST(Genius, GoToTest) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6");
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");

	my_tour->GoTo("7");
	STRCMP_EQUAL("7", my_tour->tour.current_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("6", my_tour->tour.previous_element().c_str());

	my_tour->GoTo("4");
	STRCMP_EQUAL("3", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("3", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("4", my_tour->tour.next_element().c_str());

	my_tour->GoTo("8");
	STRCMP_EQUAL("8", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("8", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.previous_element().c_str());
}

TEST(Genius, GetSubtourTest) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6");
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");

	data::clist<string> subtour =
		my_tour->GetSubtour("3", "8");

	STRCMP_EQUAL(
		"3 => 4 => 5 => 6 => 7 => 8 => 3",
		my_tour->TourToString(subtour).c_str());

	data::clist<string> rev_subtour =
			my_tour->GetReversedSubtour("3", "8");

	STRCMP_EQUAL(
		"8 => 7 => 6 => 5 => 4 => 3 => 8",
		my_tour->TourToString(rev_subtour).c_str());
}

TEST(Genius, ShouldInsertNodeInMyTour) {
	my_tour->tour.add_element("1"); // i
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6"); // j
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");
	my_tour->tour.add_element("11"); // k
	my_tour->tour.add_element("12");
	my_tour->tour.add_element("13");
	my_tour->tour.add_element("14");
	my_tour->tour.add_element("15");
	my_tour->tour.add_element("16");

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 1",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeI("100", "1", "6", "11");

	STRCMP_EQUAL(
		"100 => 6 => 5 => 4 => 3 => 2 => 11 => 10 => 9 => 8 => 7 => 12 => 13 => 14 => 15 => 16 => 1 => 100",
		my_tour->TourToString().c_str());
}

TEST(Genius, CanFindIndexOfAnElement) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");

	CHECK(my_tour->FindIndex("1") ==  0);
	CHECK(my_tour->FindIndex("2") ==  1);
	CHECK(my_tour->FindIndex("3") ==  2);
	CHECK(my_tour->FindIndex("4") == -1);
	CHECK(my_tour->FindIndex("1") ==  0);
	CHECK(my_tour->FindIndex("3") ==  2);
	CHECK(my_tour->FindIndex("2") ==  1);
}

TEST(Genius, TestIsBetween) {
	my_tour->tour.add_element("1");
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6");
	my_tour->tour.add_element("7");

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 1",
		my_tour->TourToString().c_str());

	CHECK(my_tour->IsBetween("3", "2", "4") == true); // caso normale, nodi adiacenti
	CHECK(my_tour->IsBetween("1", "7", "2") == true); // check testa, nodi adiacenti
	CHECK(my_tour->IsBetween("7", "6", "1") == true); // check coda, nodi adiacenti
	CHECK(my_tour->IsBetween("4", "2", "7") == true); // caso normale, nodi non adiacenti
	CHECK(my_tour->IsBetween("1", "5", "3") == true); // check testa, nodi non adiacenti
	CHECK(my_tour->IsBetween("7", "6", "4") == true); // check coda, nodi non adiacenti

	CHECK(my_tour->IsBetween("3", "4", "2") == false); // caso normale, nodi adiacenti
	CHECK(my_tour->IsBetween("1", "2", "7") == false); // check testa, nodi adiacenti
	CHECK(my_tour->IsBetween("7", "1", "6") == false); // check coda, nodi adiacenti
	CHECK(my_tour->IsBetween("4", "7", "2") == false); // caso normale, nodi non adiacenti
	CHECK(my_tour->IsBetween("1", "3", "5") == false); // check testa, nodi non adiacenti
	CHECK(my_tour->IsBetween("7", "4", "6") == false); // check coda, nodi non adiacenti

	CHECK(my_tour->IsBetween("3", "3", "6") == true); // x e from collassati
	CHECK(my_tour->IsBetween("6", "3", "6") == true); // x e to collassati
	CHECK(my_tour->IsBetween("3", "3", "3") == true); // x, from e to collassati
}

TEST(Genius, TestReverse) {
	my_tour->tour.add_element("1"); // i
	my_tour->tour.add_element("2"); // k
	my_tour->tour.add_element("3"); // j

	STRCMP_EQUAL(
		"1 => 2 => 3 => 1",
		my_tour->TourToString().c_str());

	my_tour->tour.o_reverse_process() = true;
	my_tour->tour.sort();

	STRCMP_EQUAL(
		"3 => 2 => 1 => 3",
		my_tour->TourToString().c_str());

	my_tour->tour.o_reverse_process() = false;
	my_tour->tour.sort();

	STRCMP_EQUAL(
			"1 => 2 => 3 => 1",
			my_tour->TourToString().c_str());

}

TEST(Genius, ReverseTour) {
	my_tour->tour.add_element("primo");
	my_tour->tour.add_element("secondo");
	my_tour->tour.add_element("terzo");
	my_tour->tour.add_element("quarto");
	my_tour->tour.add_element("quinto");
	my_tour->tour.add_element("sesto");

	STRCMP_EQUAL(
		"primo => secondo => terzo => quarto => quinto => sesto => primo",
		my_tour->TourToString().c_str());

	int size = (int)my_tour->tour.size();
	my_tour->tour.reverse_order(0, size);

	STRCMP_EQUAL(
		"sesto => quinto => quarto => terzo => secondo => primo => sesto",
		my_tour->TourToString().c_str());

}

TEST(Genius, ReverseTour2) {
	my_tour->tour.add_element("1"); // i
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6"); // j
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10");
	my_tour->tour.add_element("11"); // k
	my_tour->tour.add_element("12");
	my_tour->tour.add_element("13");
	my_tour->tour.add_element("14");
	my_tour->tour.add_element("15");
	my_tour->tour.add_element("16");

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 1",
		my_tour->TourToString().c_str());

	// reverse from j to k
	my_tour->tour.reverse_order(5, 11); // elemento 5 compreso, 11 escluso

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 11 => 10 => 9 => 8 => 7 => 6 => 12 => 13 => 14 => 15 => 16 => 1",
		my_tour->TourToString().c_str());

}

TEST(Genius, TestInsertIIOnMyTour) {
	my_tour->tour.add_element("1"); // i
	my_tour->tour.add_element("2");
	my_tour->tour.add_element("3");
	my_tour->tour.add_element("4");
	my_tour->tour.add_element("5");
	my_tour->tour.add_element("6"); // l
	my_tour->tour.add_element("7");
	my_tour->tour.add_element("8");
	my_tour->tour.add_element("9");
	my_tour->tour.add_element("10"); // j
	my_tour->tour.add_element("11");
	my_tour->tour.add_element("12");
	my_tour->tour.add_element("13");
	my_tour->tour.add_element("14");
	my_tour->tour.add_element("15");
	my_tour->tour.add_element("16");
	my_tour->tour.add_element("17"); // k
	my_tour->tour.add_element("18");
	my_tour->tour.add_element("19");
	my_tour->tour.add_element("20");

	STRCMP_EQUAL(
		"1 => 2 => 3 => 4 => 5 => 6 => 7 => 8 => 9 => 10 => 11 => 12 => 13 => 14 => 15 => 16 => 17 => 18 => 19 => 20 => 1",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeII("100", "1", "10", "17", "6");

	STRCMP_EQUAL(
		"100 => 10 => 9 => 8 => 7 => 6 => 11 => 12 => 13 => 14 => 15 => 16 => 5 => 4 => 3 => 2 => 17 => 18 => 19 => 20 => 1 => 100",
		my_tour->TourToString().c_str());
}

TEST(Genius, ShouldInsertNodeInPaperTour) {
	my_tour->tour.add_element("1"); // i
	my_tour->tour.add_element("2"); // k
	my_tour->tour.add_element("3"); // j

	STRCMP_EQUAL(
		"1 => 2 => 3 => 1",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeI("4", "1", "3", "2");

	STRCMP_EQUAL(
		"4 => 3 => 2 => 1 => 4",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeI("5", "1", "2", "3");

	STRCMP_EQUAL(
		"5 => 2 => 3 => 4 => 1 => 5",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeI("6", "2", "4", "3");

	STRCMP_EQUAL(
		"6 => 4 => 1 => 5 => 3 => 2 => 6",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeII("7", "1", "2", "4", "2");

	STRCMP_EQUAL(
		"7 => 2 => 6 => 3 => 5 => 4 => 1 => 7",
		my_tour->TourToString().c_str());

	my_tour->InsertTypeII("8", "2", "5", "2", "3");

	STRCMP_EQUAL(
		"8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		my_tour->TourToString().c_str());
}

} /* namespace Genius */
