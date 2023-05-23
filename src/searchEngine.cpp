#include "searchEngine.h"

searchEngine::searchEngine(){
    madeReverseIdx = false;
}

bool searchEngine::alreadyMadeReverseIdx(){
    return this->madeReverseIdx;
}