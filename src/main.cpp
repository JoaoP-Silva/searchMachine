#include "searchEngine.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    //Geracao do indice reverso
    searchEngine eng;
    eng.genReverseIdx();

    set<string> words;
    for(int i = 1; i < argc; i++){
        string w = argv[i];
        words.insert(w);
    }
    vector<string> res;
    eng.query(words, res);

    for(string s : res){
        cout << s << endl;
    }
    
    return 0;
}