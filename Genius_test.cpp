#include "Genius.h"
#include "TourFactory.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

pInstance paperInstance;

pGenius genius;
pTour paperTourStep1;
pTour paperTourStep2;
pTour paperTourStep3;
pTour paperTourStep4;
pTour paperTourStep5;

pTourFactory tf;

TEST_GROUP(Genius) {
	void setup() {

		paperInstance = new Instance();
		paperInstance->Add(new Node(1, 21.8, 72.8));
		paperInstance->Add(new Node(2, 31.5, 10.8));
		paperInstance->Add(new Node(3, 16.3, 13.7));
		paperInstance->Add(new Node(4,  3.7, 54.8));
		paperInstance->Add(new Node(5, 21.0, 21.7));
		paperInstance->Add(new Node(6, 69.3,  1.3));
		paperInstance->Add(new Node(7, 40.8, 60.1));
		paperInstance->Add(new Node(8, 27.8, 26.2));

		genius = new Genius();
		tf = new TourFactory(paperInstance);

		paperTourStep1 = tf->GetTour();
		paperTourStep1->Append(paperInstance->GetNode(0));
		paperTourStep1->Append(paperInstance->GetNode(1));
		paperTourStep1->Append(paperInstance->GetNode(2));

		paperTourStep2 = tf->GetTour();
		paperTourStep2->Append(paperInstance->GetNode(0));
		paperTourStep2->Append(paperInstance->GetNode(1));
		paperTourStep2->Append(paperInstance->GetNode(2));
		paperTourStep2->Append(paperInstance->GetNode(3));

		paperTourStep3 = tf->GetTour();
		paperTourStep3->Append(paperInstance->GetNode(4));
		paperTourStep3->Append(paperInstance->GetNode(1));
		paperTourStep3->Append(paperInstance->GetNode(2));
		paperTourStep3->Append(paperInstance->GetNode(3));
		paperTourStep3->Append(paperInstance->GetNode(0));

		paperTourStep4 = tf->GetTour();
		paperTourStep4->Append(paperInstance->GetNode(5));
		paperTourStep4->Append(paperInstance->GetNode(1));
		paperTourStep4->Append(paperInstance->GetNode(2));
		paperTourStep4->Append(paperInstance->GetNode(4));
		paperTourStep4->Append(paperInstance->GetNode(0));
		paperTourStep4->Append(paperInstance->GetNode(3));

		paperTourStep5 = tf->GetTour();
		paperTourStep5->Append(paperInstance->GetNode(6));
		paperTourStep5->Append(paperInstance->GetNode(1));
		paperTourStep5->Append(paperInstance->GetNode(5));
		paperTourStep5->Append(paperInstance->GetNode(2));
		paperTourStep5->Append(paperInstance->GetNode(4));
		paperTourStep5->Append(paperInstance->GetNode(3));
		paperTourStep5->Append(paperInstance->GetNode(0));
	}

	void teardown() {
		SAFE_DELETE(paperInstance);

		SAFE_DELETE(paperTourStep1);
		SAFE_DELETE(paperTourStep2);
		SAFE_DELETE(paperTourStep3);
		SAFE_DELETE(paperTourStep4);
		SAFE_DELETE(paperTourStep5);

		SAFE_DELETE(genius);
		SAFE_DELETE(tf);
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

TEST(Genius, EvaluateInsertionParamsForPaperTourStep1) {

	pNode v = paperInstance->GetNode(3);
	InsertTypeIParams params =
		genius->EvaluateBestInsertTypeIParams(paperTourStep1, v, 4);

	CHECK(v->Id  == 4);
	CHECK(params.vi->Id == 1);
	CHECK(params.vj->Id == 3);
	CHECK(params.vk->Id == 2);
	CHECK(params.tourMustBeReversed == true);
	CHECK_EQUAL_C_REAL(146.7, params.distance, 0.1);
}

TEST(Genius, EvaluateInsertionParamsForPaperTourStep2) {

	pNode v = paperInstance->GetNode(4);
	InsertTypeIParams params =
		genius->EvaluateBestInsertTypeIParams(paperTourStep2, v, 4);

	CHECK(v->Id  == 5);
	CHECK(params.vi->Id == 2);
	CHECK(params.vj->Id == 1);
	CHECK(params.vk->Id == 4);
	CHECK(params.tourMustBeReversed == true);
	CHECK_EQUAL_C_REAL(150.2, params.distance, 0.1);
}

TEST(Genius, EvaluateInsertionParamsForPaperTourStep3) {

	pNode v = paperInstance->GetNode(5);
	InsertTypeIParams params =
		genius->EvaluateBestInsertTypeIParams(paperTourStep3, v, 4);

	CHECK(v->Id  == 6);
	CHECK(params.vi->Id == 4);
	CHECK(params.vj->Id == 2);
	CHECK(params.vk->Id == 5);
	CHECK(params.tourMustBeReversed == true);
	CHECK_EQUAL_C_REAL(225.0, params.distance, 0.1);
}

TEST(Genius, EvaluateInsertionParamsForPaperTourStep4) {

	pNode v = paperInstance->GetNode(6);
	InsertTypeIIParams params =
		genius->EvaluateBestInsertTypeIIParams(paperTourStep4, v, 4);

	CHECK(v->Id  == 7);
	CHECK(params.vi->Id == 2);
	CHECK(params.vj->Id == 1);
	CHECK(params.vk->Id == 2);
	CHECK(params.vl->Id == 4);
	CHECK(params.tourMustBeReversed == true);
	CHECK_EQUAL_C_REAL(238.6, params.distance, 0.1);
}

TEST(Genius, EvaluateInsertionParamsForPaperTourStep5) {

	pNode v = paperInstance->GetNode(7);
	InsertTypeIIParams params =
		genius->EvaluateBestInsertTypeIIParams(paperTourStep5, v, 4);

	CHECK(v->Id == 8);
	CHECK(params.vi->Id == 2);
	CHECK(params.vj->Id == 5);
	CHECK(params.vk->Id == 2);
	CHECK(params.vl->Id == 3);
	CHECK(params.tourMustBeReversed == false);
	CHECK_EQUAL_C_REAL(229.0, params.distance, 0.1);
}

TEST(Genius, BAAAAADErrorTest) {
	pNode node = paperInstance->GetNode(4);
	pTour tour = paperTourStep2;

	genius->StringNodeInTour(node, tour, 4);

	node = paperInstance->GetNode(5);
	CHECK(tour->Length() == 5);
	STRCMP_EQUAL("5 => 1 => 4 => 3 => 2 => 5",
		tour->ToString().c_str());

	genius->StringNodeInTour(node, tour, 4);

	CHECK(tour->Length() == 6);
	STRCMP_EQUAL("6 => 2 => 3 => 5 => 1 => 4 => 6",
		tour->ToString().c_str());

	CHECK_EQUAL_C_REAL(225.0, tour->TotalDistance(), 0.1);
}

TEST(Genius, PaperTourStringingTest) {
	pNode node = NULL;
	pTour tour = paperTourStep1;
	CHECK(tour->Length() == 3);
	STRCMP_EQUAL("1 => 2 => 3 => 1",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(137.6, tour->TotalDistance(), 0.1);

	node = paperInstance->GetNode(3);
	genius->StringNodeInTour(node, tour, 4);
	CHECK(tour->Length() == 4);
	STRCMP_EQUAL("4 => 3 => 2 => 1 => 4",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(146.7, tour->TotalDistance(), 0.1);

	node = paperInstance->GetNode(4);
	genius->StringNodeInTour(node, tour, 4);
	CHECK(tour->Length() == 5);
	STRCMP_EQUAL("5 => 2 => 3 => 4 => 1 => 5",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(150.2, tour->TotalDistance(), 0.1);

	node = paperInstance->GetNode(5);
	genius->StringNodeInTour(node, tour, 4);
	CHECK(tour->Length() == 6);
	STRCMP_EQUAL("6 => 2 => 3 => 5 => 1 => 4 => 6",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(225.0, tour->TotalDistance(), 0.1);

	node = paperInstance->GetNode(6);
	genius->StringNodeInTour(node, tour, 4);
	CHECK(tour->Length() == 7);
	STRCMP_EQUAL("7 => 1 => 4 => 5 => 3 => 6 => 2 => 7",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(238.6, tour->TotalDistance(), 0.1);

	node = paperInstance->GetNode(7);
	genius->StringNodeInTour(node, tour, 4);
	CHECK(tour->Length() == 8);
	STRCMP_EQUAL("8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(229.0, tour->TotalDistance(), 0.1);
}

TEST(Genius, ApplyGeniToPaperTourWithP_4) {
	pTour tour = genius->ExecuteGeni(paperInstance, 4);

	STRCMP_EQUAL("8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(229.0, tour->TotalDistance(), 0.1);

	SAFE_DELETE(tour);
}

TEST(Genius, ApplyGeniToPaperTourWithP_5) { // NO! Ma funziona con p=6 ...mah...
	pTour tour = genius->ExecuteGeni(paperInstance, 6);

	STRCMP_EQUAL("8 => 4 => 1 => 7 => 6 => 2 => 3 => 5 => 8",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(223.0, tour->TotalDistance(), 0.1);

	SAFE_DELETE(tour);
}

TEST(Genius, PaperTourUnstringingTest) {
	pTour tour = genius->ExecuteGeni(paperInstance, 4);

	STRCMP_EQUAL("8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(229.0, tour->TotalDistance(), 0.1);

	pTour t = genius->ExecuteUs(tour, 4);
//	cout << "Final Tour after US Optimization: " << t->ToString().c_str() << endl;

	STRCMP_EQUAL("8 => 5 => 3 => 4 => 1 => 7 => 6 => 2 => 8",
		tour->ToString().c_str());
	CHECK_EQUAL_C_REAL(223.0, t->TotalDistance(), 0.1);

	SAFE_DELETE(t);
	SAFE_DELETE(tour);
}

} /* namespace Genius */
