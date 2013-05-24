#include "Benchmark.h"

#include "CommonIncludes.h"
#include "HtspInstanceGenerator.h"
#include "HtspSolverTypeI.h"
#include "HtspSolverTypeII.h"

#include <CppUTest/TestHarness.h>

namespace Genius {

pBenchmark b;

TEST_GROUP(Benchmark) {
	void setup() {
		b = new Benchmark();
	}
	void teardown() {
		SAFE_DELETE(b);
	}
};

TEST(Benchmark, SolveGeneratedInstanceTest) {
	HtspInstanceGenerator::CreateInstance("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest_Benchmark_01.htsp", 12, 3, 0);

	pHtspNodeParser parser = new HtspNodeParser();
	pInstance testInstance = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest_Benchmark_01.htsp", parser);

	pDrawer d = new Drawer();
	d->Draw(testInstance, "TestInstance");

	pHtspSolverTypeI htspSolverI = new HtspSolverTypeI(testInstance);
//	b->StartTimer("SI");
	pTour htspSolutionI = htspSolverI->Solve();
//	cout << "Solver Type I Time: " << b->TimerElapsedToString("SI") << "s" << endl;

	d->Draw(htspSolutionI, "SolverI Solution");

	pHtspSolverTypeII htspSolverII = new HtspSolverTypeII(testInstance);
//	b->StartTimer("SII");
	pTour htspSolutionII = htspSolverII->Solve();
//	cout << "Solver Type II Time: " << b->TimerElapsedToString("SII") << "s" << endl;

	d->Draw(htspSolutionII, "SolverII Solution");

	SAFE_DELETE(d);
	SAFE_DELETE(testInstance);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolverI);
	SAFE_DELETE(htspSolutionI);
	SAFE_DELETE(htspSolverII);
	SAFE_DELETE(htspSolutionII);
}

TEST(Benchmark, SolveBigGeneratedInstanceTest) {
	HtspInstanceGenerator::CreateInstance("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest_Benchmark_02.htsp", 100, 5, 0);

	pHtspNodeParser parser = new HtspNodeParser();
	pInstance testInstance = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest_Benchmark_02.htsp", parser);

	pDrawer d = new Drawer();
	d->Draw(testInstance, "TestInstance");

	pHtspSolverTypeI htspSolverI = new HtspSolverTypeI(testInstance);
//	b->StartTimer("SI");
	pTour htspSolutionI = htspSolverI->Solve();
//	cout << "Solver Type I Time: " << b->TimerElapsedToString("SI") << "s" << endl;

	d->Draw(htspSolutionI, "SolverI Solution");

	pHtspSolverTypeII htspSolverII = new HtspSolverTypeII(testInstance);
//	b->StartTimer("SII");
	pTour htspSolutionII = htspSolverII->Solve();
//	cout << "Solver Type II Time: " << b->TimerElapsedToString("SII") << "s" << endl;

	d->Draw(htspSolutionII, "SolverII Solution");

	SAFE_DELETE(d);
	SAFE_DELETE(testInstance);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolverI);
	SAFE_DELETE(htspSolutionI);
	SAFE_DELETE(htspSolverII);
	SAFE_DELETE(htspSolutionII);
}

IGNORE_TEST(Benchmark, GenerateInstances) {
	int nodes[] = { 100, 200, 300, 400 };
	int P[] = { 5, 10 };
	int K[] = { 0, 1, 2, 3 };

	for (int n=0; n<4; n++) {
		for (int p=0; p<2; p++) {
			for (int k=0; k<4; k++) {
				HtspInstanceGenerator::CreateInstance("/home/fede/workspace/tsp_instances/htsp/benchmark/" +
					Utils::ToString(nodes[n]) + "_" +
					Utils::ToString(P[p]) + "_" +
					Utils::ToString(K[k]) + ".htsp",
					nodes[n], P[p], K[k]);
			}
		}
	}
}

TEST(Benchmark, SolveBenchmarkInstances) {
	int nodes[] = { 100, 200, 300, 400 };
	int P[] = { 5, 10 };
	int K[] = { 0, 1, 2, 3 };

	cout << endl << endl << "Starting benchmark" << endl;
	cout << "nodes P k Solution_TSP Solution_HTSP_I SolutionHTSP_II Time_I Time_II" << endl;

	for (int n=0; n<4; n++) {
		for (int p=0; p<2; p++) {
			for (int k=0; k<4; k++) {
				string instance = "/home/fede/workspace/tsp_instances/htsp/benchmark_2013-05-23/" +
					Utils::ToString(nodes[n]) + "_" + Utils::ToString(P[p]) + "_" + Utils::ToString(K[k]) + ".htsp";

				pHtspNodeParser parser = new HtspNodeParser();
				pInstance testInstance = InstanceLoader::LoadFromFile(instance, parser);

				pHtspSolverTypeI htspSolverI = new HtspSolverTypeI(testInstance);
				b->StartTimer("SI");
				pTour htspSolutionI = htspSolverI->Solve();
				b->StopTimer("SI");

				pHtspSolverTypeII htspSolverII = new HtspSolverTypeII(testInstance);
				b->StartTimer("SII");
				pTour htspSolutionII = htspSolverII->Solve();
				b->StopTimer("SII");

				cout << nodes[n] << " " << P[p] << " " << K[k] << " "
					 << htspSolverI->GetSolutionSummary() << " " << htspSolverII->GetSolutionSummary() << " "
					 << b->TimerElapsedToString("SI") << " " << b->TimerElapsedToString("SII") << endl;

				SAFE_DELETE(testInstance);
				SAFE_DELETE(parser);
				SAFE_DELETE(htspSolverI);
				SAFE_DELETE(htspSolutionI);
				SAFE_DELETE(htspSolverII);
				SAFE_DELETE(htspSolutionII);
			}
		}
	}
}

IGNORE_TEST(Benchmark, OptimizationSolverITest) {
	string instance = "/home/fede/workspace/tsp_instances/htsp/benchmark_2013-05-23/200_5_0.htsp";

	pHtspNodeParser parser = new HtspNodeParser();
	pInstance testInstance = InstanceLoader::LoadFromFile(instance, parser);

	pHtspSolverTypeI htspSolverI = new HtspSolverTypeI(testInstance);
	b->StartTimer("SI");
	pTour htspSolutionI = htspSolverI->Solve();
	b->StopTimer("SI");

	pHtspSolverTypeII htspSolverII = new HtspSolverTypeII(testInstance);
	b->StartTimer("SII");
	pTour htspSolutionII = htspSolverII->Solve();
	b->StopTimer("SII");

	cout << endl
		 << "200 5 0 "
		 << htspSolverI->GetSolutionSummary() << " " << htspSolverII->GetSolutionSummary() << " "
		 << b->TimerElapsedToString("SI") << " " << b->TimerElapsedToString("SII")
		 << endl;

	SAFE_DELETE(testInstance);
	SAFE_DELETE(parser);
	SAFE_DELETE(htspSolverI);
	SAFE_DELETE(htspSolutionI);
	SAFE_DELETE(htspSolverII);
	SAFE_DELETE(htspSolutionII);
}

} /* namespace Genius */
