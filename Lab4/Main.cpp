#include "Rparser.h"

int main()
{
    string line , command , str;
    NodeList list_of_nodes;
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
            add ( lineStream , &list_of_nodes);
		}

		else if (command == "changeR") {	//same
			changeR ( lineStream , &list_of_nodes);
		}

		else if (command == "find") {		//same
			find ( lineStream , &list_of_nodes);
		}

		else if (command == "list") {		//same
			list ( lineStream , &list_of_nodes);
		}

		else if (command == "clear") {		//same
            clear ( lineStream , &list_of_nodes);
		}

		else if (command == "remove") {
            remove (lineStream , &list_of_nodes);
		}

		else {
			cout << "Error: unknown command\n";		//if the command is not recognized: Error message.
		}
	}
	return 0;
}
