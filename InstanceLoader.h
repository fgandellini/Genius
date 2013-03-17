#ifndef INSTANCELOADER_H_
#define INSTANCELOADER_H_

#include "CommonIncludes.h"
#include "Instance.h"
#include "Tour.h"
#include "NodeParser.h"

namespace Genius {

class InstanceLoader {
private:
	static string GetFilename(string absolutePath);
public:
	InstanceLoader();
	virtual ~InstanceLoader();

	static pInstance LoadFromFile(string file);
	static pInstance LoadFromFile(string file, pNodeParser nodeParser);

	static pTour LoadOptTourFromFile(pInstance instance, string file);

	static pNode GetNodeToAddToInstance(FILE* fileStream);
};
//typedef InstanceLoader* pInstanceLoader;

} /* namespace Genius */
#endif /* INSTANCELOADER_H_ */
