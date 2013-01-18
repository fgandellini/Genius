#ifndef INSTANCELOADER_H_
#define INSTANCELOADER_H_

#include "CommonIncludes.h"
#include "Instance.h"
#include "Tour.h"

namespace Genius {

class InstanceLoader {
private:
	static string GetFilename(string absolutePath);
public:
	InstanceLoader();
	virtual ~InstanceLoader();

	static pInstance LoadFromFile(string file);
	static pTour LoadOptTourFromFile(pInstance instance, string file);
};
//typedef InstanceLoader* pInstanceLoader;

} /* namespace Genius */
#endif /* INSTANCELOADER_H_ */
