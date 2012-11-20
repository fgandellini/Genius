#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "CommonIncludes.h"
#include "Node.h"

namespace Genius {

class Instance {
private:
	pNodeVector nodes;

public:
	Instance();
	virtual ~Instance();

	//static string Name;
	//static string File;

	//static int NodesCount;

	//static void Load(pNodeVector nodes);

	void Add(pNode node);
	pNode GetNode(int index);
	pNode GetNodeById(int id);

	int Size();
};
typedef Instance* pInstance;

} /* namespace Genius */
#endif /* INSTANCE_H_ */
