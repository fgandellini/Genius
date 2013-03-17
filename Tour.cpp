#include "Tour.h"

namespace Genius {

static bool CompareNodes(const pNode first, const int second) {
	return first->Id == second;
}

pNode referenceNode = NULL;
struct NodeSorterByDistanceFromReferenceNode {
    bool operator ()(pNode const& node1, pNode const& node2) const {
    	double distanceFromNode1 = referenceNode->DistanceFrom(node1);
    	double distanceFromNode2 = referenceNode->DistanceFrom(node2);
    	return (distanceFromNode1 < distanceFromNode2);
    }
};

Tour::Tour(pInstance instance) : nodes() {
	this->Id = 0;
	this->instance = instance;

	this->neighborhoods = new Neighborhoods();
	this->InitNeighborhoods();
	this->UpdateNeighborhoods();
}

Tour::~Tour() {
	this->DeleteNeighborhoods();
}

pTour Tour::Clone() {
	pTour clonedTour = new Tour(this->instance);

	for(int i=0; i<this->Length(); i++) {
		clonedTour->Append(this->Get(i));
	}

	return clonedTour;
}

pInstance Tour::GetInstance() {
	return this->instance;
}

int Tour::Length() const {
	return (int)this->nodes.size();
}

void Tour::Append(pNode node) {
	this->nodes.add_element(node);
	this->UpdateNeighborhoods();
}

void Tour::ResetIterator() {
	this->nodes.index.set_to_begin();
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

bool Tour::Contains(pNode node) {
	return ( this->nodes.f_find(node->Id, &CompareNodes) != -1 );
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

pNode Tour::Get(int position) {
	return this->nodes.get_element(position);
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

void Tour::Reverse() {
	this->nodes.reverse_order();
}

data::clist<pNode> Tour::GetSubtour(pNode from, pNode to) {
	data::clist<pNode> subtour;

	this->GoTo(from);
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

bool Tour::CheckInsertTypeIConditions(pNode v, pNode vi, pNode vj, pNode vk, bool useAssert) {
	if (useAssert) {
		assert(vi->Id != vj->Id);
		assert(vk->Id != vi->Id);
		assert(vk->Id != vj->Id);
		assert(this->IsBetween(vk, vj, vi));
	} else {
		return ((vi->Id != vj->Id) &&
				 (vk->Id != vi->Id) &&
				 (vk->Id != vj->Id) &&
				 this->IsBetween(vk, vj, vi));
	}
	return true;
}

bool Tour::CheckInsertTypeIIConditions(pNode v, pNode vi, pNode vj, pNode vk, pNode vl, bool useAssert) {
	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);

	if (useAssert) {
		assert(vk->Id != vj->Id);
		assert(vk->Id != vjplus1->Id);
		assert(vl->Id != vi->Id);
		assert(vl->Id != viplus1->Id);
		assert(this->IsBetween(vk, vj, vi) &&
			   this->IsBetween(vl, vi, vj) );
	} else {
		return ((vk->Id != vj->Id) &&
				 (vk->Id != vjplus1->Id) &&
				 (vl->Id != vi->Id) &&
				 (vl->Id != viplus1->Id) &&
				 this->IsBetween(vk, vj, vi) &&
				 this->IsBetween(vl, vi, vj) );
	}
	return true;
}

bool Tour::CheckRemoveTypeIConditions(pNode vi, pNode vj, pNode vk, bool useAssert) {
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	if (useAssert) {
		assert(vi->Id != vj->Id);
		assert(vi->Id != vk->Id);
		assert(vi->Id != vkplus1->Id);
		assert(vi->Id != vjplus1->Id);
		assert(vj->Id != vk->Id);
		assert(this->IsBetween(vk, viplus1, vjminus1));
	} else {
		return ((vi->Id != vj->Id) &&
				 (vi->Id != vk->Id) &&
				 (vi->Id != vkplus1->Id) &&
				 (vi->Id != vjplus1->Id) &&
				 (vj->Id != vk->Id) &&
				 this->IsBetween(vk, viplus1, vjminus1) );
	}
	return true;
}

bool Tour::CheckRemoveTypeIIConditions(pNode vi, pNode vj, pNode vk, pNode vl, bool useAssert) {
	pNode viminus1 = this->Previous(vi);
	pNode viminus2 = this->Previous(viminus1);
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vkplus1 = this->Next(vk);
	pNode vlplus1 = this->Next(vl);

	if (useAssert) {
		assert(vi->Id != vj->Id);
		assert(vi->Id != vk->Id);
		assert(vi->Id != vl->Id);
		assert(vi->Id != vjminus1->Id);
		assert(vi->Id != vkplus1->Id);
		assert(vi->Id != vlplus1->Id);
		assert(vj->Id != vk->Id);
		assert(vj->Id != vl->Id);
		assert(vj->Id != viminus1->Id);
		assert(vk->Id != vl->Id);
		assert(vk->Id != vjminus1->Id);
		assert(vk->Id != viplus1->Id);
		assert(vk->Id != vlplus1->Id);
		assert(vl->Id != vjplus1->Id);
		assert(viminus1->Id != vlplus1->Id);
		assert(vkminus1->Id != vlplus1->Id);
		assert(vjminus1->Id != vkplus1->Id);
		assert(this->IsBetween(vk, vjplus1, viminus2) &&
			   this->IsBetween(vl, vj, vkminus1)	   );
	} else {
		return ((vi->Id != vj->Id) &&
				 (vi->Id != vk->Id) &&
				 (vi->Id != vl->Id) &&
				 (vi->Id != vjminus1->Id) &&
				 (vi->Id != vkplus1->Id) &&
				 (vi->Id != vlplus1->Id) &&
				 (vj->Id != vk->Id) &&
				 (vj->Id != vl->Id) &&
				 (vj->Id != viminus1->Id) &&
				 (vk->Id != vl->Id) &&
				 (vk->Id != vjminus1->Id) &&
				 (vk->Id != viplus1->Id) &&
				 (vk->Id != vlplus1->Id) &&
				 (vl->Id != vjplus1->Id) &&
				 (viminus1->Id != vlplus1->Id) &&
				 (vkminus1->Id != vlplus1->Id) &&
				 (vjminus1->Id != vkplus1->Id) &&
				 this->IsBetween(vk, vjplus1, viminus2) &&
				 this->IsBetween(vl, vj, vkminus1));
	}
	return true;
}


double Tour::EvaluateInsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	if (this->CheckInsertTypeIConditions(v, vi, vj, vk, true)) {

		// Il costo di inserimento è
		// il costo del vecchio tour + gli archi da inserire - gli archi da rimuovere
		double tourDistance = this->TotalDistance();

		// costo degli archi da rimuovere
		tourDistance -= vi->DistanceFrom(viplus1);
		tourDistance -= vj->DistanceFrom(vjplus1);
		tourDistance -= vk->DistanceFrom(vkplus1);

		// costo degli archi da aggiungere
		tourDistance += vi->DistanceFrom(v);
		tourDistance += v->DistanceFrom(vj);
		tourDistance += viplus1->DistanceFrom(vk);
		tourDistance += vjplus1->DistanceFrom(vkplus1);

		return tourDistance;
	}
	return INF_DISTANCE;
}

double Tour::EvaluateInsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl) {
	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vlminus1 = this->Previous(vl);

	if (this->CheckInsertTypeIIConditions(v, vi, vj, vk, vl, true)) {

		// Il costo di inserimento è
		// il costo del vecchio tour + gli archi da inserire - gli archi da rimuovere
		double tourDistance = this->TotalDistance();

		// costo degli archi da rimuovere
		tourDistance -= vi->DistanceFrom(viplus1);
		tourDistance -= vlminus1->DistanceFrom(vl);
		tourDistance -= vj->DistanceFrom(vjplus1);
		tourDistance -= vkminus1->DistanceFrom(vk);

		// costo degli archi da aggiungere
		tourDistance += vi->DistanceFrom(v);
		tourDistance += v->DistanceFrom(vj);
		tourDistance += vl->DistanceFrom(vjplus1);
		tourDistance += vkminus1->DistanceFrom(vlminus1);
		tourDistance += viplus1->DistanceFrom(vk);

		return tourDistance;
	}
	return INF_DISTANCE;
}

double Tour::EvaluateRemoveTypeI(pNode vi, pNode vj, pNode vk) {
	pNode viminus1 = this->Previous(vi);
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	if (this->CheckRemoveTypeIConditions(vi, vj, vk, true)) {

		// Il costo di inserimento è
		// il costo del vecchio tour + gli archi da inserire - gli archi da rimuovere
		double tourDistance = this->TotalDistance();

		// costo degli archi da rimuovere
		tourDistance -= viminus1->DistanceFrom(vi);
		tourDistance -= vi->DistanceFrom(viplus1);
		tourDistance -= vk->DistanceFrom(vkplus1);
		tourDistance -= vj->DistanceFrom(vjplus1);

		// costo degli archi da aggiungere
		tourDistance += viminus1->DistanceFrom(vk);
		tourDistance += viplus1->DistanceFrom(vj);
		tourDistance += vkplus1->DistanceFrom(vjplus1);

		return tourDistance;
	}
	return INF_DISTANCE;
}

double Tour::EvaluateRemoveTypeII(pNode vi, pNode vj, pNode vk, pNode vl) {
	pNode viminus1 = this->Previous(vi);
	pNode viminus2 = this->Previous(viminus1);
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	//pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vkplus1 = this->Next(vk);
	pNode vlplus1 = this->Next(vl);

//	assert(vk->Id != vj->Id);
//	assert(vk->Id != vjplus1->Id);
//	assert(vl->Id != vi->Id);
//	assert(vl->Id != viplus1->Id);

	if (this->CheckRemoveTypeIIConditions(vi, vj, vk, vl, true)) {

		// Il costo di inserimento è
		// il costo del vecchio tour + gli archi da inserire - gli archi da rimuovere
		double tourDistance = this->TotalDistance();

		// costo degli archi da rimuovere
		tourDistance -= viminus1->DistanceFrom(vi);
		tourDistance -= vi->DistanceFrom(viplus1);
		tourDistance -= vjminus1->DistanceFrom(vj);
		tourDistance -= vk->DistanceFrom(vkplus1);
		tourDistance -= vl->DistanceFrom(vlplus1);

		// costo degli archi da aggiungere
		tourDistance += viminus1->DistanceFrom(vk);
		tourDistance += vlplus1->DistanceFrom(vjminus1);
		tourDistance += viplus1->DistanceFrom(vj);
		tourDistance += vl->DistanceFrom(vkplus1);

		return tourDistance;
	}
	return INF_DISTANCE;
}

void Tour::InsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
	data::clist<pNode> result;

	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	// Consistency check
	this->CheckInsertTypeIConditions(v, vi, vj, vk, true);

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

	UpdateNeighborhoods();
}

void Tour::InsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl) {
	data::clist<pNode> result;

	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vlminus1 = this->Previous(vl);

	// Consistency check
	this->CheckInsertTypeIIConditions(v, vi, vj, vk, vl, true);

	result.add_element(v);

	data::clist<pNode> subtour_vl_vj =
		this->GetReversedSubtour(vl, vj);
	this->AddSubtour(subtour_vl_vj, result);

	data::clist<pNode> subtour_vjplus1_vkminus1 =
		this->GetSubtour(vjplus1, vkminus1);
	this->AddSubtour(subtour_vjplus1_vkminus1, result);

	data::clist<pNode> subtour_viplus1_vlminus1 =
		this->GetReversedSubtour(viplus1, vlminus1);
	this->AddSubtour(subtour_viplus1_vlminus1, result);

	data::clist<pNode> subtour_vk_vi =
		this->GetSubtour(vk, vi);
	this->AddSubtour(subtour_vk_vi, result);

	this->nodes = result;

	UpdateNeighborhoods();
}

