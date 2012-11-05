#include "Genius.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

pInstance paper_instance;

TEST_GROUP(Genius) {
	void setup() {
		paper_instance = new Instance();
		paper_instance->push_back(new Node(1, 21.8, 72.8));
		paper_instance->push_back(new Node(2, 31.5, 10.8));
		paper_instance->push_back(new Node(3, 16.3, 13.7));
		paper_instance->push_back(new Node(4,  3.7, 54.8));
		paper_instance->push_back(new Node(5, 21.0, 21.7));
		paper_instance->push_back(new Node(6, 69.3,  1.3));
		paper_instance->push_back(new Node(7, 40.8, 60.1));
		paper_instance->push_back(new Node(8, 27.8, 26.2));
	}

	void teardown() {
		SAFE_DELETE_VECTOR(paper_instance);
	}
};

TEST(Genius, PrintDistancesMatrix) {
//	pNode refNode;
//	cout << endl << endl << "distance matrix" << endl << "    ";
//	for(int i=0; i<(int)paper_instance->size(); i++) {
//		cout << i+1 << "\t";
//	}
//	cout << endl;
//	for(int i=0; i<(int)paper_instance->size(); i++) {
//		refNode = paper_instance->at(i);
//		cout << i+1 << " | ";
//		for(int j=0; j<(int)paper_instance->size(); j++) {
//			cout << refNode->DistanceFrom(paper_instance->at(j)) << "\t";
//		}
//		cout << endl;
//	}
//	cout << endl;
//
/*
    1		2		3		4		5		6		7		8
--+----------------------------------------------------------------
1 | 0		62.7542	59.3554	25.5267	51.1063	85.84	22.8537	46.9847
2 | 62.7542	0		15.4742	52.0465	15.1347	38.9755	50.1695	15.8382
3 | 59.3554	15.4742	0 		42.988	9.27847	54.4312	52.471	16.9853
4 | 25.5267	52.0465	42.988	0		37.3484	84.6499	37.4767	37.4001
5 | 51.1063	15.1347	9.27847	37.3484	0		52.4314	43.2042	8.15414
6 | 85.84	38.9755	54.4312	84.6499	52.4314	0		65.3429	48.3969
7 | 22.8537	50.1695	52.471	37.4767	43.2042	65.3429	0		36.3072
8 | 46.9847	15.8382	16.9853	37.4001	8.15414	48.3969	36.3072	0

*/
}

TEST(Genius, AddNodeToPaperTour) {

}

} /* namespace Genius */
