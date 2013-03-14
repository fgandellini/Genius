#define RUN_TESTS

#ifndef RUN_TESTS // -- Production Main ---------------------------------------
#include "CommonIncludes.h"
#include "Utils.h"
#include "InstanceLoader.h"
#include "Instance.h"
#include "Genius.h"

using namespace Genius;

int main(int argc, char** argv) {
/*
	pNode v  = new Node(0, 0, 0);
	pNode vi = new Node(0, 0, 0);
	pNode vj = new Node(0, 0, 0);
	pNode vk = new Node(0, 0, 0);

	pTour long_tour = new Tour();
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

	cout << "Initial tour: " << long_tour->ToString() << endl;

	v->Id = 100;
	vi->Id = 1;
	vj->Id = 6;
	vk->Id = 11;
	long_tour->InsertTypeI(v, vi, vj, vk);

	cout << "End tour: " << long_tour->ToString() << endl;

	//SAFE_DELETE(v);
	SAFE_DELETE(vi);
	SAFE_DELETE(vj);
	SAFE_DELETE(vk);
	SAFE_DELETE(long_tour);
*/

	pGenius genius = new Genius::Genius();

	genius->ExecuteGeniusWithTimeTrace(
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.tsp",
		"/home/fede/workspace/tsp_instances/with_sol/ch130/ch130.opt.tour", 4);

	SAFE_DELETE(genius);

	return EXIT_SUCCESS;
}

#else // -- Test Main ---------------------------------------------------------

#include <CppUTest/CommandLineTestRunner.h>

int main(int argc, char** argv) {
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

#endif
