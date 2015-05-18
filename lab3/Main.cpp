#include "Rparser.h"

Node nodes[MAX_NODE_NUMBER+1];
int resID = 0;
Resistor resArray[MAX_RESISTORS];

int main()
{
    string line , command , str;
	while(1){
		cout << "> ";
		getline ( cin , line);

		if ( cin.eof() ) {
			cout << endl;			//Whend Ctrl + D is pressed it will print endl and close the program.
			break;
		}

		stringstream lineStream (line);

		lineStream >> command;

		if (command == "add") {			//if the command matches with the string it will run the function.
            add ( lineStream );
		}

		else if (command == "changeR") {	//same
			changeR ( lineStream );
		}

		else if (command == "find") {		//same
			find ( lineStream );
		}

		else if (command == "list") {		//same
			list ( lineStream );
		}

		else if (command == "clear") {		//same
			clear ( lineStream );
		}
		
		else {
			cout << "Error: unknown command\n";		//if the command is not recognized: Error message.
		}
	}
	return 0;
}
