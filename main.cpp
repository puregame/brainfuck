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
    
    in_file.open("/Users/matthewgougeon/Desktop/file.TXT", ios::binary);
    if (in_file.fail()){
        cout <<"file open failed";
    }
    while ((command = in_file.get()) != EOF){
        //cout <<"got command: " <<command<<" "<< in_file.tellg() << endl;
        doCommand(command, in_file);
    }
    
    //read size of the file and set a dynamic array to that size
    return 0;
}


int doCommand(char command, ifstream &inStream){
    char c;
    int pos;
    //cout << inStream.tellg()<<endl;
    
    
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
            if(*p==0){ // go to end of loop (to ]
                int loopc = 0;
                for (;;){
                    c = inStream.get();
                    if (loopc ==0 && c ==']')break;
                    if (c=='[') loopc++;
                    if (c== ']') loopc--;
                }
            }
            else{
                //inStream.seekg(pos);
                
                
                
                while(true){//loop through next code
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
                        doCommand(c, inStream);
                        
                    }
                }
            }
    }
    
    return 0;
}
