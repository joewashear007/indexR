#include "SafeHashTable.h"

SafeHashTable::SafeHashTable(){
    //buckets = new vector<SafeBucket*>();
    this->prime_cnt = 1;
    this->fill_ratio = 0.75;
    this->num_elemets = 0;
    this->table_size = NextCubanPrime();
    this->buckets = new vector<SafeBucket*>(table_size, nullptr);
}

SafeHashTable::~SafeHashTable(){
    //delete buckets;
    //to do: delete elements
}

void SafeHashTable::insert(string w){
    insert(new SafeBucket(w));
}

void SafeHashTable::insert(SafeBucket* bucket){
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
    checkTableSize();

}
//
//SafeBucket* SafeHashTable::get(string w){
//    SafeBucket* temp_bucket = new SafeBucket(w);
//    SafeBucket* result = nullptr;
//
//    int loc = temp_bucket->hash() % table_size;
//
//    if(buckets->at(loc) != nullptr ){
//        if( buckets->at(loc)->getWord() == temp_bucket->getWord() ){
//            result = buckets->at(loc);
//        }else if{
//            SafeBucket* link = temp_bucketbuckets->at(loc)->getLink();
//            while( (link!= nullptr) && (result != nullptr) ){
//                if( link->getWord() == temp_bucket->getWord())
//                    result = link;
//                link = link->getLink();
//            }
//        }
//    }
//    delete temp_bucket;
//	return result;
//}

bool SafeHashTable::contains(string w){
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
	return found;
}

void SafeHashTable::checkTableSize(){
    double cur_ratio = this->num_elemets / (double) table_size;
    //cout << "Stats: " << this->num_elemets << "/" << table_size << "=" << cur_ratio << endl;
    if(cur_ratio > this->fill_ratio){
        cout << "The table needs to be resized! " << cur_ratio << ":" << this->fill_ratio << endl;
        //print();
        resize();
        //print();
    }else{
        //cout << "the table is still not full" << endl;
    }
}

void SafeHashTable::resize(){
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

    for( auto it = old_buckets->begin(); it != old_buckets->end(); ++it ){
        if ( (*it) != nullptr ){
            insert( (*it)->getWord() );
            delete (*it);
        }
    }
    delete old_buckets;
}

int SafeHashTable::NextCubanPrime(){
    //3y2 + 3y + 1 // Cuban Prime numbers
    prime_cnt += 3;
    return (3*prime_cnt*prime_cnt) + (3*prime_cnt) + 1;
}

void SafeHashTable::addLocation(string w, long offset){
    SafeBucket* temp_bucket = new SafeBucket(w);

    int loc = temp_bucket->hash() % table_size;
    bool found = false;

    if(buckets->at(loc) != nullptr ){
        if( buckets->at(loc)->getWord() == temp_bucket->getWord()){
            buckets->at(loc)->addLocation(offset);
            found = true;
        }else{
            SafeBucket* link = buckets->at(loc)->getLink();
            while( (link!= nullptr) ){
                if( link->getWord() == temp_bucket->getWord()){
                    buckets->at(loc)->addLocation(offset);
                    found = true;
                    break;
                }
                link = link->getLink();
            }
        }
    }
    delete temp_bucket;
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

