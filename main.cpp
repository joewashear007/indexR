/*
* Project2 - indexR
* EECS 3540 - Project 2
* Jospeh Livecchi
* Main Programs - handles cmd line args, spliting given file, starting threads, and printing out
*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "SafeHashTable.h"
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void printCommandLineError(){
    cout << "indexR: invaild options!" << endl;
    cout << "Try 'indexR --help' more options" << endl;
}

void printHelp(){
    cout << "indexR is a word frequency program" << endl;
    cout << "it will print out a sorted list of all the words in a document and there location in bytes" << endl;
    cout << endl;
    cout << "Usage:\n ./Project1 filename\n ./Project1 -f filename -t thread_count"
 << endl;
}

int getFileInfo(string filename, int thread_cnt){
    struct stat fileinfo;
    lstat(filename.c_str(), &fileinfo);
    long bytes = fileinfo.st_size;
    long bytes_to_read = bytes / thread_cnt;
    cout << "The file is " << bytes << " bytes long\n";
    cout << "Running " << thread_cnt << " threads, each thread will read " << bytes_to_read << endl << endl << endl;
    return bytes_to_read;
}

void ReadFileChunk(SafeHashTable* table,  string filename, long start, long lenght){
    ifstream file (filename, ios_base::in);
    string word;

    if(start > 1 ){
        file.seekg(start);
        if ( file.peek() != ' ' ){
            file >> word;
        }
    }

    bool readNext = true;
    while(readNext){
        long word_position = file.tellg();
        file >> word;
        if( file.good() ){
             if(!table->contains(word))
                table->insert(word);
            table->get(word)->addLocation(word_position);
            if ( ( file.tellg() > (start + lenght)) ){
                readNext = false;
            }
        }else{
            readNext = false;
        }

    }
}

int main(int argc, char* argv[]){
    string filename;
    int thread_cnt = 4;

    //---- Parse Arguments -----------------
    if(argc == 2){
        //args form: ./indexR file
        string arg = argv[1];
        if( arg == "--help"){
            printHelp();
            exit(EXIT_SUCCESS);
        }else{
            filename = arg;
        }
    }else if(argc == 5){
        // arg form: ./Project1 -f filename -t thread_count
        for(int i=1; i < argc; i++) {
            string arg(argv[i]);
            if (i + 1 != argc) {
                if (arg == "-f") {
                    filename = argv[i + 1];
                    i++;
                } else if (arg == "-t") {
                    thread_cnt = atoi(argv[i + 1]);
                    i++;
                } else if( (i+1) == argc ){
                    filename = argv[i];
                } else {
                    printCommandLineError();
                    exit(EXIT_FAILURE);
                }
            }
        }
    }else{
        // bad arg form
        printCommandLineError();
        exit(EXIT_FAILURE);
    }

    //---------------- Main Progam ------------
    SafeHashTable* table = new SafeHashTable();
    cout << "\nReading file: " << filename << endl;

    int bytes = getFileInfo(filename, thread_cnt);

    vector<thread*> threads;
    for(int i=0; i<thread_cnt ;i++){
        long start = i * bytes;
        threads.push_back(new thread (ReadFileChunk, table, filename, start, bytes) );
    }
    for (auto it=threads.begin(); it!=threads.end(); ++it){
        (*it)->join();
    }

    // ---------- Print out the result --------------------
    list<string>* keys = table->getKeys();
    keys->sort();

    for( auto it = keys->begin(); it != keys->end(); ++ it){
        table->get(*it)->print();
    }
    cout << "\n\nTable Size " << table->size() << ": " << table->ratio() << endl;
    cout << "Numnber of Elements: " << table->count() << endl << endl;

    return 0;
}
