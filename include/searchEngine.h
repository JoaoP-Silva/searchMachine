#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class searchEngine{
    private:
        //O indice invertido de uma palavra
        unordered_map<string, unordered_map<string, int>> reverseIndex;

        //Atributo madeReverseIndex para salvar se o indice reverso ja foi construido
        bool madeReverseIndex;

    //Metodos
    public:
        //Construtor vazio padrao
        searchEngine();

    private:
        //Gera o indice reverso a partir de documentos no diretorio ../documentos,
        void genReverseIndex();
        
};

#endif