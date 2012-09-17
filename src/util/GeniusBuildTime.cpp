#include "GeniusBuildTime.h"

GeniusBuildTime::GeniusBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

GeniusBuildTime::~GeniusBuildTime()
{
}

const char* GeniusBuildTime::GetDateTime()
{
    return dateTime;
}

