#ifndef HTSPINSTANCEGENERATOR_H_
#define HTSPINSTANCEGENERATOR_H_

#include "CommonIncludes.h"

namespace Genius {

class HtspInstanceGenerator {
private:
	static int GetLevel(int index, int nodesPerLevel, int P);

public:
	HtspInstanceGenerator();
	virtual ~HtspInstanceGenerator();

	static void CreateInstance(string filePath, int dimension, int P, int k);
};

} /* namespace Genius */
#endif /* HTSPINSTANCEGENERATOR_H_ */