void Tour::RemoveTypeI(pNode vi, pNode vj, pNode vk) {
	data::clist<pNode> result;

	pNode viminus1 = this->Previous(vi);
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	pNode vjplus1 = this->Next(vj);
	pNode vkplus1 = this->Next(vk);

	this->CheckRemoveTypeIConditions(vi, vj, vk, true);

	//result.add_element(viminus1);
	//cout << ">> added viminus1: " << viminus1->Id << endl;

	data::clist<pNode> subtour_viplus1_vk =
		this->GetReversedSubtour(viplus1, vk);
	this->AddSubtour(subtour_viplus1_vk, result);

//	cout << ">> added subtour_viplus1_vk: " << this->TourToString(subtour_viplus1_vk) << endl;

	data::clist<pNode> subtour_vkplus1_vj =
		this->GetReversedSubtour(vkplus1, vj);
	this->AddSubtour(subtour_vkplus1_vj, result);

//	cout << ">> added subtour_vkplus1_vj: " << this->TourToString(subtour_vkplus1_vj) << endl;

	data::clist<pNode> subtour_vjplus1_viminus1 =
		this->GetSubtour(vjplus1, viminus1);
	this->AddSubtour(subtour_vjplus1_viminus1, result);

//	cout << ">> added subtour_vjplus1_viminus1: " << this->TourToString(subtour_vjplus1_viminus1) << endl;

	this->nodes = result;

	UpdateNeighborhoods();
}

