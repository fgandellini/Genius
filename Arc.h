#ifndef ARC_H_
#define ARC_H_

#include "Node.h"

namespace Genius {

class Arc {
private:
	pNode start;
	pNode end;

	void init(pNode from, pNode to);

public:
	Arc(pNode from, pNode to);
	Arc(int fromId, int toId);
	virtual ~Arc();

	pNode getStart();
	pNode getEnd();
};
typedef Arc* pArc;
typedef vector<pArc> Arcs;
typedef Arcs* pArcs;

} /* namespace Genius */
#endif /* ARC_H_ */
