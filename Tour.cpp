#include "Tour.h"

namespace Genius {

static bool CompareNodes(const pNode first, const int second) {
	return first->Id == second;
}

pNode referenceNode = NULL;
struct NodeSorterByDistanceFromReferenceNode
{
    inline bool operator() (const pNode& node1, const pNode& node2)
    {
    	return (node1->DistanceFrom(referenceNode) < node2->DistanceFrom(referenceNode));
    }
};

//pNode referenceNode;
//bool CompareNodesByDistance (const pNode first, const int second) {
//	if (referenceNode )
//
//}

Tour::Tour(pInstance instance) : neighborhoods(), nodes() {
	this->Id = 0;
	this->instance = instance;
	this->NeighborhoodSize = INF;

	this->neighborhoods = new Neighborhoods();
	this->InitNeighborhoods();

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
	return ( this->nodes.f_find(node->Id, &CompareNodes) != NULL );
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




//double Tour::CalcSubtourDistance(pNode from, pNode to) {
//	double subtourDistance = 0;
//	double dist;
//
//	cout << "subtour ("<< from->Id << "=>" << to->Id << "): ";
//
//	if (from->Id != to->Id)
//	{
//		this->GoTo(from);
//		pNode current = this->Current();
//		this->Next();
//		pNode next = this->Next();
//
//		while (next->Id != to->Id) {
//			dist = current->DistanceFrom(next);
//			subtourDistance += dist;
//			cout << current->Id << " ==[" << dist << "]==> ";
//			current = next;
//			next = this->Next();
//		}
//		dist = current->DistanceFrom(next);
//		subtourDistance += dist;
//		cout << current->Id << " ==[" << dist << "]==> " << next->Id << " ";
//		this->ResetIterator();
//	}
//
//	cout << "= +" << subtourDistance << endl;
//	return subtourDistance;
//}
//
//double Tour::CalcReversedSubtourDistance(pNode from, pNode to) {
//	double subtourDistance = 0;
//	double dist;
//
//	cout << "rev subtour ("<< from->Id << "=>" << to->Id << "): ";
//
//	if (from->Id != to->Id)
//	{
//		this->GoTo(from);
//		pNode current = this->Current();
//		pNode previous = this->Previous();
//
//		while (previous->Id != to->Id) {
//			dist = current->DistanceFrom(previous);
//			subtourDistance += dist;
//			cout << current->Id << " ==[" << dist << "]==> ";
//			current = previous;
//			previous = this->Previous();
//		}
//		dist = current->DistanceFrom(previous);
//		subtourDistance += dist;
//		cout << current->Id << " ==[" << dist << "]==> " << previous->Id << " ";
//		this->ResetIterator();
//	}
//
//	cout << "= +" << subtourDistance << endl;
//	return subtourDistance;
//}

bool Tour::CheckInsertTypeIConditions(pNode vi, pNode vj, pNode vk) {
	if ((vi->Id != vj->Id) &&
		(vk->Id != vi->Id) &&
		(vk->Id != vj->Id) &&
		this->IsBetween(vk, vj, vi)) {
		return true;
	}
	return false;
}

bool Tour::CheckInsertTypeIIConditions(pNode vi, pNode vj, pNode vk, pNode vl) {
	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vlminus1 = this->Previous(vl);

	if ((vk->Id != vj->Id) &&
		(vk->Id != vjplus1->Id) &&
		(vl->Id != vi->Id) &&
		(vl->Id != viplus1->Id) &&
		this->IsBetween(vk, vj, vi) &&
		this->IsBetween(vl, vi, vj) ) {
		return true;
	}
	return false;
}

double Tour::EvaluateInsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
	assert(vi->Id != vj->Id);
	assert(vk->Id != vi->Id);
	assert(vk->Id != vj->Id);

	if (this->IsBetween(vk, vj, vi)) {

		pNode viplus1 = this->Next(vi);
		pNode vjplus1 = this->Next(vj);
		pNode vkplus1 = this->Next(vk);

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

	assert(vk->Id != vj->Id);
	assert(vk->Id != vjplus1->Id);
	assert(vl->Id != vi->Id);
	assert(vl->Id != viplus1->Id);
	if (this->IsBetween(vk, vj, vi) &&
		this->IsBetween(vl, vi, vj)) {

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



//double Tour::EvaluateReversedInsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
//	double tourDistance = 0;
//	double dist = 0;
////	bool tourHasBeenReversed = false;
//	cout << endl;
//
//	assert(vk->Id != vi->Id);
//	assert(vk->Id != vj->Id);
//
//	if (!this->IsBetween(vk, vj, vi)) {
//		//cout << "tour reversed!" << endl;
//		//this->Reverse();
//		//tourHasBeenReversed = true;
//
//		return INF_DISTANCE;
//	}
//
//	pNode viplus1 = this->Next(vi);
//	pNode vjplus1 = this->Next(vj);
//	pNode vkplus1 = this->Next(vk);
//
//	dist = v->DistanceFrom(vj);
//	tourDistance += dist;
//	cout << v->Id << "->" << vj->Id << " = +" << dist << endl;
//
//	dist = this->CalcReversedSubtourDistance(vj, viplus1);
//	tourDistance += dist;
////	cout << vj->Id << "->...->" << viplus1->Id << " = +" << dist << endl;
//
//	dist = viplus1->DistanceFrom(vk);
//	tourDistance += dist;
//	cout << viplus1->Id << "->" << vk->Id << " = +" << dist << endl;
//
//	dist = this->CalcReversedSubtourDistance(vk, vjplus1);
//	tourDistance += dist;
////	cout << vk->Id << "->...->" << vjplus1->Id << " = +" << dist << endl;
//
//	dist = vjplus1->DistanceFrom(vkplus1);
//	tourDistance += dist;
//	cout << vjplus1->Id << "->" << vkplus1->Id << " = +" << dist << endl;
//
//	dist = this->CalcReversedSubtourDistance(vkplus1, vi);
//	tourDistance += dist;
////	cout << vkplus1->Id << "->...->" << vi->Id << " = +" << dist << endl;
//
//	dist = vi->DistanceFrom(v);
//	tourDistance += dist;
//	cout << vi->Id << "->" << v->Id << " = +" << dist << endl;
//
//	cout << "TOTAL = " << tourDistance << endl;
//
////	if (tourHasBeenReversed) {
////		this->Reverse();
////	}
//	this->ResetIterator();
//
//	return tourDistance;
//}


//double Tour::EvaluateInsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl);

void Tour::InsertTypeI(pNode v, pNode vi, pNode vj, pNode vk) {
	data::clist<pNode> result;

	assert(vk->Id != vi->Id);
	assert(vk->Id != vj->Id);

	if (!this->IsBetween(vk, vj, vi)) {
		this->Reverse();
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

void Tour::InsertTypeII(pNode v, pNode vi, pNode vj, pNode vk, pNode vl) {
	data::clist<pNode> result;

	pNode viplus1 = this->Next(vi);
	pNode vjplus1 = this->Next(vj);
	pNode vkminus1 = this->Previous(vk);
	pNode vlminus1 = this->Previous(vl);

	assert(vk->Id != vj->Id);
	assert(vk->Id != vjplus1->Id);
	assert(vl->Id != vi->Id);
	assert(vl->Id != viplus1->Id);

	if (!this->IsBetween(vk, vj, vi) ||
		!this->IsBetween(vl, vi, vj)) {
		this->nodes.reverse_order();
	}

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

void SetMaxNeighborhoodSize(int size) {

}

pNodeVector Tour::GetNeighborhood(pNode node) {
//	return this->neighborhoods->at(node->Id);
return NULL;
}

void Tour::UpdateNeighborhoods() {
//	for (int n=0; n<this->instance->Size(); n++) {
//
//		referenceNode =
//			this->instance->GetNode(n);
//
//		pNodeVector allNodes =
//			this->neighborhoods->at(referenceNode->Id);
//
//		sort(allNodes->begin(), allNodes->end(),
//			NodeSorterByDistanceFromReferenceNode());
//	}
}

void Tour::InitNeighborhoods() {
//	for (int n=0; n<this->instance->Size(); n++) {
//		int nodeId = this->instance->GetNode(n)->Id;
//		this->neighborhoods->at(nodeId) = new NodeVector();
//		for (int nn=0; nn<this->instance->Size(); nn++) {
//			this->neighborhoods->at(nodeId)->push_back(this->instance->GetNode(nn));
//		}
//	}
}

void Tour::PrintNeighborhoods() {
//	cout << endl;
//	cout << "Neighborhoods for tour " << this->Id
//		 << "(p=" << this->NeighborhoodSize << ")" << endl;
//
//	for (int n=0; n<this->instance->Size(); n++) {
//		pNode refNode = this->instance->GetNode(n);
//		cout << refNode->Id << " ]";
//		for (int nn=0; nn<this->instance->Size(); nn++) {
//			pNode neighbNode = this->neighborhoods->at(refNode->Id)->at(nn);
//			cout << "> " << neighbNode->Id
//				 << "(" << refNode->DistanceFrom(neighbNode) << ")";
//		}
//		cout << endl;
//	}
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
