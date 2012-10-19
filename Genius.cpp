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

void Genius::InsertTypeIReversed(string v, int i, int j, int k) {
	data::clist<string> result;
	tour.h_first_element();

	tour.h_get_element(i);
	tour.previous_element();
	string iplus1 = tour.previous_element();
	tour.h_first_element();

	tour.h_get_element(j);
	tour.previous_element();
	string jplus1 = tour.previous_element();
	tour.h_first_element();

	tour.h_get_element(k);
	tour.previous_element();
	string kplus1 = tour.previous_element();
	tour.h_first_element();

	// v
	result.add_element(v);

	// j => i+1
	string current = tour.h_get_element(j);
	while(current.compare(iplus1) != 0) {
		result.add_element(current);
		current = tour.next_element();
	}
	result.add_element(iplus1);
	tour.h_first_element();

	// k => j+1
	current = tour.h_get_element(k);
	while(current.compare(jplus1) != 0) {
		result.add_element(current);
		current = tour.next_element();
	}
	result.add_element(jplus1);
	tour.h_first_element();

	// k+1 => i
	string element_i = tour.get_element(i);
	tour.h_get_element(k);
	tour.previous_element();
	current = tour.previous_element();
	while(current.compare(element_i) != 0) {
		result.add_element(current);
		current = tour.previous_element();
	}
	result.add_element(element_i);
	tour.h_first_element();

	tour = result;
}

void Genius::GoTo(string s) {
	tour.index.set_to_begin();
	tour.h_get_element(tour.find(s));
}

string Genius::GetNext(string previous) {
	this->GoTo(previous);
	string next = tour.next_element();
	tour.index.set_to_begin();
	return next;
}

void Genius::AddSubtour(data::clist<string> &result, string from, string to) {
	this->GoTo(from);
	string current = from;
	while (current.compare(to) != 0) {
		result.add_element(current);
		current = tour.next_element();
	}
	result.add_element(tour.next_element());
	tour.index.set_to_begin();
}

void Genius::AddReversedSubtour(data::clist<string> &result, string from, string to) {
	this->GoTo(from);
	string current = from;
	while (current.compare(to) != 0) {
		result.add_element(current);
		current = tour.previous_element();
	}
	result.add_element(tour.previous_element());
	tour.index.set_to_begin();
}

void Genius::InsertTypeI(string v, string vi, string vj, string vk) {
	data::clist<string> result;
	string current = "";
	if (this->IsBetween(vk, vj, vi)) {

		string viplus1 = this->GetNext(vi);
		string vjplus1 = this->GetNext(vj);
		string vkplus1 = this->GetNext(vk);

		result.add_element(v);

		this->AddReversedSubtour(result, viplus1, vj);
		this->AddReversedSubtour(result, vjplus1, vk);
		this->AddSubtour(result, vkplus1, vi);

		tour = result;
	}
}

void Genius::InsertTypeI(string v, int i, int j, int k) {
	data::clist<string> result;
	tour.h_first_element();

	tour.h_get_element(i);
	tour.next_element();
	string iplus1 = tour.next_element();
	tour.h_first_element();

	tour.h_get_element(j);
	tour.next_element();
	string jplus1 = tour.next_element();
	tour.h_first_element();

	tour.h_get_element(k);
	tour.next_element();
	string kplus1 = tour.next_element();
	tour.h_first_element();

	// v
	result.add_element(v);

	// j => i+1
	string current = tour.h_get_element(j);
	while(current.compare(iplus1) != 0) {
		result.add_element(current);
		current = tour.previous_element();
	}
	result.add_element(iplus1);
	tour.h_first_element();

	// k => j+1
	current = tour.h_get_element(k);
	while(current.compare(jplus1) != 0) {
		result.add_element(current);
		current = tour.previous_element();
	}
	result.add_element(jplus1);
	tour.h_first_element();

	// k+1 => i
	string element_i = tour.get_element(i);
	tour.h_get_element(k);
	tour.next_element();
	current = tour.next_element();
	while(current.compare(element_i) != 0) {
		result.add_element(current);
		current = tour.next_element();
	}
	result.add_element(element_i);
	tour.h_first_element();

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

void Genius::InsertTypeI_old(string v, string vi, string vj, string vk) {

	//bool reversed = false;
	//data::clist<string> result;

	int i = this->FindIndex(vi);
	int j = this->FindIndex(vj);
	int k = this->FindIndex(vk);

	assert(k != i);
	assert(k != j);

	if (this->IsBetween(vk, vj, vi)) {
		this->InsertTypeI(v, i, j, k);
	} else {
		this->InsertTypeIReversed(v, i, j, k);
	}
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

} /* namespace Genius */
