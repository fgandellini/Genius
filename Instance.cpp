#include "Instance.h"

namespace Genius {

Instance::Instance() {
	this->nodes = new NodeVector();
	this->Name = "Unknown";
	this->Type = UNKNOWN;
	this->P = 0;
	this->k = 0;
	this->Distances = NULL;
}

Instance::~Instance() {
	if (this->Distances != NULL) {
		for (int n=0; n<this->Size(); n++) {
			delete[] this->Distances[n];
		}
		delete[] this->Distances;
	}

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

void Instance::CalculateDistances() {
	int nodes = this->Size();

	this->Distances = new double*[nodes];

	for (int n1 = 0 ; n1 < nodes ; n1++ ) {
		pNode node1 = this->GetNode(n1);

		this->Distances[n1] = new double[nodes];

		for (int n2 = 0 ; n2 < nodes ; n2++ ) {
			pNode node2 = this->GetNode(n2);

			this->Distances[node1->Id - 1][node2->Id -1] =
				this->CalculateDistanceBetweenNodes(node1, node2);
		}
	}

	for (int n = 0 ; n < nodes ; n++ ) {
		this->GetNode(n)->Instance = this;
	}
}

double Instance::CalculateDistanceBetweenNodes(pNode node1, pNode node2) {
	double xi = node1->X;
	double yi = node1->Y;
	double xj = node2->X;
	double yj = node2->Y;
	double xx = ( (xi - xj) * (xi - xj) );
	double yy = ( (yi - yj) * (yi - yj) );
	return sqrt(xx + yy);
}

} /* namespace Genius */
