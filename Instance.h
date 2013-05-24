#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "CommonIncludes.h"
#include "Node.h"

namespace Genius {

class Instance {
protected:
	pNodeVector nodes;

	double CalculateDistanceBetweenNodes(pNode node1, pNode node2);

public:
	Instance();
	virtual ~Instance();

	double** Distances;

	void Add(pNode node);
	pNode GetNode(int index);
	pNode GetNodeById(int id);
	int GetIndex(pNode node);

	string Name;
	int Type;
	int P; // Numero di livelli di priorità
	int k; // Parametro per rilassare il vincolo sulla priorità

	int Size();

	void CalculateDistances();
};
typedef Instance* pInstance;
typedef vector<pInstance> InstanceVector;
typedef InstanceVector* pInstanceVector;

} /* namespace Genius */
#endif /* INSTANCE_H_ */
