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

TEST(HtspSolver, Solve) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolver htspSolver = new HtspSolver(ulysses16Htsp);
	pTour htspTour = htspSolver->Solve();

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspTour);
	SAFE_DELETE(htspSolver);
}


} /* namespace Genius */
