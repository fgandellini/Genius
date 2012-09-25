#include <vector>
#include <cstring>
using namespace std;

#ifndef NULL
	#define NULL 0
#endif

#define SAFE_DELETE(x) if (x != NULL) { delete x; }
#define SAFE_DELETE_VECTOR(v) if (v != NULL) { for (unsigned int i=0; i<v->size(); ++i) { SAFE_DELETE(v->at(i)); } SAFE_DELETE(v); }

