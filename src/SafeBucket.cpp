#include "SafeBucket.h"

SafeBucket::SafeBucket(){
    this->count  = 0;
    this->word = "";
    this->link = nullptr;
}

SafeBucket::SafeBucket(string s){
    this->count  = 0;
    this->link = nullptr;
    setWord(s);
}

SafeBucket::~SafeBucket(){
    if(link != nullptr){
        delete link;
    }
}

SafeBucket* SafeBucket::getLink(){
    return link;
}

void SafeBucket::setLink(SafeBucket* link){
    this->link = link;
}

void SafeBucket::setWord(string w){
    string::iterator s_begin = w.begin();
    string::iterator s_end = w.end();
    transform(s_begin, s_end, s_begin, ::tolower);
    string::iterator newEnd =  std::remove_if(s_begin, s_end, isSpecialChar);
    string result(s_begin, newEnd);
    this->word = result;
}

string SafeBucket::getWord(){
    return word;
}

bool SafeBucket::isSpecialChar(char c){
    return !isalnum(c);
}


int SafeBucket::hash(){
    char alpha;
    int exp = 0;
    int hashSum = 0;

    for (unsigned int i=0; i<word.length(); ++i)
    {
        alpha = tolower(word[i]);
        if (exp == 2)
            exp = 0;
        hashSum += alpha * (32 ^ exp);
        exp++;
    }
    return hashSum;
}

void SafeBucket::addLocation(long i){
    this->locations.push_back(i);
}

void SafeBucket::print(){
    cout << this->word << " (" << locations.size() << ")- " ;
    //const char* const delim = ", ";
    //std::ostringstream imploded;
    for ( auto it = locations.begin(); it != locations.end(); ++it){
        cout << (*it) << ", ";
    }
    //copy(locations.begin(), locations.end(), ostream_iterator<int>(imploded, delim));
    //<< imploded.rdbuf();
}
