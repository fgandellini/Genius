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
	STRCMP_EQUAL("8", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("7", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("6", my_tour->tour.previous_element().c_str());

	my_tour->GoTo("4");
	STRCMP_EQUAL("3", my_tour->tour.previous_element().c_str());
	STRCMP_EQUAL("4", my_tour->tour.next_element().c_str());
	STRCMP_EQUAL("5", my_tour->tour.next_element().c_str());
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

IGNORE_TEST(Genius, ShouldInsertNodeInPaperTour) {
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
}

} /* namespace Genius */
