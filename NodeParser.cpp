#include "NodeParser.h"

namespace Genius {

NodeParser::NodeParser() { this->Type = UNKNOWN; }
NodeParser::~NodeParser() {}

TspNodeParser::TspNodeParser() { this->Type = TSP; }
TspNodeParser::~TspNodeParser() {}
pNode TspNodeParser::parseNode(FILE* fileStream) {
	int id;
	double x;
	double y;
	fscanf(fileStream, "%d %lf %lf", &id, &x, &y);
	return new Node(id, x, y);
}

HtspNodeParser::HtspNodeParser() { this->Type = HTSP; }
HtspNodeParser::~HtspNodeParser() {}
pNode HtspNodeParser::parseNode(FILE* fileStream) {
	int id;
	int priority;
	double x;
	double y;
	fscanf(fileStream, "%d %d %lf %lf", &id, &priority, &x, &y);
	return new Node(id, x, y, priority);
}

} /* namespace Genius */

