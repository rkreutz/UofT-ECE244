#include <iostream>
#include <sstream>
#include <string>
#define MAX_NODE_NUMBER 10000
#define MIN_NODE_NUMBER 0
#define GOOD 0
#define BAD 1
#define CH_NOTHING -1	//I discovered this value peeking the char of a valid number (like an entry of 4 for a resistance) and then I printed the value of the peeked char (with the pointer already at the number 4) and that should be the char that haves nothing in it. I first tried to compare the char peeked with '\0'(something similar with the function 'arguments') but it didn't worked, so I printed the value of the char peeked to see what it was equal to, and seemed that all the times that the entry was valid we had the same value for the char peeked (-1).

using namespace std;

int arguments ( string last , string control ); 		//function to analise the number of arguments.
int node ( string x , string x2 , int *y , int *z);		//function to analise both nodes given by user.
int resistance ( string x , float *r );				//function to analise the resistance given by user.
int not_all ( string x );					//function to analise if string it's equal to 'all'.

void add ( stringstream &lineStream );		//
void changeR ( stringstream &lineStream );	//
void find ( stringstream &lineStream );		//		FUNCTIONS FOR EACH COMMAND
void list ( stringstream &lineStream );		//
void clear ( stringstream &lineStream );	//

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
	return GOOD;
}


//Will test if there is more or fewer arguments
int arguments ( string last , string control )
{
	if (last == "\0") {					//if the last argument of a function is the character '\0' (end of string) it will give an error message and return number 1.
		cout << "Error: missing argument\n";
		return BAD;
	}

	else if (control != "\0") {				//if there is more arguments than it should it will be stored as control in this function and will be tested
		cout << "Error: too many arguments\n";		//to se if it is a character '\0', otherwise it will print an error message and return 1.
		return BAD;
	}

	else
		return GOOD;					//if everything is ok it returns 0.
}


//Will test if both nodes are a numerical value, and after that it will test to see if both numbers are in the specific range.
int node ( string x , string x2 ,int *y ,int *z)
{
	stringstream str (x) , str2 (x2);	//will create 2 stringstreams, one for each node contained in the strings.
	char c1,c2;


	if( (! (str >> *y ) ) || (! (str2 >> *z) ) ) {		//will test if the strings contains valid values for the integers. It will see if putting the values in the variables will fail.
		cout << "Error: argument is not a number\n";	//will store the values of the strings in 2 integers pointers.
		return BAD;					//still remains a bug, if you digit a float value it will store only the value until the point, and won't report any errors. It wasn't specified what to do in this case (give an error report or change the value).
	}

	c1 = str.peek();
	c2 = str.peek();

	if ( c1 != CH_NOTHING || c2 != CH_NOTHING ) {		//will test if there is anything after the numbers. The char that was peeked must be equal to the defined value, that will say that the char peeked is actually nothing.
		cout << "Error: argument is not a number\n";
		return BAD;
	}	

	if (*y<MIN_NODE_NUMBER || *y>MAX_NODE_NUMBER) {
		cout << "Error: value " << *y << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;	//test if 'y' is out of 0-10000, if it does returns 1 and an error message is printed.
		return BAD;
	}

	if (*z>=MIN_NODE_NUMBER && *z<=MAX_NODE_NUMBER) {		//same test as in 'y' but it will test if 'z' is in the range of 0-10000,
		return GOOD;
	}
	else {
		cout << "Error: value " << *z << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;	//if it's not will return 1 and print an error message.
		return BAD;
	}
}


//First it will test if the resistance value is actually a numerical value, and after that will test if it is a positive number.
int resistance ( string x , float *r )
{
	float y;
	stringstream str (x);
	char c;

	if ( ! (str >> y)) {			//will test if putting the string into the float variable fails or not.
		cout << "Error: argument is not a number\n";
		return BAD;
	}

	c = str.peek();
	
	if ( c != CH_NOTHING ) {		//will test if there is anything after the numbers. The char that was peeked must be equal to the defined value, that will say that the char peeked is actually nothing.
		cout << "Error: argument is not a number\n";
		return BAD;
	}

	if (y>=0) {
		*r = y;
		return GOOD;				//it will test if the number is positive, and if is it will store the number in the float 'r' by a pointer.
	}
	else {
		cout << "Error: invalid resistance (negative)\n";
		return BAD;
	}
}


//It will test if the string it's equal to 'all'.
int not_all (string x)
{
	if ( x == "all")		//test if the string that was given is 'all'.
		return GOOD;
	else {
		cout << "Error: invalid argument: expected \"all\"\n";
		return BAD;
	}
}

//command add
void add ( stringstream &lineStream )
{
	string num1,num2,label,res,control;
	float r;
	int a,b;

	lineStream >> num1 >> num2 >> label >> res >> control;	//will continue storing the linestream in the respective variables.

	if ( arguments ( res , control ) != BAD ) {	//if the function returns 1, it will end this function, therefore ignoring all the other information.
		if ( node ( num1 , num2 , &a , &b) != BAD ) {	//same as above, and will determine the value of the nodes.
			if ( resistance ( res , &r ) != BAD) {	//same as above
				cout.precision(1);
				cout << "Added: resistor " << label << " " << fixed << r << " Ohms " << a << " -> " << b << endl;	//print the correct message. (with a fixed precision of 1 decimal unit)
			}							//the value of 'r' was given in the 'resistance' function by a pointer.
		}
	}
}

//command changeR
void changeR ( stringstream &lineStream )
{
	string label,res,control;
	float r;					//same as in the function above.

	lineStream >> label >> res >> control;		//stores variables

	if ( arguments ( res , control ) != BAD ) {	//test of conditions
		if ( resistance ( res , &r ) != BAD) {
			cout.precision(1);
			cout << "Changed: resistor " << label << " to " << fixed << r << " Ohms\n";	//if everything is ok, prints the correct phrase, with 1 decimal unit precision.
		}
	}
}

//command find
void find ( stringstream &lineStream )
{
	string label,control;

	lineStream >> label >> control;		//stores variables

	if ( arguments ( label , control ) != BAD ) {	//test condition
		cout << "Find: resistor " << label << endl;	//prints correct phrase.
	}
}

//command list
void list ( stringstream &lineStream )
{
	string al,control;

	lineStream >> al >> control;		//stores variables

	if ( arguments ( al , control ) != BAD) {	//test conditions
		if ( not_all ( al ) != BAD) {		
			cout << "List all\n";		//prints correct phrase.
		}
	}
}

//command clear
void clear ( stringstream &lineStream )
{
	string al,control;

	lineStream >> al >> control;		//same as in the function above

	if ( arguments ( al , control ) != BAD) {	//test conditions
		if ( not_all ( al ) != BAD ) {
			cout << "Clear all\n";		//prints correct phrase.
		}
	}
}
