#ifndef GENIUS_H_
#define GENIUS_H_

#include "CommonIncludes.h"

namespace Genius {

class Genius {
public:
	data::clist<string> tour;

	Genius();
	virtual ~Genius();

	string TourToString();
	string TourToString(data::clist<string> &tourToPrint);

	void GoTo(string s);
	string GetNext(string previous);
	string GetPrev(string previous);

	data::clist<string> GetSubtour(string from, string to);
	data::clist<string> GetReversedSubtour(string from, string to);
	void AddSubtour(data::clist<string> &result, data::clist<string> subtour);

	void InsertTypeI(string v, string vi, string vj, string vk);
	void InsertTypeII(string v, string vi, string vj, string vk, string vl);

	int FindIndex(string s);
	bool IsBetween(string x, string from, string to);
};

} /* namespace Genius */
#endif /* GENIUS_H_ */
