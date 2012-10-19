#define RUN_TESTS
#ifndef RUN_TESTS

#include "CommonIncludes.h"

typedef int id;

id inc(vector<id> &tour, id i) {
	return (i == ((id)tour.size()-1)) ? 0 : i+1;
}

id dec(vector<int> &tour, id i) {
	return (i == 0) ? (id)tour.size()-1 : i-1;
}

void printtour(vector<int> &tour) {
	id i=0;
	for (; i<(id)tour.size(); i++) {
		cout << tour[i] << "=>";
	}
	id last = (id)tour.size()-1;
	cout << tour[inc(tour, last)] << endl;
}

vector<int> insert(vector<int> &tour, int v, id i, id j) {

	// Tour: i => l => j => k => i
	id k = inc(tour, j);
	id kplus1 = inc(tour, k);
	// j <= k <= i

	id iplus1 = inc(tour, i);
	id jplus1 = inc(tour, j);

	vector<int> result;

	result.push_back(tour[i]);

	// k+1 => i
	for (id x=kplus1; x<=i; x=inc(tour, x)) {
		result.push_back(tour[x]);
	}

	// v
	result.push_back(v);

	// j => i+1
	for (id x=j; x<=iplus1; x=dec(tour, x)) {
		result.push_back(tour[x]);
	}

	// k => j+1
	for (id x=k; x<=jplus1; x=dec(tour, x)) {
		result.push_back(tour[x]);
	}
}

//class Node {
//public:
//	int val;
//	Node* prev;
//	Node* next;
//
//	Node(int val) { this->val = val; this->prev = NULL; this->next = NULL; }
//	~Node() { if (this->next != NULL) delete this->next; }
//};
//
//class Tour {
//public:
//	Node* head;
//	Tour() { this->head = NULL; }
//	~Tour() { if (this->head != NULL) delete this->head; }
//
//	Tour* Append(Node* n) {
//		Node* tail = this->head->prev;
//
//		n->next = head;
//		n->prev = tail;
//		tail->next = n;
//		head->prev = n;
//
//		return this;
//	}
//};

//void printtour(Node* t) {
//	Node* currentNode = t;
//	while (currentNode != NULL) {
//		cout << currentNode->val << " => ";
//		currentNode = currentNode->next;
//	}
//	cout << t->val << endl;
//}


#include "clist/clist.hpp"

data::clist<string> insert_typeI(data::clist<string> &tour, string v, int i, int j, int k) {

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

	return result;
}









int main(int argc, char** argv) {

	data::clist<string> tour;
	tour.add_element(" [1] "); // i
	tour.add_element(" [2] ");
	tour.add_element(" [3] ");
	tour.add_element(" [4] ");
	tour.add_element(" [5] ");
	tour.add_element(" [6] "); // j
	tour.add_element(" [7] ");
	tour.add_element(" [8] ");
	tour.add_element(" [9] ");
	tour.add_element(" [10] ");
	tour.add_element(" [11] "); // k
	tour.add_element(" [12] ");
	tour.add_element(" [13] ");
	tour.add_element(" [14] ");
	tour.add_element(" [15] ");
	tour.add_element(" [16] ");

	cout << tour <<endl;

	data::clist<string> new_tour = insert_typeI(tour, " [100] ", 0, 5, 10);

	cout << new_tour <<endl;

	// ----------------------------------------------------------------------------
	cout << "-- Paper Tour --------------------" << endl;

	data::clist<string> paper_tour;
	paper_tour.add_element(" [1] ");
	paper_tour.add_element(" [2] ");
	paper_tour.add_element(" [3] ");

	cout << "Paper Tour: " << paper_tour <<endl;

	data::clist<string> paper_tour_1 = insert_typeI(paper_tour, " [4] ", 0, 2, 1);
	cout << "Paper Tour (1): " << paper_tour_1 <<endl;

	data::clist<string> paper_tour_2 = insert_typeI(paper_tour_1, " [5] ", 0, 1, 2);
	cout << "Paper Tour (2): " << paper_tour_2 <<endl;










//	vector<int> tour;
//	tour.push_back(1);
//	tour.push_back(2);
//	tour.push_back(3);
//	tour.push_back(4);
//	tour.push_back(5);
//	tour.push_back(6);
	//tour.push_back(7);
	//tour.push_back(8);
	//printtour(tour);


//	int a = 0;
//	cout << "INC" << endl;
//	for (id i=0; i<tour.size(); i=inc(tour, i))
//	{
//		a++;
//		cout << a << " => tour[" << i << "] = " << tour[i] << endl;
//		if (a == 10) break;
//	}
//
//	a = 0;
//	cout << "DEC" << endl;
//	for (id i=0; i<tour.size(); i=dec(tour, i))
//	{
//		a++;
//		cout << a << " => tour[" << i << "] = " << tour[i] << endl;
//		if (a == 10) break;
//	}

	return EXIT_SUCCESS;
}





#else
#include <CppUTest/CommandLineTestRunner.h>
int main(int argc, char** argv) {
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
#endif
