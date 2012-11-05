#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"

namespace Genius {

class Genius {
public:
	Genius();
	virtual ~Genius();

	void Geni(vector<string> &nodesToVisit);
};

} /* namespace Genius */
#endif /* GENIUS_H_ */
