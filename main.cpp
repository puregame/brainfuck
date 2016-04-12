//
//  main.cpp
//  brainfuck
//
//  Created by Matthew Gougeon on 1/4/2014.
//  Copyright (c) 2014 Matthew Gougeon. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <errno.h>
int *p;

using namespace std;
int doCommand(char command, ifstream &inStream);

int main(int argc, const char * argv[])
{
    char command;
    int a[30000];
    p = &a[0];
    
    ifstream in_file;
    cout<<"What is the path of the input file? ";
    string inFilePath;
    cin >> inFilePath;
    in_file.open(inFilePath.c_str());
    
    if (in_file.fail()){
        cout <<"file open failed";
    }
    
    while ((command = in_file.get()) != EOF){ //keep running commands until the end of the file
        doCommand(command, in_file);
    }
    
    return 0;
}


int doCommand(char command, ifstream &inStream){
    char c;
    long int pos;
    
    switch(command){
        case '<':
            p--;
            break;
        case '>':
            p++;
            break;
        case '+':
            ++*p;
            break;
        case '-':
            --*p;
            break;
        case '.':
            cout <<(char)*p;
            break;
        case ',':
            *p = cin.get();
            break;
        case '[':
            pos = inStream.tellg();
            if(*p==0){ // go to end of loop (to ])
                int loopc = 0;
                for (;;){
                    c = inStream.get();
                    if (loopc ==0 && c ==']')break;
                    if (c=='[') loopc++;
                    if (c== ']') loopc--;
                }
            }
            else{
                while(true){ //loop through next code
                    c = inStream.get();
                    if (c == ']'){
                        if (*p==0){ // end loop
                            break;
                        }
                        else{ //continue loop from pos
                            inStream.seekg(pos);
                            continue;
                        }
                    }
                    else{// send command to doCommand
                        doCommand(c, inStream); //recursion is a beautiful thing
                        
                    }
                }
            }
    }
    return 0;
}
