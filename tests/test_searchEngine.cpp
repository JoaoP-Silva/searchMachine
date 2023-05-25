#include "test_searchEngine.h"

void testSearchEngine::testConstructor(){
    searchEngine a;
    assert(a.alreadyMadeReverseIdx() == false);
    cout << "Test constructor : OK\n";
}

void testSearchEngine::testNormalize(){
    wstring t = L"aÁáÀàÃãÂâÉéÈèÊêÍíÌìÎîÓóÒòÕõÔôÚúÙùÛûÇçÜüÄäÖöËëÏï";
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
int main(){
    testSearchEngine tester;
    tester.testConstructor();
    tester.testNormalize();
    tester.testInsertItem();
    tester.testAlreadyMadeReverseIdx();
}