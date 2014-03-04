#include <iostream>
#include <fstream>
#include <string>
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

//
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

    cout << "\n\n\n========================= Final Table ===========\n";
    table->print();
   // cout << "Ratio:" << (table->num_elemets / (double) table->table_size);
    return 0;
}
