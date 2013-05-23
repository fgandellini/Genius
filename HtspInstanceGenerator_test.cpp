#include "HtspInstanceGenerator.h"
#include "InstanceLoader.h"
#include "Drawer.h"
#include <CppUTest/TestHarness.h>

namespace Genius {

TEST_GROUP(HtspInstanceGenerator) {
	void setup() {}
	void teardown() {}
};

TEST(HtspInstanceGenerator, CreateInstanceTest) {
	HtspInstanceGenerator::CreateInstance("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest01.htsp", 21, 5, 2);

	pHtspNodeParser parser = new HtspNodeParser();
	pInstance testInstance = InstanceLoader::LoadFromFile("/home/fede/workspace/tsp_instances/htsp/HtspInstanceTest01.htsp", parser);

	CHECK(testInstance->Type == HTSP);
	CHECK(testInstance->P == 5);
	CHECK(testInstance->k == 2);

	CHECK(testInstance->GetNode(0)->Priority == 1);
	CHECK(testInstance->GetNode(1)->Priority == 1);
	CHECK(testInstance->GetNode(2)->Priority == 1);
	CHECK(testInstance->GetNode(3)->Priority == 1);
	CHECK(testInstance->GetNode(4)->Priority == 2);
	CHECK(testInstance->GetNode(5)->Priority == 2);
	CHECK(testInstance->GetNode(6)->Priority == 2);
	CHECK(testInstance->GetNode(7)->Priority == 2);
	CHECK(testInstance->GetNode(8)->Priority == 3);
	CHECK(testInstance->GetNode(9)->Priority == 3);
	CHECK(testInstance->GetNode(10)->Priority == 3);
	CHECK(testInstance->GetNode(11)->Priority == 3);
	CHECK(testInstance->GetNode(12)->Priority == 4);
	CHECK(testInstance->GetNode(13)->Priority == 4);
	CHECK(testInstance->GetNode(14)->Priority == 4);
	CHECK(testInstance->GetNode(15)->Priority == 4);
	CHECK(testInstance->GetNode(16)->Priority == 5);
	CHECK(testInstance->GetNode(17)->Priority == 5);
	CHECK(testInstance->GetNode(18)->Priority == 5);
	CHECK(testInstance->GetNode(19)->Priority == 5);
	CHECK(testInstance->GetNode(20)->Priority == 5);

	pDrawer d = new Drawer();
	d->Draw(testInstance, "TestInstance");

	SAFE_DELETE(d);
	SAFE_DELETE(testInstance);
	SAFE_DELETE(parser);
}

} /* namespace Genius */
