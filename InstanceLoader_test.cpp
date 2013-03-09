#include "InstanceLoader.h"
#include "Genius.h"
#include "Drawer.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

pInstance ulysses16;
pTour ulysses16OptimalTour;
pGenius ulysses16Genius;

pDrawer drawer;

TEST_GROUP(InstanceLoader) {
	void setup() {
		drawer = new Drawer();

		ulysses16 = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/with_sol/ulysses16/ulysses16.tsp");
		ulysses16OptimalTour = InstanceLoader::LoadOptTourFromFile(ulysses16,
			"/home/fede/workspace/tsp_instances/with_sol/ulysses16/ulysses16.opt.tour");

		ulysses16Genius = new Genius();
	}
	void teardown() {
		SAFE_DELETE(ulysses16);
		SAFE_DELETE(ulysses16OptimalTour);

		SAFE_DELETE(ulysses16Genius);

		SAFE_DELETE(drawer);
	}
};

TEST(InstanceLoader, LoadInstanceFromFileTest) {
	CHECK(ulysses16 != NULL);
	CHECK(ulysses16->Size() == 16);

	CHECK(ulysses16->GetNode(0)->Id == 1);
	CHECK(ulysses16->GetNode(1)->Id == 2);
	CHECK(ulysses16->GetNode(2)->Id == 3);
	CHECK(ulysses16->GetNode(3)->Id == 4);
	CHECK(ulysses16->GetNode(4)->Id == 5);
	CHECK(ulysses16->GetNode(5)->Id == 6);
	CHECK(ulysses16->GetNode(6)->Id == 7);
	CHECK(ulysses16->GetNode(7)->Id == 8);
	CHECK(ulysses16->GetNode(8)->Id == 9);
	CHECK(ulysses16->GetNode(9)->Id == 10);
	CHECK(ulysses16->GetNode(10)->Id == 11);
	CHECK(ulysses16->GetNode(11)->Id == 12);
	CHECK(ulysses16->GetNode(12)->Id == 13);
	CHECK(ulysses16->GetNode(13)->Id == 14);
	CHECK(ulysses16->GetNode(14)->Id == 15);
	CHECK(ulysses16->GetNode(15)->Id == 16);

	CHECK_EQUAL_C_REAL(38.24, ulysses16->GetNode(0)->X, 0.001);
	CHECK_EQUAL_C_REAL(39.57, ulysses16->GetNode(1)->X, 0.001);
	CHECK_EQUAL_C_REAL(40.56, ulysses16->GetNode(2)->X, 0.001);
	CHECK_EQUAL_C_REAL(36.26, ulysses16->GetNode(3)->X, 0.001);
	CHECK_EQUAL_C_REAL(33.48, ulysses16->GetNode(4)->X, 0.001);
	CHECK_EQUAL_C_REAL(37.56, ulysses16->GetNode(5)->X, 0.001);
	CHECK_EQUAL_C_REAL(38.42, ulysses16->GetNode(6)->X, 0.001);
	CHECK_EQUAL_C_REAL(37.52, ulysses16->GetNode(7)->X, 0.001);
	CHECK_EQUAL_C_REAL(41.23, ulysses16->GetNode(8)->X, 0.001);
	CHECK_EQUAL_C_REAL(41.17, ulysses16->GetNode(9)->X, 0.001);
	CHECK_EQUAL_C_REAL(36.08, ulysses16->GetNode(10)->X, 0.001);
	CHECK_EQUAL_C_REAL(38.47, ulysses16->GetNode(11)->X, 0.001);
	CHECK_EQUAL_C_REAL(38.15, ulysses16->GetNode(12)->X, 0.001);
	CHECK_EQUAL_C_REAL(37.51, ulysses16->GetNode(13)->X, 0.001);
	CHECK_EQUAL_C_REAL(35.49, ulysses16->GetNode(14)->X, 0.001);
	CHECK_EQUAL_C_REAL(39.36, ulysses16->GetNode(15)->X, 0.001);

	CHECK_EQUAL_C_REAL(20.42, ulysses16->GetNode(0)->Y, 0.001);
	CHECK_EQUAL_C_REAL(26.15, ulysses16->GetNode(1)->Y, 0.001);
	CHECK_EQUAL_C_REAL(25.32, ulysses16->GetNode(2)->Y, 0.001);
	CHECK_EQUAL_C_REAL(23.12, ulysses16->GetNode(3)->Y, 0.001);
	CHECK_EQUAL_C_REAL(10.54, ulysses16->GetNode(4)->Y, 0.001);
	CHECK_EQUAL_C_REAL(12.19, ulysses16->GetNode(5)->Y, 0.001);
	CHECK_EQUAL_C_REAL(13.11, ulysses16->GetNode(6)->Y, 0.001);
	CHECK_EQUAL_C_REAL(20.44, ulysses16->GetNode(7)->Y, 0.001);
	CHECK_EQUAL_C_REAL(9.10, ulysses16->GetNode(8)->Y, 0.001);
	CHECK_EQUAL_C_REAL(13.05, ulysses16->GetNode(9)->Y, 0.001);
	CHECK_EQUAL_C_REAL(-5.21, ulysses16->GetNode(10)->Y, 0.001);
	CHECK_EQUAL_C_REAL(15.13, ulysses16->GetNode(11)->Y, 0.001);
	CHECK_EQUAL_C_REAL(15.35, ulysses16->GetNode(12)->Y, 0.001);
	CHECK_EQUAL_C_REAL(15.17, ulysses16->GetNode(13)->Y, 0.001);
	CHECK_EQUAL_C_REAL(14.32, ulysses16->GetNode(14)->Y, 0.001);
	CHECK_EQUAL_C_REAL(19.56, ulysses16->GetNode(15)->Y, 0.001);
}

