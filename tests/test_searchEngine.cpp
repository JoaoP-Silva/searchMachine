#include "searchEngine.h"
#include <cassert>

void testConstructor(){
    searchEngine a;
    assert(a.alreadyMadeReverseIdx() == false);
    cout << "Test constructor : OK\n";
}