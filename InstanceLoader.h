#ifndef INSTANCELOADER_H_
#define INSTANCELOADER_H_

#include "CommonIncludes.h"
#include "Instance.h"

namespace Genius {

class InstanceLoader {
public:
	InstanceLoader();
	virtual ~InstanceLoader();

	static pInstance LoadFromFile(string file);
};
//typedef InstanceLoader* pInstanceLoader;

} /* namespace Genius */
#endif /* INSTANCELOADER_H_ */
