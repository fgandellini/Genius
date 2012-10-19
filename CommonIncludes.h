#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <assert.h>
#include "clist/clist.hpp"

using namespace std;

#ifndef NULL
	#define NULL 0
#endif

#define SAFE_DELETE(x) if (x != NULL) { delete x; }
#define SAFE_DELETE_VECTOR(v) if (v != NULL) { for (unsigned int SAFE_DELETE_VECTOR_i=0; SAFE_DELETE_VECTOR_i<v->size(); ++SAFE_DELETE_VECTOR_i) { SAFE_DELETE(v->at(SAFE_DELETE_VECTOR_i)); } SAFE_DELETE(v); }




