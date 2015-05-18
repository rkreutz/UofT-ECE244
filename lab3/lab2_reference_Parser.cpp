/* 
 * File:   Parser.cpp
 * Author: Vaughn Betz
 *
 * Created on September 7, 2012, 5:59 AM
 * Parser program for lab 2 of ECE 244
 * This program does line-oriented parsing, by getting a line at a time
 * from cin, loading that line into a stringstream, and parsing the command
 * using stream commands.  The input is checked for all sorts of errors.
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define MAX_NODE_NUMBER 10000   // Largest allowed node number

// One function to parse each command
void parse_add (stringstream& lineStream);
void parse_change (stringstream& lineStream);
void parse_find (stringstream& lineStream);
void parse_list (stringstream& lineStream);
void parse_clear (stringstream& lineStream);

// Helper functions to parse and print error messages for each 
// type of argument
bool getNode (stringstream& lineStream, int& nodde);
bool getResistance (stringstream& lineStream, double& resistance);
bool getStringArg (stringstream& lineStream, string& argument);
bool checkKeyword (stringstream& lineStream, string keyword);
bool checkNoExtraArgs (stringstream& lineStream);


int main(int argc, char** argv) {
    
    string line, command;
    // Set output format for double numbers; fixed point, with 1 decimal place    
    cout.precision(1);   
    cout.setf(ios::fixed);
    
    // Get first set of input, and if not EOF, start parsing it. 
    // Keep parsing until EOF.
    
    cout << "> ";         // Prompt for input
    getline (cin, line);  // Get a line from standard input
    
    while ( !cin.eof () ) {
        // cout << line << endl;       // Uncomment to make sample session output.
        
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are in a known state
        stringstream lineStream (line);   
        lineStream >> command;
        
        if (lineStream.fail () ) {
           // No command entered. We'll call that unknown command.
            cout << "Error: unknown command\n";
        }
        else if (command == "add") {
            parse_add (lineStream);
        }
        else if (command == "changeR") {
            parse_change (lineStream);
        }
        else if (command == "find") {
            parse_find (lineStream);
        }
        else if (command == "list") {
            parse_list (lineStream);
        }
        else if (command == "clear") {
            parse_clear (lineStream);
        }
        else {
            cout << "Error: unknown command\n";
        }
        
        cout << "> ";          // Prompt for input
        getline (cin, line);
    }  // End input loop until EOF.
    
    return 0;
}


// All the parse_<commandName> routines work the same way. They parse the
// arguments for the command, passed in by reference in lineStream 
// (streams MUST be passed by reference; we need the stream to be updated
// as we extract characters, plus they can be too big to copy). As the functions
// parse arguments from left to right they print an error message if there is
// a problem, and immediately return to prevent any further (possibly 
// spurious) error messages from being printed.
// If we reach the end of the routine, the line is valid and we 
// print the appropriate output for that command.


void parse_add (stringstream& lineStream) {
    int node1, node2;
    double resistance;
    string label;
    
    if (!getNode (lineStream, node1))
        return;  // Error, skip rest of line.
    
    if (!getNode (lineStream, node2))
        return;  // Error, skip rest of line.
    
    if (!getStringArg (lineStream, label) )
        return;
    
    if (!getResistance (lineStream, resistance)) 
        return;   // Error, skip rest of line.
    
    if (!checkNoExtraArgs (lineStream) )
        return;
    
    cout << "Added: resistor " << label << " " << resistance  
            << " Ohms " << node1 << " -> " << node2 << endl;

}


void parse_change (stringstream& lineStream) {
    
    string label;
    double resistance;
    
    if (!getStringArg (lineStream, label) )
        return;
    
    if (!getResistance (lineStream, resistance) ) 
        return;
        
    if (!checkNoExtraArgs (lineStream) )
        return;
    
    cout << "Changed " << label << " to " << resistance << " Ohms\n";
}


void parse_find (stringstream& lineStream) {
    
    string label;
    
    if (!getStringArg (lineStream, label) )
        return;
    
    if (!checkNoExtraArgs (lineStream) )
        return;
    
    cout << "Find: resistor " << label << endl;
}


void parse_list (stringstream& lineStream) {
    
    if (!checkKeyword (lineStream, "all") ) 
        return;
    
    if (!checkNoExtraArgs (lineStream) )
        return;
    
    cout << "List all\n";
}


void parse_clear (stringstream& lineStream) {
    
    if (!checkKeyword (lineStream, "all") )
        return;
    
    if (!checkNoExtraArgs (lineStream) )
        return;
    
    cout << "Clear all\n";
}


bool getStringArg (stringstream &lineStream, string& label) {
    
    // Attempts to parse a string from lineStream. Returns the string 
    // by reference through label. If there is an error, print a message
    // and return false. Otherwise return true.
    
    lineStream >> label;  // No need to check for eof first, as only way this fails is EOF
    if (lineStream.fail()) {
        cout << "Error: missing argument\n"; 
        return (false);
    }
    return (true);
}


bool checkKeyword (stringstream& lineStream, string keyword) {
    // Checks that the next word in lineStream is keyword.
    // Returns true if it is.
    // Prints an error message and returns false otherwise.
    
    string argument;
    
    if (!getStringArg(lineStream, argument) )
        return (false);
    
    if (argument != keyword) {
        cout << "Error: invalid argument: expected \"" << keyword << "\"" << endl;
        return (false);
    }
    
    return (true);
}


bool getNode (stringstream& lineStream, int& node) {
    
    // Reads in a node (integer in a certain range) from lineStream. 
    // Prints error messages if appropriate. Returns the node number by
    // reference, and returns true if we successfully parsed it, false 
    // otherwise.
    
    lineStream >> node;
    
    if (lineStream.fail ()) {
        // Couldn't read. Did we have bad input, or no text left in the line?
        if (lineStream.eof () ) {
            cout << "Error: missing argument\n";
        }
        else {
            cout << "Error: argument is not a number\n";
        }
        return (false);
    }
    // Read an int.  Check that it has whitespace or nothing after it (not
    // non-digit characters spliced to it, e.g. 11kk is not a number).
    else if (lineStream.peek() != ' ' && lineStream.peek() != '\t' 
             && !lineStream.eof ()) {
        cout << "Error: argument is not a number\n";
        return (false);
    }
    else if (node < 0 || node > MAX_NODE_NUMBER) {
        cout << "Error: value " << node << " is out of permitted range 0-"
                << MAX_NODE_NUMBER << endl;
        return (false);
    }
    
    return (true);
}


bool getResistance (stringstream& lineStream, double& resistance) {
    
    // Parses a resistance value from lineStream. Prints error messages
    // if appropriate, and returns true if the resistance was successfully
    // parsed, false otherwise.

    lineStream >> resistance; 
    if (lineStream.fail ()) {
        // Failed to read.  Could be bad input, or end of line. 
        if (lineStream.eof () ) {
            cout << "Error: missing argument\n";
        }
        else {
           cout << "Error: argument is not a number\n";
        }
        return (false);
    }
    // Read a double.  Check that it has whitespace or nothing after it (not
    // non-digit characters spliced to it, e.g. 11kk is not a number).
    else if (lineStream.peek() != ' ' && lineStream.peek() != '\t' 
             && !lineStream.eof ()) {
        cout << "Error: argument is not a number\n";
        return (false);
    }
    else if (resistance < 0) {
        cout << "Error: invalid resistance (negative)\n";
        return (false);
    }
    
    return (true);
}


bool checkNoExtraArgs (stringstream& lineStream) {
    
    // Returns true if there is no input left in the lineStream, 
    // false otherwise.
    
    string extraArg;
    lineStream >> extraArg;
    
    if (!lineStream.fail ()) {
        cout << "Error: too many arguments\n";
        return (false);
    }
    
    return (true);
}
