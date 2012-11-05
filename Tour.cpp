#include "Tour.h"

namespace Genius {

static bool CompareNodes(const pNode first, const int second) {
	return first->Id == second;
}

//pNode referenceNode;
//bool CompareNodesByDistance (const pNode first, const int second) {
//	if (referenceNode )
//
//}

Tour::Tour() : nodes() {
	this->Id = 0;
}

Tour::~Tour() {
//	int length = this->Length();
//	for (int i=0; i<length; i++) {
//		SAFE_DELETE(this->nodes[i]);
//	}
//	this->nodes.clear_all();
}

int Tour::Length() const {
	return (int)this->nodes.size();
}

void Tour::Append(pNode node) {
	this->nodes.add_element(node);
}

pNode Tour::Current() {
	return this->nodes.current_element();
}

pNode Tour::Next() {
	return this->nodes.next_element();
}

pNode Tour::Previous() {
	return this->nodes.previous_element();
}

void Tour::GoTo(pNode node) {
	this->nodes.index.set_to_begin();
	this->nodes.h_get_element(this->nodes.f_find(node->Id, &CompareNodes));
}

pNode Tour::Next(pNode node) {
	this->GoTo(node);
	this->nodes.next_element();
	pNode next = this->nodes.next_element();
	this->nodes.index.set_to_begin();
	return next;
}

pNode Tour::Previous(pNode node) {
	this->GoTo(node);
	pNode prev = this->nodes.previous_element();
	this->nodes.index.set_to_begin();
	return prev;
}

void Tour::DeleteAt(int position) {
	pNode nodeToDelete = this->nodes.get_element(position);
	SAFE_DELETE(nodeToDelete);
}

int Tour::GetIndex(pNode node) {
	this->nodes.index.set_to_begin();
    for (int i = 0; i < (int)this->nodes.size(); i++) {
    	if (this->nodes.next_element()->Id == node->Id) {
    		this->nodes.index.set_to_begin();
    		return i;
    	}
    }
    this->nodes.index.set_to_begin();
    return -1;
}

bool Tour::IsBetween(pNode x, pNode from, pNode to) {
	this->nodes.index.set_to_begin();

    if (x->Id == from->Id) { // found!
    	return true;
    }

    if (x->Id == to->Id) { // found!
    	return true;
    }

    int fromIndex = this->GetIndex(from);
    pNode current = this->nodes.h_get_element(fromIndex);
    while(current->Id != to->Id) {
    	if (current->Id == x->Id) { // found!
    		this->nodes.index.set_to_begin();
    		return true;
    	}
    	current = this->nodes.next_element();
    }

    this->nodes.index.set_to_begin();
    return false;
}

data::clist<pNode> Tour::GetSubtour(pNode from, pNode to) {
	data::clist<pNode> subtour;

	this->GoTo(from);
	//this->nodes.next_element();
	//pNode current = from;

	pNode current = this->Current();
	this->nodes.next_element();

	while (current->Id != to->Id) {
		subtour.add_element(current);
		current = this->nodes.next_element();
	}
	subtour.add_element(current);
	this->nodes.index.set_to_begin();

	return subtour;
}

data::clist<pNode> Tour::GetReversedSubtour(pNode from, pNode to) {
	data::clist<pNode> subtour;

	this->GoTo(to);
	//pNode current = to;

	pNode current = this->Current();

	while (current->Id != from->Id) {
		subtour.add_element(current);
		current = this->nodes.previous_element();
	}
	subtour.add_element(current);
	this->nodes.index.set_to_begin();

	return subtour;
}

void Tour::AddSubtour(data::clist<pNode> subtour, data::clist<pNode> &result) {
	int subtourSize = (int)subtour.size();
	for (int i=0; i<subtourSize; i++) {
		result.add_element(subtour[i]);
	}
}

void Tour::InsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
	data::clist<pNode> result;

	assert(vk->Id != vi->Id);
	assert(vk->Id != vj->Id);

