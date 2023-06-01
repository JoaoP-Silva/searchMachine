#ifndef TEST_SEARCH_ENGINE_H
#define TEST_SEARCH_ENGINE_H

#include "searchEngine.h"
#include <cassert>

class testSearchEngine{
    public:
        void testConstructor();
        void testNormalize();
        void testInsertItem();
        void testAlreadyMadeReverseIdx();
        void testQuery();
        void testGenReverseIdx();
};


#endif