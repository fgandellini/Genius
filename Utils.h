#ifndef UTILS_H_
#define UTILS_H_

#define V_NONE 0
#define V_ERRORS 1
#define V_WARNING 3
#define V_INFO 5
#define V_DEBUG 9

#define VERBOSITY V_NONE

#define ENABLE_DRAWER false

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace Genius {

class Utils {
public:
	Utils();
	virtual ~Utils();

	static string ToString(int i);
	static string ToString(int i, bool twoChars);
	static string ToString(double d);

	static std::ostream& Log(int level);
};

#define OUT Utils::Log(V_NONE)
#define ERR Utils::Log(V_ERRORS)
#define WARN Utils::Log(V_WARNING)
#define INFO Utils::Log(V_INFO)
#define DBG Utils::Log(V_DEBUG)


} /* namespace Genius */
#endif /* UTILS_H_ */