	if (!this->IsBetween(vk, vj, vi)) {
		this->nodes.reverse_order();
	}

	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	result.add_element(v);

	data::clist<pNode> subtour_viplus1_vj =
		this->GetReversedSubtour(viplus1, vj);
	this->AddSubtour(subtour_viplus1_vj, result);

	data::clist<pNode> subtour_vjplus1_vk =
		this->GetReversedSubtour(vjplus1, vk);
	this->AddSubtour(subtour_vjplus1_vk, result);

	data::clist<pNode> subtour_vkplus1_vi =
		this->GetSubtour(vkplus1, vi);
	this->AddSubtour(subtour_vkplus1_vi, result);


	this->nodes = result;
}



//void Genius::InsertTypeII(string v, string vi, string vj, string vk, string vl) {
//	data::clist<string> result;
//	string current = "";
//
//	string viplus1 = this->GetNext(vi);
//	string vjplus1 = this->GetNext(vj);
//	string vkminus1 = this->GetPrev(vk);
//	string vlminus1 = this->GetPrev(vl);
//
//	assert(vk.compare(vj) != 0);
//	assert(vk.compare(vjplus1) != 0);
//	assert(vl.compare(vi) != 0);
//	assert(vl.compare(viplus1) != 0);
//
//	if (!this->IsBetween(vk, vj, vi) ||
//		!this->IsBetween(vl, vi, vj)) {
//		int size = (int)tour.size();
//		tour.reverse_order(0, size);
//	}
//
//	result.add_element(v);
//
//	data::clist<string> subtour_vl_vj =
//		this->GetReversedSubtour(vl, vj);
//	this->AddSubtour(result, subtour_vl_vj);
//
//	data::clist<string> subtour_vjplus1_vkminus1 =
//		this->GetSubtour(vjplus1, vkminus1);
//	this->AddSubtour(result, subtour_vjplus1_vkminus1);
//
//	data::clist<string> subtour_viplus1_vlminus1 =
//		this->GetReversedSubtour(viplus1, vlminus1);
//	this->AddSubtour(result, subtour_viplus1_vlminus1);
//
//	data::clist<string> subtour_vk_vi =
//		this->GetSubtour(vk, vi);
//	this->AddSubtour(result, subtour_vk_vi);
//
//	tour = result;
//}

double Tour::CalcDistance(pNode first, pNode second) {
	double xi = first->X;
	double yi = first->Y;
	double xj = second->X;
	double yj = second->Y;

	double xx = ( (xi - xj) * (xi - xj) );
	double yy = ( (yi - yj) * (yi - yj) );
	double d = sqrt(xx + yy);

	return d;
}

double Tour::TotalDistance() {
	double totalDistance = 0.0;
	int tourLen = this->Length();
	if (tourLen >= 2) {
		pNode first = this->nodes[0];
		pNode second;
		for (int i=1; i<tourLen; i++) {
			second = this->nodes[i];
			totalDistance += this->CalcDistance(first, second);
			first = second;
		}
		second = this->nodes[0];
		totalDistance += this->CalcDistance(first, second);
	}
	return totalDistance;
}

list<pNode> Tour::GetNodesByDistanceFrom(pNode referenceNode) {
	list<pNode> orderedNodes;

	return orderedNodes;
}

void Tour::BuildNeighborhoods(int size) {


}

string Tour::ToString() {
	string result = "empty tour!";
	int size = this->nodes.size();
	if (size > 0) {
		result = "";
		for (int i=0; i<size; i++) {
			result.append(this->nodes[i]->ToString() + " => ");
		}
		result.append(this->nodes[0]->ToString());
	}
	return result;
}

string Tour::TourToString(data::clist<pNode> &tourToPrint) {
	string result = "empty tour!";
	int size = tourToPrint.size();
	if (size > 0) {
		result = "";
		for (int i=0; i<size; i++) {
			result.append(tourToPrint[i]->ToString() + " => ");
		}
		result.append(tourToPrint[0]->ToString());
	}
	return result;
}

} /* namespace Genius */
