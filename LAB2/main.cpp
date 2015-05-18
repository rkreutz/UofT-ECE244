#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#define MAX_NODE_NUMBER 10000

using namespace std;

int arguments ( string last , string control );
int node ( string x , string x2);
int resistance ( string x , float *r);
int notall ( string x );
void add ( stringstream &lineStream );
void changeR ( stringstream &lineStream );
void find ( stringstream &lineStream );
void list ( stringstream &lineStream );
void clear ( stringstream &lineStream );

int main(int argc, char *argv[])
{
    string line , command ;
    char c;
    while(1){
        cout << "> ";
        getline ( cin , line );
        
        if ( cin.eof())
            return 0;
            
        stringstream lineStream ( line );
        
        lineStream >> command;
        
        if (command == "add"){
            add ( lineStream );
        }
        
        else if (command == "changeR") {
            changeR ( lineStream );
        }
                
        else if (command == "find") {
            find ( lineStream );
        }
        
        else if (command == "list") {
            list ( lineStream );
        }
        
        else if (command == "clear") {
            clear ( lineStream );
        }
            
        else
            cout << "Error: unknown command." << endl;
        
        
    }
}

int arguments ( string last , string control )
{
    if (last == "\0") {
        cout << "Error: fewer arguments were given then expected for a command.\n";
        return 1;
    }
    
    else if (control != "\0") {
        cout << "Error: more arguments were given then expected for a command.\n";
        return 1;
    }
    
    else return 0;
}

int node (string x , string x2)
{
    int y,z;
    stringstream str (x) , str1 , str2 (x2) , str3;
    
    str >> y;
    
    str2 >> z;

    if ( isdigit(str.str()) ) {
        cout << "Error: an argument that should be a number was provided a non-numerical value.\n";
        return 1;
    }
    
    if (y>=0&&y<=MAX_NODE_NUMBER) {
        NULL;
    }
    else {
        cout << "Error: value " << y << " is out of permited range 0 - " << MAX_NODE_NUMBER << endl;
        return 1;
    }
    if (z>=0&&z<=MAX_NODE_NUMBER) {
        return 0;
    }
    else {
        cout << "Error: value " << z << " is out of permited range 0 - " << MAX_NODE_NUMBER << endl;
        return 1;
    }
}

int resistance ( string x , float *r)
{
    float y;
    stringstream str (x) , str1;
    
    str >> y;
    str1 << y;
    
  
    
    if (y>=0) {
        *r = y;
        return 0;
    }
    else {
        cout << "Error: invalid resistance (negative).\n";
        return 1;
    }
}

int notall ( string x )
{
    if ( x == "all")
        return 0;
    else {
        cout << "Error: an argument of \"all\" was expected, but a different argument was given.\n";
        return 1;
    }
}

void add ( stringstream &lineStream )
{
    string num1,num2,label,res,control;
    float r;
    
    lineStream >> num1 >> num2 >> label >> res >> control;
    
    if ( arguments ( res , control ) != 1) {
        if ( node ( num1 , num2 ) != 1) {
            //if ( resistance ( res , &r) != 1) {
                cout.precision(1);
                cout << "Added: resistor " << label << " " << res << " Ohms " << num1 << " -> " << num2 << endl;
            }
        }
    }


void changeR ( stringstream &lineStream )
{
    string label,res,control;
    float r;
    
    lineStream >> label >> res >> control;
    
    if ( arguments ( res , control ) != 1) {
        if ( resistance ( res , &r ) != 1) {
            cout.precision(1);
            cout << "Changed: Resistor " << label << " to " << fixed << r << " Ohms.\n";
        }
    }
}

void find ( stringstream &lineStream )
{
    string label,control;
    
    lineStream >> label >> control;
    
    if ( arguments ( label , control ) != 1) {
        cout << "Find: resistor " << label << endl;
    }
}

void list ( stringstream &lineStream )
{
    string al,control;
    
    lineStream >> al >> control;
    
    if ( arguments ( al , control ) != 1) {
        if ( notall ( al ) != 1) {
            cout << "List all\n";
        }
    }
}

void clear ( stringstream &lineStream )
{
    string al,control;
    
    lineStream >> al >> control;
    
    if ( arguments ( al , control ) != 1) {
        if ( notall ( al ) != 1) {
            cout << "Clear all\n";
        }
    }
}
