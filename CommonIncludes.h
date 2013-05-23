#include <vector>
#include <list>
#include <map>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include "Utils.h"
#include "RandomNumberGenerator.h"
#include "clist/clist.hpp"
#include "simple_svg_1.0.0.hpp"

using namespace std;
using namespace svg;

#ifndef NULL
	#define NULL 0
#endif

//#define INF 10000
#define INF_DISTANCE 10000000.0

#define SAFE_DELETE(x) if (x != NULL) { delete x; x = NULL; }
#define SAFE_DELETE_VECTOR(v) if (v != NULL) { for (unsigned int SAFE_DELETE_VECTOR_i=0; SAFE_DELETE_VECTOR_i<v->size(); ++SAFE_DELETE_VECTOR_i) { SAFE_DELETE(v->at(SAFE_DELETE_VECTOR_i)); } SAFE_DELETE(v); }

// Instance Types
#define UNKNOWN 0
#define TSP 1
#define HTSP 2

