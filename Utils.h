#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <sstream>

using namespace std;

namespace Genius {

class Utils {
public:
	Utils();
	virtual ~Utils();

	static string ToString(int i);
	static string ToString(int i, bool twoChars);
	static string ToString(double d);
};

} /* namespace Genius */
#endif /* UTILS_H_ */
