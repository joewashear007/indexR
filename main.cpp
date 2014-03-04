#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "SafeHashTable.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    SafeHashTable* table = new SafeHashTable();
    ifstream file;
    file.open ("/home/joewashere/pp.txt");

    string word;
    long bytes = 0;
    while (!file.eof())
    {
        long word_position = file.tellg();
        file >> word;
        if(!table->contains(word))
            table->insert(word);
        table->addLocation(word, word_position);
//        cout << word << " = " << sizeof(word) << " @ " << file.tellg() << endl;
//        bytes = file.tellp();
////        cout << bytes << endl;
    }


//    table->insert("Hel!lo");
//    table->addLocation("Hel!lo", 34);
//    table->addLocation("Hello", 356);
//    table->addLocation("hello", 23);
//    table->insert("tabl@e");
//    table->insert("book.");
//    table->insert("greeting ");
//    table->insert(">kenya");
//    table->insert("cup,");
//    table->insert("glass-");
//    table->insert("how.");
//    table->insert("joe.");
//    table->insert("coffee");
//    table->addLocation("coffee", 345);
//    table->insert("bean");
//    table->addLocation("bean", 345);
//    table->insert("camel");
//    table->addLocation("camel", 345);
//    table->insert("cheese");
//    table->addLocation("cheese", 345);

    cout << "\n\n\n========================= Final Table ===========\n";
    list<string>* keys = table->getKeys();
    keys->sort();
    int nulls = 0;

    for( auto it = keys->begin(); it != keys->end(); ++ it){
        table->get(*it)->print();
    }
    //table->print();
    cout << "----- NUlls: " << nulls << endl;
    cout << "Tabke Size " << table->size() << endl;
    cout << "Number of Keys: " << keys->size() << "vs Number of Elements:" << table->count() << endl;

   // cout << "Ratio:" << (table->num_elemets / (double) table->table_size);
    return 0;
}
