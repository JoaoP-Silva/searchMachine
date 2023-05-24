#include "test_searchEngine.h"

void testSearchEngine::testConstructor(){
    searchEngine a;
    assert(a.alreadyMadeReverseIdx() == false);
    cout << "Test constructor : OK\n";
}

int main(){
    testSearchEngine tester;
    tester.testConstructor();

}