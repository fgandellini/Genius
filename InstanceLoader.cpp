#include "InstanceLoader.h"

namespace Genius {

InstanceLoader::InstanceLoader() {
}

InstanceLoader::~InstanceLoader() {
}

pInstance InstanceLoader::LoadFromFile(string file) {
	pTspNodeParser parser = new TspNodeParser();
	pInstance instance = InstanceLoader::LoadFromFile(file, parser);
	SAFE_DELETE(parser);
	return instance;
}

pInstance InstanceLoader::LoadFromFile(string file, pNodeParser nodeParser) {
	pInstance instance = new Instance();
	instance->Type = nodeParser->Type;
	instance->Name = InstanceLoader::GetFilename(file);

	int n;
	int P = 0, k = 0;

	char buf[3000];
	FILE* tsp_file = fopen(file.c_str(), "r");
	assert(tsp_file != NULL);

    fscanf(tsp_file,"%s", buf);
    while ( strcmp("NODE_COORD_SECTION", buf) != 0 ) {
    	if ( strcmp("DIMENSION", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	else if ( strcmp("DIMENSION:", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	else if ( (instance->Type == HTSP) && (strcmp("P:", buf) == 0) ) { fscanf(tsp_file, "%d", &P); }
    	else if ( (instance->Type == HTSP) && (strcmp("K:", buf) == 0) ) { fscanf(tsp_file, "%d", &k); }
    	buf[0]=0;
    	fscanf(tsp_file,"%s", buf);
    }

    if( strcmp("NODE_COORD_SECTION", buf) == 0 ) {
    	for (int i = 0 ; i < n ; i++ ) {
    		instance->Add(nodeParser->parseNode(tsp_file));
    	}
    }

    if (instance->Type == HTSP) {
    	instance->P = P;
    	instance->k = k;
    }

	return instance;
}

pTour InstanceLoader::LoadOptTourFromFile(pInstance instance, string file) {
	pTour optTour = new Tour(instance);

	int n;

	char buf[3000];
	FILE* tsp_file = fopen(file.c_str(), "r");
	assert(tsp_file != NULL);

    fscanf(tsp_file,"%s", buf);
    while ( strcmp("TOUR_SECTION", buf) != 0 ) {
    	if ( strcmp("DIMENSION", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	else if ( strcmp("DIMENSION:", buf) == 0 ) { fscanf(tsp_file, "%d", &n); }
    	buf[0]=0;
    	fscanf(tsp_file,"%s", buf);
    }

    if( strcmp("TOUR_SECTION", buf) == 0 ) {
    	int id;
    	for (int i = 0 ; i < n ; i++ ) {
    		fscanf(tsp_file, "%d", &id);
    		optTour->Append(instance->GetNodeById(id));
    	}
    }
    return optTour;
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