void Tour::RemoveTypeII(pNode vi, pNode vj, pNode vk, pNode vl) {
	data::clist<pNode> result;

	pNode viminus1 = this->Previous(vi);
	pNode viplus1 = this->Next(vi);
	pNode vjminus1 = this->Previous(vj);
	pNode vkplus1 = this->Next(vk);
	pNode vlplus1 = this->Next(vl);

	this->CheckRemoveTypeIIConditions(vi, vj, vk, vl, true);

	DBG << endl
		<< "     viminus1=" << Utils::ToString(viminus1->Id, true) << endl
		<< "     viplus1=" << Utils::ToString(viplus1->Id, true) << endl
		<< "     vjminus1=" << Utils::ToString(vjminus1 ->Id, true) << endl
		<< "     vkplus1=" << Utils::ToString(vkplus1->Id, true) << endl
		<< "     vlplus1="  << Utils::ToString(vlplus1->Id, true) << endl;

	data::clist<pNode> subtour_vlplus1_vk =
		this->GetReversedSubtour(vlplus1, vk);
	this->AddSubtour(subtour_vlplus1_vk, result);

	data::clist<pNode> subtour_viplus1_vjminus1 =
		this->GetReversedSubtour(viplus1, vjminus1);
	this->AddSubtour(subtour_viplus1_vjminus1, result);

	data::clist<pNode> subtour_vj_vl =
		this->GetSubtour(vj, vl);
	this->AddSubtour(subtour_vj_vl, result);

	data::clist<pNode> subtour_vkplus1_viminus1 =
		this->GetSubtour(vkplus1, viminus1);
	this->AddSubtour(subtour_vkplus1_viminus1, result);

	this->nodes = result;

	UpdateNeighborhoods();
}

