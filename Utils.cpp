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

std::ostream& Utils::Log(int level) {
	static std::ostream rc(std::cout.rdbuf());
	rc.rdbuf(level <= VERBOSITY ? std::cout.rdbuf() : NULL);
	return rc;
}

} /* namespace Genius */