TEST(InstanceLoader, SolveInstanceFromFileTest) {

//	cout << endl
//		 << "ulysses16 Optimal Tour: " << ulysses16OptimalTour->ToString()
//		 << " (" << ulysses16OptimalTour->TotalDistance() << ")" << endl;

	pTour geniTour = ulysses16Genius->ExecuteGeni(ulysses16, 4);
//	cout << "ulysses16 GENI tour: " << geniTour->ToString()
//		 << " (" << geniTour->TotalDistance() << ")" << endl;

	pTour solution = ulysses16Genius->ExecuteUs(geniTour, 4);
//	cout << "ulysses16 solution: " << solution->ToString()
//		 << " (" << solution->TotalDistance() << ")" << endl;

	INFO << "!!] Optimal tour                    ("
		 << ulysses16OptimalTour->TotalDistance() << ") "
		 << ulysses16OptimalTour->ToString() << flush << endl;

	CHECK(solution->Length() == ulysses16OptimalTour->Length());
	//CHECK(solution->TotalDistance() >= ulysses16OptimalTour->TotalDistance());

	//CHECK(solution->IsEqualTo(ulysses16OptimalTour));

	drawer->Draw(ulysses16, "instance");
	drawer->Draw(ulysses16OptimalTour, "optimalTour");
	drawer->Draw(solution, "solution");

	SAFE_DELETE(geniTour);
	SAFE_DELETE(solution);
}

TEST(InstanceLoader, SolveInstancesTest) {

//	int p = 4;
//
//	pInstance instance1 = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/with_sol/att48/att48.tsp");
//	CHECK(instance1->Size() > 0);
//	pTour optTour1 = InstanceLoader::LoadOptTourFromFile(instance1,
//		"/home/fede/workspace/tsp_instances/with_sol/att48/att48.opt.tour");
//	CHECK(instance1->Size() == optTour1->Length());
//
//	pTour geniSol1 = genius->ExecuteGeni(instance1, p);
//	pTour solution1 = genius->ExecuteUs(geniSol1, p);
//
//	CHECK(solution1->Length() == optTour1->Length());
//	CHECK(solution1->TotalDistance() >= optTour1->TotalDistance());
//	//CHECK(solution->IsEqualTo(ulysses16OptimalTour));
//
//	drawer->Draw(instance1, "instance");
//	drawer->Draw(optTour1, "optTour");
//	drawer->Draw(solution1, "solution");
//
//	SAFE_DELETE(geniSol1);
//	SAFE_DELETE(solution1);
//	SAFE_DELETE(optTour1);
//	SAFE_DELETE(instance1);

	pGenius genius = new Genius();

//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/att48/att48.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/att48/att48.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/st70/st70.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/st70/st70.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/berlin52/berlin52.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/berlin52/berlin52.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/pr76/pr76.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/pr76/pr76.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/gr96/gr96.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/gr96/gr96.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/eil76/eil76.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/eil76/eil76.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/eil51/eil51.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/eil51/eil51.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/ulysses22/ulysses22.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/ulysses22/ulysses22.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/kroA100/kroA100.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/kroA100/kroA100.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/kroC100/kroC100.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/kroC100/kroC100.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/kroD100/kroD100.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/kroD100/kroD100.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/eil101/eil101.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/eil101/eil101.opt.tour", 4);

	genius->ExecuteGeniusWithTimeTrace(
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.tsp",
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.opt.tour", 4);

	genius->ExecuteGeniusWithTimeTrace(
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.tsp",
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.opt.tour", 4);

//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/ch150/ch150.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/ch150/ch150.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/lin105/lin105.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/lin105/lin105.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/a280/a280.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/a280/a280.opt.tour", 4);
//
//	genius->ExecuteGenius(
//		"/home/fede/workspace/tsp_instances/with_sol/pcb442/pcb442.tsp",
//		"/home/fede/workspace/tsp_instances/with_sol/pcb442/pcb442.opt.tour", 4);

	SAFE_DELETE(genius);
}


//IGNORE_TEST(InstanceLoader, ulysses16UnstringErrorTest) {
//
//	pTour startTour = ulysses16TourFactory->GetTour();
//
//	startTour->Append(ulysses16->GetNode(2));
//	startTour->Append(ulysses16->GetNode(1));
//	startTour->Append(ulysses16->GetNode(3));
//	startTour->Append(ulysses16->GetNode(7));
//	startTour->Append(ulysses16->GetNode(5));
//	startTour->Append(ulysses16->GetNode(6));
//	startTour->Append(ulysses16->GetNode(9));
//	startTour->Append(ulysses16->GetNode(8));
//	startTour->Append(ulysses16->GetNode(10));
//	startTour->Append(ulysses16->GetNode(4));
//	startTour->Append(ulysses16->GetNode(14));
//	startTour->Append(ulysses16->GetNode(13));
//	startTour->Append(ulysses16->GetNode(12));
//	startTour->Append(ulysses16->GetNode(11));
//	startTour->Append(ulysses16->GetNode(15));
//	startTour->Append(ulysses16->GetNode(0));
//
//	STRCMP_EQUAL(
//		"3 => 2 => 4 => 8 => 6 => 7 => 10 => 9 => 11 => 5 => 15 => 14 => 13 => 12 => 16 => 1 => 3",
//		startTour->ToString().c_str());
//
//	pNode n = ulysses16->GetNode(3);
//
//	ulysses16Genius->UnstringNodeFromTour(n, startTour, 4);
//	cout << "final tour: " << startTour->ToString();
//
//	SAFE_DELETE(startTour);
//}

} /* namespace Genius */
