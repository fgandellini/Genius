/*
 * HtspSolverTypeII_test.cpp
 *
 *  Created on: 09/mag/2013
 *      Author: fede
 */

#include "HtspSolverTypeII.h"
#include "HtspInstanceGenerator.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

TEST_GROUP(HtspSolverTypeII) {
	void setup() {}
	void teardown() {}
};

TEST(HtspSolverTypeII, SolveTest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverTypeII htspSolver = new HtspSolverTypeII(ulysses16Htsp);
	pTour htspSolution = htspSolver->Solve();

	CHECK(htspSolver->subtours->size() == 2);

	pSubtour firstSubtour = htspSolver->subtours->at(0);
	CHECK(firstSubtour->tour->Length() == 10);
	CHECK(firstSubtour->candidateArcs->size() == 10);

	pSubtour secondSubtour = htspSolver->subtours->at(1);
	CHECK(secondSubtour->tour->Length() == 6);
	CHECK(secondSubtour->candidateArcs->size() == 6);

	CHECK(htspSolution->Length() == ulysses16Htsp->Size());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	SAFE_DELETE(htspSolution);
}

} /* namespace Genius */
