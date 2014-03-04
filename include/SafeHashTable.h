#ifndef SAFEHASHTABLE_H
#define SAFEHASHTABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include "SafeBucket.h"

using namespace std;

class SafeHashTable
{
    public:
        int NextCubanPrime();

        SafeHashTable();
        virtual ~SafeHashTable();

        void insert(SafeBucket* bucket);
        void insert(string w);
        void print();

        bool contains(string w);
        void addLocation(string w, long offset);
        SafeBucket* get(string w);

        list<string>* getKeys();
        int count();
        int size();
    private:
        int prime_cnt;
        int num_elemets;
        int table_size;
        double fill_ratio;

        vector<SafeBucket*>* buckets;

        void resize();
        void checkTableSize();
};

#endif // SAFEHASHTABLE_H
