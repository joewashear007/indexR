/*
* Project2 - indexR
* EECS 3540 - Project 2
* Jospeh Livecchi
* Hash Table Source - A thread safe hash table with read/write locks.
        dynamical resizes, collisions are handled by linked list
*/

#ifndef SAFEHASHTABLE_H
#define SAFEHASHTABLE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <mutex>
#include <pthread.h>
#include <unistd.h>
#include "SafeBucket.h"

using namespace std;

class SafeHashTable
{
    public:
        int NextCubanPrime();

        SafeHashTable();
        virtual ~SafeHashTable();
        void insert(string w);


        void print();

        bool contains(string w);
        void addLocation(string w, long offset);
        SafeBucket* get(string w);

        list<string>* getKeys();
        int count();
        int size();
        double ratio();
    private:
        int prime_cnt;
        int num_elemets;
        int table_size;
        double fill_ratio;
        pthread_rwlock_t table_lock;

        vector<SafeBucket*>* buckets;

        void insert(SafeBucket* bucket);
        void resize();
        void checkTableSize();
};

#endif // SAFEHASHTABLE_H
