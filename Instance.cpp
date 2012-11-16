/*
 * Instance.cpp
 *
 *  Created on: 16/nov/2012
 *      Author: fede
 */

#include "Instance.h"

namespace Genius {

string Instance::Name = "Unknown Genius Instance";
string Instance::File = "path/of/instance/file";

int Instance::NodesCount = 0;
pNodeVector Instance::Nodes = new NodeVector();

Instance::Instance() {
}

Instance::~Instance() {
}

void Instance::Load(pNodeVector nodes) {
	Instance::Nodes = nodes;
	Instance::NodesCount = (int)Instance::Nodes->size();
}

} /* namespace Genius */
