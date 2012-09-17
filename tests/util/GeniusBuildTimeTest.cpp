#include "CppUTest/TestHarness.h"
#include "GeniusBuildTime.h"

TEST_GROUP(GeniusBuildTime)
{
  GeniusBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new GeniusBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(GeniusBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

