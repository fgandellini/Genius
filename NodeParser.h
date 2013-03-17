#ifndef NODEPARSER_H_
#define NODEPARSER_H_

#include "Node.h"

namespace Genius {

class NodeParser {
public:
	NodeParser();
	virtual ~NodeParser();
	int Type;
	virtual pNode parseNode(FILE* fileStream) = 0;
};
typedef NodeParser* pNodeParser;

class TspNodeParser : public NodeParser {
public:
	TspNodeParser();
	virtual ~TspNodeParser();
	pNode parseNode(FILE* fileStream);
};
typedef TspNodeParser* pTspNodeParser;

class HtspNodeParser : public NodeParser {
public:
	HtspNodeParser();
	virtual ~HtspNodeParser();
	pNode parseNode(FILE* fileStream);
};
typedef HtspNodeParser* pHtspNodeParser;

} /* namespace Genius */
#endif /* NODEPARSER_H_ */
