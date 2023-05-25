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

int main(){
    testSearchEngine tester;
    tester.testConstructor();
    tester.testNormalize();
}