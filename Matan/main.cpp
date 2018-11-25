//
//  main.cpp
//  CIS22C_Lab5
//
//  Created by Matan Broner on 11/17/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#include <iostream>
#include "BirthdayDatabase.h"
using namespace std;
int main()
{
    
    string outputFile;
    cout << "=== Welcome to the 'Name and Birthday Logger' ===" << endl << endl;
    
    cout << "Provide an INCOMPLETE file address for your NAMES and DATES output files [file will be named for you, provide only a path]" << endl;
    cout << "--> ";
    getline(cin, outputFile);
    
    BirthdayDatabase database(outputFile);
    database.displayMenu();
    
    return 0;
}
