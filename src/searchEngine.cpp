#include "searchEngine.h"

using namespace std;

searchEngine::searchEngine(){
    madeReverseIdx = false;
}

bool searchEngine::alreadyMadeReverseIdx(){
    return this->madeReverseIdx;
}

vector<string>* searchEngine::filePaths(){
    string path = filesystem::current_path();
    path += "/../documentos";
    vector<string>* documentsPaths = new vector<string>;

    for(auto& it : filesystem::directory_iterator(path)){
        if(it.path().filename() != ".gitignore"){
            documentsPaths->push_back(it.path());
        }
    }
    return documentsPaths;
}

string* searchEngine::normalize(wstring& s){

    //Mapeia todos os caracteres especiais até o seu caractere normalizado resultante
    unordered_map<wchar_t, char> specialCharMap = {
    {L'á', 'a'}, {L'à', 'a'}, {L'ã', 'a'}, {L'â', 'a'}, {L'ä', 'a'},
    {L'é', 'e'}, {L'è', 'e'}, {L'ê', 'e'}, {L'ë', 'e'},
    {L'í', 'i'}, {L'ì', 'i'}, {L'î', 'i'}, {L'ï', 'i'},
    {L'ó', 'o'}, {L'ò', 'o'}, {L'õ', 'o'}, {L'ô', 'o'}, {L'ö', 'o'},
    {L'ú', 'u'}, {L'ù', 'u'}, {L'û', 'u'}, {L'ü', 'u'},
    {L'ç', 'c'},
    {L'Á', 'a'}, {L'À', 'a'}, {L'Ã', 'a'}, {L'Â', 'a'}, {L'Ä', 'a'},
    {L'É', 'e'}, {L'È', 'e'}, {L'Ê', 'e'}, {L'Ë', 'e'},
    {L'Í', 'i'}, {L'Ì', 'i'}, {L'Î', 'i'}, {L'Ï', 'i'},
    {L'Ó', 'o'}, {L'Ò', 'o'}, {L'Õ', 'o'}, {L'Ô', 'o'}, {L'Ö', 'o'},
    {L'Ú', 'u'}, {L'Ù', 'u'}, {L'Û', 'u'}, {L'Ü', 'u'},
    {L'Ç', 'c'}, {L'ñ', 'n'}, {L'Ñ', 'n'}
};
    string* normalizedString = new string;
    wchar_t letter;
    for(unsigned i = 0; i < s.length(); i++){
        letter = s.at(i);
        auto it = specialCharMap.find(letter);
        if(it != specialCharMap.end()){ 
            normalizedString->push_back(it->second);
        }
        
        else if(isalnum(s[i])){
            char letter = (char)tolower(s[i]);
            normalizedString->push_back(letter);
        }
    }
    return normalizedString;
}

void searchEngine::genReverseIdx(){
    vector<string>* filePaths = searchEngine::filePaths();
    for(int i = 0; i < filePaths->size(); i++){
        //Open each path in filePaths
        wfstream f((*filePaths)[i], fstream::in);
        if(f.is_open()){
            while(!f.eof()){
                wstring word;
                f >> word;
                searchEngine::normalize(word);
            }
        }
    }
}