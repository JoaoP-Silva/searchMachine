#include "searchEngine.h"

using namespace std;

searchEngine::searchEngine(){
    this->madeReverseIdx = false;
    this->numFiles = 0;
}

bool searchEngine::alreadyMadeReverseIdx(){
    return this->madeReverseIdx;
}

void searchEngine::filePaths(vector<string>& filePaths, vector<string>& fileNames){
    string path = filesystem::current_path();
    path += "/documentos";

    for(auto& it : filesystem::directory_iterator(path)){
        if(it.path().filename() != ".gitignore"){
            filePaths.push_back(it.path());
            fileNames.push_back(it.path().filename());
        }
    }
}

string* searchEngine::normalize(string s){
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
    {L'Ç', 'c'}, {L'ñ', 'n'}, {L'Ñ', 'n'}   };
    
    string* normalizedString = new string;

    wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    wstring word = converter.from_bytes(s);

    for(unsigned i = 0; i < word.length(); i++){
        wchar_t letter = word.at(i);
        if(iswalnum(letter)){
            char l = towlower(letter);
            normalizedString->push_back(l);
        }else{
            auto it = specialCharMap.find(letter);
            if(it != specialCharMap.end()){
                normalizedString->push_back(it->second);
            }
        }
    }
    return normalizedString;
}

void searchEngine::genReverseIdx(){
    vector<string> filePaths, fileNames;
    searchEngine::filePaths(filePaths, fileNames);
    for(int i = 0; i < filePaths.size(); i++){
        string filePath = filePaths[i];
        string fileName = fileNames[i];
        //Open each path in filePaths
        fstream f(filePath, fstream::in);
        if(f.is_open()){
            while(!f.eof()){
                string word;
                f >> word;
                string* normalizedPtr = searchEngine::normalize(word);

                //Copia a string normalizada criada no metodo e apaga o ponteiro
                string normalized = *normalizedPtr;
                delete normalizedPtr;
                
                searchEngine::insertItem(normalized, fileName);
            }
        }
    }
    this->madeReverseIdx = true;
    this->numFiles = fileNames.size();
}

void searchEngine::insertItem(string i, string f){
    auto it = this->reverseIdx.find(i);
    if(it == this->reverseIdx.end()){
        unordered_map<string, int> stringToCount = { {f, 1} };
        this->reverseIdx.insert(make_pair(i, stringToCount));
    }else{
        unordered_map<string, int>& stringToCount = it->second;
        auto it2 = stringToCount.find(f);
        if(it2 == stringToCount.end()){
            stringToCount.insert(make_pair(f, 1));
        }else{
            stringToCount[f]+=1;
        }
    }
}



//Comparador para ordenar vetor de pares int e string 
struct greater_than_key
{
    inline bool operator() (const pair<int, string>& v1, const pair<int, string>& v2)
    {
        if(v1.first < v2.first){
            return (v2.first < v1.first);
        }else{
            return (v2.second > v1.second);
        }
    }
};

void searchEngine::query(set<string> s, vector<string>& res){
    vector<pair<int, string>> finded;
    unordered_map<string, int> findedIdx;
    int currIdx = 0;

    for(auto it = s.begin(); it != s.end(); it++){
        string word = *it;
        unordered_map<string, int> fileToCount = this->reverseIdx[word];
        if(fileToCount.size() < this->numFiles){ continue; }
        for(auto& it : fileToCount){
            string file = it.first; 
            int count = it.second;
            if(findedIdx.find(file) == findedIdx.end()){
                findedIdx.insert(make_pair(file, currIdx));
                currIdx++;
                finded.push_back(make_pair(count, file));
            }else{
                int i = findedIdx[file];
                finded[i].first += count;
            }
        }
    }
    sort(finded.begin(), finded.end(), greater_than_key());

    for(int i = 0 ; i < finded.size(); i++){
        res.push_back(finded[i].second);
    }
}