#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "SafeHashTable.h"
#include <thread>

using namespace std;


void AddStuff1(SafeHashTable* table){
    table->insert("Hel!lo");
    table->addLocation("Hello", 1);
    table->addLocation("Hello", 2);
    table->addLocation("hello", 3);

    table->insert("tabl@e");
    table->insert("book.");
    table->insert("greeting ");
    table->insert(">kenya");
    table->insert("cup,");
    table->insert("glass-");
    table->insert("rocks");
    table->insert("socks");
    //table->insert("clocks");
}

void AddStuff2(SafeHashTable* table){
    //table->insert("twigs");
    table->insert("jigs");
    table->addLocation("hello", 4);
    table->addLocation("hello", 5);
    table->addLocation("hello", 6);
    table->insert("figs");
    table->insert("how.");
    table->insert("joe.");
    table->insert("coffee");
//    table->addLocation("coffee", 20);
    table->insert("bean");
//    table->addLocation("bean", 30);
    table->insert("camel");
//    table->addLocation("camel", 40);
    table->insert("cheese");
//    table->addLocation("cheese", 50);
}

int main()
{

    SafeHashTable* table = new SafeHashTable();
    cout << "Hello world!" << endl;
//    ifstream file;
//    file.open ("/home/joewashere/pp.txt");
//
//    string word;
//    long bytes = 0;
//    while (!file.eof())
//    {
//        long word_position = file.tellg();
//        file >> word;
//        if(!table->contains(word))
//            table->insert(word);
//        table->addLocation(word, word_position);
////        cout << word << " = " << sizeof(word) << " @ " << file.tellg() << endl;
////        bytes = file.tellp();
//////        cout << bytes << endl;
//    }

//
    cout << "Starting Treads!" << endl;
    thread first (AddStuff1, table);
    thread second (AddStuff2, table);


    first.join();


    second.join();


//    AddStuff1(table);
//    AddStuff2(table);

    cout << "\n\n\n========================= Final Table ===========\n";
    list<string>* keys = table->getKeys();
    keys->sort();

    for( auto it = keys->begin(); it != keys->end(); ++ it){
        table->get(*it)->print();
    }
    //table->print();
    cout << "Table Size " << table->size() << endl;
    cout << "Number of Keys: " << keys->size() << "vs Number of Elements:" << table->count() << endl;

    return 0;
}
