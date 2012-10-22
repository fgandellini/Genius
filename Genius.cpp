/*
 * Genius.cpp
 *
 *  Created on: 19/ott/2012
 *      Author: fede
 */

#include "Genius.h"

namespace Genius {

Genius::Genius() : tour() {

}

Genius::~Genius() {
}

void Genius::GoTo(string s) {
	tour.index.set_to_begin();
	tour.h_get_element(tour.find(s));
}

string Genius::GetNext(string previous) {
	this->GoTo(previous);
	tour.next_element();
	string next = tour.next_element();
	tour.index.set_to_begin();
	return next;
}

string Genius::GetPrev(string previous) {
	this->GoTo(previous);
	string prev = tour.previous_element();
	tour.index.set_to_begin();
	return prev;
}

data::clist<string> Genius::GetSubtour(string from, string to) {
	data::clist<string> subtour;

	this->GoTo(from);
	tour.next_element();
	string current = from;
	while (current.compare(to) != 0) {
		subtour.add_element(current);
		current = tour.next_element();
	}
	subtour.add_element(current);
	tour.index.set_to_begin();

	return subtour;
}

data::clist<string> Genius::GetReversedSubtour(string from, string to) {
	data::clist<string> subtour;

	this->GoTo(to);
	string current = to;
	while (current.compare(from) != 0) {
		subtour.add_element(current);
		current = tour.previous_element();
	}
	subtour.add_element(current);
	tour.index.set_to_begin();

	return subtour;
}

void Genius::AddSubtour(data::clist<string> &result, data::clist<string> subtour) {
	int subtourSize = (int)subtour.size();
	for (int i=0; i<subtourSize; i++) {
		result.add_element(subtour[i]);
	}
}

void Genius::InsertTypeI(string v, string vi, string vj, string vk) {
	data::clist<string> result;
	string current = "";

	assert(vk.compare(vi) != 0);
	assert(vk.compare(vj) != 0);

	if (!this->IsBetween(vk, vj, vi)) {
		int size = (int)tour.size();
		tour.reverse_order(0, size);
	}

	string viplus1 = this->GetNext(vi);
	string vjplus1 = this->GetNext(vj);
	string vkplus1 = this->GetNext(vk);

	result.add_element(v);

	data::clist<string> subtour_viplus1_vj =
		this->GetReversedSubtour(viplus1, vj);
	this->AddSubtour(result, subtour_viplus1_vj);

	data::clist<string> subtour_vjplus1_vk =
		this->GetReversedSubtour(vjplus1, vk);
	this->AddSubtour(result, subtour_vjplus1_vk);

	data::clist<string> subtour_vkplus1_vi =
		this->GetSubtour(vkplus1, vi);
	this->AddSubtour(result, subtour_vkplus1_vi);

	tour = result;
}

void Genius::InsertTypeII(string v, string vi, string vj, string vk, string vl) {
	data::clist<string> result;
	string current = "";

	string viplus1 = this->GetNext(vi);
	string vjplus1 = this->GetNext(vj);
	string vkminus1 = this->GetPrev(vk);
	string vlminus1 = this->GetPrev(vl);

	assert(vk.compare(vj) != 0);
	assert(vk.compare(vjplus1) != 0);
	assert(vl.compare(vi) != 0);
	assert(vl.compare(viplus1) != 0);

	if (!this->IsBetween(vk, vj, vi) ||
		!this->IsBetween(vl, vi, vj)) {
		int size = (int)tour.size();
		tour.reverse_order(0, size);
	}

	result.add_element(v);

	data::clist<string> subtour_vl_vj =
		this->GetReversedSubtour(vl, vj);
	this->AddSubtour(result, subtour_vl_vj);

	data::clist<string> subtour_vjplus1_vkminus1 =
		this->GetSubtour(vjplus1, vkminus1);
	this->AddSubtour(result, subtour_vjplus1_vkminus1);

	data::clist<string> subtour_viplus1_vlminus1 =
		this->GetReversedSubtour(viplus1, vlminus1);
	this->AddSubtour(result, subtour_viplus1_vlminus1);

	data::clist<string> subtour_vk_vi =
		this->GetSubtour(vk, vi);
	this->AddSubtour(result, subtour_vk_vi);

	tour = result;
}

int Genius::FindIndex(string s) {
    tour.index.set_to_begin();
    for (int i = 0; i < (int)tour.size(); i++) {
    	if (tour.next_element().compare(s) == 0) {
    		tour.index.set_to_begin();
    		return i;
    	}
    }
    tour.index.set_to_begin();
    return -1;
}

bool Genius::IsBetween(string x, string from, string to) {
	tour.index.set_to_begin();

    if (x.compare(from) == 0) { // found!
    	return true;
    }

    if (x.compare(to) == 0) { // found!
    	return true;
    }

    int fromIndex = this->FindIndex(from);
    string current = tour.h_get_element(fromIndex);
    while(current.compare(to) != 0) {
    	if (current.compare(x) == 0) { // found!
    		tour.index.set_to_begin();
    		return true;
    	}
    	current = tour.next_element();
    }

    tour.index.set_to_begin();
    return false;
}

string Genius::TourToString() {
	string result = "empty tour!";
	int size = tour.size();
	if (size > 0) {
		result = "";
		for (int i=0; i<size; i++) {
			result.append(tour[i] + " => ");
		}
		result.append(tour[0]);
	}
	return result;
}

string Genius::TourToString(data::clist<string> &tourToPrint) {
	string result = "empty tour!";
	int size = tourToPrint.size();
	if (size > 0) {
		result = "";
		for (int i=0; i<size; i++) {
			result.append(tourToPrint[i] + " => ");
		}
		result.append(tourToPrint[0]);
	}
	return result;
}

} /* namespace Genius */
