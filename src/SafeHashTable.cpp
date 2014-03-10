#include "SafeHashTable.h"

SafeHashTable::SafeHashTable(){
    //buckets = new vector<SafeBucket*>();
    this->prime_cnt = -1;
    this->fill_ratio = 0.75;
    this->num_elemets = 0;
    this->table_size = NextCubanPrime();
    this->buckets = new vector<SafeBucket*>(table_size, nullptr);
    pthread_rwlock_init(&table_lock, NULL);
}

SafeHashTable::~SafeHashTable(){
    pthread_rwlock_destroy(&table_lock);
    //delete buckets;
    //to do: delete elements
}

/* --------- Read Methods --------- */

SafeBucket* SafeHashTable::get(string w){
    SafeBucket* temp_bucket = new SafeBucket(w);
    SafeBucket* result = nullptr;

    pthread_rwlock_rdlock(&table_lock);
    int loc = temp_bucket->hash() % table_size;
    if(buckets->at(loc) != nullptr ){
        if( buckets->at(loc)->getWord() == temp_bucket->getWord() ){
            result = buckets->at(loc);
        }else{
            SafeBucket* link = buckets->at(loc)->getLink();
            while( (link!= nullptr) ){
                if( link->getWord() == temp_bucket->getWord()){
                    result = link;
                    break;
                }
                link = link->getLink();
            }
        }
    }
    pthread_rwlock_unlock(&table_lock);
    delete temp_bucket;
	return result;
}

bool SafeHashTable::contains(string w){
    pthread_rwlock_rdlock(&table_lock);
    SafeBucket* bucket = new SafeBucket(w);
    int loc = bucket->hash() % table_size;
    bool found = false;

    if(buckets->at(loc) == nullptr){
        found = false;
    }else if(buckets->at(loc)->getWord() == bucket->getWord()){
        found = true;
    }else{
        SafeBucket* link = buckets->at(loc)->getLink();
        while( (link!= nullptr) && !found ){
            if( link->getWord() == bucket->getWord())
                found = true;
            link = link->getLink();
        }
    }
    pthread_rwlock_unlock(&table_lock);
	return found;
}

void SafeHashTable::checkTableSize(){
    double cur_ratio = this->num_elemets / (double) table_size;
    if(cur_ratio > this->fill_ratio){
        cout << "The table needs to be resized! " << cur_ratio << ":" << this->fill_ratio << endl;
        resize();
    }
}

int SafeHashTable::NextCubanPrime(){
    //Cuban Prime numbers: 3y2 + 3y + 1
    prime_cnt += 3;
    return (3*prime_cnt*prime_cnt) + (3*prime_cnt) + 1;
}

int SafeHashTable::count(){
    pthread_rwlock_rdlock(&table_lock);
    return num_elemets;
    pthread_rwlock_unlock(&table_lock);
}

int SafeHashTable::size(){
    pthread_rwlock_rdlock(&table_lock);
    return table_size;
    pthread_rwlock_unlock(&table_lock);
}

double SafeHashTable::ratio(){
    pthread_rwlock_rdlock(&table_lock);
    return this->num_elemets / (double) table_size;
    pthread_rwlock_unlock(&table_lock);
}

void SafeHashTable::print(){
    cout <<"Table Size: " << table_size << endl;
    for (int i = 0; i < table_size; i++){

        if( buckets->at(i) != nullptr){
            cout << "[" << i << "] : ";
            buckets->at(i)->print();
            if(buckets->at(i)->getLink() != nullptr){
                SafeBucket* link = buckets->at(i)->getLink();
                while(link != nullptr){
                    cout << "\n\t -> ";
                    link->print();
                    link = link->getLink();
                }
            }
            cout << endl;
        }

    }
}

list<string>* SafeHashTable::getKeys(){
    pthread_rwlock_rdlock(&table_lock);
    list<string>* keys = new list<string>();
    for(auto it = buckets->begin(); it != buckets->end(); ++it){
        SafeBucket* item = (*it);
        while(item != nullptr){
            keys->push_back(item->getWord());
            item = item->getLink();
        }
    }
    pthread_rwlock_unlock(&table_lock);
    return keys;
}

/* -------------- Write Methods -------------- */

void SafeHashTable::insert(string w){
    insert(new SafeBucket(w));
}

void SafeHashTable::insert(SafeBucket* bucket){
    pthread_rwlock_wrlock(&table_lock);
    int loc = bucket->hash() % table_size;

    if( buckets->at(loc) == nullptr){
        buckets->at(loc) = bucket;
    }else{
        SafeBucket* link_element = buckets->at(loc);
        while(link_element->getLink() != nullptr){
            link_element = link_element->getLink();
        }
        link_element->setLink(bucket);
    }
    //cout << "Inserted @ : " << loc << endl;
    this->num_elemets++;
    pthread_rwlock_unlock(&table_lock);
    checkTableSize();
}

void SafeHashTable::addLocation(string w, long offset){
    pthread_rwlock_wrlock(&table_lock);
    SafeBucket* temp_bucket = new SafeBucket(w);

    int loc = temp_bucket->hash() % table_size;

    if(buckets->at(loc) != nullptr ){
        if( buckets->at(loc)->getWord() == temp_bucket->getWord()){
            buckets->at(loc)->addLocation(offset);
        }else{
            SafeBucket* link = buckets->at(loc)->getLink();
            while( (link!= nullptr) ){
                if( link->getWord() == temp_bucket->getWord()){
                    link->addLocation(offset);
                    break;
                }
                link = link->getLink();
            }
        }
    }
    pthread_rwlock_unlock(&table_lock);
    delete temp_bucket;
}

void SafeHashTable::resize(){
    pthread_rwlock_wrlock(&table_lock);
    int new_size = NextCubanPrime();
    cout << "=====================================================\n";
    cout << "Resizing!!! New Table size: " << new_size << endl;
    cout << "Old Table Data: " << buckets->size() << " Cap: "<< buckets->capacity() << endl;

    vector<SafeBucket*>* old_buckets = buckets;
    this->buckets = new vector<SafeBucket*>(new_size, nullptr);

    cout << "New Table Data: " << buckets->size() << " Cap: "<< buckets->capacity() << endl;
    cout << "=====================================================\n";

    num_elemets= 0;
    table_size = new_size;

    SafeBucket* temp_holder;
    SafeBucket* temp_link_holder;
    for( auto it = old_buckets->begin(); it != old_buckets->end(); ++it ){
        temp_holder = (*it);
        while(temp_holder != nullptr){
            temp_link_holder = temp_holder->getLink();
            temp_holder->setLink(nullptr);
            insert(temp_holder);
            temp_holder = temp_link_holder;
        }
    }
    pthread_rwlock_unlock(&table_lock);
    delete old_buckets;
}
