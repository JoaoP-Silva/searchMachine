#include "searchEngine.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    searchEngine eng;
    eng.genReverseIdx();

    //Leitura da entrada real ainda a ser realizada
    set<string> q = {"ninguem"};
    vector<string> res;
    eng.query(q, res);
    for(auto& i : res){
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}