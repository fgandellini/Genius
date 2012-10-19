#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"

namespace Genius {

class Genius {
public:
	data::clist<string> tour;

	Genius();
	virtual ~Genius();

	void InsertTypeI(string v, int i, int j, int k);
	void InsertTypeIReversed(string v, int i, int j, int k);

	void InsertTypeI_old(string v, string vi, string vj, string vk);

	string TourToString();

	void GoTo(string s);
	string GetNext(string previous);
	void AddSubtour(data::clist<string> &result, string from, string to);
	void AddReversedSubtour(data::clist<string> &result, string from, string to);

	void InsertTypeI(string v, string vi, string vj, string vk);

	int FindIndex(string s);
	bool IsBetween(string x, string from, string to);
};

} /* namespace Genius */
#endif /* GENIUS_H_ */
