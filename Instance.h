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

	void Add(pNode node);
	pNode GetNode(int index);
	pNode GetNodeById(int id);
	int GetIndex(pNode node);

	string Name;
	int Type;
	int P; // Numero di livelli di priorità
	int k; // Parametro per rilassare il vincolo sulla priorità

	int Size();
};
typedef Instance* pInstance;
typedef vector<pInstance> InstanceVector;
typedef InstanceVector* pInstanceVector;

} /* namespace Genius */
#endif /* INSTANCE_H_ */
