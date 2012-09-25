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

TEST(Tour, HasAnIncrementalIdWhenCreated) {
	pTour firstTour = new Tour();
	pTour secondTour = new Tour();
	int expectedSecondTourId = firstTour->getId() + 1;
	CHECK(secondTour->getId() == expectedSecondTourId);
	SAFE_DELETE(firstTour);
	SAFE_DELETE(secondTour);
}

TEST(Tour, IsEmptyWhenCreated) {
	CHECK(tour->Length() == 0);
}

TEST(Tour, CanAddAnArc) {
	tour->add(new Arc(0, 2));
	CHECK(tour->Length() == 2);
}


} /* namespace Genius */
