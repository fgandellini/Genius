/*
 * Instance.cpp
 *
 *  Created on: 16/nov/2012
 *      Author: fede
 */

#include "Instance.h"

namespace Genius {

//int Instance::NodesCount = 0;

Instance::Instance() {
	this->nodes = new NodeVector();
	this->Name = "Unknown";
}

Instance::~Instance() {
	for (int n=0; n<this->Size(); n++) {
		SAFE_DELETE( this->nodes->at(n) );
	}
	SAFE_DELETE(this->nodes);
}

//void Instance::Load(pNodeVector nodes) {
//	Instance::Nodes = nodes;
//	Instance::NodesCount = (int)Instance::Nodes->size();
//}

void Instance::Add(pNode node) {
	this->nodes->push_back(node);
}

pNode Instance::GetNode(int index) {
	return this->nodes->at(index);
}

pNode Instance::GetNodeById(int id) {
	return NULL;
}

int Instance::GetIndex(pNode node) {
	for (int n=0; n<(int)this->nodes->size(); n++) {
		if (this->nodes->at(n)->Id == node->Id) {
			return n;
		}
	}
	return -1;
}

int Instance::Size() {
	return (int)this->nodes->size();
}

} /* namespace Genius */
