#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Movie.h"
#include "LibrarySystem.h"
/* This program is represented a basic Library Movie share system that uses 2 circular singly linked list and 1 circular doubly linked list to implement its operations.
    Each linked list were created by structs manually and at the end of the program all methods and their results were written in a file called 'output.txt'.
    Hacettepe University Computer Engineering Department
    Yavuz Emre Demirli
  */
using namespace std;

using namespace std;
int main(int argc, char* argv[] ){     // Our main method will take its argument from command line.
    string commandFile = argv[1];   
    string outputFile = argv[2];
    string line;
    vector<string> commands;        // I used vector here because lines in our commands.txt is unknown.    
    ifstream myFile(commandFile);
    if (myFile.is_open()){ 
        while(myFile.good()){
            getline(myFile,line);
            commands.push_back(line);
        }
        myFile.close(); 
    }
    else {
        cout << "Unable To Open File";  
    }
    LibrarySystem myLibrarySystem;  // I am creating our Library System here.
    myLibrarySystem.activateSystem(commands,outputFile); 
    return 0;
}

