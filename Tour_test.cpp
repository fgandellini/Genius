#include "Tour.h"
#include<CppUTest/TestHarness.h>

namespace Genius {

pTour tour;

TEST_GROUP(Tour) {
	void setup() {
		tour = new Tour();
	}

	void teardown() {
		SAFE_DELETE(tour);
	}
};

IGNORE_TEST(Tour, WhenCreatedTourIsEmpty) {
	CHECK(tour->Length() == 0);
}

IGNORE_TEST(Tour, CanAppendNodes) {
	CHECK(tour->Append(1));
	CHECK(tour->Length() == 1);
}


IGNORE_TEST(Tour, ReferencesAreCircular) {
}


IGNORE_TEST(Tour, HasAnIncrementalIdWhenCreated) {
	pTour firstTour = new Tour();
	pTour secondTour = new Tour();
//	int expectedSecondTourId = firstTour->getId() + 1;
//	CHECK(secondTour->getId() == expectedSecondTourId);
	SAFE_DELETE(firstTour);
	SAFE_DELETE(secondTour);
}

IGNORE_TEST(Tour, IsEmptyWhenCreated) {
//	CHECK(tour->Length() == 0);
}

IGNORE_TEST(Tour, CanAddAnArc) {
	//tour->add(new Arc((int)0, (int)2));
	//CHECK(tour->Length() == 2);
}


} /* namespace Genius */
