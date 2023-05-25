#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>

using namespace std;

class searchEngine{
    private:
        //O indice invertido de uma palavra
        unordered_map<string, unordered_map<string, int>> reverseIdx;

        //Atributo madeReverseIndex para salvar se o indice reverso ja foi construido
        bool madeReverseIdx;

    //Metodos
    public:
        //Construtor vazio padrao
        searchEngine();

        //Testa se ja o indice reverso ja foi construido
        bool alreadyMadeReverseIdx();

        //Gera o indice reverso a partir de documentos no diretorio ../documentos
        void genReverseIdx();
        
    private:
        //Cria um vetor com o caminho de todos os arquivos no diretorio ../documentos
        vector<string>* filePaths();

        //Retorna uma string normalizada a partir de S
        string* normalize(wstring& s);

    friend class testSearchEngine;
};

#endif