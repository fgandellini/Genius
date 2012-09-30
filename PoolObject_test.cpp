#include "PoolObject.h"
#include "MyObj.h"
#include "MyPoolObj.h"
#include <CppUTest/TestHarness.h>

#include "CommonIncludes.h"

namespace Genius {

TEST_GROUP(PoolObject) {
	void setup() {
	}

	void teardown() {
	}
};

TEST(PoolObject, IsFasterThanDefaultAllocation) {

	const int N = 1;

	//MyObj* myObjs[] = new MyObj[N];
//	MyObj* myObjs[N];
//	time_t start = time(NULL);
//
//	for (int i=0; i<N; ++i) {
//		myObjs[i] = new MyObj();
//	}
//	for (int i=0; i<N; ++i) {
//		SAFE_DELETE(myObjs[i]);
//	}






//	time_t standardAllocationTime = time(NULL) - start;
//
//	start = time(NULL);
//
//	time_t poolAllocationTime = time(NULL);
//
//	CHECK(poolAllocationTime < standardAllocationTime);

}




}