double Tour::TotalDistance() {
	double totalDistance = 0.0;
	int tourLen = this->Length();
	if (tourLen >= 2) {
		pNode first = this->nodes[0];
		pNode second;
		for (int i=1; i<tourLen; i++) {
			second = this->nodes[i];
			totalDistance += first->DistanceFrom(second);
			first = second;
		}
		second = this->nodes[0];
		totalDistance += first->DistanceFrom(second);
	}
	return totalDistance;
}

void Tour::InitNeighborhoods() {
	int nodesCount = this->instance->Size();
	for (int n=0; n<nodesCount; n++) {
		this->neighborhoods->push_back( new NodeVector() );
		pNodeVector vector = this->neighborhoods->at(n);
		for (int nn=0; nn<nodesCount; nn++) {
			if (n != nn) {
				//pNode node = this->instance->GetNode(nn);
				vector->push_back( NULL );
			}
		}
	}
}

void Tour::ClearNeighborhoods() {
	for (int n=0; n<this->instance->Size(); n++) {
		pNode refNode = this->instance->GetNode(n);
		pNodeVector vector = this->GetNeighborhood(refNode);
		vector->clear();
	}
}

void Tour::UpdateNeighborhoods() {
	this->ClearNeighborhoods();
	for (int n=0; n<this->instance->Size(); n++) {

		referenceNode = this->instance->GetNode(n);
		pNodeVector neighbors = this->neighborhoods->at(n);

		for (int nn=0; nn<this->Length(); nn++) {
			pNode node = this->Get(nn);
			if (referenceNode->Id != node->Id) {
				neighbors->push_back( node );
			}
		}

		sort(neighbors->begin(), neighbors->end(),
			NodeSorterByDistanceFromReferenceNode());
	}
}

pNodeVector Tour::GetNeighborhood(pNode node) {
	int index = this->instance->GetIndex(node);
	return this->neighborhoods->at(index);
}

bool Tour::IsNodeInNeighborhood(pNode node, pNodeVector neighborhood) {
	for (int n=0; n<(int)neighborhood->size(); n++) {
		if (neighborhood->at(n)->Id == node->Id) {
			return true;
		}
	}
	return false;
}

void Tour::PrintNeighborhoods() {
	cout << endl;
	cout << "Neighborhoods for tour " << this->Id
		 << endl;

	for (int n=0; n<this->instance->Size(); n++) {
		pNode refNode = this->instance->GetNode(n);
		cout << refNode->Id << " ]";
		pNodeVector vector = this->GetNeighborhood(refNode);
		for (int nn=0; nn<(int)vector->size(); nn++) {
			pNode neighbor = vector->at(nn);
			cout << "=> " << neighbor->Id
				 << "(" << refNode->DistanceFrom(neighbor) << ") ";
		}
		cout << endl;
	}
}

void Tour::DeleteNeighborhoods() {
	for (int n=0; n<(int)this->neighborhoods->size(); n++) {
		pNodeVector vector = this->neighborhoods->at(n);
		SAFE_DELETE( vector );
	}
	SAFE_DELETE(this->neighborhoods);
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

bool Tour::IsEqualTo(pTour tourToCompare) {
	pNode secondTourStartNode = tourToCompare->Get(0);

	this->GoTo(secondTourStartNode);
	do {
		pNode n1 = this->Current();
		pNode n2 = tourToCompare->Current();
		if (n1->Id != n2->Id) {
			return false;
		}
		this->Next();
		tourToCompare->Next();
	} while(tourToCompare->Current()->Id != secondTourStartNode->Id);

	return true;
}

} /* namespace Genius */
