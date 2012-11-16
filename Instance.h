#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "CommonIncludes.h"
#include "Node.h"

namespace Genius {

class Instance {
public:
	Instance();
	virtual ~Instance();

	static string Name;
	static string File;

	static int NodesCount;
	static pNodeVector Nodes;

	static void Load(pNodeVector nodes);
};
typedef Instance* pInstance;

} /* namespace Genius */
#endif /* INSTANCE_H_ */
