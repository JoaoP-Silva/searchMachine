#include "test_searchEngine.h"

void testSearchEngine::testConstructor(){
    searchEngine a;
    assert(a.alreadyMadeReverseIdx() == false);
    cout << "Test constructor : OK\n";
}

void testSearchEngine::testNormalize(){
    string t = "aÁáÀàÃãÂâÉéÈèÊêÍíÌìÎîÓóÒòÕõÔôÚúÙùÛûÇçÜüÄäÖöËëÏï";
    searchEngine a;
    string* r = a.normalize(t);
    assert(*r == "aaaaaaaaaeeeeeeiiiiiioooooooouuuuuuccuuaaooeeii");
    delete r;
    cout << "Test normalize : OK\n";
}

void testSearchEngine::testInsertItem(){
    string i = "teste";
    string f = "arquivo";
    searchEngine a;
    a.insertItem(i, f);
    assert(a.reverseIdx[i][f] == 1);
    a.insertItem(i, f);
    assert(a.reverseIdx[i][f] == 2);
    cout << "Test insertItem : OK\n";
}

void testSearchEngine::testAlreadyMadeReverseIdx(){
    searchEngine a;
    assert(a.alreadyMadeReverseIdx() == false);
    a.madeReverseIdx = true;
    assert(a.alreadyMadeReverseIdx() == true);
    cout << "Test madeReverseIdx : OK\n";
}

void testSearchEngine::testQuery(){
    string f1 = "teste1"; 
    string f2 = "teste2";
    string word =  "banana";

    vector<string> a;
    a.push_back(f1);
    a.push_back(f2);

    searchEngine s;
    s.insertItem(word, f1);
    s.insertItem(word, f2);  

    vector<string> res;
    set<string> q = {"banana"};
    s.query(q, res);
    assert(res == a);
    cout << "Test Query : OK\n";
}

void testSearchEngine::testGenReverseIdx(){
    searchEngine a;
    a.genReverseIdx();
    assert(a.reverseIdx["teste"]["teste1.txt"] == 1);
    assert(a.reverseIdx["um"]["teste1.txt"] == 1);
    assert(a.reverseIdx["teste"]["teste2.txt"] == 2);
}

int main(){
    testSearchEngine tester;
    tester.testConstructor();
    tester.testNormalize();
    tester.testInsertItem();
    tester.testAlreadyMadeReverseIdx();
    tester.testQuery();
    //tester.testGenReverseIdx();
}