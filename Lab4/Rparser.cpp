#include "Rparser.h"

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

	return GOOD;
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
void add ( stringstream &lineStream , NodeList* list_of_nodes)
{
	string num1,num2,label,res,control;
	double r;
	int a,b;
	lineStream >> num1 >> num2 >> label >> res >> control;

	if ( node ( num1 , num2 , &a , &b) != BAD ) {
	    if ( few_arg ( res ) != BAD ) {
		    if ( resistance ( res , &r ) != BAD ) {
			    if ( more_arg ( control ) != BAD) {
                    Resistor* check_existance;
                    check_existance = list_of_nodes->find_res(label);
                    if(check_existance == NULL){
                        if(a != b){
                            Node* pNode;
                            pNode = list_of_nodes->find(a);
                            if(pNode == NULL){
                                pNode = list_of_nodes->create(a);
                                ResistorList* p_list_res;
                                p_list_res = pNode ->get_res_list();
                                p_list_res ->add(label , r , a , b);
                                pNode ->addRes();
                                list_of_nodes->organize(pNode);
                            }
                            else{
                                ResistorList* p_list_res;
                                p_list_res = pNode ->get_res_list();
                                p_list_res ->add(label , r , a , b);
                                pNode ->addRes();
                            }
                            pNode = list_of_nodes->find(b);
                            if(pNode == NULL){
                                pNode = list_of_nodes->create(b);
                                ResistorList* p_list_res;
                                p_list_res = pNode ->get_res_list();
                                p_list_res ->add(label , r , a , b);
                                pNode ->addRes();
                                list_of_nodes->organize(pNode);
                            }
                            else{
                                ResistorList* p_list_res;
                                p_list_res = pNode ->get_res_list();
                                p_list_res ->add(label , r , a , b);
                                pNode ->addRes();
                            }
                            cout.precision(1);
                            cout << "Added: resistor " << label << " " << fixed << r << " Ohms " << a << " -> " << b << endl;
                        }
                        else{
                            cout << "Error: cannot connect a node to itself\n";
                        }
                    }
                    else{
                        cout << "Error: resistor " << label << " already exists\n";
                    }
			    }
		    }
	    }
    }
}

//command changeR
void changeR ( stringstream &lineStream , NodeList *list_of_nodes)
{
	string label,res,control;
	double r,r_old;

	lineStream >> label >> res >> control;

	if ( few_arg ( res ) != BAD ) {
		if ( resistance ( res , &r ) != BAD) {
            if ( more_arg ( control ) != BAD ) {
                Resistor* pRes;
                pRes = list_of_nodes->find_res(label);
                if(pRes == NULL)
                    cout << "Error: resistor " << label << " cannot be found\n";
                else{
                    r_old = pRes->getResistance();
                    pRes->setResistance(r);
                    int lastNode;
                    lastNode = pRes->get_last_endpoint();
                    Node* pNode;
                    pNode = list_of_nodes->find(lastNode);
                    ResistorList* p_res_list;
                    p_res_list = pNode ->get_res_list();
                    pRes = p_res_list ->find(label);
                    pRes->setResistance(r);
			        cout.precision(1);
			        cout << "Changed: resistor " << label << " from " << fixed << r_old << " Ohms to " << fixed << r << " Ohms\n";
                }
            }
		}
	}
}

//command find
void find ( stringstream &lineStream , NodeList *list_of_nodes)
{
	string label,control;

	lineStream >> label >> control;

	if ( few_arg ( label ) != BAD ) {
	    if ( more_arg (control) != BAD ) {
            Resistor* check_existance;
            check_existance = list_of_nodes->find_res(label);
            if (check_existance == NULL){
                cout << "Error: resistor " << label << " cannot be found\n";
            }
            else{
                cout << "Found: ";
                check_existance->print();
            }
        }
	}
}

//command list
void list ( stringstream &lineStream , NodeList *list_of_nodes)
{
	string al,control;
	lineStream >> al >> control;
    if ( few_arg ( al ) != BAD ) {
	    if ( not_all ( al ) != BAD) {
		    if ( more_arg (control) != BAD) {
                list_of_nodes->print();
            }
		}
	}
}

//command clear
void clear ( stringstream &lineStream , NodeList *list_of_nodes)
{
	string al,control;

	lineStream >> al >> control;

	if ( few_arg ( al ) != BAD ) {
	    if ( not_all ( al ) != BAD) {
		    if ( more_arg (control) != BAD) {
                list_of_nodes->clear();
			    cout << "Deleted all resistors\n";
            }
		}
	}
}

void remove ( stringstream &lineStream , NodeList *list_of_nodes){
    string label,control;

	lineStream >> label >> control;

	if ( few_arg ( label ) != BAD ) {
	    if ( more_arg (control) != BAD ) {
            Resistor* check_existance;
            check_existance = list_of_nodes->find_res(label);
            if (check_existance == NULL){
                cout << "Error: resistor " << label << " cannot be found\n";
            }
            else{
                int a,b;
                a = check_existance->get_first_endpoint();
                b = check_existance->get_last_endpoint();
                Node* A;
                Node* B;
                A = list_of_nodes->find(a);
                B = list_of_nodes->find(b);
                A->removeRes(label);
                B->removeRes(label);
                cout << "Removed: resistor " << label << endl;
            }
        }
	}
}

