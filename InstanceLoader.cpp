#include "InstanceLoader.h"

namespace Genius {

InstanceLoader::InstanceLoader() {
}

InstanceLoader::~InstanceLoader() {
}

pInstance InstanceLoader::LoadFromFile(string file) {

	pInstance instance = new Instance();
	int n;

	char buf[3000];
	FILE* tsp_file = fopen(file.c_str(), "r");
	assert(tsp_file != NULL);

    fscanf(tsp_file,"%s", buf);
    while ( strcmp("NODE_COORD_SECTION", buf) != 0 ) {
    	if ( strcmp("DIMENSION", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	else if ( strcmp("DIMENSION:", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	buf[0]=0;
    	fscanf(tsp_file,"%s", buf);
    }

    if( strcmp("NODE_COORD_SECTION", buf) == 0 ) {
    	int id;
    	double x;
    	double y;
    	for (int i = 0 ; i < n ; i++ ) {
    		fscanf(tsp_file, "%d %lf %lf", &id, &x, &y);
    		instance->Add(new Node(id, x, y));
    	}
    }
	return instance;
}

} /* namespace Genius */
