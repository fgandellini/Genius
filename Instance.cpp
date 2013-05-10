#include "Instance.h"

namespace Genius {

Instance::Instance() {
	this->nodes = new NodeVector();
	this->Name = "Unknown";
	this->Type = UNKNOWN;
	this->P = 0;
	this->k = 0;
}

Instance::~Instance() {
	for (int n=0; n<this->Size(); n++) {
		SAFE_DELETE( this->nodes->at(n) );
	}
	SAFE_DELETE(this->nodes);
}

void Instance::Add(pNode node) {
	this->nodes->push_back(node);
}

pNode Instance::GetNode(int index) {
	return this->nodes->at(index);
}

pNode Instance::GetNodeById(int id) {
	for (int n=0; n<(int)this->nodes->size(); n++) {
		pNode node = this->nodes->at(n);
		if (node->Id == id) {
			return node;
		}
	}
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
