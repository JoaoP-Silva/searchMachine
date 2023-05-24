#include "searchEngine.h"

using namespace std;

searchEngine::searchEngine(){
    madeReverseIdx = false;
}

bool searchEngine::alreadyMadeReverseIdx(){
    return this->madeReverseIdx;
}

vector<string>* searchEngine::filePaths(){
    string path = filesystem::current_path();
    path += "/../documentos";
    vector<string>* documentsPaths = new vector<string>;

    for(auto& it : filesystem::directory_iterator(path)){
        if(it.path().filename() != ".gitignore"){
            documentsPaths->push_back(it.path());
        }
    }
    return documentsPaths;
}

void searchEngine::genReverseIdx(){
    vector<string>* filePaths = searchEngine::filePaths();
    for(int i = 0; i < filePaths->size(); i++){
        //Open each path in filePaths
        fstream f((*filePaths)[i], fstream::in);
        if(f.is_open()){
            while(!f.eof()){
                string word;
                f >> word;
                searchEngine::normalize(word);
            }
        }
    }
}