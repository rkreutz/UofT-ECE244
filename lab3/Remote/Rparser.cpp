#include "Rparser.h"

extern Node nodes[MAX_NODE_NUMBER+1];   //Array of nodes.
extern int resID;   //Index of the next resistor to be created, or number of resistors.
extern Resistor resArray[MAX_RESISTORS];    //Array of Resistors.

//Will test if there are more arguments
int more_arg ( string control )
{
	if (control != "\0") {				
		cout << "Error: too many arguments\n";
		return BAD;
	}

	else
		return GOOD;
}


//Will test if both nodes are a numerical value, and after that it will test to see if both numbers are in the specific range.
int node ( string x , string x2 ,int *y ,int *z)
{
	stringstream str (x) , str2 (x2);	
	char c1,c2;


	if( (! (str >> *y ) ) || (! (str2 >> *z) ) ) {		
		cout << "Error: argument is not a number\n";	
		return BAD;					
								
	}

	c1 = str.peek();
	c2 = str2.peek();

	if ( c1 != CH_NOTHING || c2 != CH_NOTHING ) {		
								
		cout << "Error: argument is not a number\n";
		return BAD;
	}	

	if (*y<MIN_NODE_NUMBER || *y>MAX_NODE_NUMBER) {
		cout << "Error: value " << *y << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;	
		return BAD;
	}

	if (*z>=MIN_NODE_NUMBER && *z<=MAX_NODE_NUMBER) {		
		return GOOD;
	}
	else {
		cout << "Error: value " << *z << " is out of permitted range 0-" << MAX_NODE_NUMBER << endl;	
		return BAD;
	}
}


//First it will test if the resistance value is actually a numerical value, and after that will test if it is a positive number.
int resistance ( string x , double *r )
{
	double y;
	stringstream str (x);
	char c;

	if ( ! (str >> y)) {			
		cout << "Error: argument is not a number\n";
		return BAD;
	}

	c = str.peek();
	
	if ( c != CH_NOTHING ) {		
						
		cout << "Error: argument is not a number\n";
		return BAD;
	}

	if (y>=0) {
		*r = y;
		return GOOD;				
	}
	else {
		cout << "Error: invalid resistance (negative)\n";
		return BAD;
	}
}


//It will test if the string it's equal to 'all'.
int not_all (string x)
{
	if ( x == "all")		
		return GOOD;
	else {
		cout << "Error: invalid argument: expected \"all\"\n";
		return BAD;
	}
}

//Test if there are fewer arguments
int few_arg ( string last ) {
    if ( last == "\0" ) {
        cout << "Error: missing argument\n";
        return BAD;
    }
    
    else
        return GOOD;
}

//command add
void add ( stringstream &lineStream )
{
	string num1,num2,label,res,control;
	double r;
	int a,b;

	lineStream >> num1 >> num2 >> label >> res >> control;	
    
	if ( node ( num1 , num2 , &a , &b) != BAD ) {	
	    if ( few_arg ( res ) != BAD ) {
		    if ( resistance ( res , &r ) != BAD ) {	
			    if ( more_arg ( control ) != BAD) {	
				    if ( resID < 20 ) {             //See if there is space in the array of resistors
                        		int endPoints[2] = {a,b};
                        		Resistor R ( resID, label, r, endPoints );  //creates a variable of Class 'Resistor' with the given inputs
                        		if ( nodes[a].addResistor(resID) ) {    //try to add the resistor in the node
                            			if ( nodes[b].addResistor(resID) ) {
                                			resArray[resID]= R;    //will store de resistor in our array
                               				 resID++;                        
                                			cout.precision(1);
				                	cout << "Added: resistor " << label << " " << fixed << r << " Ohms " << a << " -> " << b << endl;
                           		 	}
                            			else
                                		nodes[a].delResistor(resID);
                        		}
                    		    }
                    
                    		    else
                        		cout << "Error: resistor array is full\n";
			    }							
		    }
	    }
    	}
}

//command changeR                      
void changeR ( stringstream &lineStream )
{
	string label,res,control;
	double r;					

	lineStream >> label >> res >> control;		

	if ( few_arg ( res ) != BAD ) {	
		if ( resistance ( res , &r ) != BAD) {
            if ( more_arg ( control ) != BAD ) {
                int x,y = -1;
                for (x=0;x<resID;x++) {
                    if ( resArray[x].getName() == label )
                        y = x;
                }
                if (y == -1) {
                    cout << "Error: resistor " << label << " cannot be found\n";
                }
                else {
                    	double res = resArray[y].getResistance();
			resArray[y].setResistance(r);                        
			        cout.precision(1);
			        cout << "Changed: " << label << " from " << fixed << res << " Ohms to " << fixed << r << " Ohms\n";
                }
            }
		}
	}
}

//command find
void find ( stringstream &lineStream )
{
	string label,control;

	lineStream >> label >> control;		

	if ( few_arg ( label ) != BAD ) {	
	    if ( more_arg (control) != BAD ) {
            int x,y = -1;
            for (x=0;x<resID;x++) {
                if ( resArray[x].getName() == label )
                    y = x;
                }
            if (y == -1) {
                cout << "Error: resistor " << label << " cannot be found\n";
            }
            else {
		        cout << "Found: ";
		        resArray[y].print();
            }
        }
	}
}

//command list
void list ( stringstream &lineStream )
{
	string al,control;

	lineStream >> al >> control;		
    if ( few_arg ( al ) != BAD ) {
	    if ( not_all ( al ) != BAD) {	
		    if ( more_arg (control) != BAD) {	
                int x;
                for (x=0;x<=MAX_NODE_NUMBER;x++)
                    nodes[x].print(x);
            }
		}
	}
}

//command clear
void clear ( stringstream &lineStream )
{
	string al,control;

	lineStream >> al >> control;		

	if ( few_arg ( al ) != BAD ) {
	    if ( not_all ( al ) != BAD) {	
		    if ( more_arg (control) != BAD) {
                resID = 0;		
			    int x;
			    for (x=0;x<=MAX_NODE_NUMBER;x++)
			        nodes[x].clear();
			    cout << "Deleted all resistors\n";
            }
		}
	}
}

