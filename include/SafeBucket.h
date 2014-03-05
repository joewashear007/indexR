#ifndef SAFEBUCKET_H
#define SAFEBUCKET_H
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <mutex>

using namespace std;

class SafeBucket
{
    public:
        static bool isSpecialChar(char c);

        SafeBucket();
        SafeBucket(string s );
        virtual ~SafeBucket();

        int hash();
        int count;

        void setLink(SafeBucket* link);
        SafeBucket* getLink();

        void setWord(string w);
        string getWord();

        void addLocation(long i);

        void print();
    private:
        string word;
        SafeBucket* link;
        vector<long> locations;
};



#endif // SAFEBUCKET_H
