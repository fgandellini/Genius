#include "Utils.h"

namespace Genius {

Utils::Utils() {}
Utils::~Utils() {}

string Utils::ToString(int i) {
	ostringstream convert;
	convert << i;
	return convert.str();
}

string Utils::ToString(int i, bool twoChars) {
	ostringstream convert;
	(twoChars && (i < 10)) ? convert << "0" << i : convert << i;
	return convert.str();
}

string Utils::ToString(double d) {
	ostringstream convert;
	convert << d;
	return convert.str();
}

} /* namespace Genius */
