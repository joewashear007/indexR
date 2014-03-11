/*
* Project2 - indexR
* EECS 3540 - Project 2
* Jospeh Livecchi
* Bucket Source - A thread safe bucket for a word and list of offsets.
        Also has a linked list for collisions
*/

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

/* -------------------------- Get Methods --------------- */

SafeBucket* SafeBucket::getLink(){
    return link;
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

void SafeBucket::print(){
    cout << this->word << " (" << locations.size() << ")- " ;
    sort(locations.begin(), locations.end() );
    for ( auto it = locations.begin(); it != locations.end(); ++it){
        cout << (*it) << ", ";
    }
    cout << endl;
}

/* ---------------- Set Methods that require a lock ------------ */

void SafeBucket::setLink(SafeBucket* link){
    mtx.lock();
    this->link = link;
    mtx.unlock();
}

void SafeBucket::addLocation(long i){
    mtx.lock();
    this->locations.push_back(i);
    mtx.unlock();
}

void SafeBucket::setWord(string w){
    mtx.lock();
    string::iterator s_begin = w.begin();
    string::iterator s_end = w.end();
    transform(s_begin, s_end, s_begin, ::tolower);
    string::iterator newEnd =  std::remove_if(s_begin, s_end, isSpecialChar);
    string result(s_begin, newEnd);
    this->word = result;
    mtx.unlock();
}
