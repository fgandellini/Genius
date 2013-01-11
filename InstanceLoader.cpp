#include "InstanceLoader.h"

namespace Genius {

InstanceLoader::InstanceLoader() {
}

InstanceLoader::~InstanceLoader() {
}

pInstance InstanceLoader::LoadFromFile(string file) {

	pInstance instance = new Instance();

	instance->Name = InstanceLoader::GetFilename(file);

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

string InstanceLoader::GetFilename(string absolutePath) {
	string filename;
	size_t pos = absolutePath.find_last_of("/");
	if(pos != std::string::npos) {
		filename.assign(absolutePath.begin() + pos + 1, absolutePath.end());
	} else {
		filename = absolutePath;
	}
	return filename;
}

} /* namespace Genius */
