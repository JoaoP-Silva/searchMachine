#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <filesystem>
#include <fstream>
#include <set>
#include <algorithm>
#include <locale>
#include <codecvt>

using namespace std;

class searchEngine{
    private:
        //O indice invertido de uma palavra
        unordered_map<string, unordered_map<string, int>> reverseIdx;

        //Atributo madeReverseIndex para salvar se o indice reverso ja foi construido
        bool madeReverseIdx;
        //Atributo para salvar o numero de documentos mapeados
        int numFiles;

    //Metodos
    public:
        //Construtor vazio padrao
        searchEngine();

        //Testa se ja o indice reverso ja foi construido
        bool alreadyMadeReverseIdx();

        //Gera o indice reverso a partir de documentos no diretorio ../documentos
        void genReverseIdx();

        //Realiza consulta de um conjunto de palavras s e salva o resultado em um vetor res 
        void query(set<string> s, vector<string>& res);
        
    private:
        //Processa o caminho e nome dos arquivos presentes no diretorio ../documentos
        // e salva nos vetores de string filePaths e fileNames passados por referencia 
        void filePaths(vector<string>& filePaths, vector<string>& fileNames);

        //Retorna uma string normalizada a partir de S
        string* normalize(string s);

        //Insere item i lido no arquivo f no indice reverso
        void insertItem(string i, string f);

    friend class testSearchEngine;
};

#endif