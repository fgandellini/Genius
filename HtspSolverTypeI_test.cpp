#include "HtspSolverTypeI.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

TEST_GROUP(HtspSolver) {
	void setup() {}
	void teardown() {}
};

TEST(HtspSolver, SolveTypeITest) {
	pHtspNodeParser parser = new HtspNodeParser();
	pInstance ulysses16Htsp = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/ulysses16.htsp", parser);

	pHtspSolverTypeI htspSolver = new HtspSolverTypeI(ulysses16Htsp);
	pTour htspSolution = htspSolver->Solve();

	CHECK(htspSolution->Length() == ulysses16Htsp->Size());
	STRCMP_EQUAL(
		"1p1 => 3p1 => 2p1 => 4p1 => 8p3 => 5p2 => 9p3 => 10p3 => 7p2 => 6p2 => 15p5 => 11p4 => 14p5 => 13p5 => 12p4 => 16p5 => 1p1",
		htspSolution->ToString().c_str());

	SAFE_DELETE(ulysses16Htsp);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolver);
	SAFE_DELETE(htspSolution);
}

} /* namespace Genius */
